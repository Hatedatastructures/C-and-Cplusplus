#include "agen.hpp"

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

  // 预取上游页面（例如百度首页），用于快速首响应
  std::shared_ptr<protocol::http::response<>> cached_response;
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
    }
    catch (const std::exception &e)
    {
      std::cerr << "prefetch failed: " << e.what() << std::endl;
    }
  }

  // 将原始字节解析为 HTTP 请求，转发到上游，并把响应回写到会话
  auto reception_processing = [agent, cached_response](agent_service::session_ptr session, std::string_view data)
  {
    protocol::http::request<> req;
    if(!req.from_string(data))
    {  
      // 解析失败可能是因为数据未完整，到达更多字节后再试；这里直接返回继续读
      return;
    }

    // 若 Host 指向本地或为空，改写为上游域名（例如百度）
    std::string host_header;
    try { host_header = req.at(protocol::http::field::host); } catch(...) {}
    if (host_header.empty() || host_header == "localhost" || host_header == "127.0.0.1")
      req.set(protocol::http::field::host, "www.baidu.com");

    // 如果是首页且已有预取内容，优先快速返回
    if (cached_response && req.method() == boost::beast::http::verb::get && req.target() == "/")
    {
      auto ec = session->send_response(*cached_response);
      if (ec)
        session->close();
      return;
    }

    auto resp = agent->transponder_ptr()->forward_async(std::move(req));
    try
    {
      auto ec = session->send_response(resp.get());
      if(ec)
        session->close();
    }
    catch (const std::exception &e)
    {
      protocol::http::response<> fallback{boost::beast::http::status::bad_gateway, 11};
      fallback.set(protocol::http::field::content_type, "text/plain; charset=utf-8");
      fallback.body() = std::string("upstream error: ") + e.what();
      fallback.prepare_payload();
      auto ec = session->send_response(fallback);
      if (ec)
        session->close();
    }
  };
  agent->set_reception_processing(reception_processing);
  // 启动服务器并运行 IO 事件循环
  if (!agent->start())
  {
    std::cerr << "agent start failed (acceptor not open or worker start failure)" << std::endl;
    return 1;
  }
  io_context.run();
  return 0;
}
