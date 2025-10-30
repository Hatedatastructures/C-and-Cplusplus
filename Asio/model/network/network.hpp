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
  /**
   * @brief 网络模块
   * @note 该模块提供网络协议、加密、会话管理、转发劫持等功能
   */
  namespace network
  {
    /**
     * @brief 协议模块
     * @note 提供`tcp`协议的定义、转换、校验等功能
     */
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
    /**
     * @brief http模块
     * @note 提供http协议的封装等功能
     */
    namespace http
    {
      using namespace protocol::http;
    } // end namespace http 
    /**
     * @brief 加密模块
     * @note 提供加密、解密、哈希等功能
     */
    namespace ciphertext
    {
      using namespace encryption; 
    } // end namespace ciphertext

    /**
     * @brief 会话模块
     */
    namespace session
    {
      using namespace conversation::fundamental;
      
      using conversation::connection_pool;
      using conversation::endpoint_config;

      using conversation::session_management;
      using conversation::session_management_config;
    } // end namespace session
    /**
     * @brief 代理模块
     * @note 提供业务逻辑的实现，如http代理等
     */
    namespace business
    {
      using namespace represents;
    } // end namespace business
  } // end namespace wan
}
