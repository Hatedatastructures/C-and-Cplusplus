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
    template <typename list_node_Type>
    class list
    {
        typedef listNode<list_node_Type> Node;

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
        void push_back(const list_node_Type& push_back_data)
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