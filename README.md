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
namespace bitset_Container 
{
    template <typename Hash_Table_Type_Key, typename Hash_Table_Type_Val,typename Hash_Table_Functor,typename Type_imitation_function = std::hash<Hash_Table_Type_Val> >
    class Hash_Table
    {
        class Hash_Table_Node
        {
        public:
            Hash_Table_Type_Val _data;
            Hash_Table_Node* _next;
            Hash_Table_Node* Link_prev;
            //全局链表指针，方便按照插入的顺序有序遍历哈希表
            Hash_Table_Node* Link_next;
            Hash_Table_Node(const Hash_Table_Type_Val& Temp_Val)
            {
                _data = Temp_Val;
                _next = nullptr;
                Link_prev = nullptr;
                Link_next = nullptr;
            }
        };
        using Node = Hash_Table_Node;
        Hash_Table_Functor _Hash_Functor;                           //仿函数
        size_t _size;                                               //哈希表大小
        size_t Load_factor;                                         //负载因子   
        size_t Capacity;                                            //哈希表容量
        MY_Template::vector_Container::vector<Node*> _Hash_Table;   //哈希表
        Type_imitation_function _Type_imitation_function;           //哈希函数
        Node* _previous_data = nullptr;                             //上一个数据
        Node* _Head_data = nullptr;                                 //插入头数据
    public:
        using iterator = Hash_iterator<Hash_Table_Type_Key,Hash_Table_Type_Val>;
        using const_iterator = Hash_iterator<const Hash_Table_Type_Key,const Hash_Table_Type_Val>;
        bool Change_Load_factor(const size_t& Temp_Load_factor);
        iterator operator[](const Hash_Table_Type_Key& Temp_Key);
        iterator begin()；                   
        const_iterator cbegin()；      
        iterator end()；                      
        const_iterator cend()；        
        size_t size()；                                       
        bool   empty()；                      
        size_t capacity()；
        bool push (const Hash_Table_Type_Val& Temp_Val)；
        bool pop(const Hash_Table_Type_Val& Temp_Val)；
        iterator find(const Hash_Table_Type_Val& Temp_Val)；                              
    };
}
```

| 方法                           | 说明                | 返回值      | 示例                        |
| ---------------------------- | ----------------- | -------- | ------------------------- |
| `push(Hash_Table_Type_Val)`          | 插入并重哈希          | `bool`   | `ht.insert(1,100)`        |
| `pop(Hash_Table_Type_Val)`                 | 删除键对应元素           | `bool`   | `ht.erase(1)`             |
| `Value* find(Hash_Table_Type_Val)`           | 返回元素指针或 `nullptr` | `Value*` | `auto v=ht.find(2)`       |
| `rehash(new_bucket_count)`   | 重构桶并重分布元素         | `void`   | `ht.rehash(32)`           |
| `size()`               | 返回元素数             | `size_t` | `ht.size()`               |
| `load_factor() const`        | 计算当前负载            | `float`  | `ht.load_factor()`        |

---
## 🧮 基类容器：BitSet `bitset_Container::BitSet`

```cpp
namespace bitset_Container 
{
    class BitSet 
    {
        MY_Template::vector_Container::vector<int> _BitSet;
        size_t _size;
    public:
        BitSet();
        BitSet(const size_t& Temp_size);
        BitSet(const BitSet& BitMap_Temp);
        BitSet& operator=(const BitSet& BitMap_Temp);
        void resize(const size_t& Temp_size);
        void set(const size_t& Temp_Val);
        void reset(const size_t& Temp_Val);
        bool test(const size_t& Temp_Val);
        size_t size();
    };
}
```

| 方法                | 说明                   | 返回值      | 示例                   |
| ----------------- | --------------------  | -------- | -------------------- |
| `BitSet()`        | 默认构造函数              | —        | `BitSet bs;`         |
| `BitSet(size_t)`  | 指定大小构造              | —        | `BitSet bs(100);`    |
| `BitSet(const BitSet&)` | 拷贝构造函数           | —        | `BitSet bs2(bs1);`   |
| `operator=(const BitSet&)` | 赋值操作符         | `BitSet&` | `bs2 = bs1;`         |
| `resize(size_t)`  | 重新设置大小              | `void`    | `bs.resize(200);`    |
| `set(size_t)`     | 置位                    | `void`    | `bs.set(3);`         |
| `reset(size_t)`   | 清位                    | `void`    | `bs.reset(3);`       |
| `test(size_t)`    | 测试某一位是否为真          | `bool`    | `bs.test(3);`        |
| `size()`          | 返回元素个数              | `size_t`  | `bs.size();`         |

---

## 🛠️ 无序关联容器：unordered\_map 与 unordered\_set

```cpp
namespace unordered_map_Container {
    template <typename unordered_Map_Type_K,typename unordered_Map_Type_V>
    class unordered_map 
    {
        using Key_Val_Type = MY_Template::Practicality::pair<unordered_Map_Type_K,unordered_Map_Type_V>;
        struct Key_Val
        {
            const unordered_Map_Type_K& operator()(const Key_Val_Type& Temp_Key_)
            {
                return Temp_Key_.first;
            }
        };
        class Hash_Functor
        {
        public:
            size_t operator()(const Key_Val_Type& Temp_Key_)
            {
                size_t num_One =  MY_Template::Imitation_functions::Hash_Imitation_functions()(Temp_Key_.first);
                num_One = num_One * 31;
                size_t num_Two =  MY_Template::Imitation_functions::Hash_Imitation_functions()(Temp_Key_.second);
                num_Two = num_Two * 31;
                return (num_One + num_Two);
            }
        };
        using Hash_Table = Base_Class_Container::Hash_Table<unordered_Map_Type_K,Key_Val_Type,Key_Val,Hash_Functor>;
        Hash_Table _Hash_Map;
    public:
        using iterator = typename Hash_Table::iterator;
        using const_iterator = typename Hash_Table::const_iterator;
        bool push(const Key_Val_Type& Temp_Key_)；
        bool pop(const Key_Val_Type& Temp_Key_)；
        iterator find(const Key_Val_Type& Temp_Key_);
        size_t size();
        size_t capacity();
        bool empty()；                                        
        iterator begin()；                                    
        iterator end()；                                      
        const_iterator cbegin()；                             
        const_iterator cend()；                               
        iterator operator[](const Key_Val_Type& Temp_Key_) 
    };
}
namespace unordered_set_Container 
{
    template <typename unordered_Set_Type_K>
    class unordered_Set
    {
        using Key_Val_Type = unordered_Set_Type_K;
        class Hash_Functor
        {
        public:
            size_t operator()(const Key_Val_Type& Temp_Key_)
            {
                return MY_Template::Imitation_functions::Hash_Imitation_functions()(Temp_Key_)* 131;
            }
        };
        class Key_Val
        {
        public:
            const Key_Val_Type& operator()(const Key_Val_Type& Temp_Key_)
            {
                return Temp_Key_;
            }
        };
        using Hash_Table = MY_Template::Base_Class_Container::Hash_Table<unordered_Set_Type_K,Key_Val_Type,Key_Val,Hash_Functor>;
        Hash_Table _Hash_Set;
    public:
        bool push(const Key_Val_Type& Set_Temp)；            
        bool pop(const Key_Val_Type& Set_Temp)；           
        iterator find(const Key_Val_Type& Set_Temp);        
        size_t size();                                       
        bool empty();                                                                                                     
        size_t capacity();                     
        iterator begin();                                    
        iterator end();                                      
        const_iterator cbegin();                             
        const_iterator cend();                               
        iterator operator[](const Key_Val_Type& Set_Temp);     
    };
}
```

| 方法                | 说明                   | 返回值             | 示例                   |
| ----------------- | --------------------    | --------------- | -------------------- |
| `push(key)`            | 调用 `_Hash_.push()`      | `bool`          | `Set_test.push(1)` |
| `pop(key)`        | 调用 `_Hash_.pop()`       | `bool`          | `Set_test.pop(1)`        |
| `find(key)`       | 调用 `_Hash_.find()`  | `iterator`       | `Set_test.find(2)`         |
| `operator[](key)` | 不存在则返回默认构造`iterator(nullptr)`  | `iterator`        | `Set_test[3]="c"`          |
| `capacity())`     | 调用 `_Hash_.capacity()`      | `size_t`          | `Set_test.capacity()`      |
| `size()`          | 调用 `_Hahs_.size()`        | `size_t`        | `Set_test.size()`          |
| `empty()`   | 调用 `_Hash_.empty()` | `bool`         | `Set_test.emptyr()`   |
| `begin()`  | 调用 `_Hash_.begin()` | `iterator` | `Set_test.begin()` |
| `end()`  | 调用 `_Hash_.end()` | `iterator` | `Set_test.end()` |
| `cbegin()`  | 调用 `_Hash_.cbegin()` | `const_iterator` | `Set_test.cbegin()` |
| `cend()`  | 调用 `_Hash_.cend()` | `const_iterator` | `Set_test.cend()` |

## 🗺️ 关联容器：map 与 set

```cpp
namespace map_Container {
    template <typename Map_Type_K, typename Map_Type_V>
    class Map
    {
        using Key_Val_Type = MY_Template::Practicality::pair<Map_Type_K, Map_Type_V>;
        struct Key_Val
        {
            /* 仿函数，返回比较的值 */
            const Map_Type_K& operator()(const Key_Val_Type& Temp_Key_)
            {
                return Temp_Key_.first;
            }
        };
        using RB_TREE = Base_Class_Container::RB_Tree<Map_Type_K, Key_Val_Type, Key_Val>;
        RB_TREE _ROOT_Map;
    public:
        using iterator = typename RB_TREE::iterator;
        using const_iterator = typename RB_TREE::const_iterator;
        using reverse_iterator = typename RB_TREE::reverse_iterator;
        using const_reverse_iterator = typename RB_TREE::const_reverse_iterator;
        
