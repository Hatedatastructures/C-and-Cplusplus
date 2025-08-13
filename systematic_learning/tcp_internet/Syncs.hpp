#pragma once
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <semaphore>
#include <thread>
#include <vector>
#include <unordered_map>
#include <shared_mutex>
static constexpr uint64_t CACHE_ALIGNMENT = 64;
namespace con
{
  /**
  * @brief #### 单生产单消费无锁队列类`SPSC`
  * @tparam  object_type 数据类型
  * @warning 在严格 `SPSC` 场景下，容器保证线程安全
  **/
  template<typename object_type>
  class pro_con_queue
  {
    static constexpr uint64_t _default_capacity = 10;
  private:
    std::atomic<uint64_t> _producer; // 生产者位置
    std::atomic<uint64_t> _consumer; // 消费者位置

    const uint64_t _current_capacity; // 当前容量

    alignas(CACHE_ALIGNMENT) std::vector<object_type> _shared_circular_queue; // 环形队列
    uint64_t compute_position(uint64_t index) const
    { 
      return index % _current_capacity;
    }
  public:
    explicit pro_con_queue(const uint64_t new_capacity = _default_capacity):_producer(0),_consumer(0),
    _current_capacity(std::max(new_capacity,static_cast<uint64_t>(1))),_shared_circular_queue(_current_capacity){}
    pro_con_queue(const pro_con_queue& another_queue) = delete;
    pro_con_queue(pro_con_queue&& another_queue) noexcept = delete;
    pro_con_queue& operator=(const pro_con_queue& another_queue) = delete;
    pro_con_queue& operator=(pro_con_queue&& another_queue) noexcept = delete;
    /**
     * @brief #### 向队列添加数据
     * @param produce_data 生产数据
     * @return 是否成功
     */
    bool push(object_type&& produce_data)
    {
      const uint64_t current_producer = _producer.fetch_add(1,std::memory_order_relaxed);
      const uint64_t position = compute_position(current_producer);

      if(current_producer - _consumer.load(std::memory_order_acquire) >= _current_capacity)
      {
        _producer.fetch_sub(1,std::memory_order_release);
        return false;
      }
      _shared_circular_queue[position] = std::forward<object_type>(produce_data);
      std::atomic_thread_fence(std::memory_order_release);
      return true;
    }
    /**
     * @brief #### 从队列中取出数据
     * @param consume_data 
     * @return 是否成功
     */
    bool pop(object_type& consume_data)
    {
      const uint64_t current_consumer = _consumer.fetch_add(1,std::memory_order_relaxed);
      const uint64_t position = compute_position(current_consumer);

      if(current_consumer >= _producer.load(std::memory_order_acquire))
      {
        _consumer.fetch_sub(1,std::memory_order_release);
        return false;
      }
      std::atomic_thread_fence(std::memory_order_acquire);
      consume_data = _shared_circular_queue[position];
      return true;
    }
    bool empty() const
    {
      return _consumer.load(std::memory_order_acquire) == _producer.load(std::memory_order_acquire);
    }
    bool full() const
    {
      return _producer.load(std::memory_order_acquire) - _consumer.load(std::memory_order_acquire) == _current_capacity;
    }
    uint64_t size() const
    {
      return _producer.load(std::memory_order_acquire) - _consumer.load(std::memory_order_acquire);
    }
  };
  /**
   * @brief #### 多生产多消费有锁队列类`MPMC`
   * @tparam object_type 数据类型
   */
  template<typename object_type>
  class pros_cons_queue
  {
    static constexpr uint64_t _default_capacity = 10;
  private:
    mutable std::mutex _access_mutex; // 访问锁

    uint64_t _current_capacity; // 当前容量

    std::atomic<bool> _close_id = false; // 关闭标识

    std::condition_variable _produce_condition; // 生产者条件变量
    std::condition_variable _consume_condition; // 消费者条件变量

