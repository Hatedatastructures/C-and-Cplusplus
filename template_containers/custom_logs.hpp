#pragma once
#include "template_container.hpp"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
using custom_string = con::string;
using log_timestamp_class = std::chrono::system_clock;  //时间戳类
namespace custom_log
{
    [[nodiscard]] bool file_exists(const std::string& path)
    {
        std::ifstream status_judgment(path);
        return status_judgment.good();
    }
    [[nodiscard]] bool file_exists(const custom_string& path)
    {
        std::ifstream status_judgment(path.c_str());
        return status_judgment.good();
    }
    [[nodiscard]] bool file_exists(const char* path)
    {
        std::ifstream status_judgment(path);
        return status_judgment.good();
    }
    enum security_level
    {
        
    };
    class file_foundation_log
    {
    public:
        using inbuilt_documents = std::ofstream;
        inbuilt_documents file_ofstream;
        file_foundation_log() = default;
        file_foundation_log(const file_foundation_log& rhs) = delete;
        file_foundation_log(file_foundation_log&& rhs) = delete;
        file_foundation_log& operator=(const file_foundation_log& rhs) = delete;
        file_foundation_log& operator=(file_foundation_log&& rhs) = delete;
        ~file_foundation_log()
        {
            file_ofstream.close();
        }
        file_foundation_log(const custom_string& file_name)
        {
            file_ofstream.open(file_name.c_str());
        }
        file_foundation_log(const char* file_name)
        {
            file_ofstream.open(file_name);
        }
        file_foundation_log(const std::string& file_name)
        {
            file_ofstream.open(file_name.c_str());
        }
    };
    class information
    {
    public:
        custom_string debugging_information;        //调试信息
        custom_string general_information;          //一般信息
        custom_string warning_messages;             //警告信息
        custom_string error_messages;               //错误信息
        custom_string critical_misinformations;     //严重错误信息
        information() = default;
        information(const information& rhs) = delete;
        information(information&& rhs) = delete;
        information& operator=(const information& rhs) = delete;
        information& operator=(information&& rhs) = delete;
        ~information() = default;
        void debugging_information_input(const custom_string& information_data)
        {
            debugging_information = information_data;
        }
        void debugging_information_input(const std::string& information_data)
        {
            debugging_information = information_data.c_str();
        }
        void debugging_information_input(const char* information_data)
        {
            debugging_information = information_data;
        }
        void general_information_input(const custom_string& information_data)
        {
            general_information = information_data;
        }
        void general_information_input(const std::string& information_data)
        {
            general_information = information_data.c_str();
        }
        void general_information_input(const char* information_data)
        {
            general_information = information_data;
        }
        void warning_messages_input(const custom_string& information_data)
        {
            warning_messages = information_data;
        }
        void warning_messages_input(const std::string& information_data)
        {
            warning_messages = information_data.c_str();
        }
        void warning_messages_input(const char* information_data)
        {
            warning_messages = information_data;
        }
        void error_messages_input(const custom_string& information_data)
        {
            error_messages = information_data;
        }
        void error_messages_input(const std::string& information_data)
        {
            error_messages = information_data.c_str();
        }
        void error_messages_input(const char* information_data)
        {
            error_messages = information_data;
        }
        void critical_misinformations_input(const custom_string& information_data)
        {
            critical_misinformations = information_data;
        }
        void critical_misinformations_input(const std::string& information_data)
        {
            critical_misinformations = information_data.c_str();
        }
        void critical_misinformations_input(const char* information_data)
        {
            critical_misinformations = information_data;
        }
    };
    class function_stacks
    {
        con::stack<con::string> function_log_stacks;
    public:
        function_stacks() = default;
        function_stacks(const function_stacks& rhs) = delete;
        function_stacks(function_stacks&& rhs) = delete;
        function_stacks& operator=(const function_stacks& rhs) = delete;
        function_stacks& operator=(function_stacks&& rhs) = delete;
        ~function_stacks() = default;
        void push (const custom_string& function_name)
        {
            function_log_stacks.push(function_name);
        }
        void push(const std::string& function_name)
        {
            function_log_stacks.push(function_name.c_str());
        }
        void push(const char* function_name)
        {
            function_log_stacks.push(function_name);
        }
        con::string top()
        {
            return function_log_stacks.top();
        }
        size_t size()
        {
            return function_log_stacks.size();
        }
        bool empty()
        {
            return function_log_stacks.empty();
        }
        void pop()
        {
            function_log_stacks.pop();
        }
    };
    class foundation_log
    {
    private:
        std::chrono::_V2::system_clock::time_point foundation_log_timestamp;
    public:
        foundation_log() = default;
        foundation_log(const foundation_log& rhs) = delete;
        foundation_log(foundation_log&& rhs) = delete;
        foundation_log& operator=(const foundation_log& rhs) = delete;
        foundation_log& operator=(foundation_log&& rhs) = delete;
        ~foundation_log() = default;
        void timestamp_acquisition(const std::chrono::_V2::system_clock::time_point& timestamp_data) noexcept
        {
            foundation_log_timestamp = timestamp_data;
        }
    };
}
