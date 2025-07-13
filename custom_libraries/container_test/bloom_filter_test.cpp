#include "../template_container.hpp"
using namespace template_container;
int main() 
{
    // 1. 创建容量为10000的布隆过滤器
    bloom_filter_container::bloom_filter<std::string,template_container::algorithm::hash_algorithm::hash_function<std::string, std::hash<std::string> > > bf(10000);
    
    // 2. 插入元素
    bf.set("apple");
    bf.set("banana");
    bf.set("cherry");
    
    // 3. 查询元素
    std::cout << "查询 'apple': "  << (bf.test("apple")  ? "可能存在" : "一定不存在") << std::endl;
    std::cout << "查询 'cherry': " << (bf.test("cherry") ? "可能存在" : "一定不存在") << std::endl;
    std::cout << "查询 'grape': "  << (bf.test("grape")  ? "可能存在" : "一定不存在") << std::endl;
    
    // 4. 查看容量和大小
    std::cout << "布隆过滤器容量: " << bf.capacity() << std::endl;
    std::cout << "已使用位数: " << bf.size() << std::endl;
    
    return 0;
}