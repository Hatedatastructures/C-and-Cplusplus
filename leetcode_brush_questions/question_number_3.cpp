#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
//题目：无重复字符的最长子串
//https://leetcode.cn/problems/longest-substring-without-repeating-characters/
namespace CPP
{
    class Solution 
    {
    public:
        int lengthOfLongestSubstring(string s) 
        {
            unordered_map<char,int> hash_table;
            int left = -1 ,return_size = 0;
            for(int right = 0; right < static_cast<int>(s.size()); right++)
            {
                if(hash_table.find(s[right]) != hash_table.end())
                {   //找到了相同的字符，需要更新左指针的位置
                    left = max(left,hash_table.find(s[right])->second);
                    /*  
                    为什么会找字符在哈希表中有没有位置呢？
                    因为:如果有就代表必定有重复的字符串，需要更新左指针的位置到重复字符的位置继续找下一个重复子串
                    */
                }
                hash_table[s[right]] = right;
                // 没找到就把字符和它的下标位置存入哈希表
                return_size = max(return_size,right - left);
                //更新长度
            }
            return return_size;
        }
    };
}
int main()
{
    {
        string string_first  = "abcabcbb";
        string string_second = "bbbbb";
        string string_third  = "pwwkew";
        cout << CPP::Solution().lengthOfLongestSubstring(string_first)  << endl;
        cout << CPP::Solution().lengthOfLongestSubstring(string_second) << endl;
        cout << CPP::Solution().lengthOfLongestSubstring(string_third)  << endl;
    }
    return 0;
}