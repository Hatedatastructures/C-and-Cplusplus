#include "../model/network/network.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <format>

#include <boost/asio.hpp>

using namespace wan::network;
const std::string html_path = "index.html";
/**
 * @brief 简单的http静态网页服务器
 */
class server
{
	boost::asio::io_context& io_context; //io上下文
	boost::asio::ip::tcp::endpoint endpoint; //tcp端点
	boost::asio::ip::tcp::acceptor acceptor; //tcp接受器
	session::session_management<http::request<>, http::response<>> session_management; //会话连接管理
private:
	std::string print()
	{
		return std::format("[{:%Y-%m-%d %H:%M:%S}]",std::chrono::system_clock::now());
	}

	std::string html_data()
	{
		std::ifstream file(html_path);
		std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		return data;
	}
	/**
	 * @brief 接受新的tcp连接
	 */
	void socket_accept()
	{
		auto handle_function = [&](boost::system::error_code ec,boost::asio::ip::tcp::socket socket)
		{
			if (!ec)
			{
				using session_ptr = std::shared_ptr<session::session<http::request<>, http::response<>>>;
				auto func = [&](session_ptr ptr, std::string_view data)
				{
					auto call = [&,sess_ptr = ptr](boost::system::error_code ec)
					{
						if(!ec)
						  std::cout << std::format("{} session id :{} send response success",print(),
							sess_ptr->get_session_id()) << std::endl;
						else
						  std::cout << std::format("{} session id :{} send response error: {}",print(),
							sess_ptr->get_session_id(),ec.message()) << std::endl;
					};
					// 构建请求
          auto request = http::request<>{};
          request.from_string(data);

					auto response = http::response<>{};
					response.result(boost::beast::http::status::ok);
					response.base().set(http::field::content_type, "text/html");
					// response.base().set(boost::beast::http::field::connection, "close"); 关闭长连接
					response.body() = html_data();
					response.base().content_length(response.body().size());
					response.prepare_payload();
					ptr->async_send_response(response,call);
				};
				std::cout << std::format("{} connection successful,from ip {}, port: {}",print(),
				socket.remote_endpoint().address().to_string(),socket.remote_endpoint().port()) << std::endl;
				auto value = session_management.create_server_session(std::move(socket));
				std::cout << std::format("{} create session success , id: {} ",print(),value.first) << std::endl;
			
				value.second->set_reception_processing(func);
				value.second->start();
			}
			else
			  std::cout << std::format("{} accept error: {} \n",print(),ec.message()) << std::endl;
			socket_accept();
		};
		acceptor.async_accept(handle_function);
	}
public:
	server(boost::asio::io_context &io_context,std::uint16_t port)
		: io_context(io_context),endpoint(boost::asio::ip::tcp::v4(), port),
		acceptor(io_context),session_management(io_context) 
		{
			std::cout << std::format("{} server initialization succeeded , port: {}",print(),port) << std::endl;
		}

	void start()
	{
		acceptor.open(endpoint.protocol());
		acceptor.bind(endpoint);
		acceptor.listen(boost::asio::socket_base::max_listen_connections);
		session_management.start();
		socket_accept();
	}
	~server()
	{
		acceptor.close();
	}
}; // end class server
