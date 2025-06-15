#pragma once
#include "template_container.hpp"
#include <fstream>
namespace file_log
{
    class log
    {
    private:
        using log_string = con::string;
        using log_file   = std::ofstream;
        log_string file_name;
        log_file file;          //文件对象
    public:
        log() = default;
        log(const log& rhs) = delete;
        log(log&& rhs) = delete;
        log& operator=(const log& rhs) = delete;
        log& operator=(log&& rhs) = delete;

        explicit log(const char* str_log)
        {
            file_name = str_log;
            file.open(file_name.c_str());
        }
        explicit log(const log_string& customize_string_log)
        {
            file_name = customize_string_log;
            file.open(file_name.c_str());
        }
        void wield_file(const char* str_log)
        {
            file << str_log << std::endl;
        }
        void write_file(const log_string& customize_string_log)
        {
            file << customize_string_log << std::endl;
        }
        virtual ~log()
        {
            file.close();
        }
    };
}