        using Map_iterator = MY_Template::Practicality::pair<iterator, bool>;
        
        Map();
        Map(const Map& Map_Temp);
        Map(const Key_Val_Type& Map_Temp);
        Map& operator=(const Map& Map_Temp);
        Map_iterator push(const Key_Val_Type& Map_Temp);
        Map_iterator pop(const Key_Val_Type& Map_Temp);
        iterator find(const Key_Val_Type& Map_Temp);
        void Middle_order_traversal();
        void Pre_order_traversal();
        size_t size() const;
        bool empty();
        iterator begin();
        iterator end();
        const_iterator cbegin();
        const_iterator cend();
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator crbegin();
        const_reverse_iterator crend();
        iterator operator[](const Key_Val_Type& Map_Temp);
    };
}

namespace set_Container {
    template <typename Set_Type_K>
    class Set
    {
        using Key_Val_Type = Set_Type_K;
        struct Key_Val
        {
            /* 仿函数，返回比较的值 */
            const Set_Type_K& operator()(const Key_Val_Type& Temp_Key_)
            {
                return Temp_Key_;
            }
        };
        using RB_TREE = Base_Class_Container::RB_Tree<Set_Type_K, Key_Val_Type, Key_Val>;
        RB_TREE _ROOT_Set;
    public:
        using iterator = typename RB_TREE::iterator;
        using const_iterator = typename RB_TREE::const_iterator;
        using reverse_iterator = typename RB_TREE::reverse_iterator;
        using const_reverse_iterator = typename RB_TREE::const_reverse_iterator;
        
