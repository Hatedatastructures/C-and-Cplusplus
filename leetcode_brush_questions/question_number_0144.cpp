#include <iostream>
#include <vector>
#include <stack>
using namespace std;
//题目：二叉树的前序遍历
//https://leetcode.cn/problems/binary-tree-preorder-traversal/description/?envType=problem-list-v2&envId=stack
namespace CPP
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    class Solution
    {
    public:
        vector<int> preorderTraversal(TreeNode *root)
        {
            vector<int> foreword_value;
            stack<TreeNode *> traverse_stack;
            if (root != nullptr)
            {
                traverse_stack.push(root);
            }
            while (!traverse_stack.empty())
            {
                auto temp_node = traverse_stack.top();
                foreword_value.push_back(temp_node->val);
                traverse_stack.pop();
                if (temp_node->right != nullptr)
                {
                    traverse_stack.push(temp_node->right);
                }
                if (temp_node->left != nullptr)
                {
                    traverse_stack.push(temp_node->left);
                }
            }
            return foreword_value;
        }
    };
}
struct repeat_detect
    {
        char* first;
        char* second;
        char* third;
        bool judgment()
        {
            if(*first == *second && *second == *third)
            {
                return true;
            }
            return false;
        }
    };
int main()
{
    // [1,2,3,4,5,null,8,null,null,6,7,9]
    auto *root = new CPP::TreeNode(1);
    root->left = new CPP::TreeNode(2);
    root->right = new CPP::TreeNode(3);
    root->left->left = new CPP::TreeNode(4);
    root->left->right = new CPP::TreeNode(5);
    root->right->right = new CPP::TreeNode(8);
    root->left->right->left = new CPP::TreeNode(6);
    root->left->right->right = new CPP::TreeNode(7);
    root->right->right->left = new CPP::TreeNode(9);
    for (auto &value : CPP::Solution().preorderTraversal(root))
    {
        cout << " " << value;
    }
    repeat_detect tmp;
    tmp.first = "a";
    tmp.second = "a";
    tmp.third = "a";
    std::cout << std::endl << tmp.judgment() << std::endl;
    string s("泥嚎");
    s.clear();
    std::cout << s << std::endl;
    return 0;
}