#include <iostream>
class A
{
    public:
    size_t num = 2;

};
class B :public A
{
    size_t num = 9;
    public:
    void printf()
    {
        std::cout << num <<std::endl;
        std::cout << A::num << std::endl;
        // std::cout << ::A::sum << std::endl;
    }
};
int main()
{
    B test;
    test.printf();
    return 0;
}