#include <thread>
#include <functional>  //函数包装器
#include <vector>
#include <string>
#include <shared_mutex>
#include <atomic>      //原子操作
#include <queue>
#include <future>      //异步函数容器
#include <stdexcept>   //异常
#include <concepts>    //概念/ 约束特定的函数传参类型
#include <memory>      //智能指针
#include <type_traits> //类型萃取
#include <chrono>      //时间
#include "Syncs.hpp"   //MPMC队列

using task_function = std::function<void()>;
namespace con
{
  /**
   * @brief 线程池
   * @note - 线程池的线程数是根据任务的数量自动动态调整的
   */
  class thread_pool
  {
    struct thread_status
    {
      std::jthread _thread;
      std::stop_source _stop_src; //令牌
      std::chrono::steady_clock::time_point _last_active; //上次活动时间
    };

    std::string _name; //线程池标识

    static constexpr uint64_t _default_threads = 5;
    static constexpr uint64_t _default_min_threads = 1;
    static constexpr uint64_t _default_max_threads = 32;

    static constexpr std::chrono::milliseconds _dormancy  = std::chrono::milliseconds(5);   //线程休眠时间
    static constexpr std::chrono::milliseconds _frequency = std::chrono::milliseconds(1000);//调整频率
    static constexpr std::chrono::milliseconds _timeout   = std::chrono::milliseconds(20);  //线程超时时间

    mutable std::mutex _mutex; //线程池锁
    mutable std::mutex _name_mutex; //线程池标识称锁
    mutable std::shared_mutex _exclusive_mutex;  //回调函数锁

    uint64_t _max_threads;
    uint64_t _min_threads;

    std::condition_variable _condtion;
    std::atomic<bool> _shutdown{false}; //关闭标识

    std::atomic<uint64_t> _execute_threads;   //运行线程数
    std::atomic<uint64_t> _closure_threads;   //空闲线程数

    std::jthread _monitoring_thread; //后台监控线程
    producers_consumers_queue<task_function> _tasks; //任务队列
    alignas(CACHE_ALIGNMENT) std::vector<thread_status> _workers_thread; //线程池

    std::function<void(const std::exception &)> _exception_callback; //异常回调函数

