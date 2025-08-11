#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <string>
using namespace boost::asio::ip;
class client
{
  std::shared_ptr<udp::socket> _socket;
  udp::endpoint _server_endpoint;
  std::thread _thread;
  std::atomic<uint64_t> _count{0};
public:
  client(boost::asio::io_context& context,const std::string& server_ip,int server_port)
  :_socket(std::make_shared<udp::socket>(context,udp::endpoint(udp::v4(),0)))
  {
    udp::resolver resolver(context);
    _server_endpoint = *resolver.resolve(udp::v4(),server_ip,std::to_string(server_port)).begin();
    _thread  = std::thread([this](){thread_cin();});
  }
  void send(const std::string& message)
  {
    (void)_socket->async_send_to(boost::asio::buffer(message),_server_endpoint);
  }
  void start()
  {
    std::string send_information;
    auto call_back = [this,&send_information](boost::system::error_code error, uint64_t bytes_size)
    {
      if(!error)
      {
        std::cout << send_information << std::endl;
        _count = _count.load() + bytes_size;
        start();
      }
    };
    _socket->async_receive_from(boost::asio::buffer(send_information,1024),_server_endpoint,call_back);
  }
  void thread_cin()
  {
    std::string message;
    auto local_ip = _socket->local_endpoint();
    std::cout << "[" << local_ip.address().to_string() << " "  << local_ip.port() << "]";
    while(std::getline(std::cin,message))
    {
      send(message);
      std::cout << "[" << local_ip.address().to_string() << " "  << local_ip.port() << "]";
    }
  }
  ~client()
  {
    _thread.join();
  }
};