#include "../template_container.hpp"
using namespace template_container::set_container;
int main()
{
    {
        tree_set<int> ts = {3, 1, 2, 4};
    
        // 2. 插入元素
        ts.push(5);
        
        // 3. 查找元素
        auto it = ts.find(2);
        if (it != ts.end()) 
        {
            std::cout << "找到元素: " << *it << std::endl;  // 输出: 2
        }
        
        // 4. 中序遍历（按升序）
        std::cout << "中序遍历结果: ";
        ts.middle_order_traversal();  // 输出: 1 2 3 4 5
        
        // 5. 删除元素
        ts.pop(3);
        std::cout << "\n删除后大小: " << ts.size() << std::endl;  // 输出: 4
    }
    {
        // 1. 创建hash_set并初始化
        hash_set<int> hs = {3, 1, 2, 4};
        
        // 2. 插入元素
        hs.push(5);
        
        // 3. 查找元素
        auto it = hs.find(2);
        if (it != hs.end()) 
        {
            std::cout << "找到元素: " << *it << std::endl;  // 输出: 2
        }
        
        // 4. 遍历元素（按插入顺序）
        std::cout << "遍历元素: ";
        for (auto it = hs.begin(); it != hs.end(); ++it) \
        {
            std::cout << *it << " ";
        }
        // 输出: 3 1 2 4 5（顺序可能不同）
        
        // 5. 删除元素
        hs.pop(3);
        std::cout << "\n删除后大小: " << hs.size() << std::endl;  // 输出: 4
    }
    return 0;
}