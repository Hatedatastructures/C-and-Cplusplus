# `template_container`文件与`custom_log`文件
## 一、源文件定位对比

| 模块名称                 | 主要职责             | 核心特性                                                                          |
| -------------------- | ---------------- | ----------------------------------------------------------------------------- |
| `template_container` | 提供通用数据结构与算法模板库   | 智能指针、容器（`vector`、`list`、`map`、`set` 等）、算法、仿函数、哈希、布隆过滤器等  |
| `custom_log`         | 提供可配置、异步、高性能日志系统 | 多级信息聚合、双缓冲异步写入、时间与前缀格式化、二级缓存推送、文件/控制台输出切换                                     |
## 二、文件架构对比

### 1. [`template_container`](template_containers/template_container.md)
* ### [**跳转详细文档**](template_containers/template_container.md)
* ### [**跳转到源代码**](custom_libraries/template_container.hpp)
* **命名空间划分**：

  * `custom_exception`、`smart_pointer`、`practicality`、`imitation_functions`、`algorithm`、各类容器命名空间、`base_class_container`、`bloom_filter_container`、以及简化命名空间 `con`、`ptr`、`exc`
* **主要模块**：

  * **智能指针**：`shared_ptr`、`weak_ptr`、`unique_ptr`、`smart_ptr`
  * **算法**：`swap`、`copy`、`find`、`hash_function`
  * **基础工具**：`pair` 与 `make_pair`
  * **容器**：`string`、动态数组 `vector`、双向链表 `list`、栈/队列适配器、树形、关联（`tree_map`/`tree_set`、`hash_map`/`hash_set`）、位图 `bit_set`、布隆过滤器
* **文档结构**：

  1. 函数签名与声明
  2. 作用描述
  3. 返回值说明
  4. 使用示例
  5. 内部原理剖析
  6. 复杂度分析
  7. 边界条件与错误处理
  8. 注意事项（线程安全、迭代器失效等）

### 2. [`custom_log`](template_containers/custom_logs.md)
* ### [**跳转详细文档**](template_containers/custom_logs.md)
* ### [**跳转到源代码**](custom_libraries/custom_logs.hpp)
* **命名空间划分**：

  * `information`（多级信息聚合）
  * `buffer_queues`（双缓冲、异步写入）
  * `configurator`（前缀占位、时间与信息格式化、文件/控制台配置器、函数栈）
  * 顶层 `foundation_log`（二级缓存、并发推送）与 `log` 接口类
  * 快捷 `rec` 命名空间
* **主要模块**：

  * **信息聚合**：自定义、调试、一般、警告、错误、严重错误六级信息输入与链式调用
  * **双缓冲队列**：生产/消费队列，自动切换与后台线程
  * **配置器**：文件/控制台输出适配，时间与前缀格式化
  * **缓存推送**：二级缓存汇总，统一 `push` 输出，支持开关控制
* **文档结构**：

  1. 宏定义（快捷调用）
  2. 类型别名与枚举
  3. 各模块功能说明
  4. 详细函数签名与注释
  5. 使用示例
  6. 注意事项（线程同步、缓冲调整）

## 三、使用示例对比

```cpp
// Template Container 示例：
#include "template_container.hpp"
using namespace con;

vector<int> v;
v.push_back(1);
v.push_back(2);
list<string> lst = {"a","b","c"};
map<int,string> m;
m.push({1,"one"});
```

```cpp
// Custom Log 示例：
#include "custom_log.hpp"
using namespace rec;

log<> logger("app.log");

// 普通写入
logger.write(default_custom_information_input_macros("启动完成"),default_timestamp_macros);
// 缓存 & 推送
logger.staging(default_custom_information_input_macros("阶段数据"),default_timestamp_macros);
logger.push();
```

> 通过上述对比，可快速定位所需模块并参考对应接口与文档风格，助力项目开发与维护。
