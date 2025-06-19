#include "../custom_logs.hpp"
int main()
{
    custom_log::configurator::custom_log_information_prefix = "[临时数据]";
    std::cout << custom_log::configurator::custom_log_information_prefix << std::endl;
    return 0;
}