#include <iostream>
#include <unordered_map>
using namespace std;
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
        ListNode *deleteDuplicates(ListNode *head)
        {
            unordered_map<int, ListNode *> hash_map;
            ListNode head_node;
            ListNode *ren = &head_node;
            while (head != nullptr)
            {
                if (hash_map.find(head->val) == hash_map.end())
                {
                    hash_map[head->val] = head;
                    ren->next = head;
                    ren = ren->next;
                }
                head = head->next;
            }
            ren->next = nullptr;
            return head_node.next;
        }
    };
    class Solution_secound 
    {
    public:
        ListNode* deleteDuplicates(ListNode* head) 
        {
            ListNode* ren = head;
            ListNode* parent = nullptr;
            while(head != nullptr)
            {
                if(parent != nullptr && parent->val == head->val)
                {
                    parent->next = head->next;
                    delete head;
                    head = parent->next;
                    continue;
                }
                parent =  head;
                head = head->next;
            }
            return ren;
        }
    };
}
int main()
{
    // [1,1,2,3,3]
    CPP::ListNode node1(1);
    CPP::ListNode node2(1);
    CPP::ListNode node3(2);
    CPP::ListNode node4(3);
    CPP::ListNode node5(3);
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;
    node4.next = &node5;
    CPP::ListNode* temp_node =  CPP::Solution().deleteDuplicates(&node1);
   while(temp_node != nullptr)
   {
       cout << temp_node->val << endl;
       temp_node = temp_node->next;
       continue;
   }
    return 0;
}