⭐ MY\_Template 自定义 STL 库 详细文档

## 🔣 仿函数模块 `Imitation_functions`

```cpp
namespace Imitation_functions {
    template<typename T>
    class less {
    public:
        bool operator()(const T& a, const T& b) { return a < b; }
    };
    template<typename T>
    class greater {
    public:
        bool operator()(const T& a, const T& b) { return a > b; }
    };
    class Hash_Imitation_functions {
    public:
        size_t operator()(int x) { return static_cast<size_t>(x); }
        size_t operator()(size_t x) { return x; }
        size_t operator()(char x) { return static_cast<size_t>(x); }
        size_t operator()(double x) { return static_cast<size_t>(x); }
    };
}
```

| 签名                                               | 说明         | 返回值      | 示例                    |
| ------------------------------------------------ | ---------- | -------- | --------------------- |
| `bool less<T>::operator()(const T&, const T&)`   | 调用内置 `<`   | `bool`   | `less<int>()(a,b)`    |
| `bool greater<T>::operator()(const T&,const T&)` | 调用内置 `>`   | `bool`   | `greater<int>()(a,b)` |
| `size_t operator()(int)`                         | 返回 `x`     | `size_t` | `hf(42)`              |
| `size_t operator()(char)`                        | 返回 ASCII 值 | `size_t` | `hf('A')`             |

---

## 🧷 工具模块 `Practicality`

```cpp
namespace Practicality {
    template<typename T,typename K>
    class pair {
    public:
        T first; K second;
        pair(const T& a,const K& b):first(a),second(b){}
        bool operator==(const pair& p) const { return first==p.first&&second==p.second; }
        friend std::ostream& operator<<(std::ostream& os,const pair& p){ return os<<"("<<p.first<<":"<<p.second<<")"; }
    };
    template<typename T,typename K>
    pair<T,K> make_pair(const T& a,const K& b){ return pair<T,K>(a,b); }
}
```

| 成员 / 函数                                     | 说明                      | 返回值         | 示例                 |
| ------------------------------------------- | ----------------------- | ----------- | ------------------ |
| `pair(const T&,const K&)`                   | 构造并初始化 `first`、`second` | `pair<T,K>` | `make_pair(1,"a")` |
| `bool operator==(const pair&)`              | 成员相等比较                  | `bool`      | `p1==p2`           |
| `ostream& operator<<(ostream&,const pair&)` | 流输出                     | `ostream&`  | `cout<<p`          |
| `make_pair(const T&,const K&)`              | 简便构造                    | `pair<T,K>` | `make_pair(2,"b")` |

---

## 🔁 算法模块 `algorithm`

```cpp
namespace algorithm {
    template<typename In,typename Out>
    Out copy(In b,In e,Out d){ while(b!=e){ *d=*b; ++b;++d;} return d; }
    template<typename In,typename T>
    In find(In b,In e,const T& v){ while(b!=e&&*b!=v) ++b; return b; }
    template<typename T>
    void swap(T& a,T& b){ T t=a;a=b;b=t; }
    template<typename T,typename HF>
    class Hash_function {
    public:
        size_t Hash_SDBMHash(const T& x);
        size_t Hash_BKDRHash(const T& x);
        size_t Hash_DJBHash(const T& x);
        size_t Hash_APHash(const T& x);
        size_t Hash_PJWHash(const T& x);
    };
}
```

| 函数                     | 说明           | 返回值      | 示例                                  |
| ---------------------- | ------------ | -------- | ----------------------------------- |
| `copy(In,In,Out)`      | 线性复制         | `Out`    | `copy(a.begin(),a.end(),b.begin())` |
| `find(In,In,const T&)` | 查找等于 `v` 的元素 | `In`     | `find(a.begin(),a.end(),x)`         |
| `swap(T&,T&)`          | 交换两值         | —        | `swap(x,y)`                         |
| 各哈希函数                  | 依据相应位运算生成哈希  | `size_t` | `hf.Hash_SDBMHash(s)`               |

---

## 📄 字符串容器 `string_Container::string`

