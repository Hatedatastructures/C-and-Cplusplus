#include "../template_container.hpp"
using namespace template_container::tree_container;
int main() 
{
    // 1. 构造AVL树
    avl_tree<int, std::string> avl;
    avl.push(5, "A");
    avl.push(3, "B");
    avl.push(7, "C");
    avl.push(2, "D");
    avl.push(4, "E");
    
    std::cout << "中序遍历: ";
    avl.middle_order_traversal();  // 输出: 2 3 4 5 7
    
    // 2. 查找节点
    auto node = avl.find(3);
    if (node) 
    {
        std::cout << "\n找到键3的值: " << node->_data.second << std::endl;
    }
    
    // 3. 删除节点
    avl.pop(3);
    std::cout << "删除3后中序遍历: ";
    avl.middle_order_traversal();  // 输出: 2 4 5 7
    
    // 4. 迭代器遍历
    std::cout << "\n迭代器遍历: ";
    for (auto it = avl.begin(); it != avl.end(); ++it) 
    {
        std::cout << it->first<< " ";
    }
    
    return 0;
}