#include <string>
#include <iostream>
#include <format>
#include <functional>

using func = std::function<std::string(std::uint64_t,std::uint64_t)>;

func test_func1()
{
    return [](std::uint64_t a, std::uint64_t b)  { return std::to_string(a + b); };
}

int main()
{
    std::cout << std::format("{}",test_func1()(1, 2)) << std::endl;
    return 0;
}