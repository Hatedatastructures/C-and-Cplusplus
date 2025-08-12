#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <string>
using namespace boost::asio::ip;
class client
{
  std::shared_ptr<udp::socket> _socket;
  udp::endpoint _server_endpoint;
  std::atomic<uint64_t> _count{0};
  std::string send_information;
public:
  client(boost::asio::io_context &io_context, const std::string &ip, uint16_t port)
  :_server_endpoint(address::from_string(ip), port)
  {
    _socket = std::make_shared<udp::socket>(io_context,udp::endpoint(udp::v4(),0));
    send_information.resize(1024);
    std::cout << "远程地址: " << ip << std::endl;
  }
  void start()
  {
    //1.启动接受处理
    auto callock = [this](boost::system::error_code s,uint64_t byte_size)
    {
      if(!s)
      {
        _count = _count + byte_size;
        std::cout << send_information << std::endl;
      }
    }; //接收信息
    _socket->async_receive_from(boost::asio::buffer(send_information), _server_endpoint,callock);
  }
  void send()
  {
    auto run_thread = [this]()
    {
      std::cout << "[@" << _server_endpoint.address().to_string() << " # " << _server_endpoint.port() << "] ";
      while(std::getline(std::cin,send_information))
      {
        if(send_information == "exit")
        {
          break;
        } //发送
        _socket->send_to(boost::asio::buffer(send_information),_server_endpoint,0);
        std::cout << "[@" << _server_endpoint.address().to_string() << " # " << _server_endpoint.port() << "] ";
      }
    };
    std::thread real_time(run_thread);
    real_time.join();
  }
  ~client()
  {
    std::cout << "共计接收了: " << _count << "个字节" << std::endl;
  }
};