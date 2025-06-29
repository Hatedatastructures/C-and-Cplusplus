// 题目： 两数相加
// https://leetcode.cn/problems/add-two-numbers/
#include <stdio.h>
#include <stdlib.h>
namespace C
{
    struct ListNode 
    {
        int val;
        struct ListNode* next;
    };
    void push_back(struct ListNode** cur , int val )
    {
        struct ListNode* list = (struct ListNode*)malloc(sizeof(struct ListNode));
        list->next = NULL;
        //如果list->next不置为空，则会出现野指针，出现内存错误等
        if (list == NULL) 
        {
            return;
        }
        if(*cur == NULL)
        {
            list->val = val ;
            *cur = list;
        }
        else
        {
            struct ListNode* temp = *cur ;
            while(temp->next)
            {
                temp = temp->next;
            }
            //找末尾
            list->val = val ;
            temp->next = list;
        }
    }
    struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) 
    {
        struct ListNode* head = NULL;
        int carry = 0; // 进位变量
        //如果while循环内没有carry判断，可以在循环判断过后检查carry，拷贝在链表的最后一个节点
        while (l1 || l2 || carry) 
        { 
            // 当 l1、l2 有节点或还有进位时循环
            int head_val = l1 ? l1->val : 0;
            int tail_val = l2 ? l2->val : 0;
            int sum = head_val + tail_val + carry;

            carry = sum / 10; 

            int list_val = sum % 10; 
            // 取个位
            push_back(&head, list_val);
            if (l1) 
            {
                l1 = l1->next; // 移动 l1
            }

            if (l2) 
            {
                l2 = l2->next; // 移动 l2
            }
        }
        //没有需要释放的内存
        return head;
    }
}

namespace CPP
{   //   C++  代码
    class Solution 
    {
    private:
        struct ListNode 
        {
            int val;
            ListNode *next;
            ListNode() : val(0), next(nullptr) 
            {
                ;
            }
            ListNode(int x) : val(x), next(nullptr) 
            {
                ;
            }
            ListNode(int x, ListNode *next) : val(x), next(next) 
            {
                ;
            }
        };
    public:
    //实现
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
        {
            ListNode* head = nullptr;
            //创建头节点一定要初始化为空
            size_t len_sum = 0;
            size_t sum = 0;
            //加上sum判断保证在最后一个节点在还有值的情况下完成拷贝
            while(l1 || l2 || sum )
            {
                int L1_val = l1 ? l1->val : 0 ;
                int l2_val = l2 ? l2->val : 0 ;

                len_sum = L1_val + l2_val + sum;
                sum = len_sum / 10;
                //计算进位数
                int temp_val = len_sum % 10;
                //计算个位
                if(head != nullptr)
                {
                    ListNode* temp = head;
                    while(temp->next)
                    {
                        temp = temp->next;
                    } 
                    ListNode* _val  = new ListNode(temp_val);
                    temp->next = _val;
                }
                else
                {
                    ListNode* temp = new ListNode(temp_val);
                    head = temp;
                }

                if( l1 )
                {
                    l1 = l1->next;
                }
                if( l2 )
                {
                    l2 = l2->next;
                }
                
            }
            return head;
        }
    };
}