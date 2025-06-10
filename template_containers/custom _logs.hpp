#pragma once
#include "template_container.hpp"
namespace file_log
{
    class log
    {
    private:
        using log_string = template_container::string_container::string;
        static void log_info(const char* info);
        static void log_error(const char* error);
        static void log_warning(const char* warning);
        static void log_debug(const char* debug);
    public:

    };
}
