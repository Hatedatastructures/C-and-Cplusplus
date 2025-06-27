#include "../template_container.hpp"
using namespace template_container;
int main()
{
    // 1. 构造函数示例
    std::cout << "=== 构造函数示例 ===\n";

    // 默认构造（大顶堆）
    queue_adapter::priority_queue<int> pq1;
    std::cout << "pq1 (默认构造，空队列): size=" << pq1.size() << std::endl;

    // 初始化列表构造
    queue_adapter::priority_queue<int> pq2 = {3, 1, 4, 1, 5, 9};
    std::cout << "pq2 (初始化列表构造): top=" << pq2.top() << std::endl;

    // 2. 优先队列操作示例
    std::cout << std::endl << "=== 优先队列操作示例 ===" <<std::endl;


    pq1.push(10);
    pq1.push(20);
    pq1.push(15);

    std::cout << "pq1 入队后: top=" << pq1.top() << std::endl;

    pq1.pop();
    std::cout << "pq1 出队后: top=" << pq1.top() << std::endl;

    // 3. 自定义比较器示例（小顶堆）
    std::cout << "\n=== 自定义比较器示例 ===\n";

    using MinHeap = queue_adapter::priority_queue<int,
        template_container::imitation_functions::greater<int>>;

    MinHeap minHeap;
    minHeap.push(5);
    minHeap.push(3);
    minHeap.push(7);

    std::cout << "小顶堆: top=" << minHeap.top() << std::endl;

    return 0;
}