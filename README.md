###
####
# ⭐ MY_Template 自定义 STL 库 文档
> 本文档提供对 `MY_Template` 库中所有核心函数的 **实现逻辑**、**执行过程**、**返回值** 及 **使用示例**

---

## 🧩 仿函数模块 `Imitation_functions`

### 🔽 `less<T>`

```cpp
template<typename T>
class less {
public:
    bool operator()(const T& a, const T& b);
};
```

- **逻辑**：直接返回 `a < b`。
- **执行过程**：比较传入的两个参数，调用内置 `<` 运算符。
- **返回值**：`true` if `a < b`，否则 `false`。
- **用法**：
  ```cpp
  less<int> cmp;
  bool res = cmp(3, 5); // true 😊
  ```

### 🔼 `greater<T>`

```cpp
template<typename T>
class greater {
public:
    bool operator()(const T& a, const T& b);
};
```

- **逻辑**：返回 `a > b`。
- **返回值**：`true` if `a > b`，否则 `false`。
- **用法**：
  ```cpp
  greater<int> cmp;
  bool res = cmp(3, 5); // false 😢
  ```

---

## 🤝 实用工具 `Practicality`

### 🧷 `pair<T, K>`

```cpp
template<typename T, typename K>
class pair {
public:
    T first;
    K second;
    // 构造、拷贝、比较、输出操作符...
};
```

- **逻辑**：简单封装两个不同类型的值。
- **返回值**：构造函数返回对象本身，比较运算返回 `bool`。
- **示例**：
  ```cpp
  auto p = MY_Template::Practicality::make_pair(1, "apple"); // p.first=1, p.second="apple" 🍎
  std::cout << p; // (1:apple)
  ```

---

## 🔁 算法模块 `algorithm`

### 📋 `copy(begin, end, dest)`

```cpp
template<typename In, typename Out>
Out copy(In begin, In end, Out dest);
```

- **逻辑**：
  1. 从 `begin` 到 `end` 逐个读取。
  2. 将读到的值赋给 `*dest`，`++dest`。
- **执行过程**：
  - 初始化迭代器 `it = begin`。
  - 循环 `while(it != end) { *dest = *it; ++it; ++dest; }`。
- **返回值**：返回指向最后写入位置之后的迭代器 `dest`。
- **示例**：
  ```cpp
  std::vector<int> src = {1,2,3};
  std::vector<int> dst(3);
  auto it = MY_Template::algorithm::copy(src.begin(), src.end(), dst.begin());
  // dst = {1,2,3} 🎉
  ```

### 🔍 `find(begin, end, value)`

```cpp
template<typename In, typename T>
In find(In begin, In end, const T& value);
```

- **逻辑**：遍历区间，`*it == value` 则返回 `it`。
- **返回值**：匹配位置或 `end`。
- **示例**：
  ```cpp
  auto it = MY_Template::algorithm::find(src.begin(), src.end(), 2);
  if(it != src.end()) { /* found 👍 */ }
  ```

### 🔃 `swap(a, b)`

```cpp
template<typename T>
void swap(T& a, T& b);
```

- **逻辑**：通过临时变量交换 `a`、`b`。
- **示例**：
  ```cpp
  int x=1, y=2;
  MY_Template::algorithm::swap(x,y); // x=2, y=1 🔄
  ```

---

## 📄 字符串类 `string_Container::string`

- **成员变量**:
  - `char* _data`：字符缓冲区
  - `size_t _size`：当前长度
  - `size_t _capacity`：分配容量

### 🚀 主要方法

| 函数原型 | 逻辑 & 执行过程 | 返回值 | 示例 |
|---|---|---|---|
| `string(const char* s)` | 分配 `strlen(s)+1`，拷贝并以 "\0"结尾 | —构造 `string` 对象 | `string s("Hi");` |
| `push_back(char c)` | 若 `_size==_capacity` 扩容，否则在 `_data[_size] = c`，`_size++` | `string&` | `s.push_back('!'); // "Hi!" 😃` |
| `resize(n, c)` | 若 `n>_capacity` 扩容至 `n`，填充 `c`；否则截断 | `string&` | `s.resize(5, '-'); // "Hi!--"` |
| `rollback()` | 从末尾到头依次 `push_back`，构造逆序新串 | 新 `string` | `s.rollback(); // "!iH"` |
| `str_withdraw(pos)` | 拷贝 `_data+pos` 长度为 `_size-pos` 的子串 | 新 `string` | `s.str_withdraw(1); // "i!"` |
| `operator+`/`+=` | 分别创建新串或就地拼接 | `string` / `string&` | `s = s + "!!"; // "Hi!!!"` |

---

## 📦 动态数组 `vector_Container::vector<T>`

