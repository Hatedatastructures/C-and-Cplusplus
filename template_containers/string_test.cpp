#include "template_container.hpp"
using namespace template_container;


int main() {
    // 1. 构造函数示例
    std::cout << "=== 构造函数示例 ===\n";
    
    // 默认构造函数
    string_container::string s1;
    std::cout << "s1 (默认构造): " << s1 << std::endl;
    
    // C风格字符串构造
    string_container::string s2("Hello");
    std::cout << "s2 (C风格字符串构造): " << s2 << std::endl;
    
    // 拷贝构造
    string_container::string s3(s2);
    std::cout << "s3 (拷贝构造自s2): " << s3 << std::endl;
    
    // 移动构造 (使用临时对象)
    string_container::string s4(string_container::string("World"));
    std::cout << "s4 (移动构造): " << s4 << std::endl;
    
    // 初始化列表构造
    string_container::string s5({'H', 'e', 'l', 'l', 'o'});
    std::cout << "s5 (初始化列表构造): " << s5 << std::endl;
    
    // 2. 访问元素示例
    std::cout << "\n=== 访问元素示例 ===\n";
    
    // 下标运算符
    std::cout << "s2[0]: " << s2[0] << std::endl;
    
    // front() 和 back()
    std::cout << "s2.front(): " << s2.front() << std::endl;
    std::cout << "s2.back(): " << s2.back() << std::endl;
    
    // c_str()
    std::cout << "s2.c_str(): " << s2.c_str() << std::endl;
    
    // 3. 字符串修改示例
    std::cout << "\n=== 字符串修改示例 ===\n";
    
    // push_back() 添加单个字符
    s2.push_back('!');
    std::cout << "s2.push_back('!'): " << s2 << std::endl;
    
    // push_back() 添加字符串
    s2.push_back(string_container::string(" World"));
    std::cout << "s2.push_back(\" World\"): " << s2 << std::endl;
    
    // push_back() 添加C风格字符串
    s2.push_back(" Again");
    std::cout << "s2.push_back(\" Again\"): " << s2 << std::endl;
    
    // prepend() 在开头插入
    s2.prepend("Hi, ");
    std::cout << "s2.prepend(\"Hi, \"): " << s2 << std::endl;
    
    // insert_sub_string() 在中间插入
    const char* str_test = " there";
    s2.insert_sub_string(str_test, 4);
    std::cout << "s2.insert_sub_string(\" there\", 4): " << s2 << std::endl;
    
    // resize() 调整大小
    s2.resize(10, 'x');
    std::cout << "s2.resize(10, 'x'): " << s2 << std::endl;
    
    s2.resize(20, 'y');
    std::cout << "s2.resize(20, 'y'): " << s2 << std::endl;
    
    // 4. 子串与反转示例
    std::cout << "\n=== 子串与反转示例 ===\n";
    
    // sub_string() 提取子串
    string_container::string sub1 = s2.sub_string(3);
    std::cout << "s2.sub_string(3): " << sub1 << std::endl;
    
    string_container::string sub2 = s2.sub_string_from(5);
    std::cout << "s2.sub_string_from(5): " << sub2 << std::endl;
    
    string_container::string sub3 = s2.sub_string(2, 8);
    std::cout << "s2.sub_string(2, 8): " << sub3 << std::endl;
    
    // reverse() 反转字符串
    string_container::string rev1 = s2.reverse();
    std::cout << "s2.reverse(): " << rev1 << std::endl;
    
    // reverse_sub_string() 反转子串
    string_container::string rev2 = s2.reverse_sub_string(3, 8);
    std::cout << "s2.reverse_sub_string(3, 8): " << rev2 << std::endl;
    
    // 5. 大小写转换示例
    std::cout << "\n=== 大小写转换示例 ===\n";
    
    s2.uppercase();
    std::cout << "s2.uppercase(): " << s2 << std::endl;
    
    s2.lowercase();
    std::cout << "s2.lowercase(): " << s2 << std::endl;
    
    // 6. 容量与工具方法示例
    std::cout << "\n=== 容量与工具方法示例 ===\n";
    
    std::cout << "s2.empty(): " << (s2.empty() ? "true" : "false") << std::endl;
    std::cout << "s2.size(): " << s2.size() << std::endl;
    std::cout << "s2.capacity(): " << s2.capacity() << std::endl;
    
    // reserve() 预分配空间
    s2.reserve(100);
    std::cout << "s2.reserve(100) 后 capacity: " << s2.capacity() << std::endl;
    
    // swap() 交换字符串
    string_container::string temp("Temp String");
    s2.swap(temp);
    std::cout << "s2.swap(temp) 后 s2: " << s2 << std::endl;
    std::cout << "s2.swap(temp) 后 temp: " << temp << std::endl;
    
    // 7. 运算符重载示例
    std::cout << "\n=== 运算符重载示例 ===\n";
    
    // 赋值运算符
    s2 = "New Value";
    std::cout << "s2 = \"New Value\": " << s2 << std::endl;
    
    s2 = string_container::string("Another Value");
    std::cout << "s2 = string(\"Another Value\"): " << s2 << std::endl;
    
    // += 运算符
    s2 += " appended";
    std::cout << "s2 += \" appended\": " << s2 << std::endl;
    
    // + 运算符
    string_container::string s6 = s2 + " and more";
    std::cout << "s6 = s2 + \" and more\": " << s6 << std::endl;
    
    // 比较运算符
    string_container::string s7("Test");
    string_container::string s8("Test");
    string_container::string s9("Different");
    
    std::cout << "s7 == s8: " << (s7 == s8 ? "true" : "false") << std::endl;
    std::cout << "s7 == s9: " << (s7 == s9 ? "true" : "false") << std::endl;
    std::cout << "s7 < s9: " << (s7 < s9 ? "true" : "false") << std::endl;
    std::cout << "s7 > s9: " << (s7 > s9 ? "true" : "false") << std::endl;
    
    // 8. 输入输出示例
    std::cout << "\n=== 输入输出示例 ===\n";
    
    // 输出
    std::cout << "请输入一个字符串: ";
    string_container::string input;
    std::cin >> input;
    std::cout << "你输入的是: " << input << std::endl;
    
    // 9. 迭代器示例
    std::cout << "\n=== 迭代器示例 ===\n";
    
    std::cout << "使用迭代器遍历 s2: ";
    for (auto it = s2.begin(); it != s2.end(); ++it) {
        std::cout << *it;
    }
    std::cout << std::endl;
    
    std::cout << "使用反向迭代器遍历 s2: ";
    for (auto it = s2.rbegin(); it != s2.rend(); --it) {
        std::cout << *it;
    }
    std::cout << std::endl;
    
    // 10. 工具方法
    std::cout << "\n=== 工具方法示例 ===\n";
    
    std::cout << "打印 s2: ";
    s2.string_print();
    
    std::cout << "反向打印 s2: ";
    s2.string_reverse_print();
    
    return 0;
}
