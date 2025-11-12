#include "server.hpp"

#include <iostream>
#include <thread>

int main()
{
  boost::asio::io_context io_context;
  server server(io_context,8080);
  server.set_web_root("./webroot");
  server.start();
  std::jthread thread([&io_context]()
  {
    io_context.run();
    std::cout << "io_context.run() finished" << std::endl;
  });
  return 0;
}