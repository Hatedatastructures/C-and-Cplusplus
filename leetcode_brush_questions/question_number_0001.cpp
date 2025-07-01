#include <iostream>
#include <vector>
#include <thread>
#include "windows.h"
#include <unordered_map>
using namespace std;
//题目：两数之和
//https://leetcode.cn/problems/two-sum/description/?envType=problem-list-v2&envId=hash-table
namespace CPP
{
    class Solution 
    {
    public:
        vector<int> twoSum(vector<int>& nums, int target) 
        {
            unordered_map<int,int> hash_table;
            int size = 0;
            for(auto traverse_results : nums)
            {
                auto temp_value = hash_table.find(target - traverse_results);
                if(temp_value != hash_table.end())
                {
                    return {temp_value->second,size};
                }   //如果没找到就插入进去开启下一循环
                hash_table.insert(std::pair<int,int>(traverse_results,size));
                ++size;
            }
            return {};
        }
    };
}
void cpp_procedure()
{
    using test_type = pair<vector<int>,int>;
    test_type test_example_first  = {{2,7,11,15},9};
    test_type test_example_second = {{3,2,4},6};
    test_type test_example_third  = {{3,3},6};
    vector<vector<int>> temporary_data_pools;
    CPP::Solution function_value;
    temporary_data_pools.push_back(function_value.twoSum(test_example_first.first,test_example_first.second));
    temporary_data_pools.push_back(function_value.twoSum(test_example_second.first,test_example_second.second));
    temporary_data_pools.push_back(function_value.twoSum(test_example_third.first,test_example_third.second));
    for(auto temporary_data : temporary_data_pools)
    {
        for(auto temporary_data_value : temporary_data)
        {
            std::cout << temporary_data_value << " ";
        }
        std::cout << std::endl;
    }
}
int main()
{
    thread cpp_thread([]{cpp_procedure();});
    cpp_thread.join();
    Sleep(1000);
    return 0;
}