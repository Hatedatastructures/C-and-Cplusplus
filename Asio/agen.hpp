#pragma once
#include "model/network/network.hpp"
#include "model/sched/thread_pool.hpp"

#include <memory>
#include <string>
#include <iostream>

using namespace wan;

class agent_service : public std::enable_shared_from_this<agent_service>
{
  // std::string web_root;
public:
  using session_ptr = std::shared_ptr<session::session<http::request<>,http::response<>>>;
private:
  std::function<void(session_ptr, std::string_view)> reception_processing; // 接收处理函数
private:
  std::shared_ptr<pool::thread_pool> thread_pool; // 异步执行流
  std::shared_ptr<business::transponder<>> transponder; // 转发器
  std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor; // 监听器
  std::shared_ptr<session::session_management<http::request<>,http::response<>>> session_management; // 会话管理器
public: 
  agent_service(boost::asio::io_context &io_context,std::shared_ptr<pool::thread_pool> stream_pool)
   :thread_pool(stream_pool), transponder(std::make_shared<business::transponder<>>(io_context)),
   acceptor(std::make_shared<boost::asio::ip::tcp::acceptor>(io_context, 
    boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 0))),
    session_management(std::make_shared<session::session_management<http::request<>,http::response<>>>(io_context)) 
  {}
  
  agent_service(boost::asio::io_context &io_context, std::uint16_t port )
   :transponder(std::make_shared<business::transponder<>>(io_context)),
   acceptor(std::make_shared<boost::asio::ip::tcp::acceptor>(io_context, 
    boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))),
   session_management(std::make_shared<session::session_management<http::request<>,http::response<>>>(io_context)) 
   {acceptor->listen();}

  /**
   * @brief 增加上游代理端点
   */
  void increase_endpoint(std::string domain, std::string host, std::uint16_t port, bool https = false)
  {
    transponder->add_upstream(domain, host, port, https);
  }

  /**
   * @brief 绑定监听端口并进入监听状态
   * @param port 监听端口
   */
  void bind_port(std::uint16_t port)
  {
    acceptor->open(boost::asio::ip::tcp::v4());
    acceptor->bind(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
    acceptor->listen(); // 进入监听状态
  }

  auto transponder_ptr()
  ->std::shared_ptr<business::transponder<>>
  {
    return transponder;
  }
  
  /**
   * @brief 增加异步执行流
   */
  void set_execution_stream(std::shared_ptr<wan::pool::thread_pool> stream)
  {
    thread_pool = stream;
    transponder->set_async_executor(thread_pool); // 所有异步转发逻辑经过线程池来调度
  }

  /**
   * @brief 访问异步执行流
   * @return std::shared_ptr<pool::thread_pool> 异步执行流
   */
  std::shared_ptr<pool::thread_pool> execution_stream()
  {
    return thread_pool;
  }

  /**
   * @brief 设置SSL CA文件路径
   * @param path CA文件路径
   */
  void CA_path(std::string path)
  {
    transponder->set_ssl_ca_file(path);
    transponder->set_ssl_insecure_skip_verify(true);
  }

  void set_reception_processing(std::function<void(session_ptr, std::string_view)> processing)
  {
    reception_processing = processing;
  }

  /**
   * @brief 转发请求
   */
  bool start()
  {
    if(thread_pool && thread_pool->start() && session_management && session_management->start())
    {
      enter_monitoring();
      return true;
    }
    return false;
  }

  void enter_monitoring()
  {
    auto monitoring_function = [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
    {
      if(!ec)
      {
        boost::system::error_code re_ec;
        auto ep = socket.remote_endpoint(re_ec); // 获取客户端 ip 地址 信息
        if(!re_ec)
          std::cout << std::format("[{:%Y-%m-%d %H:%M:%S}] [conversationss : {}] Accepted connection from: {}:{}\n",
          std::chrono::system_clock::now(),session_management->get_session_count(), ep.address().to_string(), ep.port());
        else
          std::cout << std::format("[{:%Y-%m-%d %H:%M:%S}] [conversationss : {}] Accepted connection\n",
            std::chrono::system_clock::now(), session_management->get_session_count());
        // 捕获到共享指针，保证任务可复制以适配 std::function 存储
        auto self = this->shared_from_this();
        auto sock_ptr = std::make_shared<boost::asio::ip::tcp::socket>(std::move(socket));
        auto task = [self, sock_ptr]() mutable 
        {
          self->forward_processing(std::move(*sock_ptr));
        };
        thread_pool->submit(std::move(task)); // 直接提交可调用对象，无额外形参
      }
      else
        std::cerr << "accept error: " << ec.message() << std::endl; // 监听错误
      enter_monitoring();
    };
    acceptor->async_accept(std::move(monitoring_function));
  }
  void forward_processing(boost::asio::ip::tcp::socket&& socket)
  {
    auto pair = session_management->create_server_session(std::move(socket));
    pair.second->set_reception_processing(reception_processing);
    pair.second->start();
  }
};