#include <vector>
#include <iostream>
#include <queue>
using namespace std;
//题目：数据流的中位数
//https://leetcode.cn/problems/find-median-from-data-stream/description/?envType=problem-list-v2&envId=heap-priority-queue
class MedianFinder 
{
    priority_queue<int,vector<int>,less<int>>    min_heap;
    priority_queue<int,vector<int>,greater<int>> max_heap;
public:
    MedianFinder() 
    {
        ;
    }
    
    void addNum(int num) 
    {
        if(min_heap.empty() || num <= min_heap.top())
        {
            min_heap.push(num);
            if (max_heap.size() + 1 < min_heap.size()) 
            {
                max_heap.push(min_heap.top());
                min_heap.pop();
            }
        }
        else
        {
            max_heap.push(num);
            if (max_heap.size() > min_heap.size()) 
            {
                min_heap.push(max_heap.top());
                max_heap.pop();
            }
        }
    }
    
    double findMedian() 
    {
        if (min_heap.size() > max_heap.size()) 
        {
            return min_heap.top();
        }
        return (min_heap.top() + max_heap.top()) / 2.0;
    }
};
int main()
{
    MedianFinder* obj = new MedianFinder();
    obj->addNum(1);
    obj->addNum(2);
    cout << obj->findMedian() << endl;
    return 0;
}
