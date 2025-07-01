#include <iostream>
#include <string>
#include <queue>
using namespace std;
//题目：回文数
//https://leetcode.cn/problems/palindrome-number/description/
namespace CPP
{
    class Solution 
    {
    public:
        bool isPalindrome(int x) 
        {
            string string_value = to_string(x);
            return string_value ==  string(string_value.rbegin(),string_value.rend());
        }
    };
}
int main()
{
    {
        CPP::Solution solution;
        cout << solution.isPalindrome(121)  << endl;
        cout << solution.isPalindrome(-121) << endl;
    }
    return 0;
}