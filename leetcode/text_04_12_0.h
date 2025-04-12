#include <stdlib.h>
#include <stdio.h>
//题目：寻找两个正序数组的中位数
//https://leetcode.cn/problems/median-of-two-sorted-arrays/?envType=problem-list-v2&envId=kWO4qAVh
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
        ret = (newnums[size / 2 - 1] + newnums[size / 2]) / 2.0;
    }

    // 释放动态分配的内存
    free(newnums);

    return ret;
}