```cpp
namespace string_Container {
    class string {
    private:
        char* _data; size_t _size,_capacity;
    public:
        string(const char* s="");
        string(const string&);
        string(string&&);
        ~string();
        string& push_back(char);
        string& push_back(const char*);
        string& resize(size_t,char='\0');
        string& reserve(size_t);
        string& swap(string&);
        string rollback()const;
        string str_withdraw(size_t)const;
        char& operator[](size_t);
        string& operator+=(const string&);
        friend std::ostream& operator<<(std::ostream&,const string&);
    };
}
```

| 方法                       | 说明            | 返回值        | 示例                  |
| ------------------------ | ------------- | ---------- | ------------------- |
| 构造/拷贝/移动/析构              | 资源分配、复制、移动、释放 | —          | `string("hi")`      |
| `push_back(char)`        | 尾插字符，必要时扩容    | `string&`  | `s.push_back('a')`  |
| `push_back(const char*)` | 插入 C-串        | `string&`  | `s.push_back("bc")` |
| `resize(n,c)`            | 调整长度，填充或截断    | `string&`  | `s.resize(5,'-')`   |
| `reserve(n)`             | 保证容量          | `string&`  | `s.reserve(20)`     |
| `swap(other)`            | 交换内部指针和元数据    | `string&`  | `s.swap(t)`         |
| `rollback()`             | 逆序返回新串        | `string`   | `s.rollback()`      |
| `str_withdraw(pos)`      | 提取子串          | `string`   | `s.str_withdraw(2)` |
| `operator[](i)`          | 下标访问          | `char&`    | `s[0]`              |
| `operator+=(rhs)`        | 拼接字符串         | `string&`  | `s1+=s2`            |
| `operator<<`             | 输出            | `ostream&` | `cout<<s`           |

---

## 📦 动态数组 `vector_Container::vector<T>`

```cpp
namespace vector_Container {
    template<typename T>
    class vector {
    private:
        T* _data; size_t _size,_capacity;
    public:
        vector();
        vector(size_t n,const T& v);
        vector(std::initializer_list<T>);
        ~vector();
        void push_back(const T&);
        void pop_back();
        void push_front(const T&);
        void pop_front();
        iterator erase(iterator);
        void resize(size_t,const T&);
        void swap(vector&);
        vector& operator+=(const vector&);
        T& operator[](size_t);
        size_t size()const;
        size_t capacity()const;
    };
}
```

| 方法           | 说明          | 返回值        | 示例                |
| ------------ | ----------- | ---------- | ----------------- |
| 构造/析构        | 初始化、释放      | —          | `vector<int> v;`  |
| `push_back`  | 尾插          | `void`     | `v.push_back(5)`  |
| `pop_back`   | 删除尾         | `void`     | `v.pop_back()`    |
| `push_front` | 头插          | `void`     | `v.push_front(1)` |
| `pop_front`  | 删除头         | `void`     | `v.pop_front()`   |
| `erase`      | 删除指定位置      | `iterator` | `v.erase(it)`     |
| `resize`     | 调整大小并填充/截断  | `void`     | `v.resize(10,0)`  |
| `swap`       | 交换内容        | `void`     | `v.swap(u)`       |
| `operator+=` | 拼接两个 vector | `vector&`  | `v+=u`            |
| `operator[]` | 随机访问        | `T&`       | `v[0]`            |

---

## 🔗 链表 `list_Container::list<T>`

```cpp
namespace list_Container {
    template<typename T>
    class list {
    private:
        struct Node{ Node* prev; Node* next; T data; };
        Node* _head;
    public:
        list();
        ~list();
        void push_back(const T&);
        void push_front(const T&);
        void pop_back();
        void pop_front();
        iterator insert(iterator,const T&);
        iterator erase(iterator);
        void clear();
        void resize(size_t,const T&);
        list& operator+=(const list&);
        size_t size()const;
    };
}
```