    /**
     * @brief - 扩容到指定的线程数
     * @brief - 只增加超过最大线程数的空闲线程
     */
    void expand_capacity(uint64_t counter)
    {
      if (counter == 0)
        return;
      std::lock_guard<std::mutex> lock(_mutex);
      for (uint64_t i = 0; i < counter; ++i)
      {
        thread_status initial;
        initial._last_active = std::chrono::steady_clock::now();
        _workers_thread.emplace_back(std::move(initial));
        auto &worker = _workers_thread.back();
        auto task = [this, &worker]()
        {
          this->thread_task(worker._stop_src.get_token(), std::ref(worker));
        };
        worker._thread = std::jthread(task);
        ++_closure_threads;
      }
    }
    /**
     * @brief - 缩容指定的线程数
     * @brief - 只停止超过最小线程数的空闲线程
     */
    void shrink_capacity(uint64_t counter)
    {
      if (counter == 0 || _shutdown)
        return;
      std::lock_guard<std::mutex> lock(_mutex);
      uint64_t removed = 0;
      auto now = std::chrono::steady_clock::now();
      auto it = _workers_thread.begin();
      uint64_t current_threads = _execute_threads + _closure_threads;
      while (removed < counter && it != _workers_thread.end())
      {
        if (current_threads > _min_threads && (now - it->_last_active) >= _timeout)
        {
          it->_stop_src.request_stop();
          if (it->_thread.joinable())
          {
            it->_thread.join();
          }
          it = _workers_thread.erase(it);
          ++removed;
          --_closure_threads;
          --current_threads;
        }
        else
          ++it;
      }
    }
    /**
     * @brief 工作线程任务逻辑
     * @brief - 循环获取任务并执行
     * @brief - 处理线程状态转换（空闲/工作）
     * @brief - 响应停止请求
     */
    void thread_task(std::stop_token stop_tok, thread_status &status)
    {
      bool idle = true;
      while (!stop_tok.stop_requested() && !_shutdown)
      {
        task_function task;
        if (_tasks.pop(task))
        {
          idle ? (_closure_threads -= 1, _execute_threads += 1, idle = false) : false;
          try
          {
            task();
          }
          catch (const std::exception &mistake)
          {
            std::unique_lock<std::shared_mutex> lock(_exclusive_mutex);
            if (_exception_callback)
              _exception_callback(mistake);
            else
              std::cerr << mistake.what() << '\n';
          }
          status._last_active = std::chrono::steady_clock::now();
        }
        else
        {
          if (!idle)
          {
            _execute_threads -= 1;
            _closure_threads += 1;
            idle = true;
            status._last_active = std::chrono::steady_clock::now();
          }
          std::unique_lock<std::mutex> lock(_mutex);
          auto wait_function = [this, stop_tok]()
          {
            return stop_tok.stop_requested() || !_tasks.empty() || _shutdown;
          };
          _condtion.wait_for(lock, _dormancy, wait_function);
        }
      }
      idle ? --_closure_threads : --_execute_threads;
    }
    /**
     * @brief 监控线程池任务
     * @brief - 根据任务数量动态调整线程池大小
     * @brief - 调整频率为500ms调整一次
     * @note - 扩容逻辑：任务数超过当前线程数的两倍时，增加线程数
     * @note - 缩容逻辑：任务数少于当前线程数时，减少线程数
     */
    void monitoring_thread_func(std::stop_token stop_tok)
    {
      while (!stop_tok.stop_requested() && !_shutdown)
      {
        std::this_thread::sleep_for(_frequency);
        uint64_t current_threads = _execute_threads + _closure_threads;
        uint64_t tasks_count = _tasks.size();
        if (tasks_count > _execute_threads * 2 && current_threads < _max_threads)
        {
          const uint64_t standard_number = (tasks_count + 1) / 2;
          const uint64_t increase_threads = std::min(standard_number, _max_threads - current_threads);
          expand_capacity(increase_threads);
        }
        else if (tasks_count < _execute_threads && current_threads > _min_threads)
        {
          const uint64_t standard_number = current_threads - _min_threads;
          const uint64_t decrease_threads = std::min(standard_number, _closure_threads.load());
          shrink_capacity(decrease_threads);
        }
      }
    }
  public:
    /**
     * @brief 构造函数：支持自定义线程池参数
     * @param init_threads 初始线程数（默认5）
     * @param min_threads 最小线程数（默认1）
     * @param max_threads 最大线程数（默认32）
     */
    thread_pool(uint64_t init_threads = _default_threads, uint64_t min = _default_min_threads,
        uint64_t max = _default_max_threads) : _max_threads(max), _min_threads(min), _execute_threads(0),
                    _closure_threads(0), _tasks(max * 2), _workers_thread(max)
    {
      if (init_threads > max || init_threads < min || min > max)
      {
        throw std::invalid_argument("非法参数");
      }
      expand_capacity(init_threads);
      auto monitoring = [this](std::stop_token stop_tok)
      {
        this->monitoring_thread_func(stop_tok);
      };
      _monitoring_thread = std::jthread(monitoring);
    }
    thread_pool(const thread_pool &) = delete;
    thread_pool(thread_pool &&) = delete;
    thread_pool &operator=(const thread_pool &) = delete;
    thread_pool &operator=(thread_pool &&) = delete;
    /**
     * @brief 提交任务到线程池
     * @param task 任务函数
     * @param args 任务参数
     * @return `std::future<return_type>` 任务结果
     */
    template <class... Args, std::invocable<Args...> func>
    auto submit(func &&task_value, Args &&...args)
    -> std::future<std::invoke_result_t<func, Args...>>
    {
      using return_type = std::invoke_result_t<func, Args...>;
      auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<func>(task_value), std::forward<Args>(args)...));
      std::future<return_type> result = task->get_future();
      _tasks.push([task](){ (*task)(); });
      _condtion.notify_one();
      return result;
    }
    /**
     * @brief 获取当前正在执行任务的线程数
     */
    uint64_t active_threads() const 
    {
      return _execute_threads.load(std::memory_order_acquire);
    }

    /**
     * @brief 获取当前空闲线程数
     */
    uint64_t idle_threads() const 
    {
      return _closure_threads.load(std::memory_order_acquire);
    }

    /**
     * @brief 获取当前线程池中线程数量
     */
    uint64_t total_threads() const 
    {
      return active_threads() + idle_threads();
    }
    /**
     * @brief 设置任务异常的回调函数
     */
    void set_exception_handler(std::function<void(const std::exception &)> error_callback)
    {
      std::unique_lock<std::shared_mutex> lock(_exclusive_mutex);
      _exception_callback = std::move(error_callback);
    }
    /**
     * @brief 设置线程池标识
     */
    void set_thread_name(const std::string &name)
    {
      std::lock_guard<std::mutex> lock(_name_mutex);
      _name = std::move(name);
    }
    /**
     * @brief  获取线程池标识
     */
    std::string get_thread_name() const
    {
      std::lock_guard<std::mutex> lock(_name_mutex);
      return _name;
    }
    /**
     * @brief 关闭任务队列
     */
    void close_task_queue()
    {
      _tasks.close();
    }
    /**
     * @brief 启用任务队列
     */
    void enable_task_queue()
    {
      _tasks.enable();
    }
    /**
     * @brief 清空任务队列
     */
    void clear_task_queue()
    {

      _tasks.clear();
    }
    /**
     * @brief 获取当前线程池中的任务数
     */
    uint64_t get_task_size() const
    {
      return _tasks.size();
    }
    /**
     * @brief 设置线程池最小线程数
     */
    bool set_min_threads(uint64_t min)
    {
      if(min == 0 || min > _max_threads || _shutdown)
      {
        return false;
      }
      std::lock_guard<std::mutex> lock(_mutex);
      _min_threads = min;
      uint64_t current_threads = total_threads();
      if (current_threads < min)
      {
        expand_capacity(min - current_threads);
      }
      return true;
    }
    /**
     * @brief 设置线程池最大线程数
     */
    bool set_max_threads(uint64_t max)
    {
      if(max == 0 || max < _min_threads || _shutdown)
      {
        return false;
      }
      std::lock_guard<std::mutex> lock(_mutex);
      _max_threads = max;
      uint64_t current_threads = total_threads();
      if (current_threads > max)
      {
        shrink_capacity(current_threads - max);
      }
      return true;
    }
    /**
     * @brief  增加线程数
     * @param increase_threads 
     */
    void increase_threads(uint64_t increase_threads)
    {
      if(increase_threads == 0 || _shutdown) return;
      expand_capacity(increase_threads);
    }
    /**
     * @brief 减少线程数
     * @param decrease_threads 
     */
    void decrease_threads(uint64_t decrease_threads)
    {
      if(decrease_threads == 0 || _shutdown) return;
      shrink_capacity(decrease_threads);
    }
    /**
     * @brief 析构函数：销毁线程池
     */
    ~thread_pool()
    {
      _shutdown.store(true, std::memory_order_release);
      if (_monitoring_thread.joinable())
      {
        _monitoring_thread.request_stop();  
        _monitoring_thread.join();       
      }
      _tasks.close();
      {
        std::lock_guard<std::mutex> lock(_mutex);
        for (auto& worker : _workers_thread)
        {
            worker._stop_src.request_stop(); 
        }
        _condtion.notify_all();
      }
      std::vector<std::jthread> threads_to_join;
      {
        std::lock_guard<std::mutex> lock(_mutex);
        for (auto& worker : _workers_thread)
        {
          if (worker._thread.joinable())
          {
            threads_to_join.emplace_back(std::move(worker._thread));  
          }
        }
        _workers_thread.clear(); 
      }
      for (auto& thread : threads_to_join)
      {
        thread.join();
      }
    }
  };
}
