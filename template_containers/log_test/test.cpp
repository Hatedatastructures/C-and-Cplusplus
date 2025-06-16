#include "../custom_logs.hpp"
#include "../template_container.hpp"
int main()
{
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    std::cout << current_time << std::endl;
    
    // 转换为本地时间结构
    std::tm* localTime = std::localtime(&current_time);
    
    // 格式化输出
    std::cout << "当前时间: " << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
    con::string file_name = "日志文件.txt";
    std::string storehouse_file_name = file_name.c_str();
    std::cout << custom_log::file_exists("日志文件.txt") << std::endl;
    std::cout << custom_log::file_exists(file_name) << std::endl;
    std::cout << custom_log::file_exists(storehouse_file_name) << std::endl;
    con::string count;
    std::cout << "输出count:" << count << std::endl;
    {
        con::string file_name = "日志文件.txt"; 
        if(custom_log::file_exists(file_name))
        {
            custom_log::foundation_log test_log (file_name);
            custom_log::information temp_information;
            temp_information.debugging_information_input("测试日志,进入作用域");
            temp_information.warning_messages_input("非法操作");

            test_log.write_file(temp_information,custom_log::log_timestamp_class::now());
        }
        else
        {
            std::cout << "文件不存在" << std::endl;
        }
    }
    return 0;
}