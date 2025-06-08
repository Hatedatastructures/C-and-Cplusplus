#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <mutex>
namespace custom_exception
{
    class customize_exception : public std::exception
    {
    private:
        const char* message;
        const char* function_name;
        size_t line_number;
    public:
        customize_exception(const char* message_target,const char* function_name_target,const size_t& line_number_target) noexcept 
        {
            message = new char [std::strlen(message_target) + 1];
            std::strcpy(message,message_target);
            function_name = new char [std::strlen(function_name_target) + 1];
            std::strcpy(function_name,function_name_target);
            line_number = line_number_target;
        }
        [[nodiscard]] virtual const char* what() const noexcept override
        {
            return message;
        }
        [[nodiscard]] const char* function_name_get() const noexcept
        {
            return function_name;
        }
        [[nodiscard]] size_t line_number_get() const noexcept
        {
            return line_number;
        }
        ~customize_exception() noexcept
        {
            delete [] message;
            delete [] function_name;
        }
    };
}
namespace smart_pointer
{
    template<typename smart_ptr_type>
    class smart_ptr
    {
    private:
        smart_ptr_type* _ptr;
        using Ref = smart_ptr_type&;
        using Ptr = smart_ptr_type*;
    public:
        smart_ptr(smart_ptr_type* Ptr) noexcept
        {
            _ptr = Ptr;
        }
        ~smart_ptr() noexcept
        {
            if( _ptr != nullptr)
            {
                delete _ptr;
                _ptr = nullptr;
            }
        }
        smart_ptr(const smart_ptr& _SmartPtr) noexcept
        {
            //管理权转移到另一个
            _ptr = _SmartPtr._ptr;
            _SmartPtr._ptr = nullptr;
        }
        Ref operator*() noexcept
        {
            return *(_ptr);
        }
        Ptr operator->() noexcept
        {
            return _ptr;
        }
        smart_ptr<smart_ptr_type>& operator=(const smart_ptr& _SmartPtr) noexcept
        {
            if( _ptr != nullptr)
            {
                delete _ptr;
                _ptr = nullptr;
            }
            _ptr = _SmartPtr._ptr;
            _SmartPtr._ptr = nullptr;
            return *this;
        }
    };
    template <typename unique_ptr_type>
    class unique_ptr
    {
    private:
        unique_ptr_type* _ptr;
        using Ref = unique_ptr_type&;
        using Ptr = unique_ptr_type*;
    public:
        unique_ptr(unique_ptr_type* Ptr) noexcept
        {
            _ptr = Ptr;
        }
        ~unique_ptr() noexcept
        {
            if( _ptr != nullptr)
            {
                delete _ptr;
                _ptr = nullptr;
            }
        }
        Ref operator*() noexcept
        {
            return *(_ptr);
        }
        Ptr operator->() noexcept
        {
            return _ptr;
        }
        unique_ptr(const unique_ptr& _UniquePtr) noexcept = delete;
        unique_ptr<unique_ptr_type>& operator= (const unique_ptr& _UniquePtr) noexcept = delete;
        //禁止拷贝
    };
    template <typename shared_ptr_type>
    class shared_ptr
    {
    private:
        shared_ptr_type* _ptr;
        int* _SharedPCount;
        std::mutex* _pmutex;
        using Ref = shared_ptr_type&;
        using Ptr = shared_ptr_type*;
    public:
        shared_ptr(shared_ptr_type* Ptr = nullptr)
        {
            _ptr = Ptr;
            _SharedPCount = new int(1);
            _pmutex = new std::mutex;
        }
        shared_ptr(const shared_ptr& _SharedPtr) noexcept
        {
            _ptr = _SharedPtr._ptr;
            _SharedPCount = _SharedPtr._SharedPCount;
            _pmutex = _SharedPtr._pmutex;
            //上锁
            _pmutex->lock();
            (*_SharedPCount)++;
            _pmutex->unlock();
        }
        ~shared_ptr() noexcept
        {
           release();
        }
        void release() noexcept
        {
            _pmutex->lock();
            bool flag = false;
            if(--(*_SharedPCount) == 0 && _ptr != nullptr)
            {
                delete _ptr;
                _ptr = nullptr;
                delete _SharedPCount;
                _SharedPCount = nullptr;
                flag = true;
            }
            _pmutex->unlock();
            if(flag == true)
            {
                delete _pmutex;
                _pmutex = nullptr;
            }
        }
        Ref operator*() noexcept
        {
            return *(_ptr);
        }
        Ptr operator->() noexcept
        {
            return _ptr;
        }
        Ptr get_ptr() const noexcept
        {
            return _ptr;
        }
        shared_ptr<shared_ptr_type>& operator=(const shared_ptr& _SharedPtr) noexcept
        {
            if(_ptr != _SharedPtr._ptr)
            {
                release();
                _ptr = _SharedPtr._ptr;
                _SharedPCount = _SharedPtr._SharedPCount;
                _pmutex = _SharedPtr._pmutex;
                //上锁
                _pmutex->lock();
                (*_SharedPCount)++;
                _pmutex->unlock();
            }
            return *this;
        }
        int get_sharedp_count() const noexcept
        {
            return *_SharedPCount;
        }
    };
    template <typename weak_ptr_type>
    class weak_ptr
    {
    private:
        weak_ptr_type* _ptr;
        using Ref = weak_ptr_type&;
        using Ptr = weak_ptr_type*;
    public:
        weak_ptr() = default;
        weak_ptr(smart_pointer::shared_ptr<weak_ptr_type>& Ptr) noexcept
        {
            _ptr = Ptr.get_ptr();
        }
        weak_ptr(const weak_ptr& _WeakPtr) noexcept
        {
            _ptr = _WeakPtr._ptr;
        }
        Ref operator*() noexcept
        {
            return *(_ptr);
        }
        Ptr operator->() noexcept
        {
            return _ptr;
        }
        weak_ptr<weak_ptr_type>& operator=(smart_pointer::shared_ptr<weak_ptr_type>& Ptr) noexcept
        {
            _ptr = Ptr.get_ptr();
            return *this;
        }
    };
}
namespace template_container
{
    namespace imitation_functions
    {
        //仿函数命名空间
        template<typename imitation_functions_less>
        class less
        {
        public:
            constexpr bool operator()(const imitation_functions_less& _test1 ,const imitation_functions_less& _test2) noexcept
            {
                return _test1 < _test2;
            }
        };
        template<typename imitation_functions_greater>
        class greater
        {
        public:
            constexpr bool operator()(const imitation_functions_greater& _test1 ,const imitation_functions_greater& _test2) noexcept
            {
                return _test1 > _test2;
            }
        };
        class hash_imitation_functions
        {
        public:
            size_t operator()(const int str_data) noexcept                                {       return str_data;                }
            size_t operator()(const size_t data_size_t) noexcept                          {       return data_size_t;             }
            size_t operator()(const char data_char) noexcept                              {       return data_char;               }
            size_t operator()(const double data_double) noexcept                          {       return data_double;             }
            size_t operator()(const float data_float) noexcept                            {       return data_float;              }
            size_t operator()(const long data_long) noexcept                              {       return data_long;               }
            size_t operator()(const short data_short) noexcept                            {       return data_short;              }
            size_t operator()(const long long data_long_long) noexcept                    {       return data_long_long;          }
            size_t operator()(const unsigned int data_unsigned) noexcept                  {       return data_unsigned;           }
            size_t operator()(const unsigned long data_unsigned_long) noexcept            {       return data_unsigned_long;      }
            size_t operator()(const unsigned short data_unsigned_short) noexcept          {       return data_unsigned_short;     }
            
  
            // size_t operator()(const MY_Template::string_container::string& data_string)
            // {
            //     size_t hash_value = 0;
            //     for(size_t i = 0; i < data_string._size; ++i)
            //     {
            //         hash_value = hash_value * 31 + data_string._data[i];
            //     }
            //     return hash_value;
            // }
            //有需要可以重载本文件的string容器和vector容器.list容器等计算哈希的函数,这里就不重载了
        };
    }
    namespace algorithm
    {
        template <typename source_sequence_copy,typename target_sequence_copy>
        constexpr target_sequence_copy copy(source_sequence_copy begin,source_sequence_copy end,target_sequence_copy first) noexcept
        {
            while(begin != end)
            {
                *first = *begin;
                ++begin;
                ++first;
            }
            return first;
        }
        //返回下一个位置的迭代器，是否深浅拷贝取决于自定义类型重载和拷贝构造
        template<typename source_sequence_find,typename target_sequence_find>
        constexpr source_sequence_find find(source_sequence_find begin,source_sequence_find end,const target_sequence_find& value) noexcept
        {
            while(begin!= end)
            {
                if(*begin == value)
                {
                    return begin;
                }
                ++begin;
            }
            return end;
        } 
        template<typename swap_data_type>
        constexpr void swap(swap_data_type& a,swap_data_type& b) noexcept
        {
            swap_data_type temp = a;
            a = b;
            b = temp;
        }
        namespace hash_algorithm
        {
            template <typename hash_algorithm_type ,typename hash_if = template_container::imitation_functions::hash_imitation_functions>
            class hash_function
            {
            public:
                hash_if hash_imitation_functions_object;
                [[nodiscard]] constexpr size_t hash_sdmmhash(const hash_algorithm_type& data_hash) noexcept
                {
                    size_t return_value = hash_imitation_functions_object(data_hash);
                    return_value = 65599 * return_value;
                    return return_value;
                }
                [[nodiscard]] constexpr size_t hash_bkdrhash(const hash_algorithm_type& data_hash) noexcept
                {
                    size_t return_value = hash_imitation_functions_object(data_hash);
                    return_value = 131 * return_value;
                    return return_value;
                }
                [[nodiscard]] constexpr size_t hash_djbhash(const hash_algorithm_type& data_hash) noexcept
                {
                    size_t return_value = hash_imitation_functions_object(data_hash);
                    return_value = 33 * return_value;
                    return return_value;
                }
                [[nodiscard]] constexpr size_t hash_aphash(const hash_algorithm_type& data_hash) noexcept
                {
                    size_t return_value = hash_imitation_functions_object(data_hash);
                    return_value = return_value * 1031;
                    return return_value;
                }
                [[nodiscard]] constexpr size_t hash_pjwhash(const hash_algorithm_type& data_hash) noexcept
                {
                    size_t return_value = hash_imitation_functions_object(data_hash);
                    return_value = (return_value << 2) + return_value;
                    return return_value;
                }
            };
        }
    }
    namespace practicality
    {
        template<typename pair_data_type_example_t,typename pair_data_type_example_k>
        class pair
        {
            using T = pair_data_type_example_t;
            using K = pair_data_type_example_k;
            //处理指针类型
        public:
            //链接两个相同或不同的类型为一个类型，方便使用
            T first;
            K second;
            pair() noexcept 
            {
                first  = T();
                second = K();
            } 

            pair(const T& _first,const K& _second) noexcept
            {
                first  = _first;
                second = _second;
            }
            pair(const pair& other) noexcept
            {
                first  = other.first;
                second = other.second;
            }

            pair(T&& _first,K&& _second) noexcept
            :first(std::forward<T>(_first)),second(std::forward<K>(_second))
            {
                ;
            }
            pair(pair&& other) noexcept
            :first(std::move(other.first)),second(std::move(other.second))
            {
                ;
            }
            pair& operator=(const pair& other) noexcept
            {
                if(this != &other)
                {
                    first = other.first;
                    second = other.second;
                }
                return *this;
            }
            pair& operator=(pair&& other) noexcept
            {
                if(this != &other)
                {
                    first = std::move(other.first);
                    second = std::move(other.second);
                }
                return *this;
            }
            bool operator==(const pair& other) const  noexcept  
            {       
                return (this == &other) ? true : (first == other.first && second == other.second);  
            }
            bool operator==(const pair& other) noexcept         
            {       
                return this == &other ? true : (first == other.first && second == other.second);    
            }
            bool operator!=(const pair& other) noexcept         
            {       
                return !(*this == other);   
            }
            pair* operator->() noexcept                         {       return this;        }
            const pair* operator->()const  noexcept             {       return this;        }
            template<typename pair_ostream_t,typename pair_ostream_k>
            friend std::ostream& operator<<(std::ostream& os,const pair<pair_ostream_t,pair_ostream_k>& p);
        };
        template<typename pair_ostream_t,typename pair_ostream_k>
        std::ostream& operator<<(std::ostream& os,const pair<pair_ostream_t,pair_ostream_k>& p)
        {
            os << "(" << p.first << ":" << p.second << ")";
            return os;
        }
        /*                               类分隔                                   */
        template<typename make_pair_t,typename make_pair_k>
        pair<make_pair_t,make_pair_k> make_pair (const make_pair_t& _first,const make_pair_k& _second)
        {
            return pair<make_pair_t,make_pair_k>(_first,_second);
        }
    }

    /*############################     string容器     ############################*/
    namespace string_container
    {
        class string
        {
        private:
            char*  _data;
            size_t _size;
            size_t _capacity;
        public:
            //创建迭代器
            using iterator = char*;
            using const_iterator = const char*;
    
            using reverse_iterator = iterator;
            using const_reverse_iterator = const_iterator;
            //反向迭代器
            //限定字符串最大值
            constexpr static const size_t nops = -1;
            iterator begin() noexcept                       {   return _data;   }

            iterator end() noexcept                         {   return _data + _size;   }

            const_iterator cbegin()const noexcept           {   return const_iterator(_data);   }

            const_iterator cend()const noexcept             {   return const_iterator(_data + _size);   }

            reverse_iterator rbegin() noexcept              {   return empty() ? reverse_iterator(end()) : reverse_iterator(end() - 1);  }

            reverse_iterator rend() noexcept                {   return empty() ? reverse_iterator(begin()) : reverse_iterator(begin() - 1);  }

            const_reverse_iterator crbegin()const noexcept  {   return const_reverse_iterator(cend()- 1);   }

            const_reverse_iterator crend()const noexcept    {   return const_reverse_iterator(cbegin()- 1); }

            bool empty() noexcept                           {   return _size == 0;  }

            size_t size()const noexcept                     {   return _size;       }

            size_t capacity()const noexcept                 {   return _capacity;   }

            char* c_str()const noexcept                     {   return _data;       } //返回C风格字符串

            char back() noexcept                            {   return _size > 0 ? _data[_size - 1] : '\0';    }

            char front() noexcept                           {   return _data[0];    }//返回尾字符

            string(const char* str_data = " ")
            :_size(str_data == nullptr ? 0 : strlen(str_data)),_capacity(_size)
            {
                //传进来的字符串是常量字符串，不能直接修改，需要拷贝一份，并且常量字符串在数据段(常量区)浅拷贝会导致程序崩溃
                if(str_data != nullptr) 
                {
                    _data = new char[_capacity + 1];
                    std::strncpy(_data,str_data,std::strlen(str_data));
                    // strcpy(_data,str_data);
                    _data[_size] = '\0';
                }
                else
                {
                    _data = new char[1];
                    _data[0] = '\0';
                }
            }
            string(char*&& str_data) noexcept
            :_data(nullptr),_size(str_data == nullptr ? 0 : strlen(str_data)),_capacity(_size)
            {
                //移动构造函数，拿传入对象的变量初始化本地变量，对于涉及开辟内存的都要深拷贝
                if(str_data != nullptr)
                {
                    _data = std::move(str_data);
                    str_data = nullptr;
                }
                else
                {
                    _data = new char[1];
                    _data[0] = '\0';
                }
            }
            string(const string& str_data)
            :_data(nullptr),_size(str_data._size),_capacity(str_data._capacity)
            {
                //拷贝构造函数，拿传入对象的变量初始化本地变量，对于涉及开辟内存的都要深拷贝
                size_t capacity = str_data._capacity;
                _data = new char[capacity + 1];
                // algorithm::copy(_data,_data+capacity,str_data._data); const对象出错
                std::strcpy(_data, str_data._data);
            }
            string(string&& str_data) noexcept
            :_data(nullptr),_size(str_data._size),_capacity(str_data._capacity)
            {
                //移动构造函数，拿传入对象的变量初始化本地变量，对于涉及开辟内存的都要深拷贝
                // template_container::algorithm::swap(str_data._data,_data);
                _data = std::move(str_data._data);
                _size = std::move(str_data._size);
                _capacity = std::move(str_data._capacity);
                str_data._data = nullptr;
            }
            string(std::initializer_list<char> str_data)
            {
                //初始化列表构造函数
                _size = str_data.size();
                _capacity = _size;
                _data = new char[_capacity + 1];
                template_container::algorithm::copy(str_data.begin(), str_data.end(), _data);
                _data[_size] = '\0';
            }
            ~string() noexcept
            {
                delete [] _data;
                _data = nullptr;
                _capacity = _size = 0;
            }
            string& uppercase() noexcept
            {
                //字符串转大写
                for(string::iterator start_position = _data; start_position != _data + _size; start_position++)
                {
                    if(*start_position >= 'a' && *start_position <= 'z')
                    {
                        *start_position -= 32;
                    }
                }
                return *this;
            }
            string& lowercase() noexcept
            {
                //字符串转小写
                for(string::iterator start_position = _data; start_position != _data + _size; start_position++)
                {
                    if(*start_position >= 'A' && *start_position <= 'Z')
                    {
                        *start_position += 32;
                    }
                }
                return *this;
            }
            // size_t str_substring_kmp(const char*& sub_string)
            // {
            //     //查找子串
            // }
            string& prepend(const char*& sub_string)
            {
                //前部插入子串
                size_t len = strlen(sub_string);
                size_t new_size = _size + len;
                allocate_resources(new_size);
                char* temporary_buffers = new char[_capacity + 1];
                //临时变量
                memmove(temporary_buffers , _data , _size + 1);
                memmove(_data , sub_string , len);
                memmove(_data + len , temporary_buffers , _size + 1);
                //比memcpy更安全，memcpy会覆盖原有数据，memmove会先拷贝到临时变量再拷贝到目标地址
                _size = new_size;
                _data[_size] = '\0';
                delete [] temporary_buffers;
                return *this;
            }
            string& insert_sub_string(const char*& sub_string,const size_t& start_position)
            {
                try
                {
                    //中间位置插入子串
                    if(start_position > _size)
                    {
                        throw custom_exception::customize_exception("传入参数位置越界","insert_sub_string",__LINE__);
                    }
                    size_t len = strlen(sub_string);
                    size_t new_size = _size + len;
                    allocate_resources(new_size);
                    char* temporary_buffers = new char[new_size + 1];
                    //临时变量
                    memmove(temporary_buffers, _data, _size + 1);
                    //从oid_pos开始插入
                    memmove(_data + start_position + len, temporary_buffers + start_position, _size - start_position + 1);
                    memmove(_data + start_position, sub_string, len);
                    _size = new_size;
                    _data[_size] = '\0';
                    delete [] temporary_buffers;
                    return *this;
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;
                }
            }
            string sub_string(const size_t& start_position)
            {
                //提取字串到'\0'
                try
                {
                    if(start_position > _size)
                    {
                        throw custom_exception::customize_exception("传入参数位置越界","sub_string",__LINE__);
                    }
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;                
                }
                string result;
                size_t sub_len = _size - start_position;
                result.allocate_resources(sub_len);
                std::strncpy(result._data , _data + start_position,sub_len);
                result._size = sub_len;
                result._data[result._size] = '\0';
                return result;
            }
            string sub_string_from(const size_t& start_position)
            {
                //提取字串到末尾
                try
                {
                    if(start_position > _size)
                    {
                        throw custom_exception::customize_exception("传入参数位置越界","sub_string_from",__LINE__);
                    }
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;
                }
                string result;
                size_t sub_len = _size - start_position;
                result.allocate_resources(sub_len);
                std::strncpy(result._data , _data + start_position,sub_len);
                result._size = sub_len;
                result._data[result._size] = '\0';
                return result;
            }
            string sub_string(const size_t& start_position ,const size_t& terminate_position)
            {
                //提取字串到指定位置
                try
                {
                    if(start_position > _size || terminate_position > _size || start_position > terminate_position)
                    {
                        throw custom_exception::customize_exception("传入参数位置越界","sub_string",__LINE__);
                    }
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;
                }
                string result;
                size_t sub_len = terminate_position - start_position;
                result.allocate_resources(sub_len);
                //strncpy更安全
                std::strncpy(result._data , _data + start_position,sub_len);
                result._size = sub_len;
                result._data[result._size] = '\0';
                return result;
            }
            void allocate_resources(const size_t& new_inaugurate_capacity)
            {
                //检查string空间大小，来分配内存
                if(new_inaugurate_capacity <= _capacity)
                {
                    //防止无意义频繁拷贝
                    return;
                }
                char* temporary_str_array = new char[new_inaugurate_capacity+1];
                std::memcpy(temporary_str_array,_data,_size+1);
                
                temporary_str_array[_size] = '\0';
                delete[] _data;
                _data = temporary_str_array;
                _capacity = new_inaugurate_capacity;
            }
            string& push_back(const char& temporary_str_data)
            {
                if(_size == _capacity)
                {
                    size_t newcapacity = _capacity == 0 ? 2 :_capacity*2;
                    allocate_resources(newcapacity);
                }
                _data[_size] = temporary_str_data;
                ++_size;
                _data[_size] = '\0';
                return *this;
            }
            string& push_back(const string& temporary_string_data)
            {
                size_t len = _size + temporary_string_data._size;
                if(len > _capacity)
                {
                    size_t new_container_capacity = len;
                    allocate_resources(new_container_capacity);
                }
                std::strncpy(_data+_size,temporary_string_data._data,temporary_string_data.size());
                _size =_size + temporary_string_data._size;
                _data[_size] = '\0';
                return *this;
            }
            string& push_back(const char* temporary_str_ptr_data)
            {
                if(temporary_str_ptr_data == nullptr)
                {
                    return *this;
                }
                size_t len = strlen( temporary_str_ptr_data );
                size_t new_container_capacity = len + _size ;
                if(new_container_capacity >_capacity)
                {
                   allocate_resources(new_container_capacity);
                }
                std::strncpy(_data+_size , temporary_str_ptr_data,len);
                _size = _size + len;
                _data[_size] = '\0';
                return *this;
            }
            string& resize(const size_t& inaugurate_size ,const char& default_data = '\0')
            {
                //扩展字符串长度
                if(inaugurate_size >_capacity)
                {
                    //长度大于容量，重新开辟内存
                    try
                    {
                        allocate_resources(inaugurate_size);
                    }
                    catch(const std::bad_alloc& new_charptr_abnormal)
                    {
                        std::cerr << new_charptr_abnormal.what() << std::endl;
                        throw;
                    }
                    for(string::iterator start_position = _data + _size; start_position != _data + inaugurate_size; start_position++)
                    {
                        *start_position = default_data;
                    }
                    _size = inaugurate_size;
                    _data[_size] = '\0';
                }
                else
                {
                    //如果新长度小于当前字符串长度，直接截断放'\0'
                    _size = inaugurate_size;
                    _data[_size] = '\0';
                }
                return *this;
            }
            iterator reserve(const size_t& new_container_capacity)
            {
                try
                {
                    allocate_resources(new_container_capacity);
                }
                catch(const std::bad_alloc& new_charptr_abnormal)
                {
                    std::cerr << new_charptr_abnormal.what() << std::endl;
                    throw;
                }
                return _data;
                //返回首地址迭代器
            }
            string& swap(string& str_data) noexcept
            {
                template_container::algorithm::swap(_data,str_data._data);
                template_container::algorithm::swap(_size,str_data._size);
                template_container::algorithm::swap(_capacity,str_data._capacity);
                return *this;
            }
            string reverse()
            {
                try
                {
                    if(_size == 0)
                    {
                        throw custom_exception::customize_exception("当前string为空","reserve",__LINE__);
                    }
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;
                }
                string reversed_string;
                for(string::const_reverse_iterator reverse = rbegin();reverse != rend();reverse--)
                {
                    reversed_string.push_back(*reverse);
                }
                return reversed_string;
            }
            string reverse_sub_string(const size_t& start_position , const size_t& terminate_position)
            {
                try
                {
                    if(start_position > _size || terminate_position > _size || start_position > terminate_position || _size == 0)
                    {
                        throw custom_exception::customize_exception("string回滚位置异常","reverse_sub_string",__LINE__);
                    }
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;
                } 
                string reversed_result;
                for(string::const_reverse_iterator reverse = _data + terminate_position - 1;reverse != _data + start_position - 1;reverse--)
                {
                    reversed_result.push_back(*reverse);
                }
                return reversed_result;
            }
            void string_print() const noexcept
            {
                std::cout << _data << std::endl;
            }
            void string_reverse_print() const noexcept
            {
                for(string::const_reverse_iterator start_position = crbegin();start_position != crend();start_position--)
                {
                    std::cout << *start_position;
                }
                std::cout << std::endl;
            }
            friend std::ostream& operator<<(std::ostream& string_ostream,const string &str_data);
            friend std::istream& operator>>(std::istream& string_istream,string& str_data);
            string& operator=(const string& str_data)
            {
                try
                {
                    if(this != &str_data) //防止无意义拷贝
                    {
                        delete [] _data;
                        size_t capacity = str_data._capacity;
                        _data = new char[capacity + 1];
                        std::strncpy(_data,str_data._data,str_data.size());
                        _capacity = str_data._capacity;
                        _size = str_data._size;
                        _data[_size] = '\0';
                    }
                }
                catch(const std::bad_alloc& process)
                {
                    std::cerr << process.what() << std::endl;
                    throw;
                }
                return *this;
            }
            string& operator=(const char* str_data)
            {
                try
                {
                    delete [] _data;
                    size_t capacity = strlen(str_data);
                    _data = new char[capacity + 1];
                    std::strncpy(_data,str_data,strlen(str_data));
                    _capacity = capacity;
                    _size = capacity;
                    _data[_size] = '\0';
                }
                catch(const std::bad_alloc& process)
                {
                    std::cerr << process.what() << std::endl;
                    throw;
                }
                return *this;
            } 
            string& operator=(string&& str_data) noexcept
            {
                if(this != &str_data)
                {
                    delete [] _data;
                    _size = str_data._size;
                    _capacity = str_data._capacity;
                    _data = str_data._data;
                    str_data._data = nullptr;
                }
                return *this;
            }
            string& operator+=(const string& str_data)
            {
                size_t len = _size + str_data._size;
                allocate_resources(len);
                std::strncpy(_data + _size,str_data._data,str_data.size());
                _size = _size + str_data._size;
                _data[_size] = '\0';
                return *this;
            }
            bool operator==(const string& str_data) const noexcept
            {
                if(_size != str_data._size)
                {
                    return false;
                }
                for(size_t compare_traversal = 0;compare_traversal < _size;compare_traversal++)
                {
                    if(_data[compare_traversal] != str_data._data[compare_traversal])
                    {
                        return false;
                    }
                }
                return true;
            }
            bool operator<(const string& str_data) const noexcept
            {
                size_t min_len = _size < str_data._size ? _size : str_data._size;
                for(size_t compare_traversal = 0;compare_traversal < min_len;compare_traversal++)
                {
                    if(_data[compare_traversal] != str_data._data[compare_traversal])
                    {
                        return _data[compare_traversal] < str_data._data[compare_traversal];
                    }
                }
                return _size < str_data._size;
            }
            bool operator>(const string& str_data) const noexcept
            {
                size_t min_len = _size < str_data._size? _size : str_data._size;
                for(size_t compare_traversal = 0;compare_traversal < min_len;compare_traversal++)
                {
                    if(_data[compare_traversal]!= str_data._data[compare_traversal])
                    {
                        return _data[compare_traversal] > str_data._data[compare_traversal];
                    }
                }
                return _size > str_data._size;
            }
            char& operator[](const size_t& access_location) 
            {
                try
                {
                    if(access_location <= _size)
                    {
                        return _data[access_location]; //返回第ergodic_value个元素的引用
                    }
                    else
                    {
                        throw custom_exception::customize_exception("越界访问","string::operator[]",__LINE__);
                    }
                }
                catch(const custom_exception::customize_exception& access_exception)
                {
                    std::cerr << access_exception.what() << " " << access_exception.function_name_get() << " " << access_exception.line_number_get() << std::endl;
                    throw;
                }
                //就像_data在外面就能访问它以及它的成员，所以这种就可以理解成出了函数作用域还在，进函数之前也能访问的就是引用
            }
            const char& operator[](const size_t& access_location) const
            {
                try
                {
                    if(access_location <= _size)
                    {
                        return _data[access_location]; //返回第ergodic_value个元素的引用
                    }
                    else
                    {
                        throw custom_exception::customize_exception("越界访问","string::operator[]const",__LINE__);
                    }
                }
                catch(const custom_exception::customize_exception& access_exception)
                {
                    std::cerr << access_exception.what() << " " << access_exception.function_name_get() << " " << access_exception.line_number_get() << std::endl;
                    throw;
                }
            }
            string operator+(const string& string_array)
            {
                string return_string_object;
                size_t object_len = _size + string_array._size;
                return_string_object.allocate_resources(object_len);
                std::strncpy(return_string_object._data , _data,size());
                std::strncpy(return_string_object._data + _size , string_array._data,string_array.size());
                return_string_object._size = _size + string_array._size;
                return_string_object._data[return_string_object._size] = '\0';
                return return_string_object;
            }
        };
        std::istream& operator>>(std::istream& string_istream,string& str_data)
        {
            while(true)
            {
                char single_char = string_istream.get();                    //gat函数只读取一个字符
                if(single_char == '\n' || single_char == EOF)
                {
                    break;
                }
                else
                {
                    str_data.push_back(single_char);
                }
            }
            return string_istream;
        }
        inline std::ostream& operator<<(std::ostream& string_ostream,const string &str_data)
        {
            for(template_container::string_container::string::const_iterator start_position = str_data.cbegin();start_position != str_data.cend();start_position++)
            {
                string_ostream << *start_position;
            }
            return string_ostream;
        }
    }
    /*############################     vector容器     ############################*/
    namespace vector_container
    {
        template <typename vector_type>
        class vector
        {
        public:
            using iterator = vector_type*;
            using const_iterator = const vector_type*;
            using reverse_iterator = iterator;
            using const_reverse_iterator = const_iterator;
        private:
            iterator _data_pointer;     //指向数据的头
            iterator _size_pointer;     //指向数据的尾
            iterator _capacity_pointer; //指向容量的尾
        public:
            iterator begin() noexcept        {   return _data_pointer;   }

