#include <iostream>
#include <stack>
using namespace std;
// 题目：删除链表倒数的第N个节点
// https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
namespace CPP
{
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };
    class Solution
    {
    public:
        ListNode *removeNthFromEnd(ListNode *head, int n)
        {
            // 栈
            ListNode ren(0, head);
            stack<ListNode *> delete_stack;
            ListNode *cur = &ren;
            while (cur)
            {
                delete_stack.push(cur);
                cur = cur->next;
            }
            if (!delete_stack.empty())
            {
                for (int i = 0; i < n; ++i)
                {
                    delete_stack.pop();
                }
                ListNode *delete_prve_node = delete_stack.top();
                ListNode *delete_node = delete_prve_node->next;
                if (delete_node != nullptr)
                {
                    delete_prve_node->next = delete_node->next;
                    delete delete_node;
                }
            }
            return ren.next;
        }
    };
}
int main()
{
    CPP::Solution s;
    CPP::ListNode *head = nullptr;
    head = new CPP::ListNode(1);
    head->next = new CPP::ListNode(2);
    head->next->next = new CPP::ListNode(3);
    head->next->next->next = new CPP::ListNode(4);
    head->next->next->next->next = new CPP::ListNode(5);
    CPP::ListNode* new_list = s.removeNthFromEnd(head, 2);
    while(new_list)
    {
        cout << new_list->val << endl;
        new_list = new_list->next;
    }
    return 0;
}