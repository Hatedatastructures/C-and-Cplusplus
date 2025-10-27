#include <coroutine>
#include <string>
#include <iostream>
#include <utility>

// coroutine demo
struct task
{
  struct promise_type
  {
    std::coroutine_handle<promise_type> _handle; // 构建一个句柄
    task get_return_object() 
    { 
      // 从当前promise构建一个句柄
      _handle = std::coroutine_handle<promise_type>::from_promise(*this);
      return task{_handle};
    }
    std::suspend_never initial_suspend() noexcept { return {}; } // 初始挂起，立即返回
    std::suspend_always final_suspend() noexcept { return {}; } // 最终挂起，立即返回
    void return_void() {}
    void unhandled_exception() {}
  };
  std::coroutine_handle<promise_type> _handle; 
  task(std::coroutine_handle<promise_type> handle) : _handle(handle)  {}
  ~task() {if(_handle) _handle.destroy();}
  bool done()  { return _handle.done(); }
  void resume() { if(_handle && !_handle.done()) _handle.resume(); }
  task(const task&) = delete;
  task& operator=(const task&) = delete;
  task(task&& other) : _handle(std::exchange(other._handle, {})) {}
  task& operator=(task&& other)
  {
    if(_handle) _handle.destroy(); //先销毁当前句柄
    _handle = std::exchange(other._handle, {}); // 重新获取其他句柄
    return *this;
  }
};
task func()
{
  std::cout << std::string("1") << std::endl;
  co_await std::suspend_always{}; // 挂起协程
  std::cout << std::string("2") << std::endl;
}

int main()
{
  task value = func(); // 获取协程句柄
  std::cout << std::string("现在手动终止协程") << std::endl;
  value.resume(); // 恢复协程
  value.resume(); // 再次恢复协程
  if(value.done())
  {
    std::cout << std::string("协程已完成") << std::boolalpha << value.done() << std::endl;
  }
  return 0;
}