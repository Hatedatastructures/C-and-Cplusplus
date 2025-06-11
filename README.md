# [文件说明](#说明)
  * [命名空间与整体结构](#命名空间与整体结构)
## [异常处理 `custom_exception`](#异常处理-custom_exception)
## [智能指针 `smart_pointer`](#智能指针-smart_pointer)
 * [`smart_ptr`](#smart_ptrsmart_ptr_type)
 * [`unique_ptr`](#unique_ptrunique_ptr_type)
 * [`shared_ptr`](#shared_ptrshared_ptr_type)
 * [`weak_ptr`](#weak_ptrweak_ptr_type)
## [模板容器 `template_container`](#模板容器-template_container)
 * ### [仿函数 `imitation_functions` ](#仿函数与算法模块)
     * [`less` ]()
     * [`greater`]()
     * [`hash_imitation_functions`](#imitation_functions)
 * ### [算法 `algorithm`]()
     * [`copy`]()
     * [`swap`]()
     * [`find`]()
     * [`hash_function`]()
 * ### [基础工具 `practicality`](#基础工具命名空间-practicality)
    * [`pair`]()
    * [`make_pair`]()
 * ### [字符数组 `string_container`](#字符数组)
    * [`string`](#string_container)
 * ### [动态数组容器 `vector_container`](#动态数组)
    * [`vector`](#vector_container)
 * ### [链表容器 `list_container`](#链表容器)
     * [`list`](#list_container)
 * ### [栈适配器 `stack_adapter`]()
     * [`stack`](#stack_adapterstack)
 * ### [队列适配器 `queue_adapter`]()
     * [`queue`](#queue_adapterqueue)
     * [`priority_queue`](#queue_adapterpriority_queue)
 * ### [树形容器 `tree_container`](#树形容器基础-tree_container)

     * [`binary_search_tree`](#binary_search_tree二叉搜索树)
     * [`avl_tree`](#avl-树若有对比说明)

 * ### [基类容器 `base_class_container`]()
     * [`rb_tree`]()
     * [`hash_table`]()
     * [`bit_set`]()
 * ### [关联式容器 `map_container` `set_container`]()
    * ### [`有序容器`]()
        * #### [`tree_map`](#map_containertree_map)
        * #### [`tree_set`](#tree_set-容器)
    * ### [`无序容器`]()
        * #### [`hash_map`](#set_containertree_set)
        * #### [`hash_set`](#hash_set-容器)
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

> **注意**：此处省略完整源码摘录，文档假设已严格依据头文件实现，不做任何命名或签名更改。
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

## 基础工具命名空间 `practicality`

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
> **引用/出处**：头文件中 `namespace template_container::practicality::pair`

---

## 仿函数

### `imitation_functions`

* **内容**：包含常见比较、等价、散列等仿函数。
* 常见类型：

    * `less<T>`, `greater<T>`, `equal_to<T>` 等，用于比较元素大小、相等。
    * `hash_imitation_functions`：针对一些类型提供 `operator()(const T&) -> size_t` 散列值。
* **用途**：关联容器、哈希表等需要自定义比较、散列时，可传入此默认仿函数或用户自定义仿函数。
* **示例**

  ```cpp
  template_container::imitation_functions::less<int> cmp;
  bool lt = cmp(3, 5); // true
  template_container::imitation_functions::hash_imitation_functions hf;
  size_t hv = hf("hello");
  ```
* **注意**：若需要自定义类型散列，可特化或自定义仿函数类型，并传递给容器模板参数。

### `algorithm`

* **内容**：基本算法工具，如哈希函数实现（`hash_algorithm::hash_function<T>`），可能包括 `hash_sdmmhash`, `hash_djbhash`, `hash_pjwhash` 等多种哈希函数实现。
* **用途**：布隆过滤器或哈希表中使用不同哈希函数，减少冲突。
* **示例**

  ```cpp
  template_container::algorithm::hash_algorithm::hash_function<std::string> hf;
  size_t h1 = hf.hash_sdmmhash("key");
  ```
* **复杂度**：哈希函数计算时间依赖输入长度，通常 O(len)。

> **引用**：头文件中 `namespace template_container::algorithm` 部分，具体函数签名在头文件中可查阅。（具体编号视检索结果）

---

## 字符数组

### `string_container`
* **概览**：提供类似 `std::string` 或自定义字符串容器功能。
* **主要类**：假设名为 `string` 或 `basic_string`。
* **成员函数**：

    * 构造/析构、拷贝/移动、赋值操作。
    * `size()`, `empty()`, `capacity()`, `reserve()`, `resize()`.
    * `operator+`, `append`, `insert`, `erase`, `find`, `substr` 等。
* **内部实现**：基于动态数组管理字符缓冲，支持小对象优化或直接 new/delete。
* **复杂度分析**：

    * 普通访问 O(1)，连接/插入可能涉及重分配，平均摊销 O(n)。
* **示例**

  ```cpp
  template_container::string_container::string s("hello");
  s.append(", world");
  std::cout << s << std::endl;
  ```
* **引用**：头文件 `string_container` 部分。

---

## 动态数组

### `vector_container`

**定义位置**：
`namespace vector_container { template<typename T> class vector { ... }; }`
**引用**：

#### 内部数据结构

* **底层**：基于动态内存的连续数组。
* **成员变量**：

    * `T* _data` 3个原生指针，指向已分配内存区域。
    * 可能有分配器或异常安全相关成员。
* **内存布局**：位置连续，符合随机访问迭代器要求。

#### 构造与析构

* **默认构造**：`vector()`，初始化 `_data_pointer = nullptr`, `_size_pointer = nullptr`, `_capacity_pointer = nullptr`。
* **带初始容量构造**：`explicit vector(const size_t& n)`，分配至少 `n` 个元素空间。
* **拷贝构造**：分配相同容量，复制所有元素（调用拷贝构造）。
* **移动构造**：接管右值 `_data` 指针，置右值为 null，避免复制元素。
* **析构**：析构所有元素，释放底层内存。

#### 迭代器

* 定义 `iterator`, `const_iterator`, `reverse_iterator`, `const_reverse_iterator`，支持随机访问特性。
* **begin()/end()** 返回指向 `_data_pointer`, `_size_pointer`。
* **rbegin()/rend()** 返回反向迭代器。
* **c++ 标准兼容**：遵循 STL 接口设计。

#### 访问元素

* `T& operator[](size_t index)`, `const T& operator[](size_t index) const`：做边界检查，直接访问第 index 个元素。
* `at(size_t index)`：若实现，可能抛出异常或调用 `customize_exception` 报错越界。
* `front()`, `back()`: 访问第一个和最后一个元素；须保证 `_size > 0`。
* **示例**

  ```cpp
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  std::cout << v[0] << ", " << v.back();
  ```
* **引用**：头文件 `vector_container` 部分方法签名。

#### 插入与删除

* `void push_back(const T&)`：在末尾插入新元素；若 `_size_pointer== _capacity_pointer`，需扩容。
* `void pop_back()`：移除末尾元素；析构该元素并 `--_size_pointer`。
* `iterator insert(iterator pos, const T&)`：在指定位置插入；需要移动后续元素，开销 O(n)。
* `iterator erase(iterator pos)`, `iterator erase(iterator first, iterator last)`：移除元素，需要移动后续元素，O(n)。
* `void clear()`：析构所有元素，`size = 0`，可能保留容量。

##### 扩容策略

* 常见策略：若 `capacity == 0`，置为 1；否则 `capacity *= 2`；或其他增长因子。
* **复杂度摊销分析**：插入操作平均摊销 O(1)，最坏情况 O(n)（扩容并复制所有元素）。

#### 大小与容量

* `size()`, `capacity()`, `empty()`：O(1) 访问。
* `void reserve(size_t new_cap)`: 提前分配至少 `new_cap` 空间，避免频繁扩容。
* `void shrink_to_fit()`: 若有实现，可释放多余容量，使 `_capacity == _size`。

#### 边界条件与异常安全

* 在扩容过程中，若分配或元素复制抛异常，应保证容器处于有效状态：未修改原数据，或使用强异常保证。若头文件使用 `customize_exception` 抛出，需在 catch 中释放分配、回滚 `_size` 等。
* `operator[]` 不检查边界；`at` 实现应检查并抛出 `customize_exception`。
* 多线程：非线程安全；若多线程访问同一 `vector`，需外部同步。

#### 复杂度

* 随机访问：O(1)。
* 插入/删除末尾：平均 O(1)（摊销），最坏 O(n)（扩容）。
* 插入/删除中间：O(n)。
* 空间：O(n) 元素，占用连续内存。

---

## 链表容器
### `list_container`

**定义位置**：
`namespace list_container { template<typename T> class list { ... }; }`
**引用**：

#### 内部数据结构

* **底层**：双向循环链表。
* **节点类型**：包含 `T _data; list_node* _prev; list_node* _next;`。
* **成员变量**：

    * `list_node* head; list_node* tail; size_t _size;`。
    * 可能有哨兵节点（sentinel）简化边界处理。

#### 构造与析构

* 默认构造：`head = tail = nullptr; _size = 0;`。
* 拷贝构造：遍历源列表，逐个复制节点数据，保持顺序。
* 移动构造：接管源列表指针，置源 `head/tail` 为 nullptr，`_size` 调整。
* 析构：遍历所有节点，析构数据、释放节点内存。

#### 迭代器

* `iterator`, `const_iterator`, `reverse_iterator`，支持双向迭代。
* `begin()`: 指向 `head`；`end()`: 指向 `nullptr` 或哨兵；同理 `rbegin()`, `rend()`。
* **失效规则**：插入或删除节点会使相关迭代器失效（指向被删除节点的迭代器无效；其它节点迭代器仍有效）。

#### 插入与删除

* `void push_back(const T&)`, `void push_front(const T&)`：在尾部/头部插入新节点，O(1)。
* `void pop_back()`, `void pop_front()`: 移除尾部/头部节点，析构并释放，O(1)。
* `iterator insert(iterator pos, const T&)`: 在给定位置前插入，需定位 pos 节点，若持有 iterator，直接操作，O(1)；否则可能 O(n) 查找。
* `iterator erase(iterator pos)`: 删除 pos 指向节点，O(1)。
* `void clear()`: 遍历删除所有节点，O(n)。

#### 访问

* 不支持随机访问，仅支持迭代访问。
* `front()`, `back()`: 返回首/尾元素，需保证非空。

#### 复杂度

* 插入/删除给定节点：O(1)。
* 查找某值：O(n)。
* 迭代遍历：O(n)。
* 空间：每节点多 2 个指针开销。

#### 示例

```cpp
template_container::list_container::list<int> lst;
lst.push_back(1);
lst.push_front(0);
for(auto it = lst.begin(); it != lst.end(); ++it) 
{
    std::cout << *it << " ";
}
lst.pop_back();
lst.clear();
```

#### 边界与异常

* 插入时若内存分配失败，应抛出 `customize_exception`；需保证链表状态一致或回滚。
* 多线程：非线程安全；并发修改需同步。

---

## 容器适配器

### stack\_adapter::stack

**定义位置**：
`namespace stack_adapter { template<typename T, typename Container = vector_container::vector<T>> class stack { ... }; }`
**引用**：头文件 `stack_adapter` 部分。

#### 原理

* 基于底层容器（默认 `vector<T>`）实现后进先出 (LIFO)。
* **成员变量**：`Container c;` 存储元素。

#### 主要接口

* `void push(const T&)`: `c.push_back(value)`；
* `void pop()`: `c.pop_back()`；
* `T& top()`: 返回 `c.back()`；
* `bool empty() const`: `c.empty()`；
* `size_t size() const`: `c.size()`；
* 移动/拷贝构造与赋值按底层容器行为实现。

#### 复杂度

* push/pop/top O(1) 平摊。
* 空间与底层容器一致。

#### 示例

```cpp
template_container::stack_adapter::stack<int> st;
st.push(1);
st.push(2);
std::cout << st.top(); // 2
st.pop();
```

### queue\_adapter::queue

**定义位置**：
`namespace queue_adapter { template<typename T, typename Container = list_container::list<T>> class queue { ... }; }`
**引用**：

#### 原理

* 基于底层容器（默认 `list<T>`）实现先进先出 (FIFO)。
* **成员变量**：`Container c;`。

#### 主要接口

* `void push(const T&)`: `c.push_back(value)`；
* `void pop()`: `c.pop_front()`；
* `T& front()`: `c.front()`；
* `T& back()`: `c.back()`；
* `bool empty() const`, `size_t size() const`.

#### 复杂度

* push/pop O(1)。
* 空间与底层容器一致。

#### 示例

```cpp
template_container::queue_adapter::queue<int> q;
q.push(1); q.push(2);
std::cout << q.front(); // 1
q.pop();
```

### queue\_adapter::priority\_queue

**定义位置**：
`namespace queue_adapter { template<typename T, typename Compare = imitation_functions::less<T>> class priority_queue { ... }; }`
**引用**：

#### 原理

* 基于底层 `vector<T>` 实现二叉堆；维护最大堆或最小堆（依据 Compare）。
* **成员变量**：`vector_container::vector<T> vector_container_object; Compare function_policy;`

#### 主要接口

* 构造函数：

    * 默认构造：空堆。
    * 从单个元素构造：插入元素后上浮调整。
    * 拷贝/移动构造与赋值。
* `void push(const T&)`:

    * 将新元素插入 `vector_container_object.push_back(val)`，然后上浮 `priority_queue_adjust_upwards` 保持堆性质。
* `void pop()`:

    * 交换根元素与最后元素，删除最后元素，调用 `priority_queue_adjust_downwards` 从根开始下沉调整。
* `T& top()`: 返回 `vector_container_object.front()` 或 `vector_container_object[0]`。
* `bool empty() const`, `size_t size() const`.
* `void adjust_upwards(int idx)`, `void adjust_downwards(int idx)`: 内部堆调整函数。
* **复杂度**

    * push/pop O(log n)；top O(1)。
    * 构造若给定范围批量建堆，可 O(n)，但头文件若无批量构造，从空逐个插入 O(n log n)。
* **示意图**

    * 堆插入上浮：从插入节点不断与父节点比较并交换，直到不需交换或到达根。
    * 堆删除下沉：从根节点开始，将较小/较大子节点上移替代，直到叶子或无需调整位置。
    * 可在文档中插入示意图（手绘或工具生成），如节点数组映射树结构。
* **示例**

  ```cpp
  template_container::queue_adapter::priority_queue<int> pq;
  pq.push(5);
  pq.push(3);
  pq.push(7);
  std::cout << pq.top(); // 7 (若为最大堆)
  pq.pop(); // 删除 7
  std::cout << pq.top(); // 5
  ```
* **引用**：详见&#x20;

---

## 树形容器基础 `tree_container`

### binary\_search\_tree（二叉搜索树）

**定义位置**：

```cpp
namespace tree_container
{
    template <typename binary_search_tree_type, typename container_imitate_function = template_container::imitation_functions::less<binary_search_tree_type>>
    class binary_search_tree
    {
    private:
        class binary_search_tree_type_node
        {
        public:
            binary_search_tree_type_node* _left;
            binary_search_tree_type_node* _right;
            binary_search_tree_type _data;
            explicit binary_search_tree_type_node(const binary_search_tree_type& data = binary_search_tree_type());
            ~binary_search_tree_type_node();
        };
        using container_node = binary_search_tree_type_node;
        container_node* _root;
        container_imitate_function function_policy;
        // 内部递归或迭代遍历辅助函数...
    public:
        binary_search_tree();
        ~binary_search_tree();
        bool push(const binary_search_tree_type& value);
        bool pop(const binary_search_tree_type& value);
        container_node* find(const binary_search_tree_type& value);
        void middle_order_traversal() const;
        size_t size() const;
    };
}
```

* **引用**：

#### 数据结构与性质

* 每个节点存储 `_data`，左子树值 < 当前值，右子树值 > 当前值（或使用 `function_policy` 定义的比较）。
* 不保证平衡，最坏情况可退化为链表。

#### 构造与析构

* 默认构造：`_root = nullptr;`。
* 析构：需要遍历整棵树释放所有节点；通常递归或迭代后序遍历删除。头文件可能在 `~binary_search_tree()` 实现中处理。

#### 插入 `bool push(const T& value)`

* **流程**

    1. 若 `_root == nullptr`，创建新节点 `_root = new node(value)`，`_data = value`，左右子树指向 nullptr，返回 `true`（首次插入）。
    2. 否则，从 `_root` 开始，通过 `function_policy(value, current->_data)` 判断走左或右：

        * 若小于当前节点值，则递归或迭代进入左子树；若左子树为空，创建新节点插入并返回 `true`；否则继续。
        * 若大于当前节点值，则同理右子树。
        * 若相等（取决实现），可认为已存在，插入失败返回 `false`，或允许重复插入取决需求；头文件实现需查看 `function_policy` 或设计。
* **返回值**：

    * `true`：插入成功。
    * `false`：值已存在或插入失败。
* **复杂度**

    * 平均 O(log n)（随机插入时），最坏 O(n)（退化链表）。
* **边界与错误**

    * 内存分配失败抛出 `customize_exception`；调用者可捕获或让程序终止。
* **示例**

  ```cpp
  tree_container::binary_search_tree<int> bst;
  bst.push(5);
  bst.push(3);
  bst.push(7);
  if(!bst.push(5)) {
      std::cout << "已存在 5，不插入重复项\n";
  }
  ```

#### 查找 `container_node* find(const T& value)`

* **流程**

    * 从 `_root` 出发，比较 `value` 与 `current->_data`：若相等，返回当前节点指针；若小于，进入左子树；若大于，进入右子树；直至叶节点或 nullptr。
* **返回值**

    * 若找到，返回指向节点的指针；否则返回 `nullptr`。
* **复杂度**：平均 O(log n)，最坏 O(n)。
* **示例**

  ```cpp
  auto node_ptr = bst.find(7);
  if(node_ptr) {
      std::cout << "找到值 7\n";
  }
  ```

#### 删除 `bool pop(const T& value)`

* **流程**

    1. 先查找目标节点及其父节点。
    2. 若节点不存在，返回 `false`。
    3. 若节点是叶节点，直接删除并将父指针置 `nullptr`。
    4. 若只有一个子节点，用子节点替代当前节点，delete 当前节点。
    5. 若有两个子节点，一般做：

        * 找到右子树的最小节点（或左子树最大节点）作为“后继”或“前驱”，将其值赋给当前节点，然后删除该后继节点（后继节点必无左子节点），或相应前驱逻辑。
    6. 返回 `true`。
* **复杂度**：平均 O(log n)，最坏 O(n)。
* **注意**

    * 删除节点时要确保正确维护父子指针。
    * 由于不平衡，删除后可能加剧失衡，影响后续操作性能；需谨慎，如果需平衡，考虑 AVL/RB 树。
* **示例**

  ```cpp
  if(bst.pop(3)) {
      std::cout << "删除 3 成功\n";
  } else {
      std::cout << "未找到 3\n";
  }
  ```

#### 遍历 `void middle_order_traversal() const`

* **中序遍历**：递归或非递归方式。
* 头文件示例使用迭代栈方式：

  ```cpp
  void interior_middle_order_traversal(container_node* node) {
      stack<container_node*> st;
      while(node != nullptr || !st.empty()) {
          while(node != nullptr) {
              st.push(node);
              node = node->_left;
          }
          node = st.top(); st.pop();
          std::cout << node->_data << " ";
          node = node->_right;
      }
  }
  void middle_order_traversal() const {
      interior_middle_order_traversal(_root);
  }
  ```

    * 引用：
* **前序/后序遍历**：若实现，可类比。
* **用途**：调试、打印、有序输出。

#### size() `size_t size() const`

* **实现**：可能在插入/删除时维护 `_size` 成员；若无，遍历整树计数，O(n)。
* **头文件**：查看 `size()` 实现细节，若递归或迭代统计节点数。
* **引用**：可见  中对 `_size()` 统计过程的示例（红黑树统计类似）。

---

### rb\_tree（红黑树）

**定义位置**：

```cpp
namespace tree_container
{
    template <typename rb_tree_type_key,
              typename rb_tree_type_value,
              typename key_extractor,  // 从 value 提取用于比较的 key
              typename Compare = template_container::imitation_functions::less<rb_tree_type_key>>
    class rb_tree
    {
    private:
        enum Color { red, black };
        struct container_node
        {
            rb_tree_type_value _data;
            container_node* _left;
            container_node* _right;
            container_node* _parent;
            Color _color;
            explicit container_node(const rb_tree_type_value& data);
            explicit container_node(rb_tree_type_value&& data) noexcept;
        };
        container_node* _root;
        Compare function_policy;
        key_extractor element;  // 提取 key：operator()(const value&) -> const key&
        // 可能有其他成员，如哨兵 nil 节点、size 统计等
    public:
        using iterator = rb_tree_iterator<...>;
        using const_iterator = rb_tree_iterator<...>;
        using reverse_iterator = rb_tree_reverse_iterator<iterator>;
        using const_reverse_iterator = rb_tree_reverse_iterator<const_iterator>;
        using return_pair_value = template_container::practicality::pair<iterator, bool>;
        rb_tree();
        explicit rb_tree(const rb_tree_type_value& data);
        explicit rb_tree(rb_tree_type_value&& data) noexcept;
        rb_tree(rb_tree&& data) noexcept;
        rb_tree(const rb_tree& data);
        ~rb_tree();
        return_pair_value push(const rb_tree_type_value& data);
        return_pair_value push(rb_tree_type_value&& data) noexcept;
        iterator pop(const rb_tree_type_value& key);
        container_node* find(const rb_tree_type_value& key) const;
        void middle_order_traversal() const;
        size_t size() const;
        // 其他辅助函数：旋转、修正颜色、平衡插入/删除逻辑
    };
}
```

* **引用**：

#### 红黑树性质

1. 每个节点或红或黑。
2. 根节点为黑。
3. 每个叶节点（nil 节点）为黑。
4. 若一个节点为红，则其子节点均为黑。
5. 对每个节点，从该节点到其所有叶子节点的简单路径上，均包含相同数目的黑节点。

这些性质保证树高度 O(log n)，插入/删除后通过旋转和重新着色修复性质。

#### 插入操作 `pair<iterator,bool> push(const V& data)`

* **查找插入位置**：与 BST 类似，根据 `key_extractor(data)` 提取 key，通过 `function_policy` 比较，定位插入叶子位置，创建新节点，初始颜色为红。

* **修正红黑性质**：插入新红节点可能破坏性质，需执行以下步骤（经典 CLRS 插入修正算法）：

    1. 若插入节点为根，直接着色为黑，完成。
    2. 若父节点为黑，无需调整，完成。
    3. 若父节点为红，需根据叔叔节点颜色和位置进行修正：

        * **情况1**：叔叔节点存在且为红。将父、叔叔着色为黑，祖父着色为红，将当前节点指向祖父，继续循环检查。
        * **情况2/3**：叔叔为黑或不存在，根据当前节点在父/祖父的左/右位置分为“外侧插入”或“内侧插入”：

            * 若为“内侧插入”，先对父进行旋转（左右旋转），转换为“外侧插入”情形，再执行下一步。
            * 对祖父进行相反方向旋转，并交换颜色：祖父变红，父变黑。
    4. 最后保证根为黑。

* **旋转操作**：

    * **左旋**（以 x 节点为中心）：

        * 设 y = x->\_right，将 y 取代 x 位置，x->\_right = y->\_left，若 y->\_left 不为空，其父指向 x，y->\_left 置为 x，x->\_parent 更新为 y，更新祖父指向 y。
        * 头文件可见 `rotate_left(container_node* x)` 实现，签名与实现严格对应。
        * 参见示意图：![RB 左旋前](images/rb_left_before.png) / ![RB 左旋后](images/rb_left_after.png)。
    * **右旋** 与左旋对称。

* **示意图引用**：

    * 左旋前后示意图：

      ```md
      ![](images/rb_left_before.png)  
      ![](images/rb_left_after.png)
      ```
    * 右旋前后示意图：

      ```md
      ![](images/rb_right_before.png)  
      ![](images/rb_right_after.png)
      ```
    * 确保上述图片路径正确。

* **返回值**

    * 返回 `pair<iterator, bool>`：`bool` 表示插入是否发生（若键已存在，可返回 false）；`iterator` 指向已插入或已存在节点。

* **复杂度**：O(log n) 时间，包括 BST 查找插入和插入后修正（旋转和重染色操作，常数次）。

* **边界与错误**：内存分配失败时抛出 `customize_exception`；插入重复键行为取决实现（通常不允许重复，直接返回对应 iterator 和 false）。

#### 删除操作 `iterator pop(const V& key)` 或 `bool pop(const V& key)`

* **查找待删除节点**：BST 查找定位目标节点，若不存在直接返回 end() 或 false。
* **删除流程**：

    1. 若节点有两个非空子节点，找到后继节点（右子树最小），将后继节点的数据复制到当前节点，然后删除后继节点（后继节点最多一个子节点），将删除问题转换为删除后继节点；否则直接删除。
    2. 实际删除时，若删除节点或其替代节点为黑色，删除会破坏红黑性质，需要执行删除修正算法：

        * 设 x 为替代节点（可能为 nullptr nil 节点）。
        * 若 x 或其子节点为红，可通过重新着色解决；否则通过复杂的“借兄弟”或“旋转”方案修正双重黑问题（CLRS 中 delete-fixup 算法）。
        * 旋转和重染色操作确保最终恢复红黑性质。
* **示意图**：可绘制删除及修正流程示意，如兄弟节点不同情形。
* **返回值**：按实现可能返回指向替代节点的 iterator，或 bool 表示成功；头文件具体签名需严格引用。
* **复杂度**：O(log n)。
* **边界**：删除根节点、叶子节点、仅有一个子节点或两个子节点情况均需考虑；若删除导致树空，应置 `_root = nullptr`。

#### 查找 `container_node* find(const V& key) const`

* 与 BST 查找类似，O(log n) 平均，O(n) 最坏（因红黑树保持平衡，实际最坏 O(log n)）。
* 返回指向节点或 nullptr。

#### 遍历 `void middle_order_traversal() const`

* 中序遍历输出有序序列。实现可类似 BST 中序遍历。
* **用途**：打印或导出有序元素，验证结构正确。

#### size() `size_t size() const`

* 可维护 `_size` 成员以 O(1) 返回当前节点数；若无，则每次遍历统计，O(n)。头文件中可能使用辅助函数 `_size()` 通过迭代器统计，成本 O(n)；若维护成员，更新插入/删除时增减，可 O(1)。
* **引用**：

#### 旋转示意与图解

* **左旋**：参见 AVL 左旋相似逻辑，但需额外颜色调整；示意图同前。
* **右旋**：对称。
* **伪代码**（摘自 CLRS，结合头文件实现顺序）：

  ```text
  rotate_left(x):
      y = x.right
      x.right = y.left
      if y.left != nil:
          y.left.parent = x
      y.parent = x.parent
      if x.parent == nil:
          root = y
      else if x == x.parent.left:
          x.parent.left = y
      else:
          x.parent.right = y
      y.left = x
      x.parent = y
  ```

  对于红黑树插入/删除修正，旋转后通常还需交换颜色等。
* **引用实现**：头文件中 `rotate_left(container_node* x)`, `rotate_right(container_node* x)` 等，签名严格按照头文件定义。

#### 复杂度与平衡性

* 插入/删除后修正保证树高度在 `2*log(n+1)` 内，故查找、插入、删除均 O(log n)。
* 空间：节点额外存储颜色位和父指针。

#### 边界与异常

* 内存分配失败需抛出异常并处理回滚。
* 旋转与修正过程中需保证指针正确指向；错误可能导致内存泄漏或非法访问。
* 多线程：非线程安全，若并发多线程修改同一树，需外部同步。

---

### AVL 树（若在头文件中有实现或对比说明）

头文件中若提供 AVL 树实现，可与红黑树对比。若无，可仅在文档中做对比说明：

* **AVL 树**：严格平衡，任何节点左右子树高度之差 ≤ 1；查询性能更优，插入/删除修正（旋转）更频繁。
* **红黑树**：相对松散的平衡条件，插入/删除较少旋转，维护成本稍低，适用于关联容器 STL。
* **示意图**：前面已生成 AVL 左旋/右旋示意图：

  ```md
  ![](images/avl_left_before.png)
  ![](images/avl_left_after.png)
  ![](images/avl_right_before.png)
  ![](images/avl_right_after.png)
  ```
* **旋转逻辑**：与红黑树旋转类似，但无需额外颜色调整，仅更新高度。
* **插入/删除修正**：需在每次插入/删除后，沿路径更新高度，若高度差超限，进行 LL、RR、LR、RL 四种旋转或双旋。
* **签名**：若有 `avl_tree` 类，函数 `push`, `pop`, `find`, `middle_order_traversal`, `pre_order_traversal`, `size` 等；具体签名请参照头文件。

> 若头文件无 AVL 实现，此处仅做理论对比，不生成不一致签名。

---

## 关联容器

### map\_container::tree\_map

**定义位置**：

```cpp
namespace map_container
{
    template <typename map_type_k, typename map_type_v, typename comparators = template_container::imitation_functions::less<map_type_k>>
    class tree_map
    {
        using key_val_type = template_container::practicality::pair<map_type_k,map_type_v>;
        struct key_val
        {
            const map_type_k& operator()(const key_val_type& key_value) { return key_value.first; }
        };
        using instance_rb = base_class_container::rb_tree<map_type_k, key_val_type, key_val, comparators>;
        instance_rb instance_tree_map;
    public:
        using iterator = typename instance_rb::iterator;
        using const_iterator = typename instance_rb::const_iterator;
        using reverse_iterator = typename instance_rb::reverse_iterator;
        using const_reverse_iterator = typename instance_rb::const_reverse_iterator;
        using map_iterator = template_container::practicality::pair<iterator,bool>;
        tree_map();
        ~tree_map() = default;
        tree_map(const tree_map& other);
        tree_map(tree_map&& other) noexcept;
        explicit tree_map(const key_val_type& data);
        explicit tree_map(key_val_type&& data) noexcept;
        tree_map(const std::initializer_list<key_val_type>& list);
        tree_map& operator=(const tree_map& other);
        tree_map& operator=(tree_map&& other) noexcept;
        tree_map& operator=(const std::initializer_list<key_val_type>& list);
        map_iterator push(const key_val_type& data);
        map_iterator push(key_val_type&& data) noexcept;
        map_iterator pop(const key_val_type& data);
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

#### 数据结构

* 内部使用 `rb_tree<map_type_k, key_val_type, key_val, comparators>`。
* `key_extractor` 为 `key_val`，通过 `operator()(pair)` 返回 `first` 作为用于比较的 key；value 存储在 `_data.second`。

#### 接口详解

1. **构造与析构**

    * 默认构造：创建空红黑树。
    * 拷贝/移动：对应复制或接管内部红黑树。
    * 从单元素或初始化列表构造：依次插入元素。
    * 析构：默认析构，内部 `rb_tree` 负责节点释放。
2. **插入 `map_iterator push(const key_val_type& data)`**

    * 调用内部 `instance_tree_map.push(data)`，若键不存在插入并返回 `<iterator,true>`，若已存在不插入返回 `<iterator,false>`。
    * **示例**

      ```cpp
      template_container::map_container::tree_map<int, std::string> m;
      auto [it, ok] = m.push({1, "one"});
      if(!ok) { /* 已存在键 1 */ }
      ```
    * **复杂度**：O(log n)。
3. **删除 `map_iterator pop(const key_val_type& data)`**

    * 删除指定键，对应内部 `rb_tree.pop(...)`，返回 iterator（可能特殊含义）。
    * **使用注意**：若键不存在，可能返回 end()；文档需说明其行为。
4. **查找 `iterator find(const key_val_type& data)`**

    * 内部 `rb_tree.find`：O(log n)。
    * **示例**

      ```cpp
      auto it = m.find({1, ""});
      if(it != m.end()) {
          std::cout << it->second;
      }
      ```
5. **访问或插入 `iterator operator[](const key_val_type& data)`**

    * 若键存在，返回对应 iterator；若不存在，插入新键，其 value 默构造或传入的 `data.second`？需参考实现：头文件签名为 `operator[](const key_val_type& tree_map_data)`，可能表示插入 data.second 或默认值；文档中应说明实际行为。
    * **引用**：请依据头文件实现逻辑说明。
6. **遍历**

    * `middle_order_traversal()`, `pre_order_traversal()`: 调用内部 `rb_tree` 对应遍历，输出键值对 `{key, value}`，以某种格式打印。
    * **示例**

      ```cpp
      m.middle_order_traversal(); // 以中序输出所有键值对
      ```
7. **大小与状态**

    * `size() const`: 返回元素数量。
    * `empty()`: 返回是否为空。
8. **迭代器**

    * `begin()/end()`, `cbegin()/cend()`, `rbegin()/rend()`, `crbegin()/crend()`: 支持范围 for、STL 兼容算法。
    * **迭代器类型**：内部 `rb_tree` 提供双向迭代器，可增量/减量访问下一个/上一个元素。
    * **失效规则**：插入/删除可能使迭代器失效；文档应说明。

#### 内部原理剖析

* 以红黑树组织元素，按 key 排序。
* 查找、插入、删除操作同红黑树逻辑，保证平衡。
* `value` 存储在节点中，与 key 一起。
* 迭代器通过中序遍历实现“下一个”指针，通常用栈或 parent 指针实现。

#### 复杂度

* 插入/删除/查找：O(log n)。
* 遍历：O(n)。
* 空间：O(n) 节点，节点额外存储 parent 指针、color、value、key。

#### 示例

```cpp
template_container::map_container::tree_map<std::string,int> dict;
dict.push({"apple", 5});
dict.push({"banana", 3});
auto it = dict.find({"apple",0});
if(it != dict.end()) {
    std::cout << "apple count: " << it->second << std::endl;
}
for(auto it2 = dict.begin(); it2 != dict.end(); ++it2) {
    std::cout << it2->first << " -> " << it2->second << std::endl;
}
dict.pop({"banana",0});
```

---

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

