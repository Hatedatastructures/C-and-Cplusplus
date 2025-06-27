#include <iostream>
#include <string>
using namespace std;
namespace test_1
{
    //这是继承
    class Name
    {
        public:
        std::string _name;//名字
        virtual void printf()
        {
            std::cout << _name << std::endl;
        }
         ~Name()
        {
            std::cout << "Name析构函数" << std::endl;
        }
    };

    class Student :public Name
    {
        public:
        size_t size; //学号
        virtual void printf()
        {
            std::cout << _name << " " << size << std::endl;
        }
         ~Student()
        {
            std::cout << "Student析构函数" << std::endl;
        }
    };
}
namespace test_2
{
    //这是继承
    class Name
    {
        public:
        std::string _name;//名字
        virtual void printf()
        {
            std::cout << _name << std::endl;
        }
        virtual ~Name()
        {
            std::cout << "Name析构函数" << std::endl;
        }
    };

    class Student :public Name
    {
        public:
        size_t size; //学号
        virtual void printf()
        {
            std::cout << _name << " " << size << std::endl;
        }
        virtual ~Student()
        {
            std::cout << "Student析构函数" << std::endl;
        }
    };
}
void test_virtual_(test_1::Name& test_virtual_)
{
    //虚函数调用一般是通过引用或者是指针来调用
    test_virtual_.printf();
}
void test_virtual_(test_2::Name* test_virtual_)
{
    //虚函数调用一般是通过引用或者是指针来调用
    test_virtual_->printf();
}
void test_test1()
{
    test_1::Student s;
    test_1::Name n;
    s._name = "张三";
    s.size = 1001;
    test_virtual_(s);
    test_virtual_(n);
    n._name = "李四";
    test_virtual_(n);
}
void test_test_1_s()
{
    test_2::Student* s = new test_2::Student;
    test_2::Name* n = new test_2::Name;
    s->_name = "王五";
    s->size = 1999;
    test_virtual_(s);
    test_virtual_(n);
    n->_name = "于六";
    test_virtual_(n);
    delete s;
    delete n;
}
// void test_test2()
// {
//     test_1::Student* s = new test_1::Student;
//     test_1::Name* n = new test_1::Name;
//     delete s;
//     delete n;
// }

/*             上面的类没把析构函数写成虚函数导致报错                                                       */
/*            对于多态如果想用自定义类型指针需要把派生类和*基类析构函数写成虚函数来保证指针的正常使用           */
/*            虚函数底层是有虚基表实现，而且虚函数和他存储在常量区(代码段)中，所以虚函数不能在类外定义          */
void test_test2()
{
    test_2::Student* s = new test_2::Student;
    test_2::Name* n = new test_2::Name;
    delete s;
    delete n;
}
int main() // 主函数，程序的入口点
{
    test_test1(); // 调用函数 test_test1，执行其功能
    std::cout << std::endl << std::endl << std::endl;
    test_test_1_s();
    std::cout << std::endl << std::endl << std::endl;
    test_test2();
    return 0; // 返回0，表示程序正常结束
    return 0;
}