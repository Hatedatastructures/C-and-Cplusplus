#include "agen.hpp"
#include <unordered_map>
#include <algorithm>
#include <format>
#include <fstream>
#include <string>

static const std::string html_path = {"C:\\Users\\C1373\\Desktop\\thread_pool.html"};

int main()
{
  boost::asio::io_context io_context;
  auto tp_unique = pool::make_lightweight_pool(20);
  std::shared_ptr<pool::thread_pool> thread_pool(std::move(tp_unique));
  auto agent = std::make_shared<agent_service>(io_context, thread_pool);
  if (!agent->bind_port(6779))
  {
    std::cerr << "bind_port(6779) failed; port in use or permission denied" << std::endl;
    return 1;
  }
  agent->increase_endpoint("www.baidu.com","",80,false);
  agent->CA_path("G:\\git\\Git\\usr\\ssl\\certs\\ca-bundle.crt");
  agent->set_execution_stream(thread_pool);

  // 预取上游页面（例如百度首页），使用异步任务避免阻塞主线程
  std::shared_ptr<protocol::http::response<>> cached_response;
  auto request_function = [agent, &cached_response]() mutable 
  {
    protocol::http::request<> preq;
    preq.method(boost::beast::http::verb::get);
    preq.version(11);
    preq.target("/");
    preq.set(protocol::http::field::host, "www.baidu.com");
    preq.set(protocol::http::field::user_agent, "agent-prefetch/1.0");
    preq.prepare_payload();
    try 
    {
      auto fut = agent->transponder_ptr()->forward_async(std::move(preq));
      auto res = fut.get();
      cached_response = std::make_shared<protocol::http::response<>>(std::move(res));
    } catch (const std::exception &e) 
    {
      std::cerr << "prefetch failed: " << e.what() << std::endl;
    }
  };
  agent->execution_stream()->submit(request_function); // 提交预取任务到线程池

  auto reception_processing = [agent, &cached_response](agent_service::session_ptr session, std::string_view data)
  {
    // 先测试数据的响应
    // if(!data.empty()) 
    // {
    //   if(!html_path.empty())
    //   {
    //     std::ifstream file(html_path);
    //     if(file.is_open())
    //     {
    //       std::string html_string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    //       file.close();
    //       http::response<boost::beast::http::string_body> res;
    //       res.version(11);
    //       res.base().result(boost::beast::http::status::ok);
    //       res.set(http::field::content_type, "text/html");
    //       res.body() = html_string;
    //       res.prepare_payload();
    //       session->async_send_response(std::move(res));
    //     }
    //     else
    //       std::cerr << std::format("open html file {} failed" ,html_path) << std::endl;
    //   }
    //   else
    //     std::cout << std::format("[ session_id = {} ]" ,session->get_session_id());
    // }

    // 转发响应
    // auto log_function = [ str_data = std::move(data) ](boost::system::error_code ec)
    // {
    //   if(!ec)
    //     std::cout << std::format("{}",str_data) << std::endl;
    //   else
    //     std::cout << std::format("[ send response failed: {} ]",ec.message()) << std::endl;
    // };
    // session->async_send_response(*cached_response,log_function);

    http::request<boost::beast::http::string_body> req;
    req.from_string(data);
    req.base().set(http::field::host, "www.baidu.com");
    auto req_value = agent->transponder_ptr()->forward_async((std::move(req)));
    if(!req_value.valid())
    {
      std::cerr << std::format("forward_async failed") << std::endl;
      return;
    }
    session->async_send_response(req_value.get());
    // std::cout << std::format("{} \n {}", std::string("转发成功"),req_value.get().to_string()) << std::endl;
    std::cout << std::format("{}", std::string("转发成功")) << std::endl;
    // std::cout << std::format("{} \n {}", std::string("转发成功"),req.to_string()) << std::endl;
  };
  agent->set_reception_processing(reception_processing);
  // 启动服务器并运行 IO 事件循环
  if (!agent->start())
  {
    std::cerr << std::format("agent start failed (acceptor not open or worker start failure)") << std::endl;
    return 1;
  }
  io_context.run();
  return 0;
}
