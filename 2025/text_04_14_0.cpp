#include <iostream>
//模拟实现list
namespace wa
{ 
    template<typename list_Ndoe_Type>
    struct listNode
    {
        list_Ndoe_Type _data;
        listNode<list_Ndoe_Type>* _prev;
        listNode<list_Ndoe_Type>* _next;

        listNode(const list_Ndoe_Type& data = list_Ndoe_Type())
        :_prev(nullptr), _next(nullptr), _data(data)
        {
            //列表初始化
        }
    };
    template <typename list_Node_Type>
    class _list_iterator_
    {
        //迭代器类
        typedef listNode<list_Node_Type> Node;
        Node* _node;
    public:
        _list_iterator_(Node* node)
        :_node(node)
        {
            //拿一个指针来构造迭代器
        }
        list_Node_Type& operator*()
        {
            //返回该节点的自定义类型的数据
            return _node->_data;
        }
        _list_iterator_<list_Node_Type>& operator++()
        {
            //返回加之后的位置
            _node = _node -> _next;
            return *this;
        }
    };
    template <typename list_Node_Type>
    class list
    {
        typedef listNode<list_Node_Type> Node;

        Node* _head;
        void CreateHead()
        {
            _head = new Node;
            _head -> _prev = _head;
            _head -> _next = _head;
        }
    public:
        list()
        {
            CreateHead();
        }
        void push_back(const list_Node_Type& push_back_data)
        {
            Node* tail = _head->_prev;
            Node* new_node = new Node(push_back_data); 
            //开辟内存拷贝把list_Node_Type类型赋值到_data里
            tail->next = new_node;
            new_node->_prev = tail;
            _head->_prev = new_node;
            new_node->_next = _head;
        }
    };
}