    alignas(CACHE_ALIGNMENT) std::queue<object_type> _shared_queue; // 共享队列
    /**
     * @brief 判断队列是否满
     * @return 满返回 `true`，否则返回 `false`
     */
    bool full_internal() const
    {
      return _shared_queue.size() == _current_capacity;
    }
    /**
     * @brief 判断队列是否为空
     * @return 空返回 `true`，否则返回 `false`
     */
    bool empty_internal() const
    {
      return _shared_queue.empty();
    }
    /**
     * @brief 入队，不保证线程安全
     * @tparam enqueue_type
     */
    template<typename enqueue_type>
    void enqueue(enqueue_type && produce_data)
    {
      _shared_queue.push(std::forward<enqueue_type>(produce_data));
    }
  public:
    pros_cons_queue(const uint64_t new_capacity = _default_capacity)
    :_current_capacity(std::max(new_capacity,static_cast<uint64_t>(1))){}
    pros_cons_queue(const pros_cons_queue& another_queue) = delete;
    pros_cons_queue(pros_cons_queue&& another_queue) noexcept = delete;
    pros_cons_queue& operator=(const pros_cons_queue& another_queue) = delete;
    pros_cons_queue& operator=(pros_cons_queue&& another_queue) noexcept = delete;
    /**
     * @brief  #### 阻塞式入队，队列满时等待
     * @tparam push_type
     * @param produce_data
     * @return 成功返回 `true`，队列关闭已关闭返回 `false`
     */
    template<typename push_type>
    bool push(push_type&& produce_data)
    {
      std::unique_lock<std::mutex> access_lock(_access_mutex);
      while(full_internal() && !_close_id)
      {
        _produce_condition.wait(access_lock);
      }
      if(_close_id) return false;
      enqueue(std::forward<push_type>(produce_data));
      access_lock.unlock();
      _consume_condition.notify_one();
      return true;
    }
    /**
     * @brief  #### 非阻塞式入队，不等待
     * @tparam try_push_type
     * @param produce_data
     * @return 成功返回 `true`，队列关闭已关闭返回 `false`
     */
    template<typename try_push_type>
    bool try_push(try_push_type&& produce_data)
    {
      std::unique_lock<std::mutex> access_lock(_access_mutex,std::try_to_lock);
      if(!access_lock.owns_lock()) return false;
      if(_close_id.load(std::memory_order_relaxed) || full_internal()) return false;
      enqueue(std::forward<try_push_type>(produce_data));
      access_lock.unlock();
      _consume_condition.notify_one();
      return true;
    }
    /**
     * @brief  #### 限时入队，超时返回
     * @tparam precision
     * @tparam period
     * @param produce_data
     * @param time_out
     * @return 成功返回 `true`，超时 / 关闭返回 `false`
     */
    template<typename push_for_type, typename precision, typename period>
    bool push_for(push_for_type&& produce_data,const std::chrono::duration<precision, period> time_out)
    {
      std::unique_lock<std::mutex> access_lock(_access_mutex);
      auto status = _produce_condition.wait_for(access_lock,time_out,[this](){return !full_internal() || _close_id;});
      if(_close_id || status == std::cv_status::timeout) return false;
      enqueue(std::forward<push_for_type>(produce_data));
      access_lock.unlock();
      _consume_condition.notify_one();
      return true;
    }
    /**
     * @brief #### 阻塞式出队，队列空时等待
     * @return 成功返回 `true`，失败（锁竞争 / 空 / 关闭）返回 `false`
     */
    bool pop(object_type& consume_data)
    {
      std::unique_lock<std::mutex> access_lock(_access_mutex);
      while(empty_internal() && !_close_id)
      {
        _consume_condition.wait(access_lock);
      }
      if(_close_id && empty_internal()) return false;
      consume_data = std::move(_shared_queue.front());
      _shared_queue.pop();
      access_lock.unlock();
      _produce_condition.notify_one();
      return true;
    }
    /**
     * @brief  #### 非阻塞式出队，不等待
     * @return 成功返回 `true`，失败（锁竞争 / 空 / 关闭）返回 `false`
     */
    bool try_pop(object_type& consume_data)
    {
      std::unique_lock<std::mutex> access_lock(_access_mutex,std::try_to_lock);
      if(!access_lock.owns_lock()) return false;
      if(_close_id.load(std::memory_order_relaxed) || empty_internal()) return false;
      consume_data = _shared_queue.front();
      _shared_queue.pop();
      access_lock.unlock();
      _produce_condition.notify_one();
      return true;
    }
    /**
     * @brief  #### 限时出队，超时返回
     * @tparam precision 
     * @tparam period 
     * @param consume_data 
     * @param time_out 
     * @return 成功返回 `true`，超时 / 关闭返回 `false`
     */
    template<typename precision, typename period>
    bool pop_for(object_type& consume_data,const std::chrono::duration<precision, period> time_out)
    {
      std::unique_lock<std::mutex> access_lock(_access_mutex);
      auto status = _consume_condition.wait_for(access_lock,time_out,[this](){return !empty_internal() || _close_id;});
      if((_close_id && empty_internal()) || status == std::cv_status::timeout) return false;
      consume_data = _shared_queue.front();
      _shared_queue.pop();
      access_lock.unlock();
      _produce_condition.notify_one();
      return true;
    }
    /**
     * @brief #### 关闭队列，关闭后无法再入队或出队
     * @warning - 关闭后无法再入队
     */
    void close() 
    {
      if(_close_id.load(std::memory_order_acquire)) return;
      std::unique_lock<std::mutex> access_lock(_access_mutex);
      if(_close_id) return;
      _close_id.store(true,std::memory_order_release);
      access_lock.unlock();

      _produce_condition.notify_all();
      _consume_condition.notify_all();
    }
    void clear()
    {
      std::lock_guard<std::mutex> lock(_access_mutex);
      while(!empty_internal())
      {
        _shared_queue.pop();
      }
    }
    void enable()
    {
      if(!_close_id.load(std::memory_order_acquire)) return;
      std::unique_lock<std::mutex> access_lock(_access_mutex);
      if(!_close_id) return;
      _close_id.store(false,std::memory_order_release);
      access_lock.unlock();

      _produce_condition.notify_all();
      _consume_condition.notify_all();
    }
    bool full() const
    {
      std::lock_guard<std::mutex> access_lock(_access_mutex);
      return full_internal();
    }
    uint64_t size() const
    {
      std::lock_guard<std::mutex> access_lock(_access_mutex);
      return _shared_queue.size();
    }
    bool empty() const
    {
      std::lock_guard<std::mutex> access_lock(_access_mutex);
      return empty_internal();
    }
    /**
     * @brief #### 检测队列是否关闭
     * @return 关闭返回 `true`，未关闭返回 `false`
     */
    bool whether_close() const
    {
      return _close_id.load(std::memory_order_acquire);
    }
    double load_judgment() const
    {
      std::lock_guard<std::mutex> access_lock(_access_mutex);
      return static_cast<double>(_shared_queue.size()) / static_cast<double>(_current_capacity);
    }
  };
  /**
   * @brief #### 多生产多消费有锁双队列类`MPMC`
   * @tparam object_type 数据类型
   */
  template<typename object_type>
  class pro_con_queues
  {
    static constexpr uint64_t _default_capacity = 10;
  private: 
    uint64_t _current_capacity;  //当前容量
    std::thread _supporting_thread;  //后台辅助线程

