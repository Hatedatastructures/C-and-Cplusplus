#include "../custom_logs.hpp"
int main()
{
    custom_log::configurator::custom_log_information_prefix = "[临时数据]";
    std::cout << custom_log::configurator::custom_log_information_prefix << std::endl;
    std::cout << default_document_checking_macros("text_log_.txt") << std::endl;
    custom_log::foundation_log test_name ("text_log_.txt");
    test_name.staging(default_custom_information_input_macros("这是宏测试"),default_timestamp_macros);
    test_name.push_to_file();
    return 0;
}