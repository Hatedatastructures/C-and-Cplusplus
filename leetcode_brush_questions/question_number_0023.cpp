#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//题目：合并 K 个升序链表
//https://leetcode.cn/problems/merge-k-sorted-lists/description/?envType=problem-list-v2&envId=heap-priority-queue
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
    struct compareage
    {
        bool operator()(const ListNode* first,const ListNode* second)
        {
            return first->val > second->val;
        }
    };
    class Solution 
    {
    public:
        ListNode* mergeKLists(vector<ListNode*>& lists) 
        {
            if(lists.size() == 0)
            {
                return nullptr;
            }
            priority_queue<ListNode*,vector<ListNode*>,compareage> heap;
            for(auto& bucket : lists)
            {
                while(bucket != nullptr)
                {
                    heap.push(bucket);
                    bucket = bucket->next;
                }
            }
            ListNode* list_node = nullptr;
            ListNode* list_head_node = nullptr;
            while(heap.size())
            {
                if(list_node == nullptr)
                {
                    list_node = heap.top();
                    list_head_node = list_node;
                }
                else
                {
                    list_node->next = heap.top();
                    list_node = list_node->next;
                    if(heap.size() == 1)
                    {
                        list_node->next = nullptr;
                    }
                }
                heap.pop();
            }
            return list_head_node;
        }
    };
}
int main()
{
    //[[1,4,5],[1,3,4],[2,6]]
    vector<CPP::ListNode*> list_array;
    CPP::ListNode* node1 = new CPP::ListNode(1);
    CPP::ListNode* node2 = new CPP::ListNode(4);
    CPP::ListNode* node3 = new CPP::ListNode(5);
    node1->next = node2;
    node2->next = node3;
    list_array.push_back(node1);
    node1 = new CPP::ListNode(1);
    node2 = new CPP::ListNode(3);
    node3 = new CPP::ListNode(4);
    node1->next = node2;
    node2->next = node3;
    list_array.push_back(node1);
    node1 = new CPP::ListNode(2);
    node2 = new CPP::ListNode(6);
    node1->next = node2;
    list_array.push_back(node1);
    CPP::ListNode* new_list_node =  CPP::Solution().mergeKLists(list_array);
    while(new_list_node != nullptr)
    {
        cout << new_list_node->val << " ";
        new_list_node = new_list_node->next;
    }
    return 0;
}