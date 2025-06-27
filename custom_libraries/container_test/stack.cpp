#include "../template_container.hpp"
using namespace template_container;

int main()
{
    // 1. 构造函数示例
    std::cout << "=== 构造函数示例 ===\n";

    // 默认构造
    stack_adapter::stack<int> s1;
    std::cout << "s1 (默认构造，空栈): size=" << s1.size() << std::endl;

    // 元素构造
    stack_adapter::stack<double> s2(3.14);
    std::cout << "s2 (元素构造): top=" << s2.top() << std::endl;

    // 初始化列表构造
    stack_adapter::stack<std::string> s3 = {"hello", "world"};
    std::cout << "s3 (初始化列表构造): ";
    while ( !s3.empty() ) 
    {
        std::cout << s3.top() << " ";
        s3.pop();
    }
    std::cout << std::endl;

    // 2. 栈操作示例
    std::cout << "\n=== 栈操作示例 ===\n";

    stack_adapter::stack<int> s4;
    s4.push(10);
    s4.push(20);
    s4.push(30);

    std::cout << "s4 压栈后 size=" << s4.size() << ", top=" << s4.top() << std::endl;

    s4.pop();
    std::cout << "s4 弹栈后 size=" << s4.size() << ", top=" << s4.top() << std::endl;

    // 3. 拷贝与移动示例
    std::cout << "\n=== 拷贝与移动示例 ===\n";

    // 拷贝构造
    stack_adapter::stack<int> s5(s4);
    std::cout << "s5 (拷贝构造自 s4): top=" << s5.top() << std::endl;

    // 移动构造
    stack_adapter::stack<int> s6(std::move(s5));
    std::cout << "s6 (移动构造自 s5): top=" << s6.top() << ", s5 size=" << s5.size() << std::endl;

    return 0;
}