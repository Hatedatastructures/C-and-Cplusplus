

# 协议框架类文档

## 1. auxiliary.hpp - 基础辅助类

### 1.1 枚举类型

#### protocol_type
```cpp
enum class protocol_type : std::uint8_t
{
  JSON_RPC = 0,      // JSON-RPC协议
  WEBSOCKET = 1,     // WebSocket协议
  CUSTOM_TCP = 2,    // 自定义TCP协议
  BINARY_STREAM = 3, // 二进制流协议
  USER_DEFINED = 4   // 用户自定义协议
};
```
**功能**: 定义支持的基于TCP的网络协议类型
**用途**: 用于标识协议头部的协议类型，所有协议均基于TCP传输层

#### checksum_type
```cpp
enum class checksum_type : std::uint8_t
{
  CRC32 = 0,
  MD5 = 1,
  SHA256 = 2,
  CUSTOM = 3
};
```
**功能**: 定义支持的校验和算法类型
**用途**: 用于数据完整性验证

### 1.2 基础类

#### protocol_header
```cpp
class protocol_header
```
**功能**: 协议头部基类，提供通用的协议头部功能
**主要成员变量**:
- `_protocol_version`: 协议版本号
- `_checksum_type`: 校验和类型
- `_content_length`: 内容长度
- `_headers`: 头部字段映射
- `_cached_string`: 缓存的字符串表示
- `_string_cache_valid`: 字符串缓存有效性标志

**主要方法**:
- `get_version()`/`set_version()`: 获取/设置协议版本
- `get_checksum_value()`/`set_checksum_value()`: 获取/设置校验值
- `get_content_length()`/`set_content_length()`: 获取/设置内容长度
- `set_header()`: 设置头部字段
- `remove_header()`: 移除头部字段
- `get_header()`: 获取头部字段值
- `clear_headers()`: 清空所有头部字段
- `get_headers()`: 获取所有头部字段
- `to_string()`: 序列化为字符串
- `from_string()`: 从字符串反序列化
- `to_json()`: 转换为JSON对象
- `from_json()`: 从JSON对象反序列化
- `calculate_and_set_checksum()`: 计算并设置校验值
- `verify_integrity()`: 验证数据完整性

---

## 2. protocol.hpp - 核心协议类

### 2.1 概念约束

#### header_constraint
```cpp
template <typename T>
concept header_constraint = std::is_base_of_v<protocol_header, T>;
```
**功能**: 定义头部类型约束，确保头部类型继承自protocol_header

### 2.2 请求头部类

#### request_header
```cpp
class request_header : public protocol_header
```
**功能**: TCP请求头部类，继承自protocol_header
**主要成员变量**:
- `_method`: 请求方法
- `_target`: 请求目标
- `_user_agent`: 用户代理
- `_timestamp`: 时间戳

**主要方法**:
- `get_method()`/`set_method()`: 获取/设置请求方法
- `get_target()`/`set_target()`: 获取/设置请求目标
- `get_user_agent()`/`set_user_agent()`: 获取/设置用户代理
- `get_timestamp()`/`set_timestamp()`: 获取/设置时间戳
- `to_string()`: 序列化为字符串
- `from_string()`: 从字符串反序列化
- `to_json()`: 序列化为`JSON`
- `from_json()`: 从`JSON`反序列化

### 2.3 响应头部类

#### response_header
```cpp
class response_header : public protocol_header
```
**功能**: TCP响应头部类，继承自protocol_header
**主要成员变量**:
- `_server`: 服务器信息
- `_status_code`: 状态码
- `_status_message`: 状态消息
- `_timestamp`: 时间戳

**主要方法**:
- `get_server()`/`set_server()`: 获取/设置服务器信息
- `get_status_code()`/`set_status_code()`: 获取/设置状态码
- `get_status_message()`/`set_status_message()`: 获取/设置状态消息
- `get_timestamp()`/`set_timestamp()`: 获取/设置时间戳
- `to_string()`: 序列化为字符串
- `from_string()`: 从字符串反序列化
- `to_json()`: 序列化为`JSON`
- `from_json()`: 从`JSON`反序列化

### 2.4 请求类模板