    std::atomic<bool> _close_id;    //关闭标志
    std::atomic<bool> _switch_id;   //交换标志

    std::mutex _produce_mutex;  //生产者互斥锁
    std::mutex _consume_mutex;  //消费者互斥锁

    std::condition_variable _produce_condition;  //生产者条件变量
    std::condition_variable _consume_condition;  //消费者条件变量

    std::atomic<std::queue<object_type>*> _produce;  //生产者队列
    std::atomic<std::queue<object_type>*> _consume;  //消费者队列

    alignas(CACHE_ALIGNMENT) std::queue<object_type> _produce_pipe;  //原生生产者队列
    alignas(CACHE_ALIGNMENT) std::queue<object_type> _consume_pipe;  //原生消费者队列
    /**
     * @brief #### 检测队列是否为空
     * @note - 队列空时，交换队列
     */
    void swap_queue()
    {
      if(_consume.load(std::memory_order_acquire)->empty())
      {
        auto tmp_produce = _produce.load(std::memory_order_relaxed);

        _produce.store(_consume.load(std::memory_order_relaxed),std::memory_order_release);
        _consume.store(tmp_produce,std::memory_order_release);
      }
    }
    /**
     * @brief #### 后台辅助线程
     * @remark - 检测队列情况，交换队列，通知生产者或消费者
     */
    void supporting_thread_func()
    {
      //循环检测队列情况
      while(!_close_id.load(std::memory_order_acquire))
      {
        std::unique_lock<std::mutex> proudce_lock(_produce_mutex);
        auto conditions_exchange = [this]()
        {
          return _switch_id.load(std::memory_order_acquire) || _close_id.load(std::memory_order_acquire);
        };
        _produce_condition.wait(proudce_lock,conditions_exchange);
        if(_close_id.load(std::memory_order_acquire)) return;
        {
          std::lock_guard<std::mutex> consume_lock(_consume_mutex);
          swap_queue();
        }
        _switch_id.store(false,std::memory_order_release);

        _produce_condition.notify_all();
        _consume_condition.notify_one();
      }
    }
    /**
     * @brief #### 刷新队列
     * @remark - 刷新队列，将生产者队列中的数据全部转移到消费者队列中
     */
    void shutdown()
    {
      {
        std::lock_guard<std::mutex> proudce_lock(_produce_mutex);
        std::lock_guard<std::mutex> consume_lock(_consume_mutex);

        _close_id.store(true,std::memory_order_release);
      }

      _produce_condition.notify_all();
      _consume_condition.notify_all();
      
      if(_supporting_thread.joinable())
      {
        _supporting_thread.join();
      }
    }

