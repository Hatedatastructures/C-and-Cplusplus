#include <iostream>
//模拟实现list
namespace wa
{ 
    template<typename list_Ndoe_Type>
    struct listNode
    {
        listNode<list_Ndoe_Type>* _prev;
        listNode<list_Ndoe_Type>* _next;
        list_Ndoe_Type _data;

        listNode(const list_Ndoe_Type& data = list_Ndoe_Type())
        :_prev(nullptr), _next(nullptr), _data(data)
        {
            //列表初始化
        }
        
    };


    template <typename list_Node_Type ,typename Ref ,typename Ptr >
    class _list_iterator_
    {
    public:
        //迭代器类
        typedef listNode<list_Node_Type> Node;
        typedef _list_iterator_<list_Node_Type ,list_Node_Type& ,list_Node_Type*> iterator;
        Node* _node;
        _list_iterator_(Node* node)
        :_node(node)
        {
            //拿一个指针来构造迭代器
        }
        Ref operator*()
        {
            //返回该节点的自定义类型的数据
            return _node->_data;
        }
        _list_iterator_& operator++()
        {
            //先用再加，返回加之后的位置
            _node = _node -> _next;
            return *this;
            //返回类型名，如果为迭代器就会因为const 报错
        }
        _list_iterator_ operator++(int)
        {
            //先加再用返回加之前的位置
            _list_iterator_ temp = *this;
            ++(*this);
            return temp;
        }
        bool operator!= (const iterator& _iterator_temp_)
        {
            //比较两个指针及其上一个和下一个指针地址
            return _node != _iterator_temp_._node;
        }
        Ptr operator->()
        {
            return &(_node->_data);
        }
    };
    template <typename iterator>
    class _Reverse_list_iterator_
    {
        typedef typename iterator::Ref Ref;
        typedef typename iterator::Ptr Ptr;
    };
    template <typename list_Node_Type>
    class list
    {
        typedef listNode<list_Node_Type> Node;

        Node* _head;
        //_head为哨兵位
        void CreateHead()
        {
            _head = new Node;
            _head -> _prev = _head;
            _head -> _next = _head;
        }
    public:
        typedef _list_iterator_<list_Node_Type,list_Node_Type& ,list_Node_Type*> iterator;
        typedef _list_iterator_<list_Node_Type,const list_Node_Type&,const list_Node_Type*> const_iterator;

        typedef _Reverse_list_iterator_<iterator> reverse_iterator;
        typedef _Reverse_list_iterator_<const_iterator> reverse_const_iterator;
        list()
        {
            CreateHead();
        }
        iterator begin()
        {
            //因为_head为哨兵位，所以哨兵下一个结点为有效数据
            return iterator(_head ->_next);
        }
        iterator end()
        {
            return iterator(_head);
        }
        const_iterator cbegin()const
        {
            //因为_head为哨兵位，所以哨兵下一个结点为有效数据
            return const_iterator(_head ->_next);
        }
        const_iterator cend()const
        {
            return const_iterator(_head);
        }
        void push_back(const list_Node_Type& push_back_data)
        {
            Node* tail = _head->_prev;
            Node* new_node = new Node(push_back_data); 
            //开辟内存拷贝把list_Node_Type类型赋值到_data里
            tail->_next = new_node;
            new_node->_prev = tail;
            _head->_prev = new_node;
            new_node->_next = _head;
        }
    };
}
int main()
{
    wa::list<int> test1;
    for(size_t i = 1; i < 10; i++)
    {
        test1.push_back(i);
    }
    wa::list<int>::const_iterator it =test1.cbegin();
    while(it != test1.end())
    {
        std::cout << *it  << " ";
        it++;
    }
    std::cout << std::endl;
    return 0;
}