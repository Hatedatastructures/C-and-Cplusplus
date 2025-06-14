#include "../template_container.hpp"
using namespace  template_container;
int main()
{
    // 1. 构造函数示例
    std::cout << "=== 构造函数示例 ===\n";

    // 默认构造
    queue_adapter::queue<int> q1;
    std::cout << "q1 (默认构造，空队列): size=" << q1.size() << std::endl;

    // 元素构造
    queue_adapter::queue<double> q2(3.14);
    std::cout << "q2 (元素构造): front=" << q2.front() << std::endl;

    // 初始化列表构造
    queue_adapter::queue<std::string> q3 = {"hello", "world"};
    std::cout << "q3 (初始化列表构造): ";
    while (!q3.empty())
    {
        std::cout << q3.front() << " ";
        q3.pop();
    }
    std::cout << std::endl;

    // 2. 队列操作示例
    std::cout << "\n=== 队列操作示例 ===\n";

    queue_adapter::queue<int> q4;
    q4.push(10);
    q4.push(20);
    q4.push(30);

    std::cout << "q4 入队后: front=" << q4.front() << ", back=" << q4.back() << std::endl;

    q4.pop();
    std::cout << "q4 出队后: front=" << q4.front() << ", size=" << q4.size() << std::endl;

    // 3. 拷贝与移动示例
    std::cout << "\n=== 拷贝与移动示例 ===\n";

    // 拷贝构造
    queue_adapter::queue<int> q5(q4);
    std::cout << "q5 (拷贝构造自 q4): front=" << q5.front() << std::endl;

    // 移动构造
    queue_adapter::queue<int> q6(std::move(q5));
    std::cout << "q6 (移动构造自 q5): front=" << q6.front() << ", q5 empty=" << q5.empty() << std::endl;

    return 0;
}