  public:
    pro_con_queues(uint64_t capacity = _default_capacity)
    :_current_capacity(capacity),_close_id(false),_switch_id(false),_produce(&_produce_pipe),_consume(&_consume_pipe)
    {
      auto transmission = [this](){this->supporting_thread_func();};
      _supporting_thread = std::thread(transmission);
    }
    pro_con_queues(const pro_con_queues& other) = delete;
    pro_con_queues& operator=(const pro_con_queues& other) = delete;
    pro_con_queues(pro_con_queues&& other) = delete;
    pro_con_queues& operator=(pro_con_queues&& other) = delete;
    /**
     * @brief #### 向队列中添加数据
     * @param produce_data 生产数据
     * @return true 添加成功，false 添加失败
     */
    template<typename push_type>
    bool push(push_type&& produce_data)
    {
      if(_close_id.load(std::memory_order_acquire)) return false;
      while(true)
      {
        { //限制锁粒度，减少锁竞争
          std::lock_guard<std::mutex> proudce_lock(_produce_mutex);
          if(_produce.load(std::memory_order_acquire)->size() < _current_capacity)
          {
            _produce.load(std::memory_order_acquire)->push(std::forward<push_type>(produce_data));
            return true;
          }
        }
        flush();
        if(_close_id.load(std::memory_order_acquire)) return false;
      }
    }
    /**
     * @brief #### 从队列中取出数据
     * @param consume_data 消费数据
     * @return true 取出成功，false 取出失败
     */
    bool pop(object_type& consume_data)
    {
      std::unique_lock<std::mutex> consume_lock(_consume_mutex);
      while (true)
      {
        auto queue_ptr = _consume.load(std::memory_order_acquire);
        if (!queue_ptr->empty())
        {
          consume_data = std::move(queue_ptr->front());
          queue_ptr->pop();
          return true;
        }
        if (_close_id.load(std::memory_order_acquire)) return false;
        _consume_condition.wait(consume_lock);
      }
    }
    /**
     * @brief #### 获取生产者队列的大小
     * @return uint64_t 生产者队列的大小
     */
    uint64_t produce_size_unsafe()
    {
      std::lock_guard<std::mutex> proudce_lock(_produce_mutex);
      return _produce.load(std::memory_order_relaxed)->size();
    }
    /**
     * @brief #### 获取消费者队列的大小
     * @return uint64_t 消费者队列的大小
     */
    uint64_t consume_size_unsafe()
    {
      std::lock_guard<std::mutex> consume_lock(_consume_mutex);
      return _consume.load(std::memory_order_relaxed)->size();
    }
    /**
     * @brief #### 关闭队列
     * @remark - 关闭队列，通知生产者和消费者
     */
    void close()
    {
      _close_id.store(true,std::memory_order_release);

      _produce_condition.notify_all();
      _consume_condition.notify_all();
    }
    /**
     * @brief #### 刷新队列
     * @remark - 刷新队列，将生产者队列中的数据全部转移到消费者队列中
     */
    void flush()
    {
      bool swap_flag = false;
      if(_switch_id.compare_exchange_strong(swap_flag,true))
      { //比较两个布尔值是否相等,相等则切换为true，函数返回值代表是否已经切换，切换为真，反之为假
        _produce_condition.notify_one();
      }
      std::unique_lock<std::mutex> proudce_lock(_produce_mutex);
      auto waiting_consumption = [this]()
      {
        return !_switch_id.load(std::memory_order_acquire) || _close_id.load(std::memory_order_acquire);
      };
      _produce_condition.wait(proudce_lock,waiting_consumption);
    }
    ~pro_con_queues()
    {
      flush();
      shutdown();
    }
  };
  /**
   * @brief #### 多生产多消费有锁信号量队列
   * @warning 由于标准库限制队列容量只能写死
   * @tparam object_type  数据类型
   */
  template<typename object_type>
  class pro_con_semaphore_queue
  {
    static constexpr uint64_t _largest_semaphore = 10ULL;
  private:
    std::vector<object_type> _semaphore_queue; // 信号量队列