#### request<header_t>
```cpp
template <header_constraint header_t = request_header>
class request
```
**功能**: 通用请求类模板，支持自定义头部类型
**主要成员变量**:
- `_header`: 请求头部对象
- `_message`: 请求体内容
- `_cached_full`: 缓存的完整请求字符串
- `_full_cache_valid`: 完整缓存是否有效

**主要方法**:
- `header()`: 获取请求头部对象
- `body()`: 获取请求体内容
- `set_message()`: 设置请求体内容
- `to_string()`: 序列化为字符串
- `from_string()`: 从字符串反序列化
- `to_json()`: 转换为JSON对象
- `from_json()`: 从JSON对象反序列化
- `verify_integrity()`: 验证数据完整性
- `empty()`: 检查请求体是否为空

### 2.5 响应类模板

#### response<header_t>
```cpp
template <header_constraint header_t = response_header>
class response
```
**功能**: 通用响应类模板，支持自定义头部类型
**主要成员变量**:
- `_header`: 响应头部对象
- `_message`: 响应体内容
- `_cached_full`: 缓存的完整响应字符串
- `_full_cache_valid`: 完整缓存是否有效

**主要方法**:
- `header()`: 获取响应头部对象
- `body()`: 获取响应体内容
- `set_message()`: 设置响应体内容
- `get_status_code()`: 获取状态码（仅适用于response_header）
- `set_status_code()`: 设置状态码（仅适用于response_header）
- `get_status_message()`: 获取状态消息（仅适用于response_header）
- `set_status_message()`: 设置状态消息（仅适用于response_header）
- `to_string()`: 序列化为字符串
- `from_string()`: 从字符串反序列化
- `to_json()`: 转换为JSON对象
- `from_json()`: 从JSON对象反序列化
- `verify_integrity()`: 验证数据完整性
- `empty()`: 检查响应体是否为空

---

## 3. json.hpp - JSON处理类

### 3.1 JSON包装类

#### json
```cpp
class json
```
**功能**: `boost::json`的C++包装类，提供简化的JSON操作接口
**主要成员变量**:
- `_value`: `boost::json::value`对象
- `_cached_string`: 缓存的`JSON`字符串
- `_string_cache_valid`: 字符串缓存有效性标志

**主要方法**:
- `from_string()`: 从字符串解析`JSON`
- `to_string()`: 转换为字符串（带缓存优化）
- `value()`: 获取原始`boost::json::value`引用
- `get<T>()`: 类型安全的值获取（支持任意类型）
- `set<T>()`: 类型安全的值设置（支持任意类型）
- `contains()`: 检查是否包含指定键
- `remove()`: 移除指定键
- `clear()`: 清空所有内容
- `size()`: 获取对象大小
- `empty()`: 检查是否为空

**特性**:
- 支持拷贝和移动语义，优化缓存处理
- 提供异常安全保证
- 支持任意类型的值获取和设置
- 内置字符串缓存机制，提高性能

---

## 4. conversion.hpp - 协议转换类

### 4.1 协议转换器

#### protocol_converter
```cpp
class protocol_converter
```
**功能**: 提供协议对象与JSON之间的转换功能
**主要静态方法**:

##### 请求转换
- `request_to_json<header_t>()`: 将请求对象转换为JSON
- `json_to_request<header_t>()`: 将JSON转换为请求对象（返回`std::optional`）

##### 响应转换
- `response_to_json<header_t>()`: 将响应对象转换为JSON
- `json_to_response<header_t>()`: 将JSON转换为响应对象（返回`std::optional`）

**特性**:
- 支持模板化的头部类型
- 使用`std::optional`提供安全的转换失败处理
- 静态方法设计，无需实例化

---

## 5. 框架特性

- **类型安全**: 使用C++20概念约束确保类型安全
- **模板化设计**: 支持自定义头部类型的请求/响应类
- **性能优化**: 内置缓存机制，减少重复序列化开销
- **标准兼容**: 使用现代C++特性

### 主要功能
- 协议头部管理和序列化
- 请求/响应对象的完整生命周期管理
- `JSON`与协议对象的双向转换
- 数据完整性验证
- 灵活的头部字段管理