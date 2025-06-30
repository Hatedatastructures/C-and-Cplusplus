#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;
//题目：寻找两个正序数组的中位数
//https://leetcode.cn/problems/median-of-two-sorted-arrays/?envType=problem-list-v2&envId=kWO4qAVh
namespace C
{
    double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) 
    {
        int* s1 = nums1;
        int* s2 = nums2;
        int* newnums = (int*)malloc(sizeof(int) * (nums1Size + nums2Size));
        if (!newnums) 
        {
            exit(-1);
        }
        int size = 0;
        int i = 0, j = 0;

        // 合并两个有序数组
        while (i < nums1Size && j < nums2Size) 
        {
            if (s1[i] < s2[j]) 
            {
                newnums[size++] = s1[i++];
            } 
            else 
            {
                newnums[size++] = s2[j++];
            }
        }
        // 处理 nums1 剩余元素
        while (i < nums1Size) 
        {
            newnums[size++] = s1[i++];
        }
        // 处理 nums2 剩余元素
        while (j < nums2Size) 
        {
            newnums[size++] = s2[j++];
        }
        double ret;
        if (size % 2 != 0) 
        {
            ret = newnums[size / 2];
        } 
        else 
        {
            //因为下标是从零开始的，下标为9实际上是10个数 10/2 = 5  (10/2) -1 = 4
            // 0 1 2 3 4 5 6 7 8 9      刚好4 5 在中间
            ret = (newnums[size / 2 - 1] + newnums[size / 2]) / 2.0;
        }

        // 释放动态分配的内存
        free(newnums);

        return ret;
    }
}
namespace CPP
{
    class Solution 
    {
    public:
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) 
        {
            int nums1_size = nums1.size();
            int nums2_size = nums2.size();
            vector<int> newnums ;
            int i = 0; int j = 0;
            while(i< nums1_size && j< nums2_size)
            {
                if(nums1[i] > nums2[j])
                {
                    newnums.push_back(nums2[j++]);
                }
                else
                {
                    newnums.push_back(nums1[i++]);
                }
                //先把容器元素个数少的插入到新容器中
            }
            while(i < nums1_size)
            {
                newnums.push_back(nums1[i++]);
            }
            while(j < nums2_size)
            {
                newnums.push_back(nums2[j++]);
            }
            //把剩下没有插入进去的补上1
            double return_ret;
            int newnums_size = newnums.size();
            if( newnums_size%2 != 0)
            {
                return_ret = newnums[newnums_size/2];
                return return_ret;
            }
            else
            {
                int size_v = newnums_size/ 2;
                int num1 = newnums[size_v -1];
                //因为下标是从零开始的，下标为9实际上是10个数 10/2 = 5  (10/2) -1 = 4
                // 0 1 2 3 4 5 6 7 8 9      刚好4 5 在中间
                int num2 = newnums[size_v];
                double return_ret = (num1+num2)/2.0;
                return return_ret;
            }
        }
    };
}






