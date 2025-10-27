#pragma once

#include "./crypt/encryption.hpp" // 加密 哈希


#include "./agreement/http.hpp"  // http协议
#include "./agreement/json.hpp"  // json协议
#include "./agreement/auxiliary.hpp" // tcp协议头基类
#include "./agreement/protocol.hpp"  // tcp协议头和协议封装
#include "./agreement/conversion.hpp" // tcp协议转换


#include "./session/fundamental.hpp" // 会话封装
#include "./session/conversation.hpp" // 会话管理

#include "./business/forwarder.hpp" // 服务端http / https 代理类

namespace wan
{
  namespace agreement
  {
    using protocol::json;
    using protocol::request;
    using protocol::response;
    using protocol::request_header;
    using protocol::response_header;

    using protocol::auxiliary::checksum_type;
    using protocol::auxiliary::protocol_type;
    using protocol::auxiliary::protocol_header;

    using protocol::conversion::protocol_converter;
  } // end namespace agreement
  namespace http
  {
    using namespace protocol::http;
  } // end namespace http 
  namespace ciphertext
  {
    using namespace encryption; 
  } // end namespace ciphertext
  namespace session
  {
    using namespace conversation::fundamental;
    
    using conversation::connection_pool;
    using conversation::endpoint_config;

    using conversation::session_management;
    using conversation::session_management_config;
  } // end namespace session
  namespace business
  {
    using namespace represents;
  } // end namespace business
} // end namespace wan
