#include "../template_container.hpp"
using namespace  template_container;

int main()
{
    // 1. 构造函数示例
    std::cout << "=== 构造函数示例 ===\n";

    // 默认构造
    list_container::list<int> l1;
    std::cout << "l1 (默认构造): " << l1 << std::endl;

    // 初始化列表构造
    list_container::list<std::string> l2 = {"hello", "world", "!"};
    std::cout << "l2 (初始化列表构造): " << l2 << std::endl;

    // 拷贝构造
    list_container::list<std::string> l3(l2);
    std::cout << "l3 (拷贝构造): " << l3 << std::endl;

    // 2. 插入操作示例
    std::cout << "\n=== 插入操作示例 ===\n";

    l1.push_back(10);
    l1.push_back(20);
    l1.push_front(5);
    std::cout << "l1 插入后: " << l1 << std::endl;

    // 指定位置插入
    auto it = l1.begin();
    ++it;  // 指向第二个元素
    l1.insert(it, 15);
    std::cout << "l1 插入中间: " << l1 << std::endl;

    // 3. 删除操作示例
    std::cout << "\n=== 删除操作示例 ===\n";

    l1.pop_back();
    std::cout << "l1 删除尾部: " << l1 << std::endl;

    l1.pop_front();
    std::cout << "l1 删除头部: " << l1 << std::endl;

    it = l1.begin();
    l1.erase(it);
    std::cout << "l1 删除中间: " << l1 << std::endl;

    // 4. 迭代器遍历示例
    std::cout << "\n=== 迭代器遍历示例 ===\n";

    std::cout << "正向遍历 l2: ";
    for (auto list_iterator = l2.begin(); list_iterator != l2.end(); ++list_iterator) {
        std::cout << *list_iterator << " ";
    }
    std::cout << std::endl;

    std::cout << "反向遍历 l2: ";
    for (auto reverse_list_iterator = l2.rbegin(); reverse_list_iterator != l2.rend(); ++reverse_list_iterator) {
        std::cout << *reverse_list_iterator << " ";
    }
    std::cout << std::endl;

    // 5. 其他操作示例
    std::cout << "\n=== 其他操作示例 ===\n";

    std::cout << "l2 size: " << l2.size() << std::endl;
    std::cout << "l2 empty: " << (l2.empty() ? "true" : "false") << std::endl;

    l2.resize(5, "default");
    std::cout << "l2 resize: " << l2 << std::endl;

    // 6. 运算符重载示例
    std::cout << "\n=== 运算符重载示例 ===\n";

    list_container::list<std::string> l4 = {"a", "b"};
    l4 += l2;
    std::cout << "l4 += l2: " << l4 << std::endl;

    list_container::list<std::string> l5 = l4 + l2;
    std::cout << "l5 = l4 + l2: " << l5 << std::endl;

    return 0;
}