| 方法           | 说明       | 返回值        | 示例                |
| ------------ | -------- | ---------- | ----------------- |
| 构造/析构        | 初始化哨兵、释放 | —          | `list<int> l;`    |
| `push_back`  | 尾插节点     | `void`     | `l.push_back(1)`  |
| `push_front` | 头插节点     | `void`     | `l.push_front(0)` |
| `pop_back`   | 删除尾节点    | `void`     | `l.pop_back()`    |
| `pop_front`  | 删除头节点    | `void`     | `l.pop_front()`   |
| `insert`     | 在迭代器前插   | `iterator` | `l.insert(it,2)`  |
| `erase`      | 删除迭代器处节点 | `iterator` | `l.erase(it)`     |
| `clear`      | 清空全部节点   | `void`     | `l.clear()`       |
| `resize`     | 增减节点并填充值 | `void`     | `l.resize(3,5)`   |
| `operator+=` | 合并两链表    | `list&`    | `l1+=l2`          |

---

## 🌳 二叉搜索树 `Tree_Container::BS_Tree<T>`

```cpp
namespace Tree_Container {
    template<typename T,typename Compare>
    class BS_Tree {
    private:
        struct Node{ T data; Node* left; Node* right; }* _root;
        size_t _size; Compare _comp;
    public:
        BS_Tree();~BS_Tree();
        bool push(const T&);
        bool pop(const T&);
        Node* find(const T&);
        void Middle_order_traversal()const;
        size_t size()const;
    };
}
```

| 方法                       | 说明     | 返回值      | 示例                             |
| ------------------------ | ------ | -------- | ------------------------------ |
| `push`                   | BST 插入 | `bool`   | `bst.push(5)`                  |
| `pop`                    | 删除节点   | `bool`   | `bst.pop(5)`                   |
| `find`                   | 查找节点   | `Node*`  | `bst.find(3)`                  |
| `Middle_order_traversal` | 中序遍历   | `void`   | `bst.Middle_order_traversal()` |
| `size`                   | 返回节点数  | `size_t` | `bst.size()`                   |

---

## 🌳 平衡红黑树 `Tree_Container::RB_Tree<T>`

```cpp
namespace Tree_Container {
    template<typename T,typename Compare>
    class RB_Tree {
    private:
        enum Color{RED,BLACK};
        struct Node{ T data; }* _root;
        size_t _size; Compare _comp;
    public:
        RB_Tree();~RB_Tree();
        bool push(const T&);
        bool pop(const T&);
        Node* find(const T&)const;
        void Middle_order_traversa()const;
        size_t size()const;
    };
}
```

| 方法                          | 说明        | 返回值      | 示例                        |
| --------------------------- | --------- | -------- | ------------------------- |
| `push(const T&)`          | 插入并修正红黑性质 | `bool`   | `rbt.push(10)`          |
| `pop(const T&)`           | 删除并修正红黑性质 | `bool`   | `rbt.pop(5)`            |
| `find(const T&) const`      | 查找节点      | `Node*`  | `rbt.find(20)`            |
| `Middle_order_traversal() const` | 中序遍历      | `void`   | `rbt.Middle_order_traversa()` |
| `size() const`              | 返回节点数     | `size_t` | `rbt.size()`              |

---

## 🗄️ 哈希表 `Hash_table<Key,Value,HF>`

```cpp
template<typename Key,typename Value,typename HF>
class Hash_table {
private:
    using Bucket=std::list<Practicality::pair<Key,Value>>;
    std::vector<Bucket> _buckets;
    size_t _size; float _max_load;
    HF _hash;
    void check_and_rehash();
public:
    Hash_table(size_t bc=16,float ml=0.75f);
    bool insert(const Key&,const Value&);
    bool erase(const Key&);
    Value* find(const Key&);
    void rehash(size_t);
    size_t size()const;
    float load_factor()const;
};
```

| 方法                           | 说明                | 返回值      | 示例                        |
| ---------------------------- | ----------------- | -------- | ------------------------- |
| 构造(bucket\_count, max\_load) | 初始化桶与负载阈值         | —        | `Hash_table<int,int> ht;` |
| `insert(key,value)`          | 链式插入并重哈希          | `bool`   | `ht.insert(1,100)`        |
| `erase(key)`                 | 删除键对应元素           | `bool`   | `ht.erase(1)`             |
| `Value* find(key)`           | 返回元素指针或 `nullptr` | `Value*` | `auto v=ht.find(2)`       |
| `rehash(new_bucket_count)`   | 重构桶并重分布元素         | `void`   | `ht.rehash(32)`           |
| `size() const`               | 返回元素数             | `size_t` | `ht.size()`               |
| `load_factor() const`        | 计算当前负载            | `float`  | `ht.load_factor()`        |

