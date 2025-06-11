#pragma once
#include "template_container.hpp"
#include <fstream>
namespace file_log
{
    class log
    {
    private:
        using log_string = template_container::string_container::string;
        using log_file   = std::ofstream;
        log_string file_name;
        log_file file;
    public:
        log() = default;
        log(const log& rhs) = delete;
        log(log&& rhs) = delete;
        log& operator=(const log& rhs) = delete;
        log& operator=(log&& rhs) = delete;

        explicit log(const char* str_data)
        {
            file_name = str_data;
            file.open(file_name.c_str());
        }

        explicit log(const log_string& string_data)
        {
            file_name = string_data;
            file.open(file_name.c_str());
        }
        virtual void write_file(const log_string& string_data)
        {
            file << string_data << std::endl;
        }
        virtual void wield_file(const char str_data)
        {
            file << str_data << std::endl;
        }
        virtual ~log()
        {
            file.close();
        }
    };
}