            iterator end()  noexcept         {   return _size_pointer;   }

            size_t size() const  noexcept    {   return _data_pointer ? (_size_pointer - _data_pointer) : 0; }

            size_t capacity() const noexcept {   return _data_pointer ? (_capacity_pointer - _data_pointer) : 0; }

            vector_type& front() noexcept    {   return head();      }

            vector_type& back() noexcept     {   return tail();      }

            bool empty() noexcept            {   return size() == 0; }

            vector_type& head() noexcept     {   return *_data_pointer;  }

            vector_type& tail() noexcept     {   return *(_size_pointer-1);  }

            vector() noexcept
            {
                _data_pointer = nullptr;
                _size_pointer = nullptr;
                _capacity_pointer = nullptr;
            }
            vector(const size_t& container_capacity , const vector_type& vector_data = vector_type())
            :_data_pointer(new vector_type[container_capacity]),_size_pointer(_data_pointer + container_capacity)
            ,_capacity_pointer(_data_pointer + container_capacity)
            {
                for(size_t corresponding_location = 0;corresponding_location < container_capacity;corresponding_location++)
                {
                    _data_pointer[corresponding_location] = vector_data;
                }
            }
            vector(std::initializer_list<vector_type> lightweight_container)
            :_data_pointer(new vector_type[lightweight_container.size()]),_size_pointer(_data_pointer + lightweight_container.size())
            ,_capacity_pointer(_data_pointer + lightweight_container.size())
            {
                //链式拷贝
                size_t corresponding_location = 0;
                for(auto& chained_values:lightweight_container)
                {
                    _data_pointer[corresponding_location] = std::move(chained_values);
                    corresponding_location++;
                }
            }
            vector_type& find(const size_t& find_size)
            {
                try
                {
                    if(find_size >= size())
                    {
                        throw custom_exception::customize_exception("传入数据超出容器范围","vector::find",__LINE__);
                    }
                    else
                    {
                        return _data_pointer[find_size];
                    }
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;
                }
            }
            vector<vector_type>& size_adjust(const size_t& data_size , const vector_type& padding_temp_data = vector_type())
            {
                size_t container_size = size();
                size_t container_capacity  = capacity();
                if(data_size > container_capacity)
                {
                    resize(data_size);
                    for(size_t assignment_traversal = container_capacity; assignment_traversal < data_size ; assignment_traversal++)
                    {
                        _data_pointer[assignment_traversal] = padding_temp_data;
                    }
                }
                else
                {
                    if(data_size > container_size)
                    {
                        for(size_t assignment_traversal = container_size; assignment_traversal < data_size ; assignment_traversal++)
                        {
                            _data_pointer[assignment_traversal] = padding_temp_data;
                        }
                    }
                    else if (data_size < container_size)
                    {
                        _size_pointer = _data_pointer + data_size;
                    }
                }
                return *this;
            }
            vector(const vector<vector_type>& vector_data)
            :_data_pointer(vector_data.capacity() ? new vector_type[vector_data.capacity()] : nullptr),
            _size_pointer(_data_pointer + vector_data.size()),_capacity_pointer(_data_pointer + vector_data.capacity())
            {
                for(size_t copy_assignment_traversal = 0; copy_assignment_traversal < vector_data.size();copy_assignment_traversal++)
                {
                    _data_pointer[copy_assignment_traversal] = vector_data._data_pointer[copy_assignment_traversal];
                }
            }
            vector(vector<vector_type>&& vector_data) noexcept
            {
                _data_pointer     = std::move(vector_data._data_pointer);
                _size_pointer     = std::move(vector_data._size_pointer);
                _capacity_pointer = std::move(vector_data._capacity_pointer);
                vector_data._data_pointer = vector_data._size_pointer = vector_data._capacity_pointer = nullptr;
            }
            ~vector()
            {
                delete[] _data_pointer;
                _data_pointer = _size_pointer =_capacity_pointer = nullptr;
            }
            void swap(vector<vector_type>& vector_data) noexcept
            {
                template_container::algorithm::swap(_data_pointer    , vector_data._data_pointer);
                template_container::algorithm::swap(_size_pointer    , vector_data._size_pointer);
                template_container::algorithm::swap(_capacity_pointer, vector_data._capacity_pointer);
            }
            iterator erase(iterator delete_position) noexcept
            {
                //删除元素
                iterator next_position = delete_position + 1;
                while (next_position != _size_pointer)
                {
                    *(next_position-1) = *next_position; //(temp-1)就是pos的位置，从pos位置开始覆盖，覆盖到倒数第1个结束，最后一个会被--屏蔽掉
                    next_position++;
                }
                --_size_pointer;
                return next_position;                 //返回下一个位置地址
            }
            vector<vector_type>& resize(const size_t& new_container_capacity, const vector_type& vector_data = vector_type())
            {
                try 
                {
                    size_t original_size = size();  // 先保存原来的元素数量
                    if ((size_t)(_capacity_pointer - _data_pointer) < new_container_capacity) 
                    {
                        //涉及到迭代器失效问题，不能调用size()函数，会释放未知空间
                        iterator new_vector_type_array = new vector_type[new_container_capacity]; 
                        // 复制原先的数据
                        for (size_t original_data_traversal = 0; original_data_traversal < original_size; original_data_traversal++) 
                        {
                            new_vector_type_array[original_data_traversal] = std::move(_data_pointer[original_data_traversal]);
                        }
                        for(size_t assignment_traversal = original_size; assignment_traversal < new_container_capacity; assignment_traversal++)
                        {
                            new_vector_type_array[assignment_traversal] = vector_data;
                        }
                        delete [] _data_pointer;
                        _data_pointer = new_vector_type_array;
                        _size_pointer = _data_pointer + original_size;  // 使用 original_size 来重建 _size_pointer
                        _capacity_pointer = _data_pointer + new_container_capacity;
                    }
                }
                catch(const std::bad_alloc& process)
                {
                    delete [] _data_pointer;
                    _data_pointer = _size_pointer = _capacity_pointer = nullptr;
                    std::cerr << process.what() << std::endl;
                    throw;
                }
                return *this;
            }
            vector<vector_type>& push_back(const vector_type& vector_type_data)
            {
                if(_size_pointer == _capacity_pointer)
                {
                    size_t new_container_capacity = _data_pointer == nullptr ? 10 : (size_t)(_capacity_pointer-_data_pointer)*2;
                    resize(new_container_capacity);
                }
                //注意—_size_pointer是原生迭代器指针，需要解引用才能赋值
                *_size_pointer = vector_type_data;
                _size_pointer++;
                return *this;
            }
            vector<vector_type>& push_back(vector_type&& vector_type_data)
            {
                if(_size_pointer == _capacity_pointer)
                {
                    size_t new_container_capacity = _data_pointer == nullptr ? 10 : (size_t)(_capacity_pointer-_data_pointer)*2;
                    resize(new_container_capacity);
                }
                //注意_size_pointer是原生迭代器指针，需要解引用才能赋值
                *_size_pointer = std::move(vector_type_data);
                // new (_data_pointer) vector_type(std::forward<vector_type>(vector_type_data));
                _size_pointer++;
                return *this;
            }
            vector<vector_type>& pop_back() 
            {
                if (_size_pointer > _data_pointer) 
                {    // 至少有一个元素
                    --_size_pointer; // 尾指针前移
                }
                return *this;
            }
            vector<vector_type>& push_front(const vector_type& vector_type_data)
            {
                //头插
                if(_size_pointer == _capacity_pointer)
                {
                    size_t new_container_size = _data_pointer == nullptr ? 10 : (size_t)(_capacity_pointer-_data_pointer)*2;
                    resize(new_container_size);
                }
                for(size_t container_size = size() ; container_size > 0 ; --container_size)
                {
                    _data_pointer[container_size] = _data_pointer[container_size -1];
                }
                *_data_pointer = vector_type_data;
                ++_size_pointer;
                return *this;
            }
            vector<vector_type>& pop_front()
            {
                if( size() > 0 )
                {
                    for(size_t assignment_traversal = 1;assignment_traversal < size();assignment_traversal++)
                    {
                        _data_pointer[assignment_traversal - 1] = _data_pointer[assignment_traversal];
                    }
                    --_size_pointer;
                }
                return *this;
            }
            vector_type& operator[](const size_t& access_location)
            {
                try 
                {
                    if( access_location >= capacity())
                    {
                        throw custom_exception::customize_exception("传入参数越界","vector::operatot[]",__LINE__);
                    }
                    else
                    {
                        return _data_pointer[access_location];
                    }
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;
                }
            }
            const vector_type& operator[](const size_t& access_location) const 
            {
                // return _data_pointer[access_location];
                try 
                {
                    if( access_location >= capacity())
                    {
                        throw custom_exception::customize_exception("传入参数越界","vector::operatot[]",__LINE__);
                    }
                    else
                    {
                        return _data_pointer[access_location];
                    }
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;
                }
            }
            vector<vector_type>& operator=(const vector<vector_type>& vector_data)
            {
                if (this != &vector_data) 
                {
                    vector<vector_type> return_vector_object(vector_data); // 拷贝构造
                    swap(return_vector_object); // 交换资源，temp析构时会释放原资源
                }
                return *this;
            }
            vector<vector_type>& operator=(vector<vector_type>&& vector_mobile_data) noexcept
            {
                if( this != &vector_mobile_data)
                {
                   _data_pointer     = std::move(vector_mobile_data._data_pointer);
                   _size_pointer     = std::move(vector_mobile_data._size_pointer);
                   _capacity_pointer = std::move(vector_mobile_data._capacity_pointer);
                   vector_mobile_data._data_pointer = vector_mobile_data._size_pointer = vector_mobile_data._capacity_pointer = nullptr;
                }
                return *this;
            }
            vector<vector_type>& operator+=(const vector<vector_type>& vector_data)
            {
                if(vector_data.size() == 0|| vector_data._data_pointer == nullptr)
                {
                    return *this;
                }
                size_t vector_data_size = vector_data.size();
                size_t container_size = size();
                size_t container_capacity = capacity();
                if(vector_data_size + container_size > container_capacity)
                {
                    resize(vector_data_size + container_size);
                } 
                size_t array_counter = 0;
                for(size_t slicing_traversal = container_size ; slicing_traversal < (vector_data_size + container_size); slicing_traversal++)
                {
                    _data_pointer[slicing_traversal] = vector_data._data_pointer[array_counter++];
                }
                _size_pointer = _data_pointer + (vector_data_size + container_size);
                return *this;
            }
            template <typename const_vector_output_templates>
            friend std::ostream& operator<< (std::ostream& vector_ostream, const vector<const_vector_output_templates>& dynamic_arrays_data);
        };
        template <typename const_vector_output_templates>
        std::ostream& operator<<(std::ostream& vector_ostream, const vector<const_vector_output_templates>& dynamic_arrays_data)
        {
            for(size_t input_traversal = 0; input_traversal < dynamic_arrays_data.size(); input_traversal++)
            {
                vector_ostream << dynamic_arrays_data[input_traversal] << " ";
            }
            return vector_ostream;
        }
    }

    /*############################     list容器     ############################*/
    namespace list_container
    {
        template <typename list_type>
        class list
        {
            template<typename list_type_function_node>
            struct list_container_node
            {
                //节点类
                list_container_node<list_type_function_node>* _prev;
                list_container_node<list_type_function_node>* _next;
                list_type_function_node _data;

                list_container_node(const list_type_function_node& list_type_data = list_type_function_node()) 
                :_prev(nullptr), _next(nullptr), _data(list_type_data)
                {
                    //列表初始化
                }
                list_container_node(const list_type_function_node&& data) 
                :_prev(nullptr), _next(nullptr)
                {
                    _data = data;
                }
            };
            template <typename listNodeTypeIterator ,typename Ref ,typename Ptr >
            class list_iterator
            {
            public:
                //迭代器类
                using container_node = list_container_node<listNodeTypeIterator> ;
                using iterator  = list_iterator<listNodeTypeIterator ,listNodeTypeIterator& ,listNodeTypeIterator*>;
                using reference = Ref ;
                using pointer   = Ptr ;
                container_node* _node;
                list_iterator(container_node* node) noexcept
                :_node(node)
                {
                    ;//拿一个指针来构造迭代器
                }
                Ref operator*() noexcept
                {
                    //返回该节点的自定义类型的数据
                    return _node->_data;
                }
                list_iterator& operator++() noexcept
                {
                    //先加在用
                    _node = _node -> _next;
                    return *this;
                    //返回类型名，如果为迭代器就会因为const 报错
                }
                list_iterator operator++(int) noexcept
                {
                    //先用在加
                    list_iterator return_self(_node);
                    _node = _node->_next;
                    //把本体指向下一个位置
                    return return_self;
                }
                list_iterator& operator--() noexcept
                {
                    _node = _node->_prev;
                    return *this;
                }
                list_iterator operator--(int) noexcept
                {
                    list_iterator return_self (_node);
                    _node = _node->_prev;
                    return return_self;
                }
                bool operator!= (const list_iterator& IteratorTemp) noexcept
                {
                    //比较两个指针及其上一个和下一个指针地址
                    return _node != IteratorTemp._node;
                }
                Ptr operator->() noexcept
                {
                    return &(_node->_data);
                }
            };
            template <typename iterator>
            class reverse_list_iterator
            {
                //创建反向迭代器
                using  Ref = typename iterator::reference;
                using  Ptr = typename iterator::pointer ;
                using  const_reverse_list_iterator = reverse_list_iterator<iterator>;
            public:
                iterator _it;
                reverse_list_iterator(iterator it) noexcept
                :_it(it)
                {
                    ;
                } 
                Ref& operator*() noexcept
                {
                    //因为反向迭代器起始位置在哨兵节点所以通过指向上一个来找到准确位置
                    //正好到rend位置停下来的时候已经遍历到rend位置
                    iterator return_self(_it);
                    --(return_self);
                    return *return_self;
                }
                Ptr operator->() noexcept
                {
                    //两者函数差不多可直接调用
                    return &(operator*());
                }
                reverse_list_iterator& operator++() noexcept
                {
                    --_it;
                    return *this;
                }
                reverse_list_iterator operator++(int) noexcept
                {
                    reverse_list_iterator _temp (_it);
                    --_it;
                    return _temp;
                }
                reverse_list_iterator& operator--() noexcept
                {
                    ++_it;
                    return *this;
                }
                reverse_list_iterator operator--(int) noexcept
                {
                    reverse_list_iterator _temp (_it);
                    ++_it;
                    return _temp;
                }
                bool operator!=(const const_reverse_list_iterator& Temp) noexcept
                {
                    return _it != Temp._it;
                }
            };
            using container_node = list_container_node<list_type>;

            container_node* _head;
            //_head为哨兵位
            void create_head()
            {
                try
                {
                    _head = new container_node;
                    _head -> _prev = _head;
                    _head -> _next = _head;
                }
                catch(const std::bad_alloc& process)
                {
                    _head = nullptr;
                    std::cerr << process.what() << std::endl;
                    throw;
                }
            }
        public:
            using iterator = list_iterator<list_type,list_type& ,list_type*>;
            using const_iterator = list_iterator<list_type,const list_type&,const list_type*>;

            //拿正向迭代器构造反向迭代器，可以直接调用 iterator 已经重载的运算符和函数，相当于在封装一层类
            using reverse_iterator = reverse_list_iterator<iterator> ;
            using reverse_const_iterator = reverse_list_iterator<const_iterator>;
            list()      {       create_head();       }
            ~list()
            {
                clear();
                delete _head;
                _head = nullptr;
            }
            list(iterator first , iterator last)
            {
                try
                {
                    if(first._node == nullptr || last._node == nullptr)
                    {
                        throw custom_exception::customize_exception("传入迭代器参数为空","list::list",__LINE__);
                    }
                    if(first == last)
                    {
                        throw custom_exception::customize_exception("传入迭代器参函数相同","list::list",__LINE__);
                    }
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;
                }
                create_head();       //通过另一个list对象构建一个list
                //已经创建一个哨兵节点
                while (first != last)
                {
                    push_back(*first);
                    ++first;
                }
            }
            list(std::initializer_list<list_type> lightweight_container)
            {
                //通过初始化列表构建一个list
                create_head();
                for(auto& chained_values:lightweight_container)
                {
                    push_back(std::move(chained_values));
                }
            }
            list(const_iterator first , const_iterator last)
            {
                create_head();
                //已经创建一个哨兵节点
                while (first != last)
                {
                    push_back(*first);
                    ++first;
                }
            }
            list(const list<list_type>& list_data)
            {
                create_head();
                list<list_type> Temp (list_data.cbegin(),list_data.cend());
                swap(Temp);
            }
            list(list<list_type>&& list_data)
            {
                create_head();  //移动构造
                _head = std::move(list_data._head);
                list_data._head = nullptr;
            }
            void swap(template_container::list_container::list<list_type>& swap_target)
            {
                template_container::algorithm::swap(_head,swap_target._head);
            }
            iterator begin() noexcept                       {   return iterator(_head ->_next);  }

