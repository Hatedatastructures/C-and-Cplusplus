#include "../custom_logs.hpp"
#include "../template_container.hpp"
int main()
{
    // {
    //     custom_log::foundation_log text_string_log (con::string("日志文件.txt"));
    //     con::string custom_string = "This is a foundation_log string";
    //     std::string storehouse_log_string = "This is a storehouse foundation_log string";
    //     std::cout << custom_string << std::endl;
    //     text_string_log.write_file(custom_string);
    //     text_string_log.write_file(custom_string);
    //     text_string_log.write_file("文件测试");
    //     text_string_log.write_file(custom_string);
    //     text_string_log.write_file(storehouse_log_string);
    // }
    // auto now = std::chrono::system_clock::now();
    // std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    // std::cout << current_time << std::endl;
    
    // // 转换为本地时间结构
    // std::tm* localTime = std::localtime(&current_time);
    
    // // 格式化输出
    // std::cout << "当前时间: " << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
    con::string file_name = "日志文件.txt";
    std::string storehouse_file_name = file_name.c_str();
    std::cout << custom_log::file_exists("日志文件.txt") << std::endl;
    std::cout << custom_log::file_exists(file_name) << std::endl;
    std::cout << custom_log::file_exists(storehouse_file_name) << std::endl;
    con::string count;
    std::cout << "输出count:" << count << std::endl;
    return 0;
}