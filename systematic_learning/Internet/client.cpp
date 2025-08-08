#include "client.hpp"
int main()
{
  try
  {
    boost::asio::io_context _service;
    client test(_service,"127.0.0.1", 6779);
    _service.run();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}