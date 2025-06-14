#include "../template_container.hpp"
using namespace template_container::tree_container;

int main() 
{
    // 1. 构造二叉搜索树
    binary_search_tree<int> bst = {5, 3, 7, 2, 4, 6, 8};
    
    std::cout << "中序遍历: ";
    bst.middle_order_traversal();  // 输出: 2 3 4 5 6 7 8
    std::cout << "\n前序遍历: ";
    bst.pre_order_traversal();   // 输出: 5 3 2 4 7 6 8
    std::cout << "\n树大小: " << bst.size() << std::endl;  // 输出: 7
    
    // 2. 插入节点
    bst.push(9);
    std::cout << "插入9后中序遍历: ";
    bst.middle_order_traversal();  // 输出: 2 3 4 5 6 7 8 9
    
    // 3. 删除节点
    bst.pop(3);
    std::cout << "删除3后中序遍历: ";
    bst.middle_order_traversal();  // 输出: 2 4 5 6 7 8 9
    
    // 4. 查找节点
    auto node = bst.find(6);
    if (node) 
    {
        std::cout << "\n找到节点: " << node->_data << std::endl;
    }
    
    // 5. 拷贝构造
    binary_search_tree<int> bst_copy = bst;
    std::cout << "拷贝树中序遍历: ";
    bst_copy.middle_order_traversal();
    
    return 0;
}