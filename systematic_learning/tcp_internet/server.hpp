#include "boost/asio.hpp"
#include "Thread_pool.hpp"
#include <iostream>
using namespace boost::asio::ip;
class server
{
  con::thread_pool _thread; // 动态线程池
  tcp::acceptor _acceptor;  //tcp接收器
  void response_information(tcp::socket& socket,const std::string temp_data)
  {
    std::string response_data = "服务器收到数据 : " + temp_data;
    auto response_func = [this](boost::system::error_code s,uint64_t len)
    {
      if(s)
      {
        std::cout << "回复客户端失败" << s.message() << " 数据长度 : " << len << std::endl;
      }
    }; //回传数据
    socket.async_write_some(boost::asio::buffer(response_data),response_func);
  }
  void information_stream(tcp::socket socket)
  { //接受数据流
    std::shared_ptr<tcp::socket> client_socket = std::make_shared<tcp::socket>(std::move(socket));
    auto _data = std::make_shared<std::string>();
    _data->resize(1024);
    auto process_stream = [this,_data,client_socket](boost::system::error_code s,uint64_t len)
    {
      if(!s)
      {
        if(len > 0)
        {
          std::cout << "收到来自 " << client_socket->remote_endpoint() << " 的数据长度为 : " << len 
          << " 数据 : " << _data->substr(0,len) << std::endl;
          //回复客户端数据
          response_information(*client_socket,_data->substr(0,len)); //回传数据
          information_stream(std::move(*client_socket)); //继续接受数据
        }
        // std::cout << "收到来自 " << client_socket->remote_endpoint() << " 的数据长度为 : " << len 
        // << " 数据 : " << _data->substr(0,len) << std::endl;
        // //回复客户端数据
        // response_information(*client_socket,_data->substr(0,len)); //回传数据
        // information_stream(std::move(*client_socket)); //继续接受数据
      }
    }; //异步执行
    client_socket->async_read_some(boost::asio::buffer(*_data),process_stream);
  }
  public:
  server(boost::asio::io_context& context,uint16_t port)
  :_thread(10,2ULL),_acceptor(context,tcp::endpoint(tcp::v4(),port))
  {
    std::cout << "当前tcp服务器端口号是 : " << port << std::endl;
  }
  void accptor()
  {
    auto func = [this](boost::system::error_code s,tcp::socket socket)
    {
      process_information(std::move(socket),s); 
    }; //异步执行
    _acceptor.async_accept(func);
  }
  void process_information(tcp::socket&& socket,boost::system::error_code s)
  {
    if(!s)
    {
      auto socket_ptr = std::make_shared<tcp::socket>(std::move(socket));
      auto task = [this,socket_ptr]()
      {
        information_stream(std::move(*socket_ptr));
      };
      _thread.submit(task); //调用线程池来执行任务
    }
    else
    {
      std::cout << "客户端连接失败" << s.message() << std::endl;
    }
    accptor();
  }
};