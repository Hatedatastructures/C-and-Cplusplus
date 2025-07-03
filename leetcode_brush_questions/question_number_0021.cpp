#include <iostream>
using namespace std;
// 题目：合并两个有序链表
// https://leetcode.cn/problems/merge-two-sorted-lists/description/?envType=problem-list-v2&envId=linked-list
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
        ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
        {
            ListNode head_node;
            ListNode *new_list = &head_node;
            while (list1 != nullptr && list2 != nullptr)
            {
                if (list1->val < list2->val)
                {
                    new_list->next = list1;
                    list1 = list1->next;
                }
                else
                {
                    new_list->next = list2;
                    list2 = list2->next;
                }
                new_list = new_list->next;
            }
            new_list->next = list1 ? list1 : list2;
            // 如果上面有一个链表没拼接完成到下面会继续拼接
            return head_node.next;
            // 用哨兵点位的下一个来返回避免了其他问题
        }
    };
}
int main()
{
    CPP::ListNode* list1 = new CPP::ListNode(1);
    list1->next = new CPP::ListNode(2);
    list1->next->next = new CPP::ListNode(4);
    CPP::ListNode* list2 = new CPP::ListNode(1);
    list2->next = new CPP::ListNode(3);
    list2->next->next = new CPP::ListNode(4);
    CPP::Solution soulution;
    CPP::ListNode* new_list = soulution.mergeTwoLists(list1,list2);
    while(new_list != nullptr)
    {
        cout << new_list->val << " ";
        new_list = new_list->next;
    }
    cout << std::endl;
    return 0;
}