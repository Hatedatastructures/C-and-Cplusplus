#pragma once
#include "template_container.hpp"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
namespace custom_log
{
    using custom_string = con::string;
    using log_timestamp_class = std::chrono::system_clock;  //时间戳类
    using log_timestamp_type = std::chrono::system_clock::time_point;
    [[nodiscard]] inline bool file_exists(const std::string& path)
    {
        std::ifstream status_judgment(path);
        return status_judgment.good();
    }
    [[nodiscard]] inline bool file_exists(const custom_string& path)
    {
        std::ifstream status_judgment(path.c_str());
        return status_judgment.good();
    }
    [[nodiscard]] inline bool file_exists(const char* path)
    {
        std::ifstream status_judgment(path);
        return status_judgment.good();
    }
    enum class severity_level 
    {
        TRIVIAL = 0,    // 轻微问题，不影响系统运行
        MINOR = 1,      // 次要问题，可能需要注意
        MODERATE = 2,   // 中等问题，需要处理
        MAJOR = 3,      // 主要问题，影响系统功能
        CRITICAL = 4,   // 严重问题，导致部分功能失效
        BLOCKER = 5,    // 阻塞问题，系统无法正常运行
        FATAL = 6       // 致命错误，系统崩溃或数据丢失
    };
    class information
    {
        #define DECLARE_INFO_INPUT(type)template<typename macro_parameters>\
        void type##_message_input(const macro_parameters& data){type##_information = to_custom_string(data);} 
    protected:
        static custom_string to_custom_string(const std::string& string_value) 
        {
            return custom_string(string_value.c_str());
        }
        static custom_string to_custom_string(const custom_string& string_value)
        {
            return string_value;
        }
        static custom_string to_custom_string(const char* string_value)
        {
            return custom_string(string_value);
        }
    public:
        custom_string debugging_information;        //调试信息
        custom_string general_information;          //一般信息
        custom_string warning_information;          //警告信息
        custom_string error_information;            //错误信息
        custom_string serious_error_information;    //严重错误信息
        information() = default;
        information(const information& rhs) = delete;
        information(information&& rhs) = delete;
        information& operator=(const information& rhs) = delete;
        information& operator=(information&& rhs) = delete;
        ~information() = default;
        DECLARE_INFO_INPUT(debugging)
        DECLARE_INFO_INPUT(general)
        DECLARE_INFO_INPUT(warning)
        DECLARE_INFO_INPUT(error)
        DECLARE_INFO_INPUT(serious_error)
    };
    // 定义一个名为file_foundation_log的类
    class file_foundation_log
    {
    protected:
        const char* convert_to_cstr(const std::string& string_value)        {return string_value.c_str();}
        const char* convert_to_cstr(const custom_string& string_value)      {return string_value.c_str();}
        const char* convert_to_cstr(const char* str_value)                  {return str_value;}
        const char* convert_to_string(const custom_string& string_value)    {return string_value.c_str(); }
        const char* convert_to_string(const std::string& string_value)      {return string_value.c_str(); }
        const char* convert_to_string(const char* str_value)                {return str_value; }
        con::string format_time(const log_timestamp_type& time_value) 
        {
            auto time_t = std::chrono::system_clock::to_time_t(time_value);
            std::tm* local_time = std::localtime(&time_t);
            std::ostringstream oss;
            oss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");
            return oss.str().c_str();
        }
        template<typename file_open>
        void open_file(const file_open& file_name) 
        {
            file_ofstream.open(convert_to_cstr(file_name));
        }
        con::string format_information(const information& information_value)const
        {
            std::ostringstream oss;
            oss << "[DEBUG]("    << information_value.debugging_information     << ") " 
                << "[INFO]("     << information_value.general_information       << ") " 
                << "[WARNING]("  << information_value.warning_information       << ") "
                << "[ERROR]("    << information_value.error_information         << ") "
                << "[CRITICAL](" << information_value.serious_error_information << ") ";
            return oss.str().c_str();
        }
    public:
        using inbuilt_documents = std::ofstream;
        inbuilt_documents file_ofstream;
        file_foundation_log() = default;
        file_foundation_log(const file_foundation_log& rhs) = delete;
        file_foundation_log(file_foundation_log&& rhs) = delete;
        file_foundation_log& operator=(const file_foundation_log& rhs) = delete;
        file_foundation_log& operator=(file_foundation_log&& rhs) = delete;
        ~file_foundation_log()      {file_ofstream.close();}
        template<typename structure>
        file_foundation_log(const structure& file_name) 
        {
            open_file(file_name);
        }
        template<typename file_write>
        void write(const file_write& file_value) 
        {
            file_ofstream << convert_to_string(file_value);
        }
        void write(const log_timestamp_type& time_value)
        {
            file_ofstream << "[" << std::chrono::system_clock::to_time_t(time_value) << "] " ;
        }
        void write(const information& information_value) 
        {
            file_ofstream << format_information(information_value).c_str();
        }
        void data(const log_timestamp_type& time) 
        {
            file_ofstream << "[运行时间]" << format_time(time).c_str() << std::endl << std::endl;
        }   //让结构更清晰
        con::string get_string_str(const information& information_value)const
        {
            con::string temporary_string;
            temporary_string = format_information(information_value);
            return temporary_string;
        }
    };
    class function_stacks //作为高级日志中控调用
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
        con::string top() const {return function_log_stacks.top();}
        size_t size()           {return function_log_stacks.size();}
        bool empty() const      {return function_log_stacks.empty();}
        void pop()              {function_log_stacks.pop();}
    };
    class foundation_log
    {
        using foundation_log_type = con::pair<con::string,log_timestamp_type>;
    private:
        file_foundation_log log_file;
        con::vector<foundation_log_type> temporary_string_buffer;
        foundation_log_type temporary_caching(const information& log_information,const log_timestamp_type& time = log_timestamp_class::now())
        {
            con::string temporary_string_caching = log_file.get_string_str(log_information);
            return foundation_log_type(temporary_string_caching,time);
        }
    public:
        foundation_log(const foundation_log& rhs) = delete;
        foundation_log(foundation_log&& rhs) = delete;
        foundation_log& operator=(const foundation_log& rhs) = delete;
        foundation_log& operator=(foundation_log&& rhs) = delete;
        ~foundation_log() = default;
        foundation_log(const custom_string& log_file_name)
        :log_file(log_file_name){}
        foundation_log(const std::string& log_file_name)
        :log_file(log_file_name.c_str()){}
        foundation_log(const char* log_file_name)
        : log_file(log_file_name){}
        virtual void write_file(const information& log_information,const log_timestamp_type& time = log_timestamp_class::now())
        {
            log_file.write(time);
            log_file.write(log_information);
            log_file.data(time);
        }
        virtual void staging(const information& log_information,const log_timestamp_type& time = log_timestamp_class::now())
        {
            temporary_string_buffer.push_back(temporary_caching(log_information,time));
        }
        virtual void push_to_file()
        {
            con::vector<foundation_log_type> new_temporary_string_buffer;
            for(auto& cushioningp : temporary_string_buffer)
            {
                log_file.write(cushioningp.second);
                log_file.write(cushioningp.first);
                log_file.data(cushioningp.second);
            }
            new_temporary_string_buffer.swap(temporary_string_buffer);
        }
    };
    class log : private custom_log::foundation_log
    {
    private:
        function_stacks function_call_stack;
    public:
        template <typename file_name>
        log(const file_name& file)
        {
            log::foundation_log::foundation_log(file);
        }
        // virtual write_file(const information& log_information,constlog_timestamp_type& time = log_timestamp_class::now()) override
        // {

        // }
        ~log() = default;
    };
}
