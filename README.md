# [文件说明](#说明)
  * [命名空间与整体结构](#命名空间与整体结构)
## [异常处理 `custom_exception`](#异常处理-custom_exception)
## [智能指针 `smart_pointer`](#智能指针-smart_pointer)
 * [`smart_ptr`](#smart_ptrsmart_ptr_type)
 * [`unique_ptr`](#unique_ptrunique_ptr_type)
 * [`shared_ptr`](#shared_ptrshared_ptr_type)
 * [`weak_ptr`](#weak_ptrweak_ptr_type)
## [模板容器 `template_container`](#模板容器-template_container)
 * ### [仿函数 `imitation_functions` ](#仿函数-imitation_functions)
     * [`less` ](#imitation_functions)
     * [`greater`](#imitation_functions)
     * [`hash_imitation_functions`](#imitation_functions)
 * ### [算法 `algorithm`](#算法-algorithm)
     * [`copy`](#copy)
     * [`swap`](#swap)
     * [`find`](#find)
     * [`hash_function`](#hash_algorithmhash_function)
 * ### [基础工具 `practicality`](#基础工具命名空间-practicality)
    * [`pair`](#pairk-v)
    * [`make_pair`](#pairk-v)
 * ### [字符数组 `string_container`](#字符数组)
    * [`string`](#string_container)
 * ### [动态数组容器 `vector_container`](#动态数组)
    * [`vector`](#vector_container)
 * ### [链表容器 `list_container`](#链表容器)
     * [`list`](#list_container)
 * ### [栈适配器 `stack_adapter`](#stack_adapterstack)
     * [`stack`](#stack_adapterstack)
 * ### [队列适配器 `queue_adapter`](#队列适配器)
     * [`queue`](#queue_adapterqueue)
     * [`priority_queue`](#queue_adapterpriority_queue)
 * ### [树形容器 `tree_container`](#树形容器基础-tree_container)

     * [`binary_search_tree`](#binary_search_tree)
     * [`avl_tree`](#avl_tree)

 * ### [基类容器 `base_class_container`]()
     * [`rb_tree`]()
     * [`hash_table`]()
     * [`bit_set`]()
 * ### [关联式容器 `map_container` `set_container`]()
    * ### [`有序容器`]()
         #### [`tree_map`](#map_containertree_map)
         #### [`tree_set`](#tree_set-容器)
    * ### [`无序容器`]()
        #### [`hash_map`](#set_containertree_set)
        #### [`hash_set`](#hash_set-容器)
 * ### [布隆过滤器 `bloom_filter_container`]()
    * ### [`bloom_filter`]()
## [算法细节与性能分析](#算法细节与性能分析)

---
## `说明`

本文档基于 `template_container.hpp` 头文件内容的文档。每个模块按照以下思路进行说明：

* **函数签名与声明**：直接引用头文件中签名，并标注出处。
* **作用描述**：基于函数名与实现逻辑，从使用者角度和实现者角度双重解释函数用途。
* **返回值说明**：给出返回类型、语义含义、可能的错误或异常情况。
* **使用示例**：提供调用示例，演示典型用法。
* **内部原理剖析**：解析底层数据结构、算法流程、关键步骤，结合代码或流程图加深理解。
* **复杂度分析**：对时间复杂度、空间复杂度做详尽分析，包含平均/最坏/摊销情况。
* **边界条件和错误处理**：讨论空容器、极限值、异常抛出或安全检查。
* **示意图**：对涉及树旋转、链表操作、哈希冲突处理等，提供示意图（当前未添加）。
* **注意事项**：包含多线程安全、异常安全、迭代器失效规则等。

---

# 命名空间与整体结构

`template_container.hpp` 中，整体内容分布在以下主要命名空间（摘录并引用）：

* `custom_exception`：自定义异常类 `customize_exception`，用于抛出带消息、函数名、行号信息的异常 。
* `smart_pointer`：实现 `shared_ptr`, `weak_ptr`,`smart_ptr`,`unique_ptr` 4种智能指针，管理动态内存资源。
* `practicality`：提供工具类型，如 `pair`、和 `make_pair`函数 `make_pair`函数自动推导类型。
* `imitation_functions`：仿函数集合，如 `less`, `greater`, `hash_imitation_functions` 等，用于比较和返回内置类型哈希值操作。
* `algorithm`：算法模块，包含`hash_algorithm`、`swap`、`copy`、`find`这个几个基础算法工具,`hash_algorithm`是个命名空间，展开是`hash_function`类,在`con`命名空间已经展开
* `string_container`：字符数组`string`。
* `vector_container`：动态数组 `vector`。
* `list_container`：双向链表 `list`。
* `stack_adapter`, `queue_adapter`：容器适配器 `stack`, `queue`, `priority_queue`。
* `tree_container`：树形容器基础，包括 `binary_search_tree`, `avl_tree` 等。
* `map_container`, `set_container`：关联容器 `tree_map`, `tree_set`，基于红黑树实现。`hash_map`,`hash_set`,基于哈希表实现。
* `base_class_container`：基类容器，如 `hash_table`, `bit_set`, `rb_tree` 基类实现等（在此命名空间）。
* `bloom_filter_container`：布隆过滤器实现，依赖基类容器`bit_set`。
* `con`, `ptr`, `exc`：方便使用的命名空间，将上述容器异常智能指针引入，减少命名长度,方便`直接调用`

整体结构如：

```cpp
namespace custom_exception          { ... }
namespace smart_pointer             { ... }
namespace practicality              { ... }
namespace imitation_functions       { ... }
namespace algorithm                 { ... }
namespace string_container          { ... }
namespace vector_container          { ... }
namespace list_container            { ... }
namespace stack_adapter             { ... }
namespace queue_adapter             { ... }
namespace tree_container            { ... }
namespace map_container             { ... }
namespace set_container             { ... }
namespace base_class_container      { ... }
namespace bloom_filter_container    { ... }
namespace con                       { using namespace template_container; }
namespace ptr                       { using namespace smart_pointer;      }
namespace exc                       { using namespace custom_exception;   }
```

>各模块实现互相调用，结构清晰。但是对于map和set那块比较复杂，会在他们的文档里详细介绍

---

# 异常处理 `custom_exception`

## 类 `customize_exception`

**定义位置**：`custom_exception`里

```cpp
namespace custom_exception
{
    class customize_exception final : public std::exception
    {
    private:
        char* message;
        char* function_name;
        size_t line_number;
    public:
        customize_exception(const char* message_target,const char* function_name_target,const size_t& line_number_target) noexcept;
        [[nodiscard]] const char* what() const noexcept override;
        [[nodiscard]] const char* function_name_get() const noexcept;
        [[nodiscard]] size_t line_number_get() const noexcept;
        ~customize_exception() noexcept override;
    };
}
```

**引用**：`template_container::customize_exception`.

**注意**：该类不能被继承

### 作用

* 该类实列用于在发生错误或异常情况下，抛出带有详细信息的异常，包含错误消息、发生异常的函数名、异常位置的代码行号，便于调试和查找异常错误。

### 构造函数

```cpp
customize_exception(const char* message_target, const char* function_name_target, const size_t& line_number_target) noexcept
```

* **参数**

    * `message_target`：返回错误消息字符串。
    * `function_name_target`：返回抛出异常的函数名称。
    * `line_number_target`：返回抛出异常的代码行号。
* **异常规范**：`noexcept`，保证构造过程中不再抛出异常。
* **内部实现**：复制字符串到内部 `char*` 缓冲区（通过 `new char[...]`），保存行号。
* **边界检查**：若 `message_target` 或 `function_name_target` 为空？头文件实现未对空指针进行检查，调用者需自己保证传入非空合法指针以避免未定义行为。

### 成员方法

1. `[[nodiscard]] const char* what() const noexcept override`

    * **作用**：返回异常消息，覆写 `std::exception::what()`。
    * **返回值**：`const char*`，指向内部存储的消息字符串。
    * **注意**：返回值生命周期与异常对象相同，异常对象销毁后不应再访问。

2. `[[nodiscard]] const char* function_name_get() const noexcept`

    * **作用**：返回抛出异常时的函数名字符串。
    * **返回值**：`const char*`，指向内部存储的函数名。

3. `[[nodiscard]] size_t line_number_get() const noexcept`

    * **作用**：获取抛出异常地行号。
    * **返回值**：`size_t`，行号信息。

4. 析构函数：`~customize_exception() noexcept override`

    * **作用**：释放内部 `message`、`function_name` 指针分配的内存，避免内存泄漏。
    * **异常规范**：`noexcept`，在析构时不会抛出。
    * **实现注意**：若复制或释放过程中出现错误，因 `noexcept`，应保证安全。

### 使用示例

```cpp
#include "template_container.hpp"
// ...
void some_function()
{
    if(error_condition) 
    {
        throw custom_exception::customize_exception("错误信息", __func__, __LINE__);
    }
}
try // 捕获 
{
    some_function();
}
catch(const custom_exception::customize_exception& e) 
{
    std::cerr << "Exception: "   << e.what() 
              << " in function " << e.function_name_get() 
              << " at line "     << e.line_number_get() << std::endl;
}
```

* **错误处理建议**：调用者在捕获时，可结合 `what()`, `function_name_get()`, `line_number_get()` 记录详细日志或输出到调试控制台，提升排错效率。

### 复杂度与安全

* 注意改异常类不支持`拷贝构造`,`移动拷贝构造`,`赋值`，`移动赋值`。
* 构造时字符串复制成本与消息长度成正比，通常较短消息复制开销较小。
* 析构释放开销固定。
* 该未使用锁或多线程保护，若在多线程环境中抛出/捕获异常时，请根据自己环境重载库标准异常。

---

## 智能指针`smart_pointer`
>注意！当前未处理个别错误，及涉及到指针管理权转移等，还未测试
### 模块概览

`smart_pointer` 命名空间中，提供如 `shared_ptr`, `weak_ptr`,`smart_ptr`,`unique_ptr` 4种智能指针的实现，管理资源，避免手动 `delete`，支持引用计数、多线程安全（通过内部互斥锁）。

**引用**：在头文件中，可搜索 `namespace smart_pointer` 获取完整实现；以下示例基于头文件内容分析。

> **注意**：此处省略完整源码摘录
#### `smart_ptr<smart_ptr_type>`
* **成员变量**
    * `_ptr`：裸指针，指向托管对象。
* **构造与析构**
    * 构造自裸指针：`explicit smart_ptr(smart_ptr_type* p)`。
    * 拷贝构造：指针管理权转移，原先智能指针为空。
    * 析构：作用域结束自动释放。
* **赋值运算符**
    * 拷贝赋值：指针管理权转移，原先智能指针为空。
* **成员函数**

    * `Ref& operator*() const`, `Ptr operator->() const`: 访问托管对象。
* **线程安全**
    * 存在线程安全。
* **问题**
    * > 如果在赋值和拷贝之后，管理权转移，如果还访问原先的智能指针就会出现错误！ 
* **示例**

  ```cpp
  template_container::smart_pointer:: smart_ptr<my_class> sp1(new my_class(...));
  {
      auto sp2 = sp1; //指针管理权转移
  } 
  delete 对象
  ```
* **复杂度**

    * 拷贝构造/赋值，时间复杂度 O(1)。
    * 访问托管对象效率与裸指针相当。
> **引用/出处**：头文件中 `namespace smart_pointer::smart_ptr`

---
#### `unique_ptr<unique_ptr_type>`
* **成员变量**
    * `_ptr`：裸指针，指向托管对象。
* **构造与析构**

    * 构造自裸指针：`explicit unique_ptr(unique_ptr_type* p)`。
    * 拷贝构造：删除状态。
    * 析构：作用域结束自动释放。
* **赋值运算符**
    * 拷贝赋值：删除状态。
* **成员函数**
    * `Ref& operator*() const`, `Ptr operator->() const`: 访问托管对象。
    * `get_ptr() const noexcept` 返回托管指针。
* **线程安全**
    * 存在线程安全。
* **问题**
    * > 暂时没发现，欢迎测试
* **示例**

  ```cpp
  template_container::smart_pointer::unique_ptr<my_class> sp1(new my_class(...));
  {
      auto sp2 = sp1; //独占资源，不存在赋值一类行为
  } 
  delete 对象
  ```
* **复杂度**

    * 拷贝构造/赋值，时间复杂度 O(1)。
    * 访问托管对象效率与裸指针相当。
> **引用/出处**：头文件中 `namespace smart_pointer::unique_ptr`
--- 
#### `shared_ptr<shared_ptr_type>`

* **成员变量**
    * `_ptr`：裸指针，指向托管对象。
    * `shared_pcount`：引用计数（通常为指针，指向堆上计数）。
    * `_pmutex`：`std::mutex*` 或其他同步机制，用于多线程引用计数安全。
* **构造与析构**
    * 默认构造：初始化 `_ptr` 为 `nullptr`，`shared_pcount` 为 nullptr 或 0。
    * 构造自裸指针：`explicit shared_ptr(shared_ptr_type* p)`，设置 `_ptr = p`，`shared_pcount = new size_t(1)`，初始化互斥锁。
    * 拷贝构造：加锁后引用计数递增。
    * 移动构造：接管资源，不增加引用计数。
    * 析构：加锁后引用计数递减，若减为 0，则 `delete _ptr`，释放互斥锁及计数内存。
* **赋值运算符**
    * 拷贝赋值：先比较自赋值保护，释放自身旧资源（递减引用计数并可能删除），再复制新资源并加锁递增。
    * 移动赋值：释放自身旧资源，再接管右值资源，无需增加计数。
* **成员函数**

    * `Ptr get_ptr() const noexcept`: 返回裸指针。
    * `Ref operator*() const`, `Ptr operator->() const`: 访问托管对象。
    * `int get_sharedp_count() const noexcept`: 返回当前引用计数。
    * `void release() noexcept`: 释放当前资源并可能删除，重新托管 `p`。
* **线程安全**

    * 通过内部互斥锁保护引用计数的递增/递减，保证多线程场景下安全管理。
* **示例**

  ```cpp
  template_container::smart_pointer::shared_ptr<my_Class> sp1(new my_class(...));
  {
      auto sp2 = sp1; // 引用计数从 1 增到 2
      std::cout << sp1.get_sharedp_count(); // 输出 2
  } // sp2 离开作用域，引用计数减为 1
  sp1.release(); // 计数减为 0，delete 对象
  ```
* **复杂度**
    * 拷贝构造/赋值、析构涉及锁和计数更新，时间复杂度 O(1)，但存在锁开销。
    * 访问托管对象效率与裸指针相当。
> **引用/出处**：头文件中 `namespace smart_pointer::shared_ptr`
---
#### `weak_ptr<weak_ptr_type>`

* **用途**：解决循环引用问题，可观察 `shared_ptr` 管理的对象但不影响引用计数。
* **成员变量**
    * `_weak_pcount`：指向与 `shared_ptr` 相同或独立的弱引用计数结构。
    * `_pmutex`：共享锁或与 `shared_ptr` 共享的互斥锁用于同步。
* **构造与析构**
    * 从 `shared_ptr` 构造：增加弱引用计数，不增加强引用计数。
    * 默认构造：空状态，无托管对象。
    * 拷贝/移动：调整弱引用计数或接管资源。
    * 析构：减少弱引用计数，不会删除托管对象，只当强引用计数为 0 且弱引用计数为 0 时回收计数结构。
* **成员函数**

    * `int get_sharedp_count() const noexcept`: 返回当前强引用计数。
    * `void release() noexcept`: 释放弱引用，不影响托管对象。
* **示例**

  ```cpp
  auto sp = template_container::smart_pointer::shared_ptr<my_Class>(new my_class);
  template_container::smart_pointer::weak_ptr<my_class> wp = sp;
  if(auto locked = wp.lock()) 
  {
      // 托管对象依然存在，可安全使用 locked
  }
  sp.release(); // 删除托管对象
  ```
* **复杂度**

    * lock() 涉及原子或锁检查计数，O(1)时间；其后构造临时 shared_ptr 可能涉及锁和计数递增。
    * 其他操作 O(1)。

> **引用/出处**：头文件中 `namespace smart_pointer::weak_ptr` 

---

# 模板容器 `template_container`

##  基础工具命名空间 `practicality`
### `pair<K, V>`

* **定义**：类似于 `std::pair`，用于键值对存储，如 map/set 中。
* **成员**

    * `first`：键类型 `K` 或其它用途类型。
    * `second`：值类型 `V`。
* **构造**
    * 默认构造：`pair()`，`first`、`second` 默认初始化。
    * `pair(const K&, const V&)` 构造。
* **运算符**
    * 拷贝/移动构造、赋值运算符。
    * `operator==`, `operator!=`。
    * `pair* operator->() noexcept`.
    * 重载 `std::ostream& operator<<` 可以直接输出
* **用途**：关联容器 `tree_map`, `hash_map` 等内部使用 `pair<key, value>` 存储元素。
  * **示例**

    ```cpp
    template_container::practicality::pair<int, con::string> p(1, "one");
    std::cout << p.first << ": " << p.second << std::endl;
    ```
### `make_pair`
 * **make_pair函数** ：一个自动类型推导的函数，返回的是pair类实例。

>   **引用/出处**：头文件中 `namespace template_container::practicality::pair`
## 仿函数 `imitation_functions`

### `imitation_functions`

* **内容**：包含常见比较、等价、散列等仿函数。
* 常见类型：

    * `less<T>`, `greater<T>`，用于比较元素大小、相等。
    * `hash_imitation_functions`：针对一些内置类型提供 ` size_t operator()(const T&) -> size_t` 数据哈希值。
* **用途**：关联容器、哈希表等需要自定义比较器、哈希计算时，可传入此默认仿函数或用户自定义仿函数。
* **示例**

  ```cpp
  template_container::imitation_functions::less<int> cmp;
  bool lt = cmp(3, 5); // true
  template_container::imitation_functions::hash_imitation_functions hf;
  size_t hv = hf(5678.8763468);
  ```
* **注意**：若需要`自定义类型`，可重新写一个哈希仿函数返回数据类型哈希值，并传递给容器模板参数。

## 算法 `algorithm`
### `copy`
* **内容**：基本算法工具 `copy`
* **用途**：线性拷贝值
* **示例**

  ```cpp
  using template_container::algorithm;
  int source[] = {1, 2, 3, 4, 5};
  int size = sizeof(source) / sizeof(source[0]);
  // 创建数组
  int target[size];
  copy(source, source + size, target);
  
  ```
  * **参数**：起始位置 `source_sequence_copy begin`，结束位置 `source_sequence_copy end`，拷贝位置 `target_sequence_copy first`.
  * **返回值** ：返回原先拷贝位置地址

  >   **引用**：头文件中`namespace template_container::algorithm::copy`.
### `find`
* **内容**：基本算法工具 `find`
* **用途**：迭代器查找某个值
  * **示例**

    ```cpp
     using template_container::algorithm;
     using map_pair = template_container::practicality::pair<size_t,size_t>;
     using map_string = template_container::string_container::string;
     using map_data = template_container::practicality::pair<map_pair,map_string>;
     template_container::map_container::tree_map<map_pair,map_string,imitation_functions::comparators> map_pair_test;
     constexpr size_t size = 100000;
     template_container::vector_container::vector<map_pair> map_pair_array;
     template_container::vector_container::vector<map_string> map_string_array;
     template_container::vector_container::vector<map_data> map_data_array;
     for(size_t i = 0; i < size; i++)
     {
         map_pair_array.push_back(map_pair(i,i));
         map_string_array.push_back(map_string("hello world"));
         map_data_array.push_back(map_data(std::move(map_pair_array[i]),std::move(map_string_array[i])));
     }
     for(size_t j = 0; j < size; j++)
     {
         map_pair_test.push(std::move(map_data_array[j]));
     }                                                              //注意自定义==的重载才能用find函数
     auto map_iterator = find(map_pair_test.begin(), map_pair_test.end(),std::move(map_data_array[j])); //返回找到位置的迭代器
    ```
      * **参数**：起始位置 `source_sequence_find begin`，结束位置 `source_sequence_find end`，查找的数据 `target_sequence_find& value`.
      * **返回值** ：如果找到值返回该值的迭代器，如果找不到返回尾位置迭代器

  >    **引用**：头文件中`namespace template_container::algorithm::find`.

### `swap`
* **内容**：基本算法工具 `swap`
* **用途**：数据类型深拷贝交换（需要提前重载数据类型的拷贝构造）
* **示例**

  ```cpp
  void swap(template_container::list_container::list<list_type>& swap_target) noexcept
  {
     template_container::algorithm::swap(_head,swap_target._head);
  }
  
  ```
    * **参数**：数据位置A `swap_data_type& a`，数据位置B `swap_data_type& b`.
    * **返回值** ：void

  >   **引用**：头文件中`namespace template_container::algorithm::swap`.
### `hash_algorithm::hash_function`

* **内容**：基本算法工具，如哈希函数实现（`hash_algorithm::hash_function<T>`），包括 `hash_sdmmhash`, `hash_djbhash`, `hash_pjwhash` 等多种哈希函数实现。
* **用途**：布隆过滤器或哈希表中使用不同哈希函数，减少冲突。
* **示例**

  ```cpp
  using string =  template_container::string_container::string;
  class custom_comparators 
  {
  public:
     size_t operator() (const string& string_data)
     {
         size_t hash_string = 0;
         for(const auto&  ch : string_data)
         {
              hash_string  = hash_string * 131 + static_cast<size_t>(ch);
         }
         return hash_string;
     }
  }
  //可重载模板版本的，前提把像custom_comparators类的size_t operator()封装好
  template_container::algorithm::hash_algorithm::hash_function<string,custom_comparators> hf;
  string test_string = "hello,word!";
  size_t h1 = hf.hash_sdmmhash(test_string);
  ```
* **复杂度**：哈希函数计算时间依赖输入长度，通常 O(len)。

    > **引用**：头文件中`namespace template_container::algorithm::hash_algorithm`.

---

## 字符数组

### `string_container`
* **概览**:`string`类是一个自定义实现的字符串容器，模拟了标准库`std::string`的核心功能，
同时提供了额外的字符串操作方法。该类使用动态内存分配管理字符数据，支持迭代器遍历、字符串修改、子串操作等功能。
### 类及其函数定义：
```cpp
namespace string_container 
{
    class string 
    {
    private:
        char*  _data;
        size_t _size;
        size_t _capacity;
    public:
        // 迭代器类型定义
        using iterator = char*;
        using const_iterator = const char*;
        using reverse_iterator = iterator;
        using const_reverse_iterator = const_iterator;
        constexpr static const size_t nops = -1;
        
        // 构造函数、析构函数及赋值运算符
        string(const char* str_data = " ");
        string(char*&& str_data) noexcept;
        string(const string& str_data);
        string(string&& str_data) noexcept;
        string(const std::initializer_list<char> str_data);
        ~string() noexcept;
        
        // 迭代器相关方法
        [[nodiscard]] iterator begin() const noexcept;
        [[nodiscard]] iterator end() const noexcept;
        [[nodiscard]] const_iterator cbegin() const noexcept;
        [[nodiscard]] const_iterator cend() const noexcept;
        [[nodiscard]] reverse_iterator rbegin() const noexcept;
        [[nodiscard]] reverse_iterator rend() const noexcept;
        [[nodiscard]] const_reverse_iterator crbegin() const noexcept;
        [[nodiscard]] const_reverse_iterator crend() const noexcept;
        
        // 容量相关方法
        [[nodiscard]] bool empty() const noexcept;
        [[nodiscard]] size_t size() const noexcept;
        [[nodiscard]] size_t capacity() const noexcept;
        
        // 元素访问方法
        [[nodiscard]] char* c_str() const noexcept;
        [[nodiscard]] char back() const noexcept;
        [[nodiscard]] char front() const noexcept;
        char& operator[](const size_t& access_location);
        const char& operator[](const size_t& access_location) const;
        
        // 字符串修改方法
        string& uppercase() noexcept;
        string& lowercase() noexcept;
        string& prepend(const char*& sub_string);
        string& insert_sub_string(const char*& sub_string, const size_t& start_position);
        string sub_string(const size_t& start_position) const;
        string sub_string_from(const size_t& start_position) const;
        string sub_string(const size_t& start_position, const size_t& terminate_position) const;
        void allocate_resources(const size_t& new_inaugurate_capacity);
        string& push_back(const char& temporary_str_data);
        string& push_back(const string& temporary_string_data);
        string& push_back(const char* temporary_str_ptr_data);
        string& resize(const size_t& inaugurate_size, const char& default_data = '\0');
        iterator reserve(const size_t& new_container_capacity);
        string& swap(string& str_data) noexcept;
        [[nodiscard]] string reverse() const;
        [[nodiscard]] string reverse_sub_string(const size_t& start_position, const size_t& terminate_position) const;
        
        // 输出方法
        void string_print() const noexcept;
        void string_reverse_print() const noexcept;
        
        // 运算符重载
        friend std::ostream& operator<<(std::ostream& string_ostream, const string& str_data);
        friend std::istream& operator>>(std::istream& string_istream, string& str_data);
        string& operator=(const string& str_data);
        string& operator=(const char* str_data);
        string& operator=(string&& str_data) noexcept;
        string& operator+=(const string& str_data);
        bool operator==(const string& str_data) const noexcept;
        bool operator<(const string& str_data) const noexcept;
        bool operator>(const string& str_data) const noexcept;
        [[nodiscard]] string operator+(const string& string_array) const;
    };
}
```
### 内部数据结构
* **底层**：基于动态内存的连续字符数组。
* **成员变量** ：
    * `char* _data`：指向已分配内存区域的首地址。
    * `size_t _size`：当前字符串长度。
    * `size_t _capacity`：当前分配的内存容量。
* **内存布局** 位置连续，以 `\0`结尾，符合 C 风格字符串要求。
### 构造与析构
* **默认构造**：  `string(const char* str_data = " ")`，初始化 `_data` 为输入字符串的副本。
* **移动构造**： `string(char*&& str_data) noexcept`，接管右值 `_data` 指针，置右值为 `nullptr`，避免复制字符串。
* **拷贝构造**： `string(const string& str_data)`，分配相同容量，复制所有字符。
* **移动构造**： `string(string&& str_data) noexcept`，接管右值 `_data` 指针，置右值为 `nullptr`，避免复制字符。
* **初始化列表构造**：`string(const std::initializer_list<char> str_data)`，使用初始化列表中的字符初始化字符串。
* **析构**：释放 `_data` 指向的内存。
### 迭代器
* **定义** `iterator`, `const_iterator`, `reverse_iterator`, `const_reverse_iterator`，支持随机访问特性。
* `begin()`/`end()` 返回指向 `_data`, _`data + _size`。
* `rbegin()`/`rend()` 返回反向迭代器
### 访问元素
* `char& operator[](size_t index)`, `const char& operator[](size_t index) const`：做边界检查，直接访问第`index`个字符。
* `front()`, `back()`: 访问第一个和最后一个字符；须保证 `_size > 0`。
* `c_str()`: 返回指向内部字符数组的指针，以 `\0` 结尾。
  * #### 示例
    ```cpp
    string s("hello");
    std::cout << s[0] << ", " << s.back() << ", " << s.c_str();
    ```
        
### 字符串修改
#### 追加操作
* `string& push_back(const char& c)` 
    * **功能**：末尾添加字符，容量不足时扩容，策略：`空间不足2倍增容`。
* `string& push_back(const string& str)` / `string& push_back(const char* str)`
    * **功能**：追加字符串 / `C` 串，自动扩容并深拷贝内容。
#### 插入操作
* `string& prepend(const char*& sub)`
   * **功能**：头部插入子串，使用`memmove`移动原数据并扩容。
* `string& insert_sub_string(const char*& sub, size_t pos)` 
   * **功能**：在`pos`位置插入子串，越界抛异常，通过临时缓冲区保证内存安全。
#### 内存管理
* `void allocate_resources(size_t new_cap)`
   * **功能**：重新分配内存，复制原数据后释放旧空间，仅在`new_cap > _capacity`时执行。
*  `iterator reserve(size_t new_cap)`
   * **功能**：预分配内存，返回首地址迭代器，内存不足抛`std::bad_alloc`。
#### 其他修改
*  `string& resize(size_t n, char c = '\0')`
    * **功能**：调整长度，扩容时用c填充，缩容时截断并添加\0。
*   `string& swap(string& str) noexcept`
    * **功能**：交换两字符串的`_data、_size`、`_capacity`，时间复杂度 `O(1)`。
####  子串与反转
* `string sub_string(size_t start) / string sub_string_from(size_t start)`
  * **功能**：从start提取子串至末尾，越界抛custom_exception。
*  `string sub_string(size_t start, size_t terminate)`
   * **功能**：提取`[start, terminate)`区间子串，检查位置合法性。
*   `string reverse() const`
    * **功能**：返回反转后的新字符串，空串抛异常，通过反向迭代器实现。
*   `string reverse_sub_string(size_t start, size_t terminate) const`
    * **功能**：返回指定区间子串的反转，校验参数有效性。
#### 大小写转换
 * `string& uppercase() noexcept / string& lowercase() noexcept`
   * **功能**：原地转换大小写，遍历字符并调整 `ASCII` 码（小写 + 32 / 大写 - 32）。
#### 容量与工具方法
 * `bool empty() const noexcept` / `size_t size() const noexcept` / `size_t capacity() const noexcept`
     * **功能**：返回空状态、长度和容量，时间复杂度 O (1)。
 * `void string_print() const noexcept` / `void string_reverse_print() const noexcept`
     * **功能**：正向打印字符串和反向打印字符串。
 ####  运算符重载
 * ##### 赋值运算符：
     * `string& operator=(const string& str)` / `string& operator=(const char* str)`
       * **功能**：深拷贝赋值，先释放原内存再重新分配。
     * `string& operator=(string&& str) noexcept`
       * **功能**：移动赋值，接管右值资源并清空原对象。
 * ##### 拼接运算符：
     * `string& operator+=(const string& str)`
       * **功能**：原地拼接，扩容后复制数据。
     *  `string operator+(const string& str) const`
        * **功能**：返回拼接后的新字符串，避免修改原对象。
 * ##### 比较运算符：
    * `bool operator==(const string& str) const noexcept`
       `bool operator<(const string& str) const noexcept` / `bool operator>(const string& str) const noexcept`
        * **功能**：字典序比较，先比字符再比长度，空串小于非空串。
 #### 输入输出运算符
 * `friend std::istream& operator>>(std::istream&, string&)`
   * **功能**：读取字符直至换行或 `EOF`，逐个`push_back`实现输入。
* `friend std::ostream& operator<<(std::ostream&, const string&)`
    * **功能**：遍历字符并输出，支持流式操作。
#### 复杂度与异常安全
*  **时间复杂度**：
    *  **随机访问**：`O(1)`
    *  **插入** / **删除中间**：`O(n)`（移动元素）
    *  **扩容**：`O(n)`（复制数据），摊销后均摊 `O(1)`
* **空间复杂度**：
  * `O(n)`（存储字符 +`\0`）
* **异常处理**：
    * 内存分配失败抛`std::bad_alloc`。
    * 越界操作抛`custom_exception::customize_exception`，包含错误位置和函数名。
*  **迭代器失效**：
   * 扩容或修改数据时，所有迭代器和引用失效。
#### 注意事项
* **迭代器安全**：扩容或修改数据会导致迭代器失效，需重新获取`迭代器`。
* **内存优化**：频繁拼接前建议使用`reserve(n)`预分配空间，减少重分配开销。
* **异常安全**：插入 / 扩容操作可能抛异常，建议使用`try-catch`处理或确保传入参数合法。
* **移动语义**：对临时字符串优先使用移动构造 / 赋值`（string&&）`，避免深拷贝性能损耗。
### **`string`** 类用法示例

  ```cpp
using namespace template_container;
int main() 
{
    // 1. 构造函数示例
    std::cout << "=== 构造函数示例 ===\n";
    
    // 默认构造函数
    string_container::string s1;
    std::cout << "s1 (默认构造): " << s1 << std::endl;
    
    // C风格字符串构造
    string_container::string s2("Hello");
    std::cout << "s2 (C风格字符串构造): " << s2 << std::endl;
    
    // 拷贝构造
    string_container::string s3(s2);
    std::cout << "s3 (拷贝构造自s2): " << s3 << std::endl;
    
    // 移动构造 (使用临时对象)
    string_container::string s4(string_container::string("World"));
    std::cout << "s4 (移动构造): " << s4 << std::endl;
    
    // 初始化列表构造
    string_container::string s5({'H', 'e', 'l', 'l', 'o'});
    std::cout << "s5 (初始化列表构造): " << s5 << std::endl;
    
    // 2. 访问元素示例
    std::cout << "\n=== 访问元素示例 ===\n";
    
    // 下标运算符
    std::cout << "s2[0]: " << s2[0] << std::endl;
    
    // front() 和 back()
    std::cout << "s2.front(): " << s2.front() << std::endl;
    std::cout << "s2.back(): " << s2.back() << std::endl;
    
    // c_str()
    std::cout << "s2.c_str(): " << s2.c_str() << std::endl;
    
    // 3. 字符串修改示例
    std::cout << "\n=== 字符串修改示例 ===\n";
    
    // push_back() 添加单个字符
    s2.push_back('!');
    std::cout << "s2.push_back('!'): " << s2 << std::endl;
    
    // push_back() 添加字符串
    s2.push_back(string_container::string(" World"));
    std::cout << "s2.push_back(\" World\"): " << s2 << std::endl;
    
    // push_back() 添加C风格字符串
    s2.push_back(" Again");
    std::cout << "s2.push_back(\" Again\"): " << s2 << std::endl;
    
    // prepend() 在开头插入
    s2.prepend("Hi, ");
    std::cout << "s2.prepend(\"Hi, \"): " << s2 << std::endl;
    
    // insert_sub_string() 在中间插入
    const char* str_test = " there";
    s2.insert_sub_string(str_test, 4);
    std::cout << "s2.insert_sub_string(\" there\", 4): " << s2 << std::endl;
    
    // resize() 调整大小
    s2.resize(10, 'x');
    std::cout << "s2.resize(10, 'x'): " << s2 << std::endl;
    
    s2.resize(20, 'y');
    std::cout << "s2.resize(20, 'y'): " << s2 << std::endl;
    
    // 4. 子串与反转示例
    std::cout << "\n=== 子串与反转示例 ===\n";
    
    // sub_string() 提取子串
    string_container::string sub1 = s2.sub_string(3);
    std::cout << "s2.sub_string(3): " << sub1 << std::endl;
    
    string_container::string sub2 = s2.sub_string_from(5);
    std::cout << "s2.sub_string_from(5): " << sub2 << std::endl;
    
    string_container::string sub3 = s2.sub_string(2, 8);
    std::cout << "s2.sub_string(2, 8): " << sub3 << std::endl;
    
    // reverse() 反转字符串
    string_container::string rev1 = s2.reverse();
    std::cout << "s2.reverse(): " << rev1 << std::endl;
    
    // reverse_sub_string() 反转子串
    string_container::string rev2 = s2.reverse_sub_string(3, 8);
    std::cout << "s2.reverse_sub_string(3, 8): " << rev2 << std::endl;
    
    // 5. 大小写转换示例
    std::cout << "\n=== 大小写转换示例 ===\n";
    
    s2.uppercase();
    std::cout << "s2.uppercase(): " << s2 << std::endl;
    
    s2.lowercase();
    std::cout << "s2.lowercase(): " << s2 << std::endl;
    
    // 6. 容量与工具方法示例
    std::cout << "\n=== 容量与工具方法示例 ===\n";
    
    std::cout << "s2.empty(): " << (s2.empty() ? "true" : "false") << std::endl;
    std::cout << "s2.size(): " << s2.size() << std::endl;
    std::cout << "s2.capacity(): " << s2.capacity() << std::endl;
    
    // reserve() 预分配空间
    s2.reserve(100);
    std::cout << "s2.reserve(100) 后 capacity: " << s2.capacity() << std::endl;
    
    // swap() 交换字符串
    string_container::string temp("Temp String");
    s2.swap(temp);
    std::cout << "s2.swap(temp) 后 s2: " << s2 << std::endl;
    std::cout << "s2.swap(temp) 后 temp: " << temp << std::endl;
    
    // 7. 运算符重载示例
    std::cout << "\n=== 运算符重载示例 ===\n";
    
    // 赋值运算符
    s2 = "New Value";
    std::cout << "s2 = \"New Value\": " << s2 << std::endl;
    
    s2 = string_container::string("Another Value");
    std::cout << "s2 = string(\"Another Value\"): " << s2 << std::endl;
    
    // += 运算符
    s2 += " appended";
    std::cout << "s2 += \" appended\": " << s2 << std::endl;
    
    // + 运算符
    string_container::string s6 = s2 + " and more";
    std::cout << "s6 = s2 + \" and more\": " << s6 << std::endl;
    
    // 比较运算符
    string_container::string s7("Test");
    string_container::string s8("Test");
    string_container::string s9("Different");
    
    std::cout << "s7 == s8: " << (s7 == s8 ? "true" : "false") << std::endl;
    std::cout << "s7 == s9: " << (s7 == s9 ? "true" : "false") << std::endl;
    std::cout << "s7 < s9: " << (s7 < s9 ? "true" : "false") << std::endl;
    std::cout << "s7 > s9: " << (s7 > s9 ? "true" : "false") << std::endl;
    
    // 8. 输入输出示例
    std::cout << "\n=== 输入输出示例 ===\n";
    
    // 输出
    std::cout << "请输入一个字符串: ";
    string_container::string input;
    std::cin >> input;
    std::cout << "你输入的是: " << input << std::endl;
    
    // 9. 迭代器示例
    std::cout << "\n=== 迭代器示例 ===\n";
    
    std::cout << "使用迭代器遍历 s2: ";
    for (auto it = s2.begin(); it != s2.end(); ++it) 
    {
        std::cout << *it;
    }
    std::cout << std::endl;
    
    std::cout << "使用反向迭代器遍历 s2: ";
    for (auto it = s2.rbegin(); it != s2.rend(); --it) 
    {
        std::cout << *it;
    }
    std::cout << std::endl;
    
    // 10. 工具方法
    std::cout << "\n=== 工具方法示例 ===\n";
    
    std::cout << "打印 s2: ";
    s2.string_print();
    
    std::cout << "反向打印 s2: ";
    s2.string_reverse_print();
    
    return 0;
}

  ```

> **引用**：头文件 `string_container` 命名空间。

---

## 动态数组

### `vector_container`

#### 类概述
*   `vector` 类是一个模板化的动态数组容器，模拟了标准库 `std::vector` 的核心功能。
    该容器使用连续内存存储元素，支持动态扩容、随机访问和各种容器操作。通过模板参数 `vector_type`
    支持任意数据类型，并提供了完整的迭代器系统和异常处理机制。
### **类及其函数定义**：
```cpp
namespace vector_container 
{
    template <typename vector_type>
    class vector 
    {
    public:
        using iterator = vector_type*;
        using const_iterator = const vector_type*;
        using reverse_iterator = iterator;
        using const_reverse_iterator = const_iterator;
    
    private:
        iterator _data_pointer;     // 指向数据起始位置
        iterator _size_pointer;     // 指向数据结束位置（最后一个元素的下一个位置）
        iterator _capacity_pointer; // 指向容量结束位置
    
    public:
        // 迭代器方法
        [[nodiscard]] iterator begin() noexcept;
        [[nodiscard]] iterator end() noexcept;
        
        // 容量方法
        [[nodiscard]] size_t size() const noexcept;
        [[nodiscard]] size_t capacity() const noexcept;
        [[nodiscard]] bool empty() const noexcept;
        
        // 元素访问
        [[nodiscard]] vector_type& front() const noexcept;
        [[nodiscard]] vector_type& back() const noexcept;
        [[nodiscard]] vector_type& head() const noexcept;
        [[nodiscard]] vector_type& tail() const noexcept;
        vector_type& find(const size_t& find_size);
        vector_type& operator[](const size_t& access_location);
        const vector_type& operator[](const size_t& access_location) const;
        
        // 构造函数
        vector() noexcept;
        explicit vector(const size_t& container_capacity, const vector_type& vector_data = vector_type());
        vector(std::initializer_list<vector_type> lightweight_container);
        vector(const vector<vector_type>& vector_data);
        vector(vector<vector_type>&& vector_data) noexcept;
        ~vector() noexcept;
        
        // 修改方法
        void swap(vector<vector_type>& vector_data) noexcept;
        iterator erase(iterator delete_position) noexcept;
        vector<vector_type>& resize(const size_t& new_container_capacity, const vector_type& vector_data = vector_type());
        vector<vector_type>& push_back(const vector_type& vector_type_data);
        vector<vector_type>& push_back(vector_type&& vector_type_data);
        vector<vector_type>& pop_back();
        vector<vector_type>& push_front(const vector_type& vector_type_data);
        vector<vector_type>& pop_front();
        vector<vector_type>& size_adjust(const size_t& data_size, const vector_type& padding_temp_data = vector_type());
        
        // 赋值运算符
        vector<vector_type>& operator=(const vector<vector_type>& vector_data);
        vector<vector_type>& operator=(vector<vector_type>&& vector_mobile_data) noexcept;
        vector<vector_type>& operator+=(const vector<vector_type>& vector_data);
        
        // 友元运算符
        template <typename const_vector_output_templates>
        friend std::ostream& operator<<(std::ostream& vector_ostream, const vector<const_vector_output_templates>& dynamic_arrays_data);
    };
    
    template <typename const_vector_output_templates>
    std::ostream& operator<<(std::ostream& vector_ostream, const vector<const_vector_output_templates>& dynamic_arrays_data);
}
```
#### 内部数据结构

* **底层**：基于动态内存的连续数组,使用原生指针管理数组。
* **成员变量**：
    * `iterator _data_pointer`：指向已分配内存区域的首地址。
    * `iterator _size_pointer`：指向当前数据末尾的下一个位置。
    * `iterator _capacity_pointer`：指向已分配内存容量的末尾。
* **内存布局**：位置连续，存储任意自定义类型的 `vector_type` 对象，符合 `STL`库容器设计规范。

#### 构造与析构

* **默认构造**：`vector() noexcept`，初始化空向量，所有指针为 `nullptr`。
* **容量构造**：`vector(const size_t& container_capacity`, `const vector_type& vector_data = vector_type())`，分配指定容量并初始化所有元素。
* **链式构造**：`vector(std::initializer_list<vector_type> lightweight_container)`，使用初始化列表元素初始化向量。
* **拷贝构造**：`vector(const vector<vector_type>& vector_data)`，深拷贝另一个向量的所有元素。
* **移动构造**：`vector(vector<vector_type>&& vector_data) noexcept`，接管右值资源，避免深拷贝。
* **析构**：释放 `_data_pointer` 指向的内存，防止内存泄漏。

#### 迭代器

* 定义 `iterator`, `const_iterator`, `reverse_iterator`, `const_reverse_iterator`，支持随机访问特性。
* **`begin()`/`end()`** 返回指向 `_data_pointer`, `_size_pointer`位置的迭代器。
* **`rbegin()`/`rend()`** 返回反向迭代器,支持从后往前遍历。
### 访问元素
* `vector_type& operator[](const size_t& access_location)`：直接访问第 `access_location` 个元素，越界时抛异常。
* `const vector_type& operator[](const size_t& access_location) const`：常量版本的下标运算符。
* `front()`/`back()`：访问第一个和最后一个元素，容器非空时有效。
* `head()`/`tail()`：与 `front()`/`back()` 功能相同，提供额外命名方式。
* `find(const size_t& find_size)`：查找指定位置元素，越界时抛异常。
### 容器修改
* #### 追加操作
    * `push_back(const vector_type& vector_type_data)`：末尾添加元素，容量不足时扩容（初始 10，不足时翻倍）。
     * `push_back(vector_type&& vector_type_data)`：移动语义版本的 `push_back`，避免不必要的拷贝。
* #### 头部插入
    * `push_front(const vector_type& vector_type_data)`：头部插入元素，需移动所有现有元素，时间复杂度 `O(n)`。
* #### 删除操作
     * `pop_back()`：移除最后一个元素，不释放内存。
     * `pop_front()`：移除第一个元素，移动所有剩余元素，时间复杂度 `O(n)`。
     * `erase(iterator delete_position)`：删除指定位置元素，返回下一个位置的迭代器。
### 内存管理
* `resize(const size_t& new_container_capacity, const vector_type& vector_data = vector_type())`：调整容量，扩容时用 `vector_data` 填充新增空间。
* `size_adjust(const size_t& data_size, const vector_type& padding_temp_data = vector_type())`：调整大小，支持扩容和缩容。
### 其他修改
* `swap(vector<vector_type>& vector_data) noexcept`：交换两个向量的内容，时间复杂度 `O(1)`。
### 容量与工具方法
* `empty() const noexcept`：判断容器是否为空。
* `size() const noexcept`：返回当前元素数量。
* `capacity() const noexcept`：返回当前分配的容量。
* `operator<<`：支持流式输出，遍历所有元素。
### 运算符重载
* #### 赋值运算符
    * `operator=(const vector<vector_type>& vector_data)`：深拷贝赋值。
    * `operator=(vector<vector_type>&& vector_mobile_data) noexcept`：移动赋值，接管右值资源。
* #### 拼接运算符
    * `operator+=(const vector<vector_type>& vector_data)`：将另一个向量的元素追加到当前向量末尾。
### 复杂度与异常安全
* #### 时间复杂度
  * **随机访问**：`O(1)`
  * **末尾插入** / **删除**：均摊 `O(1)`（扩容时 `O(n)`）
  * **头部** / **中间插入** / **删除**：`O(n)`（移动元素）
  * **扩容**：`O(n)`（复制元素） 
* #### 空间复杂度
  * `O(n)`（存储元素 + 额外容量）
* #### 异常处理
  *  内存分配失败抛 `std::bad_alloc`。
  *  越界操作抛 `custom_exception::customize_exception`。
* #### 迭代器失效
  *  扩容或修改元素时，所有迭代器和引用失效
### 注意事项
* **迭代器安全**：`扩容`或`修改数据`会导致迭代器失效，需重新获取。
* **内存优化**：频繁插入前建议使用 `reserve()` 预分配空间。
* **异常安全**：`插入` / `扩容`操作可能抛异常，建议使用 `try-catch` 处理。
* **移动语义**：优先使用`移动`构造或`移动`赋值，避免不必要的深拷贝。
* **迭代器**：注意当前迭代器未实现封装，导致反向迭代器无法使用，如果想实现的话可以根据链表迭代器类来封装
### **`vector`** 类用法示例

  ```cpp
using namespace template_container;

int main()
{
    // 1. 构造函数示例
    std::cout << "=== 构造函数示例 ===\n";

    // 默认构造
    vector_container::vector<double> v1;
    std::cout << "v1 (默认构造): " << v1 << std::endl;

    // 指定容量构造
    vector_container::vector<double> v2(5, 3.14);
    std::cout << "v2 (指定容量构造): " << v2 << std::endl;

    // 初始化列表构造
    vector_container::vector<std::string> v3 = {"hello", "world", "!"};
    std::cout << "v3 (初始化列表构造): " << v3 << std::endl;

    // 拷贝构造
    vector_container::vector<double> v4(v2);
    std::cout << "v4 (拷贝构造自v2): " << v4 << std::endl;

    // 移动构造
    vector_container::vector<double> v5(std::move(v1));
    std::cout << "v5 (移动构造): " << v5 << std::endl;
    std::cout << "v1 (移动后): " << v1 << std::endl;

    // 2. 访问元素示例
    std::cout << "\n=== 访问元素示例 ===\n";

    // 下标运算符
    std::cout << "v3[0]: " << v3[0] << std::endl;

    // front() 和 back()
    std::cout << "v3.front(): " << v3.front() << std::endl;
    std::cout << "v3.back(): " << v3.back() << std::endl;

    // head() 和 tail()
    std::cout << "v3.head(): " << v3.head() << std::endl;
    std::cout << "v3.tail(): " << v3.tail() << std::endl;

    // find()
    std::cout << "v3.find(1): " << v3.find(1) << std::endl;

    // 3. 容器修改示例
    std::cout << "\n=== 容器修改示例 ===\n";

    // push_back()
    v3.push_back("new");
    std::cout << "v3.push_back(\"new\"): " << v3 << std::endl;

    // push_back() 移动语义
    std::string temp = "moved";
    v3.push_back(std::move(temp));
    std::cout << "v3.push_back(std::move(temp)): " << v3 << std::endl;

    // push_front()
    v3.push_front("start");
    std::cout << "v3.push_front(\"start\"): " << v3 << std::endl;

    // pop_back()
    v3.pop_back();
    std::cout << "v3.pop_back(): " << v3 << std::endl;

    // pop_front()
    v3.pop_front();
    std::cout << "v3.pop_front(): " << v3 << std::endl;

    // erase()
    auto it = v3.begin() + 1;
    v3.erase(it);
    std::cout << "v3.erase(v3.begin() + 1): " << v3 << std::endl;

    // resize()
    v3.resize(10, "default");
    std::cout << "v3.resize(10, \"default\"): " << v3 << std::endl;

    // size_adjust()
    v3.size_adjust(5, "adjusted");
    std::cout << "v3.size_adjust(5, \"adjusted\"): " << v3 << std::endl;


    // swap()
    vector_container::vector<std::string> v6 = {"a", "b", "c"};
    v3.swap(v6);
    std::cout << "v3.swap(v6) 后 v3: " << v3 << std::endl;
    std::cout << "v3.swap(v6) 后 v6: " << v6 << std::endl;

    // 4. 容量与工具方法示例
    std::cout << "\n=== 容量与工具方法示例 ===\n";

    std::cout << "v3.empty(): " << (v3.empty() ? "true" : "false") << std::endl;
    std::cout << "v3.size(): " << v3.size() << std::endl;
    std::cout << "v3.capacity(): " << v3.capacity() << std::endl;

    // 5. 运算符重载示例
    std::cout << "\n=== 运算符重载示例 ===\n";

    // 赋值运算符
    v1 = v4;
    std::cout << "v1 = v4: " << v1 << std::endl;

    // 移动赋值
    v1 = std::move(v4);
    std::cout << "v1 = std::move(v4): " << v1 << std::endl;
    std::cout << "v4 (移动后): " << v4 << std::endl;

    // += 运算符
    v1 += v2;
    std::cout << "v1 += v2: " << v1 << std::endl;

    // 6. 迭代器示例
    std::cout << "\n=== 迭代器示例 ===\n";

    // 正向迭代器
    std::cout << "正向迭代器遍历 v3: ";
    for (auto iterator = v3.begin(); iterator != v3.end(); ++iterator)
    {
        std::cout << *iterator << " ";
    }
    std::cout << std::endl;

    // 反向迭代器
    // std::cout << "反向迭代器遍历 v3: ";
    // for (auto ref_it = v3.rbegin(); ref_it != v3.rend(); --ref_it)
    // {
    //     std::cout << *ref_it << " ";
    // }
    // std::cout << std::endl;

    // 7. 异常处理示例
    std::cout << "\n=== 异常处理示例 ===\n";

    try 
    {
        // 尝试访问越界元素
        std::cout << "尝试访问 v3[10]: ";
        std::cout << v3[10] << std::endl;
    } catch (const custom_exception::customize_exception& e) 
    {
        std::cout << "捕获异常: " << e.what() << " 在 " << e.function_name_get()
                  << " 行 " << e.line_number_get() << std::endl;
    }

    // 8. 内存管理示例
    std::cout << "\n=== 内存管理示例 ===\n";

    // 测试扩容策略
    vector_container::vector<int> v7;
    std::cout << "v7 初始容量: " << v7.capacity() << std::endl;

    for (int i = 0; i < 20; ++i)
    {
        v7.push_back(i);
        if (i % 5 == 0) 
        {
            std::cout << "添加 " << i << " 后容量: " << v7.capacity() << std::endl;
        }
    }

    return 0;

  ```
>**引用**：头文件 `vector_container` 命名空间。
---

## 链表容器
### `list_container`

#### 类概述

`list` 类是一个模板化的双向链表容器，模拟标准库 `std::list` 的核心功能，通过哨兵节点实现统一边界处理，支持常量时间的任意位置插入与删除。


#### **类及其函数定义**

```cpp
namespace list_container 
{
    template <typename list_type>
    class list 
    {
    public:
        // 嵌套节点与迭代器
        template<typename list_type_function_node>
        struct list_container_node;
        template<typename listNodeTypeIterator, typename Ref, typename Ptr>
        class list_iterator;
        template<typename iterator>
        class reverse_list_iterator;

        using container_node = list_container_node<list_type>;
        using iterator = list_iterator<list_type, list_type&, list_type*>;
        using const_iterator = list_iterator<list_type, const list_type&, const list_type*>;
        using reverse_iterator = reverse_list_iterator<iterator>;
        using reverse_const_iterator = reverse_list_iterator<const_iterator>;

        // 构造与析构
        list();
        ~list() noexcept;
        list(iterator first, iterator last);
        list(const_iterator first, const_iterator last);
        list(std::initializer_list<list_type> lightweight_container);
        list(const list<list_type>& list_data);
        list(list<list_type>&& list_data) noexcept;

        // 迭代器接口
        iterator begin() noexcept;
        iterator end() noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;
        reverse_iterator rbegin() noexcept;
        reverse_iterator rend() noexcept;
        reverse_const_iterator rcbegin() const noexcept;
        reverse_const_iterator rcend() const noexcept;

        // 容量与访问
        bool empty() const noexcept;
        size_t size() const noexcept;
        list_type& front() noexcept;
        const list_type& front() const noexcept;
        list_type& back() noexcept;
        const list_type& back() const noexcept;

        // 插入/删除操作
        void push_back(const list_type& data);
        void push_back(list_type&& data);
        void push_front(const list_type& data);
        void push_front(list_type&& data);
        void pop_back();
        iterator pop_front();
        iterator insert(iterator pos, const list_type& data);
        iterator insert(iterator pos, list_type&& data);
        iterator erase(iterator pos);

        // 调整与管理
        void resize(const size_t new_container_size, const list_type& data = list_type());
        void clear() noexcept;
        void swap(list<list_type>& swap_target) noexcept;

        // 运算符重载
        list<list_type>& operator=(list<list_type> list_data) noexcept;
        list<list_type>& operator=(std::initializer_list<list_type> lightweight_container);
        list<list_type>& operator=(list<list_type>&& list_data) noexcept;
        list<list_type> operator+(const list<list_type>& list_data);
        list<list_type>& operator+=(const list<list_type>& list_data);

        template <typename const_list_output_templates>
        friend std::ostream& operator<< (std::ostream& os, const list<const_list_output_templates>& lst);
    };

    template <typename const_list_output_templates>
    std::ostream& operator<< (std::ostream& os, const list<const_list_output_templates>& lst);
}
```

---

#### **作用描述**

* **构造与析构**：

    * `list() noexcept`：初始化空链表，创建哨兵节点，`_head->next` 和 `_head->prev` 指向自身。
    * `list(iterator first, iterator last)`：从区间 `[first, last)` 拷贝或移动元素构造链表。
    * `list(std::initializer_list<list_type> init)`：接受初始化列表，按顺序插入元素。
    * 拷贝/移动构造：分别实现深拷贝或接管资源，确保原对象处于有效或空状态。
    * 析构 `~list()`：清空节点并释放哨兵。

* **迭代器接口**：

    * `begin()/end()`：返回指向首元素的正向迭代器和哨兵节点。
    * `rbegin()/rend()`：基于正向迭代器封装，实现反向遍历。

* **容量与访问**：

    * `empty()/size()`：检测是否无元素和返回元素数量。
    * `front()/back()`：访问首尾元素，调用者需保证非空。

* **修改操作**：

    * `push_back/push_front`：在尾部或头部插入，常量时间。
    * `insert/erase(iterator)`：在指定位置插入或删除节点，无需移动其他节点。
    * `pop_back/pop_front`：删除尾部或头部元素。
    * `resize`：根据目标大小增删节点。
    * `clear`：释放所有数据节点，保留哨兵。
    * `swap`：交换两链表头指针，时间 O(1)。

* **运算符重载**：

    * 赋值、合并（`+`/`+=`）、流式输出，提供直观便捷的接口。


#### **返回值说明**

* `size()` → 返回 `size_t`：链表中元素数量，始终非负。
* `empty()` → 返回 `bool`：链表是否为空。
* `begin()/end()` → 返回 `iterator`：正向遍历的起始和终止位置。
* `push_back`/`push_front` → 返回 `void`：在尾部/头部插入元素，可能抛 `std::bad_alloc`。
* `insert(pos, value)` → 返回 `iterator`：指向新插入节点的位置，传入空或非法迭代器时抛 `custom_exception`。
* `erase(pos)` → 返回 `iterator`：指向被删除节点的下一个位置，传入空或非法迭代器时抛 `custom_exception`。
* `front()/back()` → 返回引用(`list_type&` 或 `const list_type&`)：访问首/尾元素，空表时调用未定义行为。
* `swap(other)` → 返回 `void`：交换两链表内容，无异常。

#### **内部数据结构**

* **节点结构 (`list_container_node`)**：

    * `_prev`：指向前驱节点。
    * `_next`：指向后继节点。
    * `_data`：存储用户数据。
* **哨兵节点 (`_head`)**：

    * 不存储有效数据，用于统一边界处理。
    * 初始时 `_head->_prev` 和 `_head->_next` 均指向自身。
* **内存布局**：

    * 链表通过动态 `new/delete` 分配节点。
    * 所有节点通过双向指针连接，形成循环结构。

#### **构造与析构**

* **默认构造**：`list() noexcept`，创建哨兵节点，初始化空表状态。
* **范围构造**：`list(iterator first, iterator last)` / `list(const_iterator first, const_iterator last)`，从区间复制或移动元素。
* **初始化列表构造**：`list(std::initializer_list<list_type> init)`，按顺序插入列表元素。
* **拷贝构造**：`list(const list& other)`，深拷贝所有节点数据。
* **移动构造**：`list(list&& other) noexcept`，接管原链表头指针，置空源对象。
* **析构**：`~list() noexcept`，调用 `clear()` 释放所有数据节点，然后释放哨兵。


#### **迭代器**

* **定义**：

    * `iterator` / `const_iterator`：支持 `operator++`, `operator--`, `operator*`, `operator->`, `operator!=`。
    * `reverse_iterator` / `reverse_const_iterator`：基于正向迭代器封装，反向遍历。
* **用法**：

    * `begin()` / `cbegin()`：指向首元素的迭代器。
    * `end()` / `cend()`：指向哨兵节点。
    * `rbegin()` / `rcbegin()`：指向尾元素。
    * `rend()` / `rcend()`：指向哨兵节点。



#### **元素访问**

* **`empty()`**：检查链表是否为空（仅哨兵）。
* **`size()`**：遍历计数后返回元素数量。
* **`front()`** / **`back()`**：返回头/尾节点的数据引用，常量和非常量版本。



#### **修改操作**

* **尾部插入**：

    * `push_back(const list_type& value)` / `push_back(list_type&& value)`，在哨兵前插入节点。
* **头部插入**：

    * `push_front(const list_type& value)` / `push_front(list_type&& value)`，在哨兵后插入节点。
* **插入指定位置**：

    * `insert(iterator pos, const list_type& value)` / `insert(iterator pos, list_type&& value)`，在 `pos` 前插入。
* **删除操作**：

    * `pop_back()`：删除尾节点。
    * `pop_front()`：删除头节点，返回下一个位置迭代器。
    * `erase(iterator pos)`：删除 `pos` 指向节点并返回下一个节点迭代器。



#### **内存管理 & swap**

* **调整大小**：

    * `resize(size_t count, const list_type& value = list_type())`，根据 `count` 增删节点。
* **清理资源**：

    * `clear() noexcept`，循环删除所有数据节点，保留哨兵。
* **交换**：

    * `swap(list& other) noexcept`，交换两个链表的哨兵指针。


#### **复杂度分析**

* `empty()`：`O(1)`，直接检查哨兵指针。
* `size()`：`O(n)`，遍历整个链表统计元素（可通过缓存优化至 `O(1)`）。
* `push_back()/push_front()`：`O(1)`，在哨兵相邻位置插入新节点。
* `insert()/erase()`：`O(1)`，在已知节点位置常量时间操作。
* `clear()`：`O(n)`，释放所有数据节点。
* `operator+`：`O(n + m)`，合并两个链表时遍历所有元素。

#### **边界条件和错误处理**

* **空表操作**：`front()/back()` 前应检查 `empty()`；否则行为未定义。
* **迭代器有效性**：`insert` 与 `erase` 参数必须指向同一链表且非哨兵空指针。
* **内存分配失败**：插入时抛 `std::bad_alloc`，建议在高层捕获。
* **自定义异常**：传入空迭代器或非法区间时抛 `custom_exception::customize_exception`。

---

#### **注意事项**

* **迭代器失效规则**：链表插入/删除仅失效目标位置的迭代器，其他迭代器保持有效。
* **异常安全**：插入失败时保证链表状态不变（强异常保证）。
* **多线程安全**：非线程安全，需外部同步锁。
* **性能优化**：频繁 `size()` 可缓存；可扩展 `reserve` 模式减少节点分配。
#### **使用示例**

```cpp
using namespace list_container;

int main()
{
    // 1. 构造函数示例
    std::cout << "=== 构造函数示例 ===\n";

    // 默认构造
    list_container::list<int> l1;
    std::cout << "l1 (默认构造): " << l1 << std::endl;

    // 初始化列表构造
    list_container::list<std::string> l2 = {"hello", "world", "!"};
    std::cout << "l2 (初始化列表构造): " << l2 << std::endl;

    // 拷贝构造
    list_container::list<std::string> l3(l2);
    std::cout << "l3 (拷贝构造): " << l3 << std::endl;

    // 2. 插入操作示例
    std::cout << "\n=== 插入操作示例 ===\n";

    l1.push_back(10);
    l1.push_back(20);
    l1.push_front(5);
    std::cout << "l1 插入后: " << l1 << std::endl;

    // 指定位置插入
    auto it = l1.begin();
    ++it;  // 指向第二个元素
    l1.insert(it, 15);
    std::cout << "l1 插入中间: " << l1 << std::endl;

    // 3. 删除操作示例
    std::cout << "\n=== 删除操作示例 ===\n";

    l1.pop_back();
    std::cout << "l1 删除尾部: " << l1 << std::endl;

    l1.pop_front();
    std::cout << "l1 删除头部: " << l1 << std::endl;

    it = l1.begin();
    l1.erase(it);
    std::cout << "l1 删除中间: " << l1 << std::endl;

    // 4. 迭代器遍历示例
    std::cout << "\n=== 迭代器遍历示例 ===\n";

    std::cout << "正向遍历 l2: ";
    for (auto list_iterator = l2.begin(); list_iterator != l2.end(); ++list_iterator) {
        std::cout << *list_iterator << " ";
    }
    std::cout << std::endl;

    std::cout << "反向遍历 l2: ";
    for (auto reverse_list_iterator = l2.rbegin(); reverse_list_iterator != l2.rend(); ++reverse_list_iterator) {
        std::cout << *reverse_list_iterator << " ";
    }
    std::cout << std::endl;

    // 5. 其他操作示例
    std::cout << "\n=== 其他操作示例 ===\n";

    std::cout << "l2 size: " << l2.size() << std::endl;
    std::cout << "l2 empty: " << (l2.empty() ? "true" : "false") << std::endl;

    l2.resize(5, "default");
    std::cout << "l2 resize: " << l2 << std::endl;

    // 6. 运算符重载示例
    std::cout << "\n=== 运算符重载示例 ===\n";

    list_container::list<std::string> l4 = {"a", "b"};
    l4 += l2;
    std::cout << "l4 += l2: " << l4 << std::endl;

    list_container::list<std::string> l5 = l4 + l2;
    std::cout << "l5 = l4 + l2: " << l5 << std::endl;

    return 0;
}
```


>**引用**：头文件 `list_container` 命名空间。

---

## 栈适配器

### `stack_adapter::stack`
### 类概述
* `stack` 类是一个基于向量容器的栈适配器，采用适配器设计模式实现。
通过模板参数 `stack_type` 支持任意数据类型，并可指定底层容器类型（默认为 `template_container::vector_container::vector`）。
该类将向量的接口转换为栈的后进先出`（LIFO）`接口，提供了标准栈的所有核心操作。
#### **类及其函数定义**

```cpp
namespace stack_adapter 
{
    template <typename stack_type,typename vector_based_stack = template_container::vector_container::vector<stack_type>>
    class stack 
    {
    private:
        vector_based_stack vector_object;
    public:
        stack() = default;
        ~stack();

        // 构造与赋值
        explicit stack(const stack<stack_type>& stack_data);
        explicit stack(stack<stack_type>&& stack_data) noexcept;
        stack(std::initializer_list<stack_type> stack_type_data);
        explicit stack(const stack_type& stack_type_data);
        stack& operator=(const stack<stack_type>& stack_data);
        stack& operator=(stack<stack_type>&& stack_data) noexcept;

        // 栈操作
        void push(const stack_type& stack_type_data);
        void push(stack_type&& stack_type_data);
        void pop();
        [[nodiscard]] stack_type& top() const noexcept;
        [[nodiscard]] bool empty() const noexcept;
        size_t size() noexcept;
        stack_type& footer() noexcept;
    };
}
```

---

#### **作用描述**

* `push(const stack_type&)` / `push(stack_type&&)`：向栈顶添加元素。前者拷贝语义，后者移动语义。
* `pop()`：移除栈顶元素，调用底层容器的 `pop_back()`。
* `top() const`：返回栈顶元素的引用，通过底层容器的 `back()` 获取。
* `empty() const`：检查栈是否为空，底层调用 `vector.empty()`。
* `size()`：返回栈中元素数量，底层调用 `vector.size()`。
* `footer()`：与 `top()` 相同，返回栈顶元素引用。
* 构造/赋值：

    * 拷贝构造与拷贝赋值：深拷贝底层容器。
    * 移动构造与移动赋值：接管底层容器资源。
    * 初始化列表构造：按顺序将列表值 `push_back` 至栈中。
    * 单值构造：将单个元素 `push_back`。


#### **返回值说明**

* `push(...)` → `void`：无返回，可能抛 `std::bad_alloc`。
* `pop()` → `void`：无返回，调用前应保证非空。
* `top()` / `footer()` → `stack_type&`：栈顶元素引用，栈空时行为未定义。
* `empty()` → `bool`：栈是否为空。
* `size()` → `size_t`：当前元素数量。
* 构造/赋值函数 → 返回对象引用或构造新实例，可能抛 `std::bad_alloc` 或 `custom_exception`。

#### **内部原理剖析**

* 适配器模式：封装底层 `vector_container::vector`，利用其 `push_back`/`pop_back`/`back` 实现栈行为。
* 栈顶对应底层容器末尾。
* 所有操作委托给底层容器，简化实现。


#### **复杂度分析**

* `push` / `pop` / `top` / `footer` / `empty` / `size`：均为底层 `vector` 的 `O(1)` 均摊时间。
* 构造与赋值：深拷贝为 `O(n)`，移动为 `O(1)`。


#### **边界条件和错误处理**

* `top()` / `pop()` 在空栈上调用行为未定义，需先检查 `empty()`。
* 元素插入若底层扩容失败，会抛 `std::bad_alloc`。


#### **注意事项**

* 非线程安全：多线程访问需加锁。
* 异常安全：`push` 失败时无副作用，保持旧状态。
* 迭代器不可用：适配器未提供迭代接口，只能通过 `pop`/`top` 访问元素。
### **使用示例**

```cpp
using namespace template_container;

int main()
{
    // 1. 构造函数示例
    std::cout << "=== 构造函数示例 ===\n";

    // 默认构造
    stack_adapter::stack<int> s1;
    std::cout << "s1 (默认构造，空栈): size=" << s1.size() << std::endl;

    // 元素构造
    stack_adapter::stack<double> s2(3.14);
    std::cout << "s2 (元素构造): top=" << s2.top() << std::endl;

    // 初始化列表构造
    stack_adapter::stack<std::string> s3 = {"hello", "world"};
    std::cout << "s3 (初始化列表构造): ";
    while ( !s3.empty() ) 
    {
        std::cout << s3.top() << " ";
        s3.pop();
    }
    std::cout << std::endl;

    // 2. 栈操作示例
    std::cout << "\n=== 栈操作示例 ===\n";

    stack_adapter::stack<int> s4;
    s4.push(10);
    s4.push(20);
    s4.push(30);

    std::cout << "s4 压栈后 size=" << s4.size() << ", top=" << s4.top() << std::endl;

    s4.pop();
    std::cout << "s4 弹栈后 size=" << s4.size() << ", top=" << s4.top() << std::endl;

    // 3. 拷贝与移动示例
    std::cout << "\n=== 拷贝与移动示例 ===\n";

    // 拷贝构造
    stack_adapter::stack<int> s5(s4);
    std::cout << "s5 (拷贝构造自 s4): top=" << s5.top() << std::endl;

    // 移动构造
    stack_adapter::stack<int> s6(std::move(s5));
    std::cout << "s6 (移动构造自 s5): top=" << s6.top() << ", s5 size=" << s5.size() << std::endl;

    return 0;
}
```
>**引用**：头文件 `stack_adapter` 命名空间。
---

## 队列适配器
## 队列
### `queue_adapter::queue`
### 类概述
* `queue` 类是一个基于双向链表的队列适配器，
采用先进先出`（FIFO）`的操作方式。通过模板参数 `queue_type` 支持任意数据类型，
并可指定底层容器类型（默认为 `template_container::list_container::list`）。该类将链表的接口转换为队列的标准接口，提供了队列的所有核心操作。
#### **类及其函数定义**

```cpp
namespace queue_adapter 
{
    template <typename queue_type,typename list_based_queue = template_container::list_container::list<queue_type>>
    class queue 
    {
    private:
        list_based_queue list_object;
    public:
        queue() = default;
        ~queue();

        // 构造与赋值
        explicit queue(const queue& queue_data);
        explicit queue(queue&& queue_data) noexcept;
        queue(std::initializer_list<queue_type> list_data);
        explicit queue(const queue_type& single_data);
        queue& operator=(const queue& queue_data);
        queue& operator=(queue&& queue_data) noexcept;

        // 核心操作
        void push(const queue_type& data);
        void push(queue_type&& data);
        void pop();
        [[nodiscard]] queue_type& front() noexcept;
        [[nodiscard]] queue_type& back() noexcept;
        [[nodiscard]] size_t size() const noexcept;
        [[nodiscard]] bool empty() const noexcept;
    };
}
```

#### **作用描述**

* **模板参数**：`queue_type` 为元素类型；`list_based_queue` 为底层双向链表类型。
* **push**：将元素追加到队尾，支持拷贝与移动语义。
* **pop**：移除队首元素。
* **front/back**：返回队首/队尾元素的引用。
* **empty/size**：获取队列状态和元素数量。
* **构造/赋值**：支持拷贝、移动、初始化列表和单值构造。

#### **返回值说明**

* `push`/`pop` → `void`：无返回，`push` 可能抛 `std::bad_alloc`。
* `front()/back()` → `queue_type&`：返回元素引用，空队列调用行为未定义。
* `empty()` → `bool`：是否为空。
* `size()` → `size_t`：元素数量。
* 构造/赋值 → 返回实例或对象引用，异常安全需依赖底层链表。

#### **内部原理剖析**

* 基于自定义双向链表：节点通过 `_prev`/`_next` 链接。
* `push` 在尾部插入新节点，`pop` 在头部删除节点，均为 O(1)。
* 利用哨兵节点简化边界操作。

#### **复杂度分析**

* `push`, `pop`, `front`, `back`, `empty`, `size`：O(1)。
* 构造（初始化列表）: O(n)。

#### **边界条件和错误处理**

* 操作前应调用 `empty()` 检查空队列。
* 底层分配失败抛 `std::bad_alloc`。

#### **注意事项**

* 非线程安全。
* 无迭代接口。

#### **使用示例**

```cpp
using namespace  template_container;
int main()
{
    // 1. 构造函数示例
    std::cout << "=== 构造函数示例 ===\n";

    // 默认构造
    queue_adapter::queue<int> q1;
    std::cout << "q1 (默认构造，空队列): size=" << q1.size() << std::endl;

    // 元素构造
    queue_adapter::queue<double> q2(3.14);
    std::cout << "q2 (元素构造): front=" << q2.front() << std::endl;

    // 初始化列表构造
    queue_adapter::queue<std::string> q3 = {"hello", "world"};
    std::cout << "q3 (初始化列表构造): ";
    while (!q3.empty())
    {
        std::cout << q3.front() << " ";
        q3.pop();
    }
    std::cout << std::endl;

    // 2. 队列操作示例
    std::cout << "\n=== 队列操作示例 ===\n";

    queue_adapter::queue<int> q4;
    q4.push(10);
    q4.push(20);
    q4.push(30);

    std::cout << "q4 入队后: front=" << q4.front() << ", back=" << q4.back() << std::endl;

    q4.pop();
    std::cout << "q4 出队后: front=" << q4.front() << ", size=" << q4.size() << std::endl;

    // 3. 拷贝与移动示例
    std::cout << "\n=== 拷贝与移动示例 ===\n";

    // 拷贝构造
    queue_adapter::queue<int> q5(q4);
    std::cout << "q5 (拷贝构造自 q4): front=" << q5.front() << std::endl;

    // 移动构造
    queue_adapter::queue<int> q6(std::move(q5));
    std::cout << "q6 (移动构造自 q5): front=" << q6.front() << ", q5 empty=" << q5.empty() << std::endl;

    return 0;
}
```
> **引用**： 头文件 `queue_adapter` 命名空间
---
### 优先级队列
### `queue_adapter::priority_queue`

#### **类及其函数定义**

```cpp
namespace queue_adapter 
{
    template <typename priority_queue_type,typename compare = template_container::imitation_functions::less<priority_queue_type>,
    typename vector_based_priority_queue = template_container::vector_container::vector<priority_queue_type>>
    class priority_queue 
    {
    private:
        vector_based_priority_queue data;
        compare comp;
        void adjust_up(int idx) noexcept;
        void adjust_down(int idx = 0) noexcept;
    public:
        priority_queue() = default;
        ~priority_queue() noexcept;
        priority_queue(std::initializer_list<priority_queue_type> init);
        priority_queue(const priority_queue& other);
        priority_queue(priority_queue&& other) noexcept;
        explicit priority_queue(const priority_queue_type& single);
        priority_queue& operator=(const priority_queue& other);
        priority_queue& operator=(priority_queue&& other) noexcept;

        // 核心操作
        void push(const priority_queue_type& value);
        [[nodiscard]] priority_queue_type& top() noexcept;
        void pop();
        [[nodiscard]] size_t size() const noexcept;
        [[nodiscard]] bool empty() const noexcept;
    };
}
```

#### **作用描述**

* **模板参数**：`priority_queue_type` 为元素类型；`compare` 为排序仿函数。
* **push**：末尾插入后调用 `adjust_up` 恢复堆序。
* **top**：返回堆顶元素引用。
* **pop**：交换堆顶与尾部元素，删除尾部并 `adjust_down`。
* **empty/size**：获取堆状态和大小。
* **构造/赋值**：支持初始化列表、拷贝和移动语义。

#### **返回值说明**

* `push`/`pop` → `void`：`push` 可能抛 `std::bad_alloc`。
* `top()` → `priority_queue_type&`：返回元素引用，空堆调用未定义。
* `empty()` → `bool`。
* `size()` → `size_t`。

#### **内部原理剖析**

* 基于动态数组（`vector`）：

    * 栈顶对应 `data[0]`。
    * **向上调整**：比较子与父，必要时交换。
    * **向下调整**：比较父与子，交换以维护堆序。
    * 紧耦合 `comp` 仿函数，可配大顶/小顶堆。

#### **复杂度分析**

* `push`, `pop`：`O(log n)`。
* `top`, `empty`, `size`：`O(1)`。
* 构造（初始化列表）：`O(n log n)`。
* 拷贝/移动构造：`O(n)`/`O(1)`。

#### **边界条件和错误处理**

* 操作前检查 `empty()`。
* 分配失败抛 `std::bad_alloc`。
* 确保 `compare` 满足弱排序。

#### **注意事项**

* 非线程安全。
* 无迭代接口。

#### **使用示例**

```cpp
using namespace template_container;
int main() 
{
    // 1. 构造函数示例
    std::cout << "=== 构造函数示例 ===\n";
    
    // 默认构造（大顶堆）
    queue_adapter::priority_queue<int> pq1;
    std::cout << "pq1 (默认构造，空队列): size=" << pq1.size() << std::endl;
    
    // 初始化列表构造
    queue_adapter::priority_queue<int> pq2 = {3, 1, 4, 1, 5, 9};
    std::cout << "pq2 (初始化列表构造): top=" << pq2.top() << std::endl;
    
    // 2. 优先队列操作示例
    std::cout << std::endl << "=== 优先队列操作示例 ===" <<std::endl;

    
    pq1.push(10);
    pq1.push(20);
    pq1.push(15);
    
    std::cout << "pq1 入队后: top=" << pq1.top() << std::endl;
    
    pq1.pop();
    std::cout << "pq1 出队后: top=" << pq1.top() << std::endl;
    
    // 3. 自定义比较器示例（小顶堆）
    std::cout << "\n=== 自定义比较器示例 ===\n";
    
    using MinHeap = queue_adapter::priority_queue<int, 
        template_container::imitation_functions::greater<int>>;
    
    MinHeap minHeap;
    minHeap.push(5);
    minHeap.push(3);
    minHeap.push(7);
    
    std::cout << "小顶堆: top=" << minHeap.top() << std::endl;
    
    return 0;
}
```
> **引用**：头文件 `queue_adapter` 命名空间
---
## 树容器 `tree_container`

### 二叉搜索树

### `binary_search_tree`
* **概述**：`binary_search_tree` 类是一个模板化的二叉搜索树实现，支持任意数据类型和自定义比较策略。
二叉搜索树是一种有序数据结构，具有以下性质：左子树所有节点值小于根节点，右子树所有节点值大于根节点。
该类实现了树的插入、删除、查找和遍历等核心操作，并提供了拷贝构造、移动语义等高级功能。

#### **类及其函数定义**

```cpp
template <typename binary_search_tree_type,
    typename container_imitate_function = template_container::imitation_functions::less<binary_search_tree_type>>
class binary_search_tree 
{
private:
    class binary_search_tree_type_node 
    {
    public:
        binary_search_tree_type_node* _left;
        binary_search_tree_type_node* _right;
        binary_search_tree_type _data;
        explicit binary_search_tree_type_node(const binary_search_tree_type& val = binary_search_tree_type());
        ~binary_search_tree_type_node();
    };

    using container_node = binary_search_tree_type_node;
    container_node* _root;
    container_imitate_function function_policy;

    // 内部遍历与辅助
    void interior_middle_order_traversal(container_node* node);
    size_t interior_middle_order_traversal(container_node* node, size_t& counter);
    void interior_pre_order_traversal(container_node* node);
    void clear() noexcept;

public:
    // 构造与析构
    binary_search_tree() = default;
    explicit binary_search_tree(const binary_search_tree_type& val);
    binary_search_tree(std::initializer_list<binary_search_tree_type> init);
    binary_search_tree(const binary_search_tree& other);
    binary_search_tree(binary_search_tree&& other) noexcept;
    ~binary_search_tree() noexcept;

    // 核心操作
    bool push(const binary_search_tree_type& val);
    binary_search_tree& pop(const binary_search_tree_type& val);
    container_node* find(const binary_search_tree_type& val);
    void insert(const binary_search_tree_type& existing, const binary_search_tree_type& new_val);

    // 信息查询
    size_t size();
    [[nodiscard]] size_t size() const;

    // 遍历接口
    void middle_order_traversal();
    void pre_order_traversal();

    // 赋值运算符
    binary_search_tree& operator=(const binary_search_tree& other);
    binary_search_tree& operator=(binary_search_tree&& other) noexcept;
};
```

---

#### **作用描述**

* **模板参数**：

  * `binary_search_tree_type`：节点存储的数据类型。
  * `container_imitate_function`：用于比较节点值的仿函数（默认 `less<T>`）。
* **`push(val)`**：向树中插入新节点；若根为空则新建根，否则根据比较函数向左或右子树递归定位。
* **`pop(val)`**：删除具有指定值的节点，分三种情况：

  1. **无左子**：替换为右子树。
  2. **无右子**：替换为左子树。
  3. **双子**：找到右子树最小节点，与待删节点数据交换，再删除该最小节点。
* **`find(val)`**：在树中查找值等于 `val` 的节点，返回指向该节点的指针或 `nullptr`。
* **`insert(existing, new_val)`**：在已有节点后作为其右子树插入新节点。
* **遍历**：

  * `middle_order_traversal()`：非递归中序。
  * `pre_order_traversal()`：非递归前序。
* **`size()`**：通过中序遍历计数节点总数；常量/非常量版本。
* **`clear()`**：非递归释放所有节点。
* **赋值运算符**：支持深拷贝和移动赋值，清理旧树后接管或复制节点。


#### **返回值说明**

* `push` → `bool`：插入成功返回 `true`，遇到重复元素返回 `false`。
* `pop` → `binary_search_tree&`：操作完成后返回自身引用。
* `find` → `container_node*`：指向找到的节点或 `nullptr`。
* `size()` → `size_t`：返回当前节点总数。
* 遍历/clear → `void`。
* 构造/赋值 → 实例化或赋值，无返回。


#### **内部原理剖析**

* **节点结构**：`_left`、`_right` 双向指针与数据 `_data`。
* **插入**：从根开始，使用 `function_policy` 决定向左或向右，直到空位置。
* **删除**：三种子树情况处理，并使用 `swap` 数据简化双子删除。
* **非递归遍历**：利用自定义 `stack_adapter::stack<container_node*>` 实现中序和前序遍历。
* **清理**：同样利用栈做后序释放，防止递归栈溢。


#### **复杂度分析**

* 平均情况下，操作（`push`/`pop`/`find`）时间为 `O(log n)`；最坏为退化为链表 `O(n)`。
* `size()`：`O(n)` 遍历所有节点。
* 遍历/`clear`：`O(n)`。
* 空间：`O(n)`（存储节点）+ `O(h)`额外栈空间，`h` 为树高。


#### **边界条件和错误处理**

* **空树**：在根为空时 `push` 会创建根节点；`pop`/`find` 返回空或保持无变化。
* **重复元素**：`push` 返回 `false` 而不插入。
* **内存分配失败**：抛 `std::bad_alloc`。
* **仿函数要求**：`container_imitate_function` 应提供严格弱序。


#### **注意事项**

* 非线程安全，需外部同步。
* 对深度大或不平衡树，递归遍历易栈溢，故使用显式栈。
* `pop` 删除后，外部持有的节点指针可能失效。

#### **使用示例**

```cpp
using namespace template_container::tree_container;
int main() 
{
    // 1. 构造二叉搜索树
    binary_search_tree<int> bst = {5, 3, 7, 2, 4, 6, 8};
    
    std::cout << "中序遍历: ";
    bst.middle_order_traversal();  // 输出: 2 3 4 5 6 7 8
    std::cout << "\n前序遍历: ";
    bst.pre_order_traversal();   // 输出: 5 3 2 4 7 6 8
    std::cout << "\n树大小: " << bst.size() << std::endl;  // 输出: 7
    
    // 2. 插入节点
    bst.push(9);
    std::cout << "插入9后中序遍历: ";
    bst.middle_order_traversal();  // 输出: 2 3 4 5 6 7 8 9
    
    // 3. 删除节点
    bst.pop(3);
    std::cout << "删除3后中序遍历: ";
    bst.middle_order_traversal();  // 输出: 2 4 5 6 7 8 9
    
    // 4. 查找节点
    auto node = bst.find(6);
    if (node) 
    {
        std::cout << "\n找到节点: " << node->_data << std::endl;
    }
    
    // 5. 拷贝构造
    binary_search_tree<int> bst_copy = bst;
    std::cout << "拷贝树中序遍历: ";
    bst_copy.middle_order_traversal();
    
    return 0;
}
```
> **引用**： 头文件 `tree_container` 命名空间

---
### AVL树
### `avl_tree`
### 类概述
* `avl_tree` 类是一个模板化的平衡二叉搜索树实现（`AVL` 树），支持键值对存储和自动平衡功能。`AVL` 树通过旋转操作保持平衡性质：任意节点的左右子树高度差不超过 1，确保了插入、删除和查找操作的平均时间复杂度为 `O (log n)`。该类实现了完整的迭代器系统、平衡旋转算法和异常处理机制。

#### **类及其函数定义**

```cpp
template <typename avl_tree_type_k,typename avl_tree_type_v,
          typename container_imitate_function = template_container::imitation_functions::less<avl_tree_type_k>,
          typename avl_tree_node_pair = template_container::practicality::pair<avl_tree_type_k,avl_tree_type_v>>
class avl_tree 
{
private:
    class avl_tree_type_node 
    {
    public:
        avl_tree_node_pair _data;               // 键值对数据
        avl_tree_type_node* _left;              // 左子树指针
        avl_tree_type_node* _right;             // 右子树指针
        avl_tree_type_node* _parent;            // 父节点指针
        int _balance_factor;                    // 平衡因子：右子高 - 左子高

        explicit avl_tree_type_node(const avl_tree_type_k& key = avl_tree_type_k(),const avl_tree_type_v& val = avl_tree_type_v());
        explicit avl_tree_type_node(const avl_tree_node_pair& pair_data);
    };

    using container_node = avl_tree_type_node;
    container_node* _root;                      // 树根
    container_imitate_function function_policy;  // 键比较策略

    // 旋转操作
    void left_revolve(container_node*& subtree);
    void right_revolve(container_node*& subtree);
    void left_right_revolve(container_node*& subtree);
    void right_left_revolve(container_node*& subtree);

    // 插入与删除辅助
    bool insert_node(container_node*& subtree, container_node* parent, const avl_tree_node_pair& pr);
    container_node* remove_node(container_node*& subtree, const avl_tree_type_k& key, bool& erased);

    // 非递归遍历
    void interior_pre_order_traversal(container_node* start);
    void interior_middle_order_traversal(container_node* start);

    // 资源清理
    void clear_tree(container_node* node) noexcept;

public:
    using iterator = avl_tree_iterator<avl_tree_node_pair, avl_tree_node_pair&, avl_tree_node_pair*>;
    using const_iterator = avl_tree_iterator<avl_tree_node_pair, const avl_tree_node_pair&, const avl_tree_node_pair*>;
    using reverse_iterator = avl_tree_reverse_iterator<iterator>;
    using const_reverse_iterator = avl_tree_reverse_iterator<const_iterator>;

    // 构造与析构
    avl_tree();  // 空树
    explicit avl_tree(const avl_tree_node_pair& pr, container_imitate_function comp = container_imitate_function());
    avl_tree(const avl_tree_type_k& key, const avl_tree_type_v& val = avl_tree_type_v(), container_imitate_function comp = container_imitate_function());
    avl_tree(std::initializer_list<avl_tree_node_pair> init, container_imitate_function comp = container_imitate_function());
    avl_tree(const avl_tree& other);  // 深拷贝
    avl_tree(avl_tree&& other) noexcept;  // 移动
    ~avl_tree() noexcept;

    // 核心操作
    bool push(const avl_tree_node_pair& pr);  // 插入键值对
    bool push(const avl_tree_type_k& key, const avl_tree_type_v& val = avl_tree_type_v());
    bool pop(const avl_tree_type_k& key);   // 删除指定键
    avl_tree_node_pair* find(const avl_tree_type_k& key);  // 查找

    // 信息查询
    [[nodiscard]] size_t size() const;  // 总节点数
    [[nodiscard]] bool empty() const;   // 是否为空

    // 遍历
    iterator begin();  // 中序首
    iterator end();    // 中序尾
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    // 赋值运算符
    avl_tree& operator=(const avl_tree& other);
    avl_tree& operator=(avl_tree&& other) noexcept;
};
```

#### **作用描述**
**模板参数**
* `avl_tree_type_k`：键的类型（用于排序和查找）
* `avl_tree_type_v`：值的类型（与键关联的数据）
* `container_imitate_function`：键的比较器（默认：`less<avl_tree_type_k>`）
* `avl_tree_node_pair`：键值对类型（默认：`pair<avl_tree_type_k, avl_tree_type_v>`）

 **构造与析构**

   * **空构造**：`avl_tree()` 初始化 `_root=nullptr`，无内存分配。
   * **键值对构造**：`avl_tree(pr)` 在空树创建根节点，`_balance_factor=0`。
   * **键/值构造**：`avl_tree(key,val)` 同上，可指定初始键值。
   * **初始化列表**：依次调用 `push` 对每个元素执行插入并自动平衡。
   * **拷贝构造**：递归或显式栈深拷贝所有节点与平衡因子。
   * **移动构造**：直接接管 `other._root` 与 `other.function_policy`，清空源。
   * **析构**：调用 `clear_tree(_root)` 释放所有节点。

**插入 (`push`)**

   * **查重**：若在定位过程中遇 `comp(a,b)==false && comp(b,a)==false` 则为重复，返回 `false`。
   * **节点创建**：新节点 `_balance_factor=0`，父指针指向插入位置。
   * **回溯更新**：从插入节点沿父链向上更新 `_balance_factor`：右插增+1，左插减-1。
   * **失衡检测**：当因子绝对值>1，识别为 LL/RR/LR/RL 失衡并调用相应旋转：

     * **LL**：`right_revolve`
     * **RR**：`left_revolve`
     * **LR**：`left_revolve(left child)` 后 `right_revolve`
     * **RL**：`right_revolve(right child)` 后 `left_revolve`
   * **因子修正**：旋转后子树高度恢复，更新相关因子。

 **删除 (`pop`)**

   * **定位**：类似 `find` 查找节点。
   * **三种删除情况**：

     1. **叶节点**：直接删除并将父链接置 `nullptr`。
     2. **单子**：用唯一子节点替代被删除节点。
     3. **双子**：查找右子树最左（中序后继），交换数据并删除该后继。
   * **回溯平衡**：从删除点父节点起向上更新因子并执行旋转。

 **查找 (`find`)**

   * 自 `_root` 比较 `key` 与 `node->_data.first`，左滑或右滑直至命中或 `nullptr`。

 **查询 (`size`/`empty`)**

   * `empty()`：`O(1)` 检查 `_root==nullptr`。
   * `size()`：`O(n)` 通过 `_size()` 递归或迭代统计。

 **遍历接口**

   * **中序**：`begin()`、`end()` 生成正序迭代器，内部调 `interior_middle_order_traversal`。
   * **逆序**：`rbegin()`、`rend()` 生成反向迭代器。
   * **前序**：`interior_pre_order_traversal` 用于序列化或打印调试。

#### **返回值说明**

* `push(...)` → `bool`：成功插入并平衡返回 `true`；重复键返回 `false`。
* `pop(key)` → `bool`：存在则删除并返回 `true`；不存在返回 `false`。
* `find(key)` → `Pair*`：命中返回指针；未命中返回 `nullptr`。
* `size()` → `size_t`：当前节点数。
* `empty()` → `bool`：是否无节点。
* 构造/析构/旋转/遍历 → `void` 或迭代器。

#### **内部原理剖析**

* **节点结构**：包含键值对 `_data`、四指针与 `_balance_factor`。
* **平衡因子维护**：插入删除后更新并触发局部旋转。
* **四种失衡与旋转**：LL/RR 用单旋，LR/RL 用双旋。
* **旋转细节**：

  1. **单旋**：重挂子指针，更新父子关系与因子。
  2. **双旋**：先旋转子树，再旋转当前树。
* **无递归遍历**：借助适配器 `stack_adapter::stack`，模拟系统栈。
* **资源释放**：后序栈或递归，确保先删除子节点。

#### **复杂度分析**

* **时间**：插入/删除/查找 `O(log n)` 平均,`O(n)` 最坏。
* **空间**：节点存储 `O(n)`，递归或栈辅助 `O(h)`，h=树高。
* **遍历/清理**：`O(n)` 时间。

#### **边界条件和错误处理**

* 空树：`pop`/`find` 返回 `false`/`nullptr`；`size=0`。
* 重复键：`push` 不插入，返回 `false`。
* 内存不足：新节点分配时抛 `std::bad_alloc`。
* 无效仿函数：若不满足严格弱序，行为未定义。

#### **注意事项**

* **线程安全**：非线程安全，需外部同步。
* **迭代器失效**：树结构变更后所有迭代器失效。
* **连续旋转性能**：频繁批量插入可能触发大量旋转。
* **平衡因子同步**：任何指针操作后都需更新因子。

#### **使用示例**

```cpp
using namespace template_container::tree_container;
int main() 
{
    // 1. 构造AVL树
    avl_tree<int, std::string> avl;
    avl.push(5, "A");
    avl.push(3, "B");
    avl.push(7, "C");
    avl.push(2, "D");
    avl.push(4, "E");
    
    std::cout << "中序遍历: ";
    avl.middle_order_traversal();  // 输出: 2 3 4 5 7
    
    // 2. 查找节点
    auto node = avl.find(3);
    if (node) 
    {
        std::cout << "\n找到键3的值: " << node->_data.second << std::endl;
    }
    
    // 3. 删除节点
    avl.pop(3);
    std::cout << "删除3后中序遍历: ";
    avl.middle_order_traversal();  // 输出: 2 4 5 7
    
    // 4. 迭代器遍历
    std::cout << "\n迭代器遍历: ";
    for (auto it = avl.begin(); it != avl.end(); ++it) 
    {
        std::cout << it->first<< " ";
    }
    
    return 0;
}
```
> **引用**：头文件 `tree_container` 命名空间。
---
## 基类容器 `base_class_container`
## 红黑树 
## `rb_tree`
### 类概述
* `rb_tree` 类是一个模板化的红黑树实现，支持键值对存储和自动平衡功能。
红黑树通过颜色标记和旋转操作保持平衡，确保插入、删除和查找操作的平均时间复杂度为 O (log n)。该类实现了完整的迭代器系统、红黑树调整算法和异常处理机制。
#### **类及其函数定义**
```cpp
template <typename rb_tree_type_key,typename rb_tree_type_value,typename container_imitate_function_visit,
    typename container_imitate_function = template_container::imitation_functions::less<rb_tree_type_key>>
class rb_tree 
{
private:
    enum rb_tree_color 
    { red, black };

    class rb_tree_node 
    {
    public:
        rb_tree_type_value _data;
        rb_tree_node*      _left;
        rb_tree_node*      _right;
        rb_tree_node*      _parent;
        rb_tree_color      _color;

        explicit rb_tree_node(const rb_tree_type_value& val_data = rb_tree_type_value());
        explicit rb_tree_node(rb_tree_type_value&& val_data) noexcept;
    };

    using container_node = rb_tree_node;
    container_node*                 _root;
    container_imitate_function_visit element;
    container_imitate_function      function_policy;

    // 核心旋转方法
    void left_revolve(container_node* x);
    void right_revolve(container_node* x);
    // 删除平衡
    void delete_adjust(container_node* x, container_node* parent);

    // 清理与遍历
    void clear(container_node* node) noexcept;
    void interior_middle_order_traversal(container_node* node);
    void interior_pre_order_traversal(container_node* node);
    size_t _size() const;

public:
    using iterator = rb_tree_iterator<rb_tree_type_value, rb_tree_type_value&, rb_tree_type_value*>;
    using const_iterator = rb_tree_iterator<rb_tree_type_value const, rb_tree_type_value const&, rb_tree_type_value const*>;
    using reverse_iterator = rb_tree_reverse_iterator<iterator>;
    using const_reverse_iterator = rb_tree_reverse_iterator<const_iterator>;
    using return_pair_value = template_container::practicality::pair<iterator, bool>;

    // 构造与析构
    rb_tree();
    explicit rb_tree(const rb_tree_type_value& data);
    explicit rb_tree(rb_tree_type_value&& data) noexcept;
    rb_tree(const rb_tree& other);
    rb_tree(rb_tree&& other) noexcept;
    ~rb_tree() noexcept;

    // 核心操作
    return_pair_value push(const rb_tree_type_value& v);
    return_pair_value push(rb_tree_type_value&& v) noexcept;
    return_pair_value pop(const rb_tree_type_value& v);
    iterator           find(const rb_tree_type_value& v);

    // 查询与遍历
    size_t            size() const;
    bool              empty() const;
    void              middle_order_traversal();
    void              pre_order_traversal();
    iterator          begin();
    iterator          end();
    const_iterator    cbegin() const;
    const_iterator    cend() const;
    reverse_iterator  rbegin();
    reverse_iterator  rend();
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    // 运算符
    iterator operator[](const rb_tree_type_value& v);
    rb_tree& operator=(const rb_tree other);
    rb_tree& operator=(rb_tree&& other) noexcept;
};
```
#### **作用描述**
* **模板参数** 
* `rb_tree_type_key`：键的类型（用于排序和查找）
* `rb_tree_type_value`：值的类型（与键关联的数据）
* `container_imitate_function_visit`：值访问器（用于从值中提取键）
* `container_imitate_function`：键的比较器（默认：`less<rb_tree_type_key>`）

* **构造与析构**：

  * `rb_tree()`：创建空树，`_root=nullptr`。
  * `rb_tree(data)`：根节点为黑色新节点。
  * 拷贝/移动构造：复制或接管节点和颜色。
  * `~rb_tree()`：后序调用 `clear(_root)` 释放节点。

* **插入 (`push`)**：

  1. **定位**：按 `function_policy` 比较沿左右子树查找插入位置，若遇相等则返回 `.second = false`。
  2. **插入**：新节点 `_color = red`，挂接父指针。
  3. **修正红黑性质**：从新节点向上迭代：

     * 若父黑，终止。
     * 若父和叔叔均为红：父、叔改黑，祖父改红，继续向上。
     * 否则执行旋转

       * **LL**：`right_revolve(祖父)`；
       * **RR**：`left_revolve(祖父)`；
       * **LR**：`left_revolve(父)` 后 `right_revolve(祖父)`；
       * **RL**：`right_revolve(父)` 后 `left_revolve(祖父)`。
     * 每次旋转后调整节点颜色，确保子树平衡。
  4. **根染黑**。

* **删除 (`pop`)**：

  1. **查找**：`find` 定位目标节点，若未找到返回 `.second = false`。
  2. **删除**：

     * **单/双子**：参照 BST 删除；双子先用中序后继替换。
     * 保留被删除节点原始颜色至 `orig_color`。
  3. **平衡调整**：若 `orig_color` 为 `black`，调用 `delete_adjust(node, parent)`：(因为是黑色节点删除的话会失衡：从任意节点到其所有后代叶节点的路径上，包含的黑色节点数量相同)

     * **兄弟为红**：对 `parent` 做旋转，交换 `parent` 与兄弟颜色，刷新兄弟。
     * **兄弟与子皆黑**：兄弟染红，继续向上修正。
     * **兄弟为黑，近侧子红**：先旋转兄弟使远侧子成为兄弟，再归入下一情况。
     * **兄弟为黑，远侧子红**：对 `parent` 做一次旋转，根据方向将兄弟和其子调整颜色，结束平衡。
  4. **根染黑**。

* **查找 (`find`)**：

  * 从 `_root` 开始，比较值后沿左右子树移动，返回节点迭代器或 `end()`。

* **遍历**：

  * **中序**：`middle_order_traversal` 使用显式栈保证顺序输出。
  * **前序**：`interior_pre_order_traversal` 同理实现。
  * 迭代器 `begin/end`、`rbegin/rend` 对应最左/最右节点。

* **查询**：

  * `empty()`：O(1) 检查 `_root == nullptr`。
  * `size()`：O(n) 调用 `_size()` 递归统计。

#### **返回值说明**

* `push` → `return_pair_value`：

  * `.first`：指向插入或已存在节点。
  * `.second`：`true` 插入并平衡；`false` 已存在。
* `pop` → `return_pair_value`：

  * `.first`：指向被删除节点后继或 `end()`。
  * `.second`：`true` 删除并平衡；`false` 未找到。
* `find` → `iterator`：命中返回节点；否则 `end()`。
* `size()` → `size_t`。
* `empty()` → `bool`。

#### **内部原理剖析**

* **节点颜色与路径**：

  * 红节点不能有红子节点。
  * 根到叶所有路径黑节点数相等。

* **`left_revolve(x)`**：

  * 设 `y=x->_right`。将 `y->_left` 赋给 `x->_right`，更新父指；将 `x` 设为 `y->_left`。
  * 调整 `x`, `y` 父指和 `_root` 链接；将 `y->_color=x_color`，并将 `x->_color=red`。

* **`right_revolve(x)`**：

  * 对称于 `left_revolve`，以 `y=x->_left`。

* **`delete_adjust(x, parent)`**：

  * 以 `x`（可能 `nullptr`）和其父为起点，修复双黑差：

    1. **兄弟红**：旋转 `parent`，交换颜色，刷新兄弟。
    2. **兄弟及兄弟子黑**：兄弟染红，继续向上。
    3. **兄弟黑且近侧子红**：旋转兄弟，交换颜色，转为第四种。
    4. **兄弟黑且远侧子红**：旋转 `parent`，兄弟与 `parent` 颜色互换，远侧子染黑。

* **遍历清理**：

  * 使用 `stack_adapter::stack` 显式管理栈，用后序方式释放。

#### **复杂度分析**

* 插入/删除/查找：平均与最坏均 O(log n)。
* 遍历/清理：O(n)，辅助 O(h) 栈空间。

#### **边界条件和错误处理**

* 空树：`push` 创建根；`pop`/`find` `.second=false`/返回 `end()`。
* 重复值：`push` 返回 `.second=false`。
* 内存不足：抛 `std::bad_alloc`。
* 比较函数须严格弱序。

#### **注意事项**

* 非线程安全。
* 结构修改后迭代器失效。
* 确保每次插入删除后根为黑。

#### **使用示例**
* 当前类不推荐直接使用，建议使用上层容器

> **引用** 头文件 `base_class_container` 命名空间


---
## 哈希表
## `hash_table`
### 类概述
* `hash_table` 是一个模板化的哈希表实现，采用链地址法（拉链法）解决哈希冲突，支持键值对的高效存储与查询。
该类通过维护全局插入顺序链表和桶内链表，实现了快速哈希查找和有序遍历的双重功能，并具备动态扩容机制以保持高效性能。 

#### **类及其函数定义**

```cpp
template <typename hash_table_type_key,typename hash_table_type_value,typename container_imitate_function,
          typename hash_function = std::hash<hash_table_type_value>>
class hash_table 
{
private:
    class hash_table_node 
    {
    public:
        hash_table_type_value _data;                // 存储的值
        hash_table_node*      _next;                // 桶内链指针
        hash_table_node*      overall_list_prev;    // 全局链表前向指针
        hash_table_node*      overall_list_next;    // 全局链表后向指针

        explicit hash_table_node(const hash_table_type_value& v);
        explicit hash_table_node(hash_table_type_value&& v) noexcept;
    };

    using container_node = hash_table_node;
    container_imitate_function         value_imitation_functions; // 键比较仿函数
    hash_function                      hash_function_object;    // 哈希函数

    size_t _size;          // 当前元素数量
    size_t load_factor;    // 负载因子阈值*10
    size_t hash_capacity;  // 桶数量

    template_container::vector_container::vector<container_node*> vector_hash_table; // 桶数组
    container_node* overall_list_head_node;   // 全局插入链表头
    container_node* overall_list_before_node; // 全局插入链表尾

    // 链调整辅助
    void hash_chain_adjustment(container_node*& parent, container_node*& node, size_t index);

    // 全局链表及桶重建辅助（扩容时使用）

public:
    template <typename K, typename V>
    class hash_iterator 
    {
    private:
        container_node* ptr;
    public:
        explicit hash_iterator(container_node* p);
        V& operator*() const;
        V* operator->() const;
        hash_iterator& operator++();   // 顺序遍历整体链表
        hash_iterator operator++(int);
        bool operator==(const hash_iterator& o) const;
        bool operator!=(const hash_iterator& o) const;
    };

    using iterator = hash_iterator<hash_table_type_key, hash_table_type_value>;
    using const_iterator = hash_iterator<const hash_table_type_key, const hash_table_type_value>;

    // 构造与析构
    hash_table();
    explicit hash_table(size_t initial_capacity);
    hash_table(const hash_table& other);
    hash_table(hash_table&& other) noexcept;
    ~hash_table() noexcept;

    // 核心操作
    bool change_load_factor(size_t new_load_factor);
    bool push(const hash_table_type_value& v);
    bool push(hash_table_type_value&& v) noexcept;
    bool pop(const hash_table_type_value& v);
    iterator find(const hash_table_type_value& v);

    // 查询接口
    size_t size() const;
    bool empty() const;
    size_t capacity() const;

    iterator begin();
    const_iterator cbegin() const;
    static iterator end();
    static const_iterator cend();

    // 全局顺序遍历（按插入顺序）

    // 运算符重载
    iterator operator[](const hash_table_type_key& key);
    hash_table& operator=(const hash_table& other);
    hash_table& operator=(hash_table&& other) noexcept;
};
```

#### **作用描述**

1. **模板参数**

   * `hash_table_type_key`：用于查找的键类型。
   * `hash_table_type_value`：存储的值类型。
   * `container_imitate_function`：键比较或提取仿函数。
   * `hash_function`：对值或键生成桶索引的哈希函数。

2. **构造与析构**

   * `hash_table()`：使用默认容量 `10`，负载因子 `7` (即 0.7) 初始化桶数组。
   * `hash_table(cap)`：使用指定 `cap` 大小初始化。
   * `hash_table(const other)`：深拷贝所有节点、桶结构和全局链表顺序。
   * `hash_table(hash_table&&)`：移动构造，接管内部容器与链表指针。
   * `~hash_table()`：遍历所有桶，删除每个节点。

3. **插入 (`push`)**

   1. **重复检测**：调用 `find` 查找值是否已存在，若存在返回 `false`。
   2. **扩容判断**：若 `_size * 10 >= hash_capacity * load_factor`，则：

      * 计算新容量 `new_cap = max(10, 2*hash_capacity)`。
      * 重新分配新桶数组，并遍历全局链表按插入顺序重建桶链和全局链。
   3. **插入操作**：

      * 计算 `h = hash_function_object(v) % hash_capacity`。
      * 在桶链头部执行头插：`new_node->_next = vector_hash_table[h]`，`vector_hash_table[h] = new_node`。
      * 在全局链表尾追加：链接 `overall_list_before_node` → `new_node`。
      * 更新 `_size++`。
   4. **返回**：插入成功返回 `true`。

4. **删除 (`pop`)**

   1. **查找节点**：计算 `h` 并遍历桶链，定位目标节点及其桶内父节点。
   2. **全局链表移除**：根据节点在全局链表的头/中/尾位置，更新 `overall_list_*` 指针。
   3. **桶链移除**：调用 `hash_chain_adjustment` 将父或桶头指向被删节点的下一个。
   4. **释放节点**，`_size--`，返回 `true`；未找到返回 `false`。

5. **查找 (`find`)**

   * 若 `_size==0` 返回 `end()`；否则计算 `h`，遍历桶链比较 `value_imitation_functions`。

6. **查询**

   * `size()`、`empty()`、`capacity()` 直接返回内部字段。
   * `begin()` / `end()`、`cbegin()` / `cend()` 在全局链表上按插入顺序遍历。

#### **返回值说明**

* `push(...)` → `bool`：

  * `true`：新值已插入；
  * `false`：值已存在。
* `pop(...)` → `bool`：

  * `true`：删除成功；
  * `false`：未找到。
* `find(...)` → `iterator`：

  * 指向目标；未找到为 `end()`。
* `change_load_factor` → `bool`：

  * `true`：新负载因子生效；
  * `false`：输入无效。
* `size()`, `capacity()` → `size_t`。
* `empty()` → `bool`。

#### **内部原理剖析**

* **桶数组**：`vector_hash_table` 存储每个桶的头节点指针，桶内使用单链 `_next` 处理冲突。
* **全局链表**：`overall_list_head_node` 与 `overall_list_before_node` 串联所有节点，支持按插入顺序遍历。
* **扩容**：依据负载因子动态触发；重建时保持全局插入顺序。
* **链表移除**：

  * `hash_chain_adjustment` 检查父节点是否为空，若为空更新桶头，否则更新 `parent->_next`。
  * 全局链表删除需要处理头/中/尾三类情况。

#### **复杂度分析**

* `push` / `pop` / `find`：平均 `O(1)`，最坏 `O(n)`（全部冲突或重建时为 `O(n)`。
* 扩容：`O(n)` 需遍历全局链表重建。
* 空间：`O(n + cap)` 桶数组 + 全局链表。

#### **边界条件和错误处理**

* **空表**：`find`、`pop` 安全返回；`push` 正常插入首节点。
* **重复值**：`push` 返回 `false`。
* **负载因子**：`change_load_factor` 保证新值 ≥ 1。
* **内存不足**：节点分配或扩容时抛 `std::bad_alloc`。

#### **注意事项**

* 非线程安全，需外部同步。
* 扩容过程中，原节点不失序；中途异常会导致部分重建，可考虑事务回滚。
* 全局链表内存管理需与桶链同步。

#### **使用示例**
* 当前类不推荐直接使用，建议使用上层容器
> **引用** 头文件 `base_class_container` 命名空间


### set\_container::tree\_set

**定义位置**：

```cpp
namespace set_container
{
    template <typename set_type_val, typename external_compare = template_container::imitation_functions::less<set_type_val>>
    class tree_set
    {
        using key_val_type = set_type_val;
        using instance_rb = base_class_container::rb_tree<set_type_val, set_type_val, /*key_extractor*/ ???, external_compare>;
        instance_rb instance_tree_set;
    public:
        using iterator = typename instance_rb::iterator;
        using const_iterator = typename instance_rb::const_iterator;
        using reverse_iterator = typename instance_rb::reverse_iterator;
        using const_reverse_iterator = typename instance_rb::const_reverse_iterator;
        tree_set();
        ~tree_set() = default;
        tree_set(const tree_set& other);
        tree_set(tree_set&& other) noexcept;
        explicit tree_set(const key_val_type& data);
        explicit tree_set(key_val_type&& data) noexcept;
        tree_set(const std::initializer_list<key_val_type>& list);
        tree_set& operator=(const tree_set& other);
        tree_set& operator=(tree_set&& other) noexcept;
        tree_set& operator=(const std::initializer_list<key_val_type>& list);
        iterator push(const key_val_type& data);
        set_iterator push(key_val_type&& data) noexcept;
        iterator pop(const key_val_type& data);
        iterator find(const key_val_type& data);
        void middle_order_traversal();
        void pre_order_traversal();
        [[nodiscard]] size_t size() const;
        bool empty();
        iterator begin();
        iterator end();
        const_iterator cbegin();
        const_iterator cend();
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator crbegin();
        const_reverse_iterator crend();
        iterator operator[](const key_val_type& data);
    };
}
```

* **引用**：

#### 数据结构与原理

* 内部使用 `rb_tree<set_type_val, set_type_val, key_extractor, Compare>`，其中 `key_extractor(value) -> const value&`。
* 元素按值排序，不存储重复元素。

#### 接口详解

* 与 `tree_map` 相似，但 `value` 与 `key` 相同，仅一个类型。
* **插入** `iterator push(const set_type_val& data)`：插入新元素，若已存在返回 end() 或现有 iterator；需参考实现。
* **删除** `iterator pop(const set_type_val& data)`: 删除元素，返回下一个或特定标志；文档需说明具体行为。
* **查找** `iterator find(const set_type_val& data)`: 返回 iterator 或 end()。
* **operator\[]**：意义不明显，对 set 通常不提供 operator\[]；但头文件中定义，可能用于查找或插入，需查看实现并严格说明。
* 其他同 `tree_map`。

#### 复杂度

* 插入/删除/查找 O(log n)。
* 遍历 O(n)。

#### 示例

```cpp
template_container::set_container::tree_set<int> s;
s.push(5);
s.push(3);
if(s.find(4) == s.end()) {
    std::cout << "4 不存在\n";
}
for(auto it : s) { std::cout << it << " "; }
s.pop(3);
```

---

### hash\_map 容器

**定义位置**：

```cpp
namespace map_container
{
    template <typename hash_map_type_key,
              typename hash_map_type_value,
              typename first_external_hash_functions = template_container::imitation_functions::hash_imitation_functions,
              typename second_external_hash_functions = template_container::imitation_functions::hash_imitation_functions>
    class hash_map
    {
        using key_val_type = template_container::practicality::pair<hash_map_type_key, hash_map_type_value>;
        struct key_val
        {
            const hash_map_type_key& operator()(const key_val_type& key_value) { return key_value.first; }
        };
        class inbuilt_map_hash_functor
        {
        private:
            first_external_hash_functions  first_hash_functions_object;
            second_external_hash_functions second_hash_functions_object;
        public:
            size_t operator()(const key_val_type& key_value) noexcept;
        };
        using hash_table = base_class_container::hash_table<hash_map_type_key, key_val_type, key_val, inbuilt_map_hash_functor>;
        hash_table instance_hash_map;
    public:
        using iterator = typename hash_table::iterator;
        using const_iterator = typename hash_table::const_iterator;
        hash_map();
        ~hash_map() = default;
        explicit hash_map(const key_val_type& key_value);
        hash_map(const hash_map& other);
        hash_map(hash_map&& other) noexcept;
        bool push(const key_val_type& key_value);
        bool pop(const key_val_type& key_value);
        iterator find(const key_val_type& key_value);
        [[nodiscard]] size_t size() const;
        bool empty();
        size_t capacity();
        iterator begin();
        iterator end();
        const_iterator cbegin();
        const_iterator cend();
        iterator operator[](const key_val_type& key_value);
    };
}
```

* **引用**：

#### 内部数据结构

* 基于 `base_class_container::hash_table`，用链表或其它结构解决冲突，并维护插入顺序或其他额外链表指针（头文件实现中有 `overall_list_head_node`, `overall_list_next` 等，用于保留元素插入顺序遍历）。
* `key_extractor` 提取 key；`inbuilt_map_hash_functor` 结合两个散列函数对 `(key, value)` 进行散列。

#### 核心操作

1. **插入 `bool push(const key_val_type& kv)`**

    * 计算 hash：`size_t h = functor(kv)`，取模桶数得到 `index`。
    * 遍历链表：若存在相同 key，更新 value 或不插入根据实现；头文件逻辑需严格说明。
    * 否则在桶头或尾插入新节点，调整全局链表指针保持插入顺序；`_size++`。
    * 可能触发 rehash（当 load factor 超过某阈值时），重新分配更大桶表并重新插入所有元素。
    * **返回值**：`true` 表示插入成功；若重复键且不更新，返回 `false`；若更新，则视设计可返回 `true`。
    * **复杂度**：平均 O(1)，最坏 O(n)（冲突严重或 rehash）。

2. **删除 `bool pop(const key_val_type& kv)`**

    * 计算 hash，定位桶链；遍历链表查找匹配 key；
    * 若找到，调整链表指针（桶链与全局链表），删除节点，`_size--`，返回 `true`。
    * 否则返回 `false`。
    * **参考头文件实现**：详见链式删除逻辑片段 。

3. **查找 `iterator find(const key_val_type& kv)`**

    * 计算 hash，遍历桶链，若匹配返回 iterator；否则返回 end()。
    * **引用**：

4. **迭代器、遍历**

    * 内部维护全局链表（双向链表）记录插入顺序，迭代器按该顺序遍历所有元素。
    * `begin()` 返回全局链表头；`end()` 表示尾后位置。
    * **示例**

      ```cpp
      template_container::map_container::hash_map<int, std::string> hm;
      hm.push({1, "a"});
      hm.push({2, "b"});
      for(auto it = hm.begin(); it != hm.end(); ++it) {
          auto [k, v] = *it;
          std::cout << k << " -> " << v << std::endl;
      }
      ```

5. **其他**

    * `size()`, `empty()`, `capacity()`：`capacity` 返回当前桶数组长度。
    * `operator[](const key_val_type& kv)`: 查找或插入新元素，返回 iterator 到对应元素，可用于访问或插入默认值：`hm[{key, default_value}]`。
    * **示例**

      ```cpp
      auto it = hm[{3, "default"}]; // 若 key=3 不存在，插入 {3,"default"} 并返回 iterator
      ```
    * **注意**：对 `operator[]` 的具体行为需参照头文件实现细节并严格说明。

#### rehash 机制

* **阈值**：当 `_size / bucket_count` 超过某 load factor（如 0.75）时，扩容至更大素数或两倍大小。
* **过程**：

    1. 分配更大桶数组，初始为空。
    2. 遍历旧全局链表，将每个元素重新计算 hash 并插入新桶。
    3. 更新 `vector_hash_table`、`hash_capacity`、`Load_factor` 等。
* **复杂度**：rehash O(n)。插入时偶发，摊销成本较小。

#### 复杂度

* 插入/删除/查找：平均 O(1)，最坏 O(n)。
* 迭代遍历：O(n)。
* 空间：O(n + bucket\_count)。

#### 示例

```cpp
template_container::map_container::hash_map<std::string,int> hm;
hm.push({"apple",10});
if(hm.pop({"banana",0})) { /* 删除成功 */ }
auto it = hm.find({"apple",0});
if(it != hm.end()) {
    std::cout << it->second;
}
```

---

### set\_container::hash\_set

**定义位置**：

```cpp
namespace set_container
{
    template <typename set_type_val, typename external_hash_functions = template_container::imitation_functions::hash_imitation_functions>
    class hash_set
    {
        using key_val_type = set_type_val;
        class inbuilt_set_hash_functor
        {
        private:
            external_hash_functions hash_functions_object;
        public:
            size_t operator()(const key_val_type& key_value) { return hash_functions_object(key_value)* 131; }
        };
        class key_val { public: const key_val_type& operator()(const key_val_type& key_value) { return key_value; } };
        using hash_table = template_container::base_class_container::hash_table<set_type_val, key_val_type, key_val, inbuilt_set_hash_functor>;
        hash_table instance_hash_set;
    public:
        using iterator = typename hash_table::iterator;
        using const_iterator = typename hash_table::const_iterator;
        hash_set();
        ~hash_set() = default;
        explicit hash_set(const key_val_type& data);
        hash_set(const hash_set& other);
        hash_set(hash_set&& other) noexcept;
        bool push(const key_val_type& data);
        bool pop(const key_val_type& data);
        iterator find(const key_val_type& data);
        size_t size();
        bool empty();
        size_t capacity();
        iterator begin();
        iterator end();
        const_iterator cbegin();
        const_iterator cend();
        iterator operator[](const key_val_type& data);
        // initializer_list 构造与赋值
    };
}
```

* **引用**：

#### 说明

* 与 `hash_map` 类似，但只存储键，不存储值；若需要关联值，可使用 `hash_map`。
* `push` 插入元素，返回 `true` 若插入成功；重复时返回 `false`。
* `pop` 删除；`find` 查找；`operator[]` 可插入并返回 iterator 或仅查找行为，需严格按实现说明。
* 迭代器遍历顺序为插入顺序（由全局链表维护）。
* 复杂度同 `hash_map`。
* **示例**

  ```cpp
  template_container::set_container::hash_set<int> hs;
  hs.push(5);
  if(hs.find(5) != hs.end()) { /* 存在 */ }
  hs.pop(5);
  ```

---

## 基础哈希表实现 `base_class_container::hash_table`

**定义位置**：

```cpp
namespace template_container::base_class_container
{
    template <typename Key, typename Value, typename KeyExtractor, typename HashFunctor>
    class hash_table
    {
        struct container_node
        {
            Value _data;
            container_node* _next; // 同一桶内链表
            container_node* overall_list_prev; // 全局双向链表用于遍历
            container_node* overall_list_next;
            explicit container_node(const Value& data);
        };
        using hash_table_type_value = Value;
        using hash_table_type_key = typename std::decay<decltype(std::declval<KeyExtractor>()(std::declval<Value>()))>::type;
        HashFunctor hash_function_object;
        size_t _size;
        size_t hash_capacity;
        std::vector<container_node*> vector_hash_table;
        // 全局链表头尾指针 maintained via container_node::overall_list_prev/next
        container_node* overall_list_head_node;
        container_node* overall_list_before_node;
    public:
        using iterator = Hash_iterator<...>;
        using const_iterator = Hash_iterator<...>;
        hash_table();
        ~hash_table();
        bool push(const Value& value_data);
        bool pop(const Value& value_data);
        iterator find(const Value& value_data);
        [[nodiscard]] size_t size() const;
        bool empty() const;
        size_t capacity() const;
        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;
        iterator operator[](const Value& value_data);
        // 可能其他成员：load_factor调整、rehash、resize等
    };
}
```

* **引用**：

#### 数据结构

* **桶数组** `vector<container_node*> vector_hash_table`，长度 `hash_capacity`，初始可能为某常数。
* **桶链**：每个 `vector_hash_table[i]` 指向该桶链表头，通过 `container_node::_next` 链接同一桶内元素。
* **全局链表**：通过 `container_node::overall_list_prev/next` 维护元素插入顺序，便于按插入顺序遍历；`overall_list_head_node`、`overall_list_before_node` 分别指向全局链表头和尾。
* **成员**

    * `size_t _size`：当前元素数。
    * `size_t hash_capacity`：当前桶数组大小。
    * `HashFunctor hash_function_object`：计算 `Key` 的哈希值。
    * `KeyExtractor element`：提取 `Key` 用于比较。

#### 构造与析构

* **构造** `hash_table()`：初始化 `_size = 0`，`hash_capacity` 设初始值（如 16 或根据实现），分配 `vector_hash_table` 并填充 `nullptr`，`overall_list_head_node = overall_list_before_node = nullptr`。
* **析构**：遍历全局链表释放所有节点，或遍历每桶链；释放资源。

#### 插入 `bool push(const Value& value_data)`

* **流程**：

    1. 计算 `size_t hv = hash_function_object(value_data)`；
    2. `index = hv % hash_capacity`;
    3. 遍历桶链 `vector_hash_table[index]`：对每个节点 `n`，若 `KeyExtractor(n->_data) == KeyExtractor(value_data)`，视为重复：根据设计可能更新 `n->_data` 或不插入。头文件行为需严格引用；通常返回 `false`。
    4. 若无重复，创建新节点 `new container_node(value_data)`，将其插入桶链头或尾（头文件实现细节），并插入全局链表尾：

        * 若 `overall_list_before_node == nullptr`（空表），则 `overall_list_head_node = overall_list_before_node = new_node`；
        * 否则 `overall_list_before_node->overall_list_next = new_node; new_node->overall_list_prev = overall_list_before_node; overall_list_before_node = new_node;`
        * `new_node->_next` 指向原桶链头或 nullptr，根据实现。
    5. `_size++`。
    6. 若插入后 `_size / hash_capacity > load_factor`，触发 rehash：重新分配更大 `vector_hash_table`，遍历旧全局链重新插入。
* **返回值**：

    * `true` 插入成功；
    * `false` 重复时不插入。
* **复杂度**：

    * 平均 O(1)，最坏 O(n)（长链或 rehash）。

#### 删除 `bool pop(const Value& value_data)`

* **流程**：

    1. 若 `_size == 0`，直接返回 `false`。
    2. 计算 `hv = hash_function_object(value_data)`, `index = hv % hash_capacity`;
    3. 遍历桶链：使用双指针 `parent`, `current`；若 `KeyExtractor(current->_data) == KeyExtractor(value_data)`：

        * 调整桶链指针：

            * 如果 `current` 在链头：`vector_hash_table[index] = current->_next`;
            * 否则：`parent->_next = current->_next`;
        * 调整全局链表：参见头文件删除逻辑 ：

            * 如果删除节点为全局链表头或尾，更新 `overall_list_head_node` / `overall_list_before_node`；否则调整前后指针链接。
        * `delete current; _size--; return true;`
    4. 遍历结束未找到，返回 `false`.
* **示例**引用删除片段：
* **复杂度**：平均 O(1)，最坏 O(n)。

#### 查找 `iterator find(const Value& value_data)`

* **流程**：

    * 如插入，相同哈希定位桶链，遍历链查找匹配，返回 iterator 或 end()。
* **返回值**：iterator 指向节点或 end()。
* **复杂度**：平均 O(1)，最坏 O(n)。
* **引用**：

#### 迭代器实现

* 迭代器内部持有 `container_node* current`；
* `operator++`：沿全局链表 `overall_list_next` 前进；`operator--`：沿 `overall_list_prev` 后退；
* `begin()` 返回 `overall_list_head_node`; `end()` 返回 `nullptr` 或特定哨兵；
* **失效规则**：插入操作可能使 rehash 重新分配桶数组，但全局链表节点不变，迭代器只关注全局链表，通常不影响；删除或清空使相关迭代器失效。

#### 大小与容量

* `size()` 返回 `_size`；`empty()` 判断 `_size == 0`；
* `capacity()` 返回 `hash_capacity`；
* `load_factor()`: 若实现，返回 `_size / hash_capacity`；

#### rehash / resize

* 暴露接口如 `resize(const size_t& new_capacity)` 或 `Change_Load_factor`，可手动调整桶大小或负载因子阈值；头文件若未公开，仅内部使用。
* **示例**：若头文件提供 `Change_Load_factor(const size_t& new_load)`:

  ```cpp
  hm.Change_Load_factor(2); // 设置负载因子阈值为 2.0
  ```
* **复杂度**：rehash O(n)。

#### 异常与安全

* 内存分配失败应抛 `customize_exception`；需保证状态一致或回滚。
* 多线程：非线程安全；并行修改需同步；并行遍历与修改需谨慎。

---

## 位集合容器 `base_class_container::bit_set`

**定义位置**：

```cpp
namespace template_container::base_class_container
{
    class bit_set
    {
        template_container::vector_container::vector<int> vector_bit_set;
        size_t _size;
    public:
        bit_set();
        explicit bit_set(const size_t& new_capacity);
        void resize(const size_t& new_capacity);
        bit_set(const bit_set& other);
        bit_set& operator=(const bit_set& other);
        void set(const size_t& value_data);
        void reset(const size_t& value_data);
        [[nodiscard]] size_t size() const;
        bool test(const size_t& value_data);
    };
}
```

* **引用**：

#### 数据结构

* 使用底层 `vector<int>` 存储多个 `int` 作为位块，每个 `int` 包含 32 位（假设 `int` 为 32 位）。
* `_size` 记录已置位的总数或容量？根据实现，`_size` 更新逻辑：

    * 构造或 `resize` 时 `_size = 0`，表示当前置位数量为 0。
    * 每次 `set(value_data)` 时 `_size++`；`reset(value_data)` 时 `_size--`。
    * 注意：若对同一位置重复 `set`，可能导致 `_size` 计数不准确；头文件实现简单地 `_size++`，调用者需避免重复 `set` 同一位，或文档中需特别说明：若多次 `set` 相同索引，`_size` 会累加，需谨慎。

#### 构造与析构

* `bit_set()`: `_size = 0; vector_bit_set` 为空或容量 0。
* `explicit bit_set(const size_t& new_capacity)`:

    * `_size = 0; vector_bit_set.resize((new_capacity / 32) + 1, 0);`
    * 分配足够 `int` 存储索引 `0 ... new_capacity-1`。
* `void resize(const size_t& new_capacity)`: 重置 `_size = 0; vector_bit_set.resize((new_capacity / 32) + 1, 0);`
* 拷贝构造、赋值：深拷贝 `vector_bit_set`，复制 `_size`。

#### 位操作

1. `void set(const size_t& value_data)`

    * 计算 `mapping_bit = value_data / 32; value_bit = value_data % 32;`
    * `vector_bit_set[mapping_bit] |= (1 << value_bit);`
    * `_size++`;
    * **注意**：无重复检测，若该位已为 1，仍 `_size++`；使用者需确保不重复调用，或文档提醒此实现缺陷。
    * **示例**

      ```cpp
      bit_set bs(100);
      bs.set(5); // 将第 5 位置 1
      ```
    * **复杂度**：O(1)。

2. `void reset(const size_t& value_data)`

    * `mapping_bit = value_data / 32; value_bit = value_data % 32;`
    * `vector_bit_set[mapping_bit] &= ~(1 << value_bit);`
    * `_size--`;
    * **同样无检测**：若该位已为 0，多次 reset 导致 `_size` 可能错误；文档需明确。
    * **示例**

      ```cpp
      bs.reset(5);
      ```
    * **复杂度**：O(1)。

3. `bool test(const size_t& value_data)`

    * 若 `_size == 0`，直接返回 `false`；否则
    * `mapping_bit = value_data / 32; value_bit = value_data % 32;`
    * `return (vector_bit_set[mapping_bit] & (1 << value_bit)) != 0;`
    * **示例**

      ```cpp
      if(bs.test(5)) { /* 位已置 */ }
      ```
    * **复杂度**：O(1)。
    * **注意**：若 `_size` 仅作为置位次数计数，不代表容量，test 时需关注索引是否超出 `vector_bit_set` 大小；若超出，程序可能越界访问，需文档中提醒：使用前确保 `value_data < capacity`。

4. `size_t size() const`

    * 返回 `_size`，表示置位总数（但且仅在无重复 set/reset 情形下正确）。
    * **复杂度**：O(1)。

#### 边界与错误

* **索引范围**：`value_data` 超出 `new_capacity` 范围时，访问 `vector_bit_set[mapping_bit]` 越界，导致未定义行为。
* 文档中应提示：使用前需确保 `value_data` 在 `[0, capacity())` 区间；如需安全，可在外层封装或在头文件中自行添加检查并抛 `customize_exception`。
* **重复 set/reset**：可能导致 `_size` 不准确；调用方应注意。
* **多线程**：非线程安全；并发修改应外部同步。

#### 应用场景

* **位图**：快速表示集合成员存在/不存在，空间紧凑。
* **布隆过滤器**：`bloom_filter` 中用作底层位集。
* **位运算加速**：可用于快速检查、大规模标记等。
* **示例**

  ```cpp
  // 标记 0..999 是否出现
  bit_set visitor(1000);
  for(int x : data) {
      if(visitor.test(x)) {
          std::cout << x << " 重复出现\n";
      } else {
          visitor.set(x);
      }
  }
  ```
* **容量扩展**：调用 `resize(new_capacity)` 重置位集，清空已有标记。

---

## 布隆过滤器 `bloom_filter_container::bloom_filter`

**定义位置**：

```cpp
namespace bloom_filter_container
{
    template <typename bloom_filter_type_value,typename bloom_filter_hash_functor = template_container::algorithm::hash_algorithm::hash_function<bloom_filter_type_value>>
    class bloom_filter
    {
        bloom_filter_hash_functor hash_functions_object;
        using bit_set = template_container::base_class_container::bit_set;
        bit_set instance_bit_set;
        size_t _capacity;
    public:
        bloom_filter();
        explicit bloom_filter(const size_t& Temp_Capacity);
        [[nodiscard]] size_t size() const;
        [[nodiscard]] size_t capacity() const;
        bool test(const bloom_filter_type_value& TempVal);
        void set(const bloom_filter_type_value& TempVal);
        // 不支持删除
    };
}
```


#### 概述

* 布隆过滤器是一种基于位集和多重散列的概率型数据结构，用于测试元素是否“可能存在”集合中，不允许删除操作（只支持插入和查询）。
* 返回 `test(...)` 为 `true` 时，表示“可能存在”；返回 `false` 时，表示“一定不存在”。
* 具有空间效率高、插入和查询时间 O(k)（k: 散列函数数量）；存在一定误判率。

#### 构造与初始化

1. `bloom_filter()`：

    * 默认 `_capacity = 1000`。
    * `instance_bit_set.resize(_capacity);` 分配位集长度 `_capacity`。
2. `explicit bloom_filter(const size_t& Temp_Capacity)`：

    * `_capacity = Temp_Capacity; instance_bit_set.resize(_capacity);`
3. **注意**：`capacity` 表示位数组长度；位数组越大，误判率越低，但占用更多内存。

#### 成员方法

1. `[[nodiscard]] size_t size() const`

    * 返回 `instance_bit_set.size()`，即当前置位总数（非布隆过滤器元素数量，仅指已 set 的位数，且由于重复 set 计数行为，此值可能大于实际置位位数）。
    * **用途**：可用作统计位集置位情况，用于估算负载；但对于误判率计算，实际需要统计置位位数而非重复 set 计数，此实现不精确，调用者需注意。

2. `[[nodiscard]] size_t capacity() const`

    * 返回 `_capacity`，表示位集长度。
    * **用途**：用于计算理论误判率：约 `(1 - e^{-kn/m})^k`，其中 n: 插入元素数，m: 位数组大小，k: 散列函数数量（此实现使用固定 3 个哈希函数）。

3. `bool test(const bloom_filter_type_value& TempVal)`

    * 计算三个哈希值：

        * `primary_mapping_location = hash_functions_object.hash_sdmmhash(TempVal) % _capacity;`
        * `secondary_mapping_location = hash_functions_object.hash_djbhash(TempVal) % _capacity;`
        * `tertiary_mapping_location = hash_functions_object.hash_pjwhash(TempVal) % _capacity;`
        * **引用**：多种哈希函数实现来源于 `hash_algorithm::hash_function<T>`&#x20;
    * 检查 `instance_bit_set.test(...)` 三个位是否都为 `true`；若都为 `true`，返回 `true`；否则返回 `false`。
    * **含义**：若任一位未置，则该元素一定不存在；若三位都置，则可能存在（存在误判可能）。
    * **复杂度**：每次哈希计算时间 O(len)，再三次位测试 O(1)，总体 O(k \* len)。

4. `void set(const bloom_filter_type_value& TempVal)`

    * 计算三哈希索引，同 `test`：
    * `instance_bit_set.set(primary_mapping_location); instance_bit_set.set(secondary_mapping_location); instance_bit_set.set(tertiary_mapping_location);`
    * **注意**：`bit_set.set` 会 `_size++`，但重复 set 同一位会错误累计 `_size`；布隆过滤器实际不需要维护准确置位计数，仅需置位位本身；因头文件实现限制，重复 set 会导致 `_size` 错误，文档需说明此局限。
    * **调用示例**

      ```cpp
      template_container::bloom_filter_container::bloom_filter<std::string> bf(10000);
      bf.set("hello");
      if(bf.test("hello")) { /* 可能存在 */ }
      if(!bf.test("world")) { /* 一定不存在 */ }
      ```

5. **删除不支持**：头文件注释中明确“布隆过滤器只支持插入和查找，不支持删除”。

#### 误判率与参数选择

* **理论**：误判率约 `(1 - e^{-kn/m})^k`，k=3（这里使用三个哈希函数）。插入 n 个不同元素后，位被置位概率、误判率可计算；实际使用时，需根据预计 n 和可接受误判率选择位数组大小 m。
* **示例计算**：

    * 若预计 n=1000，m=10000，k=3，则误判率约 `(1 - e^{-3*1000/10000})^3 ≈ (1 - e^{-0.3})^3 ≈ (1 - 0.7408)^3 ≈ 0.2592^3 ≈ 0.0174`（约 1.74%）。
* **文档建议**：提供示例代码或公式，帮助用户选择适当 `_capacity`。
* **注意**：头文件实现 `size()` 返回实际 `_size`（重复 set 问题），并非 n；需用户自行维护插入元素数以估算误判率。

#### 边界与错误

* **索引越界**：确保 `_capacity > 0`，`value_data` 可哈希后取模；哈希函数应返回非负数(size_t类型)。
* **多线程**：并发插入/测试位竞争可能导致数据不一致；可在外部加锁或改进 `bit_set` 的原子位操作。
* **哈希函数安全**：若 `hash_function<T>` 对输入产生不均匀哈希，可能导致高冲突；可自定义 `bloom_filter_hash_functor` 传入更合适哈希。

---

## 算法细节与性能分析

### 红黑树 vs avl 树

* **插入/删除频率 vs. 查找需求**

    * avl 更严格平衡，查询速度略优（高度更小），但插入/删除旋转次数更多。
    * rb 树平衡松散，插入/删除旋转次数较少，常用于通用关联容器。
* **实际选择**：若读操作远多于写操作，avl 可能更佳；若写操作较多，rb 更合适。

### 哈希表设计

* **负载因子**：需根据应用场景设置，文件中阈值为 0.75；过高导致冲突增多；过低浪费空间，函数接口change_load_factor()可以调节。
* **桶数量**：通常取素数或 2 的幂，见头文件实现；可提供 `resize` 接口，允许用户手动调整。
* **冲突解决**：链式散列（Chaining），实现简单；也可开放地址法，但头文件使用链表，如果及其特殊情况下挂红黑树。
* **再哈希（Rehash）**：扩容时重新分配桶数组，并重新插入所有元素，临时开销大，留意在高实时要求场景下可能引发卡顿。

### 位集与布隆过滤器

* **位运算效率**：O(1)，空间紧凑；适合大规模标记。
* **误判性**：布隆过滤器支持快速存在性测试，但存在误判；不支持删除需注意。
* **哈希函数数量与质量**：更多哈希函数降低误判率但增加计算开销；质量差的哈希函数会降低效果。

### 容器适配器与底层容器搭配

* `stack` 通常基于 `vector` 或 `deque`；`queue` 基于 `list`；`priority_queue` 基于 `vector` 实现堆。
* **迭代器失效规则**：对底层容器操作同等失效规则；文档需说明。

### 智能指针与异常安全

* `shared_ptr` 内部用于多线程安全的引用计数需谨慎，避免死锁。
* 析构与资源释放需 noexcept。
* `weak_ptr.lock()` 需原子检查并增加计数。

