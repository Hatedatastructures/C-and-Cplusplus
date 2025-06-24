#pragma once
#include "template_container.hpp" //自定义模板容器
#include <fstream>                //文件操作
#include <chrono>                 //时间操作
#include <iomanip>                //格式化输出
#include <ctime>                  //时间戳
#include <thread>                 //多线程
#include <atomic>                 //原子操作
#include <condition_variable>     //条件变量
#define built_types con::string
#define default_document_checking_macros(macros_file_name) custom_log::file_exists(macros_file_name)
#define default_timestamp_macros std::chrono::system_clock::now()
#define default_custom_information_input_macros_t(value,type) custom_log::information::information<type>().custom_log_macro_function_input(value)
#define default_custom_information_input_macros(value) custom_log::information::information<built_types>().custom_log_macro_function_input(value)
//函数宏，行数宏，文件宏,自动捕获行号....
//中控类，控制台，等级过滤，控制台颜色标记，默认参数宏调用
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
    namespace information
    {
        template<typename custom_information_type = custom_string>
        class information
        {
            #define DECLARE_INFO_INPUT(type)template<typename macro_parameters>\
            void type##_message_input(const macro_parameters& data){type##_information = to_custom_string(data);} 
        protected:
            static custom_string to_custom_string(const std::string& string_value) 
            {   return {string_value.c_str()}; }
            static custom_string to_custom_string(const custom_string& string_value)
            {   return string_value;    }
            static custom_string to_custom_string(const char* string_value)
            {   return {string_value}; }
        public:
            custom_information_type custom_log_information;     //自定义信息
            custom_string debugging_information;                //调试信息
            custom_string general_information;                  //一般信息
            custom_string warning_information;                  //警告信息
            custom_string error_information;                    //错误信息
            custom_string serious_error_information;            //严重错误信息
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
            void custom_log_message_input(const custom_information_type& data)
            {
                custom_log_information = data;
            }
            information<custom_information_type>& custom_log_macro_function_input(const custom_information_type& data)
            {
                custom_log_information = data;
                return *this;
            }
            custom_string to_custom_string()
            {   //自定义信息类须重载c_str函数，，返回char*类型支符串
                return custom_string(custom_log_information.c_str());
            }
        };
    }
    namespace buffer_queues
    {
        class double_buffer_queue   //双队列缓冲区
        {   //只接受con::string类型
            size_t buffer_size = 0;
            std::ofstream& file;
            std::mutex switch_mutex;
            std::mutex swap_locks;
            std::thread background_threads;
            std::condition_variable conditional_control;
            con::queue<con::string> produce_queue;
            con::queue<con::string> consume_queue;
            std::atomic<con::queue<con::string>*> read_queue;
            std::atomic<con::queue<con::string>*> write_queue;
            void switch_queues() 
            {
                // 交换读写队列指针
                std::lock_guard<std::mutex> lock(swap_locks);
                con::queue<con::string>* temp_atomic_queue_data = read_queue.load();
                read_queue.store(write_queue.load());
                write_queue.store(temp_atomic_queue_data);
                // 唤醒等待的消费者
                conditional_control.notify_one();
            }
            void buffer_files(std::ofstream& file)
            {
                size_t buffer_file_size = buffer_size;
                while(buffer_file_size && !read_queue.load()->empty())
                {
                    con::string temp_string_data;
                    dequeue(temp_string_data);
                    file << temp_string_data; 
                    std::cout << temp_string_data << std::endl;
                    --buffer_file_size;
                    std::cout << "当前日志数" << buffer_file_size << std::endl;
                }
            }
        public:
            static inline size_t produce_payload_size = 10;
            double_buffer_queue(std::ofstream& external_file)
            :file(external_file)
            {
                read_queue.store(&produce_queue);
                write_queue.store(&consume_queue);

            }
            double_buffer_queue(const double_buffer_queue& rhs) = delete;
            double_buffer_queue(double_buffer_queue&& rhs) = delete;
            double_buffer_queue& operator=(const double_buffer_queue& rhs) = delete;
            double_buffer_queue& operator=(double_buffer_queue&& rhs) = delete;
            ~double_buffer_queue()
            {
                for(size_t pair = 0; pair <= 1; ++pair)
                {
                    if(!write_queue.load()->empty())
                    {
                        switch_queues();
                        buffer_files(file);
                    }
                }
            }
            void enqueue(const con::string& built_string_data)
            {
                if( buffer_size >= produce_payload_size)
                {
                    switch_queues();
                    buffer_size = 0;
                    background_threads = std::thread([&]{buffer_files(file);});
                    background_threads.detach(); //分离线程
                }
                write_queue.load()->push(built_string_data);
                ++buffer_size;
            }
            void enqueue(con::string&& built_string_data)
            {
                if( buffer_size >= produce_payload_size)
                {
                    switch_queues();
                    buffer_size = 0;
                    background_threads = std::thread([&]{buffer_files(file);});
                    background_threads.detach(); //分离线程
                }
                write_queue.load()->push(std::move(built_string_data));
                ++buffer_size;
            }
            void refresh_buffer_queue()
            {
                for(size_t pair = 0; pair <= 1; ++pair)
                {
                    if(!write_queue.load()->empty())
                    {
                        switch_queues();
                        buffer_files(file);
                    }
                }
            }
            bool dequeue(con::string& result) 
            {
                auto* atomic_queue_data = read_queue.load();
                std::lock_guard<std::mutex> lock(switch_mutex);
                
                if (atomic_queue_data->empty())
                {
                    return false; //判断队列为不为空
                }
                result = std::move(atomic_queue_data->front());
                atomic_queue_data->pop();
                return true;
            }
            [[nodiscard]] size_t write_size() const
            {
                return write_queue.load()->size();
            }
            [[nodiscard]] size_t read_size() const
            {
                return read_queue.load()->size();
            }
            static  size_t& buffer_adjustments_queue(const size_t& new_produce_payload_size)
            {
                produce_payload_size = new_produce_payload_size;
                return produce_payload_size;
            }
        };
    }
    namespace configurator
    {
        namespace placeholders
        {
            inline custom_string debugging_information_prefix     = "[DEBUG]";
            inline custom_string general_information_prefix       = "[INFO]";
            inline custom_string warning_information_prefix       = "[WARNING]";
            inline custom_string error_information_prefix         = "[ERROR]";
            inline custom_string serious_error_information_prefix = "[CRITICAL]";
            inline custom_string custom_log_information_prefix    = "[DEFAULT]";
            inline custom_string log_timestamp                    = "[TIME]";
        }
        template<typename custom_information_type = custom_string>
        class file_configurator //文件配置器
        {
            using information_type = information::information<custom_information_type>;
        protected:
            static con::string convert_to_cstr(const std::string& string_value)        {return string_value.c_str();}
            static con::string convert_to_cstr(const custom_string& string_value)      {return string_value;}
            static con::string convert_to_cstr(const char* str_value)                  {return str_value;}
            static con::string convert_to_string(const custom_string& string_value)    {return string_value; }
            static con::string convert_to_string(const std::string& string_value)      {return string_value.c_str();}
            static con::string convert_to_string(const char* str_value)                {return str_value;}
            static con::string format_time(const log_timestamp_type& time_value)
            {
                const auto time_t = std::chrono::system_clock::to_time_t(time_value);
                const std::tm* local_time = std::localtime(&time_t);
                std::ostringstream oss;
                oss << std::put_time(local_time, "%Y-%m-%d %H:%M:%S");
                return oss.str().c_str();
            }
            template<typename file_open>
            void open_file(const file_open& file_name) 
            {
                file_ofstream.open(convert_to_cstr(file_name).c_str());
            }

            static con::string format_information(const information_type& information_value)
            {
                std::ostringstream oss;
                if(information_value.custom_log_information.c_str() != " ")
                {
                    oss << placeholders::custom_log_information_prefix << information_value.custom_log_information.c_str() << "";
                }
                oss << placeholders::debugging_information_prefix     << information_value.debugging_information     << " " 
                    << placeholders::general_information_prefix       << information_value.general_information       << " " 
                    << placeholders::warning_information_prefix       << information_value.warning_information       << " "
                    << placeholders::error_information_prefix         << information_value.error_information         << " "
                    << placeholders::serious_error_information_prefix << information_value.serious_error_information << " ";
                return oss.str().c_str();
            }
        public:
            using inbuilt_documents = std::ofstream;
            inbuilt_documents file_ofstream;
            buffer_queues::double_buffer_queue write_queue;
            file_configurator() = delete;
            file_configurator(const file_configurator& rhs) = delete;
            file_configurator(file_configurator&& rhs) = delete;
            file_configurator& operator=(const file_configurator& rhs) = delete;
            file_configurator& operator=(file_configurator&& rhs) = delete;
            ~file_configurator()      {file_ofstream.close();}
            template<typename structure>
            file_configurator(const structure& file_name)
            :write_queue(file_ofstream)
            {
                open_file(file_name);
            }
            template<typename file_write>
            void ordinary_type_write(const file_write& file_value)
            {
                write_queue.enqueue(convert_to_string(file_value));
            }
            void default_type_write(const information_type& information_value) 
            {
                write_queue.enqueue(format_information(information_value));
            }
            void custom_type_write(const custom_information_type& foundation_log_value)
            {
                write_queue.enqueue(placeholders::custom_log_information_prefix + con::string(foundation_log_value.c_str()));
            }
            void time_characters(const log_timestamp_type& time) 
            {
                write_queue.enqueue(placeholders::log_timestamp + format_time(time));
            }           
            void overall_information_write(const information_type& information_value)
            {
                con::string temp_value = placeholders::custom_log_information_prefix + information_value.custom_log_information;
                write_queue.enqueue(temp_value + format_information(information_value));
            }
            void write(const information_type& information_value,const log_timestamp_type& time_value)
            {
                con::string temp_value = placeholders::custom_log_information_prefix + information_value.custom_log_information;
                con::string time_value_string  = placeholders::log_timestamp + format_time(time_value);
                write_queue.enqueue(temp_value + format_information(information_value) + time_value_string);
            }
            void write(const con::string& string_value,const log_timestamp_type& time_value)
            {
                const con::string& temp_value = string_value;
                con::string time_value_string  = placeholders::log_timestamp + format_time(time_value);
                write_queue.enqueue(temp_value + time_value_string);
            }

            static bool file_buffer_adjustments(const size_t& new_buffer_size)
            {
                return custom_log::buffer_queues::double_buffer_queue::buffer_adjustments_queue(new_buffer_size) == new_buffer_size;
            }
            void refresh_buffer()
            {
                write_queue.refresh_buffer_queue();
            }
            con::string get_string_str(const information_type& information_value)const
            {
                con::string temporary_string = format_information(information_value);
                return temporary_string;
            }
        };
        class console_configurator //控制台配置器
        {

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
            [[nodiscard]] con::string top() const {return function_log_stacks.top();}
            size_t size()           {return function_log_stacks.size();}
            [[nodiscard]] bool empty() const      {return function_log_stacks.empty();}
            void pop()              {function_log_stacks.pop();}
        };
    }
    template<typename custom_foundation_log_type = custom_string> 
    class foundation_log
    {
        using information_type = information::information<custom_foundation_log_type>; 
        using foundation_log_type = con::pair<con::string,log_timestamp_type>;
    private:
        configurator::file_configurator<custom_foundation_log_type> log_file;
        con::list<con::vector<foundation_log_type>> first_level_cache_manager; // 减少时间开销，和用数组来比空间开销差不多
        con::vector<foundation_log_type> second_level_cache_manager;
        foundation_log_type temporary_caching(const information_type& log_information,const log_timestamp_type& time = log_timestamp_class::now())
        {
            const con::string temporary_string_caching = log_file.get_string_str(log_information);
            return foundation_log_type(temporary_string_caching,time);
        }
    public:
        foundation_log(const foundation_log& rhs) = delete;
        foundation_log(foundation_log&& rhs) = delete;
        foundation_log& operator=(const foundation_log& rhs) = delete;
        foundation_log& operator=(foundation_log&& rhs) = delete;

        virtual ~foundation_log() 
        {
            push_to_file();
            refresh_buffer();
        }
        foundation_log(const custom_string& log_file_name)
        :log_file(log_file_name){}
        foundation_log(const std::string& log_file_name)
        :log_file(log_file_name.c_str()){}
        foundation_log(const char* log_file_name)
        : log_file(log_file_name){}
        virtual void write_file(const information_type& log_information,const log_timestamp_type& time = log_timestamp_class::now())
        {
            log_file.default_type_write(log_information);
            log_file.time_characters(time);
        }
        virtual void staging(const information_type& log_information,const log_timestamp_type& time = log_timestamp_class::now())
        {
            if(second_level_cache_manager.size() >= 100)
            {
                con::vector<foundation_log_type> replacement_value;
                replacement_value.swap(second_level_cache_manager);
                first_level_cache_manager.push_back(std::move(replacement_value));
            }
            second_level_cache_manager.push_back(temporary_caching(log_information,time));
        }
        bool file_buffer_adjustments(const size_t& new_file_buffer_size)
        {
            return log_file.file_buffer_adjustments(new_file_buffer_size);
        }
        virtual void push_to_file()
        {
            if(!first_level_cache_manager.empty())
            {
                for(auto& first_level_cushioningp : first_level_cache_manager)
                {
                    for(auto&  second_level_cushioningp : first_level_cushioningp)
                    {
                        log_file.write(second_level_cushioningp.first,second_level_cushioningp.second);
                    }
                }
            }
            if(!second_level_cache_manager.empty())
                {
                    for(auto& second_level_cushioningp : second_level_cache_manager)
                    {
                        log_file.write(second_level_cushioningp.first,second_level_cushioningp.second);
                    }
                }
            first_level_cache_manager.clear();
            con::vector<foundation_log_type> new_second_level_cache_manager;
            new_second_level_cache_manager.swap(second_level_cache_manager);
        }
        virtual void refresh_buffer()
        {
            log_file.refresh_buffer();
        }
    };
    template <typename custom_log_type>
    class log : public custom_log::foundation_log<custom_log_type>
    {   //改为公有继承
    private:
        configurator::function_stacks function_call_stack;
    public:
        template <typename file_name>
        log(const file_name& file): foundation_log<custom_log_type>()
        {
            log::foundation_log::foundation_log(file);
        }

        ~log() override = default;
    };
}
namespace rec
{
    using namespace custom_log;
}
