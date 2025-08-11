#include "client.hpp"
int main()
{
  try
  {
    boost::asio::io_context io_context;
    std::unique_ptr<client> send(new client(io_context, "127.0.0.1", 6779));
    send->start();
    io_context.run();
  }
  catch(std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}