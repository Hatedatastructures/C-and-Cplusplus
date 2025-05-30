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
            message = message_target;
            function_name = function_name_target;
            line_number = line_number_target;
        }
        virtual const char* what() const noexcept override
        {
            return message;
        }
        const char* function_name_get() const noexcept
        {
            return function_name;
        }
        size_t line_number_get() const noexcept
        {
            return line_number;
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
        class Less
        {
        public:
            bool operator()(const imitation_functions_less& _test1 ,const imitation_functions_less& _test2) noexcept
            {
                return _test1 < _test2;
            }
        };
        template<typename imitation_functions_greater>
        class Greater
        {
        public:
            bool operator()(const imitation_functions_greater& _test1 ,const imitation_functions_greater& _test2) noexcept
            {
                return _test1 > _test2;
            }
        };
        class hash_imitation_functions
        {
        public:
            size_t operator()(const int str_data) noexcept                              {       return str_data;                }
            size_t operator()(const size_t DataNum) noexcept                            {       return DataNum;                }
            size_t operator()(const char DataChar) noexcept                             {       return DataChar;               }
            size_t operator()(const double DataDouble) noexcept                         {       return DataDouble;             }
            size_t operator()(const float DataFloat) noexcept                           {       return DataFloat;              }
            size_t operator()(const long DataLong) noexcept                             {       return DataLong;               }
            size_t operator()(const short DataShort) noexcept                           {       return DataShort;              }
            size_t operator()(const long long DataLongLong) noexcept                    {       return DataLongLong;           }
            size_t operator()(const unsigned int DataUnsigned) noexcept                 {       return DataUnsigned;           }
            size_t operator()(const unsigned long DataUnsignedLong) noexcept            {       return DataUnsignedLong;       }
            size_t operator()(const unsigned short DataUnsignedShort) noexcept          {       return DataUnsignedShort;      }
            
  
            // size_t operator()(const MY_Template::string_c::string& data_string)
            // {
            //     size_t hash_value = 0;
            //     for(size_t i = 0; i < data_string._size; ++i)
            //     {
            //         hash_value = hash_value * 31 + data_string._data[i];
            //     }
            //     return hash_value;
            // }
            //有需要可以重载本文件的string容器和vector容器.list容器等计算哈希的函数
        };
    }
    namespace algorithm
    {
        template <typename source_sequence_copy,typename target_sequence_copy>
        target_sequence_copy copy(source_sequence_copy begin,source_sequence_copy end,target_sequence_copy first) noexcept
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
        source_sequence_find find(source_sequence_find begin,source_sequence_find end,const target_sequence_find& value) noexcept
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
        void swap(swap_data_type& a,swap_data_type& b) noexcept
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
                size_t Hash_SDBMHash(const hash_algorithm_type& data_hash) noexcept
                {
                    size_t return_value = hash_imitation_functions_object(data_hash);
                    return_value = 65599 * return_value;
                    return return_value;
                }
                size_t Hash_BKDRHash(const hash_algorithm_type& data_hash) noexcept
                {
                    size_t return_value = hash_imitation_functions_object(data_hash);
                    return_value = 131 * return_value;
                    return return_value;
                }
                size_t Hash_DJBHash(const hash_algorithm_type& data_hash) noexcept
                {
                    size_t return_value = hash_imitation_functions_object(data_hash);
                    return_value = 33 * return_value;
                    return return_value;
                }
                size_t Hash_APHash(const hash_algorithm_type& data_hash) noexcept
                {
                    size_t return_value = hash_imitation_functions_object(data_hash);
                    return_value = return_value * 1031;
                    return return_value;
                }
                size_t Hash_PJWHash(const hash_algorithm_type& data_hash) noexcept
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

            pair(const T& _First,const K& _Second) noexcept
            {
                first  = _First;
                second = _Second;
            }
            pair(const pair& other) noexcept
            {
                first  = other.first;
                second = other.second;
            }

            pair(T&& _First,K&& _Second) noexcept
            {
                first  = std::move(_First);
                second = std::move(_Second);
            }
            pair(pair&& other) noexcept
            {
                first  = std::move(other.first);
                second = std::move(other.second);
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
        pair<make_pair_t,make_pair_k> make_pair (const make_pair_t& _First,const make_pair_k& _Second)
        {
            return pair<make_pair_t,make_pair_k>(_First,_Second);
        }
    }

    /*############################     string容器     ############################*/
    namespace string_c
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
            static const size_t nops = -1;
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
                    return *this; 
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
                    return *this;                
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
                    return *this;
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
                    return *this;
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
                    std::cerr << new_charptr_abnormal.what() << std::endl;;
                }
                return _data;
                //返回首地址迭代器
            }
            string& swap(string& str_data)
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
                    return *this;
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
                    return *this;
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
                for(string::const_iterator start_position = cbegin();start_position != cend();start_position++)
                {
                    std::cout << *start_position;
                }
                std::cout << std::endl;
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
                }
                return *this;
            } 
            string& operator=(string&& str_data) noexcept
            {
                if(this != &str_data)
                {
                    delete [] _data;
                    _size = std::move(str_data._size);
                    _capacity = std::move(str_data._capacity);
                    _data = std::move(str_data._data);
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
                for(size_t i = 0;i < _size;i++)
                {
                    if(_data[i]!= str_data._data[i])
                    {
                        return false;
                    }
                }
                return true;
            }
            bool operator<(const string& str_data) const noexcept
            {
                size_t min_len = _size < str_data._size ? _size : str_data._size;
                for(size_t i = 0;i < min_len;i++)
                {
                    if(_data[i]!= str_data._data[i])
                    {
                        return _data[i] < str_data._data[i];
                    }
                }
                return _size < str_data._size;
            }
            bool operator>(const string& str_data) const noexcept
            {
                size_t min_len = _size < str_data._size? _size : str_data._size;
                for(size_t i = 0;i < min_len;i++)
                {
                    if(_data[i]!= str_data._data[i])
                    {
                        return _data[i] > str_data._data[i];
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
                    return _data[0];
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
                    return _data[0];
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
        std::ostream& operator<<(std::ostream& string_ostream,const string &str_data) 
        {
            for(template_container::string_c::string::const_iterator start_position = str_data.cbegin();start_position != str_data.cend();start_position++)
            {
                string_ostream << *start_position;
            }
            return string_ostream;
        }
    }
    /*############################     vector容器     ############################*/
    namespace vector_c
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
                for(size_t i = 0;i < container_capacity;i++)
                {
                    _data_pointer[i] = vector_data;
                }
            }
            vector(std::initializer_list<vector_type> lightweight_container)
            :_data_pointer(new vector_type[lightweight_container.size()]),_size_pointer(_data_pointer + lightweight_container.size())
            ,_capacity_pointer(_data_pointer + lightweight_container.size())
            {
                //链式拷贝
                size_t i = 0;
                for(auto& chained_values:lightweight_container)
                {
                    _data_pointer[i] = std::move(chained_values);
                    i++;
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
                    return _data_pointer[0];
                }
            }
            vector<vector_type>& size_adjust(const size_t& data_size , const vector_type& padding_temp_data = vector_type())
            {
                size_t container_size = size();
                size_t container_capacity  = capacity();
                if(data_size > container_capacity)
                {
                    resize(data_size);
                    for(size_t i = container_capacity; i < data_size ; i++)
                    {
                        _data_pointer[i] = padding_temp_data;
                    }
                }
                else
                {
                    if(data_size > container_size)
                    {
                        for(size_t i = container_size; i < data_size ; i++)
                        {
                            _data_pointer[i] = padding_temp_data;
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
                for(size_t i = 0; i < vector_data.size();i++)
                {
                    _data_pointer[i] = vector_data._data_pointer[i];
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
                        for (size_t i = 0; i < original_size; i++) 
                        {
                            new_vector_type_array[i] = std::move(_data_pointer[i]);
                        }
                        for(size_t i = original_size; i < new_container_capacity; i++)
                        {
                            new_vector_type_array[i] = vector_data;
                        }
                        delete [] _data_pointer;
                        _data_pointer = new_vector_type_array;
                        _size_pointer = _data_pointer + original_size;  // 使用 original_size 来重建 _size_pointer
                        _capacity_pointer = _data_pointer + new_container_capacity;
                    }
                }
                catch(const std::bad_alloc& process)
                {
                    std::cerr << process.what() << std::endl;
                    delete [] _data_pointer;
                    _data_pointer = _size_pointer = _capacity_pointer = nullptr;
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
                    for(size_t i = 1;i<size();i++)
                    {
                        _data_pointer[i-1] = _data_pointer[i];
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
                    return _data_pointer[0];
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
                    return _data_pointer[0];
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
                for(size_t i = container_size ; i < (vector_data_size + container_size); i++)
                {
                    _data_pointer[i] = vector_data._data_pointer[array_counter++];
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
            for(size_t i = 0; i < dynamic_arrays_data.size(); i++)
            {
                vector_ostream << dynamic_arrays_data[i] << " ";
            }
            return vector_ostream;
        }
    }

    /*############################     list容器     ############################*/
    namespace list_c
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

                list_container_node(const list_type_function_node& list_type_data = list_type_function_node()) noexcept
                :_prev(nullptr), _next(nullptr), _data(list_type_data)
                {
                    //列表初始化
                }
                list_container_node(const list_type_function_node&& data) noexcept
                :_prev(nullptr), _next(nullptr)
                {
                    _data = std::move(data);
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
                    list_iterator temp(_node);
                    _node = _node->_next;
                    //把本体指向下一个位置
                    return temp;
                }
                list_iterator& operator--() noexcept
                {
                    _node = _node->_prev;
                    return *this;
                }
                list_iterator operator--(int) noexcept
                {
                    list_iterator temp (_node);
                    _node = _node->_prev;
                    return temp;
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
                    iterator temp(_it);
                    --(temp);
                    return *temp;
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
                _head = new container_node;
                _head -> _prev = _head;
                _head -> _next = _head;
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
            void swap(template_container::list_c::list<list_type>& swap_target)
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
                container_node* cur = _head->_next;
                size_t count = 0;
                while (cur != _head)
                {
                    count++;
                    cur = cur->_next;
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

            iterator insert(iterator Pos ,const list_type& Val)
            {
                container_node* new_container_node = new container_node(Val);
                //开辟新节点
                container_node* PCur = Pos._node;
                //保存pos位置的值
                new_container_node->_prev = PCur->_prev;
                new_container_node->_next = PCur;
                new_container_node->_prev->_next = new_container_node;
                PCur->_prev = new_container_node;
                return iterator(new_container_node);
            }
            iterator insert(iterator Pos ,list_type&& Val)
            {
                container_node* new_container_node = new container_node(std::forward<list_type>(Val));
                container_node* PCur = Pos._node;
                new_container_node->_prev = PCur->_prev;
                new_container_node->_next = PCur;
                new_container_node->_prev->_next = new_container_node;
                PCur->_prev = new_container_node;
                return iterator(new_container_node);
            }
            iterator erase(iterator Pos) noexcept
            {
                // 找到待删除的节点
                container_node* pDel = Pos._node;
                container_node* pRet = pDel->_next;

                // 将该节点从链表中拆下来并删除
                pDel->_prev->_next = pDel->_next;
                pDel->_next->_prev = pDel->_prev;
                delete pDel;

                return iterator(pRet);
            }
            void resize(size_t newsize, const list_type& list_type_data = list_type())
            {
                //将data插入到链表中
                size_t OldSize = size();
                if (newsize <= OldSize)
                {
                    // 有效元素个数减少到newsize
                    while (newsize < OldSize)
                    {
                        pop_back();
                        OldSize--;
                    }
                }
                else
                {
                    while (OldSize < newsize)
                    {
                        push_back(list_type_data);
                        OldSize++;
                    }
                }
            }
            void clear() noexcept
            {
                //循环释放资源
                container_node* cur = _head->_next;
                // 采用头删除
                while (cur != _head)
                {
                    _head->_next = cur->_next;
                    delete cur;
                    cur = _head->_next;
                }
                _head->_next = _head->_prev = _head;
            }
            list& operator=(list<list_type> list_data) noexcept
            {
                //运算符重载
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
                }
                return *this;
            }
            list operator+(const list<list_type>& list_data)
            {
                list<list_type> return_list_object (cbegin(),cend());
                const_iterator _begin = list_data.cbegin();
                const_iterator _end   = list_data.cend();
                while(_begin != _end)
                {
                    return_list_object.push_back(*_begin);
                    ++_begin;
                }
                return return_list_object;
            }
            list& operator+=(const list<list_type>& list_data)
            {
                const_iterator _begin = list_data.cbegin();
                const_iterator _end  = list_data.cend();
                while(_begin != _end)
                {
                    push_back(*_begin);
                    ++_begin;
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
    namespace stack_a
    {
        template <typename stack_type,typename container_stack = template_container::vector_c::vector<stack_type>>
        class stack
        {
        private:
            container_stack cm_stack;
        public:
            ~stack()
            {
                ;
            }
            void push(const stack_type& stack_type_data)
            {
                cm_stack.push_back(stack_type_data);                 //插入尾
            }
            void pop()
            {
                cm_stack.pop_back();                                 //删除尾
            }
            size_t size() noexcept
            {
                return cm_stack.size();
            }
            bool empty() noexcept
            {
                return cm_stack.empty();
            } 
            stack_type& top() noexcept
            {
                return cm_stack.back();
            }
            stack(const stack<stack_type>& stack_data)
            {
                cm_stack = stack_data.cm_stack;
            }
            stack( stack<stack_type>&& stack_data) noexcept
            {
                cm_stack = std::move(stack_data.cm_stack); //std::move将对象转换为右值引用
            }
            stack(std::initializer_list<stack_type> stack_type_data)
            {
                for(auto& chained_values:stack_type_data)
                {
                    cm_stack.push_back(chained_values);
                }
            }
            stack(const stack_type& stack_type_data)
            {
                cm_stack.push_back(stack_type_data);
            }
            stack& operator= (const stack<stack_type>& stack_data)
            {
                if(this != &stack_data)
                {
                    cm_stack = stack_data.cm_stack;
                }
                return *this;
            }
            stack& operator=(stack<stack_type>&& stack_data) noexcept
            {
                if(this != &stack_data)
                {
                    cm_stack = std::move(stack_data.cm_stack);
                }
                return *this;
            }
            stack() = default;
        };
    }
    /*############################     queue适配器     ############################*/
    namespace queue_a
    {
        template <typename Queue_Type ,typename ContainerQueue = template_container::list_c::list<Queue_Type> >
        class queue
        {
            //注意队列适配器不会自动检测队列有没有元素，为学异常，注意空间元素
            ContainerQueue ContainerQueueTemp;
        public:
            ~queue()
            {
                ;
            }
            void push(const Queue_Type& QueueTemp)
            {
                ContainerQueueTemp.push_back(QueueTemp);
            }
            void pop()
            {
                ContainerQueueTemp.pop_front();
                //list返回的是指向下一个位置的正向迭代器
                //vector返回的是整个容器
            }
            size_t size() noexcept
            {
                //返回元素个数
                return ContainerQueueTemp.size();
            }
            bool empty() noexcept
            {
                //判断容器是否为空
                return ContainerQueueTemp.empty();
            }
            Queue_Type& front() noexcept
            {
                //查看头数据
                return ContainerQueueTemp.front();
            }
            Queue_Type& back() noexcept
            {
                //查看尾数据
                return ContainerQueueTemp.back();
            }
            queue(const queue<Queue_Type>& QueueTemp)
            {
                //拷贝构造
                ContainerQueueTemp = QueueTemp.ContainerQueueTemp;
            }
            queue(queue<Queue_Type>&& QueueTemp) noexcept
            {
                //移动构造
                ContainerQueueTemp = std::move(QueueTemp.ContainerQueueTemp);
            }
            queue(std::initializer_list<Queue_Type> QueueTemp)
            {
                //链式构造
                for(auto& chained_values:QueueTemp)
                {
                    ContainerQueueTemp.push_back(chained_values);
                }
            }
            queue(const Queue_Type& QueueTemp)
            {
                ContainerQueueTemp.push_back(QueueTemp);
            }
            queue() = default;
            queue& operator= (const queue<Queue_Type>& QueueTemp)
            {
                if(this != &QueueTemp)
                {
                    ContainerQueueTemp = QueueTemp.ContainerQueueTemp;
                }
                return *this;
            }
            queue& operator=(queue<Queue_Type>&& QueueTemp) noexcept
            {
                if(this != &QueueTemp)
                {
                    ContainerQueueTemp = std::move(QueueTemp.ContainerQueueTemp);
                }
                return *this;
            }
        };
        /*############################     priority_queue 适配器     ############################*/
        template <typename priority_queue_type,typename imitation_function_parameter = template_container::imitation_functions::Less<priority_queue_type>,
        typename container_priority_queue = template_container::vector_c::vector<priority_queue_type>>
        class priority_queue
        {
            //创建容器对象
            container_priority_queue cm_priority_queue;
            imitation_function_parameter com;
            //仿函数对象

            void priority_queue_adjust_upwards(int adjust_upwards_child) noexcept
            {
                //向上调整算法
                int adjust_upwards_parent = (adjust_upwards_child-1)/2;
                while(adjust_upwards_child > 0)
                {
                    if(com(cm_priority_queue[adjust_upwards_parent],cm_priority_queue[adjust_upwards_child]))
                    {
                        template_container::algorithm::swap(cm_priority_queue[adjust_upwards_parent],cm_priority_queue[adjust_upwards_child]);
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
                while(adjust_downwards_child < (int)cm_priority_queue.size())
                {
                    int adjust_downwards_left  = adjust_downwards_child;
                    int adjust_downwards_right = adjust_downwards_left + 1;
                    if( adjust_downwards_right < (int)cm_priority_queue.size() && com(cm_priority_queue[adjust_downwards_left],cm_priority_queue[adjust_downwards_right]))
                    {
                        //大堆找出左右节点哪个孩子大
                        adjust_downwards_child = adjust_downwards_right;
                    }
                    if(com(cm_priority_queue[adjust_downwards_parent],cm_priority_queue[adjust_downwards_child]))
                    {
                        //建大堆把小的换下去，建小堆把大的换下去
                        template_container::algorithm::swap(cm_priority_queue[adjust_downwards_parent] , cm_priority_queue[adjust_downwards_child]);

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
                cm_priority_queue.~vector();
            }
            void push(const priority_queue_type& prioity_queue_type_data)
            {
                cm_priority_queue.push_back(prioity_queue_type_data);
                priority_queue_adjust_upwards((int)cm_priority_queue.size()-1);
            }
            priority_queue_type& top() noexcept
            {
                return cm_priority_queue.front();
            }
            bool empty() noexcept
            {
                return cm_priority_queue.empty();
            }
            size_t size() noexcept
            {
                return cm_priority_queue.size();
            }
            void pop()
            {
                template_container::algorithm::swap(cm_priority_queue[0],cm_priority_queue[cm_priority_queue.size()-(size_t)1]);
                cm_priority_queue.pop_back();
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
                cm_priority_queue = priority_queue_data.cm_priority_queue;
            }
            priority_queue(priority_queue&& priority_queue_data) noexcept
            :com(priority_queue_data.com)
            {
                //移动构造
                cm_priority_queue = std::move(priority_queue_data.cm_priority_queue);
            }
            priority_queue(const priority_queue_type& priority_queue_type_data)
            {
                cm_priority_queue.push_back(priority_queue_type_data);
                priority_queue_adjust_upwards((int)cm_priority_queue.size()-1);
            }
            priority_queue& operator=(priority_queue&& priority_queue_data) noexcept
            {
                //移动赋值
                if(this != &priority_queue_data)
                {
                    cm_priority_queue = std::move(priority_queue_data.cm_priority_queue);
                    com = priority_queue_data.com;
                }
                return *this;
            }
            priority_queue& operator=(const priority_queue& priority_queue_data)
            {
                //拷贝赋值
                if(this != &priority_queue_data)
                {
                    cm_priority_queue = priority_queue_data.cm_priority_queue;
                    com = priority_queue_data.com;
                }
                return *this;
            }
        };
    }
    namespace tree_c
    {
        /*############################     BSTree 容器     ############################*/
        template <typename BSTreeType,typename CompareImitationFunctionsBS = template_container::imitation_functions::Less <BSTreeType> >
        class BSTree
        {
        private:
            class BSTreeTypeNode
            {
            public:
                //节点类
                BSTreeTypeNode* _left;
                BSTreeTypeNode* _right;
                BSTreeType _data;
                BSTreeTypeNode(const BSTreeType& vector_data = BSTreeType())
                :_left(nullptr),_right(nullptr),_data(vector_data)
                {
                    ;
                }
                ~BSTreeTypeNode()
                {
                    _left  = nullptr;
                    _right = nullptr;
                }
            };
            using container_node = BSTreeTypeNode;
            container_node* _ROOT;
            CompareImitationFunctionsBS com;
            void _MiddleOrderTraversal(container_node* ROOT_Temp)
            {
                //中序遍历函数
                template_container::stack_a::stack<container_node*> stack_type_data;
                while(ROOT_Temp != nullptr || !stack_type_data.empty())
                {
                    while(ROOT_Temp!= nullptr)
                    {
                        stack_type_data.push(ROOT_Temp);
                        //压栈
                        ROOT_Temp = ROOT_Temp->_left;
                    }
                    // 访问栈顶节点
                    ROOT_Temp = stack_type_data.top();
                    //弹出栈顶元素，刷新栈顶元素，栈顶元素会变成之前压入栈的节点的父节点
                    
                    stack_type_data.pop();
                    std::cout <<  ROOT_Temp->_data << " ";
                    // std::cout << &ROOT_Temp->_data << " ";
                    //检查地址是不是值拷贝
                    // 转向右子树
                    ROOT_Temp = ROOT_Temp->_right;
                }
            }
            size_t _MiddleOrderTraversal(container_node* ROOT_Temp,size_t& SizeTemp )
            {
                template_container::stack_a::stack<container_node*> stack_type_data;
                while(ROOT_Temp != nullptr || !stack_type_data.empty())
                {
                    while(ROOT_Temp!= nullptr)
                    {
                        stack_type_data.push(ROOT_Temp);
                        //压栈
                        ROOT_Temp = ROOT_Temp->_left;
                    }
                    // 访问栈顶节点
                    ROOT_Temp = stack_type_data.top();
                    //弹出栈顶元素，刷新栈顶元素，栈顶元素会变成之前压入栈的节点的父节点
                    
                    stack_type_data.pop();
                    SizeTemp++;
                    // 转向右子树
                    ROOT_Temp = ROOT_Temp->_right;
                }
                return SizeTemp;
            }
            void _PreOrderTraversal(container_node* ROOT_Temp )
            {
                //前序遍历，最外左子树全部压栈
                if(ROOT_Temp == nullptr)
                {
                    return;
                }
                container_node* _PreOrderTraversalTest = ROOT_Temp;
                template_container::stack_a::stack<container_node*> stack_Temp;
                stack_Temp.push(_PreOrderTraversalTest);
                //不能添加|| _PreOrderTraversalTest != nullptr ，因为最后一层循环后_Pre_order_traversal_test还是为真后面循环无意义，反之还会破环性质
                while( !stack_Temp.empty() )
                {
                    _PreOrderTraversalTest = stack_Temp.top();
                    stack_Temp.pop();

                    std::cout << _PreOrderTraversalTest->_data << " ";
                    if(_PreOrderTraversalTest->_right != nullptr)
                    {
                        stack_Temp.push(_PreOrderTraversalTest->_right);
                    }
                    if(_PreOrderTraversalTest->_left != nullptr)
                    {
                        stack_Temp.push(_PreOrderTraversalTest->_left);
                    }
                    //修改逻辑错误，先压右子树再压左子树，因为这是栈
                }
            }
            void clear()
            {
                if(_ROOT == nullptr)
                {
                    return;
                }
                //循环释放资源
                template_container::stack_a::stack<container_node*> StaicClearTemp;
                StaicClearTemp.push(_ROOT);
                while(StaicClearTemp.empty() == false)
                {
                    container_node* ROOT_Temp = StaicClearTemp.top();
                    //取出元素，把左右节点入进去
                    StaicClearTemp.pop();
                    if(ROOT_Temp->_left!= nullptr)
                    {
                        StaicClearTemp.push(ROOT_Temp->_left);
                    }
                    if(ROOT_Temp->_right!= nullptr)
                    {
                        StaicClearTemp.push(ROOT_Temp->_right);
                    }
                    delete ROOT_Temp;
                }
                _ROOT = nullptr;
            }
        public:
            ~BSTree()
            {
                clear();
            }
            // 构造函数，使用初始化列表来初始化二叉搜索树
            BSTree(std::initializer_list<BSTreeType> lightweight_container)
            {
                for(auto& chained_values:lightweight_container)
                {
                    push(chained_values);
                }
            }
            BSTree(const BSTreeType& BST_Temp = BSTreeType(),CompareImitationFunctionsBS com_temp = CompareImitationFunctionsBS())
            :_ROOT(nullptr),com(com_temp)
            {   
                _ROOT = new container_node(BST_Temp);
            }
            BSTree(BSTree&& BinarySearchTreeTemp)
            :com(BinarySearchTreeTemp.com),_ROOT(nullptr)
            {
                _ROOT = std::move(BinarySearchTreeTemp._ROOT);
                BinarySearchTreeTemp._ROOT = nullptr;
            }
            BSTree(const BSTree& BinarySearchTreeTemp)
            :_ROOT(nullptr),com(BinarySearchTreeTemp.com)
            //这个拷贝构造不需要传模板参数，因为模板参数是在编译时确定的，而不是在运行时确定的，对于仿函数，直接拿传进来的引用初始化就可以了
            {
                //拷贝构造，时间复杂度为O(n)
                container_node* BinarySearchTreeTempCopy = BinarySearchTreeTemp._ROOT;
                if(BinarySearchTreeTempCopy == nullptr)
                {
                    return;
                }
                template_container::stack_a::stack<template_container::practicality::pair<container_node*,container_node**> > stack_type_data;
                //注意这里把本地_ROOT类型传过去，是因为要对本地的_ROOT进行操作，所以要传二级指针
                //这里传引用也不行，这里的对象是动态变化的，所以传引用也不行
                //如果是对全局的_ROOT进行操作，就传一级指针
                stack_type_data.push(template_container::practicality::pair<container_node*,container_node**>(BinarySearchTreeTempCopy,&_ROOT));
                while( !stack_type_data.empty() )
                {
                    auto StacKTempPair = stack_type_data.top();
                    stack_type_data.pop();
                    *(StacKTempPair.second) = new container_node(StacKTempPair.first->_data);
                    // container_node* _staic_temp_pair_second = *(StacKTempPair.second);
                    // if(StacKTempPair.first->_left!= nullptr)
                    // {
                    //     stack_type_data.push(MY_Template::practicality::pair<container_node*,container_node**>(StacKTempPair.first->_left,&_staic_temp_pair_second->_left));
                    // }
                    // if(StacKTempPair.first->_right!= nullptr)
                    // {
                    //     stack_type_data.push(MY_Template::practicality::pair<container_node*,container_node**>(StacKTempPair.first->_right,&_staic_temp_pair_second->_right));
                    // }
                    //移除临时变量，直接使用指针解引用
                    if(StacKTempPair.first->_right!= nullptr)
                    {
                        stack_type_data.push(template_container::practicality::pair<container_node*,container_node**>(StacKTempPair.first->_right,&((*StacKTempPair.second)->_right)));
                    }
                    if(StacKTempPair.first->_left!= nullptr)
                    {
                        stack_type_data.push(template_container::practicality::pair<container_node*,container_node**>(StacKTempPair.first->_left,&((*StacKTempPair.second)->_left)));
                    }
                }
            }
            void MiddleOrderTraversal()
            {
                //中序遍历函数
                _MiddleOrderTraversal(_ROOT);
            }
            void PreOrderTraversal()
            {
                _PreOrderTraversal(_ROOT);
            }
            bool push(const BSTreeType& vector_data)
            {
                //尾上插入函数
                if(_ROOT == nullptr)
                {
                    _ROOT = new container_node(vector_data);
                    return true;
                }
                else
                {
                    container_node* ROOT_Temp = _ROOT;
                    container_node* _ROOT_Temp_Parent = nullptr;
                    while(ROOT_Temp!= nullptr)
                    {
                        _ROOT_Temp_Parent = ROOT_Temp;
                        if(!com(vector_data, ROOT_Temp->_data) && !com(ROOT_Temp->_data, vector_data))
                        {
                            //改用仿函数特性，判断是否有重复元素,防止自定义类型没有重载==运算符
                            return false;
                        }
                        else if(com(vector_data , ROOT_Temp->_data))
                        {
                            ROOT_Temp = ROOT_Temp->_left;
                        }
                        else
                        {
                            ROOT_Temp = ROOT_Temp->_right;
                        }
                    }
                    //新开节点链接
                    container_node* _ROOT_Temp_Node = new container_node(vector_data);
                    //链接节点
                    if(com(vector_data , _ROOT_Temp_Parent->_data))
                    {
                        _ROOT_Temp_Parent->_left = _ROOT_Temp_Node;
                    }
                    else
                    {
                        _ROOT_Temp_Parent->_right = _ROOT_Temp_Node;
                    }
                    return true;
                }
            }
            BSTree& pop(const BSTreeType& vector_data)
            {
                //删除节点
                container_node* ROOT_Temp = _ROOT;
                container_node* _ROOT_Temp_Parent = nullptr;
                while( ROOT_Temp != nullptr )
                {
                    if(vector_data == ROOT_Temp->_data)
                    {
                        //找到节点
                        if(ROOT_Temp->_left == nullptr)
                        {
                            //左子树为空,下面判断要删除的节点是父节点的左子树还是右子树，防止多删和误删
                            if (_ROOT_Temp_Parent == nullptr)
                            {
                                // 当前节点是根节点，直接更新 _ROOT
                                _ROOT = ROOT_Temp->_right;
                            }
                            else
                            {
                                if(_ROOT_Temp_Parent->_left == ROOT_Temp)
                                {
                                    //根节点
                                    _ROOT_Temp_Parent->_left = ROOT_Temp->_right;
                                }   
                                else
                                {
                                    //非根节点
                                    _ROOT_Temp_Parent->_right = ROOT_Temp->_right;
                                }
                            }
                            delete ROOT_Temp;
                            ROOT_Temp = nullptr;
                            return *this;
                        }
                        else if(ROOT_Temp->_right == nullptr)
                        {
                            if (_ROOT_Temp_Parent == nullptr)
                            {
                                // 防止当前节点是根节点，无法解引用，直接更新 _ROOT
                                _ROOT = ROOT_Temp->_left;
                            }
                            else
                            {
                                if(_ROOT_Temp_Parent->_left == ROOT_Temp)
                                {
                                    _ROOT_Temp_Parent->_left = ROOT_Temp->_left;
                                }
                                else
                                {
                                    _ROOT_Temp_Parent->_right = ROOT_Temp->_left;
                                }
                            }
                            delete ROOT_Temp;
                            ROOT_Temp = nullptr;
                            return *this;	
                        }
                        else
                        {
                            //左右子树都不为空，找右子树的最左节点
                            container_node* _ROOT_Temp_right_min = ROOT_Temp->_right;
                            container_node* _ROOT_Temp_test_Parent = ROOT_Temp;
                            while(_ROOT_Temp_right_min->_left != nullptr)
                            {
                                _ROOT_Temp_test_Parent = _ROOT_Temp_right_min;
                                _ROOT_Temp_right_min = _ROOT_Temp_right_min->_left;
                            }
                            //找到最左节点	
                            template_container::algorithm::swap(ROOT_Temp->_data,_ROOT_Temp_right_min->_data);
                            //因为右树最左节点已经被删，但是还需要把被删的上一节点的左子树指向被删节点的右子树，不管右子树有没有节点都要连接上
                            if(_ROOT_Temp_test_Parent == ROOT_Temp)
                            {
                                //说明右子树没有左子树最小节点就是右子树的第一个根，如同上面判断条件：要删除的根节点等于右子树最小节点的父亲节点
                                _ROOT_Temp_test_Parent->_right = _ROOT_Temp_right_min->_right;
                                //这俩交换指针指向位置就行，上面已经完成值的替换
                            }
                            else
                            {
                                //情况2：说明要删除的数据的右子树的最左节点如果有数据，就把数据连接到右子树的最左节点的父亲节点的左子树指向最左子树的右子树
                                _ROOT_Temp_test_Parent->_left = _ROOT_Temp_right_min->_right;
                            }
                            delete _ROOT_Temp_right_min;
                            _ROOT_Temp_right_min = nullptr;
                            return *this;
                        }
                    }
                    else if(com(vector_data, ROOT_Temp->_data))
                    {
                        _ROOT_Temp_Parent = ROOT_Temp;
                        ROOT_Temp = ROOT_Temp->_left;
                    }
                    else
                    {
                        _ROOT_Temp_Parent = ROOT_Temp;
                        ROOT_Temp = ROOT_Temp->_right;
                    }
                }
                return *this;
            }
            size_t size()
            {
                size_t _size = 0;
                return _MiddleOrderTraversal(_ROOT,_size);
            }
            size_t size()const
            {
                size_t _size = 0;
                return _MiddleOrderTraversal(_ROOT,_size);
            }
            container_node* find(const BSTreeType& vector_data)
            {
                //查找函数
                container_node* _ROOT_Find = _ROOT;
                while(_ROOT_Find!= nullptr)
                {
                    if(vector_data == _ROOT_Find->_data)
                    {
                        return _ROOT_Find;
                    }
                    else if(com(vector_data, _ROOT_Find->_data))
                    {
                        _ROOT_Find = _ROOT_Find->_left;
                    }
                    else
                    {
                        _ROOT_Find = _ROOT_Find->_right;
                    }
                }
                return _ROOT_Find;
            }
            void insert(const BSTreeType& FormerData,const BSTreeType& LatterData)
            {
                //在former_data后面插入latter_data
                container_node* ROOTFormerData = find(FormerData);
                //插入节点
                if(ROOTFormerData == nullptr)
                {
                    return;
                }
                else
                {
                    container_node* _ROOT_latter_data = new container_node(LatterData);
                    _ROOT_latter_data->_left = ROOTFormerData->_right;
                    ROOTFormerData->_right = _ROOT_latter_data;
                }
            }
            BSTree& operator=(const BSTree& BinarySearchTreeTemp)
            {
                //赋值运算符重载
                if(this != &BinarySearchTreeTemp)
                {
                    clear();
                    com = BinarySearchTreeTemp.com;
                    BSTree BinarySearchTreeTempCopy = BinarySearchTreeTemp;
                    template_container::algorithm::swap(BinarySearchTreeTempCopy._ROOT,_ROOT);
                }
                return *this;
            }
            BSTree& operator=(BSTree && BinarySearchTreeTemp)
            {
                //移动赋值运算符重载
                if(this != &BinarySearchTreeTemp)
                {
                    clear();
                    com = BinarySearchTreeTemp.com;
                    _ROOT = std::move(BinarySearchTreeTemp._ROOT);
                    BinarySearchTreeTemp._ROOT = nullptr;
                }
                return *this;
            }

        };
        /*############################     AVLTree 容器     ############################*/
        template <typename AVLTreeTypeK,typename AVLTreeTypeV,typename CompareImitationFunctionsAVL = template_container::imitation_functions::Less <AVLTreeTypeK>,
        typename AVLSyntheticClass = template_container::practicality::pair<AVLTreeTypeK,AVLTreeTypeV> >
        class AVLTree
        {
        private:
            class AVLTreeTypeNode
            {
            public:
                AVLSyntheticClass _data;

                AVLTreeTypeNode* _left;
                AVLTreeTypeNode* _right;
                AVLTreeTypeNode* _parent;
                //平衡因子
                int _BalanceFactor;
                AVLTreeTypeNode(const AVLTreeTypeK& TreeNodeTemp = AVLTreeTypeK(),const AVLTreeTypeV& TreeNodeTemp2 = AVLTreeTypeV())
                :_data(TreeNodeTemp,TreeNodeTemp2),_left(nullptr),_right(nullptr),_parent(nullptr),_BalanceFactor(0)
                {
                    ;
                }
                AVLTreeTypeNode(const AVLSyntheticClass& AVLTreePairTemp)
                :_data(AVLTreePairTemp),_left(nullptr),_right(nullptr),_parent(nullptr),_BalanceFactor(0)
                {
                    ;
                }
            };
            template<typename T, typename Ref ,typename Ptr>
            class AVLTreeIterator
            {
            public:
                using iterator_Node = AVLTreeTypeNode;
                using Self = AVLTreeIterator<T,Ref,Ptr>;
                using pointer = Ptr;
                using reference = Ref;
                iterator_Node* _Node;
                AVLTreeIterator(iterator_Node* NodeTemp)
                :_Node(NodeTemp)
                {
                    ;
                }
                Ptr operator->()
                {
                    return &(_Node->_data);
                }
                Ref& operator*()
                {
                    return _Node->_data;
                }
                bool operator!=(const Self& SelfTemp)
                {
                    return _Node != SelfTemp._Node;
                }
                bool operator==(const Self& SelfTemp) 
                {
                    return _Node == SelfTemp._Node;
                }
                Self& operator++()
                {
                    if(_Node->_right != nullptr)
                    {
                        _Node = _Node->_right;
                        while(_Node->_left != nullptr)
                        {
                            _Node = _Node->_left;
                        }
                    }
                    else
                    {
                        container_node* NodeTemp = _Node;
                        while(NodeTemp->_parent != nullptr && NodeTemp == NodeTemp->_parent->_right)
                        {
                            NodeTemp = NodeTemp->_parent;
                        }
                        _Node = NodeTemp->_parent;
                    }
                    return *this;
                }
                Self operator++(int)
                {
                    Self temp = *this;
                    ++(*this);
                    return temp;
                }
                Self& operator--()
                {
                    if(_Node->_left != nullptr)
                    {
                        _Node = _Node->_left;
                        while(_Node->_right != nullptr)
                        {
                            _Node = _Node->_right;
                        }
                    }
                    else
                    {
                        container_node* NodeTemp = _Node;
                        while(NodeTemp->_parent != nullptr && NodeTemp == NodeTemp->_parent->_left)
                        {
                            NodeTemp = NodeTemp->_parent;
                        }
                        _Node = NodeTemp->_parent;
                    }
                    return *this;
                }
                Self operator--(int)
                {
                    Self temp = *this;
                    --(*this);
                    return temp;
                }
            };
            template<typename iterator>
            class AVLTreeReverseIterator
            {
            public:
                using Self = AVLTreeReverseIterator<iterator>;
                iterator _it;
                using Ptr = typename iterator::pointer;
                using Ref = typename iterator::reference;
                AVLTreeReverseIterator(iterator ItTemp)
                :_it(ItTemp)
                {
                    ;
                }
                Ptr operator->()
                {
                    return &(*this);
                }
                Ref& operator*()
                {
                    return *_it;
                }
                bool operator!=(const Self& SelfTemp)
                {
                    return _it != SelfTemp._it;
                }
                bool operator==(const Self& SelfTemp)
                {
                    return _it == SelfTemp._it;
                }
                Self& operator++()
                {
                    --_it;
                    return *this;
                }
                Self operator++(int)
                {
                    Self temp = *this;
                    --(*this);
                    return temp;
                }
                Self& operator--()
                {
                    ++_it;
                    return *this;
                }
                Self operator--(int)
                {
                    Self temp = *this;
                    ++(*this);
                    return temp;
                }
                
            };
            using container_node = AVLTreeTypeNode;
            container_node* _ROOT;

            CompareImitationFunctionsAVL com;
            void LeftRevolve(container_node*& ParentTempNode)
            {
                //传进来的值是发现该树平衡性被破坏的节点地址
                //大致思想：因为这是左单旋，所以找传进来的父亲节点的右根节点来当调整节点
                //然后把调整节点的左根节点赋值给传进来的父亲节点的右根节点 (刚才已经用节点保存过调整节点，所以这里直接赋值)，
                //再把父亲节点赋值给调整节点的左根节点，！！注意：在旋转的过程中还要处理每个调整节点的父亲节点的指向和平衡因子

                // {
                //     container_node* SubRightTemp = ParentTempNode->_right;
                //     ParentTempNode->_right = SubRightTemp->_left;
                //     SubRightTemp->_left = ParentTempNode;
                //     //错误写法：未同步调整父亲节点和判断调整节点的左根节点是否为空，以及全部需要调整节点的父亲指针的指针的指向
                // }
                if(ParentTempNode == nullptr|| ParentTempNode->_right == nullptr)
                {
                    std::cout <<"left "<< "空指针"  <<std::endl;
                    return ;
                }
                container_node* SubRightTemp = ParentTempNode->_right;
                // container_node* SubRightLeftTemp = SubRightTemp->_left;
                container_node* SubRightLeftTemp = (SubRightTemp->_left)? SubRightTemp->_left : nullptr;
                //防止空指针解引用
                ParentTempNode->_right = SubRightLeftTemp;
                if(SubRightLeftTemp)
                {
                    SubRightLeftTemp->_parent = ParentTempNode;
                    //如果Sub_right_left_temp(调整节点的左根节点)不等于空，还需要调整Sub_right_left_temp它的父亲节点
                }
                SubRightTemp->_left = ParentTempNode;
                //这里先保存一下parent_temp_Node的父亲地址，防止到下面else比较的时候丢失
                container_node* ParentParentTempNode = ParentTempNode->_parent;
                ParentTempNode->_parent = SubRightTemp;
                //更新parent_temp_Node节点指向正确的地址

                if(_ROOT == ParentTempNode)
                {
                    //如果要调整的节点是根根节点，直接把调整节点赋值给根节点，然后把调整节点的父亲节点置空
                    _ROOT = SubRightTemp;
                    SubRightTemp->_parent = nullptr;
                }
                else
                {
                    //调整前parent_temp_Node是这个树的根现在是Sub_right_temp是这个树的根
                    if(ParentParentTempNode->_left == ParentTempNode)
                    {
                        ParentParentTempNode->_left = SubRightTemp;
                    }
                    else
                    {
                        ParentParentTempNode->_right = SubRightTemp;
                    }
                    SubRightTemp->_parent = ParentParentTempNode;
                }
                ParentTempNode->_BalanceFactor = SubRightTemp->_BalanceFactor = 0;
            }

            void RightRevolve(container_node*& ParentTempNode)
            {
                //思路同左单旋思路差不多
                if(ParentTempNode == nullptr|| ParentTempNode->_left == nullptr)
                {
                    std::cout <<"right "<< "空指针"  <<std::endl; 
                    return ;
                }
                container_node* SubLeftTemp = ParentTempNode->_left;
                container_node* SubLeftRightTemp = (SubLeftTemp->_right) ? SubLeftTemp->_right : nullptr;
                //防止空指针解引用
                ParentTempNode->_left = SubLeftRightTemp;
                if(SubLeftRightTemp)
                {
                    SubLeftRightTemp->_parent = ParentTempNode;
                }
                SubLeftTemp->_right = ParentTempNode;
                //保存parent_temp_Node的父亲节点
                container_node* ParentParentTempNode = ParentTempNode->_parent;
                ParentTempNode->_parent = SubLeftTemp;

                if(_ROOT == ParentTempNode)
                {
                    _ROOT = SubLeftTemp;
                    SubLeftTemp->_parent = nullptr;
                }
                else
                {
                    if(ParentParentTempNode->_left == ParentTempNode)
                    {
                        ParentParentTempNode->_left = SubLeftTemp;
                    }
                    else
                    {
                        ParentParentTempNode->_right = SubLeftTemp;
                    }
                    SubLeftTemp->_parent = ParentParentTempNode;
                }
                ParentTempNode->_BalanceFactor = SubLeftTemp->_BalanceFactor = 0;
            }
            void RightLeftRevolve(container_node*& ParentTempNode)
            {
                if(ParentTempNode==nullptr || ParentTempNode->_right == nullptr)
                {
                    std::cout <<"right_left "<< "空指针"  <<std::endl;
                    return;
                }
                container_node* SubRightTemp = ParentTempNode->_right;
                container_node* SubRightLeftTemp = SubRightTemp->_left;
                int BalanceFactorTemp = SubRightLeftTemp->_BalanceFactor;

                RightRevolve(ParentTempNode->_right);
                //右旋
                LeftRevolve(ParentTempNode);
                //左旋
                if(BalanceFactorTemp == -1)
                {
                    ParentTempNode->_BalanceFactor = 0;
                    SubRightTemp->_BalanceFactor = 1;
                    SubRightLeftTemp->_BalanceFactor = 0;
                }
                else if(BalanceFactorTemp == 1)
                {
                    ParentTempNode->_BalanceFactor = -1;
                    SubRightTemp->_BalanceFactor = 0;
                    SubRightLeftTemp->_BalanceFactor = 0;
                }
                else
                {
                    ParentTempNode->_BalanceFactor = 0;
                    SubRightTemp->_BalanceFactor = 0;
                    SubRightLeftTemp->_BalanceFactor = 0;
                }
            }
            void LeftRightRevolve(container_node*& ParentTempNode)
            {   
                if(ParentTempNode == nullptr || ParentTempNode->_left == nullptr)
                {
                    std::cout << "left_right " << "空指针" << std::endl;
                    return ;
                }
                container_node* SubLeftTemp = ParentTempNode->_left;
                container_node* SubLeftRightTemp = SubLeftTemp->_right;
                int BalanceFactorTemp = SubLeftRightTemp->_BalanceFactor;

                LeftRevolve(ParentTempNode->_left);
                //左旋
                RightRevolve(ParentTempNode);
                //右旋
                if(BalanceFactorTemp == -1)
                {
                    ParentTempNode->_BalanceFactor = 0;
                    SubLeftTemp->_BalanceFactor = 1;
                    SubLeftRightTemp->_BalanceFactor = 0;
                }
                else if(BalanceFactorTemp == 1)
                {
                    ParentTempNode->_BalanceFactor = -1;
                    SubLeftTemp->_BalanceFactor = 0;
                    SubLeftRightTemp->_BalanceFactor = 0;
                }
                else
                {
                    ParentTempNode->_BalanceFactor = 0;
                    SubLeftTemp->_BalanceFactor = 0;
                    SubLeftRightTemp->_BalanceFactor = 0;
                }
            }
            void clear()
            {
                //清空所有资源
                if(_ROOT == nullptr)
                {
                    return;
                }
                else
                {
                    template_container::stack_a::stack<container_node*> stack_type_data;
                    //前序释放
                    stack_type_data.push(_ROOT);
                    while(!stack_type_data.empty())
                    {
                        container_node* temp = stack_type_data.top();
                        stack_type_data.pop();
                        if(temp->_left != nullptr)
                        {
                            stack_type_data.push(temp->_left);
                        }
                        if(temp->_right != nullptr)
                        {
                            stack_type_data.push(temp->_right);
                        }
                        delete temp;
                        temp = nullptr;
                    }
                    _ROOT = nullptr;
                }
            }
            //测试函数
            void _PreOrderTraversal(container_node* ROOT_Temp )
            {
                //前序遍历，最外左子树全部压栈
                if(ROOT_Temp == nullptr)
                {
                    return;
                }
                container_node* _PreOrderTraversalTest = ROOT_Temp;
                template_container::stack_a::stack<container_node*> stack_Temp;
                stack_Temp.push(_PreOrderTraversalTest);
                //不能添加|| _PreOrderTraversalTest != nullptr ，因为最后一层循环后_Pre_order_traversal_test还是为真后面循环无意义，反之还会破环性质
                while( !stack_Temp.empty() )
                {
                    _PreOrderTraversalTest = stack_Temp.top();
                    stack_Temp.pop();

                    std::cout << _PreOrderTraversalTest->_data << " ";
                    //修改逻辑错误，先压右子树再压左子树，因为这是栈
                    if(_PreOrderTraversalTest->_right != nullptr)
                    {
                        stack_Temp.push(_PreOrderTraversalTest->_right);
                    }
                    if(_PreOrderTraversalTest->_left != nullptr)
                    {
                        stack_Temp.push(_PreOrderTraversalTest->_left);
                    }
                }
            }
            void _MiddleOrderTraversal(container_node* ROOT_Temp)
            {
                //中序遍历函数
                template_container::stack_a::stack<container_node*> stack_type_data;
                while(ROOT_Temp != nullptr || !stack_type_data.empty())
                {
                    while(ROOT_Temp!= nullptr)
                    {
                        stack_type_data.push(ROOT_Temp);
                        //压栈
                        ROOT_Temp = ROOT_Temp->_left;
                    }
                    // 访问栈顶节点
                    ROOT_Temp = stack_type_data.top();
                    //弹出栈顶元素，刷新栈顶元素，栈顶元素会变成之前压入栈的节点的父节点
                    
                    stack_type_data.pop();
                    std::cout <<  ROOT_Temp->_data << " ";
                    // std::cout << &ROOT_Temp->_data << " ";
                    //检查地址是不是值拷贝
                    // 转向右子树
                    ROOT_Temp = ROOT_Temp->_right;
                }
            }
            size_t _size()
            {
                size_t temp = 0; 
                if(_ROOT == nullptr)
                {
                    return temp;
                }
                else
                {
                    container_node* _PreOrderTraversalTest = _ROOT;
                    template_container::stack_a::stack<container_node*> stack_Temp;
                    stack_Temp.push(_PreOrderTraversalTest);
                    while( !stack_Temp.empty() )
                    {
                        _PreOrderTraversalTest = stack_Temp.top();
                        stack_Temp.pop();

                        temp++;

                        if(_PreOrderTraversalTest->_right != nullptr)
                        {
                            stack_Temp.push(_PreOrderTraversalTest->_right);
                        }
                        if(_PreOrderTraversalTest->_left != nullptr)
                        {
                            stack_Temp.push(_PreOrderTraversalTest->_left);
                        }
                    }
                }
                return temp;
            }
        public:
            using iterator = AVLTreeIterator<AVLSyntheticClass,AVLSyntheticClass&,AVLSyntheticClass*>;
            using const_iterator = AVLTreeIterator<AVLSyntheticClass,const AVLSyntheticClass&,const AVLSyntheticClass*>;

            using reverse_iterator = AVLTreeReverseIterator<iterator>;
            using const_reverse_iterator = AVLTreeReverseIterator<const_iterator>;

            iterator begin()                    
            {
                container_node* BeginTemp = _ROOT;
                while(BeginTemp != nullptr && BeginTemp->_left!= nullptr)
                {
                    BeginTemp = BeginTemp->_left;
                }
                return iterator(BeginTemp);
            }
            iterator end()
            {
                return iterator(nullptr);
            }
            const_iterator cbegin() const
            {
                container_node* BeginTemp = _ROOT;
                while(BeginTemp != nullptr && BeginTemp->_left!= nullptr)
                {
                    BeginTemp = BeginTemp->_left;
                }
                return const_iterator(BeginTemp);
            }
            const_iterator cend() const
            {
                return const_iterator(nullptr);
            }
            reverse_iterator rbegin()
            {
                container_node* RbeginTemp = _ROOT;
                while(RbeginTemp!= nullptr && RbeginTemp->_right!= nullptr)
                {
                    RbeginTemp = RbeginTemp->_right;
                }
                return reverse_iterator(iterator(RbeginTemp));
            }
            reverse_iterator rend()
            {
                return reverse_iterator(iterator(nullptr));
            }
            const_reverse_iterator crbegin() const
            {
                container_node* RbeginTemp = _ROOT;
                while(RbeginTemp!= nullptr && RbeginTemp->_right!= nullptr)
                {
                    RbeginTemp = RbeginTemp->_right;
                }
                return const_reverse_iterator(const_iterator(RbeginTemp));
            }
            const_reverse_iterator crend() const
            {
                return const_reverse_iterator(const_iterator(nullptr));
            }
            bool empty()
            {
                return _ROOT == nullptr;
            }
            AVLTree()
            {
                _ROOT = nullptr;
            }
            AVLTree(const AVLTreeTypeK& KeyTemp,const AVLTreeTypeV& ValTemp = AVLTreeTypeV(),
            CompareImitationFunctionsAVL com_temp = CompareImitationFunctionsAVL())
            :_ROOT(nullptr),com(com_temp)
            {
                _ROOT = new container_node(KeyTemp,ValTemp);
            }
            AVLTree(const AVLSyntheticClass& AVLTreePairTemp,
            CompareImitationFunctionsAVL com_temp = CompareImitationFunctionsAVL())
            :_ROOT(nullptr),com(com_temp)
            {
                _ROOT = new container_node(AVLTreePairTemp.first,AVLTreePairTemp.second);
            }
            AVLTree(const AVLTree& AVLTreeTemp)
            : _ROOT(nullptr), com(AVLTreeTemp.com)
            {
                if (AVLTreeTemp._ROOT == nullptr)
                {
                    return;
                }

                // 使用单栈，存储源节点和目标父节点（均为一级指针）
                template_container::stack_a::stack<template_container::practicality::pair<container_node*, container_node*>> stack;
                
                // 创建根节点
                _ROOT = new container_node(AVLTreeTemp._ROOT->_data);
                _ROOT->_BalanceFactor = AVLTreeTemp._ROOT->_BalanceFactor;
                _ROOT->_parent = nullptr; // 根节点的父节点为nullptr
                
                // 初始化栈，将根节点的子节点压入（注意：这里父节点是 _ROOT，一级指针）
                if (AVLTreeTemp._ROOT->_right != nullptr)
                {
                    stack.push(template_container::practicality::pair<container_node*, container_node*>(AVLTreeTemp._ROOT->_right, _ROOT));
                }
                if (AVLTreeTemp._ROOT->_left != nullptr)
                {
                    stack.push(template_container::practicality::pair<container_node*, container_node*>(AVLTreeTemp._ROOT->_left, _ROOT));
                }

                // 遍历并复制剩余节点
                while (!stack.empty())
                {
                    auto [SourceNode, parent_node] = stack.top();
                    stack.pop();
                    
                    // 创建新节点并复制数据
                    container_node* NewNode = new container_node(SourceNode->_data);
                    NewNode->_BalanceFactor = SourceNode->_BalanceFactor;
                    
                    // 设置父节点关系（注意：parent_node 是一级指针）
                    NewNode->_parent = parent_node;
                    
                    // 判断源节点在原树中是左子还是右子
                    bool IsLeftChild = false;
                    if (SourceNode->_parent != nullptr) 
                    {
                        IsLeftChild = (SourceNode->_parent->_left == SourceNode);
                    }
                    
                    // 将新节点链接到父节点的正确位置（注意：直接使用 parent_node）
                    if (IsLeftChild) 
                    {
                        parent_node->_left = NewNode;
                    } 
                    else 
                    {
                        parent_node->_right = NewNode;
                    }

                    // 处理子节点（注意：压栈时父节点是 new_node，一级指针）
                    if (SourceNode->_right != nullptr)
                    {
                        stack.push(template_container::practicality::pair<container_node*, container_node*>(SourceNode->_right, NewNode));
                    }
                    if (SourceNode->_left != nullptr)
                    {
                        stack.push(template_container::practicality::pair<container_node*, container_node*>(SourceNode->_left, NewNode));
                    }
                }
            }
            AVLTree(AVLTree&& AVLTreeTemp)
            : _ROOT(nullptr),com(AVLTreeTemp.com)
            {
                _ROOT = std::move(AVLTreeTemp._ROOT);
                AVLTreeTemp._ROOT = nullptr;
            }
            AVLTree& operator=(AVLTree&& AVLTreeTemp)
            {
                if(this != &AVLTreeTemp)
                {
                    clear();
                    _ROOT = std::move(AVLTreeTemp._ROOT);
                    com  = std::move(AVLTreeTemp.com);
                    AVLTreeTemp._ROOT = nullptr;
                }
            }
            AVLTree& operator=(const AVLTree AVLTreeTemp)
            {
                clear();
                if(&AVLTreeTemp == this)
                {
                    return *this;
                }
                if (AVLTreeTemp._ROOT == nullptr)
                {
                    return *this;
                }
                template_container::algorithm::swap(com,AVLTreeTemp.com);
                template_container::algorithm::swap(_ROOT,AVLTreeTemp._ROOT);
                return *this;
            }
            ~AVLTree()
            {
                //析构函数
                clear();
            }
            size_t size() const
            {
                return _size();
            }
            size_t size()
            {
                return _size();
            }
            void PreOrderTraversal()
            {
                _PreOrderTraversal(_ROOT);
            }
            void MiddleOrderTraversal()
            {
                _MiddleOrderTraversal(_ROOT);
            }
            bool push(const AVLTreeTypeK& KeyTemp,const AVLTreeTypeV& ValTemp = AVLTreeTypeV())
            {
                //插入
                if(_ROOT == nullptr)
                {
                    _ROOT = new container_node(KeyTemp,ValTemp);
                    return true;
                }
                else
                {
                    container_node* _ROOT_temp = _ROOT;
                    container_node* ROOT_Temp_Parent = nullptr;
                    while(_ROOT_temp)
                    {
                        ROOT_Temp_Parent = _ROOT_temp;
                        if(!com(KeyTemp,_ROOT_temp->_data.first) && !com(_ROOT_temp->_data.first,KeyTemp))
                        {
                            return false;
                        }
                        else if(com(KeyTemp,_ROOT_temp->_data.first))
                        {
                            _ROOT_temp = _ROOT_temp->_left;
                        }
                        else
                        {
                            _ROOT_temp = _ROOT_temp->_right;
                        }
                    }
                    _ROOT_temp = new container_node(KeyTemp,ValTemp);
                    if(com(KeyTemp,ROOT_Temp_Parent->_data.first))
                    {
                        ROOT_Temp_Parent->_left = _ROOT_temp;
                    }
                    else
                    {
                        ROOT_Temp_Parent->_right = _ROOT_temp;
                    }
                    _ROOT_temp->_parent = ROOT_Temp_Parent;

                    container_node* _ROOT_temp_test = _ROOT_temp;
                    container_node* _ROOT_temp_test_parent = ROOT_Temp_Parent;

                    while(_ROOT_temp_test_parent)
                    {
                        if(_ROOT_temp_test_parent->_left == _ROOT_temp_test)
                        {
                            _ROOT_temp_test_parent->_BalanceFactor--;
                        }
                        else
                        {
                            _ROOT_temp_test_parent->_BalanceFactor++;
                        }

                        if(_ROOT_temp_test_parent->_BalanceFactor == 0)
                        {
                            break;
                        }
                        else if (_ROOT_temp_test_parent->_BalanceFactor == 1 || _ROOT_temp_test_parent->_BalanceFactor == -1)
                        {
                            _ROOT_temp_test = _ROOT_temp_test_parent;
                            _ROOT_temp_test_parent = _ROOT_temp_test_parent->_parent;
                        }
                        else if (_ROOT_temp_test_parent->_BalanceFactor == 2 || _ROOT_temp_test_parent->_BalanceFactor == -2)
                        {
                            if(_ROOT_temp_test_parent->_BalanceFactor == 2)
                            {
                                if(_ROOT_temp_test->_BalanceFactor == 1)
                                {
                                    LeftRevolve(_ROOT_temp_test_parent);
                                }
                                else
                                {
                                    RightLeftRevolve(_ROOT_temp_test_parent);
                                }
                            }
                            if(_ROOT_temp_test_parent->_BalanceFactor == -2)
                            {
                                if(_ROOT_temp_test->_BalanceFactor == -1)
                                {
                                    RightRevolve(_ROOT_temp_test_parent);
                                }
                                else
                                {
                                    LeftRightRevolve(_ROOT_temp_test_parent);
                                }
                            }
                            _ROOT_temp_test = _ROOT_temp_test_parent;
                            _ROOT_temp_test_parent = _ROOT_temp_test_parent->_parent;
                        }
                    }
                }
                return true;
            }
            bool push(const AVLSyntheticClass& AVLTreePairTemp)
            {
                //AVL树左子树比右子树高，则他俩的根节点的平衡因子为1，反之为-1，也就是说左加一，右减一，如果根节点为2和-2就要需要调整了
                if(_ROOT == nullptr)
                {
                    _ROOT = new container_node(AVLTreePairTemp.first,AVLTreePairTemp.second);
                    return true;
                }
                else
                {
                    container_node* ROOT_Temp = _ROOT;
                    container_node* ROOT_Temp_Parent = nullptr;
                    while(ROOT_Temp != nullptr)
                    {
                        ROOT_Temp_Parent = ROOT_Temp;
                        //找到first该在的节点
                        if(!com(AVLTreePairTemp.first,ROOT_Temp->_data.first) && !com(ROOT_Temp->_data.first,AVLTreePairTemp.first))
                        {
                            //不允许重复插入
                            return false;
                        } 
                        else if(com(AVLTreePairTemp.first,ROOT_Temp->_data.first))
                        {
                            ROOT_Temp = ROOT_Temp->_left;
                        }
                        else
                        {
                            ROOT_Temp = ROOT_Temp->_right;
                        }
                    }
                    ROOT_Temp = new container_node(AVLTreePairTemp);
                    if(com(AVLTreePairTemp.first,ROOT_Temp_Parent->_data.first))
                    {
                        ROOT_Temp_Parent->_left = ROOT_Temp;
                        //三叉链表，注意父亲节点指向
                    }
                    else
                    {
                        ROOT_Temp_Parent->_right = ROOT_Temp;
                    }
                    ROOT_Temp->_parent = ROOT_Temp_Parent;
                    container_node* ROOTTempTest = ROOT_Temp;
                    container_node* _ROOT_Temp_test_parent = ROOT_Temp_Parent;
                    //更新平衡因子
                    while(_ROOT_Temp_test_parent)
                    {
                        //更新到根节点跳出
                        if(ROOTTempTest == _ROOT_Temp_test_parent->_right)
                        {
                            _ROOT_Temp_test_parent->_BalanceFactor++;
                        }
                        else
                        {
                            _ROOT_Temp_test_parent->_BalanceFactor--;
                        }

                        if(_ROOT_Temp_test_parent->_BalanceFactor == 0)
                        {
                            //平衡因子为0，无需平衡
                            break;
                        }
                        else if(_ROOT_Temp_test_parent->_BalanceFactor == 1 || _ROOT_Temp_test_parent->_BalanceFactor == -1)
                        {
                            ROOTTempTest = _ROOT_Temp_test_parent;
                            _ROOT_Temp_test_parent = _ROOT_Temp_test_parent->_parent;
                            //向上更新，直到找到0或-2或2
                        }
                        else if(_ROOT_Temp_test_parent->_BalanceFactor == 2 || _ROOT_Temp_test_parent->_BalanceFactor == -2)
                        {
                            //平衡因子为2或者-2，需要平衡
                            if(_ROOT_Temp_test_parent->_BalanceFactor == 2)
                            {
                                if(ROOTTempTest->_BalanceFactor == 1)
                                {
                                    //L，说明_ROOT_Temp_test是_ROOT_Temp_test_parent的左子节点，线形
                                    LeftRevolve(_ROOT_Temp_test_parent);
                                }
                                else
                                {
                                    //RL，证明_ROOT_Temp_test是_ROOT_Temp_test_parent的右子节点，在AVL树抽象图上就是折线型的
                                    RightLeftRevolve(_ROOT_Temp_test_parent);
                                }
                            }
                            else if (_ROOT_Temp_test_parent->_BalanceFactor == -2)
                            {
                                if(ROOTTempTest->_BalanceFactor == -1)
                                {
                                    //R，说明_ROOT_Temp_test是_ROOT_Temp_test_parent的右子节点，线形
                                    RightRevolve(_ROOT_Temp_test_parent);
                                }
                                else
                                {
                                    //LR，和上同理
                                    LeftRightRevolve(_ROOT_Temp_test_parent);
                                }
                            }
                            //旋转后继续向上调整，因为旋转后父节点的平衡因子可能发生变化，每个旋转的节点都可以当作一个子树，子树旋转后，父节点平衡因子可能发生变化
                            ROOTTempTest = _ROOT_Temp_test_parent;
                            _ROOT_Temp_test_parent = _ROOT_Temp_test_parent->_parent;
                            //对于双旋的情况，相同方向先调整该节点，再调整整体
                        }
                    }
                }
                return true;
            }
            container_node* find(const AVLTreeTypeK& DataTemp)
            {
                container_node* ROOT_Temp = _ROOT;
                while(ROOT_Temp != nullptr)
                {
                    if(ROOT_Temp->_data == DataTemp)
                    {
                        break;
                    }
                    else if (com(ROOT_Temp->_data,DataTemp))
                    {
                        ROOT_Temp = ROOT_Temp->_right;
                    }
                    else
                    {
                        ROOT_Temp = ROOT_Temp->_left;
                    }
                }
                return ROOT_Temp;
            }
            AVLTree& pop(const AVLTreeTypeK& DataTemp)
            {
                if(_ROOT == nullptr)
                {
                    return *this;
                }
                container_node* ROOT_Temp = _ROOT;
                container_node* ROOT_Temp_Parent = nullptr;
                while(ROOT_Temp != nullptr)
                {
                    if(!com(DataTemp,ROOT_Temp->_data.first) && !com(ROOT_Temp->_data.first,DataTemp))
                    {
                        break;
                    }
                    ROOT_Temp_Parent = ROOT_Temp;
                    if (com(ROOT_Temp->_data.first,DataTemp))
                    {
                        ROOT_Temp = ROOT_Temp->_right;
                    }
                    else
                    {
                        ROOT_Temp = ROOT_Temp->_left;
                    }
                }
                if(ROOT_Temp == nullptr)
                {
                    return *this;
                    //没有找到
                }
                //三种情况：左空，右空，左右都不空
                if (ROOT_Temp->_left == nullptr) 
                {
                    if (ROOT_Temp->_right != nullptr) 
                    {
                        ROOT_Temp->_right->_parent = ROOT_Temp_Parent;
                    }
                    if (ROOT_Temp_Parent == nullptr) 
                    {
                        _ROOT = ROOT_Temp->_right;
                    } 
                    else 
                    {
                        if (ROOT_Temp_Parent->_left == ROOT_Temp) 
                        {
                            ROOT_Temp_Parent->_left = ROOT_Temp->_right;
                        } 
                        else 
                        {
                            ROOT_Temp_Parent->_right = ROOT_Temp->_right;
                        }
                    }
                    delete ROOT_Temp;
                    ROOT_Temp = nullptr;
                }            
                else if (ROOT_Temp->_right == nullptr)
                {
                    if(ROOT_Temp->_left != nullptr)
                    {
                        ROOT_Temp->_left->_parent = ROOT_Temp_Parent;
                    }
                    if(ROOT_Temp_Parent == nullptr)
                    {
                        _ROOT = ROOT_Temp->_left;
                    }
                    else
                    {
                        if(ROOT_Temp_Parent->_left == ROOT_Temp)
                        {
                            ROOT_Temp_Parent->_left = ROOT_Temp->_left;
                        }
                        else
                        {
                            ROOT_Temp_Parent->_right = ROOT_Temp->_left; 
                        }
                        if(ROOT_Temp->_left!= nullptr)
                        {
                            ROOT_Temp->_left->_parent = ROOT_Temp_Parent;
                        }
                        //更新父节点
                    }
                    delete ROOT_Temp;
                    ROOT_Temp = nullptr;
                }
                else if(ROOT_Temp->_right != nullptr && ROOT_Temp->_left != nullptr)
                {
                    //找右子树最左节点
                    container_node* _right_min = ROOT_Temp->_right;
                    container_node* _right_parent = ROOT_Temp;
                    while(_right_min->_left != nullptr)
                    {
                        _right_parent = _right_min;
                        _right_min = _right_min->_left;
                    }
                    template_container::algorithm::swap(_right_min->_data,ROOT_Temp->_data);
                    if (_right_parent == ROOT_Temp) 
                    {
                        _right_parent->_right = (_right_min->_right != nullptr) ? _right_min->_right : nullptr;
                    } 
                    else 
                    {
                        _right_parent->_left = (_right_min->_right != nullptr) ? _right_min->_right : nullptr;
                    }
                    if (_right_min->_right != nullptr) 
                    {
                        _right_min->_right->_parent = _right_parent;
                    }
                    delete _right_min;
                    _right_min = nullptr;         
                }
                //更新平衡因子
                container_node* parent_BF = ROOT_Temp_Parent;
                while(parent_BF != nullptr)
                {
                    if(parent_BF->_left == ROOT_Temp)
                    {
                        parent_BF->_BalanceFactor--;
                    }
                    else
                    {
                        parent_BF->_BalanceFactor++;
                    }
                    if(parent_BF->_BalanceFactor == 0)
                    {
                        break;
                    }
                    else if(parent_BF->_BalanceFactor == 1 || parent_BF->_BalanceFactor == -1)
                    {
                        ROOT_Temp = parent_BF;
                        parent_BF = parent_BF->_parent;
                    }
                    else if(parent_BF->_BalanceFactor == 2 || parent_BF->_BalanceFactor == -2)
                    {
                        if(parent_BF->_BalanceFactor == 2)
                        {
                            if(ROOT_Temp->_BalanceFactor == 1)
                            {
                                LeftRevolve(parent_BF);
                            }
                            else
                            {
                                RightLeftRevolve(parent_BF);
                            }
                        }
                        else if(parent_BF->_BalanceFactor == -2)
                        {
                            if(ROOT_Temp->_BalanceFactor == -1)
                            {
                                RightRevolve(parent_BF);
                            }
                            else
                            {
                                LeftRightRevolve(parent_BF);
                            }
                        }
                        parent_BF = parent_BF->_parent;
                        ROOT_Temp = parent_BF;
                        //双旋的情况，先调整该节点，再调整整体
                    }
                }
                return *this;
            }
        };
    }
    /*############################     基类容器命名空间     ############################*/
    namespace base_class_c
    {
        /*############################     RBTree 容器     ############################*/
        template <typename RBTreeTypeKey, typename RBTreeTypeVal, typename DataExtractionFunction,
        typename CompareImitationFunctionsRB = template_container::imitation_functions::Less<RBTreeTypeKey> >
        class RBTree
        {
        private:
            enum RBTreeColor
            {
                RED,
                BLACK,
            };
            class RBTreeNode
            {
            public:
                RBTreeTypeVal _data;
                RBTreeNode* _left;
                RBTreeNode* _right;
                RBTreeNode* _parent;
                RBTreeColor _color;
                RBTreeNode(const RBTreeTypeVal& ValTemp = RBTreeTypeVal())
                :_data(ValTemp),_left(nullptr),_right(nullptr),_parent(nullptr),_color(RED)
                {
                    ;
                }
            };
            template<typename T, typename Ref, typename Ptr>
            class RBTreeiterator
            { 
                using Self = RBTreeiterator<T,Ref,Ptr>;
                using Node_iterator = RBTreeNode;
                Node_iterator* _Node;
            public:
                using reference = Ref;
                using pointer = Ptr;
                RBTreeiterator(Node_iterator* Node_temp_)
                :_Node(Node_temp_)
                {
                    ;
                }
                RBTreeiterator()
                {
                    _Node = nullptr;
                }
                Ref& operator*()
                {
                    return _Node->_data;
                }
                Ptr operator->()
                {
                    return &(_Node->_data);
                }
                Self& operator++()
                {
                    if(_Node == nullptr)
                    {
                        return *this;
                    }
                    if(_Node->_right != nullptr)
                    {
                        container_node* Sub = _Node->_right;
                        while(Sub->_left != nullptr)
                        {
                            Sub = Sub->_left;
                        }
                        _Node = Sub;
                    }
                    else
                    {
                        //代表右子树已经走完，需要向上遍历，继续向上找右子树，如果停下来，说明走完整棵树或者是走到根节点
                        Node_iterator* ParentTemp = _Node->_parent;
                        Node_iterator* SubTemp = _Node;
                        while(ParentTemp != nullptr && SubTemp == ParentTemp->_right)
                        {
                            SubTemp = ParentTemp;
                            ParentTemp = ParentTemp->_parent;
                        }
                        _Node = ParentTemp;
                        //如果跳出循环，说明走到了根节点，或者找到了右子树
                    }
                    return *this;
                }
                Self operator++(int)
                {
                    Self Temp = *this;
                    ++(*this);
                    return Temp;
                }
                Self& operator--()
                {
                    if(_Node->_left != nullptr)
                    {
                        Node_iterator* Sub = _Node->_left;
                        while(Sub->_right != nullptr)
                        {
                            Sub = Sub->_right;
                        }
                        _Node = Sub;
                    }
                    else
                    {
                        Node_iterator* ParentTemp = _Node->_parent;
                        Node_iterator* SubTemp = _Node;
                        while(ParentTemp != nullptr && SubTemp == ParentTemp->_left)
                        {
                            SubTemp = ParentTemp;
                            ParentTemp = ParentTemp->_parent;
                        }
                        _Node = ParentTemp;
                    }
                    return *this;
                }
                Self operator--(int)
                {
                    Self Temp = *this;
                    --(*this);
                    return Temp;
                }
                bool operator==(const Self& itTemp) const
                {
                    return _Node == itTemp._Node;
                }
                bool operator!=(const Self& itTemp) const
                {
                    return _Node != itTemp._Node;
                }
            };
            template <typename iterator>
            class RBTreeReverseIterator
            {
                using Self = RBTreeReverseIterator<iterator>;
                using Ref  = typename iterator::reference;
                using Ptr  = typename iterator::pointer;
                iterator _it;
            public:
                RBTreeReverseIterator(iterator itTemp)
                :_it(itTemp)
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
                RBTreeReverseIterator& operator++() 
                { 
                    --_it; 
                    return *this; 
                }
                RBTreeReverseIterator operator++(int) 
                { 
                    auto tmp = *this; 
                    --_it; 
                    return tmp; 
                }

                // 前置自减：对应正向迭代器的自增
                RBTreeReverseIterator& operator--() 
                { 
                    ++_it; 
                    return *this; 
                }
                RBTreeReverseIterator operator--(int) 
                { 
                    auto tmp = *this; 
                    ++_it; return tmp; 
                }

                // 比较运算符
                bool operator==(const RBTreeReverseIterator& other) const 
                { 
                    return _it == other._it; 
                }
                bool operator!=(const RBTreeReverseIterator& other) const 
                { 
                    return _it != other._it; 
                }
            };
            using container_node = RBTreeNode;
            container_node* _ROOT;
            DataExtractionFunction Element;
            CompareImitationFunctionsRB com;
            void LeftRevolve(container_node* ParentTempNode)
            {
                //传进来的值是发现该树平衡性被破坏的节点地址
                //大致思想：因为这是左单旋，所以找传进来的父亲节点的右根节点来当调整节点
                //然后把调整节点的左根节点赋值给传进来的父亲节点的右根节点 (刚才已经用节点保存过调整节点，所以这里直接赋值)，
                //再把父亲节点赋值给调整节点的左根节点，！！注意：在旋转的过程中还要处理每个调整节点的父亲节点的指向和平衡因子

                // {
                //     container_node* SubRightTemp = ParentTempNode->_right;
                //     ParentTempNode->_right = SubRightTemp->_left;
                //     SubRightTemp->_left = ParentTempNode;
                //     //错误写法：未同步调整父亲节点和判断调整节点的左根节点是否为空，以及全部需要调整节点的父亲指针的指针的指向
                // }
                if(ParentTempNode == nullptr|| ParentTempNode->_right == nullptr)
                {
                    std::cout <<"left "<< "空指针"  <<std::endl;
                    return ;
                }
                container_node* SubRightTemp = ParentTempNode->_right;
                // container_node* SubRightLeftTemp = SubRightTemp->_left;
                container_node* SubRightLeftTemp = (SubRightTemp->_left)? SubRightTemp->_left : nullptr;
                //防止空指针解引用
                ParentTempNode->_right = SubRightLeftTemp;
                if(SubRightLeftTemp)
                {
                    SubRightLeftTemp->_parent = ParentTempNode;
                    //如果Sub_right_left_temp(调整节点的左根节点)不等于空，还需要调整Sub_right_left_temp它的父亲节点
                }
                SubRightTemp->_left = ParentTempNode;
                //这里先保存一下parent_temp_Node的父亲地址，防止到下面else比较的时候丢失
                container_node* ParentParentTempNode = ParentTempNode->_parent;
                ParentTempNode->_parent = SubRightTemp;
                //更新parent_temp_Node节点指向正确的地址

                if(_ROOT == ParentTempNode)
                {
                    //如果要调整的节点是根根节点，直接把调整节点赋值给根节点，然后把调整节点的父亲节点置空
                    _ROOT = SubRightTemp;
                    SubRightTemp->_parent = nullptr;
                }
                else
                {
                    //调整前parent_temp_Node是这个树的根现在是Sub_right_temp是这个树的根
                    if(ParentParentTempNode->_left == ParentTempNode)
                    {
                        ParentParentTempNode->_left = SubRightTemp;
                    }
                    else
                    {
                        ParentParentTempNode->_right = SubRightTemp;
                    }
                    SubRightTemp->_parent = ParentParentTempNode;
                }
            }
            void RightRevolve(container_node*& ParentTempNode)
            {
                //思路同左单旋思路差不多,但是相反
                if(ParentTempNode == nullptr|| ParentTempNode->_left == nullptr)
                {
                    std::cout <<"right "<< "空指针"  <<std::endl; 
                    return ;
                }
                container_node* SubLeftTemp = ParentTempNode->_left;
                container_node* SubLeftRightTemp = (SubLeftTemp->_right) ? SubLeftTemp->_right : nullptr;
                //防止空指针解引用
                ParentTempNode->_left = SubLeftRightTemp;
                if(SubLeftRightTemp)
                {
                    SubLeftRightTemp->_parent = ParentTempNode;
                }
                SubLeftTemp->_right = ParentTempNode;
                //保存parent_temp_Node的父亲节点
                container_node* ParentParentTempNode = ParentTempNode->_parent;
                ParentTempNode->_parent = SubLeftTemp;

                if(_ROOT == ParentTempNode)
                {
                    _ROOT = SubLeftTemp;
                    SubLeftTemp->_parent = nullptr;
                }
                else
                {
                    if(ParentParentTempNode->_left == ParentTempNode)
                    {
                        ParentParentTempNode->_left = SubLeftTemp;
                    }
                    else
                    {
                        ParentParentTempNode->_right = SubLeftTemp;
                    }
                    SubLeftTemp->_parent = ParentParentTempNode;
                }
            }
            void clear(container_node* _clear_Temp)
            {
                if(_clear_Temp == nullptr)
                {
                    return ;
                }
                else
                {
                    template_container::stack_a::stack<container_node*> _stack;
                    _stack.push(_clear_Temp);
                    while ( !_stack.empty() )
                    {
                        _clear_Temp = _stack.top();
                        _stack.pop();
                        if(_clear_Temp->_right != nullptr)
                        {
                            _stack.push(_clear_Temp->_right);
                        }
                        if(_clear_Temp->_left  != nullptr)
                        {
                            _stack.push(_clear_Temp->_left);
                        }
                        delete _clear_Temp;
                    }
                    _ROOT = nullptr;
                }
            }
            void _MiddleOrderTraversal(container_node* ROOT_Temp)
            {
                //中序遍历函数
                template_container::stack_a::stack<container_node*> stack_type_data;
                while(ROOT_Temp != nullptr || !stack_type_data.empty())
                {
                    while(ROOT_Temp!= nullptr)
                    {
                        stack_type_data.push(ROOT_Temp);
                        ROOT_Temp = ROOT_Temp->_left;
                    }
                    ROOT_Temp = stack_type_data.top();
                    stack_type_data.pop();
                    std::cout <<  ROOT_Temp->_data << " ";
                    // std::cout << ROOT_Temp->_color <<" ";
                    ROOT_Temp = ROOT_Temp->_right;
                }
            }
            void _PreOrderTraversal(container_node* ROOT_Temp )
            {
                //前序遍历，最外左子树全部压栈
                if(ROOT_Temp == nullptr)
                {
                    return;
                }
                container_node* _PreOrderTraversalTest = ROOT_Temp;
                template_container::stack_a::stack<container_node*> stack_Temp;
                stack_Temp.push(_PreOrderTraversalTest);
                while( !stack_Temp.empty() )
                {
                    _PreOrderTraversalTest = stack_Temp.top();
                    stack_Temp.pop();

                    std::cout << _PreOrderTraversalTest->_data << " ";
                    // std::cout << _PreOrderTraversalTest->_color <<" ";
                    //修改逻辑错误，先压右子树再压左子树，因为这是栈
                    if(_PreOrderTraversalTest->_right != nullptr)
                    {
                        stack_Temp.push(_PreOrderTraversalTest->_right);
                    }
                    if(_PreOrderTraversalTest->_left != nullptr)
                    {
                        stack_Temp.push(_PreOrderTraversalTest->_left);
                    }
                }
            }
            static inline RBTreeColor Get_color(container_node* cur)
            {
                return cur == nullptr ? BLACK : cur->_color;
            }
            static inline bool RED_Get(container_node* cur)
            {
                return Get_color(cur) == RED;
            }
            static inline bool BLACK_Get(container_node* cur)
            {
                return Get_color(cur) == BLACK;
            }
            size_t _size() const 
            {
                size_t size = 0;
                container_node* ROOT_Temp = _ROOT;
                if(ROOT_Temp == nullptr)
                {
                    return size;
                }
                container_node* _PreOrderTraversalTest = ROOT_Temp;
                template_container::stack_a::stack<container_node*> stack_Temp;
                stack_Temp.push(_PreOrderTraversalTest);
                while( !stack_Temp.empty() )
                {
                    _PreOrderTraversalTest = stack_Temp.top();
                    stack_Temp.pop();

                    size++;
                    if(_PreOrderTraversalTest->_right != nullptr)
                    {
                        stack_Temp.push(_PreOrderTraversalTest->_right);
                    }
                    if(_PreOrderTraversalTest->_left != nullptr)
                    {
                        stack_Temp.push(_PreOrderTraversalTest->_left);
                    }
                }
                return size;
            }
        public:
            using iterator = RBTreeiterator<RBTreeTypeVal,RBTreeTypeVal&,RBTreeTypeVal*>; 
            using const_iterator =  RBTreeiterator<RBTreeTypeVal const,RBTreeTypeVal const&,RBTreeTypeVal const*>;

            using reverse_iterator = RBTreeReverseIterator<iterator>;
            using const_reverse_iterator = RBTreeReverseIterator<const_iterator>;

            using insert_result = template_container::practicality::pair<iterator,bool>;
            RBTree()
            {
                _ROOT = nullptr;
            }
            RBTree(const RBTreeTypeVal& RBTreeTemp)
            {
                _ROOT = new container_node(RBTreeTemp);
                _ROOT->_color = BLACK;
            }
            RBTree(RBTree&& RBTreeTemp)
            :com(RBTreeTemp.com),Element(RBTreeTemp.Element)
            {
                _ROOT = std::move(RBTreeTemp._ROOT);
                RBTreeTemp._ROOT = nullptr;
            }
            RBTree(const RBTree& RBTreeTemp)
            :com(RBTreeTemp.com),Element(RBTreeTemp.Element)
            {
                if(_ROOT != nullptr)
                {
                    clear(_ROOT);
                }
                else
                {
                    _ROOT = nullptr;
                    if(RBTreeTemp._ROOT == nullptr)
                    {
                        _ROOT = nullptr;
                    }
                    else
                    {
                        // 使用单栈，存储源节点和目标父节点（均为一级指针）
                        template_container::stack_a::stack<template_container::practicality::pair<container_node*, container_node*>> stack;
                        
                        // 创建根节点
                        _ROOT = new container_node(RBTreeTemp._ROOT->_data);
                        _ROOT->_color = RBTreeTemp._ROOT->_color;
                        _ROOT->_parent = nullptr; // 根节点的父节点为nullptr
                        
                        // 初始化栈，将根节点的子节点压入（注意：这里父节点是 _ROOT，一级指针）
                        if (RBTreeTemp._ROOT->_right != nullptr)
                        {
                            stack.push(template_container::practicality::pair<container_node*, container_node*>(RBTreeTemp._ROOT->_right, _ROOT));
                        }
                        if (RBTreeTemp._ROOT->_left != nullptr)
                        {
                            stack.push(template_container::practicality::pair<container_node*, container_node*>(RBTreeTemp._ROOT->_left, _ROOT));
                        }

                        // 遍历并复制剩余节点
                        while (!stack.empty())
                        {
                            auto [SourceNode, parent_node] = stack.top();
                            stack.pop();
                            
                            // 创建新节点并复制数据
                            container_node* NewNode = new container_node(SourceNode->_data);
                            NewNode->_color = SourceNode-> _color;
                            
                            // 设置父节点关系（注意：parent_node 是一级指针）
                            NewNode->_parent = parent_node;
                            
                            // 判断源节点在原树中是左子还是右子
                            bool IsLeftChild = false;
                            if (SourceNode->_parent != nullptr) 
                            {
                                IsLeftChild = (SourceNode->_parent->_left == SourceNode);
                            }
                            
                            // 将新节点链接到父节点的正确位置（注意：直接使用 parent_node）
                            if (IsLeftChild) 
                            {
                                parent_node->_left = NewNode;
                            } 
                            else 
                            {
                                parent_node->_right = NewNode;
                            }

                            // 处理子节点（注意：压栈时父节点是 new_node，一级指针）
                            if (SourceNode->_right != nullptr)
                            {
                                stack.push(template_container::practicality::pair<container_node*, container_node*>(SourceNode->_right, NewNode));
                            }
                            if (SourceNode->_left != nullptr)
                            {
                                stack.push(template_container::practicality::pair<container_node*, container_node*>(SourceNode->_left, NewNode));
                            }
                        }
                    }
                }
            }
            RBTree& operator=(const RBTree RBTreeTemp)
            {
                if(this == &RBTreeTemp)
                {
                    return *this;
                }
                else
                {
                    clear(_ROOT);
                    template_container::algorithm::swap(RBTreeTemp._ROOT,_ROOT);
                    template_container::algorithm::swap(RBTreeTemp.Element,Element);
                    template_container::algorithm::swap(RBTreeTemp.com,com);
                    return *this;
                }
            }
            RBTree& operator=(RBTree&& RBTreeTemp)
            {
                if(this != &RBTreeTemp)
                {
                    clear();
                    com = std::move(RBTreeTemp.com);
                    Element = std::move(RBTreeTemp.Element);
                    _ROOT = std::move(RBTreeTemp._ROOT);
                    RBTreeTemp._ROOT = nullptr;
                }
                return *this;
            }
            ~RBTree()
            {
                clear(_ROOT);
            }
            insert_result push(const RBTreeTypeVal& Val_Temp_)
            {
                if(_ROOT == nullptr)
                {
                    _ROOT = new container_node(Val_Temp_);
                    _ROOT->_color = BLACK;
                    return insert_result(iterator(_ROOT),true);
                }
                else
                {
                    container_node* ROOT_Temp = _ROOT;
                    container_node* ROOT_Temp_Parent = nullptr;
                    while(ROOT_Temp != nullptr)
                    {
                        ROOT_Temp_Parent = ROOT_Temp;
                        if(!com(Element(ROOT_Temp->_data),Element(Val_Temp_)) && !com(Element(Val_Temp_),Element(ROOT_Temp->_data)))
                        {
                            //插入失败，找到相同的值，开始返回
                            return insert_result(iterator(ROOT_Temp),false);
                        }
                        else if(com(Element(ROOT_Temp->_data),Element(Val_Temp_)))
                        {
                            ROOT_Temp = ROOT_Temp->_right;
                        }
                        else
                        {
                            ROOT_Temp = ROOT_Temp->_left;
                        }
                    }
                    //找到插入位置
                    ROOT_Temp = new container_node(Val_Temp_);
                    if(com(Element(ROOT_Temp_Parent->_data),Element(ROOT_Temp->_data)))
                    {
                        ROOT_Temp_Parent->_right = ROOT_Temp;
                    }
                    else
                    {
                        ROOT_Temp_Parent->_left = ROOT_Temp;
                    }
                    ROOT_Temp->_color = RED;
                    ROOT_Temp->_parent = ROOT_Temp_Parent;
                    container_node* Return_Node_Push = ROOT_Temp;
                    //保存节点
                    //开始调整，向上调整颜色节点
                    while(ROOT_Temp_Parent != nullptr && ROOT_Temp_Parent->_color == RED )
                    {
                        container_node* ROOT_Temp_Grandfther = ROOT_Temp_Parent->_parent;
                        if(ROOT_Temp_Grandfther->_left == ROOT_Temp_Parent)
                        {
                            //叔叔节点
                            // std::cout << "push" <<" ";
                            container_node* Uncle = ROOT_Temp_Grandfther->_right;
                            //情况1：uncle存在，且为红
                            //情况2: uncle不存在，那么_ROOT_Temp就是新增节点
                            //情况3：uncle存在且为黑，说明_ROOT_Temp不是新增节点
                            if(Uncle && Uncle->_color == RED)
                            {
                                //情况1：
                                ROOT_Temp_Parent->_color = Uncle->_color = BLACK;
                                ROOT_Temp_Grandfther->_color = RED;
                                //颜色反转完成
                                ROOT_Temp = ROOT_Temp_Grandfther;
                                ROOT_Temp_Parent = ROOT_Temp->_parent;
                                //向上调整,继续从红色节点开始
                            }
                            else
                            {
                                //情况3：该情况双旋转单旋
                                if(ROOT_Temp == ROOT_Temp_Parent->_right)
                                {
                                    LeftRevolve(ROOT_Temp_Parent);
                                    template_container::algorithm::swap(ROOT_Temp,ROOT_Temp_Parent);
                                    // ROOT_Temp = ROOT_Temp_Parent;
                                    //折线调整，交换位置调整为情况2
                                }
                                //情况2：直接单旋
                                RightRevolve(ROOT_Temp_Grandfther);
                                ROOT_Temp_Grandfther->_color = RED;
                                ROOT_Temp_Parent->_color = BLACK;
                            }
                        }
                        else
                        {
                            container_node* Uncle = ROOT_Temp_Grandfther->_left;
                            //与上面相反
                            if(Uncle && Uncle->_color == RED)
                            {
                                //情况1：
                                ROOT_Temp_Parent->_color = Uncle->_color = BLACK;
                                ROOT_Temp_Grandfther->_color = RED;
                                //颜色反转完成
                                ROOT_Temp = ROOT_Temp_Grandfther;
                                ROOT_Temp_Parent = ROOT_Temp->_parent;
                            }
                            else
                            {
                                //情况3：该情况双旋转单旋
                                if(ROOT_Temp == ROOT_Temp_Parent->_left)
                                {
                                    RightRevolve(ROOT_Temp_Parent);
                                    template_container::algorithm::swap(ROOT_Temp,ROOT_Temp_Parent);
                                    // ROOT_Temp = ROOT_Temp_Parent;
                                    //交换指针转换为单旋
                                }
                                //情况2：单旋
                                LeftRevolve(ROOT_Temp_Grandfther);
                                ROOT_Temp_Grandfther->_color = RED;
                                ROOT_Temp_Parent->_color = BLACK;
                            }
                        }
                    }
                    _ROOT->_color = BLACK;
                    return insert_result(iterator(Return_Node_Push),true);
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
            void DeleteAdjust(container_node* cur ,container_node* parent)
            {
                //cur为被删节点的替代节点
                if(cur == nullptr && parent == nullptr)
                {
                    return;
                }
                while(cur != _ROOT && (cur == nullptr || BLACK_Get(cur)))
                {
                    if(cur == _ROOT)
                    {
                        break;
                    }
                    if(parent->_left == cur)
                    {
                        container_node* brother = parent->_right;
                        if(RED_Get(brother))
                        {
                            //情况1：兄弟节点为红
                            brother->_color = BLACK;
                            parent->_color = RED;
                            LeftRevolve(parent);
                            //调整后，兄弟节点为黑
                            //继续向下调整
                            brother = parent->_right;
                        }
                        if( (brother != nullptr && BLACK_Get(brother))  && ( brother->_left == nullptr || (brother->_left)) && 
                        (brother->_right == nullptr || BLACK_Get(brother->_right)))
                        {
                            //情况2：兄弟节点为黑，且兄弟节点两个子节点都为黑
                            brother->_color = RED;
                            cur = parent;
                            parent = cur->_parent;
                            if(cur->_color == RED)
                            {
                                cur->_color = BLACK;
                                break;
                            }
                        }
                        else if( (brother != nullptr && BLACK_Get(brother)) &&  (brother->_right == nullptr || BLACK_Get(brother->_right)) && 
                        (brother->_left != nullptr && RED_Get(brother->_left)) )
                        {
                            //情况3：兄弟节点为黑，兄弟节点左节点为红，右节点为黑
                            brother->_left->_color = BLACK;
                            brother->_color = RED;
                            RightRevolve(brother);
                            //调整后，兄弟节点为黑，兄弟节点右节点为红
                            //继续向下调整
                            brother = parent->_right;
                        }
                        else if( (brother != nullptr ||BLACK_Get(brother))  && (brother->_right != nullptr && RED_Get(brother->_right)) )
                        {
                            //情况4：兄弟节点为黑，兄弟节点右节点为红
                            brother->_color = parent->_color;
                            parent->_color = BLACK;
                            brother->_right->_color = BLACK;
                            LeftRevolve(parent);
                            cur = _ROOT;
                            parent = cur->_parent;
                        }
                    }
                    else
                    {
                        container_node* brother = parent->_left;
                        if(RED_Get(brother))
                        {
                            //情况1：兄弟节点为红
                            brother->_color = BLACK;
                            parent->_color = RED;
                            RightRevolve(parent);
                            //调整后，兄弟节点为黑
                            brother = parent->_left;
                        }
                        if( brother != nullptr && BLACK_Get(brother) && (brother->_left == nullptr || BLACK_Get(brother->_left)) &&
                        (brother->_right == nullptr || BLACK_Get(brother->_right)) )
                        {
                            //情况2：兄弟节点为黑，且兄弟节点两个子节点都为黑
                            brother->_color = RED;
                            cur = parent;
                            parent = cur->_parent;
                            if(cur->_color == RED)
                            {
                                cur->_color = BLACK;
                                break;
                            }
                        }
                        else if (brother != nullptr && BLACK_Get(brother) && (brother->_right != nullptr && RED_Get(brother->_right)) &&
                        (brother->_left == nullptr || BLACK_Get(brother->_left)) )
                        {
                            //情况3：兄弟节点为黑，兄弟节点左节点为红，右节点为黑
                            brother->_right->_color = BLACK;
                            brother->_color = RED;
                            LeftRevolve(brother);
                            //调整后，兄弟节点为黑，兄弟节点右节点为红
                            //继续向下调整
                            brother = parent->_left;
                        }
                        else if(brother != nullptr && BLACK_Get(brother) && brother->_left != nullptr && RED_Get(brother->_left))
                        {
                            //情况4：兄弟节点为黑，兄弟节点右节点为红
                            brother->_color = parent->_color;
                            parent->_color = BLACK;
                            brother->_left->_color = BLACK;
                            RightRevolve(parent);
                            cur = _ROOT;
                            parent = cur->_parent;
                        }
                    }
                }
                if(cur != nullptr)
                {
                    cur->_color = BLACK;
                }
            }
            insert_result pop(const RBTreeTypeVal& RBTreeTemp)
            {
                RBTreeColor DeleteColor;
                if(_ROOT == nullptr)
                {
                    return insert_result(iterator(nullptr),false);
                }
                else
                {
                    container_node* ROOT_Temp = _ROOT;
                    container_node* ROOT_Temp_Parent = nullptr;
                    container_node* AdjustNode = nullptr;
                    container_node* AdjustNodeParent = nullptr;
                    while(ROOT_Temp != nullptr)
                    {
                        if(!com(Element(ROOT_Temp->_data),Element(RBTreeTemp)) && !com(Element(RBTreeTemp),Element(ROOT_Temp->_data)))
                        {
                            break;
                        }
                        //防止父亲自赋值
                        ROOT_Temp_Parent = ROOT_Temp;
                        if(com(Element(ROOT_Temp->_data),Element(RBTreeTemp)))
                        {
                            ROOT_Temp = ROOT_Temp->_right;
                        }
                        else
                        {
                            ROOT_Temp = ROOT_Temp->_left;
                        }
                    }
                    if(ROOT_Temp == nullptr )
                    {
                        return insert_result(iterator(nullptr),false);
                    }
                    //找到位置开始删除
                    DeleteColor = ROOT_Temp->_color;
                    if(ROOT_Temp->_left == nullptr)
                    {
                        if(ROOT_Temp->_right != nullptr)
                        {
                            //右节点有值
                            ROOT_Temp->_right->_parent = ROOT_Temp_Parent;
                        }
                        if(ROOT_Temp_Parent == nullptr)
                        {
                            //根节点
                            _ROOT = ROOT_Temp->_right;
                        }
                        else
                        {
                            //不为空，代表要删除的数不是在根节点上
                            if(ROOT_Temp_Parent->_left == ROOT_Temp)
                            {
                                ROOT_Temp_Parent->_left = ROOT_Temp->_right;
                            }
                            else
                            {
                                ROOT_Temp_Parent->_right = ROOT_Temp->_right;
                            }
                        }
                        AdjustNode = ROOT_Temp->_right;
                        AdjustNodeParent = ROOT_Temp_Parent;
                        delete ROOT_Temp;
                        ROOT_Temp = nullptr;
                    }
                    else if (ROOT_Temp->_right == nullptr)
                    {
                        if(ROOT_Temp->_left != nullptr)
                        {
                            ROOT_Temp->_left->_parent = ROOT_Temp_Parent;
                            //链接父节点
                        }
                        if(ROOT_Temp_Parent == nullptr)
                        {
                            //与上同理
                            _ROOT = ROOT_Temp->_left;
                        }
                        else
                        {
                            if(ROOT_Temp_Parent->_left == ROOT_Temp)
                            {
                                ROOT_Temp_Parent->_left = ROOT_Temp->_left;
                            }
                            else
                            {
                                ROOT_Temp_Parent->_right = ROOT_Temp->_left;
                            }
                        }
                        AdjustNode = ROOT_Temp->_left;
                        AdjustNodeParent = ROOT_Temp_Parent;
                        delete ROOT_Temp;
                        ROOT_Temp = nullptr;
                    }
                    else if(ROOT_Temp->_right != nullptr && ROOT_Temp->_left != nullptr)
                    {
                        container_node* _right_min = ROOT_Temp->_right;
                        container_node* _right_parent = ROOT_Temp;
                        while(_right_min->_left != nullptr)
                        {
                            _right_parent = _right_min;
                            _right_min = _right_min->_left;
                        }
                        DeleteColor = _right_min->_color;

                        // 交换数据 AND 交换颜色
                        template_container::algorithm::swap(_right_min->_data,  ROOT_Temp->_data);
                        template_container::algorithm::swap(_right_min->_color, ROOT_Temp->_color);

                        // 然后正确地把后继节点的位置接到它父节点上：
                        if (_right_parent->_left == _right_min) 
                        {
                            _right_parent->_left  = _right_min->_right;
                        }
                        else 
                        {
                            _right_parent->_right = _right_min->_right;
                        }
                        if (_right_min->_right) 
                        {
                            _right_min->_right->_parent = _right_parent;
                        }
                        AdjustNode        = _right_min->_right;
                        AdjustNodeParent = _right_parent;

                        // 最后再 delete 那个后继节点
                        delete _right_min;
                        _right_min = nullptr;
                    }
                    //更新颜色
                    if( DeleteColor == BLACK )
                    {
                        //删除红色节点不影响性质
                        DeleteAdjust(AdjustNode,AdjustNodeParent);
                    }
                    if(_ROOT != nullptr)
                    {
                        _ROOT->_color = BLACK;
                    }
                    return insert_result(iterator(nullptr),false);
                }
            }
            iterator find(const RBTreeTypeVal& RB_Tree_Temp_)
            {
                if(_ROOT == nullptr)
                {
                    return iterator(nullptr);
                }
                else
                {
                    container_node* iterator_ROOT = _ROOT;
                    while(iterator_ROOT != nullptr)
                    {
                       if(!com(Element(iterator_ROOT->_data),Element(RB_Tree_Temp_)))
                       {
                           return iterator(iterator_ROOT);
                       }
                       else if(com(Element(iterator_ROOT->_data),Element(RB_Tree_Temp_)))
                       {
                           iterator_ROOT = iterator_ROOT->_right;
                       }
                       else
                       {
                           iterator_ROOT = iterator_ROOT->_left;
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
                return _ROOT == nullptr;
            }
            void MiddleOrderTraversal()
            {
                _MiddleOrderTraversal(_ROOT);
            }
            void PreOrderTraversal()
            {
                _PreOrderTraversal(_ROOT);
            }
            iterator begin()
            {
                container_node* iterator_ROOT = _ROOT;
                while(iterator_ROOT != nullptr &&  iterator_ROOT->_left != nullptr)
                {
                    iterator_ROOT = iterator_ROOT->_left;
                }
                return iterator(iterator_ROOT);
            }
            iterator end()
            {
                return iterator(nullptr);
            }
            const_iterator cbegin() const
            {
                container_node* iterator_ROOT = _ROOT;
                while(iterator_ROOT != nullptr &&  iterator_ROOT->_left != nullptr)
                {
                    iterator_ROOT = iterator_ROOT->_left;
                }
                return const_iterator(iterator_ROOT);
            }
            const_iterator cend() const
            {
                return const_iterator(nullptr);
            }
            reverse_iterator rbegin()
            {
                container_node* iterator_Node = _ROOT;
                while(iterator_Node != nullptr && iterator_Node->_right != nullptr)
                {
                    iterator_Node = iterator_Node->_right;
                }
                return reverse_iterator(iterator_Node);
            }
            reverse_iterator rend()
            {
                return reverse_iterator(nullptr);
            }
            const_reverse_iterator crbegin() const
            {
                container_node* iterator_Node = _ROOT;
                while(iterator_Node!= nullptr && iterator_Node->_right!= nullptr)
                {
                    iterator_Node = iterator_Node->_right;
                }
                return const_reverse_iterator(iterator_Node);
            }
            const_reverse_iterator crend() const
            {
                return const_reverse_iterator(nullptr);
            }
            iterator operator[](const RBTreeTypeVal& RBTreeTemp)
            {
                return find(RBTreeTemp);
            }
        };
        /*############################     hash 容器     ############################*/
        template <typename HashTableTypeKey, typename HashTableTypeVal,typename DataExtractionFunction,
        typename HashTableFunction = std::hash<HashTableTypeVal> >
        class HashTable
        {
            class HashTableNode
            {
            public:
                HashTableTypeVal _data;
                HashTableNode* _next;
                HashTableNode* LinkPrev;
                //全局链表指针，方便按照插入的顺序有序遍历哈希表
                HashTableNode* LinkNext;
                HashTableNode(const HashTableTypeVal& TempVal)
                {
                    _data = TempVal;
                    _next = nullptr;
                    LinkPrev = nullptr;
                    LinkNext = nullptr;
                }
            };
            using container_node = HashTableNode;
            DataExtractionFunction HashDataFunctor;                   //仿函数
            size_t _size;                                             //哈希表大小
            size_t LoadFactor;                                        //负载因子   
            size_t Capacity;                                          //哈希表容量
            template_container::vector_c::vector<container_node*> _HashTable;    //哈希表
            HashTableFunction hash_function;                           //哈希函数
            container_node* PreviousData = nullptr;                             //上一个数据
            container_node* HeadData = nullptr;                                 //插入头数据
            template <typename Hash_Table_iterator_Key, typename Hash_Table_iterator_Val>
            class Hash_iterator
            {
                using iterator_Node = container_node;
                using Ref  = Hash_Table_iterator_Val&;
                using Ptr  = Hash_Table_iterator_Val*;
                using Self = Hash_iterator<Hash_Table_iterator_Key,Hash_Table_iterator_Val>;
                iterator_Node* HashTableIteratorNode;
            public:
                Hash_iterator(iterator_Node* Temp_Node)      {      HashTableIteratorNode = Temp_Node;        }
                Ref operator*()                              {      return HashTableIteratorNode->_data;      }
                Ptr operator->()                             {      return &HashTableIteratorNode->_data;     }
                Self operator++()                            {      HashTableIteratorNode = HashTableIteratorNode->LinkNext;     return *this;     }
                bool operator!=(const Self& TempSelf)        {      return HashTableIteratorNode != TempSelf.HashTableIteratorNode;     }
                bool operator==(const Self& TempSelf)        {      return HashTableIteratorNode == TempSelf.HashTableIteratorNode;     }
                Self operator++(int)                         
                {       
                    Self TempSelf = *this;
                    HashTableIteratorNode = HashTableIteratorNode->LinkNext;
                    return TempSelf;
                }
            };
            void parentJudgment(container_node*& TempNodeParent,container_node*& _TempNode,size_t& HashLocationData)
            {
                if(TempNodeParent!= nullptr)
                {
                    //父亲节点不为空，防止空指针错误
                    TempNodeParent->_next = _TempNode->_next;
                }
                else
                {
                    //父亲节点为空，直接将映射位置置空
                    _HashTable[HashLocationData] = nullptr;
                }
            } 
        public:  
            using iterator = Hash_iterator<HashTableTypeKey,HashTableTypeVal>;
            using const_iterator = Hash_iterator<const HashTableTypeKey,const HashTableTypeVal>;
            HashTable()
            {
                _size = 0;
                LoadFactor = 7;
                Capacity = 10;
                _HashTable.resize(Capacity);
            }
            HashTable(size_t TempCapacity)
            {
                _size = 0;
                LoadFactor = 7;
                Capacity = TempCapacity;
                _HashTable.resize(Capacity);
            }
            HashTable(const HashTable& TempHashTable)
            : HashDataFunctor(TempHashTable.HashDataFunctor),_size(TempHashTable._size),LoadFactor(TempHashTable.LoadFactor),Capacity(TempHashTable.Capacity),
            DataExtractionFunction(TempHashTable.DataExtractionFunction),PreviousData(nullptr),   HeadData(nullptr)
            {
                if (Capacity == 0) 
                {
                    return;
                }
                // 1. 分配同样大小的桶数组，所有桶初始为空
                _HashTable.resize(Capacity, nullptr);
        
                // 2. 遍历原表的每一个桶
                for (size_t i = 0; i < Capacity; ++i) 
                {
                    container_node* SrcBucketNode = TempHashTable._HashTable[i];
                    // 桶内新表的尾节点（用于串联 _next）
                    container_node* last_in_bucket = nullptr;
        
                    // 逐节点深拷贝
                    while (SrcBucketNode) 
                    {
                        // 2.1 创建新节点并拷贝数据
                        container_node* NewNode = new container_node(SrcBucketNode->_data);
                        // 2.2 插入到“桶内部”链表
                        if (last_in_bucket != nullptr) 
                        {
                            last_in_bucket->_next = NewNode;
                        } 
                        else 
                        {
                            _HashTable[i] = NewNode;
                        }
                        last_in_bucket = NewNode;
        
                        // 2.3 插入到“全局插入
                        if(PreviousData != nullptr)
                        {
                            PreviousData->LinkNext = NewNode;
                            NewNode->LinkPrev = PreviousData;
                        } 
                        else 
                        {
                            // 第一个节点就是全局链表的头
                            HeadData = NewNode;
                        }
                        PreviousData = NewNode;
        
                        // 继续下一个源节点
                        SrcBucketNode = SrcBucketNode->_next;
                    }
                }
                if(PreviousData != nullptr)
                {
                    PreviousData->LinkNext = nullptr;
                }
            }
            HashTable(HashTable&& TempHashTable)
            {
                _HashTable = std::move(TempHashTable._HashTable);
                _size = std::move(TempHashTable._size);
                LoadFactor = std::move(TempHashTable.LoadFactor);
                Capacity = std::move(TempHashTable.Capacity);
                hash_function= std::move(TempHashTable.DataExtractionFunction);
                PreviousData = std::move(TempHashTable.PreviousData);
                HeadData = std::move(TempHashTable.HeadData);
                HashDataFunctor = std::move(TempHashTable.HashDataFunctor);
            }
            ~HashTable()
            {
                for(size_t i = 0;i < _HashTable.size();++i)
                {
                    container_node* _TempNode = _HashTable[i];
                    while(_TempNode != nullptr)
                    {
                        container_node* _Temp_Node_prev = _TempNode;
                        _TempNode = _TempNode->_next;
                        delete _Temp_Node_prev;
                        _Temp_Node_prev = nullptr;
                    }
                }
            }
            bool ChangeLoadFactor(const size_t& TempLoadFactor)
            {
                if(TempLoadFactor < 1)
                {
                    return false;
                }
                LoadFactor = TempLoadFactor;
                return true;
            }
            iterator operator[](const HashTableTypeKey& TempKey)
            {
                if( _size == 0)
                {
                    return iterator(nullptr);
                }
                else
                {
                    size_t Temp_Hash = DataExtractionFunction(TempKey);
                    size_t HashLocationData = Temp_Hash % Capacity;
                    //找到映射位置
                    container_node* _TempNode = _HashTable[HashLocationData];
                    while(_TempNode!= nullptr)
                    {
                        if(HashDataFunctor(_TempNode->_data) == HashDataFunctor(TempKey))
                        {
                            return iterator(_TempNode);
                        }
                        _TempNode = _TempNode->_next;
                    }
                    return iterator(nullptr);
                }
            }
            iterator begin()                    {   return iterator(HeadData);        }
            const_iterator cbegin() const       {   return const_iterator(HeadData);  }
            iterator end()                      {   return iterator(nullptr);           }
            const_iterator cend() const         {   return const_iterator(nullptr);     }
            size_t size()                       {   return _size;                       }
            size_t size() const                 {   return _size;                       }
            bool   empty()                      {   return _size == 0;                  }
            size_t capacity()                   {   return Capacity;                    }
            size_t capacity() const             {   return Capacity;                    }

            bool push (const HashTableTypeVal& TempVal)
            {
                if( find(TempVal) != nullptr)
                {
                    return false;
                }
                //判断扩容
                if( _size * 10 >= Capacity * LoadFactor)
                {
                    //扩容
                    size_t new_container_capacity = (Capacity == 0 && _HashTable.size() == 0) ? 10 : Capacity * 2;
                    //新容量
                    template_container::vector_c::vector<container_node*> _NewHashTable;
                    _NewHashTable.resize(new_container_capacity,nullptr);
                    size_t _New_size = 0;
                    //重新映射,按照插入链表顺序
                    container_node* _TempHeadNode = nullptr;
                    container_node* _TempPreviousData = nullptr;
                    container_node* _TempNode = HeadData;
                    while( _TempNode != nullptr)
                    {
                        size_t Temp_Hash = hash_function(_TempNode->_data) % new_container_capacity;
                        //重新计算映射值
                        container_node* New_Mapping_location = _NewHashTable[Temp_Hash];
                        if(New_Mapping_location == nullptr)
                        {
                            container_node* PushNode = new container_node(_TempNode->_data);
                            if(_TempHeadNode == nullptr)
                            {
                                PushNode->LinkPrev = nullptr;
                                PushNode->LinkNext = nullptr;
                                _TempHeadNode = _TempPreviousData =PushNode;
                            }
                            else
                            {
                                PushNode->LinkPrev = _TempPreviousData;
                                _TempPreviousData->LinkNext = PushNode;
                                _TempPreviousData = PushNode;
                            }
                            _NewHashTable[Temp_Hash] = PushNode;
                            //保存之前的遍历链表信息
                        }
                        else
                        {
                            container_node* PushNode = new container_node(_TempNode->_data);
                            if(_TempHeadNode == nullptr)
                            {
                                PushNode->LinkPrev = nullptr;
                                _TempHeadNode = _TempPreviousData =PushNode;
                            }
                            else
                            {
                                PushNode->LinkPrev = _TempPreviousData;
                                _TempPreviousData->LinkNext = PushNode;
                                _TempPreviousData = PushNode;
                            }
                            PushNode->_next = New_Mapping_location;
                            _NewHashTable[Temp_Hash] = PushNode;
                            //头插节点
                        }
                        ++_New_size;
                        _TempNode = _TempNode->LinkNext;
                    }
                    //释放旧哈希表
                    for(size_t i = 0;i < _HashTable.size(); ++i)
                    {
                        container_node* _TempNode = _HashTable[i];
                        while(_TempNode!= nullptr)
                        {
                            container_node* _Temp_Node_prev = _TempNode;
                            _TempNode = _TempNode->_next;
                            delete _Temp_Node_prev;
                            _Temp_Node_prev = nullptr;
                        }
                    }
                    _size = _New_size;
                    _HashTable.swap(_NewHashTable);
                    Capacity = new_container_capacity;
                    HeadData = _TempHeadNode;
                    PreviousData = _TempPreviousData;
                    //重新映射,按照插入链表顺序
                }
                size_t Temp_Hash = hash_function(TempVal);
                size_t HashLocationData = Temp_Hash % Capacity;
                //找到映射位置
                container_node* _TempNode = _HashTable[HashLocationData];

                container_node* PushNode = new container_node(TempVal);
                PushNode->_next = _TempNode;
                _HashTable[HashLocationData] = PushNode;
                if(_size == 0 && HeadData == nullptr)
                {
                    PushNode->LinkPrev = nullptr;
                    HeadData = PreviousData = PushNode;
                }
                else
                {
                    PushNode->LinkPrev = PreviousData;
                    PreviousData->LinkNext = PushNode;
                    PreviousData = PushNode;
                }
                _size++;
                return true;
            }
            bool pop(const HashTableTypeVal& TempVal)
            {
                //空表判断
                if( find(TempVal) == nullptr)
                {
                    return false;
                }
                size_t Temp_Hash = hash_function(TempVal);
                size_t HashLocationData = Temp_Hash % Capacity;
                //找到映射位置
                container_node* _TempNode = _HashTable[HashLocationData];
                container_node* TempNodeParent = nullptr;
                while(_TempNode!= nullptr)
                {
                    //找到位置
                    if(HashDataFunctor(_TempNode->_data) == HashDataFunctor(TempVal))
                    {
                        if(HeadData == _TempNode)
                        {
                            //头节点删除情况
                            if(_TempNode == PreviousData)
                            {
                                //只有一个节点
                                HeadData = PreviousData = nullptr;
                                parentJudgment(TempNodeParent,_TempNode,HashLocationData);
                            }
                            else
                            {
                                //是头节点，不是尾节点
                                parentJudgment(TempNodeParent,_TempNode,HashLocationData);
                                HeadData = HeadData->LinkNext;
                                HeadData->LinkPrev = nullptr;
                            }
                        }
                        else if(_TempNode == PreviousData)
                        {
                            //尾节点删除情况
                            parentJudgment(TempNodeParent,_TempNode,HashLocationData);
                            PreviousData = PreviousData->LinkPrev;
                            PreviousData->LinkNext = nullptr;
                        }
                        else
                        {
                            //中间节点删除情况
                            parentJudgment(TempNodeParent,_TempNode,HashLocationData);
                            _TempNode->LinkPrev->LinkNext = _TempNode->LinkNext;
                            _TempNode->LinkNext->LinkPrev = _TempNode->LinkPrev;
                        }
                        delete _TempNode;
                        _TempNode = nullptr;
                        --_size;
                        return true;
                    }
                    TempNodeParent = _TempNode;
                    _TempNode = _TempNode->_next;
                    //向下遍历
                }
                return false;
            }
            iterator find(const HashTableTypeVal& TempVal)
            {
                if( _size == 0)
                {
                    return iterator(nullptr);
                }
                else
                {
                    size_t Temp_Hash = hash_function(TempVal);
                    size_t HashLocationData = Temp_Hash % Capacity;
                    //找到映射位置
                    container_node* _TempNode = _HashTable[HashLocationData];
                    while(_TempNode!= nullptr)
                    {
                        if(HashDataFunctor(_TempNode->_data) == HashDataFunctor(TempVal))
                        {
                            return iterator(_TempNode);
                        }
                        _TempNode = _TempNode->_next;
                    }
                    return iterator(nullptr);
                }
            }                             
        };
        /*############################     BitSet 容器     ############################*/
        class BitSet
        {
            template_container::vector_c::vector<int> _BitSet;
            size_t _size;
        public:
            BitSet() {  ;  }
            BitSet(const size_t& Temp_size)
            {
                _size = 0;
                _BitSet.resize((Temp_size / 32) + 1,0);
                //多开一个int的空间，防止不够
            }
            void resize(const size_t& Temp_size)
            {
                _size = 0;
                _BitSet.resize((Temp_size / 32) + 1,0);
            }
            BitSet(const BitSet& BitMap_Temp)
            {
                _BitSet = BitMap_Temp._BitSet;
                _size = BitMap_Temp._size;
            }
            BitSet& operator=(const BitSet& BitMap_Temp)
            {
                if(this != &BitMap_Temp)
                {
                    _BitSet = BitMap_Temp._BitSet;
                    _size = BitMap_Temp._size;
                }
                return *this;
            }
            void set(const size_t& TempVal)
            {
                //把数映射到BitSet上的函数
                size_t BitSetLocation = TempVal / 32; //定位到BitSet的位置在哪个int上
                size_t BitSet_Location_Val = TempVal % 32; //定位到BitSet的位置在哪个int上的第几位
                _BitSet[BitSetLocation] = _BitSet[BitSetLocation] | (1 << BitSet_Location_Val);
                //比较当前位置是否为1，若为1则不需要改变，若为0则需要改变，注意|只改变当前位不会改变其他位
                //|是两个条件满足一个条件就行，&是两个条件都满足才行
                //其他位如果是1那么就还是1，如果是0那么就还是0，因为|是两个条件满足一个条件就行
                _size++;
            }
            void reset(const size_t& TempVal)
            {
                //删除映射的位置的函数
                size_t BitSetLocation = TempVal / 32;
                size_t BitSet_Location_Val = TempVal % 32;
                _BitSet[BitSetLocation] = _BitSet[BitSetLocation] & (~(1 << BitSet_Location_Val));
                //&是两个条件都满足，~是取反，^是两个条件不同时满足
                //1取反关键位是0其他位是1，这样就成功与掉，&要求是两个条件都需要满足
                //其他位如果是1那么就不会改变原来的，如果是0那么还是为0，因为与是两个条件都需要满足
                _size--;
            }
            size_t size()       { return _size; }
            bool test(const size_t& TempVal)
            {
                if(_size == 0)
                {
                    return false;
                }
                size_t BitSetLocation = TempVal / 32;
                size_t BitSet_Location_Val = TempVal % 32;
                bool return_BitSet = _BitSet[BitSetLocation] & (1 << BitSet_Location_Val);
                //如果_BitSet[BitSetLocation]里对应的位是1那么就返回true，否则返回false
                return return_BitSet;
            }
        };
    }
    /*############################     tree_map 容器     ############################*/
    namespace map_c
    {
        template <typename MapTypeK,typename MapTypeV>
        class tree_map
        {
            using KeyValType = template_container::practicality::pair<MapTypeK,MapTypeV>;
            struct Key_Val
            {
                const MapTypeK& operator()(const KeyValType& TempKey)
                {
                    return TempKey.first;
                }
            };
            using RBTREE = base_class_c::RBTree <MapTypeK,KeyValType,Key_Val>;
            RBTREE ROOTMap;
        public:
            using iterator = typename RBTREE::iterator;
            using const_iterator = typename RBTREE::const_iterator;
            using reverse_iterator = typename RBTREE::reverse_iterator;
            using const_reverse_iterator = typename RBTREE::const_reverse_iterator;
            
            using Map_iterator = template_container::practicality::pair<iterator,bool>;
            ~tree_map()
            {
                ROOTMap.~RBTree();
            }
            tree_map& operator=(const tree_map& tree_map_temp)
            {
                if(this != &tree_map_temp)
                {
                    ROOTMap = tree_map_temp.ROOTMap;
                }
                return *this;
            }
            tree_map& operator=(tree_map&& tree_map_temp)
            {
                if(this != &tree_map_temp)
                {
                    ROOTMap = std::move(tree_map_temp.ROOTMap);
                }
                return *this;
            }
            tree_map()                                                   {  ;                                   }
            tree_map(const tree_map& tree_map_temp)                                {  ROOTMap = tree_map_temp.ROOTMap;         }
            tree_map(tree_map&& tree_map_temp)                                     {  ROOTMap=std::move(tree_map_temp.ROOTMap);}
            tree_map(const KeyValType& tree_map_temp)                         {  ROOTMap.push(tree_map_temp);             }
            Map_iterator push(const KeyValType& tree_map_temp)           {  return ROOTMap.push(tree_map_temp);      }
            Map_iterator pop(const KeyValType& tree_map_temp)            {  return ROOTMap.pop(tree_map_temp);       }
            iterator find(const KeyValType& tree_map_temp)               {  return ROOTMap.find(tree_map_temp);     }
            void MiddleOrderTraversal()                             {  ROOTMap.MiddleOrderTraversal();     }
            void PreOrderTraversal()                                {  ROOTMap.PreOrderTraversal();        }
            size_t size() const                                     {  return ROOTMap.size();              }
            bool empty()                                            {  return ROOTMap.empty();             }
            iterator begin()                                        {  return ROOTMap.begin();             }
            iterator end()                                          {  return ROOTMap.end();               }
            const_iterator cbegin()                                 {  return ROOTMap.cbegin();            }
            const_iterator cend()                                   {  return ROOTMap.cend();              }
            reverse_iterator rbegin()                               {  return ROOTMap.rbegin();            }
            reverse_iterator rend()                                 {  return ROOTMap.rend();              }
            const_reverse_iterator crbegin()                        {  return ROOTMap.crbegin();           }
            const_reverse_iterator crend()                          {  return ROOTMap.crend();             }
            iterator operator[](const KeyValType& tree_map_temp)         {  return ROOTMap[tree_map_temp];           }
        };
        template <typename UnorderedMapTypeK,typename UnorderedMapTypeV>
        class hash_map
        {
            using KeyValType = template_container::practicality::pair<UnorderedMapTypeK,UnorderedMapTypeV>;
            struct Key_Val
            {
                const UnorderedMapTypeK& operator()(const KeyValType& TempKey)
                {
                    return TempKey.first;
                }
            };
            class Hash_Functor
            {
            public:
                size_t operator()(const KeyValType& TempKey)
                {
                    size_t num_One =  template_container::imitation_functions::hash_imitation_functions()(TempKey.first);
                    num_One = num_One * 31;
                    size_t num_Two =  template_container::imitation_functions::hash_imitation_functions()(TempKey.second);
                    num_Two = num_Two * 31;
                    return (num_One + num_Two);
                }
            };
            using HashTable = base_class_c::HashTable<UnorderedMapTypeK,KeyValType,Key_Val,Hash_Functor>;
            HashTable HashMap;
        public:
            using iterator = typename HashTable::iterator;
            using const_iterator = typename HashTable::const_iterator;
            hash_map()                                      {   ;                               }  
            ~hash_map()                                     {  HashMap.~HashTable();            }
            hash_map(const KeyValType& TempKey)             {  HashMap.push(TempKey);           }
            bool push(const KeyValType& TempKey)                {  return HashMap.push(TempKey);    }
            bool pop(const KeyValType& TempKey)                 {  return HashMap.pop(TempKey);     }
            iterator find(const KeyValType& TempKey)            {  return HashMap.find(TempKey);    }
            size_t size()                                       {  return HashMap.size();           }
            size_t size() const                                 {  return HashMap.size();           }
            size_t capacity() const                             {  return HashMap.capacity();       } 
            bool empty()                                        {  return HashMap.empty();          }
            iterator begin()                                    {  return HashMap.begin();          }
            iterator end()                                      {  return HashMap.end();            }
            const_iterator cbegin()                             {  return HashMap.cbegin();         }
            const_iterator cend()                               {  return HashMap.cend();           }
            iterator operator[](const KeyValType& TempKey)      {  return HashMap[TempKey];         }
        };
    }
    /*############################     tree_set 容器     ############################*/
    namespace set_c
    {
        template <typename SetTypeK>
        class tree_set
        {
            using KeyValType = SetTypeK;
            struct Key_Val
            {
                /* 仿函数，返回比较的值 */
                const SetTypeK& operator()(const KeyValType& TempKey)
                {
                    return TempKey;
                }
            };
            using RBTREE = base_class_c::RBTree<SetTypeK,KeyValType,Key_Val>;
            RBTREE ROOTSet;
        public:
            using iterator = typename RBTREE::iterator;
            using const_iterator = typename RBTREE::const_iterator;
            using reverse_iterator = typename RBTREE::reverse_iterator;
            using const_reverse_iterator = typename RBTREE::const_reverse_iterator;
            
            using Set_iterator = template_container::practicality::pair<iterator,bool>;
            tree_set& operator=(const tree_set& SetTemp)             
            {  
                if(this!= &SetTemp)                     
                {  
                    ROOTSet = SetTemp.ROOTSet;      
                }  
                return *this; 
            }
            tree_set& operator=(tree_set&& SetTemp)
            {
                if(this!= &SetTemp)                     
                {  
                    ROOTSet = std::move(SetTemp.ROOTSet);
                }
                return *this;
            }
            tree_set()                                               {  ;                                      }
            ~tree_set()                                              {  ROOTSet.~RBTree();                     }
            tree_set(const tree_set& SetTemp)                             {  ROOTSet = SetTemp.ROOTSet;             }
            tree_set(tree_set&& SetTemp)                                  {  ROOTSet=std::move(SetTemp.ROOTSet);    }
            tree_set(const KeyValType& SetTemp)                 {  ROOTSet.push(SetTemp);                 }
            Set_iterator push(const KeyValType& SetTemp)        {  return ROOTSet.push(SetTemp);          }
            Set_iterator pop(const KeyValType& SetTemp)         {  return ROOTSet.pop(SetTemp);           }
            iterator find(const KeyValType& SetTemp)            {  return ROOTSet.find(SetTemp);          }
            void MiddleOrderTraversal()                         {  ROOTSet.MiddleOrderTraversal();        }    
            void PreOrderTraversal()                            {  ROOTSet.PreOrderTraversal();           }  
            size_t size() const                                 {  return ROOTSet.size();                 }
            bool empty()                                        {  return ROOTSet.empty();                }  
            iterator begin()                                    {  return ROOTSet.begin();                }
            iterator end()                                      {  return ROOTSet.end();                  }
            const_iterator cbegin()                             {  return ROOTSet.cbegin();               }
            const_iterator cend()                               {  return ROOTSet.cend();                 }
            reverse_iterator rbegin()                           {  return ROOTSet.rbegin();               }
            reverse_iterator rend()                             {  return ROOTSet.rend();                 }
            const_reverse_iterator crbegin()                    {  return ROOTSet.crbegin();              }
            const_reverse_iterator crend()                      {  return ROOTSet.crend();                }
            iterator operator[](const KeyValType& SetTemp)      {  return ROOTSet[SetTemp];               }
        };
        template <typename UnorderedSetTypeK>
        class hash_set
        {
            using KeyValType = UnorderedSetTypeK;
            class Hash_Functor
            {
            public:
                size_t operator()(const KeyValType& TempKey)
                {
                    return template_container::imitation_functions::hash_imitation_functions()(TempKey)* 131;
                }
            };
            class Key_Val
            {
            public:
                const KeyValType& operator()(const KeyValType& TempKey)
                {
                    return TempKey;
                }
            };
            using HashTable = template_container::base_class_c::HashTable<UnorderedSetTypeK,KeyValType,Key_Val,Hash_Functor>;
            HashTable HashSet;
        public:
            using iterator = typename HashTable::iterator;
            using const_iterator = typename HashTable::const_iterator;
            hash_set()                                      {  ;                                     }
            ~hash_set()                                     {   HashSet.~HashTable();                }
            bool push(const KeyValType& SetTemp)                {  return HashSet.push(SetTemp);         }
            bool pop(const KeyValType& SetTemp)                 {  return HashSet.pop(SetTemp);          }            
            iterator find(const KeyValType& SetTemp)            {  return HashSet.find(SetTemp);         }
            size_t size()                                       {  return HashSet.size();                 }
            bool empty()                                        {  return HashSet.empty();                }
            size_t capacity()                                   {  return HashSet.capacity();             }
            size_t size() const                                 {  return HashSet.size();                 }
            size_t capacity() const                             {  return HashSet.capacity();             }
            iterator begin()                                    {  return HashSet.begin();                }
            iterator end()                                      {  return HashSet.end();                  }
            const_iterator cbegin()                             {  return HashSet.cbegin();               }
            const_iterator cend()                               {  return HashSet.cend();                 }
            iterator operator[](const KeyValType& SetTemp)      {  return HashSet[SetTemp];               }
        };
    }
    /*############################     BloomFilter 容器     ############################*/
    namespace bloom_filter_c
    {
        template <typename BloomFilterTypeVal,typename HashFunctorBloomFilter = template_container::algorithm::hash_algorithm::hash_function<BloomFilterTypeVal> >
        class BloomFilter
        {
            HashFunctorBloomFilter   _Hash;
            using BitSet = template_container::base_class_c::BitSet;
            BitSet VectorBitSet;
            size_t _Capacity;
        public:
            BloomFilter()
            {
                _Capacity = 1000;
                VectorBitSet.resize(_Capacity);
            }
            BloomFilter(const size_t& Temp_Capacity)
            {
                _Capacity = Temp_Capacity;
                VectorBitSet.resize(_Capacity);
            }
            size_t size()
            {
                return VectorBitSet.size();
            }
            size_t capacity()
            {
                return _Capacity;
            }
            bool test(const BloomFilterTypeVal& TempVal)
            {
                size_t num_One   = _Hash.Hash_SDBMHash(TempVal) % _Capacity;
                size_t num_Two   = _Hash.Hash_DJBHash (TempVal) % _Capacity;
                size_t num_Three = _Hash.Hash_PJWHash (TempVal) % _Capacity;
                if(VectorBitSet.test(num_One) == true && VectorBitSet.test(num_Two) == true && VectorBitSet.test(num_Three) && true)
                {
                    return true;
                    /* 有一个为0就返回false */
                }
                return false;
            }
            void set(const BloomFilterTypeVal& TempVal)
            {
                size_t num_One   = _Hash.Hash_SDBMHash(TempVal) % _Capacity;
                size_t num_Two   = _Hash.Hash_DJBHash (TempVal) % _Capacity;
                size_t num_Three = _Hash.Hash_PJWHash (TempVal) % _Capacity;
                VectorBitSet.set(num_One);
                VectorBitSet.set(num_Two);
                VectorBitSet.set(num_Three);
            }
            //布隆过滤器只支持插入和查找，不支持删除
        };
    }
}
namespace tc = template_container;
namespace sp = smart_pointer;
namespace ex = custom_exception;
namespace set
{
    using template_container::string_c::string;
    using template_container::vector_c::vector;
    using template_container::list_c::list;
    using template_container::stack_a::stack;
    using template_container::queue_a::queue;
    using template_container::queue_a::priority_queue;
    using template_container::base_class_c::RBTree;
    using template_container::base_class_c::HashTable;
    using template_container::map_c::tree_map;
    using template_container::map_c::hash_map;
    using template_container::set_c::tree_set;
    using template_container::set_c::hash_set;
    using template_container::base_class_c::BitSet;
    using template_container::bloom_filter_c::BloomFilter;
    using template_container::practicality::pair;
    using template_container::practicality::make_pair;
    using template_container::algorithm::copy;
    using template_container::algorithm::find;
    using template_container::algorithm::swap;
    using smart_pointer::smart_ptr;
    using smart_pointer::unique_ptr;
    using smart_pointer::shared_ptr;
    using smart_pointer::weak_ptr;
    //待测试？
}