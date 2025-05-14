

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
| `string(const char* s)` | 分配 `strlen(s)+1`，拷贝并 `