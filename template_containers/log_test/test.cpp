#include "../custom_logs.hpp"
#include "../template_container.hpp"
int main()
{
    {
        file_log::log text_string_log (con::string("日志文件.txt"));
        const con::string log_string = "This is a log string";
        std::cout << log_string << std::endl;
        text_string_log.write_file(log_string);
        text_string_log.write_file(log_string);
        text_string_log.wield_file("文件测试");
        // text_string_log.wield_file(log_string);
    }
    return 0;
}