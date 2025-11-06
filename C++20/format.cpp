#include <iostream>
#include <format>
#include "../Asio/model/concurrent/container.hpp"
#include "../Asio/model/container/container.hpp"
#include <map>

int main()
{
  {
    wan::scl::string str = {"hello"};
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};
    std::unordered_map<std::string, int> umap = {{"one", 1}, {"two", 2}, {"three", 3}};
    std::string s = "hello";
    std::cout << std::format("{}", vec) << std::endl;
    std::cout << std::format("{}", map) << std::endl;
    std::cout << std::format("{}", umap) << std::endl;
    std::cout << std::format("{}", str) << std::endl; // 基于范围的打印，迭代器思维
    std::cout << std::format("{}", s) << std::endl;
    std::cout << std::format("{}", std::next(umap.begin())->second) << std::endl;
    std::cout << std::format("{}", std::next(umap.begin(), 2)->second) << std::endl;
  }
  return 0;
}