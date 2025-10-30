#include <ranges>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> vec = {1, 2, 3, 4, 5};
  auto even = vec | std::views::filter([](int x) { return x % 2 == 0; });
  std::cout << *std::next(even.begin()) << std::endl;
  for (auto x : even)
  {
    std::cout << x << " ";
  }
  return 0;
}