- **核心指针**：
  - `_data_pointer`, `_size_pointer`, `_capacity_pointer`

### ✨ 方法详解

| 函数 | 逻辑步骤 | 返回值 | 示例 |
|---|---|---|---|
| `vector(size, val)` | 分配 `size`，所有元素设为 `val` | 构造 `vector` | `vector<int> v(3,0); // {0,0,0}` |
| `push_back(val)` | 若满则 `resize(2*capacity)`，`*(_size_pointer) = val; ++_size_pointer` | `vector&` | `v.push_back(1); // {...,1}` |
| `pop_back()` | `if(size()>0) --_size_pointer` | `vector&` | `v.pop_back();` |
| `push_front(val)` | `push_back` 扩容后，元素后移 `for(i=size; i>0; --i) data[i]=data[i-1]`,插入 | `vector&` | `v.push_front(9);` |
| `erase(pos)` | 覆盖后续元素 `for(it=pos+1; it!=end; ++it) *(it-1)=*it`，`--_size_pointer` | 下一位置迭代器 | `v.erase(v.begin()+2);` |
| `operator[]` | 直接 `data[idx]` | `T&` 或 `const T&` | `int x = v[0];` |

---

## 🔁 链表 `list_Container::list<T>`

- **节点**：含 `_prev`, `_next`, `_data`，循环双向，哨兵 `_head`。

### 📝 典型操作

| 函数 | 逻辑 & 步骤 | 返回值 | 示例 |
|---|---|---|---|
| `push_back(val)` | `insert(end(), val)` | `void` | `lst.push_back(5);` |
| `push_front(val)` | 同理 `insert(begin(), val)` | `void` | `lst.push_front(1);` |
| `insert(pos, val)` | 新建 `Node`，链接 `prev->new->pos` | `iterator` | `it = lst.insert(it, 2);` |
| `erase(pos)` | 调整前后链接，`delete node` | `iterator` of next | `lst.erase(it);` |
| `pop_back()/pop_front()` | 调用 `erase(--end())` / `erase(begin())` | `void` |
| `clear()` | 循环删除直到回到哨兵 | `void` |

---

## 📚 栈适配器 `stack_Adapter::stack<T>`

- **基于**：可选容器，默认 `vector<T>`。
- **主要接口**：
  - `push(val)`, `pop()`, `top()`, `empty()`, `size()`
- 🎈 用法：
  ```cpp
  MY_Template::stack_Adapter::stack<int> st;
  st.push(10);
  int x = st.top(); // 10
  st.pop();
  ```

---

## 🚦 队列适配器 & 优先队列 `queue_Adapter`

### 普通队列 `queue<T>`

- **容器**：默认 `list<T>`。
- **接口**：`push`, `pop`, `front`, `back`, `empty`, `size`

### 优先队列 `priority_queue<T>`

- **内部**：`vector<T>` + 堆调整。
- **核心逻辑**：
  - `push`: `push_back` 后 `Adjust_upwards(idx)` 上浮；
  - `pop`: 交换顶尾，`pop_back`，`Adjust_downwards(0)` 下沉。
- **示例**：
  ```cpp
  MY_Template::queue_Adapter::priority_queue<int> pq = {3,1,4};
  pq.push(2);
  int top = pq.top(); // 4 🎯
  ```

---

## 🌳 树结构 `Tree_Container`

### 1️⃣ `BS_Tree`（二叉搜索树）

- **核心成员**：`Node* _ROOT`, `com` 比较器
- **主要函数**:

| 函数 | 逻辑步骤 | 返回值 | 示例 |
|---|---|---|---|
| `push(val)` | 从根开始，根据 `com` 左/右遍历直到 `nullptr`，插入新节点 | `bool` 是否插入成功 | `bst.push(5);` |
| `pop(val)` | 查找节点；若有 0/1 子树，直代替；2 子树，用右子树最左替换，然后删 | `BS_Tree&` 链式 | `bst.pop(5);` |
| `find(val)` | 从根遍历左右，返回 `Node*` 或 `nullptr` | `Node*` | `auto n=bst.find(3);` |
| `Middle_order_traversal()` | 借助 `stack` 迭代输出中序 | `void` |
| `size()` | 中序计数 | `size_t` |

### 2️⃣ `AVL_Tree`（平衡树）

- **成员**：`_Balance_factor` 跟踪节点平衡
- **插入**：BST 插入后，从新节点向上更新平衡，若失衡则 LL/RR/LR/RL 旋转修复。
- **示例**：
  ```cpp
  MY_Template::Tree_Container::AVL_Tree<int,int> avl;
  avl.push(10);
  avl.push(20);
  avl.push(30); // 触发单旋转 🔄
  ```

---

> 🚀 **祝你阅读愉快，Happy Coding!** 🎉