---

## 🧮 基类容器：BitSet `bitset_Container::BitSet<N>`

```cpp
namespace bitset_Container {
    template<size_t N>
    class BitSet {
    private:
        std::array<bool,N> _bits;
    public:
        void set(size_t i);
        void reset(size_t i);
        void flip(size_t i);
        bool test(size_t i)const;
        size_t count()const;
        size_t size()const;
        std::string to_string()const;
    };
}
```

| 方法            | 说明     | 返回值      | 示例               |
| ------------- | ------ | -------- | ---------------- |
| `set(i)`      | 置位     | `void`   | `bs.set(3)`      |
| `reset(i)`    | 清位     | `void`   | `bs.reset(3)`    |
| `flip(i)`     | 翻转位    | `void`   | `bs.flip(3)`     |
| `test(i)`     | 读取位    | `bool`   | `bs.test(3)`     |
| `count()`     | 统计为1位数 | `size_t` | `bs.count()`     |
| `size()`      | 返回 N   | `size_t` | `bs.size()`      |
| `to_string()` | 二进制字符串 | `string` | `bs.to_string()` |

---

## 🛠️ 无序关联容器：unordered\_map 与 unordered\_set

```cpp
namespace unordered_map_Container {
    template<typename Key,typename Value,typename Hash,typename Eq>
    class unordered_map {
    private:
        Hash_table<Key,Value,Hash> _ht;
    public:
        std::pair<typename Hash_table<Key,Value,Hash>::Bucket::iterator,bool> insert(const std::pair<Key,Value>&);
        size_t erase(const Key&);
        typename Hash_table<Key,Value,Hash>::Bucket::iterator find(const Key&);
        Value& operator[](const Key&);
        void rehash(size_t);
        size_t size()const;
        float load_factor()const;
    };
}
namespace unordered_set_Container {
    template<typename Key,typename Hash,typename Eq>
    class unordered_set {
    private:
        Hash_table<Key,bool,Hash> _ht;
    public:
        std::pair<typename Hash_table<Key,bool,Hash>::Bucket::iterator,bool> insert(const Key&);
        size_t erase(const Key&);
        typename Hash_table<Key,bool,Hash>::Bucket::iterator find(const Key&);
        void rehash(size_t);
        size_t size()const;
        float load_factor()const;
    };
}
```

| 方法                | 说明                   | 返回值             | 示例                   |
| ----------------- | -------------------- | --------------- | -------------------- |
| `insert`          | 调用 `_ht.insert`      | `pair<it,bool>` | `um.insert({1,"a"})` |
| `erase(key)`      | 调用 `_ht.erase`       | `size_t`        | `um.erase(1)`        |
| `find(key)`       | 调用 `_ht.find`返回桶迭代器  | `iterator`      | `um.find(2)`         |
| `operator[](key)` | 不存在则插入默认构造`Value()`  | `Value&`        | `um[3]="c"`          |
| `rehash(n)`       | 调用 `_ht.rehash`      | `void`          | `um.rehash(32)`      |
| `size()`          | 调用 `_ht.size`        | `size_t`        | `um.size()`          |
| `load_factor()`   | 调用 `_ht.load_factor` | `float`         | `um.load_factor()`   |

---

## 🗺️ 关联容器：map 与 set

