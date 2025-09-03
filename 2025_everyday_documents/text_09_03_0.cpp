#include <iostream>
#include <algorithm>
#include <format>
#include <print>
#include <tuple>
auto func() 
{
    struct type
    {
        int max;
        int min;
    };
    return type{ 1, 2 };
}
int main()
{
    std::cout << std::format("Hello, {}!\n", "World");
    auto result = func();
    std::cout << result.max << " " << result.min << std::endl;
    std::tuple<int, double, std::string> t(1, 3.14, "hello");
    return 0;
}