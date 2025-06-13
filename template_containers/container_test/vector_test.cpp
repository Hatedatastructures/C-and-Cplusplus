#include "../template_container.hpp"
using namespace template_container;

int main()
{
    // 1. 构造函数示例
    std::cout << "=== 构造函数示例 ===\n";

    // 默认构造
    vector_container::vector<double> v1;
    std::cout << "v1 (默认构造): " << v1 << std::endl;

    // 指定容量构造
    vector_container::vector<double> v2(5, 3.14);
    std::cout << "v2 (指定容量构造): " << v2 << std::endl;

    // 初始化列表构造
    vector_container::vector<std::string> v3 = {"hello", "world", "!"};
    std::cout << "v3 (初始化列表构造): " << v3 << std::endl;

    // 拷贝构造
    vector_container::vector<double> v4(v2);
    std::cout << "v4 (拷贝构造自v2): " << v4 << std::endl;

    // 移动构造
    vector_container::vector<double> v5(std::move(v1));
    std::cout << "v5 (移动构造): " << v5 << std::endl;
    std::cout << "v1 (移动后): " << v1 << std::endl;

    // 2. 访问元素示例
    std::cout << "\n=== 访问元素示例 ===\n";

    // 下标运算符
    std::cout << "v3[0]: " << v3[0] << std::endl;

    // front() 和 back()
    std::cout << "v3.front(): " << v3.front() << std::endl;
    std::cout << "v3.back(): " << v3.back() << std::endl;

    // head() 和 tail()
    std::cout << "v3.head(): " << v3.head() << std::endl;
    std::cout << "v3.tail(): " << v3.tail() << std::endl;

    // find()
    std::cout << "v3.find(1): " << v3.find(1) << std::endl;

    // 3. 容器修改示例
    std::cout << "\n=== 容器修改示例 ===\n";

    // push_back()
    v3.push_back("new");
    std::cout << "v3.push_back(\"new\"): " << v3 << std::endl;

    // push_back() 移动语义
    std::string temp = "moved";
    v3.push_back(std::move(temp));
    std::cout << "v3.push_back(std::move(temp)): " << v3 << std::endl;

    // push_front()
    v3.push_front("start");
    std::cout << "v3.push_front(\"start\"): " << v3 << std::endl;

    // pop_back()
    v3.pop_back();
    std::cout << "v3.pop_back(): " << v3 << std::endl;

    // pop_front()
    v3.pop_front();
    std::cout << "v3.pop_front(): " << v3 << std::endl;

    // erase()
    auto it = v3.begin() + 1;
    v3.erase(it);
    std::cout << "v3.erase(v3.begin() + 1): " << v3 << std::endl;

    // resize()
    v3.resize(10, "default");
    std::cout << "v3.resize(10, \"default\"): " << v3 << std::endl;

    // size_adjust()
    v3.size_adjust(5, "adjusted");
    std::cout << "v3.size_adjust(5, \"adjusted\"): " << v3 << std::endl;


    // swap()
    vector_container::vector<std::string> v6 = {"a", "b", "c"};
    v3.swap(v6);
    std::cout << "v3.swap(v6) 后 v3: " << v3 << std::endl;
    std::cout << "v3.swap(v6) 后 v6: " << v6 << std::endl;

    // 4. 容量与工具方法示例
    std::cout << "\n=== 容量与工具方法示例 ===\n";

    std::cout << "v3.empty(): " << (v3.empty() ? "true" : "false") << std::endl;
    std::cout << "v3.size(): " << v3.size() << std::endl;
    std::cout << "v3.capacity(): " << v3.capacity() << std::endl;

    // 5. 运算符重载示例
    std::cout << "\n=== 运算符重载示例 ===\n";

    // 赋值运算符
    v1 = v4;
    std::cout << "v1 = v4: " << v1 << std::endl;

    // 移动赋值
    v1 = std::move(v4);
    std::cout << "v1 = std::move(v4): " << v1 << std::endl;
    std::cout << "v4 (移动后): " << v4 << std::endl;

    // += 运算符
    v1 += v2;
    std::cout << "v1 += v2: " << v1 << std::endl;

    // 6. 迭代器示例
    std::cout << "\n=== 迭代器示例 ===\n";

    // 正向迭代器
    std::cout << "正向迭代器遍历 v3: ";
    for (auto iterator = v3.begin(); iterator != v3.end(); ++iterator)
    {
        std::cout << *iterator << " ";
    }
    std::cout << std::endl;

    // 反向迭代器
    // std::cout << "反向迭代器遍历 v3: ";
    // for (auto ref_it = v3.rbegin(); ref_it != v3.rend(); --ref_it)
    // {
    //     std::cout << *ref_it << " ";
    // }
    // std::cout << std::endl;

    // 7. 异常处理示例
    std::cout << "\n=== 异常处理示例 ===\n";

    try 
    {
        // 尝试访问越界元素
        std::cout << "尝试访问 v3[10]: ";
        std::cout << v3[10] << std::endl;
    } catch (const custom_exception::customize_exception& e) 
    {
        std::cout << "捕获异常: " << e.what() << " 在 " << e.function_name_get()
                  << " 行 " << e.line_number_get() << std::endl;
    }

    // 8. 内存管理示例
    std::cout << "\n=== 内存管理示例 ===\n";

    // 测试扩容策略
    vector_container::vector<int> v7;
    std::cout << "v7 初始容量: " << v7.capacity() << std::endl;

    for (int i = 0; i < 20; ++i)
    {
        v7.push_back(i);
        if (i % 5 == 0) 
        {
            std::cout << "添加 " << i << " 后容量: " << v7.capacity() << std::endl;
        }
    }

    return 0;
}