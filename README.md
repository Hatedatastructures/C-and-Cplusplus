### 日常代码学习库

- 跨语言代码练习与示例集合，`C/C++` 为主，包含网络编程、并发调度、数据结构模拟、系统编程、小型工具与前端静态页面等。
- 主要模块：`Asio` 网络模型与静态`HTTP`服务器、`Linux` 平台练习与网络示例、`C`/`C++20` 语法与标准库示例、`Go`/`Python` 脚本、`Qt` 示例、`Html` 静态资源。
- 自定义库迁移至: [跳转](https://github.com/Hatedatastructures/Custom-libraries#)

### 目录结构概览

- `Asio/` 网络模型与工具
  - `httpserver/` 简单静态`HTTP`服务器，`webroot/`为前端静态资源
  - `model/network/` 协议封装（`http/json/tcp`）、会话管理、代理与加密
  - `model/sched/` 任务调度与线程池
- `Linux/` 平台相关示例
  - `Internet/` `UDP`/`TCP` 网络示例
  - `small_projects/` 倒计时、进度条、进程池等小项目（含`makefile`）
  - `tcp_internet/` `TCP` 通讯模块化示例
- `C/` C语言基础与小程序示例
- `C++20/` 协程、`format`、`ranges` 等标准库示例
- `Go/` 基础库与测试脚本
- `Python/` 简单脚本示例
- `Html/` 静态页面与素材
- `Qt/` 简单`Qt`示例入口 `main.cpp`
- `2024/`、`2025/` 每日练习代码（按日期命名）
- `third_party_libraries/` 第三方库相关测试

