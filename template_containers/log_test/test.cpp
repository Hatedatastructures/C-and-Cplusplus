#include "../custom_logs.hpp"
#include "../template_container.hpp"
#include "windows.h"
#include <random>
#include <thread>
size_t generate_random_size_t(size_t min, size_t max) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}
using log_one =  con::pair<custom_log::custom_string,size_t>;
class test_log
{
public:
    test_log() : test_log_pair(log_one(con::string(""), 0), 0) {}
    test_log(const con::string& test,const size_t& one,const size_t& two )
    {
        test_log_pair = con::pair<log_one,size_t>(log_one(test,one),two);
    }
    con::pair<log_one,size_t> test_log_pair;
    [[nodiscard]] const char* c_str()const
    {
        return test_log_pair.first.first.c_str();//管理未知数组
    }
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    auto now = std::chrono::system_clock::now();
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    std::cout << current_time << std::endl;
    
    // 转换为本地时间结构
    std::tm* localTime = std::localtime(&current_time);
    
    // 格式化输出
    std::cout << "当前时间: " << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
    con::string file_name = "text_log_.txt";
    std::string storehouse_file_name = file_name.c_str();
    std::cout << custom_log::file_exists("text_log_.txt") << std::endl;
    std::cout << custom_log::file_exists(file_name) << std::endl;
    std::cout << custom_log::file_exists(storehouse_file_name) << std::endl;
    std::cout << std::endl;
    {
        if(con::string name = "text_log_.txt"; custom_log::file_exists(name))
        {
            custom_log::foundation_log test_log (name);
            custom_log::information::information temp_information;
            temp_information.debugging_message_input("测试日志,进入作用域");
            temp_information.warning_message_input("非法操作");

            test_log.write_file(temp_information,custom_log::log_timestamp_class::now());
        }
        else
        {
            std::cout << "文件不存在" << std::endl ;
        }
    }
    con::vector<con::string> debugging = 
    {"开始计算权重","进入**函数","开始调用**函数","进行合并数据","输入样本"};
    con::vector<con::string> general = 
    {"环境:vs code + g++","项目编号:ROJ-2025-067","需求分析:已完成(100%)","负责人:张某某","Web服务:运行中端口 8080"};
    con::vector<con::string> warning = 
    {"磁盘空间剩余不足5%","内存使用率达90%","可能导致日志写入失败、服务卡顿或进程崩溃 ","存在远程代码执行漏洞","立即在防火墙封禁UDP 161/162端口(SNMP协议)"};
    con::vector<con::string> error =
    {"调用UserService时传入的userID=9999为无效用户","代码未对查询结果进行空值校验","检查前端参数合法性 ","错误码:EACCES (权限拒绝)","API调用失败"};
    con::vector<con::string> serious_error =
    {"ERR_DB_CONN_001","000","Excel文件解析失败","0x00000709","Operation not permitted"};
    {
        custom_log::foundation_log test_log(file_name);
        // if(test_log.file_buffer_adjustments(10))
        // {
        //     std::cout << "文件缓冲区调整成功" << std::endl;
        // }
        for(size_t list = 0; list < 1000; list++)
        {
            custom_log::information::information temp_information;
            temp_information.debugging_message_input(debugging[generate_random_size_t(1763824,347632485789)% debugging.size()]);
            temp_information.warning_message_input(warning[generate_random_size_t(1763824,347632485789)% warning.size()]);
            temp_information.general_message_input(general[generate_random_size_t(1763824,347632485789)% general.size()]);
            temp_information.error_message_input(error[generate_random_size_t(1763824,347632485789)% error.size()]);
            temp_information.serious_error_message_input(serious_error[generate_random_size_t(1763824,347632485789)% serious_error.size()]);
            // Sleep(generate_random_size_t(6,37));
            test_log.staging(temp_information,custom_log::log_timestamp_class::now());
            std::cout << "###进度 :" << static_cast<double>(list)/10 << "% / 100%" << "..." << std::endl;
        }
        std::cout << "暂存没问题" << std::endl;
        test_log.push();
        std::cout << "写入文件成功" << std::endl;
    }
    {
        test_log v1_(con::string("测试日志,进入作用域"),1,2);
        custom_log::foundation_log<test_log> two_test_log(file_name);
        custom_log::information::information<test_log> temp_information;
        test_log test_(con::string("测试日志,进入作用域"),1,2);
        temp_information.custom_log_message_input(test_); 
        // std::cout << temp_information.to_custom_string() << std::endl;
        two_test_log.staging(temp_information,default_timestamp_macros);
        two_test_log.push();
    }
    {
        custom_log::foundation_log _v2(file_name);
        _v2.staging(custom_log::information::information().custom_log_macro_function_input("测试日志,进入作用域"),default_timestamp_macros);
        _v2.push_to_console();
        _v2.push_to_file();
        _v2.push();
    }
    system("pause");
    std::thread test([&]    {   std::cout << "hello,word!" << file_name << std::endl;   } );
    test.join();
    std::cout << "程序结束" << std::endl;
    system("pause");
    
    return 0;
}