```cpp
namespace map_Container {
    template<typename Key,typename Value,typename Compare,typename HF>
    class map {
    private:
        RB_Tree<Practicality::pair<const Key,Value>,Compare> _tree;
    public:
        std::pair<typename RB_Tree<Practicality::pair<const Key,Value>,Compare>::Node*,bool> insert(const Practicality::pair<const Key,Value>&);
        size_t erase(const Key&);
        typename RB_Tree<Practicality::pair<const Key,Value>,Compare>::Node* find(const Key&);
        Value& operator[](const Key&);
        void clear();
        size_t size()const;
    };
}
namespace set_Container {
    template<typename Key,typename Compare,typename HF>
    class set {
    private:
        RB_Tree<Key,Compare> _tree;
    public:
        std::pair<typename RB_Tree<Key,Compare>::Node*,bool> insert(const Key&);
        size_t erase(const Key&);
        typename RB_Tree<Key,Compare>::Node* find(const Key&);
        void clear();
        size_t size()const;
    };
}
```

| 方法                | 说明      | 返回值                | 示例                  |
| ----------------- | ------- | ------------------ | ------------------- |
| `insert(pair)`    | 红黑树插入   | `pair<Node*,bool>` | `m.insert({1,"a"})` |
| `erase(key)`      | 红黑树删除   | `size_t`           | `m.erase(1)`        |
| `find(key)`       | 红黑树查找   | `Node*`            | `m.find(2)`         |
| `operator[](key)` | 插入并返回引用 | `Value&`           | `m[3]="c"`          |
| `clear()`         | 清空所有节点  | `void`             | `m.clear()`         |
| `size() const`    | 返回元素数   | `size_t`           | `m.size()`          |

---

## 🔍 布隆过滤器 `Bloom_filter<Key,HF>`

```cpp
template<typename Key,typename HF>
class Bloom_filter {
private:
    std::vector<bool> _bits;
    size_t _k_hashes;
    HF _hash;
public:
    Bloom_filter(size_t size,size_t k);
    void add(const Key&);
    bool contains(const Key&)const;
    void clear();
};
```

| 方法                    | 说明            | 返回值    | 示例                                |
| --------------------- | ------------- | ------ | --------------------------------- |
| 构造(size,k)            | 初始化位数组与哈希函数数量 | —      | `Bloom_filter<string> b(1024,3);` |
| `add(key)`            | k 次哈希并置位      | `void` | `b.add("x")`                      |
| `contains(key) const` | 检查所有位         | `bool` | `b.contains("y")`                 |
| `clear()`             | 重置所有位         | `void` | `b.clear()`                       |

---

## 🗂️ 适配器模块

```cpp
namespace stack_Adapter {
    template<typename T>
    class stack {
    private: vector_Container::vector<T> _con;
    public:
        void push(const T&);
        void pop();
        T& top();
        bool empty()const;
        size_t size()const;
    };
}
namespace queue_Adapter {
    template<typename T>
    class queue {
    private: list_Container::list<T> _con;
    public:
        void push(const T&);
        void pop();
        T& front();
        T& back();
        bool empty()const;
        size_t size()const;
    };
}
namespace priority_queue_Adapter {
    template<typename T,typename Compare>
    class priority_queue {
    private: vector_Container::vector<T> _con; Compare _comp;
    public:
        void push(const T&);
        void pop();
        const T& top()const;
        bool empty()const;
        size_t size()const;
    };
}
```

| 容器                  | 方法           | 说明                 | 返回值             | 示例           |
| ------------------- | ------------ | ------------------ | --------------- | ------------ |
| `stack<T>`          | `push`       | `con.push_back`    | `void`          | `st.push(1)` |
|                     | `pop`        | `con.pop_back`     | `void`          | `st.pop()`   |
|                     | `top`        | `con.back`         | `T&`            | `st.top()`   |
|                     | `empty/size` | 底层尺寸判断             | `bool`/`size_t` | `st.empty()` |
| `queue<T>`          | `push`       | `con.push_back`    | `void`          | `q.push(2)`  |
|                     | `pop`        | `con.pop_front`    | `void`          | `q.pop()`    |
|                     | `front/back` | `con.front/back`   | `T&`            | `q.front()`  |
| `priority_queue<T>` | `push`       | `con.push_back`+上浮 | `void`          | `pq.push(3)` |
|                     | `pop`        | `swap首尾`+下沉        | `void`          | `pq.pop()`   |
|                     | `top`        | `con.front`        | `const T&`      | `pq.top()`   |

---

> 🚀 **祝您阅读愉快，Happy Coding!** 🎉
