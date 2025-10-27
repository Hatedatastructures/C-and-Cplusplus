#include "agen.hpp"

int main()
{
  boost::asio::io_context io_context;
  auto tp_unique = pool::make_lightweight_pool(20);
  std::shared_ptr<pool::thread_pool> thread_pool(std::move(tp_unique));
  auto agent = std::make_shared<agent_service>(io_context, thread_pool);
  agent->bind_port(6779);
  agent->increase_endpoint("www.baidu.com","",80,false);
  agent->CA_path("G:\\git\\Git\\usr\\ssl\\certs\\ca-bundle.crt");
  agent->set_execution_stream(thread_pool);

  // 将原始字节解析为 HTTP 请求，转发到上游，并把响应回写到会话
  auto reception_processing = [agent](agent_service::session_ptr session, std::string_view data)
  {
    protocol::http::request<> req;
    if(!req.from_string(data))
    {
      // 解析失败可能是因为数据未完整，到达更多字节后再试；这里直接返回继续读
      return;
    }
    auto resp = agent->transponder_ptr()->forward_async(std::move(req));
    auto ec = session->send_response(resp.get());
    if(ec)
      session->close();
  };
  agent->set_reception_processing(reception_processing);
  // 启动服务器并运行 IO 事件循环
  agent->start();
  io_context.run();
  return 0;
}