    std::counting_semaphore<_largest_semaphore> _produce_semaphore; // 生产者信号量
    std::counting_semaphore<_largest_semaphore> _consume_semaphore; // 消费者信号量

    std::mutex _produce_mutex; // 生产者锁
    std::mutex _consume_mutex; // 消费者锁

    uint64_t _produce_location; // 生产者位置
    uint64_t _consume_location; // 消费者位置

  public:
    pro_con_semaphore_queue()
    :_semaphore_queue(_largest_semaphore),_produce_semaphore(0),_consume_semaphore(_largest_semaphore),
    _produce_location(0),_consume_location(0){}
    void push(const pro_con_semaphore_queue& produce_data)
    {
      _consume_semaphore.acquire();
      std::unique_lock<std::mutex> proudce_lock(_produce_mutex);
      _semaphore_queue[_produce_location++] = produce_data;
      _produce_location = _produce_location % _largest_semaphore;
      proudce_lock.unlock();
      _produce_semaphore.release();
    }
    void pop(object_type& consume_data)
    {
      _produce_semaphore.acquire();
      std::unique_lock<std::mutex> consume_lock(_consume_mutex);
      consume_data = std::move(_semaphore_queue[_consume_location++]);
      _consume_location = _consume_location %  _largest_semaphore;
      consume_lock.unlock();
      _consume_semaphore.release();
    }
  };
}
