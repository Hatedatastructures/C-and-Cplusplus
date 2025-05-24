#include "MY_Template.hpp"
#include <thread>
// import MY_Template;
#include <random>
#include <algorithm>
#include <atomic>
int main()
{   
    /*            string测试             */
    {
        std::cout << " string 测试 " << std::endl << std::endl;
        MyTemplate::string_Container::string string_test1("hello");
        MyTemplate::string_Container::string string_test2("world");
        
        MyTemplate::string_Container::string string_test3 = string_test1 + string_test2;
        std::cout << "string_test3: " << string_test3 << std::endl;
        string_test3.push_back('!');
        const char* insert_str = "inserted";
        string_test3.nose_Insertion_substrings(insert_str);
        std::cout << "str3 after insertion: " << string_test3 << std::endl;

        size_t old_pos = strlen(insert_str);
        MyTemplate::string_Container::string string_test4 = string_test3.str_withdraw(old_pos);
        std::cout << "string_test4: " << string_test4 << std::endl;

        std::cout << string_test3.conversions_oldest() << std::endl;
        std::cout << string_test3.conversions_few() << std::endl;

        MyTemplate::string_Container::string string_test5 = string_test3.str_withdraw_extremity(5);
        std::cout << "string_test5: " << string_test5 << std::endl;

        MyTemplate::string_Container::string string_test6 = string_test3.str_withdraw_detail(5, 10);
        std::cout << "string_test6: " << string_test6 << std::endl;

        std::cout << "str3 size: " << string_test3.size() << std::endl;
        std::cout << "str3 capacity: " << string_test3.capacity() << std::endl;
        std::cout << "string_test3 after resize: " << string_test3.resize(21, '*') << std::endl;

        std::cout << "string_test3 after rollback: " << string_test3.rollback() << std::endl;

        std::cout << "string_test3 after rollback_limit: " << string_test3.rollback_limit(5, 10) << std::endl;

        string_test3.string_print();
        string_test3.string_print_reverse();

        for(auto i :string_test3)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        for(MyTemplate::string_Container::string::const_iterator i = string_test3.begin();i != string_test3.end();i++)
        {
            std::cout << *i << " ";
        }
        std::cout << string_test3[30000000] << std::endl;
        std::cout << std::endl;
        {
            //异常测试
            MyTemplate::string_Container::string Ex;
            Ex.resize(size_t(10000000));
            Ex.push_back("异常测试");
        }
    }

    /*            vector测试             */
    {
        std::cout << " vector 测试 " << std::endl << std::endl;
        MyTemplate::vector_Container::vector<int> vector_test(5,1);
        for(auto i: vector_test)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        MyTemplate::vector_Container::vector<int> vector_test1(vector_test);
        for(const auto& i  : vector_test1 )
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        MyTemplate::vector_Container::vector<int> test2 = vector_test1;
        for(const auto i : test2)
        {
            std::cout << i << " ";
        }
        MyTemplate::string_Container::string s2 = "name";
        std::cout << std::endl;
        MyTemplate::vector_Container::vector<MyTemplate::string_Container::string> name_test(10,s2);
        for(const auto& i : name_test )
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        MyTemplate::vector_Container::vector<MyTemplate::string_Container::string> name_test1 =name_test ;
        for(const auto& i : name_test1 )
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        MyTemplate::string_Container::string s3 = "hello word!";
        name_test1.push_back(s3);
        for(const auto& i : name_test1 )
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        name_test1.push_front(s3);
        for(const auto& i : name_test1 )
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        name_test1+=name_test;
        for(const auto& i : name_test1 )
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        std::cout << name_test1 << std::endl;
        std::cout << name_test1.pop_back() << std::endl;
    }


    /*            list测试             */
    {
        std::cout << " list 测试 " << std::endl << std::endl;
        MyTemplate::list_Container::list<int> list_test1;
        for(size_t i = 1; i < 10; i++)
        {
            list_test1.push_back(i);
        }
        MyTemplate::list_Container::list<int>::const_iterator it =list_test1.cbegin();
        while(it != list_test1.cend())
        {
            std::cout << *it  << " ";
            it++;
        }
        std::cout << std::endl;
        MyTemplate::list_Container::list<int>::reverse_const_iterator i = list_test1.rcbegin();
        while(i != list_test1.rcend())
        {
            std::cout << *i << " ";
            i++;
        }
        std::cout <<std::endl;

        list_test1.pop_back(); 
        MyTemplate::list_Container::list<int>::const_iterator j =list_test1.cbegin();
        while(j != list_test1.cend())
        {
            std::cout << *j  << " ";
            j++;
        }
        std::cout << std::endl;
        std::cout << list_test1.size() << std::endl;

        MyTemplate::list_Container::list<int> list_test2 = list_test1;
        MyTemplate::list_Container::list<int>::const_iterator p =list_test2.cbegin();
        while(p != list_test2.cend())
        {
            std::cout << *p  << " ";
            p++;
        }
        std::cout << std::endl;
        std::cout << list_test2.size() << std::endl;

        MyTemplate::list_Container::list<int> list_test3 = list_test2 + list_test1;
        MyTemplate::list_Container::list<int>::const_iterator k =list_test3.cbegin();
        while(k != list_test3.cend())
        {
            std::cout << *k  << " ";
            k++;
        }
        std::cout << std::endl;
        std::cout << list_test3.size() << std::endl;

        MyTemplate::list_Container::list<int> list_test4 = list_test3 + list_test1;
        MyTemplate::list_Container::list<int>::const_iterator kp =list_test4.cbegin();
        while(kp != list_test4.cend())
        {
            std::cout << *kp  << " ";
            kp++;
        }
        std::cout << std::endl;
        std::cout << list_test4.size() << std::endl;
        std::cout << list_test4 << std::endl;
    }

    /*            staic测试             */
    {
        std::cout << " staic 测试 " << std::endl << std::endl;
        MyTemplate::string_Container::string staic_test_str1 = "hello";
        MyTemplate::string_Container::string staic_test_str2 = "word";
        MyTemplate::string_Container::string staic_test_str3 = "  ";
        MyTemplate::stack_Adapter::stack< MyTemplate::string_Container::string> staic_test1;

        staic_test1.push(staic_test_str1);
        staic_test1.push(staic_test_str3);
        staic_test1.push(staic_test_str2);

        std::cout << staic_test1.top() << std::endl;
        staic_test1.pop();
        std::cout << staic_test1.top() << std::endl;
        staic_test1.pop();
        std::cout << staic_test1.top() << std::endl;
        staic_test1.pop();
    }

    /*            queue测试             */
    {
        std::cout << " queue 测试 " << std::endl << std::endl;
        MyTemplate::string_Container::string queue_test_str1 = "hello";
        MyTemplate::string_Container::string queue_test_str2 = "word";
        MyTemplate::string_Container::string queue_test_str3 = "  ";
        MyTemplate::queue_Adapter::queue< MyTemplate::string_Container::string,MyTemplate::list_Container::list< MyTemplate::string_Container::string>> queue_test1;

        queue_test1.push(queue_test_str1);
        queue_test1.push(queue_test_str3);
        queue_test1.push(queue_test_str2);

        std::cout << queue_test1.front() << std::endl;
        std::cout << queue_test1.back()  << std::endl;

        std::cout << queue_test1.front() << " ";
        queue_test1.pop();
        std::cout << queue_test1.front() << " ";
        queue_test1.pop();
        std::cout << queue_test1.front() << " ";
        queue_test1.pop();
    }

    /*            priority_queue测试             */
    {
        time_t num1 = clock();
        std::cout << " priority_queue 测试 " << std::endl << std::endl;
        MyTemplate::queue_Adapter::priority_queue<int> priority_queue_test;
        for(int i = 0; i < 10000 ; i++)
        {
            priority_queue_test.push(i);
        }

        std::cout << priority_queue_test.size() << std::endl;

        for(size_t i = 0; i < 10000; i++)
        {
            std::cout << priority_queue_test.top() << " ";
            priority_queue_test.pop();
        }
        std::cout << std::endl;
        time_t num2 = clock();
        std::cout << num2-num1 << std::endl;
    }

    /*            BS_Tree 测试             */
    {
        time_t Binary_search_tree_num1 = clock();
        MyTemplate::Tree_Container::BS_Tree<int,MyTemplate::ImitationFunctions::greater<int>> Binary_search_tree_test;
        for(size_t i = 100; i > 0; i--)
        {
            //相对来说这算是有序插入导致二叉树相乘时间复杂度为O(N)的链表
            Binary_search_tree_test.push(i);
        }
        time_t Binary_search_tree_num2 = clock();

        time_t Binary_search_tree_num3 = clock();
        std::cout << Binary_search_tree_test.find(58) << std::endl;
        time_t Binary_search_tree_num4 = clock();
        // Binary_search_tree_test.Middle_order_traversal();
        std::cout << "退化链表插入时间" << Binary_search_tree_num2-Binary_search_tree_num1 << std::endl;
        std::cout << "退化链表查找时间" << Binary_search_tree_num4-Binary_search_tree_num3 << std::endl;
        std::cout << std::endl << std::endl;
    }

    {
        MyTemplate::Tree_Container::BS_Tree<int, MyTemplate::ImitationFunctions::greater<int>> bst;
        bst.push(5);
        bst.push(4);
        bst.push(3);
        bst.push(2);
        bst.push(1);
        bst.Middle_order_traversal(); 
        std::cout << std::endl << std::endl;
    }

    {
        const size_t Binary_search_tree_arraySize = 10;
        MyTemplate::vector_Container::vector<int> Binary_search_tree_array(Binary_search_tree_arraySize);
        for (size_t i = 0; i < Binary_search_tree_arraySize; ++i) 
        {
            Binary_search_tree_array[i] = i;
        }

        // 创建随机数引擎和分布
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(Binary_search_tree_array.begin(), Binary_search_tree_array.end(), g);
        //输出打乱后的数组
        // for(auto& i : Binary_search_tree_array)
        // {
        //     std::cout << i << " ";
        // }

        //打乱数组元素顺序
        size_t size = 0;
        time_t Binary_search_tree_num1 = clock();
        MyTemplate::Tree_Container::BS_Tree<int,MyTemplate::ImitationFunctions::greater<int>> Binary_search_tree_test;
        for(const auto& Binary_search_tree_for_test: Binary_search_tree_array)
        {
            if(Binary_search_tree_test.push(Binary_search_tree_for_test))
            {
                size++;
            }
        }
        time_t Binary_search_tree_num2 = clock();

        const int Binary_search_tree_find = Binary_search_tree_array[Binary_search_tree_arraySize/2];

        time_t Binary_search_tree_num3 = clock();
        Binary_search_tree_test.find(Binary_search_tree_find);
        time_t Binary_search_tree_num4 = clock();
        // Binary_search_tree_test.Middle_order_traversal();
        std::cout << "插入个数" << size << std::endl;
        std::cout << "插入时间" << Binary_search_tree_num2-Binary_search_tree_num1 << std::endl;
        std::cout << "查找时间" << Binary_search_tree_num4-Binary_search_tree_num3 << std::endl;
        /*              查找数据时间不稳定时间复杂度是O(logN)        */
        std::cout << std::endl << std::endl;
    }

    {
        const size_t Binary_search_tree_arraySize = 20;
        MyTemplate::vector_Container::vector<int> Binary_search_tree_array(Binary_search_tree_arraySize);
        for (size_t i = 0; i < Binary_search_tree_arraySize; ++i) 
        {
            Binary_search_tree_array[i] = i;
        }

        // 创建随机数引擎和分布
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(Binary_search_tree_array.begin(), Binary_search_tree_array.end(), g);
        //输出打乱后的数组
        // for(auto& i : Binary_search_tree_array)
        // {
        //     std::cout << i << " ";
        // }

        //打乱数组元素顺序
        size_t size = 0;
        time_t Binary_search_tree_num1 = clock();
        MyTemplate::Tree_Container::BS_Tree<int,MyTemplate::ImitationFunctions::greater<int>> Binary_search_tree_test;
        for(const auto& Binary_search_tree_for_test: Binary_search_tree_array)
        {
            if(Binary_search_tree_test.push(Binary_search_tree_for_test))
            {
                size++;
                std::cout << size << " ";
            }
        }
        std::cout << std::endl;
        time_t Binary_search_tree_num2 = clock();
        MyTemplate::Tree_Container::BS_Tree<int,MyTemplate::ImitationFunctions::greater<int>> Binary_search_tree_test1 = Binary_search_tree_test;
        time_t Binary_search_tree_num3 = clock();
        std::cout << "拷贝构造没问题 " << std::endl;

        Binary_search_tree_test.pop(Binary_search_tree_array[2]);
        std::cout << "pop(1)函数没问题 " << std::endl;
        Binary_search_tree_test.pop(Binary_search_tree_array[0]);
        std::cout << "pop(2)函数没问题 " << std::endl;
        Binary_search_tree_test.pop(Binary_search_tree_array[1]);
        std::cout << "pop(3)函数没问题 " << std::endl;
        Binary_search_tree_test.pop(Binary_search_tree_array[3]);
        std::cout << "pop(4)函数没问题 " << std::endl;


        Binary_search_tree_test.Middle_order_traversal();
        std::cout << std::endl;
        Binary_search_tree_test1.Middle_order_traversal();

        std::cout << "前序遍历 "<< std::endl;
        Binary_search_tree_test.Pre_order_traversal();
        std::cout << std::endl;
        Binary_search_tree_test1.Pre_order_traversal();
        std::cout << std::endl;
        std::cout << "插入个数" << size << std::endl;
        std::cout << "插入时间" << Binary_search_tree_num2-Binary_search_tree_num1 << std::endl;
        std::cout << "拷贝时间" << Binary_search_tree_num3-Binary_search_tree_num2 << std::endl;
    }

    {
        MyTemplate::string_Container::string str1 = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        std::cout << str1 << std::endl;
        MyTemplate::vector_Container::vector< MyTemplate::string_Container::string> vector_str = 
        {"西瓜","樱桃","苹果","西瓜","樱桃","苹果","樱桃","西瓜","樱桃","西瓜","樱桃","苹果","樱桃","苹果","樱桃"};

        MyTemplate::Tree_Container::BS_Tree< MyTemplate::string_Container::string> BST_temp;
        size_t _BST_size = vector_str.size();
        for(size_t i = 0 ; i < _BST_size;i++)
        {
            if(BST_temp.push(vector_str[i]))
            {
                std::cout << "插入成功" << std::endl;
            }
            else
            {
                //当前未实现累加功能
                std::cout << "插入失败" << std::endl;
            }
        }
        BST_temp.Middle_order_traversal();
        std::cout << BST_temp.size() << std::endl;
    }
    /*            pair类 测试             */
    {
        const int i = 31; const int j = 28;
        MyTemplate::Practicality::Pair<int,int> pair_test =MyTemplate::Practicality::make_pair(i,j);
        std::cout << pair_test << std::endl;
    }
    /*            AVL_Tree 测试             */
    {
        MyTemplate::Tree_Container::AVL_Tree <MyTemplate::Practicality::Pair<int,int>,int> AVL_Tree_test_pair(MyTemplate::Practicality::Pair(9,0), 10);
        MyTemplate::Practicality::Pair<MyTemplate::Practicality::Pair<int,int>,int> pair_test_ (MyTemplate::Practicality::Pair(9,0), 10);
        MyTemplate::Tree_Container::AVL_Tree <MyTemplate::Practicality::Pair<int,int>,int> AVL_Tree_test(pair_test_);
        //两个构造函数，根据传值调用来查看调用情况
        MyTemplate::Tree_Container::AVL_Tree<MyTemplate::string_Container::string,int> AVL_Tree_test2;
        AVL_Tree_test2.~AVL_Tree();
    }
    {
        MyTemplate::Tree_Container::AVL_Tree<int,int> AVL_Tree_test_pair;
        MyTemplate::vector_Container::vector<MyTemplate::Practicality::Pair<int,int>> AVL_Tree_array_pair = 
        {{22,0},{16,0},{13,0},{15,0},{11,0},{12,0},{14,0},{10,0},{2,0},{10,0}};
        for(auto& i : AVL_Tree_array_pair)
        {
            AVL_Tree_test_pair.push(i);
        }
        std::cout << "前序遍历 "<< std::endl;
        AVL_Tree_test_pair.Pre_order_traversal();
        std::cout << std::endl;
        std::cout << "中序遍历 "<< std::endl;
        AVL_Tree_test_pair.Middle_order_traversal();
        std::cout << std::endl;
    }
    {
        MyTemplate::Tree_Container::AVL_Tree<int,int> AVL_Tree_test_pair;
        MyTemplate::vector_Container::vector<MyTemplate::Practicality::Pair<int,int>> AVL_Tree_array_pair = 
        {{22,0},{16,0},{13,0},{15,0},{11,0},{12,0},{14,0},{10,0},{2,0},{10,0}};

        for(auto& i : AVL_Tree_array_pair)
        {
            AVL_Tree_test_pair.push(i);
        }
        std::cout << "前序遍历 "<< std::endl;
        AVL_Tree_test_pair.Pre_order_traversal();
        std::cout << std::endl;
        std::cout << "中序遍历 "<< std::endl;
        AVL_Tree_test_pair.Middle_order_traversal();
        std::cout << std::endl; 
        MyTemplate::Tree_Container::AVL_Tree<int,int>AVL_Tree_test_pair1(AVL_Tree_test_pair);
        std::cout << "前序遍历 "<< std::endl;
        AVL_Tree_test_pair1.Pre_order_traversal();
        std::cout << std::endl;
        std::cout << "中序遍历 "<< std::endl;
        AVL_Tree_test_pair1.Middle_order_traversal();
        std::cout << std::endl; 

        MyTemplate::Tree_Container::BS_Tree<char> BS_Tr;
        MyTemplate::string_Container::string str1 = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        for(auto& i :str1)
        {
            BS_Tr.push(i);
        }
        BS_Tr.Middle_order_traversal();
        std::cout << std::endl;
        MyTemplate::Tree_Container::BS_Tree<char> BS_TREE(BS_Tr);
        BS_TREE.Middle_order_traversal();
        std::cout << std::endl;
    }
    {
        MyTemplate::Tree_Container::AVL_Tree<int,int> AVL_Tree_test_pair;
        MyTemplate::vector_Container::vector<MyTemplate::Practicality::Pair<int,int>> AVL_Tree_array_pair = 
        {{22,0},{16,0},{13,0},{15,0},{11,0},{12,0},{14,0},{10,0},{2,0},{10,0}};

        for(auto& i : AVL_Tree_array_pair)
        {
            AVL_Tree_test_pair.push(i);
        }
        std::cout << std::endl;
        for ( auto i : AVL_Tree_test_pair)
        {
            std::cout << i << " ";
            // 该行会被推断为pair<int,int>类型
            //C++11的新特性,存在疑问？，Map容器是如何推导的？
        }
        std::cout << std::endl;
        for (auto it = AVL_Tree_test_pair.begin(); it != AVL_Tree_test_pair.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        for (auto const &p : AVL_Tree_test_pair) 
        {
            std::cout << p << " ";
        }
        
    }
    {
        //删除测试
        MyTemplate::Tree_Container::AVL_Tree<int,int> AVL_Tree_test_pair;
        MyTemplate::vector_Container::vector<MyTemplate::Practicality::Pair<int,int>> AVL_Tree_array_pair = 
        {{22,0},{16,0},{13,0},{15,0},{11,0},{12,0},{14,0},{10,0},{2,0},{10,0}};
        for(auto& i : AVL_Tree_array_pair)
        {
            AVL_Tree_test_pair.push(i);
        }
        std::cout << "前序遍历 "<< std::endl;
        AVL_Tree_test_pair.Pre_order_traversal();
        std::cout << std::endl;
        std::cout << "开始删除 "<< std::endl;
        for(auto& i : AVL_Tree_array_pair)
        {
            AVL_Tree_test_pair.pop(i.first);
            AVL_Tree_test_pair.Pre_order_traversal();
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    {
        //性能测试
        /*                   pair 类型                */
        MyTemplate::Tree_Container::AVL_Tree<size_t,int> AVL_Tree_test_pair;
        MyTemplate::vector_Container::vector<MyTemplate::Practicality::Pair<size_t,int>> AVL_Tree_array_pair;
        size_t size = 100000;
        for(size_t i = 0; i < size; i++)
        {
            AVL_Tree_array_pair.push_back(MyTemplate::Practicality::Pair<size_t,int>(i,0));
        }
        time_t AVL_Tree_num1 = clock();
        for(auto& i : AVL_Tree_array_pair)
        {
            AVL_Tree_test_pair.push(i);
        }
        time_t AVL_Tree_num2 = clock();
        std::cout << "插入个数:" << AVL_Tree_test_pair.size()  << " " << " 插入时间:" << AVL_Tree_num2 - AVL_Tree_num1 << std::endl;

        /*                  非pair 类型               */
        MyTemplate::Tree_Container::AVL_Tree<size_t,int> AVL_Tree_test;
        MyTemplate::vector_Container::vector<size_t> AVL_Tree_array;
        for(size_t j = 0; j < size ; j++)
        {
            AVL_Tree_array.push_back(j);
        }
        time_t AVL_Tree_num3 = clock();
        for(auto& j : AVL_Tree_array)
        {
            AVL_Tree_test.push(j);
        }
        time_t AVL_Tree_num4 = clock();
        std::cout << "插入个数:" << AVL_Tree_test.size()  << " " << " 插入时间:" << AVL_Tree_num4 - AVL_Tree_num3 << std::endl;
    }
    /*            Map 测试             */
    {
        MyTemplate::Map_Container::Map<size_t,size_t> Map_Test;
        size_t size = 10;
        MyTemplate::vector_Container::vector<MyTemplate::Practicality::Pair<size_t,size_t>> arr;
        size_t l = 0;
        for(size_t i = 0 ; i < size; i++ ,l = i)
        {
            arr.push_back(MyTemplate::Practicality::Pair<size_t,size_t>(i,l));
        }
        std::cout << arr << std::endl;
        for(auto& j : arr)
        {
            Map_Test.push(j);
            std::cout << "前序" << " ";
            Map_Test.Pre_order_traversal();
            std::cout << "   " << "中序:"<< Map_Test.size() << " " << Map_Test.empty() << " ";
            Map_Test.Middle_order_traversal();
            std::cout << std::endl;
        }
        std::cout << Map_Test.empty() << " ";
        std::cout << "正向" << std::endl;
        for(const auto& Map : Map_Test)
        {
            std::cout << Map << " ";
        }
        std::cout << "反向" << std::endl;
        for(auto it = Map_Test.crbegin(); it != Map_Test.crend(); it++)
        {
            std::cout << *it << " ";
        }
        for(auto& j : arr)
        {
            Map_Test.pop(j);
            // std::cout << "前序" << " ";
            // Map_Test.Pre_order_traversal();
            std::cout << "   " << "中序:"<< Map_Test.size() << " " << Map_Test.empty() << " ";
            Map_Test.Middle_order_traversal();
            std::cout << std::endl;
        }
    }
    /*            Set 测试             */
    {
        MyTemplate::Set_Container::Set<size_t> Set_test;
        size_t size = 20;
        MyTemplate::vector_Container::vector<size_t> arr;
        for(size_t i = 0; i < size; i++ )
        {
            arr.push_back(i);
        }
         std::cout << arr << std::endl;
        for(auto& j : arr)
        {
            Set_test.push(j);
            std::cout << "前序" << " ";
            Set_test.Pre_order_traversal();
            std::cout << "   " << "中序" << " ";
            Set_test.Middle_order_traversal();
            std::cout << std::endl;
        }
        std::cout << "正向"<< std::endl;
        for(auto& j : Set_test)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl << "反向"<< std::endl;
        for(auto j = Set_test.crbegin(); j != Set_test.crend(); j++)
        {
            std::cout << *j << " ";
        }
    }
    /*            unordered_Map 测试             */
    {
        MyTemplate::Map_Container::unordered_Map<size_t,size_t> unordered_Map_test;
        size_t size = 23;
        MyTemplate::vector_Container::vector<MyTemplate::Practicality::Pair<size_t,size_t>> arr;
        size_t l = 0;
        for(size_t i = 0 ; i < size; i++,l = i)
        {
            arr.push_back(MyTemplate::Practicality::Pair<size_t,size_t>(i,l));
        }
        for(size_t i = 0; i < size; i++)
        {
            unordered_Map_test.push(arr[i]);
        }
        std::cout << std::endl;

        std::cout << arr << std::endl;
        std::cout << *unordered_Map_test.find(MyTemplate::Practicality::Pair<size_t,size_t>(20,20)) << std::endl;
        for(size_t i = 0; i < size; i++)
        {
            std::cout << *unordered_Map_test.find(MyTemplate::Practicality::Pair<size_t,size_t>(i,i)) << " ";
        }
        std::cout << std::endl;
        for(size_t i = 0; i < (size - 10); i++)
        {
            std::cout <<  unordered_Map_test.pop(MyTemplate::Practicality::Pair<size_t,size_t>(i,i)) <<" ";
        }
        // auto it = unordered_Map_test.begin();//迭代器越界
        // for(size_t i = 0; i < size; i++)
        // {
        //     //
        //     std::cout << *it <<" ";
        //     ++it;
        // }
        std::cout << std::endl;
        // for(auto& i : unordered_Map_test)
        // {
        //     std::cout << i << " ";
        // }
        std::cout << std::endl;
    }
    /*            BloomFilter 测试             */
    {
        MyTemplate::BloomFilter_Container::BloomFilter<size_t> BloomFilter_test(3000000000);
        size_t size = 20;
        MyTemplate::vector_Container::vector<size_t> arr;
        for(size_t i = 0; i < size; i++ )
        {
            arr.push_back(i);
        }
        std::cout << arr << std::endl;
        for(auto& j : arr)
        {
            BloomFilter_test.set(j);
        }
        for(auto& j : arr)
        {
            std::cout << BloomFilter_test.test(j) << " ";
        }
        std::cout << BloomFilter_test.test(100) << " ";
        std::cout << std::endl;
    }
    {
        std::cout << "AVL_Tree移动构造测试" <<std::endl;
        MyTemplate::Tree_Container::AVL_Tree<int,int> AVL_Tree_test_pair;
        MyTemplate::vector_Container::vector<MyTemplate::Practicality::Pair<int,int>> AVL_Tree_array_pair = 
        {{22,0},{16,0},{13,0},{15,0},{11,0},{12,0},{14,0},{10,0},{2,0},{10,0}};

        for(auto& i : AVL_Tree_array_pair)
        {
            AVL_Tree_test_pair.push(i);
        }

        std::cout << "移动前：" ;
        AVL_Tree_test_pair.Middle_order_traversal();
        MyTemplate::Tree_Container::AVL_Tree<int,int> AVL_Tree_test = std::move(AVL_Tree_test_pair);
        std::cout << std::endl;
        std::cout << "移动构造：";
        AVL_Tree_test.Middle_order_traversal();
        std::cout << std::endl;
        std::cout << "移动后：" ;
        AVL_Tree_test_pair.Middle_order_traversal();
        //移动构造就是窃取资源
        std::cout << std::endl;
    }
    {
        std::cout << "AVL_Tree拷贝构造测试" <<std::endl;
        MyTemplate::Tree_Container::AVL_Tree<int,int> AVL_Tree_test_pair;
        MyTemplate::vector_Container::vector<MyTemplate::Practicality::Pair<int,int>> AVL_Tree_array_pair = 
        {{22,0},{16,0},{13,0},{15,0},{11,0},{12,0},{14,0},{10,0},{2,0},{10,0}};

        for(auto& i : AVL_Tree_array_pair)
        {
            AVL_Tree_test_pair.push(i);
        }

        std::cout << "拷贝前：" ;
        AVL_Tree_test_pair.Middle_order_traversal();
        MyTemplate::Tree_Container::AVL_Tree<int,int> AVL_Tree_test = AVL_Tree_test_pair;
        std::cout << std::endl;
        std::cout << "移动构造：";
        AVL_Tree_test.Middle_order_traversal();
        std::cout << std::endl;
        std::cout << "拷贝后：" ;
        AVL_Tree_test_pair.Middle_order_traversal();
        std::cout << std::endl;
    }
    {
        //链式输出轻量化容器
        std::initializer_list<int> init_list = {1,2,3,4,5,6,7,8,9,10};
        std::initializer_list<int>::iterator it = init_list.begin();
        for(;it != init_list.end();it++)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        for(auto& i : init_list)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    {
        // std::forward<int>(1);
        //完美转发，不会丢失左右值属性
        
    }
    // {
    //     std::atomic<size_t> sum(0);
    //     auto func = [&sum](){sum += 6;};
    //     MY_Template::vector_Container::vector<std::thread> array_thread;
    //     array_thread.resize(30);//30个空线程
    //     for(auto& size_thread :array_thread)
    //     {
    //         size_thread = std::thread(func);
    //     }
    //     for(auto& size_join :array_thread)
    //     {
    //         std::cout << "线程：" << size_join.get_id() << " " << std::endl;
    //         size_join.join();
    //     }
    //     std::cout << sum << std::endl;
    // }
    //问题vector容器resize函数问题
    return 0;
}