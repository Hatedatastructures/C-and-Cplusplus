
### [模块总览](#模块总览)
### [宏定义](#宏定义)
### [基础类型别名](#基础类型别名)
### [文件存在性检查](#文件存在性检查)
### [日志级别枚举](#日志级别枚举)
### [信息聚合模块](#信息聚合模块)
### [双缓冲队列模块](#双缓冲队列模块)
* [`buffer_queues`](#双缓冲队列模块)
### [配置器模块](#配置器模块)

   * [`placeholders`](#占位符-placeholders)
   * [`to_string`](#类型转换-tostring)
   * [`file_configurator`](#文件配置器-file_configurator)
   * [ `console_configurator`](#控制台配置器-console_configurator)
   * [`function_stacks`](#函数栈管理-function_stacks)
### [核心日志类 `foundation_log`](#核心日志类-foundation_log)
### [接口类 `log`](#接口类-log)
### [快捷命名空间 `rec`](#快捷命名空间-rec)

---

## 模块总览

`custom_log` 模块负责：

* **信息聚合**：收集多级日志内容。
* **双缓冲队列**：异步写入文件或打印控制台。
* **配置器**：格式化前缀与时间，管理输出流。
* **核心日志**：二级缓存，推送到目标（文件/控制台）。
* **接口类**：向外暴露简化使用。

---

## 宏定义

```cpp
#define built_types con::string
#define default_document_checking_macros(path)   custom_log::file_exists(path)
#define default_timestamp_macros               std::chrono::system_clock::now()
#define default_custom_information_input_macros(value) \
    custom_log::information::information<built_types>().custom_log_macro_function_input(value)
```

* **built\_types**：内置信息类型。
* **default\_document\_checking\_macros**：文件存在检查。
* **default\_timestamp\_macros**：获取当前时间。
* **default\_custom\_information\_input\_macros**：链式设置自定义信息。

---

## 基础类型别名

```cpp
using custom_string      = con::string;
using log_timestamp_type = std::chrono::system_clock::time_point;
```

统一使用 `custom_string` 和 `log_timestamp_type`。

---

## 文件存在性检查

```cpp
[[nodiscard]] bool file_exists(const std::string& path);
[[nodiscard]] bool file_exists(const custom_string& path);
[[nodiscard]] bool file_exists(const char* path);
```

* 内联实现，通过 `std::ifstream::good()` 判断。

---

## 日志级别枚举

```cpp
enum class severity_level 
{
    TRIVIAL=0, MINOR, MODERATE, MAJOR, CRITICAL, BLOCKER, FATAL
};
```

* **TRIVIAL** 至 **FATAL**：从轻微到致命。

---

## 信息聚合模块

```cpp
namespace custom_log::information 
{
    template<typename T=custom_string>
    class information 
    {
    public:
        T custom_log_information;
        custom_string debugging_information;
        custom_string general_information;
        custom_string warning_information;
        custom_string error_information;
        custom_string serious_error_information;

        void custom_log_message_input(const T& data);
        information& custom_log_macro_function_input(const T& data);
        template<typename U> void debugging_message_input(const U& data);
        // ... 各级别输入
    };
}
```

* **成员变量**：存储各级别信息。
* **方法**：

  * `*_message_input`：模板输入，自动转 `custom_string`。
  * `custom_log_macro_function_input`：链式调用。

---

## 双缓冲队列模块

```cpp
namespace custom_log::buffer_queues 
{
    class double_buffer_queue 
    {
    public:
        explicit double_buffer_queue(std::ofstream*);
        void enqueue_file(con::string&&);
        void enqueue_console(con::string&&);
        void refresh_buffer_queue();
    private:
        void enqueue(con::string&&, bool to_file);
        void switch_queues();
        void file_buffer();
        void console_buffer();
        bool dequeue(con::string&);
        void flush_all();
    };
}
```

* **两阶段队列**：`produce_queue`、`consume_queue`。
* **自动切换**：达到 `produce_payload_size` 后，启动后台线程刷新。
* **API**：

  * `enqueue_file/console`：数据入队。
  * `refresh_buffer_queue`：强制刷新剩余。

---

## 配置器模块

### 占位符 `placeholders`

```cpp
namespace placeholders 
{
    inline custom_string debugging_information_prefix = "[DEBUG]";
    // … general, warning, error, critical, time 等前缀。
}
```

统一前缀定义。

### 类型转换 `to_string`

```cpp
template<typename T=custom_string>
struct to_string 
{
    static con::string format_time(const log_timestamp_type&);
    static con::string format_information(const information::information<T>&);
};
```

* **format\_time**：`YYYY-MM-DD HH:MM:SS`
* **format\_information**：拼接各级别前缀与信息。

### 文件配置器 `file_configurator`

```cpp
template<typename T>
class file_configurator 
{
public:
    explicit file_configurator(const std::string&);
    template<typename U> void ordinary_type_write(const U&);
    void default_type_write(const information::information<T>&);
    void time_characters(const log_timestamp_type&);
    void refresh_buffer();
};
```

* **功能**：打开文件、入队写入、刷新。
* **缓冲**：调用 `double_buffer_queue`。

### 控制台配置器 `console_configurator`

```cpp
template<typename T>
class console_configurator 
{
public:
    console_configurator();
    template<typename U> void ordinary_type_print(const U&);
    void default_type_print(const information::information<T>&);
    void time_characters(const log_timestamp_type&);
    void refresh_buffer();
};
```

与文件配置器对称，实现控制台输出。

### 函数栈管理 `function_stacks`

```cpp
class function_stacks 
{
public:
    void push(const custom_string&);
    void pop();
    custom_string top() const;
    bool empty() const;
};
```

* **用途**：记录调用链，辅助日志上下文。

---

## 核心日志类 `foundation_log`

```cpp
template<typename T>
class foundation_log 
{
public:
    explicit foundation_log(const std::string&);
    virtual ~foundation_log();

    void write(const information::information<T>&, const log_timestamp_type&);
    void staging(const information::information<T>&, const log_timestamp_type&);
    void push();
    void refresh_buffer();

private:
    file_configurator<T>    log_file;
    console_configurator<T> log_console;
    bool file_output_;
    bool console_output_;
    // 一级、二级缓存容器
};
```

* **`staging`**：二级缓存；超限归档一级。
* **`push`**：并行写入文件与控制台。
* **开关**：`file_switch(bool)`、`console_switch(bool)`。

---

## 接口类 `log`

```cpp
template<typename T>
class log : public foundation_log<T> 
{
public:
    explicit log(const std::string&);
};
```

简化构造，直接调用 `foundation_log` 功能。

---

## 快捷命名空间 `rec`

```cpp
namespace rec 
{
    using namespace custom_log;
    using namespace custom_log::configurator::placeholders;
}
```

简化常用类型与前缀调用。
