#include <print>
#include <iostream>
#include <string>

int main() 
{
  std::string str1 = "Hello World!";
  std::string str2 = "Hello World!";
  std::println("{},{}",str1,str2); // 编译失败
  return 0;
}