            iterator end() noexcept                         {   return iterator(_head);     }

            const_iterator cbegin()const noexcept           {   return const_iterator(_head ->_next);   }

            const_iterator cend()const noexcept             {   return const_iterator(_head);   }
            
            bool empty() const noexcept                     {   return _head->_next == _head;   }

            reverse_iterator rbegin() noexcept              {   return reverse_iterator(_head->_prev);  }

            reverse_iterator rend() noexcept                {   return reverse_iterator(_head); }

            reverse_const_iterator rcbegin()const noexcept  {   return reverse_const_iterator(cend());  }

            reverse_const_iterator rcend()const noexcept    {   return reverse_const_iterator(cbegin());  }

            size_t size()const noexcept
            {
                container_node* current_node = _head->_next;
                size_t count = 0;
                while (current_node != _head)
                {
                    count++;
                    current_node = current_node->_next;
                }
                return count;
            }
            /*
            元素访问操作
            */
            const list_type& front()const noexcept       {       return _head->_next->_data;         }

            const list_type& back()const noexcept        {       return _head->_prev->_data;         }
            list_type& front()noexcept
            {
                return _head->_next->_data;
            }

            list_type& back()noexcept
            {
                return _head->_prev->_data;
            }
            /*
            插入删除操作
            */
            void push_back (const list_type& PushBackData)     {       insert(end(),PushBackData);     }

            void push_front(const list_type& PushfrontData)    {       insert(begin(),PushfrontData);  }

            void push_back(list_type&& PushBackData)           {       insert(end(),std::forward<list_type>(PushBackData)); }

            void push_front(list_type&& PushfrontData)         {       insert(begin(),std::forward<list_type>(PushfrontData));  }

            void pop_back()                                    {       erase(--end());     }

            iterator pop_front()                               {       return erase(begin());  }

            iterator insert(iterator iterator_position ,const list_type& list_type_data)
            {
                try 
                {
                    if(iterator_position._node == nullptr)
                    {
                        throw custom_exception::customize_exception("传入迭代器参数为空","list::insert",__LINE__);
                    }
                    container_node* new_container_node = new container_node(list_type_data);
                    //开辟新节点
                    container_node* iterator_current_node = iterator_position._node;
                    //保存pos位置的值
                    new_container_node->_prev = iterator_current_node->_prev;
                    new_container_node->_next = iterator_current_node;
                    new_container_node->_prev->_next = new_container_node;
                    iterator_current_node->_prev = new_container_node;
                    return iterator(new_container_node);
                }
                catch(const std::bad_alloc& process)
                {
                    std::cerr << process.what() << std::endl;
                    throw;
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;
                }
            }
            iterator insert(iterator iterator_position ,list_type&& list_type_data)
            {
                try 
                {
                    if(iterator_position._node == nullptr)
                    {
                        throw custom_exception::customize_exception("传入迭代器参数为空","list::insert移动语义版本",__LINE__);
                    }
                    container_node* new_container_node = new container_node(std::forward<list_type>(list_type_data));
                    container_node* iterator_current_node = iterator_position._node;
                    new_container_node->_prev = iterator_current_node->_prev;
                    new_container_node->_next = iterator_current_node;
                    new_container_node->_prev->_next = new_container_node;
                    iterator_current_node->_prev = new_container_node;
                    return iterator(new_container_node);
                }
                catch(const std::bad_alloc& process)
                {
                    std::cerr << process.what() << "插入时内存不足" << std::endl;
                    throw;
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;
                }
            }
            iterator erase(iterator iterator_position) 
            {
                try
                {
                    if(iterator_position._node == nullptr)
                    {
                        throw custom_exception::customize_exception("传入迭代器参数为空","list::erase",__LINE__);
                    }
                    container_node* iterator_delete_node = iterator_position._node;   // 找到待删除的节点
                    container_node* next_element_node = iterator_delete_node->_next;  // 保存下一个节点的位置

                    iterator_delete_node->_prev->_next = iterator_delete_node->_next; // 将该节点从链表中拆下来并删除
                    iterator_delete_node->_next->_prev = iterator_delete_node->_prev;
                    delete iterator_delete_node;

                    return iterator(next_element_node); 
                }
                catch(const custom_exception::customize_exception& process)
                {
                    std::cerr << process.what() << " " << process.function_name_get() << " " << process.line_number_get() << std::endl;
                    throw;
                }
            }
            void resize(size_t new_container_size, const list_type& list_type_data = list_type())
            {
                size_t container_size = size();
                if (new_container_size <= container_size)
                {
                    // 有效元素个数减少到new_container_size
                    while (new_container_size < container_size)
                    {
                        pop_back();
                        container_size--;
                    }
                }
                else
                {
                    while (container_size < new_container_size)
                    {
                        push_back(list_type_data);
                        container_size++;
                    }
                }
            }
            void clear() noexcept
            {
                //循环释放资源
                container_node* current_node = _head->_next;
                // 采用头删除
                while (current_node != _head)
                {
                    _head->_next = current_node->_next;
                    delete current_node;
                    current_node = _head->_next;
                }
                _head->_next = _head->_prev = _head;
            }
            list& operator=(list<list_type> list_data) noexcept
            {
                //拷贝赋值
                if( this != &list_data)
                {
                    swap(list_data);
                }
                return *this;
            }
            list& operator=(std::initializer_list<list_type> lightweight_container)
            {
                clear();
                for(auto& chained_values:lightweight_container)
                {
                    push_back(std::move(chained_values));
                }
                return *this;
            }
            list& operator=(list<list_type>&& list_data) noexcept
            {
                if( this != &list_data)
                {
                    _head = std::move(list_data._head);
                    list_data._head = nullptr;
                }
                return *this;
            }
            list operator+(const list<list_type>& list_data)
            {
                list<list_type> return_list_object (cbegin(),cend());
                const_iterator start_position_iterator = list_data.cbegin();
                const_iterator end_position_iterator   = list_data.cend();
                while(start_position_iterator != end_position_iterator)
                {
                    return_list_object.push_back(*start_position_iterator);
                    ++start_position_iterator;
                }
                return return_list_object;
            }
            list& operator+=(const list<list_type>& list_data)
            {
                const_iterator start_position_iterator = list_data.cbegin();
                const_iterator end_position_iterator  = list_data.cend();
                while(start_position_iterator != end_position_iterator)
                {
                    push_back(*start_position_iterator);
                    ++start_position_iterator;
                }
                return *this;
            }
            template <typename const_list_output_templates>
            friend std::ostream& operator<< (std::ostream& list_ostream, const list<const_list_output_templates>& dynamic_arrays_data);
        };
        template <typename const_list_output_templates>
        std::ostream& operator<< (std::ostream& list_ostream, const list<const_list_output_templates>& dynamic_arrays_data)
        {
            typename list<const_list_output_templates>::const_iterator it = dynamic_arrays_data.cbegin();
            while (it != dynamic_arrays_data.cend()) 
            {
                list_ostream << *it << " ";
                ++it;
            }
            return list_ostream;
        }
    }
    /*############################     stack适配器     ############################*/
    namespace stack_adapter
    {
        template <typename stack_type,typename vector_based_stack = template_container::vector_container::vector<stack_type>>
        class stack
        {
        private:
            vector_based_stack vector_object;
        public:
            ~stack()                                                {       ;       }

            void push(stack_type&& stack_type_data)                 {       vector_object.push_back(std::forward<stack_type>(stack_type_data));                 }

            void push(const stack_type& stack_type_data)            {       vector_object.push_back(stack_type_data);                 }

            void pop()                                              {       vector_object.pop_back();                                 }

            size_t size() noexcept                                  {       return vector_object.size();                              }

            stack_type& top() noexcept                              {       return vector_object.back();                              }

            bool empty() noexcept                                   {       return vector_object.empty();                             }

            stack(const stack<stack_type>& stack_data)              {       vector_object = stack_data.vector_object;                 }

            stack_type& footer() noexcept                           {       return vector_object.back();                              }

            stack( stack<stack_type>&& stack_data) noexcept
            {
                vector_object = std::move(stack_data.vector_object); //std::move将对象转换为右值引用
            }
            stack(std::initializer_list<stack_type> stack_type_data)
            {
                for(auto& chained_values:stack_type_data)
                {
                    vector_object.push_back(chained_values);
                }
            }
            stack(const stack_type& stack_type_data)
            {
                vector_object.push_back(stack_type_data);
            }
            stack& operator= (const stack<stack_type>& stack_data)
            {
                if(this != &stack_data)
                {
                    vector_object = stack_data.vector_object;
                }
                return *this;
            }
            stack& operator=(stack<stack_type>&& stack_data) noexcept
            {
                if(this != &stack_data)
                {
                    vector_object = std::move(stack_data.vector_object);
                }
                return *this;
            }
            stack() = default;
        };
    }
    /*############################     queue适配器     ############################*/
    namespace queue_adapter
    {
        template <typename queue_type ,typename list_based_queue = template_container::list_container::list<queue_type> >
        class queue
        {
            //注意队列适配器不会自动检测队列有没有元素，为学异常，注意空间元素
            list_based_queue list_object;
        public:
            ~queue()                                        {    ;       }
            
            void push(queue_type&& queue_type_data)         {   list_object.push_back(std::forward<queue_type>(queue_type_data));    }

            void push(const queue_type& queue_type_data)    {   list_object.push_back(queue_type_data);    }

            void pop()                                      {   list_object.pop_front();                   }

            size_t size() noexcept                          {   return list_object.size();                 }

            bool empty() noexcept                           {   return list_object.empty();                }

            queue_type& front() noexcept                    {   return list_object.front();                }

            queue_type& back() noexcept                     {   return list_object.back();                 }

            queue(const queue<queue_type>& queue_data)      {   list_object = queue_data.list_object;      }

            queue(queue<queue_type>&& queue_type_data) noexcept
            {
                //移动构造
                list_object = std::forward<list_based_queue>(queue_type_data.list_object);
            }
            queue(std::initializer_list<queue_type> queue_type_data)
            {
                //链式构造
                for(auto& chained_values:queue_type_data)
                {
                    list_object.push_back(std::move(chained_values));
                }
            }
            queue(const queue_type& queue_type_data)
            {
                list_object.push_back(queue_type_data);
            }
            queue() = default;
            queue& operator= (const queue<queue_type>& queue_data)
            {
                if(this != &queue_data)
                {
                    list_object = queue_data.list_object;
                }
                return *this;
            }
            queue& operator=(queue<queue_type>&& queue_data) noexcept
            {
                if(this != &queue_data)
                {
                    list_object = std::forward<list_based_queue>(queue_data.list_object);
                }
                return *this;
            }
        };
        /*############################     priority_queue 适配器     ############################*/
        template <typename priority_queue_type,typename container_imitate_function = template_container::imitation_functions::less<priority_queue_type>,
        typename vector_based_priority_queue = template_container::vector_container::vector<priority_queue_type>>
        class priority_queue
        {
            //创建容器对象
            vector_based_priority_queue vector_container_object;
            container_imitate_function function_policy;
            //仿函数对象

