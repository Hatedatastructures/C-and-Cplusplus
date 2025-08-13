#include <iostream>
#include "server.hpp"
int main()
{
  try
  {
    boost::asio::io_context io_context;
    std::unique_ptr<server> s(new server(io_context,6779));
    s->accptor();
    io_context.run();
  }
  catch(const std::exception& e)
  {
    std::cerr << "服务器异常: "<< e.what() << '\n';
  }
  return 0;
}