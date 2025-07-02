#include <queue>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
//题目：数组中的第K个最大元素
//https://leetcode.cn/problems/kth-largest-element-in-an-array/description/?envType=problem-list-v2&envId=heap-priority-queue
namespace CPP
{
    class Solution 
    {           // NlogN
    public:
        int findKthLargest(vector<int>& nums, int k) 
        {
            
            priority_queue<int> heap;
            for(auto& insert_value : nums)
            {
                heap.push(insert_value);
            }
            for(int delete_frequency = 1; delete_frequency < k;delete_frequency++)
            {
                heap.pop();
            }
            return heap.top();
        }
    };
    int middle_size(vector<int>& nums, int left,int right)
    {
        int mid = nums.size()/2;
        if(nums[left] < nums[right])
        {
            if(nums[left] > nums[mid])
            {
                return left;
            }
            if(nums[mid] > nums[right])
            {
                return right;
            }
            return mid;
        }
        else if(nums[left] > nums[right])
        {
            if(nums[mid] > nums[left])
            {
                return left;
            }
            if(nums[right] > nums[mid])
            {
                return right;
            }
            return mid;
        }
        return left;
    }
    int qtravers(vector<int>& nums,int left,int right)
    {
        int mid = middle_size(nums,left,right);
        swap(nums[left],nums[mid]);
        int key = nums[left];
        int key_index = left;
        while(left < right)
        {
            while(left < right && nums[right] >= key)
            {
                right--;
            }
            while(left < right && nums[left] <= key)
            {
                left++;
            }
            swap(nums[left],nums[right]);
        }
        swap(nums[key_index],nums[left]);
        return key_index;
    }
    void quick_sort(vector<int>& nums)
    {
        stack<int> stack;
        stack.push(0);
        stack.push(nums.size()-1);
        while(!stack.empty())
        {
            int right = stack.top();
            stack.pop();
            int left = stack.top();
            stack.pop();
            int mid = qtravers(nums,left,right);
            if(mid-1 > left)
            {
                stack.push(left);
                stack.push(mid-1);
            }
            if(mid+1 < right)
            {
                stack.push(mid+1);
                stack.push(right);
            }
        }
    }
    class Solution_second
    {   //最后一个测试用例过不去
    public:
        int findKthLargest(vector<int>& nums, int k) 
        {
            quick_sort(nums);
            return nums[nums.size()-k];
        }
    };
}
int main()
{
    vector<int> nums_first  = {3,2,1,5,6,4};
    vector<int> nums_second = {3,2,3,1,2,4,5,5,6};
    CPP::Solution soulution_first;
    CPP::Solution_second soulution_second;
    cout << soulution_first.findKthLargest(nums_first, 2)   << std::endl;
    cout << soulution_first.findKthLargest(nums_second, 4)  << std::endl;
    cout << soulution_second.findKthLargest(nums_first, 2)  << std::endl;
    cout << soulution_second.findKthLargest(nums_second, 4) << std::endl;
    return 0;
}