            void priority_queue_adjust_upwards(int adjust_upwards_child) noexcept
            {
                //向上调整算法
                int adjust_upwards_parent = (adjust_upwards_child-1)/2;
                while(adjust_upwards_child > 0)
                {
                    if(function_policy(vector_container_object[adjust_upwards_parent],vector_container_object[adjust_upwards_child]))
                    {
                        template_container::algorithm::swap(vector_container_object[adjust_upwards_parent],vector_container_object[adjust_upwards_child]);
                        adjust_upwards_child = adjust_upwards_parent;
                        adjust_upwards_parent = (adjust_upwards_child-1)/2;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            void priority_queue_adjust_downwards(int adjust_downwards_parent = 0) noexcept
            {
                int adjust_downwards_child = (adjust_downwards_parent*2)+1;
                while(adjust_downwards_child < (int)vector_container_object.size())
                {
                    int adjust_downwards_left  = adjust_downwards_child;
                    int adjust_downwards_right = adjust_downwards_left + 1;
                    if( adjust_downwards_right < (int)vector_container_object.size() && 
                    function_policy(vector_container_object[adjust_downwards_left],vector_container_object[adjust_downwards_right]))
                    {
                        //大堆找出左右节点哪个孩子大
                        adjust_downwards_child = adjust_downwards_right;
                    }
                    if(function_policy(vector_container_object[adjust_downwards_parent],vector_container_object[adjust_downwards_child]))
                    {
                        //建大堆把小的换下去，建小堆把大的换下去
                        template_container::algorithm::swap(vector_container_object[adjust_downwards_parent] , vector_container_object[adjust_downwards_child]);

                        //换完之后如果是大堆，则父亲节点是较大的值，需要更新孩子节点继续向下找比孩子节点大的值，如果有继续交换
                        adjust_downwards_parent = adjust_downwards_child;
                        adjust_downwards_child = (adjust_downwards_parent*2)+1;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        public:
            ~priority_queue()  
            {
                vector_container_object.~vector();
            }
            void push(const priority_queue_type& prioity_queue_type_data)
            {
                vector_container_object.push_back(prioity_queue_type_data);
                priority_queue_adjust_upwards((int)vector_container_object.size()-1);
            }
            priority_queue_type& top() noexcept
            {
                return vector_container_object.front();
            }
            bool empty() noexcept
            {
                return vector_container_object.empty();
            }
            size_t size() noexcept
            {
                return vector_container_object.size();
            }
            void pop()
            {
                template_container::algorithm::swap(vector_container_object[0],vector_container_object[vector_container_object.size()-(size_t)1]);
                vector_container_object.pop_back();
                priority_queue_adjust_downwards();
            }
            priority_queue() 
            {
                ;
            }
            priority_queue(std::initializer_list<priority_queue_type> lightweight_container)
            {
                //通过初始化列表构建一个list
                for(auto& chained_values:lightweight_container)
                {
                    push(std::move(chained_values));
                }
            }
            priority_queue(const priority_queue& priority_queue_data)
            {
                //拷贝构造
                vector_container_object = priority_queue_data.vector_container_object;
            }
            priority_queue(priority_queue&& priority_queue_data) noexcept
            :function_policy(priority_queue_data.function_policy)
            {
                //移动构造
                vector_container_object = std::move(priority_queue_data.vector_container_object);
            }
            priority_queue(const priority_queue_type& priority_queue_type_data)
            {
                vector_container_object.push_back(priority_queue_type_data);
                priority_queue_adjust_upwards((int)vector_container_object.size()-1);
            }
            priority_queue& operator=(priority_queue&& priority_queue_data) noexcept
            {
                //移动赋值
                if(this != &priority_queue_data)
                {
                    vector_container_object = std::move(priority_queue_data.vector_container_object);
                    function_policy = priority_queue_data.function_policy;
                }
                return *this;
            }
            priority_queue& operator=(const priority_queue& priority_queue_data)
            {
                //拷贝赋值
                if(this != &priority_queue_data)
                {
                    vector_container_object = priority_queue_data.vector_container_object;
                    function_policy = priority_queue_data.function_policy;
                }
                return *this;
            }
        };
    }
    namespace tree_container
    {
        /*############################     binary_search_tree 容器     ############################*/
        template <typename binary_search_tree_type,typename container_imitate_function = template_container::imitation_functions::less<binary_search_tree_type>>
        class binary_search_tree
        {
        private:
            class binary_search_tree_type_node
            {
            public:
                //节点类
                binary_search_tree_type_node* _left;
                binary_search_tree_type_node* _right;
                binary_search_tree_type _data;
                binary_search_tree_type_node(const binary_search_tree_type& binary_search_tree_type_data = binary_search_tree_type())
                :_left(nullptr),_right(nullptr),_data(binary_search_tree_type_data)
                {
                    ;
                }
                ~binary_search_tree_type_node()
                {
                    _left  = nullptr;
                    _right = nullptr;
                }
            };
            using container_node = binary_search_tree_type_node;
            container_node* _root;                       //根节点
            container_imitate_function function_policy;  //仿函数对象
            void interior_middle_order_traversal(container_node* root_subtree_node)
            {
                //内调中序遍历函数
                template_container::stack_adapter::stack<container_node*> interior_stack;
                while(root_subtree_node != nullptr || !interior_stack.empty())
                {
                    while(root_subtree_node!= nullptr)
                    {
                        interior_stack.push(root_subtree_node);
                        //压栈
                        root_subtree_node = root_subtree_node->_left;
                    }
                    // 访问栈顶节点
                    root_subtree_node = interior_stack.top();
                    //弹出栈顶元素，刷新栈顶元素，栈顶元素会变成之前压入栈的节点的父节点
                    
                    interior_stack.pop();
                    std::cout <<  root_subtree_node->_data << " ";
                    // std::cout << &root_subtree_node->_data << " ";
                    //检查地址是不是值拷贝
                    // 转向右子树
                    root_subtree_node = root_subtree_node->_right;
                }
            }
            size_t interior_middle_order_traversal(container_node* root_subtree_node,size_t& node_counter)
            {
                template_container::stack_adapter::stack<container_node*> interior_stack;
                while(root_subtree_node != nullptr || !interior_stack.empty())
                {
                    while(root_subtree_node!= nullptr)
                    {
                        interior_stack.push(root_subtree_node);
                        root_subtree_node = root_subtree_node->_left;
                    }
                    root_subtree_node = interior_stack.top();
                    interior_stack.pop();
                    node_counter++;
                    root_subtree_node = root_subtree_node->_right;
                }
                return node_counter;
            }
            void interior_pre_order_traversal(container_node* root_subtree_node )
            {
                //前序遍历，最外左子树全部压栈
                if(root_subtree_node == nullptr)
                {
                    return;
                }
                container_node* reference_node = root_subtree_node;
                template_container::stack_adapter::stack<container_node*> interior_stack;
                interior_stack.push(reference_node);
                //不能添加|| reference_node != nullptr ，因为最后一层循环后reference_node指针还是为真后面循环无意义，反之还会破环性质
                while( !interior_stack.empty() )
                {
                    reference_node = interior_stack.top();
                    interior_stack.pop();

                    std::cout << reference_node->_data << " ";
                    if(reference_node->_right != nullptr)
                    {
                        interior_stack.push(reference_node->_right);
                    }
                    if(reference_node->_left != nullptr)
                    {
                        interior_stack.push(reference_node->_left);
                    }    //修改逻辑错误，先压右子树再压左子树，因为这是栈
                }
            }
            void clear()
            {
                if(_root == nullptr)
                {
                    return;
                }
                template_container::stack_adapter::stack<container_node*> resource_release_stack;
                resource_release_stack.push(_root);
                while(resource_release_stack.empty() == false)
                {
                    container_node* pending_deletion_node = resource_release_stack.top();
                    //取出元素，把左右节点入进去
                    resource_release_stack.pop();
                    if(pending_deletion_node->_left!= nullptr)
                    {
                        resource_release_stack.push(pending_deletion_node->_left);
                    }
                    if(pending_deletion_node->_right!= nullptr)
                    {
                        resource_release_stack.push(pending_deletion_node->_right);
                    }
                    delete pending_deletion_node;
                }
                _root = nullptr;
            }
        public:
            ~binary_search_tree()                       {           clear();                }
            // 构造函数，使用初始化列表来初始化二叉搜索树
            binary_search_tree(std::initializer_list<binary_search_tree_type> lightweight_container)
            {
                for(auto& chained_values:lightweight_container)
                {
                    push(chained_values);
                }
            }
            binary_search_tree(const binary_search_tree_type& bstt_node = binary_search_tree_type())
            :_root(nullptr)
            {   
                _root = new container_node(bstt_node);
            }
            binary_search_tree(binary_search_tree&& binary_search_tree_object) noexcept
            :function_policy(binary_search_tree_object.function_policy),_root(nullptr)
            {
                _root = std::move(binary_search_tree_object._root);
                binary_search_tree_object._root = nullptr;
            }
            binary_search_tree(const binary_search_tree& binary_search_tree_object)
            :_root(nullptr),function_policy(binary_search_tree_object.function_policy)
            //这个拷贝构造不需要传模板参数，因为模板参数是在编译时确定的，而不是在运行时确定的，对于仿函数，直接拿传进来的引用初始化就可以了
            {
                //拷贝构造，时间复杂度为O(n)
                container_node* reference_node = binary_search_tree_object._root;
                if(reference_node == nullptr)
                {
                    throw custom_exception::customize_exception("拷贝构造失败二叉搜索树为空","binary_search_tree",__LINE__);
                }
                template_container::stack_adapter::stack<template_container::practicality::pair<container_node*,container_node**> > interior_stack;
                //注意这里把本地_root类型传过去，是因为要对本地的_root进行操作，所以要传二级指针
                //这里传引用也不行，这里的对象是动态变化的，所以传引用也不行
                //如果是对全局的_ROOT进行操作，就传一级指针
                interior_stack.push(template_container::practicality::pair<container_node*,container_node**>(reference_node,&_root));
                while( !interior_stack.empty() )
                {
                    auto pair_node = interior_stack.top();
                    interior_stack.pop();
                    *(pair_node.second) = new container_node(pair_node.first->_data);
                    // container_node* _staic_temp_pair_second = *(pair_node.second);
                    // if(pair_node.first->_left!= nullptr)
                    // {   //远古版本
                    //     interior_stack.push(MY_Template::practicality::pair<container_node*,container_node**>(pair_node.first->_left,&_staic_temp_pair_second->_left));
                    // }
                    // if(pair_node.first->_right!= nullptr)
                    // {
                    //     interior_stack.push(MY_Template::practicality::pair<container_node*,container_node**>(pair_node.first->_right,&_staic_temp_pair_second->_right));
                    // }
                    //移除临时变量，直接使用指针解引用
                    if(pair_node.first->_right!= nullptr)
                    {
                        interior_stack.push(template_container::practicality::pair<container_node*,container_node**>(pair_node.first->_right,&((*pair_node.second)->_right)));
                    }
                    if(pair_node.first->_left!= nullptr)
                    {
                        interior_stack.push(template_container::practicality::pair<container_node*,container_node**>(pair_node.first->_left,&((*pair_node.second)->_left)));
                    }
                }
            }
            void middle_order_traversal()
            {
                interior_middle_order_traversal(_root);
            }
            void pre_order_traversal()
            {
                interior_pre_order_traversal(_root);
            }
            bool push(const binary_search_tree_type& binary_search_tree_type_data)
            {
                if(_root == nullptr)
                {
                    _root = new container_node(binary_search_tree_type_data);
                    return true;
                }
                else
                {
                    container_node* reference_node = _root;
                    container_node* subtree_node = nullptr;
                    while(reference_node!= nullptr)
                    {
                        subtree_node = reference_node;
                        if(!function_policy(binary_search_tree_type_data, reference_node->_data) && !function_policy(reference_node->_data, binary_search_tree_type_data))
                        {
                            //改用仿函数特性，判断是否有重复元素,防止自定义类型没有重载==运算符
                            return false;
                        }
                        else if(function_policy(binary_search_tree_type_data , reference_node->_data))
                        {
                            reference_node = reference_node->_left;
                        }
                        else
                        {
                            reference_node = reference_node->_right;
                        }
                    }
                    //新开节点链接
                    container_node* new_element_node = new container_node(binary_search_tree_type_data);
                    //链接节点
                    if(function_policy(binary_search_tree_type_data , subtree_node->_data))
                    {
                        subtree_node->_left = new_element_node;
                    }
                    else
                    {
                        subtree_node->_right = new_element_node;
                    }
                    return true;
                }
            }
            binary_search_tree& pop(const binary_search_tree_type& binary_search_tree_type_data)
            {
                //删除节点
                container_node* reference_node = _root;
                container_node* subtree_node = nullptr;
                while( reference_node != nullptr )
                {
                    if(binary_search_tree_type_data == reference_node->_data)
                    {
                        //找到节点
                        if(reference_node->_left == nullptr)
                        {
                            //左子树为空,下面判断要删除的节点是父节点的左子树还是右子树，防止多删和误删
                            if (subtree_node == nullptr)
                            {
                                // 当前节点是根节点，直接更新 _root
                                _root = reference_node->_right;
                            }
                            else
                            {
                                if(subtree_node->_left == reference_node)
                                {
                                    //根节点
                                    subtree_node->_left = reference_node->_right;
                                }   
                                else
                                {
                                    //非根节点
                                    subtree_node->_right = reference_node->_right;
                                }
                            }
                            delete reference_node;
                            reference_node = nullptr;
                            return *this;
                        }
                        else if(reference_node->_right == nullptr)
                        {
                            if (subtree_node == nullptr)
                            {
                                // 防止当前节点是根节点，无法解引用，直接更新 _root
                                _root = reference_node->_left;
                            }
                            else
                            {
                                if(subtree_node->_left == reference_node)
                                {
                                    subtree_node->_left = reference_node->_left;
                                }
                                else
                                {
                                    subtree_node->_right = reference_node->_left;
                                }
                            }
                            delete reference_node;
                            reference_node = nullptr;
                            return *this;	
                        }
                        else
                        {
                            //左右子树都不为空，找右子树的最左节点
                            container_node* right_subtree_least_node = reference_node->_right;
                            container_node* subtree_parent_node = reference_node;
                            while(right_subtree_least_node->_left != nullptr)
                            {
                                subtree_parent_node = right_subtree_least_node;
                                right_subtree_least_node = right_subtree_least_node->_left;
                            }
                            //找到最左节点	
                            template_container::algorithm::swap(reference_node->_data,right_subtree_least_node->_data);
                            //因为右树最左节点已经被删，但是还需要把被删的上一节点的左子树指向被删节点的右子树，不管右子树有没有节点都要连接上
                            if(subtree_parent_node == reference_node)
                            {
                                //说明右子树没有左子树最小节点就是右子树的第一个根，如同上面判断条件：要删除的根节点等于右子树最小节点的父亲节点
                                subtree_parent_node->_right = right_subtree_least_node->_right;
                                //这俩交换指针指向位置就行，上面已经完成值的替换
                            }
                            else
                            {
                                //情况2：说明要删除的数据的右子树的最左节点如果有数据，就把数据连接到右子树的最左节点的父亲节点的左子树指向最左子树的右子树
                                subtree_parent_node->_left = right_subtree_least_node->_right;
                            }
                            delete right_subtree_least_node;
                            right_subtree_least_node = nullptr;
                            return *this;
                        }
                    }
                    else if(function_policy(binary_search_tree_type_data, reference_node->_data))
                    {
                        subtree_node = reference_node;
                        reference_node = reference_node->_left;
                    }
                    else
                    {
                        subtree_node = reference_node;
                        reference_node = reference_node->_right;
                    }
                }
                return *this;
            }
            size_t size()
            {
                size_t _size = 0;
                return interior_middle_order_traversal(_root,_size);
            }
            size_t size()const
            {
                size_t node_number_counter = 0;
                return interior_middle_order_traversal(_root,node_number_counter);
            }
            container_node* find(const binary_search_tree_type& find_node)
            {
                //查找函数
                container_node* reference_node = _root;
                while(reference_node != nullptr)
                {
                    if(find_node == reference_node->_data)
                    {
                        return reference_node;
                    }
                    else if(function_policy(find_node, reference_node->_data))
                    {
                        reference_node = reference_node->_left;
                    }
                    else
                    {
                        reference_node = reference_node->_right;
                    }
                }
                return nullptr;
            }
            void insert(const binary_search_tree_type& existing_value,const binary_search_tree_type& new_value)
            {
                //在existing_value后面插入new_value
                container_node* existing_value_node = find(existing_value);
                //插入节点
                if(existing_value_node == nullptr)
                {
                    throw custom_exception::customize_exception("传入值未找到！","insert::find",__LINE__);
                }
                else
                {
                    container_node* new_value_node = new container_node(new_value);
                    new_value_node->_left = existing_value_node->_right;
                    existing_value_node->_right = new_value_node;
                }
            }
            binary_search_tree& operator=(const binary_search_tree& binary_search_tree_object)
            {
                //赋值运算符重载
                if(this != &binary_search_tree_object)
                {
                    clear();
                    function_policy = binary_search_tree_object.function_policy;
                    binary_search_tree reference_node = binary_search_tree_object;
                    template_container::algorithm::swap(reference_node._root,_root);
                }
                return *this;
            }
            binary_search_tree& operator=(binary_search_tree && binary_search_tree_object) noexcept
            {
                //移动赋值运算符重载
                if(this != &binary_search_tree_object)
                {
                    clear();
                    function_policy = binary_search_tree_object.function_policy;
                    _root = std::move(binary_search_tree_object._root);
                    binary_search_tree_object._root = nullptr;
                }
                return *this;
            }

        };
        /*############################     avl_tree 容器     ############################*/
        template <typename avl_tree_type_k,typename avl_tree_type_v,typename container_imitate_function = template_container::imitation_functions::less<avl_tree_type_k>,
        typename avl_tree_node_pair = template_container::practicality::pair<avl_tree_type_k,avl_tree_type_v>>
        class avl_tree
        {
        private:
            class avl_tree_type_node
            {
            public:
                avl_tree_node_pair _data;

                avl_tree_type_node* _left;
                avl_tree_type_node* _right;
                avl_tree_type_node* _parent;
                //平衡因子
                int _balance_factor;
                avl_tree_type_node(const avl_tree_type_k& avl_tt_k_data = avl_tree_type_k(),const avl_tree_type_v& avl_tt_v_data = avl_tree_type_v())
                :_data(avl_tt_k_data,avl_tt_v_data),_left(nullptr),_right(nullptr),_parent(nullptr),_balance_factor(0)
                {
                    ;
                }
                avl_tree_type_node(const avl_tree_node_pair& pair_type_data)
                :_data(pair_type_data),_left(nullptr),_right(nullptr),_parent(nullptr),_balance_factor(0)
                {
                    ;
                }
            };
            template<typename T, typename Ref ,typename Ptr>
            class avl_tree_iterator
            {
            public:
                using iterator_node = avl_tree_type_node;
                using self = avl_tree_iterator<T,Ref,Ptr>;
                using pointer = Ptr;
                using reference = Ref;
                iterator_node* _node_iterator_ptr;
                avl_tree_iterator(iterator_node* iterator_ptr_data)
                :_node_iterator_ptr(iterator_ptr_data)                  {               ;               }

                Ptr operator->()                                        {       return &(_node_iterator_ptr->_data);        }

                Ref& operator*()                                        {       return _node_iterator_ptr->_data;           }
                 
                bool operator!=(const self& another_iterator)           {       return _node_iterator_ptr != another_iterator._node_iterator_ptr;       }

                bool operator==(const self& another_iterator)           {       return _node_iterator_ptr == another_iterator._node_iterator_ptr;       }
                self& operator++()
                {
                    if(_node_iterator_ptr->_right != nullptr)
                    {
                        _node_iterator_ptr = _node_iterator_ptr->_right;
                        while(_node_iterator_ptr->_left != nullptr)
                        {
                            _node_iterator_ptr = _node_iterator_ptr->_left;
                        }
                    }
                    else
                    {
                        container_node* _iterator_self_node = _node_iterator_ptr;
                        while(_iterator_self_node->_parent != nullptr && _iterator_self_node == _iterator_self_node->_parent->_right)
                        {
                            _iterator_self_node = _iterator_self_node->_parent;
                        }
                        _node_iterator_ptr = _iterator_self_node->_parent;
                    }
                    return *this;
                }
                self operator++(int)
                {
                    self return_self = *this;
                    ++(*this);
                    return return_self;
                }
                self& operator--()
                {
                    if(_node_iterator_ptr->_left != nullptr)
                    {
                        _node_iterator_ptr = _node_iterator_ptr->_left;
                        while(_node_iterator_ptr->_right != nullptr)
                        {
                            _node_iterator_ptr = _node_iterator_ptr->_right;
                        }
                    }
                    else
                    {
                        container_node* _iterator_self_node = _node_iterator_ptr;
                        while(_iterator_self_node->_parent != nullptr && _iterator_self_node == _iterator_self_node->_parent->_left)
                        {
                            _iterator_self_node = _iterator_self_node->_parent;
                        }
                        _node_iterator_ptr = _iterator_self_node->_parent;
                    }
                    return *this;
                }
                self operator--(int)
                {
                    self return_self = *this;
                    --(*this);
                    return return_self;
                }
            };
            template<typename iterator>
            class avl_tree_reverse_iterator
            {
            public:
                using self = avl_tree_reverse_iterator<iterator>;
                iterator _it;
                using Ptr = typename iterator::pointer;
                using Ref = typename iterator::reference;
                avl_tree_reverse_iterator(iterator iterator_data)
                :_it(iterator_data)                                 {       ;           }

                Ptr operator->()                                    {   return &(*this);    }

                Ref& operator*()                                    {   return *_it;         }

                bool operator!=(const self& another_iterator)       {   return _it != another_iterator._it;     }

                bool operator==(const self& another_iterator)       {   return _it == another_iterator._it;     }
                self& operator++()
                {
                    --_it;
                    return *this;
                }
                self operator++(int)
                {
                    self return_self = *this;
                    --(*this);
                    return return_self;
                }
                self& operator--()
                {
                    ++_it;
                    return *this;
                }
                self operator--(int)
                {
                    self return_self = *this;
                    ++(*this);
                    return return_self;
                }
                
            };
            using container_node = avl_tree_type_node;
            container_node* _root;

            container_imitate_function function_policy;
            void left_revolve(container_node*& subtree_node)
            {
                /*                                                                                                              左单旋情况：简化图
                    传进来的值是发现该树平衡性被破坏的节点地址                                                                     subtree_node(10)(当前平衡因子为-2，触发调整)
                    大致思想：因为这是左单旋，所以找传进来的父亲节点的右根节点来当调整节点                                                         \
                    然后把调整节点的左根节点赋值给传进来的父亲节点的右根节点 (刚才已经用节点保存过调整节点，所以这里直接赋值)，                   sub_tree_right_node(20)(当前平衡因子为-1，不触发调整)
                    再把父亲节点赋值给调整节点的左根节点，！！注意：在旋转的过程中还要处理每个调整节点的父亲节点的指向和平衡因子                      /         \
                    {                                                                                            sub_right_left_node(nullptr)  sub_tree_right_right_node(30)
                        container_node* sub_tree_right_node = subtree_node->_right;                                  /############             分割线             ############/
                        subtree_node->_right = sub_tree_right_node->_left;                                                          sub_tree_right_node(20)(当前平衡因子为0)  
                        sub_tree_right_node->_left = subtree_node;                                                                        /       \
                        //错误写法：未同步调整父亲节点和判断调整节点的左根节点是否为空，以及全部需要调整节点的父亲指针的指针的指向        subtree_node(10)    sub_tree_right_right_node(30)
                    }                                                                                                                 \
                    if(subtree_node == nullptr || subtree_node->_right == nullptr)                                 sub_right_left_node(nullptr)
                    {
                        std::cout <<"left "<< "空指针"  <<std::endl;
                        return ;                                                                                                        
                    }
                */ 
                try 
                {
                    if(subtree_node == nullptr)
                    {
                        throw custom_exception::customize_exception("左单旋传进来的节点为空！","left_revolve",__LINE__);
                    }
                } 
                catch(const custom_exception::customize_exception& exception)
                {
                    std::cerr << exception.what() << exception.function_name_get() << exception.line_number_get() << std::endl;
                    throw;
                }    
                container_node* sub_tree_right_node = subtree_node->_right;
                // container_node* sub_right_left_node = sub_tree_right_node->_left;
                container_node* sub_right_left_node = (sub_tree_right_node->_left) ? sub_tree_right_node->_left : nullptr;
                //防止空指针解引用
                subtree_node->_right = sub_right_left_node;                      //因为调整后parent_node的位置是sub_right_left_node的位置
                if(sub_right_left_node)                                         //把parent_node的右根节点赋值给sub_right_left_node
                {
                    sub_right_left_node->_parent = subtree_node;
                    //如果sub_right_left_node(调整节点的左根节点)不等于空，还需要调整sub_right_left_node它的父亲节点
                }
                sub_tree_right_node->_left = subtree_node;
                //这里先保存一下parent_node的父亲地址，防止到下面else比较的时候丢失
                container_node* parent_node = subtree_node->_parent;
                subtree_node->_parent = sub_tree_right_node;
                //更新parent_node节点指向正确的地址

                if(_root == subtree_node)
                {
                    //如果要调整的节点是根节点，直接把调整节点赋值给根节点，然后把调整节点的父亲节点置空
                    _root = sub_tree_right_node;
                    sub_tree_right_node->_parent = nullptr;
                }
                else
                {
                    //调整前parent_node是这个树的根现在是sub_tree_right_node是这个树的根
                    if(parent_node->_left == subtree_node)
                    {
                        parent_node->_left = sub_tree_right_node;
                    }
                    else
                    {
                        parent_node->_right = sub_tree_right_node;
                    }
                    sub_tree_right_node->_parent = parent_node;
                }
                subtree_node->_balance_factor = sub_tree_right_node->_balance_factor = 0;
            }

            void right_revolve(container_node*& subtree_node)
            {
                //思路同左单旋思路差不多,实现相反，图略
                try 
                {
                    if(subtree_node == nullptr)
                    {
                        throw custom_exception::customize_exception("右单旋传进来的节点为空！","right_revolve",__LINE__);
                    }
                } 
                catch(const custom_exception::customize_exception& exception)
                {
                    std::cerr << exception.what() << exception.function_name_get() << exception.line_number_get() << std::endl;
                    throw;
                }    
                container_node* sub_tree_left_node = subtree_node->_left;
                container_node* sub_left_right_node = (sub_tree_left_node->_right) ? sub_tree_left_node->_right : nullptr;
                //防止空指针解引用
                subtree_node->_left = sub_left_right_node;
                if(sub_left_right_node)
                {
                    sub_left_right_node->_parent = subtree_node;
                }
                sub_tree_left_node->_right = subtree_node;
                //保存parent_temp_Node的父亲节点
                container_node* parent_node = subtree_node->_parent;
                subtree_node->_parent = sub_tree_left_node;

                if(_root == subtree_node)
                {
                    _root = sub_tree_left_node;
                    sub_tree_left_node->_parent = nullptr;
                }
                else
                {
                    if(parent_node->_left == subtree_node)
                    {
                        parent_node->_left = sub_tree_left_node;
                    }
                    else
                    {
                        parent_node->_right = sub_tree_left_node;
                    }
                    sub_tree_left_node->_parent = parent_node;
                }
                subtree_node->_balance_factor = sub_tree_left_node->_balance_factor = 0;
            }
            void right_left_revolve(container_node*& subtree_node)
            {
                try 
                {
                    if(subtree_node == nullptr)
                    {
                        throw custom_exception::customize_exception("右左双旋传进来的节点为空！","right_left_revolve",__LINE__);
                    }
                }
                catch(const custom_exception::customize_exception& exception)
                {
                    std::cerr << exception.what() << exception.function_name_get() << exception.line_number_get() << std::endl;
                    throw;
                }
                container_node* sub_tree_right_node = subtree_node->_right;
                container_node* sub_right_left_node = sub_tree_right_node->_left;
                int separate_balance_factor = sub_right_left_node->_balance_factor;

                right_revolve(subtree_node->_right);
                //右旋
                left_revolve(subtree_node);
                //左旋
                if(separate_balance_factor == -1)
                {
                    subtree_node->_balance_factor = 0;
                    sub_tree_right_node->_balance_factor = 1;
                    sub_right_left_node->_balance_factor = 0;
                }
                else if(separate_balance_factor == 1)
                {
                    subtree_node->_balance_factor = -1;
                    sub_tree_right_node->_balance_factor = 0;
                    sub_right_left_node->_balance_factor = 0;
                }
                else
                {
                    subtree_node->_balance_factor = 0;
                    sub_tree_right_node->_balance_factor = 0;
                    sub_right_left_node->_balance_factor = 0;
                }
            }
            void left_right_revolve(container_node*& subtree_node)
            {   
                try 
                {
                    if(subtree_node == nullptr)
                    {
                        throw custom_exception::customize_exception("左右单旋传进来的节点为空！","left_right_revolve",__LINE__);
                    }
                } 
                catch(const custom_exception::customize_exception& exception)
                {
                    std::cerr << exception.what() << exception.function_name_get() << exception.line_number_get() << std::endl;
                    throw;
                }    
                container_node* sub_tree_left_node = subtree_node->_left;
                container_node* sub_left_right_node = sub_tree_left_node->_right;
                int separate_balance_factor = sub_left_right_node->_balance_factor;

                left_revolve(subtree_node->_left);
                //左旋
                right_revolve(subtree_node);
                //右旋
                if(separate_balance_factor == -1)
                {
                    subtree_node->_balance_factor = 0;
                    sub_tree_left_node->_balance_factor = 1;
                    sub_left_right_node->_balance_factor = 0;
                }
                else if(separate_balance_factor == 1)
                {
                    subtree_node->_balance_factor = -1;
                    sub_tree_left_node->_balance_factor = 0;
                    sub_left_right_node->_balance_factor = 0;
                }
                else
                {
                    subtree_node->_balance_factor = 0;
                    sub_tree_left_node->_balance_factor = 0;
                    sub_left_right_node->_balance_factor = 0;
                }
            }
            void clear()
            {
                //清空所有资源
                if(_root == nullptr)
                {
                    return;
                }
                else
                {
                    template_container::stack_adapter::stack<container_node*> interior_stack;
                    //前序释放
                    interior_stack.push(_root);
                    while(!interior_stack.empty())
                    {
                        container_node* delete_data_node = interior_stack.top();
                        interior_stack.pop();
                        if(delete_data_node->_left != nullptr)
                        {
                            interior_stack.push(delete_data_node->_left);
                        }
                        if(delete_data_node->_right != nullptr)
                        {
                            interior_stack.push(delete_data_node->_right);
                        }
                        delete delete_data_node;
                        delete_data_node = nullptr;
                    }
                    _root = nullptr;
                }
            }
            //测试函数
            void interior_pre_order_traversal(container_node* root_subtree_node )
            {
                //前序遍历，最外左子树全部压栈
                if(root_subtree_node == nullptr)
                {
                    return;
                }
                container_node* reference_node = root_subtree_node;
                template_container::stack_adapter::stack<container_node*> interior_stack;
                interior_stack.push(reference_node);
                //不能添加|| reference_node != nullptr ，因为最后一层循环后_Pre_order_traversal_test还是为真后面循环无意义，反之还会破环性质
                while( !interior_stack.empty() )
                {
                    reference_node = interior_stack.top();
                    interior_stack.pop();

                    std::cout << reference_node->_data << " ";
                    //修改逻辑错误，先压右子树再压左子树，因为这是栈
                    if(reference_node->_right != nullptr)
                    {
                        interior_stack.push(reference_node->_right);
                    }
                    if(reference_node->_left != nullptr)
                    {
                        interior_stack.push(reference_node->_left);
                    }
                }
            }
            void interior_middle_order_traversal(container_node* root_subtree_node)
            {
                //中序遍历函数
                template_container::stack_adapter::stack<container_node*> interior_stack;
                while(root_subtree_node != nullptr || !interior_stack.empty())
                {
                    while(root_subtree_node!= nullptr)
                    {
                        interior_stack.push(root_subtree_node);
                        //压栈
                        root_subtree_node = root_subtree_node->_left;
                    }
                    // 访问栈顶节点
                    root_subtree_node = interior_stack.top();
                    //弹出栈顶元素，刷新栈顶元素，栈顶元素会变成之前压入栈的节点的父节点
                    
                    interior_stack.pop();
                    std::cout <<  root_subtree_node->_data << " ";
                    // std::cout << &root_subtree_node->_data << " ";
                    //检查地址是不是值拷贝
                    // 转向右子树
                    root_subtree_node = root_subtree_node->_right;
                }
            }
            size_t _size()
            {
                size_t avl_tree_node_counters = 0; 
                if(_root == nullptr)
                {
                    return avl_tree_node_counters;
                }
                else
                {
                    container_node* reference_node = _root;
                    template_container::stack_adapter::stack<container_node*> interior_stack;
                    interior_stack.push(reference_node);
                    while( !interior_stack.empty() )
                    {
                        reference_node = interior_stack.top();
                        interior_stack.pop();

                        avl_tree_node_counters++;

                        if(reference_node->_right != nullptr)
                        {
                            interior_stack.push(reference_node->_right);
                        }
                        if(reference_node->_left != nullptr)
                        {
                            interior_stack.push(reference_node->_left);
                        }
                    }
                }
                return avl_tree_node_counters;
            }
        public:
            using iterator = avl_tree_iterator<avl_tree_node_pair,avl_tree_node_pair&,avl_tree_node_pair*>;
            using const_iterator = avl_tree_iterator<avl_tree_node_pair,const avl_tree_node_pair&,const avl_tree_node_pair*>;

            using reverse_iterator = avl_tree_reverse_iterator<iterator>;
            using const_reverse_iterator = avl_tree_reverse_iterator<const_iterator>;

            iterator begin()                    
            {
                container_node* start_position_node = _root;
                while(start_position_node != nullptr && start_position_node->_left != nullptr)
                {
                    start_position_node = start_position_node->_left;
                }
                return iterator(start_position_node);
            }
            iterator end()
            {
                return iterator(nullptr);
            }
            const_iterator cbegin() const
            {
                container_node* start_position_node = _root;
                while(start_position_node != nullptr && start_position_node->_left != nullptr)
                {
                    start_position_node = start_position_node->_left;
                }
                return const_iterator(start_position_node);
            }
            const_iterator cend() const
            {
                return const_iterator(nullptr);
            }
            reverse_iterator rbegin()
            {
                container_node* reverse_start_position = _root;
                while(reverse_start_position!= nullptr && reverse_start_position->_right != nullptr)
                {
                    reverse_start_position = reverse_start_position->_right;
                }
                return reverse_iterator(iterator(reverse_start_position));
            }
            reverse_iterator rend()
            {
                return reverse_iterator(iterator(nullptr));
            }
            const_reverse_iterator crbegin() const
            {
                container_node* reverse_start_position = _root;
                while(reverse_start_position!= nullptr && reverse_start_position->_right != nullptr)
                {
                    reverse_start_position = reverse_start_position->_right;
                }
                return const_reverse_iterator(const_iterator(reverse_start_position));
            }
            const_reverse_iterator crend() const
            {
                return const_reverse_iterator(const_iterator(nullptr));
            }
            bool empty()
            {
                return _root == nullptr;
            }
            avl_tree()
            {
                _root = nullptr;
            }
            avl_tree(const avl_tree_type_k& key_data,const avl_tree_type_v& val_data = avl_tree_type_v(),
            container_imitate_function com_value = container_imitate_function())
            :_root(nullptr),function_policy(com_value)
            {
                _root = new container_node(key_data,val_data);
            }
            avl_tree(const avl_tree_node_pair& pair_type_data,
            container_imitate_function com_value = container_imitate_function())
            :_root(nullptr),function_policy(com_value)
            {
                _root = new container_node(pair_type_data.first,pair_type_data.second);
            }
            avl_tree(const avl_tree& avl_tree_data)
            : _root(nullptr), function_policy(avl_tree_data.function_policy)
            {
                if (avl_tree_data._root == nullptr)
                {
                    return;
                }

                // 使用单栈，存储源节点和目标父节点（均为一级指针）
                template_container::stack_adapter::stack<template_container::practicality::pair<container_node*, container_node*>> stack;
                
                // 创建根节点
                _root = new container_node(avl_tree_data._root->_data);
                _root->_balance_factor = avl_tree_data._root->_balance_factor;
                _root->_parent = nullptr; // 根节点的父节点为nullptr
                
                // 初始化栈，将根节点的子节点压入（注意：这里父节点是 _ROOT，一级指针）
                if (avl_tree_data._root->_right != nullptr)
                {
                    stack.push(template_container::practicality::pair<container_node*, container_node*>(avl_tree_data._root->_right, _root));
                }
                if (avl_tree_data._root->_left != nullptr)
                {
                    stack.push(template_container::practicality::pair<container_node*, container_node*>(avl_tree_data._root->_left, _root));
                }

                // 遍历并复制剩余节点
                while (!stack.empty())
                {
                    auto [first_node, second_node] = stack.top();
                    stack.pop();
                    
                    // 创建新节点并复制数据
                    container_node* new_structure_node = new container_node(first_node->_data);
                    new_structure_node->_balance_factor = first_node->_balance_factor;
                    
                    // 设置父节点关系（注意：second_node 是一级指针）
                    new_structure_node->_parent = second_node;
                    
                    // 判断源节点在原树中是左子还是右子
                    bool isleft_child = false;
                    if (first_node->_parent != nullptr) 
                    {
                        isleft_child = (first_node->_parent->_left == first_node);
                    }
                    
                    // 将新节点链接到父节点的正确位置（注意：直接使用 second_node）
                    if (isleft_child) 
                    {
                        second_node->_left = new_structure_node;
                    } 
                    else 
                    {
                        second_node->_right = new_structure_node;
                    }

                    // 处理子节点（注意：压栈时父节点是 new_structure_node，一级指针）
                    if (first_node->_right != nullptr)
                    {
                        stack.push(template_container::practicality::pair<container_node*, container_node*>(first_node->_right, new_structure_node));
                    }
                    if (first_node->_left != nullptr)
                    {
                        stack.push(template_container::practicality::pair<container_node*, container_node*>(first_node->_left, new_structure_node));
                    }
                }
            }
            avl_tree(avl_tree&& avl_tree_data) noexcept
            : _root(nullptr),function_policy(avl_tree_data.function_policy)
            {
                _root = std::move(avl_tree_data._root);
                avl_tree_data._root = nullptr;
            }
            avl_tree& operator=(avl_tree&& avl_tree_data) noexcept
            {
                if(this != &avl_tree_data)
                {
                    clear();
                    _root = std::move(avl_tree_data._root);
                    function_policy  = std::move(avl_tree_data.function_policy);
                    avl_tree_data._root = nullptr;
                    return *this;
                }
            }
            avl_tree& operator=(const avl_tree avl_tree_data)
            {
                clear();
                if(&avl_tree_data == this)
                {
                    return *this;
                }
                if (avl_tree_data._root == nullptr)
                {
                    return *this;
                }
                template_container::algorithm::swap(function_policy,avl_tree_data.function_policy);
                template_container::algorithm::swap(_root,avl_tree_data._root);
                return *this;
            }
            ~avl_tree()                         {       clear();            }

            size_t size() const                 {       return _size();     }

            size_t size()                       {       return _size();     } 

            void pre_order_traversal()          {       interior_pre_order_traversal(_root); }

            void middle_order_traversal()       {       interior_middle_order_traversal(_root);     }

            bool push(const avl_tree_type_k& key_data,const avl_tree_type_v& val_data = avl_tree_type_v())
            {
                //插入
                if(_root == nullptr)
                {
                    _root = new container_node(key_data,val_data);
                    return true;
                }
                else
                {
                    container_node* reference_node = _root;
                    container_node* parent_node = nullptr;
                    while(reference_node)
                    {
                        parent_node = reference_node;
                        if(!function_policy(key_data,reference_node->_data.first) && !function_policy(reference_node->_data.first,key_data))
                        {
                            return false;
                        }
                        else if(function_policy(key_data,reference_node->_data.first))
                        {
                            reference_node = reference_node->_left;
                        }
                        else
                        {
                            reference_node = reference_node->_right;
                        }
                    }
                    reference_node = new container_node(key_data,val_data);
                    if(function_policy(key_data,parent_node->_data.first))
                    {
                        parent_node->_left = reference_node;
                    }
                    else
                    {
                        parent_node->_right = reference_node;
                    }
                    reference_node->_parent = parent_node;

                    container_node* adjust_reference_node = reference_node;
                    container_node* adjust_reference_parent_node = parent_node;

                    while(adjust_reference_parent_node)
                    {
                        if(adjust_reference_parent_node->_left == adjust_reference_node)
                        {
                            adjust_reference_parent_node->_balance_factor--;
                        }
                        else
                        {
                            adjust_reference_parent_node->_balance_factor++;
                        }

                        if(adjust_reference_parent_node->_balance_factor == 0)
                        {
                            break;
                        }
                        else if (adjust_reference_parent_node->_balance_factor == 1 || adjust_reference_parent_node->_balance_factor == -1)
                        {
                            adjust_reference_node = adjust_reference_parent_node;
                            adjust_reference_parent_node = adjust_reference_parent_node->_parent;
                        }
                        else if (adjust_reference_parent_node->_balance_factor == 2 || adjust_reference_parent_node->_balance_factor == -2)
                        {
                            if(adjust_reference_parent_node->_balance_factor == 2)
                            {
                                if(adjust_reference_node->_balance_factor == 1)
                                {
                                    left_revolve(adjust_reference_parent_node);
                                }
                                else
                                {
                                    right_left_revolve(adjust_reference_parent_node);
                                }
                            }
                            if(adjust_reference_parent_node->_balance_factor == -2)
                            {
                                if(adjust_reference_node->_balance_factor == -1)
                                {
                                    right_revolve(adjust_reference_parent_node);
                                }
                                else
                                {
                                    left_right_revolve(adjust_reference_parent_node);
                                }
                            }
                            adjust_reference_node = adjust_reference_parent_node;
                            adjust_reference_parent_node = adjust_reference_parent_node->_parent;
                        }
                    }
                }
                return true;
            }
            bool push(const avl_tree_node_pair& pair_type_data)
            {
                //AVL树左子树比右子树高，则他俩的根节点的平衡因子为1，反之为-1，也就是说左加一，右减一，如果根节点为2和-2就要需要调整了
                if(_root == nullptr)
                {
                    _root = new container_node(pair_type_data.first,pair_type_data.second);
                    return true;
                }
                else
                {
                    container_node* reference_node = _root;
                    container_node* parent_node = nullptr;
                    while(reference_node != nullptr)
                    {
                        parent_node = reference_node;
                        //找到first该在的节点
                        if(!function_policy(pair_type_data.first,reference_node->_data.first) && !function_policy(reference_node->_data.first,pair_type_data.first))
                        {
                            //不允许重复插入
                            return false;
                        } 
                        else if(function_policy(pair_type_data.first,reference_node->_data.first))
                        {
                            reference_node = reference_node->_left;
                        }
                        else
                        {
                            reference_node = reference_node->_right;
                        }
                    }
                    reference_node = new container_node(pair_type_data);
                    if(function_policy(pair_type_data.first,parent_node->_data.first))
                    {
                        parent_node->_left = reference_node;
                        //三叉链表，注意父亲节点指向
                    }
                    else
                    {
                        parent_node->_right = reference_node;
                    }
                    reference_node->_parent = parent_node;
                    container_node* adjust_reference_node = reference_node;
                    container_node* adjust_reference_parent_node = parent_node;
                    //更新平衡因子
                    while(adjust_reference_parent_node)
                    {
                        //更新到根节点跳出
                        if(adjust_reference_node == adjust_reference_parent_node->_right)
                        {
                            adjust_reference_parent_node->_balance_factor++;
                        }
                        else
                        {
                            adjust_reference_parent_node->_balance_factor--;
                        }

                        if(adjust_reference_parent_node->_balance_factor == 0)
                        {
                            //平衡因子为0，无需平衡
                            break;
                        }
                        else if(adjust_reference_parent_node->_balance_factor == 1 || adjust_reference_parent_node->_balance_factor == -1)
                        {
                            adjust_reference_node = adjust_reference_parent_node;
                            adjust_reference_parent_node = adjust_reference_parent_node->_parent;
                            //向上更新，直到找到0或-2或2
                        }
                        else if(adjust_reference_parent_node->_balance_factor == 2 || adjust_reference_parent_node->_balance_factor == -2)
                        {
                            //平衡因子为2或者-2，需要平衡
                            if(adjust_reference_parent_node->_balance_factor == 2)
                            {
                                if(adjust_reference_node->_balance_factor == 1)
                                {
                                    //L，说明_ROOT_Temp_test是_ROOT_Temp_test_parent的左子节点，线形
                                    left_revolve(adjust_reference_parent_node);
                                }
                                else
                                {
                                    //RL，证明_ROOT_Temp_test是_ROOT_Temp_test_parent的右子节点，在AVL树抽象图上就是折线型的
                                    right_left_revolve(adjust_reference_parent_node);
                                }
                            }
                            else if (adjust_reference_parent_node->_balance_factor == -2)
                            {
                                if(adjust_reference_node->_balance_factor == -1)
                                {
                                    //R，说明_ROOT_Temp_test是_ROOT_Temp_test_parent的右子节点，线形
                                    right_revolve(adjust_reference_parent_node);
                                }
                                else
                                {
                                    //LR，和上同理
                                    left_right_revolve(adjust_reference_parent_node);
                                }
                            }
                            //旋转后继续向上调整，因为旋转后父节点的平衡因子可能发生变化，每个旋转的节点都可以当作一个子树，子树旋转后，父节点平衡因子可能发生变化
                            adjust_reference_node = adjust_reference_parent_node;
                            adjust_reference_parent_node = adjust_reference_parent_node->_parent;
                            //对于双旋的情况，相同方向先调整该节点，再调整整体
                        }
                    }
                }
                return true;
            }
            container_node* find(const avl_tree_type_k& key_data)
            {
                container_node* reference_node = _root;
                while(reference_node != nullptr)
                {
                    if(reference_node->_data == key_data)
                    {
                        break;
                    }
                    else if (function_policy(reference_node->_data,key_data))
                    {
                        reference_node = reference_node->_right;
                    }
                    else
                    {
                        reference_node = reference_node->_left;
                    }
                }
                return reference_node;
            }
            avl_tree& pop(const avl_tree_type_k& key_data)
            {
                if(_root == nullptr)
                {
                    return *this;
                }
                container_node* reference_node = _root;
                container_node* parent_node = nullptr;
                while(reference_node != nullptr)
                {
                    if(!function_policy(key_data,reference_node->_data.first) && !function_policy(reference_node->_data.first,key_data))
                    {
                        break;
                    }
                    parent_node = reference_node;
                    if (function_policy(reference_node->_data.first,key_data))
                    {
                        reference_node = reference_node->_right;
                    }
                    else
                    {
                        reference_node = reference_node->_left;
                    }
                }
                if(reference_node == nullptr)
                {
                    return *this;
                    //没有找到
                }
                //三种情况：左空，右空，左右都不空
                if (reference_node->_left == nullptr) 
                {
                    if (reference_node->_right != nullptr) 
                    {
                        reference_node->_right->_parent = parent_node;
                    }
                    if (parent_node == nullptr) 
                    {
                        _root = reference_node->_right;
                    } 
                    else 
                    {
                        if (parent_node->_left == reference_node) 
                        {
                            parent_node->_left = reference_node->_right;
                        } 
                        else 
                        {
                            parent_node->_right = reference_node->_right;
                        }
                    }
                    delete reference_node;
                    reference_node = nullptr;
                }            
                else if (reference_node->_right == nullptr)
                {
                    if(reference_node->_left != nullptr)
                    {
                        reference_node->_left->_parent = parent_node;
                    }
                    if(parent_node == nullptr)
                    {
                        _root = reference_node->_left;
                    }
                    else
                    {
                        if(parent_node->_left == reference_node)
                        {
                            parent_node->_left = reference_node->_left;
                        }
                        else
                        {
                            parent_node->_right = reference_node->_left; 
                        }
                        if(reference_node->_left!= nullptr)
                        {
                            reference_node->_left->_parent = parent_node;
                        }
                        //更新父节点
                    }
                    delete reference_node;
                    reference_node = nullptr;
                }
                else if(reference_node->_right != nullptr && reference_node->_left != nullptr)
                {
                    //找右子树最左节点
                    container_node* right_subtree_smallest_node = reference_node->_right;
                    container_node* smallest_parent_node = reference_node;
                    while(right_subtree_smallest_node->_left != nullptr)
                    {
                        smallest_parent_node = right_subtree_smallest_node;
                        right_subtree_smallest_node = right_subtree_smallest_node->_left;
                    }
                    template_container::algorithm::swap(right_subtree_smallest_node->_data,reference_node->_data);
                    if (smallest_parent_node == reference_node) 
                    {
                        smallest_parent_node->_right = (right_subtree_smallest_node->_right != nullptr) ? right_subtree_smallest_node->_right : nullptr;
                    } 
                    else 
                    {
                        smallest_parent_node->_left = (right_subtree_smallest_node->_right != nullptr) ? right_subtree_smallest_node->_right : nullptr;
                    }
                    if (right_subtree_smallest_node->_right != nullptr) 
                    {
                        right_subtree_smallest_node->_right->_parent = smallest_parent_node;
                    }
                    delete right_subtree_smallest_node;
                    right_subtree_smallest_node = nullptr;         
                }
                //更新平衡因子
                container_node* parent_bf = parent_node;
                while(parent_bf != nullptr)
                {
                    if(parent_bf->_left == reference_node)
                    {
                        parent_bf->_balance_factor--;
                    }
                    else
                    {
                        parent_bf->_balance_factor++;
                    }
                    if(parent_bf->_balance_factor == 0)
                    {
                        break;
                    }
                    else if(parent_bf->_balance_factor == 1 || parent_bf->_balance_factor == -1)
                    {
                        reference_node = parent_bf;
                        parent_bf = parent_bf->_parent;
                    }
                    else if(parent_bf->_balance_factor == 2 || parent_bf->_balance_factor == -2)
                    {
                        if(parent_bf->_balance_factor == 2)
                        {
                            if(reference_node->_balance_factor == 1)
                            {
                                left_revolve(parent_bf);
                            }
                            else
                            {
                                right_left_revolve(parent_bf);
                            }
                        }
                        else if(parent_bf->_balance_factor == -2)
                        {
                            if(reference_node->_balance_factor == -1)
                            {
                                right_revolve(parent_bf);
                            }
                            else
                            {
                                left_right_revolve(parent_bf);
                            }
                        }
                        parent_bf = parent_bf->_parent;
                        reference_node = parent_bf;
                        //双旋的情况，先调整该节点，再调整整体
                    }
                }
                return *this;
            }
        };
    }
    /*############################     基类容器命名空间     ############################*/
    namespace base_class_container
    {
        /*############################     rb_tree 容器     ############################*/
        template <typename rb_tree_type_key, typename rb_tree_type_value, typename container_imitate_function_visit,
        typename container_imitate_function = template_container::imitation_functions::less<rb_tree_type_key>>
        class rb_tree
        {
        private:
            enum rb_tree_color
            {
                red,
                black,
            };
            class rb_tree_node
            {
            public:
                rb_tree_type_value _data;
                rb_tree_node* _left;
                rb_tree_node* _right;
                rb_tree_node* _parent;
                rb_tree_color _color;
                rb_tree_node(const rb_tree_type_value& val_data = rb_tree_type_value())
                :_data(val_data),_left(nullptr),_right(nullptr),_parent(nullptr),_color(red)
                {
                    ;
                }
                rb_tree_node(rb_tree_type_value&& val_data) noexcept
                :_data(std::move(val_data)),_left(nullptr),_right(nullptr),_parent(nullptr),_color(red)
                {
                    ;
                }
            };
            template<typename T, typename Ref, typename Ptr>
            class rb_tree_iterator
            { 
                using self = rb_tree_iterator<T,Ref,Ptr>;
                using iterator_node = rb_tree_node;
                iterator_node* _node_iterator_ptr;
            public:
                using reference = Ref;
                using pointer = Ptr;
                rb_tree_iterator(iterator_node* iterator_ptr_data)
                :_node_iterator_ptr(iterator_ptr_data)
                {
                    ;
                }
                rb_tree_iterator()
                {
                    _node_iterator_ptr = nullptr;
                }
                Ref& operator*()
                {
                    return _node_iterator_ptr->_data;
                }
                Ptr operator->()
                {
                    return &(_node_iterator_ptr->_data);
                }
                self& operator++()
                {
                    if(_node_iterator_ptr == nullptr)
                    {
                        return *this;
                    }
                    if(_node_iterator_ptr->_right != nullptr)
                    {
                        iterator_node* subtree_node = _node_iterator_ptr->_right;
                        while(subtree_node->_left != nullptr)
                        {
                            subtree_node = subtree_node->_left;
                        }
                        _node_iterator_ptr = subtree_node;
                    }
                    else
                    {
                        //代表右子树已经走完，需要向上遍历，继续向上找右子树，如果停下来，说明走完整棵树或者是走到根节点
                        iterator_node* last_parent_node = _node_iterator_ptr->_parent;
                        iterator_node* temporary_subtree_node = _node_iterator_ptr;
                        while(last_parent_node != nullptr && temporary_subtree_node == last_parent_node->_right)
                        {
                            temporary_subtree_node = last_parent_node;
                            last_parent_node = last_parent_node->_parent;
                        }
                        _node_iterator_ptr = last_parent_node;
                        //如果跳出循环，说明走到了根节点，或者找到了右子树
                    }
                    return *this;
                }
                self operator++(int)
                {
                    self previously_iterator = *this;
                    ++(*this);
                    return previously_iterator;
                }
                self& operator--()
                {
                    if(_node_iterator_ptr->_left != nullptr)
                    {
                        iterator_node* subtree_node = _node_iterator_ptr->_left;
                        while(subtree_node->_right != nullptr)
                        {
                            subtree_node = subtree_node->_right;
                        }
                        _node_iterator_ptr = subtree_node;
                    }
                    else
                    {
                        iterator_node* last_parent_node = _node_iterator_ptr->_parent;
                        iterator_node* temporary_subtree_node = _node_iterator_ptr;
                        while(last_parent_node != nullptr && temporary_subtree_node == last_parent_node->_left)
                        {
                            temporary_subtree_node = last_parent_node;
                            last_parent_node = last_parent_node->_parent;
                        }
                        _node_iterator_ptr = last_parent_node;
                    }
                    return *this;
                }
                self operator--(int)
                {
                    self previously_iterator = *this;
                    --(*this);
                    return previously_iterator;
                }
                bool operator==(const self& it_data) const
                {
                    return _node_iterator_ptr == it_data._node_iterator_ptr;
                }
                bool operator!=(const self& it_data) const
                {
                    return _node_iterator_ptr != it_data._node_iterator_ptr;
                }
            };
            template <typename iterator>
            class rb_tree_reverse_iterator
            {
                using self = rb_tree_reverse_iterator<iterator>;
                using Ref  = typename iterator::reference;
                using Ptr  = typename iterator::pointer;
                iterator _it;
            public:
                rb_tree_reverse_iterator(iterator it_data)
                :_it(it_data)
                {
                    ;
                }
                Ref& operator*()
                {
                    return *_it;
                }
                Ptr operator->()
                {
                    return &(*this);
                }
                // 前置自增：对应正向迭代器的自减
                rb_tree_reverse_iterator& operator++() 
                { 
                    --_it; 
                    return *this; 
                }
                rb_tree_reverse_iterator operator++(int) 
                { 
                    auto previously_iterator = *this; 
                    --_it; 
                    return previously_iterator; 
                }

                // 前置自减：对应正向迭代器的自增
                rb_tree_reverse_iterator& operator--() 
                { 
                    ++_it; 
                    return *this; 
                }
                rb_tree_reverse_iterator operator--(int) 
                { 
                    auto previously_iterator = *this; 
                    ++_it; return previously_iterator; 
                }

                // 比较运算符
                bool operator==(const rb_tree_reverse_iterator& other) const 
                { 
                    return _it == other._it; 
                }
                bool operator!=(const rb_tree_reverse_iterator& other) const 
                { 
                    return _it != other._it; 
                }
            };
            using container_node = rb_tree_node;
            container_node* _root;
            container_imitate_function_visit element;
            container_imitate_function function_policy;
            void left_revolve(container_node* subtree_node)
            {
                try 
                {
                    if(subtree_node == nullptr)
                    {
                        throw custom_exception::customize_exception("左单旋传进来的节点为空！","left_revolve",__LINE__);
                    }
                } 
                catch(const custom_exception::customize_exception& exception)
                {
                    std::cerr << exception.what() << exception.function_name_get() << exception.line_number_get() << std::endl;
                    throw;
                }    
                container_node* sub_tree_right_node = subtree_node->_right;
                // container_node* sub_right_left_node = sub_tree_right_node->_left;
                container_node* sub_right_left_node = (sub_tree_right_node->_left)? sub_tree_right_node->_left : nullptr;
                //防止空指针解引用
                subtree_node->_right = sub_right_left_node;
                if(sub_right_left_node)
                {
                    sub_right_left_node->_parent = subtree_node;
                    //如果Sub_right_left_temp(调整节点的左根节点)不等于空，还需要调整Sub_right_left_temp它的父亲节点
                }
                sub_tree_right_node->_left = subtree_node;
                //这里先保存一下parent_temp_Node的父亲地址，防止到下面else比较的时候丢失
                container_node* parent_node = subtree_node->_parent;
                subtree_node->_parent = sub_tree_right_node;
                //更新parent_temp_Node节点指向正确的地址

                if(_root == subtree_node)
                {
                    //如果要调整的节点是根根节点，直接把调整节点赋值给根节点，然后把调整节点的父亲节点置空
                    _root = sub_tree_right_node;
                    sub_tree_right_node->_parent = nullptr;
                }
                else
                {
                    //调整前parent_temp_Node是这个树的根现在是Sub_right_temp是这个树的根
                    if(parent_node->_left == subtree_node)
                    {
                        parent_node->_left = sub_tree_right_node;
                    }
                    else
                    {
                        parent_node->_right = sub_tree_right_node;
                    }
                    sub_tree_right_node->_parent = parent_node;
                }
            }
            void right_revolve(container_node* subtree_node)
            {
                try 
                {
                    if(subtree_node == nullptr)
                    {
                        throw custom_exception::customize_exception("右单旋传进来的节点为空！","right_revolve",__LINE__);
                    }
                } 
                catch(const custom_exception::customize_exception& exception)
                {
                    std::cerr << exception.what() << exception.function_name_get() << exception.line_number_get() << std::endl;
                    throw;
                }    
                container_node* sub_tree_left_node = subtree_node->_left;
                container_node* sub_left_right_node = (sub_tree_left_node->_right) ? sub_tree_left_node->_right : nullptr;
                //防止空指针解引用
                subtree_node->_left = sub_left_right_node;
                if(sub_left_right_node)
                {
                    sub_left_right_node->_parent = subtree_node;
                }
                sub_tree_left_node->_right = subtree_node;
                //保存parent_temp_Node的父亲节点
                container_node* parent_node = subtree_node->_parent;
                subtree_node->_parent = sub_tree_left_node;

                if(_root == subtree_node)
                {
                    _root = sub_tree_left_node;
                    sub_tree_left_node->_parent = nullptr;
                }
                else
                {
                    if(parent_node->_left == subtree_node)
                    {
                        parent_node->_left = sub_tree_left_node;
                    }
                    else
                    {
                        parent_node->_right = sub_tree_left_node;
                    }
                    sub_tree_left_node->_parent = parent_node;
                }
            }
            void clear(container_node* clear_node_ptr)
            {
                if(clear_node_ptr == nullptr)
                {
                    return ;
                }
                else
                {
                    template_container::stack_adapter::stack<container_node*> resource_cleanup_stack;
                    resource_cleanup_stack.push(clear_node_ptr);
                    while ( !resource_cleanup_stack.empty() )
                    {
                        clear_node_ptr = resource_cleanup_stack.top();
                        resource_cleanup_stack.pop();
                        if(clear_node_ptr->_right != nullptr)
                        {
                            resource_cleanup_stack.push(clear_node_ptr->_right);
                        }
                        if(clear_node_ptr->_left  != nullptr)
                        {
                            resource_cleanup_stack.push(clear_node_ptr->_left);
                        }
                        delete clear_node_ptr;
                    }
                    _root = nullptr;
                }
            }
            void interior_middle_order_traversal(container_node* intermediate_traversal_node)
            {
                //中序遍历函数
                if(intermediate_traversal_node == nullptr)
                {
                    return ;
                }
                template_container::stack_adapter::stack<container_node*> interior_stack;
                while(intermediate_traversal_node != nullptr || !interior_stack.empty())
                {
                    while(intermediate_traversal_node!= nullptr)
                    {
                        interior_stack.push(intermediate_traversal_node);
                        intermediate_traversal_node = intermediate_traversal_node->_left;
                    }
                    intermediate_traversal_node = interior_stack.top();
                    interior_stack.pop();
                    std::cout <<  intermediate_traversal_node->_data << " ";
                    // std::cout << intermediate_traversal_node->_color <<" ";
                    intermediate_traversal_node = intermediate_traversal_node->_right;
                }
            }
            void interior_pre_order_traversal(container_node* preamble_traversal_node )
            {
                //前序遍历，最外左子树全部压栈
                if(preamble_traversal_node == nullptr)
                {
                    return;
                }
                container_node* reference_node = preamble_traversal_node;
                template_container::stack_adapter::stack<container_node*> interior_stack;
                interior_stack.push(reference_node);
                while( !interior_stack.empty() )
                {
                    reference_node = interior_stack.top();
                    interior_stack.pop();

                    std::cout << reference_node->_data << " ";
                    // std::cout << reference_node->_color <<" ";
                    //修改逻辑错误，先压右子树再压左子树，因为这是栈
                    if(reference_node->_right != nullptr)
                    {
                        interior_stack.push(reference_node->_right);
                    }
                    if(reference_node->_left != nullptr)
                    {
                        interior_stack.push(reference_node->_left);
                    }
                }
            }
            static inline rb_tree_color get_color(container_node* current_node)
            {
                return current_node == nullptr ? black : current_node->_color;
            }
            static inline bool red_get(container_node* current_node)
            {
                return get_color(current_node) == red;
            }
            static inline bool black_get(container_node* current_node)
            {
                return get_color(current_node) == black;
            }
            size_t _size() const 
            {
                size_t size = 0;
                if(_root == nullptr)
                {
                    return size;
                }
                container_node* reference_node = _root;
                template_container::stack_adapter::stack<container_node*> interior_stack;
                interior_stack.push(reference_node);
                while( !interior_stack.empty() )
                {
                    reference_node = interior_stack.top();
                    interior_stack.pop();

                    size++;
                    if(reference_node->_right != nullptr)
                    {
                        interior_stack.push(reference_node->_right);
                    }
                    if(reference_node->_left != nullptr)
                    {
                        interior_stack.push(reference_node->_left);
                    }
                }
                return size;
            }
        public:
            using iterator = rb_tree_iterator<rb_tree_type_value,rb_tree_type_value&,rb_tree_type_value*>; 
            using const_iterator =  rb_tree_iterator<rb_tree_type_value const,rb_tree_type_value const&,rb_tree_type_value const*>;

            using reverse_iterator = rb_tree_reverse_iterator<iterator>;
            using const_reverse_iterator = rb_tree_reverse_iterator<const_iterator>;

            using return_pair_value = template_container::practicality::pair<iterator,bool>;
            rb_tree()
            {
                _root = nullptr;
            }
            rb_tree(const rb_tree_type_value& rb_tree_data)
            {
                _root = new container_node(rb_tree_data);
                _root->_color = black;
            }
            rb_tree(rb_tree_type_value&& rb_tree_data) noexcept
            {
                _root = new container_node(std::forward<rb_tree_type_value>(rb_tree_data));
                _root->_color = black;
            }
            rb_tree(rb_tree&& rb_tree_data) noexcept
            :function_policy(rb_tree_data.function_policy),element(rb_tree_data.element)
            {
                _root = std::move(rb_tree_data._root);
                rb_tree_data._root = nullptr;
            }
            rb_tree(const rb_tree& rb_tree_data)
            :function_policy(rb_tree_data.function_policy),element(rb_tree_data.element),_root(nullptr)
            {
                if(rb_tree_data._root == nullptr)
                {
                    _root = nullptr;
                }
                else
                {
                    // 使用单栈，存储源节点和目标父节点（均为一级指针）
                    template_container::stack_adapter::stack<template_container::practicality::pair<container_node*, container_node*>> stack;
                    
                    // 创建根节点
                    _root = new container_node(rb_tree_data._root->_data);
                    _root->_color = rb_tree_data._root->_color;
                    _root->_parent = nullptr; // 根节点的父节点为nullptr
                    
                    // 初始化栈，将根节点的子节点压入（注意：这里父节点是 _ROOT，一级指针）
                    if (rb_tree_data._root->_right != nullptr)
                    {
                        stack.push(template_container::practicality::pair<container_node*, container_node*>(rb_tree_data._root->_right, _root));
                    }
                    if (rb_tree_data._root->_left != nullptr)
                    {
                        stack.push(template_container::practicality::pair<container_node*, container_node*>(rb_tree_data._root->_left, _root));
                    }

                    // 遍历并复制剩余节点
                    while (!stack.empty())
                    {
                        auto [first_node, parent_node] = stack.top();
                        stack.pop();
                        
                        // 创建新节点并复制数据
                        container_node* new_structure_node = new container_node(first_node->_data);
                        new_structure_node->_color = first_node-> _color;
                        
                        // 设置父节点关系（注意：parent_node 是一级指针）
                        new_structure_node->_parent = parent_node;
                        
                        // 判断源节点在原树中是左子还是右子
                        bool isleft_child = false;
                        if (first_node->_parent != nullptr) 
                        {
                            isleft_child = (first_node->_parent->_left == first_node);
                        }
                        
                        // 将新节点链接到父节点的正确位置（注意：直接使用 parent_node）
                        if (isleft_child) 
                        {
                            parent_node->_left = new_structure_node;
                        } 
                        else 
                        {
                            parent_node->_right = new_structure_node;
                        }

                        // 处理子节点（注意：压栈时父节点是 new_node，一级指针）
                        if (first_node->_right != nullptr)
                        {
                            stack.push(template_container::practicality::pair<container_node*, container_node*>(first_node->_right, new_structure_node));
                        }
                        if (first_node->_left != nullptr)
                        {
                            stack.push(template_container::practicality::pair<container_node*, container_node*>(first_node->_left, new_structure_node));
                        }
                    }
                }
            }
            rb_tree& operator=(const rb_tree rb_tree_data)
            {
                if(this == &rb_tree_data)
                {
                    return *this;
                }
                else
                {
                    clear(_root);
                    template_container::algorithm::swap(rb_tree_data._root,_root);
                    template_container::algorithm::swap(rb_tree_data.element,element);
                    template_container::algorithm::swap(rb_tree_data.function_policy,function_policy);
                    return *this;
                }
            }
            rb_tree& operator=(rb_tree&& rb_tree_data) noexcept
            {
                if(this != &rb_tree_data)
                {
                    clear();
                    function_policy = std::move(rb_tree_data.function_policy);
                    element = std::move(rb_tree_data.element);
                    _root = std::move(rb_tree_data._root);
                    rb_tree_data._root = nullptr;
                }
                return *this;
            }
            ~rb_tree()
            {
                clear(_root);
            }
            return_pair_value push(const rb_tree_type_value& value_data)
            {
                if(_root == nullptr)
                {
                    _root = new container_node(value_data);
                    _root->_color = black;
                    return return_pair_value(iterator(_root),true);
                }
                else
                {
                    container_node* reference_node = _root;
                    container_node* parent_node = nullptr;
                    while(reference_node != nullptr)
                    {
                        parent_node = reference_node;
                        if(!function_policy(element(reference_node->_data),element(value_data)) &&
                         !function_policy(element(value_data),element(reference_node->_data)))
                        {
                            //插入失败，找到相同的值，开始返回
                            return return_pair_value(iterator(reference_node),false);
                        }
                        else if(function_policy(element(reference_node->_data),element(value_data)))
                        {
                            reference_node = reference_node->_right;
                        }
                        else
                        {
                            reference_node = reference_node->_left;
                        }
                    }
                    //找到插入位置
                    reference_node = new container_node(value_data);
                    if(function_policy(element(parent_node->_data),element(reference_node->_data)))
                    {
                        parent_node->_right = reference_node;
                    }
                    else
                    {
                        parent_node->_left = reference_node;
                    }
                    reference_node->_color = red;
                    reference_node->_parent = parent_node;
                    container_node* return_push_node = reference_node;
                    //保存节点
                    //开始调整，向上调整颜色节点
                    while(parent_node != nullptr && parent_node->_color == red )
                    {
                        container_node* grandfther_node = parent_node->_parent;
                        if(grandfther_node->_left == parent_node)
                        {
                            //叔叔节点
                            // std::cout << "push" <<" ";
                            container_node* uncle_node = grandfther_node->_right;
                            //情况1：uncle存在，且为红
                            //情况2: uncle不存在，那么_ROOT_Temp就是新增节点
                            //情况3：uncle存在且为黑，说明_ROOT_Temp不是新增节点
                            if(uncle_node && uncle_node->_color == red)
                            {
                                //情况1：
                                parent_node->_color = uncle_node->_color = black;
                                grandfther_node->_color = red;
                                //颜色反转完成
                                reference_node = grandfther_node;
                                parent_node = reference_node->_parent;
                                //向上调整,继续从红色节点开始
                            }
                            else
                            {
                                //情况3：该情况双旋转单旋
                                if(reference_node == parent_node->_right)
                                {
                                    left_revolve(parent_node);
                                    template_container::algorithm::swap(reference_node,parent_node);
                                    // reference_node = parent_node;
                                    //折线调整，交换位置调整为情况2
                                }
                                //情况2：直接单旋
                                right_revolve(grandfther_node);
                                grandfther_node->_color = red;
                                parent_node->_color = black;
                            }
                        }
                        else
                        {
                            container_node* uncle_node = grandfther_node->_left;
                            //与上面相反
                            if(uncle_node && uncle_node->_color == red)
                            {
                                //情况1：
                                parent_node->_color = uncle_node->_color = black;
                                grandfther_node->_color = red;
                                //颜色反转完成
                                reference_node = grandfther_node;
                                parent_node = reference_node->_parent;
                            }
                            else
                            {
                                //情况3：该情况双旋转单旋
                                if(reference_node == parent_node->_left)
                                {
                                    right_revolve(parent_node);
                                    template_container::algorithm::swap(reference_node,parent_node);
                                    // reference_node = parent_node;
                                    //交换指针转换为单旋
                                }
                                //情况2：单旋
                                left_revolve(grandfther_node);
                                grandfther_node->_color = red;
                                parent_node->_color = black;
                            }
                        }
                    }
                    _root->_color = black;
                    return return_pair_value(iterator(return_push_node),true);
                }
            }
            return_pair_value push(rb_tree_type_value&& value_data) noexcept
            {
                if(_root == nullptr)
                {
                    _root = new container_node(std::forward<rb_tree_type_value>(value_data));
                    _root->_color = black;
                    return return_pair_value(iterator(_root),true);
                }
                else
                {
                    container_node* reference_node = _root;
                    container_node* parent_node = nullptr;
                    while(reference_node != nullptr)
                    {
                        parent_node = reference_node;
                        if(!function_policy(element(reference_node->_data),element(value_data)) &&
                         !function_policy(element(value_data),element(reference_node->_data)))
                        {
                            //插入失败，找到相同的值，开始返回
                            return return_pair_value(iterator(reference_node),false);
                        }
                        else if(function_policy(element(reference_node->_data),element(value_data)))
                        {
                            reference_node = reference_node->_right;
                        }
                        else
                        {
                            reference_node = reference_node->_left;
                        }
                    }
                    //找到插入位置
                    reference_node = new container_node(std::forward<rb_tree_type_value>(value_data));
                    if(function_policy(element(parent_node->_data),element(reference_node->_data)))
                    {
                        parent_node->_right = reference_node;
                    }
                    else
                    {
                        parent_node->_left = reference_node;
                    }
                    reference_node->_color = red;
                    reference_node->_parent = parent_node;
                    container_node* return_push_node = reference_node;
                    //保存节点
                    //开始调整，向上调整颜色节点
                    while(parent_node != nullptr && parent_node->_color == red )
                    {
                        container_node* grandfther_node = parent_node->_parent;
                        if(grandfther_node->_left == parent_node)
                        {
                            //叔叔节点
                            container_node* uncle_node = grandfther_node->_right;
                            //情况1：uncle存在，且为红
                            //情况2: uncle不存在，那么_ROOT_Temp就是新增节点
                            //情况3：uncle存在且为黑，说明_ROOT_Temp不是新增节点
                            if(uncle_node && uncle_node->_color == red)
                            {
                                //情况1：
                                parent_node->_color = uncle_node->_color = black;
                                grandfther_node->_color = red;
                                //颜色反转完成
                                reference_node = grandfther_node;
                                parent_node = reference_node->_parent;
                                //向上调整,继续从红色节点开始
                            }
                            else
                            {
                                //情况3：该情况双旋转单旋
                                if(reference_node == parent_node->_right)
                                {
                                    left_revolve(parent_node);
                                    template_container::algorithm::swap(reference_node,parent_node);
                                    // reference_node = parent_node;
                                    //折线调整，交换位置调整为情况2
                                }
                                //情况2：直接单旋
                                right_revolve(grandfther_node);
                                grandfther_node->_color = red;
                                parent_node->_color = black;
                            }
                        }
                        else
                        {
                            container_node* uncle_node = grandfther_node->_left;
                            //与上面相反
                            if(uncle_node && uncle_node->_color == red)
                            {
                                //情况1：
                                parent_node->_color = uncle_node->_color = black;
                                grandfther_node->_color = red;
                                //颜色反转完成
                                reference_node = grandfther_node;
                                parent_node = reference_node->_parent;
                            }
                            else
                            {
                                //情况3：该情况双旋转单旋
                                if(reference_node == parent_node->_left)
                                {
                                    right_revolve(parent_node);
                                    template_container::algorithm::swap(reference_node,parent_node);
                                    // reference_node = parent_node;
                                    //交换指针转换为单旋
                                }
                                //情况2：单旋
                                left_revolve(grandfther_node);
                                grandfther_node->_color = red;
                                parent_node->_color = black;
                            }
                        }
                    }
                    _root->_color = black;
                    return return_pair_value(iterator(return_push_node),true);
                }
            }
            /*
            删除节点后，调整红黑树颜色，分左右子树来调整，每颗子树分为4种情况
            情况 1：兄弟节点为红色
                    将兄弟节点设为黑色。
                    将父节点设为红色。
                    对父节点进行旋转（左子树删除则左旋，右子树删除则右旋）。
                    更新兄弟节点为新的兄弟（旋转后父节点的新子节点）。

            情况 2：兄弟节点为黑色，且兄弟的两个子节点都是黑色
                    将兄弟节点设为红色。
                    当前节点（cur）上移至父节点（parent）。
                    若上移后的节点是红色，将其设为黑色并结束调整；否则继续循环。
            情况 3：兄弟节点为黑色，兄弟的内侧子节点为红色，外侧子节点为黑色
                    将兄弟节点的内侧子节点设为黑色。
                    将兄弟节点设为红色。
                    对兄弟节点进行反向旋转（左子树删除则右旋，右子树删除则左旋）。
                    更新兄弟节点为新的兄弟（旋转后父节点的子节点）。
            情况 4：兄弟节点为黑色，且兄弟的外侧子节点为红色，内侧子节点为任意颜色
                    将兄弟节点的颜色设为父节点的颜色。
                    将父节点设为黑色。
                    将兄弟的外侧子节点设为黑色。
                    对父节点进行旋转（左子树删除则右旋，右子树删除则左旋）。
                    结束调整。
            */
            void delete_adjust(container_node* current_node ,container_node* parent)
            {
                //cur为被删节点的替代节点
                if(current_node == nullptr && parent == nullptr)
                {
                    return;
                }
                while(current_node != _root && (current_node == nullptr || black_get(current_node)))
                {
                    if(current_node == _root)
                    {
                        break;
                    }
                    if(parent->_left == current_node)
                    {
                        container_node* brother = parent->_right;
                        if(red_get(brother))
                        {
                            //情况1：兄弟节点为红
                            brother->_color = black;
                            parent->_color = red;
                            left_revolve(parent);
                            //调整后，兄弟节点为黑
                            //继续向下调整
                            brother = parent->_right;
                        }
                        if( (brother != nullptr && black_get(brother))  && ( brother->_left == nullptr || (brother->_left)) && 
                        (brother->_right == nullptr || black_get(brother->_right)))
                        {
                            //情况2：兄弟节点为黑，且兄弟节点两个子节点都为黑
                            brother->_color = red;
                            current_node = parent;
                            parent = current_node->_parent;
                            if(current_node->_color == red)
                            {
                                current_node->_color = black;
                                break;
                            }
                        }
                        else if( (brother != nullptr && black_get(brother)) &&  (brother->_right == nullptr || black_get(brother->_right)) && 
                        (brother->_left != nullptr && red_get(brother->_left)) )
                        {
                            //情况3：兄弟节点为黑，兄弟节点左节点为红，右节点为黑
                            brother->_left->_color = black;
                            brother->_color = red;
                            right_revolve(brother);
                            //调整后，兄弟节点为黑，兄弟节点右节点为红
                            //继续向下调整
                            brother = parent->_right;
                        }
                        else if( (brother != nullptr ||black_get(brother))  && (brother->_right != nullptr && red_get(brother->_right)) )
                        {
                            //情况4：兄弟节点为黑，兄弟节点右节点为红
                            brother->_color = parent->_color;
                            parent->_color = black;
                            brother->_right->_color = black;
                            left_revolve(parent);
                            current_node = _root;
                            parent = current_node->_parent;
                        }
                    }
                    else
                    {
                        container_node* brother = parent->_left;
                        if(red_get(brother))
                        {
                            //情况1：兄弟节点为红
                            brother->_color = black;
                            parent->_color = red;
                            right_revolve(parent);
                            //调整后，兄弟节点为黑
                            brother = parent->_left;
                        }
                        if( brother != nullptr && black_get(brother) && (brother->_left == nullptr || black_get(brother->_left)) &&
                        (brother->_right == nullptr || black_get(brother->_right)) )
                        {
                            //情况2：兄弟节点为黑，且兄弟节点两个子节点都为黑
                            brother->_color = red;
                            current_node = parent;
                            parent = current_node->_parent;
                            if(current_node->_color == red)
                            {
                                current_node->_color = black;
                                break;
                            }
                        }
                        else if (brother != nullptr && black_get(brother) && (brother->_right != nullptr && red_get(brother->_right)) &&
                        (brother->_left == nullptr || black_get(brother->_left)) )
                        {
                            //情况3：兄弟节点为黑，兄弟节点左节点为红，右节点为黑
                            brother->_right->_color = black;
                            brother->_color = red;
                            left_revolve(brother);
                            //调整后，兄弟节点为黑，兄弟节点右节点为红
                            //继续向下调整
                            brother = parent->_left;
                        }
                        else if(brother != nullptr && black_get(brother) && brother->_left != nullptr && red_get(brother->_left))
                        {
                            //情况4：兄弟节点为黑，兄弟节点右节点为红
                            brother->_color = parent->_color;
                            parent->_color = black;
                            brother->_left->_color = black;
                            right_revolve(parent);
                            current_node = _root;
                            parent = current_node->_parent;
                        }
                    }
                }
                if(current_node != nullptr)
                {
                    current_node->_color = black;
                }
            }
            return_pair_value pop(const rb_tree_type_value& rb_tree_data)
            {
                rb_tree_color delete_color;
                if(_root == nullptr)
                {
                    return return_pair_value(iterator(nullptr),false);
                }
                else
                {
                    container_node* reference_node = _root;
                    container_node* parent_node = nullptr;
                    container_node* adjust_node = nullptr;
                    container_node* adjust_parent_node = nullptr;
                    while(reference_node != nullptr)
                    {
                        if(!function_policy(element(reference_node->_data),element(rb_tree_data)) && !function_policy(element(rb_tree_data),element(reference_node->_data)))
                        {
                            break;
                        }
                        //防止父亲自赋值
                        parent_node = reference_node;
                        if(function_policy(element(reference_node->_data),element(rb_tree_data)))
                        {
                            reference_node = reference_node->_right;
                        }
                        else
                        {
                            reference_node = reference_node->_left;
                        }
                    }
                    if(reference_node == nullptr )
                    {
                        return return_pair_value(iterator(nullptr),false);
                    }
                    //找到位置开始删除
                    delete_color = reference_node->_color;
                    if(reference_node->_left == nullptr)
                    {
                        if(reference_node->_right != nullptr)
                        {
                            //右节点有值
                            reference_node->_right->_parent = parent_node;
                        }
                        if(parent_node == nullptr)
                        {
                            //根节点
                            _root = reference_node->_right;
                        }
                        else
                        {
                            //不为空，代表要删除的数不是在根节点上
                            if(parent_node->_left == reference_node)
                            {
                                parent_node->_left = reference_node->_right;
                            }
                            else
                            {
                                parent_node->_right = reference_node->_right;
                            }
                        }
                        adjust_node = reference_node->_right;
                        adjust_parent_node = parent_node;
                        delete reference_node;
                        reference_node = nullptr;
                    }
                    else if (reference_node->_right == nullptr)
                    {
                        if(reference_node->_left != nullptr)
                        {
                            reference_node->_left->_parent = parent_node;
                            //链接父节点
                        }
                        if(parent_node == nullptr)
                        {
                            //与上同理
                            _root = reference_node->_left;
                        }
                        else
                        {
                            if(parent_node->_left == reference_node)
                            {
                                parent_node->_left = reference_node->_left;
                            }
                            else
                            {
                                parent_node->_right = reference_node->_left;
                            }
                        }
                        adjust_node = reference_node->_left;
                        adjust_parent_node = parent_node;
                        delete reference_node;
                        reference_node = nullptr;
                    }
                    else if(reference_node->_right != nullptr && reference_node->_left != nullptr)
                    {
                        container_node* right_subtree_smallest_node = reference_node->_right;
                        container_node* smallest_parent_node = reference_node;
                        while(right_subtree_smallest_node->_left != nullptr)
                        {
                            smallest_parent_node = right_subtree_smallest_node;
                            right_subtree_smallest_node = right_subtree_smallest_node->_left;
                        }
                        delete_color = right_subtree_smallest_node->_color;

                        // 交换数据 AND 交换颜色
                        template_container::algorithm::swap(right_subtree_smallest_node->_data,  reference_node->_data);
                        template_container::algorithm::swap(right_subtree_smallest_node->_color, reference_node->_color);

                        // 然后正确地把后继节点的位置接到它父节点上：
                        if (smallest_parent_node->_left == right_subtree_smallest_node) 
                        {
                            smallest_parent_node->_left  = right_subtree_smallest_node->_right;
                        }
                        else 
                        {
                            smallest_parent_node->_right = right_subtree_smallest_node->_right;
                        }
                        if (right_subtree_smallest_node->_right) 
                        {
                            right_subtree_smallest_node->_right->_parent = smallest_parent_node;
                        }
                        adjust_node        = right_subtree_smallest_node->_right;
                        adjust_parent_node = smallest_parent_node;

                        // 最后再 delete 那个后继节点
                        delete right_subtree_smallest_node;
                        right_subtree_smallest_node = nullptr;
                    }
                    //更新颜色
                    if( delete_color == black )
                    {
                        //删除红色节点不影响性质
                        delete_adjust(adjust_node,adjust_parent_node);
                    }
                    if(_root != nullptr)
                    {
                        _root->_color = black;
                    }
                    return return_pair_value(iterator(nullptr),false);
                }
            }
            iterator find(const rb_tree_type_value& val_data)
            {
                if(_root == nullptr)
                {
                    return iterator(nullptr);
                }
                else
                {
                    container_node* root_find_node = _root;
                    while(root_find_node != nullptr)
                    {
                       if(!function_policy(element(root_find_node->_data),element(val_data)))
                       {
                           return iterator(root_find_node);
                       }
                       else if(function_policy(element(root_find_node->_data),element(val_data)))
                       {
                           root_find_node = root_find_node->_right;
                       }
                       else
                       {
                           root_find_node = root_find_node->_left;
                       }
                    }
                    return iterator(nullptr);
                }
            }
            size_t size()
            {
                return _size();
            }
            size_t size() const
            {
                return _size();
            }
            bool empty()
            {
                return _root == nullptr;
            }
            void middle_order_traversal()
            {
                interior_middle_order_traversal(_root);
            }
            void pre_order_traversal()
            {
                interior_pre_order_traversal(_root);
            }
            iterator begin()
            {
                container_node* root_node = _root;
                while(root_node != nullptr &&  root_node->_left != nullptr)
                {
                    root_node = root_node->_left;
                }
                return iterator(root_node);
            }
            iterator end()
            {
                return iterator(nullptr);
            }
            const_iterator cbegin() const
            {
                container_node* croot_node = _root;
                while(croot_node != nullptr &&  croot_node->_left != nullptr)
                {
                    croot_node = croot_node->_left;
                }
                return const_iterator(croot_node);
            }
            const_iterator cend() const
            {
                return const_iterator(nullptr);
            }
            reverse_iterator rbegin()
            {
                container_node* iterator_node = _root;
                while(iterator_node != nullptr && iterator_node->_right != nullptr)
                {
                    iterator_node = iterator_node->_right;
                }
                return reverse_iterator(iterator_node);
            }
            reverse_iterator rend()
            {
                return reverse_iterator(nullptr);
            }
            const_reverse_iterator crbegin() const
            {
                container_node* iterator_node = _root;
                while(iterator_node!= nullptr && iterator_node->_right!= nullptr)
                {
                    iterator_node = iterator_node->_right;
                }
                return const_reverse_iterator(iterator_node);
            }
            const_reverse_iterator crend() const
            {
                return const_reverse_iterator(nullptr);
            }
            iterator operator[](const rb_tree_type_value& rb_tree_data)
            {
                return find(rb_tree_data);
            }
        };
        /*############################     hash 容器     ############################*/
        template <typename hash_table_type_key, typename hash_table_type_value,typename container_imitate_function,
        typename hash_function = std::hash<hash_table_type_value>>
        class hash_table
        {
            class hash_table_node
            {
            public:
                hash_table_type_value _data;
                hash_table_node* _next;
                hash_table_node* overall_list_prev;
                //全局链表指针，方便按照插入的顺序有序遍历哈希表
                hash_table_node* overall_list_next;
                hash_table_node(const hash_table_type_value& hash_table_value_data)
                {
                    _data = hash_table_value_data;
                    _next = nullptr;
                    overall_list_prev = nullptr;
                    overall_list_next = nullptr;
                }
                hash_table_node(hash_table_type_value&& hash_table_value_data)
                {
                    _data = std::move(hash_table_value_data);
                    _next = nullptr;
                    overall_list_prev = nullptr;
                    overall_list_next = nullptr;
                }
            };
            using container_node = hash_table_node;
            container_imitate_function value_imitation_functions;                               //仿函数

            size_t _size;                                                                       //哈希表大小

            size_t load_factor;                                                                 //负载因子   

            size_t hash_capacity;                                                               //哈希表容量

            template_container::vector_container::vector<container_node*> vector_hash_table;    //哈希表

            hash_function hash_function_object;                                                 //哈希函数

            container_node* overall_list_before_node = nullptr;                                 //前一个数据

            container_node* overall_list_head_node = nullptr;                                   //全局头数据

            template <typename iterator_type_key, typename iterator_type_val>
            class hash_iterator
            {
                using iterator_node = container_node;
                using Ref  = iterator_type_val&;
                using Ptr  = iterator_type_val*;
                using self = hash_iterator<iterator_type_key,iterator_type_val>;
                iterator_node* hash_table_iterator_node;
            public:
                hash_iterator(iterator_node* iterator_ptr_node)      {      hash_table_iterator_node = iterator_ptr_node;        }

                Ref operator*()                                      {      return hash_table_iterator_node->_data;      }

                Ptr operator->()                                     {      return &hash_table_iterator_node->_data;     }

                bool operator!=(const self& iterator_data)           {      return hash_table_iterator_node != iterator_data.hash_table_iterator_node;     }

                bool operator==(const self& iterator_data)           {      return hash_table_iterator_node == iterator_data.hash_table_iterator_node;     }

                self operator++(int)                         
                {       
                    self iterator_data = *this;
                    hash_table_iterator_node = hash_table_iterator_node->overall_list_next;
                    return iterator_data;
                }
                self operator++()                                    
                {      
                    hash_table_iterator_node = hash_table_iterator_node->overall_list_next;     
                    return *this;     
                }
                iterator_node* get_node()
                {
                    return hash_table_iterator_node;
                }
            };
            void hash_chain_adjustment(container_node*& provisional_parent_node,container_node*& provisional_node,size_t& hash_map_location)
            {
                if(provisional_parent_node != nullptr)
                {
                    //父亲节点不为空，防止空指针错误
                    provisional_parent_node->_next = provisional_node->_next;
                }
                else
                {
                    //父亲节点为空，直接将映射位置置空
                    vector_hash_table[hash_map_location] = nullptr;
                }
            } 
        public:  
            using iterator = hash_iterator<hash_table_type_key,hash_table_type_value>;
            using const_iterator = hash_iterator<const hash_table_type_key,const hash_table_type_value>;
            hash_table()
            {
                _size = 0;
                load_factor = 7;
                hash_capacity = 10;
                vector_hash_table.resize(hash_capacity);
            }
            hash_table(size_t new_hash_table_capacity)
            {
                _size = 0;
                load_factor = 7;
                hash_capacity = new_hash_table_capacity;
                vector_hash_table.resize(hash_capacity);
            }
            hash_table(const hash_table& hash_table_data)
            : value_imitation_functions(hash_table_data.value_imitation_functions),_size(hash_table_data._size),load_factor(hash_table_data.load_factor),
            hash_capacity(hash_table_data.hash_capacity),value_imitation_functions(hash_table_data.container_imitate_function),overall_list_before_node(nullptr),   
            overall_list_head_node(nullptr)
            {
                if (hash_capacity == 0) 
                {
                    return;
                }
                // 1. 分配同样大小的桶数组，所有桶初始为空
                vector_hash_table.resize(hash_capacity, nullptr);
        
                // 2. 遍历原表的每一个桶
                for (size_t new_hash_container_capacity = 0; new_hash_container_capacity < hash_capacity; ++new_hash_container_capacity) 
                {
                    container_node* src_bucket_node = hash_table_data.vector_hash_table[new_hash_container_capacity];
                    // 桶内新表的尾节点（用于串联 _next）
                    container_node* last_in_bucket = nullptr;
        
                    // 逐节点深拷贝
                    while (src_bucket_node) 
                    {
                        // 2.1 创建新节点并拷贝数据
                        container_node* new_structure_node = new container_node(src_bucket_node->_data);
                        // 2.2 插入到“桶内部”链表
                        if (last_in_bucket != nullptr) 
                        {
                            last_in_bucket->_next = new_structure_node;
                        } 
                        else 
                        {
                            vector_hash_table[new_hash_container_capacity] = new_structure_node;
                        }
                        last_in_bucket = new_structure_node;
        
                        // 2.3 插入到“全局插入
                        if(overall_list_before_node != nullptr)
                        {
                            overall_list_before_node->overall_list_next = new_structure_node;
                            new_structure_node->overall_list_prev = overall_list_before_node;
                        } 
                        else 
                        {
                            // 第一个节点就是全局链表的头
                            overall_list_head_node = new_structure_node;
                        }
                        overall_list_before_node = new_structure_node;
        
                        // 继续下一个源节点
                        src_bucket_node = src_bucket_node->_next;
                    }
                }
                if(overall_list_before_node != nullptr)
                {
                    overall_list_before_node->overall_list_next = nullptr;
                }
            }
            hash_table(hash_table&& hash_table_data) noexcept
            {
                vector_hash_table = std::move(hash_table_data.vector_hash_table);
                _size = std::move(hash_table_data._size);
                load_factor = std::move(hash_table_data.load_factor);
                hash_capacity = std::move(hash_table_data.hash_capacity);
                hash_function_object = std::move(hash_table_data.hash_function_object);
                overall_list_before_node = std::move(hash_table_data.overall_list_before_node);
                overall_list_head_node = std::move(hash_table_data.overall_list_head_node);
                value_imitation_functions = std::move(hash_table_data.value_imitation_functions);
            }
            ~hash_table()
            {
                for(size_t i = 0;i < vector_hash_table.size();++i)
                {
                    container_node* hash_bucket_delete = vector_hash_table[i];
                    while(hash_bucket_delete != nullptr)
                    {
                        container_node* hash_bucket_prev_node = hash_bucket_delete;
                        hash_bucket_delete = hash_bucket_delete->_next;
                        delete hash_bucket_prev_node;
                        hash_bucket_prev_node = nullptr;
                    }
                }
            }
            bool change_load_factor(const size_t& new_load_factor)  //作用：改变负载因子大小
            {
                if(new_load_factor < 1)
                {
                    return false;
                }
                load_factor = new_load_factor;
                return true;
            }
            iterator operator[](const hash_table_type_key& key_value)
            {
                if( _size == 0)
                {
                    return iterator(nullptr);
                }
                else
                {
                    size_t hash_value = value_imitation_functions(key_value);
                    size_t hash_map_location = hash_value % hash_capacity;
                    //找到映射位置
                    container_node* bucket_node = vector_hash_table[hash_map_location];
                    while(bucket_node != nullptr)
                    {
                        if(value_imitation_functions(bucket_node->_data) == value_imitation_functions(key_value))
                        {
                            return iterator(bucket_node);
                        }
                        bucket_node = bucket_node->_next;
                    }
                    return iterator(nullptr);
                }
            }
            iterator begin()                    {   return iterator(overall_list_head_node);        }

            const_iterator cbegin() const       {   return const_iterator(overall_list_head_node);  }

            iterator end()                      {   return iterator(nullptr);           }

            const_iterator cend() const         {   return const_iterator(nullptr);     }

            size_t size()                       {   return _size;                       }

            size_t size() const                 {   return _size;                       }

            bool   empty()                      {   return _size == 0;                  }

            size_t capacity()                   {   return hash_capacity;                    }

            size_t capacity() const             {   return hash_capacity;                    }

            bool push(const hash_table_type_value& hash_table_value_data)
            {
                if( find(hash_table_value_data).get_node() != nullptr)
                {
                    return false;
                }
                //判断扩容
                if( _size * 10 >= hash_capacity * load_factor)
                {
                    //扩容
                    size_t new_container_capacity = (hash_capacity == 0 && vector_hash_table.size() == 0) ? 10 : hash_capacity * 2;
                    //新容量
                    template_container::vector_container::vector<container_node*> new_vector_hash_table;
                    new_vector_hash_table.resize(new_container_capacity,nullptr);
                    size_t new_size = 0;
                    //重新映射,按照插入链表顺序
                    container_node* regional_list_head_node = nullptr;                  //临时新哈希表全局头指针
                    container_node* regional_list_previous_node = nullptr;              //临时新哈希表全局上一个插入数据指针
                    container_node* start_position_node = overall_list_head_node;       //全局链表头指针赋值
                    while( start_position_node != nullptr)
                    {
                        size_t new_mapping_value = hash_function_object(start_position_node->_data) % new_container_capacity;
                        //重新计算映射值
                        container_node* hash_bucket_node = new_vector_hash_table[new_mapping_value];
                        if(hash_bucket_node == nullptr)
                        {
                            container_node* new_mapping_data = new container_node(start_position_node->_data);
                            if(regional_list_head_node == nullptr)
                            {
                                new_mapping_data->overall_list_prev = nullptr;
                                new_mapping_data->overall_list_next = nullptr;
                                regional_list_head_node = regional_list_previous_node =new_mapping_data;
                            }
                            else
                            {
                                new_mapping_data->overall_list_prev = regional_list_previous_node;
                                regional_list_previous_node->overall_list_next = new_mapping_data;
                                regional_list_previous_node = new_mapping_data;
                            }
                            new_vector_hash_table[new_mapping_value] = new_mapping_data;
                            //保存之前的遍历链表信息
                        }
                        else
                        {
                            container_node* new_mapping_data = new container_node(start_position_node->_data);
                            if(regional_list_head_node == nullptr)
                            {
                                new_mapping_data->overall_list_prev = nullptr;
                                regional_list_head_node = regional_list_previous_node =new_mapping_data;
                            }
                            else
                            {
                                new_mapping_data->overall_list_prev = regional_list_previous_node;
                                regional_list_previous_node->overall_list_next = new_mapping_data;
                                regional_list_previous_node = new_mapping_data;
                            }
                            new_mapping_data->_next = hash_bucket_node;
                            new_vector_hash_table[new_mapping_value] = new_mapping_data;
                            //头插节点
                        }
                        ++new_size;
                        start_position_node = start_position_node->overall_list_next;
                    }
                    //释放旧哈希表
                    for(size_t delete_traversal = 0;delete_traversal < vector_hash_table.size(); ++delete_traversal)
                    {
                        container_node* hash_bucket_delete = vector_hash_table[delete_traversal];
                        while(hash_bucket_delete!= nullptr)
                        {
                            container_node* hash_bucket_prev_node = hash_bucket_delete;
                            hash_bucket_delete = hash_bucket_delete->_next;
                            delete hash_bucket_prev_node;
                            hash_bucket_prev_node = nullptr;
                        }
                    }
                    _size = new_size;
                    vector_hash_table.swap(new_vector_hash_table);
                    hash_capacity = new_container_capacity;
                    overall_list_head_node = regional_list_head_node;
                    overall_list_before_node = regional_list_previous_node;
                    //重新映射,按照插入链表顺序
                }
                size_t hash_mapping_value = hash_function_object(hash_table_value_data);
                size_t hash_map_location = hash_mapping_value % hash_capacity;
                //找到映射位置
                container_node* hash_bucket_node = vector_hash_table[hash_map_location];

                container_node* new_mapping_data = new container_node(hash_table_value_data);
                new_mapping_data->_next = hash_bucket_node;
                vector_hash_table[hash_map_location] = new_mapping_data;
                if(_size == 0 && overall_list_head_node == nullptr)
                {
                    new_mapping_data->overall_list_prev = nullptr;
                    overall_list_head_node = overall_list_before_node = new_mapping_data;
                }
                else
                {
                    new_mapping_data->overall_list_prev = overall_list_before_node;
                    overall_list_before_node->overall_list_next = new_mapping_data;
                    overall_list_before_node = new_mapping_data;
                }
                _size++;
                return true;
            }
            bool push(hash_table_type_value&& hash_table_value_data) noexcept
            {
                if( find(hash_table_value_data).hash_table_iterator_node != nullptr)
                {
                    return false;
                }
                //判断扩容
                if( _size * 10 >= hash_capacity * load_factor)
                {
                    //扩容
                    size_t new_container_capacity = (hash_capacity == 0 && vector_hash_table.size() == 0) ? 10 : hash_capacity * 2;
                    //新容量
                    template_container::vector_container::vector<container_node*> new_vector_hash_table;
                    new_vector_hash_table.resize(new_container_capacity,nullptr);
                    size_t new_size = 0;
                    //重新映射,按照插入链表顺序
                    container_node* regional_list_head_node = nullptr;                  //临时新哈希表全局头指针
                    container_node* regional_list_previous_node = nullptr;              //临时新哈希表全局上一个插入数据指针
                    container_node* start_position_node = overall_list_head_node;       //全局链表头指针赋值
                    while( start_position_node != nullptr)
                    {
                        size_t new_mapping_value = hash_function_object(start_position_node->_data) % new_container_capacity;
                        //重新计算映射值
                        container_node* hash_bucket_node = new_vector_hash_table[new_mapping_value];
                        if(hash_bucket_node == nullptr)
                        {
                            container_node* new_mapping_data = new container_node(std::forward<hash_table_type_value>(start_position_node->_data));
                            if(regional_list_head_node == nullptr)
                            {
                                new_mapping_data->overall_list_prev = nullptr;
                                new_mapping_data->overall_list_next = nullptr;
                                regional_list_head_node = regional_list_previous_node =new_mapping_data;
                            }
                            else
                            {
                                new_mapping_data->overall_list_prev = regional_list_previous_node;
                                regional_list_previous_node->overall_list_next = new_mapping_data;
                                regional_list_previous_node = new_mapping_data;
                            }
                            new_vector_hash_table[new_mapping_value] = new_mapping_data;
                            //保存之前的遍历链表信息
                        }
                        else
                        {
                            container_node* new_mapping_data = new container_node(std::forward<hash_table_type_value>(start_position_node->_data));
                            if(regional_list_head_node == nullptr)
                            {
                                new_mapping_data->overall_list_prev = nullptr;
                                regional_list_head_node = regional_list_previous_node =new_mapping_data;
                            }
                            else
                            {
                                new_mapping_data->overall_list_prev = regional_list_previous_node;
                                regional_list_previous_node->overall_list_next = new_mapping_data;
                                regional_list_previous_node = new_mapping_data;
                            }
                            new_mapping_data->_next = hash_bucket_node;
                            new_vector_hash_table[new_mapping_value] = new_mapping_data;
                            //头插节点
                        }
                        ++new_size;
                        start_position_node = start_position_node->overall_list_next;
                    }
                    //释放旧哈希表
                    for(size_t delete_traversal = 0;delete_traversal < vector_hash_table.size(); ++delete_traversal)
                    {
                        container_node* hash_bucket_delete = vector_hash_table[delete_traversal];
                        while(hash_bucket_delete!= nullptr)
                        {
                            container_node* hash_bucket_prev_node = hash_bucket_delete;
                            hash_bucket_delete = hash_bucket_delete->_next;
                            delete hash_bucket_prev_node;
                            hash_bucket_prev_node = nullptr;
                        }
                    }
                    _size = new_size;
                    vector_hash_table.swap(new_vector_hash_table);
                    hash_capacity = new_container_capacity;
                    overall_list_head_node = regional_list_head_node;
                    overall_list_before_node = regional_list_previous_node;
                    //重新映射,按照插入链表顺序
                }
                size_t hash_mapping_value = hash_function_object(hash_table_value_data);
                size_t hash_map_location = hash_mapping_value % hash_capacity;
                //找到映射位置
                container_node* hash_bucket_node = vector_hash_table[hash_map_location];

                container_node* new_mapping_data = new container_node(std::forward<hash_table_type_value>(hash_table_value_data));
                new_mapping_data->_next = hash_bucket_node;
                vector_hash_table[hash_map_location] = new_mapping_data;
                if(_size == 0 && overall_list_head_node == nullptr)
                {
                    new_mapping_data->overall_list_prev = nullptr;
                    overall_list_head_node = overall_list_before_node = new_mapping_data;
                }
                else
                {
                    new_mapping_data->overall_list_prev = overall_list_before_node;
                    overall_list_before_node->overall_list_next = new_mapping_data;
                    overall_list_before_node = new_mapping_data;
                }
                _size++;
                return true;
            }
            bool pop(const hash_table_type_value& hash_table_value_data)
            {
                //空表判断
                if( find(hash_table_value_data).get_node() == nullptr)
                {
                    return false;
                }
                size_t hash_mapping_value = hash_function_object(hash_table_value_data);
                size_t hash_map_location = hash_mapping_value % hash_capacity;
                //找到映射位置
                container_node* hash_bucket_node = vector_hash_table[hash_map_location]; //桶头节点赋值
                container_node* hash_bucket_parent_node = nullptr;                       //保存上一个节点方便修改next指针的指向
                while(hash_bucket_node!= nullptr)
                {
                    //找到位置
                    if(value_imitation_functions(hash_bucket_node->_data) == value_imitation_functions(hash_table_value_data))
                    {
                        if(overall_list_head_node == hash_bucket_node)
                        {
                            //头节点删除情况
                            if(hash_bucket_node == overall_list_before_node)
                            {
                                //只有一个节点
                                overall_list_head_node = overall_list_before_node = nullptr;
                                hash_chain_adjustment(hash_bucket_parent_node,hash_bucket_node,hash_map_location);
                            }           //hash_chain_adjustment函数作用：检查hash_bucket_node节点是否哈希桶头结点，是则置空
                            else        //不是则将hash_bucket_node的_next节点赋值给hash_bucket_parent_node的_next指针，因为删除的是hash_bucket_node节点
                            {
                                //是头节点，不是尾节点
                                hash_chain_adjustment(hash_bucket_parent_node,hash_bucket_node,hash_map_location);
                                overall_list_head_node = overall_list_head_node->overall_list_next;
                                overall_list_head_node->overall_list_prev = nullptr;
                            }
                        }
                        else if(hash_bucket_node == overall_list_before_node)
                        {
                            //尾节点删除情况
                            hash_chain_adjustment(hash_bucket_parent_node,hash_bucket_node,hash_map_location);
                            overall_list_before_node = overall_list_before_node->overall_list_prev;
                            overall_list_before_node->overall_list_next = nullptr;
                        }
                        else
                        {
                            //中间节点删除情况
                            hash_chain_adjustment(hash_bucket_parent_node,hash_bucket_node,hash_map_location);
                            hash_bucket_node->overall_list_prev->overall_list_next = hash_bucket_node->overall_list_next;
                            hash_bucket_node->overall_list_next->overall_list_prev = hash_bucket_node->overall_list_prev;
                        }
                        delete hash_bucket_node;
                        hash_bucket_node = nullptr;
                        --_size;
                        return true;
                    }
                    hash_bucket_parent_node = hash_bucket_node;
                    hash_bucket_node = hash_bucket_node->_next;
                    //向下遍历
                }
                return false;
            }
            iterator find(const hash_table_type_value& hash_table_value_data)
            {
                if( _size == 0)
                {
                    return iterator(nullptr);
                }
                else
                {
                    size_t hash_mapping_value = hash_function_object(hash_table_value_data);
                    size_t hash_map_location = hash_mapping_value % hash_capacity;
                    //找到映射位置
                    container_node* hash_bucket_node = vector_hash_table[hash_map_location];
                    while(hash_bucket_node != nullptr)
                    {
                        if(value_imitation_functions(hash_bucket_node->_data) == value_imitation_functions(hash_table_value_data))
                        {
                            return iterator(hash_bucket_node);
                        }
                        hash_bucket_node = hash_bucket_node->_next;
                    }
                    return iterator(nullptr);
                }
            }                             
        };
        /*############################     bit_set 容器     ############################*/
        class bit_set
        {
            template_container::vector_container::vector<int> vector_bit_set;
            size_t _size;
        public:
            bit_set() {  ;  }
            bit_set(const size_t& new_capacity)
            {
                _size = 0;
                vector_bit_set.resize((new_capacity / 32) + 1,0);
                //多开一个int的空间，防止不够
            }
            void resize(const size_t& new_capacity)
            {
                _size = 0;
                vector_bit_set.resize((new_capacity / 32) + 1,0);
            }
            bit_set(const bit_set& bit_set_data)
            {
                vector_bit_set = bit_set_data.vector_bit_set;
                _size = bit_set_data._size;
            }
            bit_set& operator=(const bit_set& bit_set_data)
            {
                if(this != &bit_set_data)
                {
                    vector_bit_set = bit_set_data.vector_bit_set;
                    _size = bit_set_data._size;
                }
                return *this;
            }
            void set(const size_t& value_data)
            {
                //把数映射到BitSet上的函数
                size_t mapping_bit = value_data / 32; //定位到BitSet的位置在哪个int上
                size_t value_bit = value_data % 32; //定位到BitSet的位置在哪个int上的第几位
                vector_bit_set[mapping_bit] = vector_bit_set[mapping_bit] | (1 << value_bit);
                //比较当前位置是否为1，若为1则不需要改变，若为0则需要改变，注意|只改变当前位不会改变其他位
                //|是两个条件满足一个条件就行，&是两个条件都满足才行
                //其他位如果是1那么就还是1，如果是0那么就还是0，因为|是两个条件满足一个条件就行
                _size++;
            }
            void reset(const size_t& value_data)
            {
                //删除映射的位置的函数
                size_t mapping_bit = value_data / 32;
                size_t value_bit = value_data % 32;
                vector_bit_set[mapping_bit] = vector_bit_set[mapping_bit] & (~(1 << value_bit));
                //&是两个条件都满足，~是取反，^是两个条件不同时满足
                //1取反关键位是0其他位是1，这样就成功与掉，&要求是两个条件都需要满足
                //其他位如果是1那么就不会改变原来的，如果是0那么还是为0，因为与是两个条件都需要满足
                _size--;
            }
            size_t size()const           {   return _size;    }
            bool test(const size_t& value_data)
            {
                if(_size == 0)
                {
                    return false;
                }
                size_t mapping_bit = value_data / 32;
                size_t value_bit = value_data % 32;
                bool return_bit_set = vector_bit_set[mapping_bit] & (1 << value_bit);
                //如果_BitSet[mapping_bit]里对应的位是1那么就返回true，否则返回false
                return return_bit_set;
            }
        };
    }
    /*############################     tree_map 容器     ############################*/
    namespace map_container
    {
        template <typename map_type_k,typename map_type_v,typename comparators = template_container::imitation_functions::less<map_type_k>>
        class tree_map
        {
            using key_val_type = template_container::practicality::pair<map_type_k,map_type_v>;
            struct key_val
            {
                const map_type_k& operator()(const key_val_type& key_value)
                {
                    return key_value.first;
                }
            };
            using instance_rb = base_class_container::rb_tree <map_type_k,key_val_type,key_val,comparators>;
            instance_rb instance_tree_map;
        public:
            using iterator = typename instance_rb::iterator;
            using const_iterator = typename instance_rb::const_iterator;
            using reverse_iterator = typename instance_rb::reverse_iterator;
            using const_reverse_iterator = typename instance_rb::const_reverse_iterator;
            
            using map_iterator = template_container::practicality::pair<iterator,bool>;
            ~tree_map()
            {
                instance_tree_map.~rb_tree();
            }
            tree_map& operator=(const tree_map& tree_map_data)
            {
                if(this != &tree_map_data)
                {
                    instance_tree_map = tree_map_data.instance_tree_map;
                }
                return *this;
            }
            tree_map& operator=(tree_map&& tree_map_data) noexcept
            {
                if(this != &tree_map_data)
                {
                    instance_tree_map = std::move(tree_map_data.instance_tree_map);
                }
                return *this;
            }
            map_iterator push(key_val_type&& tree_map_data) noexcept    
            {  
                return instance_tree_map.push(tree_map_data);                   
            }
            tree_map& operator= (std::initializer_list<key_val_type> lightweight_container)
            {
                for(auto& chained_values : lightweight_container)
                {
                    instance_tree_map.push(std::move(chained_values));
                }
                return *this;
            }
            tree_map(const std::initializer_list<key_val_type>& lightweight_container)
            {
                for(auto& chained_values : lightweight_container)
                {
                    instance_tree_map.push(std::move(chained_values));
                }
            }
            tree_map()                                               {  ;                                   }

            tree_map(const tree_map& tree_map_data)                  {  instance_tree_map = tree_map_data.instance_tree_map;            }

            tree_map(tree_map&& tree_map_data) noexcept              {  instance_tree_map = std::move(tree_map_data.instance_tree_map); }

            tree_map(const key_val_type& tree_map_data)              {  instance_tree_map.push(tree_map_data);                          }

            map_iterator push(const key_val_type& tree_map_data)     {  return instance_tree_map.push(tree_map_data);                   }

            map_iterator pop(const key_val_type& tree_map_data)      {  return instance_tree_map.pop(tree_map_data);                    }

            iterator find(const key_val_type& tree_map_data)         {  return instance_tree_map.find(tree_map_data);                   }

            void middle_order_traversal()                            {  instance_tree_map.middle_order_traversal();                     }

            void pre_order_traversal()                               {  instance_tree_map.pre_order_traversal();                        }

            size_t size() const                                      {  return instance_tree_map.size();                                }

            bool empty()                                             {  return instance_tree_map.empty();                               }

            iterator begin()                                         {  return instance_tree_map.begin();                               }

            iterator end()                                           {  return instance_tree_map.end();                                 }

            const_iterator cbegin()                                  {  return instance_tree_map.cbegin();                              }

            const_iterator cend()                                    {  return instance_tree_map.cend();                                }

            reverse_iterator rbegin()                                {  return instance_tree_map.rbegin();                              }
 
            reverse_iterator rend()                                  {  return instance_tree_map.rend();                                }
 
            const_reverse_iterator crbegin()                         {  return instance_tree_map.crbegin();                             }

            const_reverse_iterator crend()                           {  return instance_tree_map.crend();                               }

            iterator operator[](const key_val_type& tree_map_data)   {  return instance_tree_map[tree_map_data];                        }

        };
        template <typename hash_map_type_key,typename hash_map_type_value,
        typename first_external_hash_functions = template_container::imitation_functions::hash_imitation_functions,
        typename second_external_hash_functions = template_container::imitation_functions::hash_imitation_functions> //两个对应的hash函数
        class hash_map
        {
            using key_val_type = template_container::practicality::pair<hash_map_type_key,hash_map_type_value>;
            struct key_val
            {
                const hash_map_type_key& operator()(const key_val_type& key_value)
                {
                    return key_value.first;
                }
            };
            class inbuilt_map_hash_functor
            {
            private:
                first_external_hash_functions  first_hash_functions_object;
                second_external_hash_functions second_hash_functions_object;
            public:
                size_t operator()(const key_val_type& key_value) noexcept
                {
                    size_t first_hash_value  =  first_hash_functions_object(key_value.first); 
                    first_hash_value = first_hash_value * 31;
                    size_t second_hash_value =  second_hash_functions_object(key_value.second);
                    second_hash_value = second_hash_value * 31;
                    return (first_hash_value + second_hash_value);
                }
            };
            using hash_table = base_class_container::hash_table<hash_map_type_key,key_val_type,key_val,inbuilt_map_hash_functor>;
            hash_table instance_hash_map;
        public:
            using iterator = typename hash_table::iterator;
            using const_iterator = typename hash_table::const_iterator; //单向迭代器
            hash_map()                                              {   ;                                         }  

            ~hash_map()                                             {  instance_hash_map.~hash_table();           }

            hash_map(const key_val_type& key_value)                 {  instance_hash_map.push(key_value);         }

            hash_map(const hash_map& hash_map_data)                 {  instance_hash_map = hash_map_data.instance_hash_map;  }

            hash_map(hash_map&& hash_map_data) noexcept             {  instance_hash_map = std::move(hash_map_data.instance_hash_map);  }

            bool push(const key_val_type& key_value)                {  return instance_hash_map.push(key_value);  }

            bool pop(const key_val_type& key_value)                 {  return instance_hash_map.pop(key_value);     }

            iterator find(const key_val_type& key_value)            {  return instance_hash_map.find(key_value);    }

            size_t size()                                           {  return instance_hash_map.size();           }

            size_t size() const                                     {  return instance_hash_map.size();           }

            size_t capacity() const                                 {  return instance_hash_map.capacity();       } 

            bool empty()                                            {  return instance_hash_map.empty();          }

            iterator begin()                                        {  return instance_hash_map.begin();          }

            iterator end()                                          {  return instance_hash_map.end();            }

            const_iterator cbegin()                                 {  return instance_hash_map.cbegin();         }

            const_iterator cend()                                   {  return instance_hash_map.cend();           }

            iterator operator[](const key_val_type& key_value)      {  return instance_hash_map[key_value];       }

            hash_map(const std::initializer_list<key_val_type>& lightweight_container)
            {
                for(auto& chained_values : lightweight_container)
                {
                    instance_hash_map.push(std::move(chained_values));
                }
            }
            hash_map& operator=(const std::initializer_list<key_val_type>& lightweight_container)
            {
                for(auto& chained_values : lightweight_container)
                {
                    instance_hash_map.push(std::move(chained_values));
                }
                return *this;
            }
            hash_map& operator=(hash_map&& hash_map_data) noexcept
            {
                if(this!= &hash_map_data)
                {
                    instance_hash_map = std::forward<hash_table>(hash_map_data.instance_hash_map);
                }
            }
            bool push(key_val_type&& key_value) noexcept                 
            {  
                return instance_hash_map.push(std::forward<key_val_type>(key_value)); 
            }
            hash_map& operator=(const hash_map& hash_map_data)
            {
                if(this!= &hash_map_data)
                {
                    instance_hash_map = hash_map_data.instance_hash_map;
                }
                return *this;
            }
        };
    }
    /*############################     tree_set 容器     ############################*/
    namespace set_container
    {
        template <typename set_type,typename comparators = template_container::imitation_functions::less<set_type>>
        class tree_set
        {
            using key_val_type = set_type;           //comparators 用户自定义比较器，用于比较两个元素的大小，方便存储
            struct key_val
            {
                const set_type& operator()(const key_val_type& key_value)
                {
                    return key_value;
                }
            };
            using instance_rb = base_class_container::rb_tree<set_type,key_val_type,key_val,comparators>;
            instance_rb instance_tree_set;
        public:
            using iterator = typename instance_rb::iterator;
            using const_iterator = typename instance_rb::const_iterator;
            using reverse_iterator = typename instance_rb::reverse_iterator;
            using const_reverse_iterator = typename instance_rb::const_reverse_iterator;
            
            using set_iterator = template_container::practicality::pair<iterator,bool>;
            tree_set& operator=(const tree_set& set_data)         
            {  
                if(this!= &set_data)                     
                {  
                    instance_tree_set = set_data.instance_tree_set;      
                }  
                return *this; 
            }
            tree_set& operator=(tree_set&& set_data) noexcept
            {
                if(this!= &set_data)                     
                {  
                    instance_tree_set = std::move(set_data.instance_tree_set);
                }
                return *this;
            }
            tree_set(std::initializer_list<key_val_type> lightweight_container)
            {
                for(auto& chained_values : lightweight_container)
                {
                    instance_tree_set.push(std::move(chained_values));
                }
            }
            tree_set& operator= (std::initializer_list<key_val_type> lightweight_container)
            {
                for(auto& chained_values : lightweight_container)
                {
                    instance_tree_set.push(std::move(chained_values));
                }
                return *this;
            }
            set_iterator push(key_val_type&& set_data) noexcept
            {
                return instance_tree_set.push(std::forward<key_val_type>(set_data));
            }

            tree_set()                                               {  ;                                                 }

            ~tree_set()                                              {  instance_tree_set.~rb_tree();                     }

            tree_set(const tree_set& set_data)                       {  instance_tree_set = set_data.instance_tree_set;             }

            tree_set(tree_set&& set_data) noexcept                   {  instance_tree_set=std::move(set_data.instance_tree_set);    }

            tree_set(const key_val_type& set_type_data)              {  instance_tree_set.push(set_type_data);                 }

            set_iterator push(const key_val_type& set_type_data)     {  return instance_tree_set.push(set_type_data);          }

            set_iterator pop(const key_val_type& set_type_data)      {  return instance_tree_set.pop(set_type_data);           }

            iterator find(const key_val_type& set_type_data)         {  return instance_tree_set.find(set_type_data);          }

            void middle_order_traversal()                            {  instance_tree_set.middle_order_traversal();      }    

            void pre_order_traversal()                               {  instance_tree_set.pre_order_traversal();         }  

            size_t size() const                                      {  return instance_tree_set.size();                 }

            bool empty()                                             {  return instance_tree_set.empty();                }  

            iterator begin()                                         {  return instance_tree_set.begin();                }

            iterator end()                                           {  return instance_tree_set.end();                  }

            const_iterator cbegin()                                  {  return instance_tree_set.cbegin();               }

            const_iterator cend()                                    {  return instance_tree_set.cend();                 }

            reverse_iterator rbegin()                                {  return instance_tree_set.rbegin();               }

            reverse_iterator rend()                                  {  return instance_tree_set.rend();                 }

            const_reverse_iterator crbegin()                         {  return instance_tree_set.crbegin();              }

            const_reverse_iterator crend()                           {  return instance_tree_set.crend();                }

            iterator operator[](const key_val_type& set_type_data)   {  return instance_tree_set[set_type_data];         }
        };
        template <typename set_type_val,typename external_hash_functions = template_container::imitation_functions::hash_imitation_functions>
        class hash_set
        {
            using key_val_type = set_type_val;
            class inbuilt_set_hash_functor
            {
            private:
                external_hash_functions hash_functions_object;
            public:
                size_t operator()(const key_val_type& key_value)
                {
                    return hash_functions_object(key_value)* 131;
                }
            };
            class key_val
            {
            public:
                const key_val_type& operator()(const key_val_type& key_value)
                {
                    return key_value;
                }
            };
            using hash_table = template_container::base_class_container::hash_table<set_type_val,key_val_type,key_val,inbuilt_set_hash_functor>;
            hash_table instance_hash_set;
        public:
            using iterator = typename hash_table::iterator;
            using const_iterator = typename hash_table::const_iterator;
            hash_set()                                                  {  ;                                                }

            hash_set(const set_type_val& set_type_data)                 {  instance_hash_set.push(set_type_data);           }

            hash_set(const hash_set& hash_set_data)                     {  instance_hash_set = hash_set_data.instance_hash_set;  }

            ~hash_set()                                                 {   instance_hash_set.~hash_table();                }

            bool push(const key_val_type& set_type_data)                {  return instance_hash_set.push(set_type_data);    }

            bool pop(const key_val_type& set_type_data)                 {  return instance_hash_set.pop(set_type_data);     }     

            iterator find(const key_val_type& set_type_data)            {  return instance_hash_set.find(set_type_data);    }

            size_t size()                                               {  return instance_hash_set.size();                 }

            bool empty()                                                {  return instance_hash_set.empty();                }

            size_t capacity()                                           {  return instance_hash_set.capacity();             }

            size_t size() const                                         {  return instance_hash_set.size();                 }

            size_t capacity() const                                     {  return instance_hash_set.capacity();             }

            iterator begin()                                            {  return instance_hash_set.begin();                }

            iterator end()                                              {  return instance_hash_set.end();                  }

            const_iterator cbegin()                                     {  return instance_hash_set.cbegin();               }

            const_iterator cend()                                       {  return instance_hash_set.cend();                 }

            iterator operator[](const key_val_type& set_type_data)      {  return instance_hash_set[set_type_data];         }

            hash_set(set_type_val&& set_type_data) noexcept             
            {  
                instance_hash_set.push(std::forward<set_type_val>(set_type_data));  
            }
            bool push(set_type_val&& set_type_data) noexcept
            {
                return instance_hash_set.push(std::forward<set_type_val>(set_type_data));
            }
            hash_set(std::initializer_list<key_val_type> lightweight_container)
            {
                for(auto& chained_values : lightweight_container)
                {
                    instance_hash_set.push(std::move(chained_values));
                }
            }
            hash_set& operator=(const std::initializer_list<key_val_type>& lightweight_container)
            {
                for(auto& chained_values : lightweight_container)
                {
                    instance_hash_set.push(std::move(chained_values));
                }
                return *this;
            }
            hash_set& operator=(const hash_set& hash_set_data)
            {
                instance_hash_set = hash_set_data.instance_hash_set;
                return *this;
            }
            hash_set& operator=(hash_set&& hash_set_data) noexcept
            {
                instance_hash_set = std::move(hash_set_data.instance_hash_set);
                return *this;
            }
        };
    }
    /*############################     bloom_filter 容器     ############################*/
    namespace bloom_filter_container
    {
        template <typename bloom_filter_type_value,typename bloom_filter_hash_functor = template_container::algorithm::hash_algorithm::hash_function<bloom_filter_type_value>>
        class bloom_filter
        {
            bloom_filter_hash_functor   hash_functions_object;
            using bit_set = template_container::base_class_container::bit_set;
            bit_set instance_bit_set;
            size_t _capacity;
        public:
            bloom_filter()
            {
                _capacity = 1000;
                instance_bit_set.resize(_capacity);
            }
            bloom_filter(const size_t& Temp_Capacity)
            {
                _capacity = Temp_Capacity;
                instance_bit_set.resize(_capacity);
            }
            size_t size()
            {
                return instance_bit_set.size();
            }
            size_t capacity()
            {
                return _capacity;
            }
            bool test(const bloom_filter_type_value& TempVal)
            {
                size_t primary_mapping_location   = hash_functions_object.hash_sdmmhash(TempVal) % _capacity;
                size_t secondary_mapping_location = hash_functions_object.hash_djbhash (TempVal) % _capacity;
                size_t tertiary_mapping_location  = hash_functions_object.hash_pjwhash (TempVal) % _capacity;
                if(instance_bit_set.test(primary_mapping_location) == true && instance_bit_set.test(secondary_mapping_location) == true && 
                instance_bit_set.test(tertiary_mapping_location) == true)
                {
                    return true;
                    /* 有一个为0就返回false */
                }
                return false;
            }
            void set(const bloom_filter_type_value& TempVal)
            {
                size_t primary_mapping_location   = hash_functions_object.hash_sdmmhash(TempVal) % _capacity;
                size_t secondary_mapping_location = hash_functions_object.hash_djbhash (TempVal) % _capacity;
                size_t tertiary_mapping_location  = hash_functions_object.hash_pjwhash (TempVal) % _capacity;
                instance_bit_set.set(primary_mapping_location);
                instance_bit_set.set(secondary_mapping_location);
                instance_bit_set.set(tertiary_mapping_location);
            }
            //布隆过滤器只支持插入和查找，不支持删除
        };
    }
}
namespace con
{
    using template_container::string_container::string;
    using template_container::vector_container::vector;
    using template_container::list_container::list;
    using template_container::stack_adapter::stack;
    using template_container::queue_adapter::queue;
    using template_container::queue_adapter::priority_queue;
    using template_container::base_class_container::rb_tree;
    using template_container::base_class_container::hash_table;
    using template_container::map_container::tree_map;
    using template_container::map_container::hash_map;
    using template_container::set_container::tree_set;
    using template_container::set_container::hash_set;
    using template_container::base_class_container::bit_set;
    using template_container::bloom_filter_container::bloom_filter;
    using template_container::practicality::pair;
    using template_container::practicality::make_pair;
    using template_container::algorithm::copy;
    using template_container::algorithm::find;
    using template_container::algorithm::swap;
    using smart_pointer::smart_ptr;
    using smart_pointer::unique_ptr;
    using smart_pointer::shared_ptr;
    using smart_pointer::weak_ptr;
}