        using Set_iterator = MY_Template::Practicality::pair<iterator, bool>;
        
        Set();
        ~Set();
        Set(const Set& Set_Temp);
        Set(const Key_Val_Type& Set_Temp);
        Set& operator=(const Set& Set_Temp);
        Set_iterator push(const Key_Val_Type& Set_Temp);
        Set_iterator pop(const Key_Val_Type& Set_Temp);
        iterator find(const Key_Val_Type& Set_Temp);
        void Middle_order_traversal();
        void Pre_order_traversal();
        size_t size() const;
        bool empty();
        iterator begin();
        iterator end();
        const_iterator cbegin();
        const_iterator cend();
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator crbegin();
        const_reverse_iterator crend();
        iterator operator[](const Key_Val_Type& Set_Temp);
    };
}
```

| 方法                | 说明                   | 返回值             | 示例                   |
| ----------------- | --------------------    | --------------- | -------------------- |
| `Map()`            | 默认构造函数      | -          | `Map<int, string> m` |
| `Map(const Map&)`        | 拷贝构造函数       | -          | `Map<int, string> m2(m)`        |
| `Map(const Key_Val_Type&)`       | 使用键值对构造  | -       | `Map<int, string> m({1, "a"})`         |
| `operator=(const Map&)` | 赋值运算符  | `Map&`        | `m2 = m`          |
| `push(Key_Val_Type)`     | 插入键值对      | `Map_iterator`          | `m.push({1, "a"})`      |
| `pop(Key_Val_Type)`          | 删除键值对        | `Map_iterator`        | `m.pop({1, "a"})`          |
| `find(Key_Val_Type)`   | 查找键值对 | `iterator`         | `m.find({1, "a"})`   |
| `Middle_order_traversal()`  | 中序遍历 | `void` | `m.Middle_order_traversal()` |
| `Pre_order_traversal()`  | 前序遍历 | `void` | `m.Pre_order_traversal()` |
| `size()`  | 返回元素个数 | `size_t` | `m.size()` |
| `empty()`  | 判断是否为空 | `bool` | `m.empty()` |
| `begin()`  | 返回首元素迭代器 | `iterator` | `m.begin()` |
| `end()`  | 返回尾后迭代器 | `iterator` | `m.end()` |
| `cbegin()`  | 返回常量首元素迭代器 | `const_iterator` | `m.cbegin()` |
| `cend()`  | 返回常量尾后迭代器 | `const_iterator` | `m.cend()` |
| `rbegin()`  | 返回反向首元素迭代器 | `reverse_iterator` | `m.rbegin()` |
| `rend()`  | 返回反向尾后迭代器 | `reverse_iterator` | `m.rend()` |
| `crbegin()`  | 返回常量反向首元素迭代器 | `const_reverse_iterator` | `m.crbegin()` |
| `crend()`  | 返回常量反向尾后迭代器 | `const_reverse_iterator` | `m.crend()` |
| `operator[](Key_Val_Type)`  | 访问或插入元素 | `iterator` | `m[{1, "a"}]` |

对于Set容器，方法与Map基本相同，只是操作的是单一键类型而非键值对。

---

## 🔍 布隆过滤器 `BloomFilter<Key,HF>`

```cpp
namespace BloomFilter_Container
{
    template <typename BloomFilter_Type_Val, typename Hash_Functor_BloomFilter = MY_Template::algorithm::Hash_algorithm::Hash_function<BloomFilter_Type_Val>>
    class BloomFilter
    {
        Hash_Functor_BloomFilter _Hash;
        using BitSet = MY_Template::Base_Class_Container::BitSet;
        BitSet _vector_BitSet;
        size_t _Capacity;
    public:
        BloomFilter();
        BloomFilter(const size_t& Temp_Capacity);
        size_t size();
        size_t capacity();
        bool test(const BloomFilter_Type_Val& Temp_Val);
        void set(const BloomFilter_Type_Val& Temp_Val);
        //布隆过滤器只支持插入和查找，不支持删除
    };
}
```

| 方法                    | 说明                  | 返回值    | 示例                                |
| --------------------- | --------------------- | ------ | --------------------------------- |
| `BloomFilter()`            | 默认构造函数，容量为1000 | -      | `BloomFilter<string> b;` |
| `BloomFilter(const size_t&)`| 指定容量的构造函数      | -      | `BloomFilter<string> b(1024);` |
| `size()`             | 返回位数组大小         | `size_t` | `b.size()` |
| `capacity()`         | 返回容量              | `size_t` | `b.capacity()` |
| `test(const BloomFilter_Type_Val&)` | 测试元素是否可能存在 | `bool` | `b.test("x")` |
| `set(const BloomFilter_Type_Val&)`  | 添加元素到过滤器     | `void` | `b.set("y")` |

> 注意：布隆过滤器只支持插入和查找，不支持删除操作。

---

## 🗂️ 适配器模块

```cpp
namespace stack_Adapter 
{
    template<typename T>
    class stack 
    {
    private: vector_Container::vector<T> _con;
    public:
        void push(const T&);
        void pop();
        T& top();
        bool empty()const;
        size_t size()const;
    };
}
namespace queue_Adapter 
{
    template<typename T>
    class queue 
    {
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
namespace priority_queue_Adapter 
{
    template<typename T,typename Compare>
    class priority_queue 
    {
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
