//本文件都是自己造的轮子
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
namespace template_container
{
    namespace imitation_functions
    {
        //仿函数命名空间
        template<typename imitation_functions_less>
        class less
        {
        public:
            bool operator()(const imitation_functions_less& _test1 ,const imitation_functions_less& _test2)
            {
                return _test1 < _test2;
            }
        };
        template<typename imitation_functions_greater>
        class greater
        {
        public:
            bool operator()(const imitation_functions_greater& _test1 ,const imitation_functions_greater& _test2)
            {
                return _test1 > _test2;
            }
        };
        class hash_imitation_functions
        {
        public:
            size_t operator()(const int data_str)                               {       return data_str;                }
            size_t operator()(const size_t data_num)                            {       return data_num;                }
            size_t operator()(const char data_char)                             {       return data_char;               }
            size_t operator()(const double data_double)                         {       return data_double;             }
            size_t operator()(const float data_float)                           {       return data_float;              }
            size_t operator()(const long data_long)                             {       return data_long;               }
            size_t operator()(const short data_short)                           {       return data_short;              }
            size_t operator()(const long long data_long_long)                   {       return data_long_long;          }
            size_t operator()(const unsigned int data_unsigned)                 {       return data_unsigned;           }
            size_t operator()(const unsigned long data_unsigned_long)           {       return data_unsigned_long;      }
            size_t operator()(const unsigned short data_unsigned_short)         {       return data_unsigned_short;     }
            
  
            // size_t operator()(const MY_Template::string_container::string& data_string)
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
        target_sequence_copy copy(source_sequence_copy begin,source_sequence_copy end,target_sequence_copy first)
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
        source_sequence_find find(source_sequence_find begin,source_sequence_find end,const target_sequence_find& value)
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
        void swap(swap_data_type& a,swap_data_type& b)
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
                size_t Hash_SDBMHash(const hash_algorithm_type& data_Hahs)
                {
                    size_t return_value = hash_imitation_functions_object(data_Hahs);
                    return_value = 65599 * return_value;
                    return return_value;
                }
                size_t Hash_BKDRHash(const hash_algorithm_type& data_Hahs)
                {
                    size_t return_value = hash_imitation_functions_object(data_Hahs);
                    return_value = 131 * return_value;
                    return return_value;
                }
                size_t Hash_DJBHash(const hash_algorithm_type& data_Hahs)
                {
                    size_t return_value = hash_imitation_functions_object(data_Hahs);
                    return_value = 33 * return_value;
                    return return_value;
                }
                size_t Hash_APHash(const hash_algorithm_type& data_Hahs)
                {
                    size_t return_value = hash_imitation_functions_object(data_Hahs);
                    return_value = return_value * 1031;
                    return return_value;
                }
                size_t Hash_PJWHash(const hash_algorithm_type& data_Hahs)
                {
                    size_t return_value = hash_imitation_functions_object(data_Hahs);
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
            pair() : first(T()), second(K())                    {       ;           }
            pair(const T& _first,const K& _second) 
            : first(_first), second(_second)                    {       ;           }
            pair(const pair& other) 
            : first(other.first), second(other.second)          {       ;           }
            pair(const T&& _first,const K&& _second) 
            : first(std::move(_first)), second(std::move(_second))                    {       ;           }
            pair(pair&& other)
            {
                template_container::algorithm::swap(first,other.first);
                template_container::algorithm::swap(second,other.second);
            }
            pair& operator=(const pair& other)
            {
                if(this != &other)
                {
                    first = other.first;
                    second = other.second;
                }
                return *this;
            }
            pair& operator=(pair&& other)
            {
                if(this != &other)
                {
                    first = std::move(other.first);
                    second = std::move(other.second);
                }
                return *this;
            }
            bool operator==(const pair& other) const    {       return (this == &other) ? true : (first == other.first && second == other.second);  }
            bool operator==(const pair& other)          {       return this == &other ? true : (first == other.first && second == other.second);    }
            bool operator!=(const pair& other)          {       return !(*this == other);   }
            pair* operator->()                          {       return this;        }
            const pair* operator->()const               {       return this;        }
            // pair& operator*() { return *this; }
            // const pair& operator*() const { return *this; }
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
            char *_data;
            size_t _size;
            size_t _capacity;
        public:
            //创建迭代器
            using iterator = char*;
            using const_iterator = const char*;
    
            using reverse_iterator = char*;
            using const_reverse_iterator = const char*;
            //反向迭代器
            //限定字符串最大值
            static const size_t nops = -1;
            iterator begin()                        {   return _data;   }

            iterator end()                          {   return _data + _size;   }

            const_iterator cbegin()const            {   return const_iterator(_data);   }

            const_iterator cend()const              {   return const_iterator(_data + _size);   }

            reverse_iterator rbegin()               {   return empty() ? reverse_iterator(end()) : reverse_iterator(end() - 1);  }

            reverse_iterator rend()                 {   return empty() ? reverse_iterator(begin()) : reverse_iterator(begin() - 1);  }

            const_reverse_iterator crbegin()const   {   return const_reverse_iterator(cend()- 1);   }

            const_reverse_iterator crend()const     {   return const_reverse_iterator(cbegin()- 1); }

            bool empty()                            {   return _size == 0;  }

            size_t size()const                      {   return _size;       }

            size_t capacity()const                  {   return _capacity;   }

            char* c_str()const                      {   return _data;       } //返回C风格字符串

            char back()                             {   return _size > 0 ? _data[_size - 1] : '\0';    }

            char Front()                            {   return _data[0];    }//返回尾字符

            string(const char* data_str = " ")
            :_size(data_str == nullptr ? 0 : strlen(data_str)),_capacity(_size)
            {
                //传进来的字符串是常量字符串，不能直接修改，需要拷贝一份，并且常量字符串在数据段(常量区)浅拷贝会导致程序崩溃
                if(data_str != nullptr)
                {
                    _data = new char[_capacity + 1];
                    std::strncpy(_data,data_str,std::strlen(data_str));
                    // strcpy(_data,data_str);
                    _data[_size] = '\0';
                }
                else
                {
                    _data = new char[1];
                    _data[0] = '\0';
                }
            }
            string(char*&& data_str)
            :_data(nullptr),_size(data_str == nullptr ? 0 : strlen(data_str)),_capacity(_size)
            {
                //移动构造函数，拿传入对象的变量初始化本地变量，对于涉及开辟内存的都要深拷贝
                if(data_str != nullptr)
                {
                    _data = data_str;
                    data_str = nullptr;
                }
                else
                {
                    _data = new char[1];
                    _data[0] = '\0';
                }
            }
            string(const string& data_str)
            :_data(nullptr),_size(data_str._size),_capacity(data_str._capacity)
            {
                //拷贝构造函数，拿传入对象的变量初始化本地变量，对于涉及开辟内存的都要深拷贝
                size_t capacity = data_str._capacity;
                _data = new char[capacity + 1];
                // algorithm::copy(_data,_data+capacity,data_str._data); const对象出错
                std::strcpy(_data, data_str._data);
            }
            string(string&& data_str)
            :_data(nullptr),_size(data_str._size),_capacity(data_str._capacity)
            {
                //移动构造函数，拿传入对象的变量初始化本地变量，对于涉及开辟内存的都要深拷贝
                template_container::algorithm::swap(data_str._data,_data);
            }
            string(std::initializer_list<char> data_str)
            {
                //初始化列表构造函数
                _size = data_str.size();
                _capacity = _size;
                _data = new char[_capacity + 1];
                template_container::algorithm::copy(data_str.begin(), data_str.end(), _data);
                _data[_size] = '\0';
            }
            ~string()
            {
                delete [] _data;
                _data = nullptr;
                _capacity = _size = 0;
            }
            string& Lowercase()
            {
                //字符串转大写
                for(string::iterator originate = _data; originate != _data + _size; originate++)
                {
                    if(*originate >= 'a' && *originate <= 'z')
                    {
                        *originate -= 32;
                    }
                }
                return *this;
            }
            string& conversions_few()
            {
                //字符串转小写
                for(string::iterator originate = _data; originate != _data + _size; originate++)
                {
                    if(*originate >= 'A' && *originate <= 'Z')
                    {
                        *originate += 32;
                    }
                }
                return *this;
            }
            // size_t str_substring_kmp(const char*& c_str_substring)
            // {
            //     //查找子串
            // }
            string& prepend(const char*& c_str_substring)
            {
                //前部插入子串
                size_t len = strlen(c_str_substring);
                size_t new_nose_insert_substrings = _size + len;
                if(allocate_resources(new_nose_insert_substrings) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return *this;
                }
                char* _c_nose_insert_substrings_temp = new char[_capacity + 1];
                //临时变量
                memmove(_c_nose_insert_substrings_temp , _data , _size + 1);
                memmove(_data , c_str_substring , len);
                memmove(_data + len , _c_nose_insert_substrings_temp , _size + 1);
                //比memcpy更安全，memcpy会覆盖原有数据，memmove会先拷贝到临时变量再拷贝到目标地址
                _size = new_nose_insert_substrings;
                _data[_size] = '\0';
                delete [] _c_nose_insert_substrings_temp;
                return *this;
            }
            string& insert_sub_string(const char*& c_str_substring,const size_t& oid_pos)
            {
                //中间位置插入子串
                if(oid_pos > _size)
                {
                    std::cout << "插入位置越界！" << std::endl;
                    return *this;
                }
                size_t len = strlen(c_str_substring);
                size_t new_interlocutory_insert_substrings = _size + len;
                if(allocate_resources(new_interlocutory_insert_substrings) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return *this;
                }
                char* _c_interlocutory_insert_substrings_temp = new char[new_interlocutory_insert_substrings + 1];
                //临时变量
                memmove(_c_interlocutory_insert_substrings_temp, _data, _size + 1);
                //从oid_pos开始插入
                memmove(_data + oid_pos + len, _c_interlocutory_insert_substrings_temp + oid_pos, _size - oid_pos + 1);
                memmove(_data + oid_pos, c_str_substring, len);
                _size = new_interlocutory_insert_substrings;
                _data[_size] = '\0';
                delete [] _c_interlocutory_insert_substrings_temp;
                return *this;
            }
            string sub_string(const size_t& old_pos)
            {
                //提取字串到'\0'
                if(old_pos > _size)
                {
                    std::cout << "提取位置越界！" << std::endl;
                    return string();
                }
                string _str_withdraw_temp;
                size_t _str_withdraw_temp_len = _size - old_pos;
                if(_str_withdraw_temp.allocate_resources(_str_withdraw_temp_len) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return string();
                }
                strncpy(_str_withdraw_temp._data , _data + old_pos,_str_withdraw_temp_len);
                _str_withdraw_temp._size = _str_withdraw_temp_len;
                _str_withdraw_temp._data[_str_withdraw_temp._size] = '\0';
                return _str_withdraw_temp;
            }
            string sub_string_from(const size_t& old_begin)
            {
                //提取字串到末尾
                if(old_begin > _size)
                {
                    std::cout << "提取位置越界！" << std::endl;
                    return string();
                }
                string _str_withdraw_extremity_temp;
                size_t _str_withdraw_extremity_temp_len = _size - old_begin;
                if(_str_withdraw_extremity_temp.allocate_resources(_str_withdraw_extremity_temp_len) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return string();
                }
                strncpy(_str_withdraw_extremity_temp._data , _data + old_begin,_str_withdraw_extremity_temp_len);
                _str_withdraw_extremity_temp._size = _str_withdraw_extremity_temp_len;
                _str_withdraw_extremity_temp._data[_str_withdraw_extremity_temp._size] = '\0';
                return _str_withdraw_extremity_temp;
            }
            string sub_string(const size_t& old_begin ,const size_t& old_end)
            {
                //提取字串到指定位置
                if(old_begin > _size || old_end > _size || old_begin > old_end)
                {
                    std::cout << "提取位置越界！" << std::endl;
                    return string();
                }
                string _str_withdraw_detail_temp;
                size_t _str_withdraw_detail_temp_len = old_end - old_begin;
                if(_str_withdraw_detail_temp.allocate_resources(_str_withdraw_detail_temp_len) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return string();
                }
                //strncpy更安全
                strncpy(_str_withdraw_detail_temp._data , _data + old_begin,_str_withdraw_detail_temp_len);
                _str_withdraw_detail_temp._size = _str_withdraw_detail_temp_len;
                _str_withdraw_detail_temp._data[_str_withdraw_detail_temp._size] = '\0';
                return _str_withdraw_detail_temp;
            }
            bool allocate_resources(const size_t& temporary_variable)
            {
                //检查string空间大小，来分配内存
                if(temporary_variable <= _capacity)
                {
                    //防止无意义频繁拷贝
                    return true;
                }
                char* temporary_ = new char[temporary_variable+1];
                if(temporary_)
                {
                    std::strncpy(temporary_,_data,size());
                    temporary_[_size] = '\0';
                    delete[] _data;
                    _data = temporary_;
                    _capacity = temporary_variable;
                    return true;
                }
                return false;
            }
            string& push_back(const char& c_temp_str)
            {
                if(_size == _capacity)
                {
                    size_t newcapacity = _capacity == 0 ? 2 :_capacity*2;
                    if(allocate_resources(newcapacity) != true)
                    {
                        std::cout << "开辟内存失败！" << std::endl;
                        return *this;
                    }
                }
                _data[_size] = c_temp_str;
                ++_size;
                _data[_size] = '\0';
                return *this;
            }
            string& push_back(const string& cpp_temp_str)
            {
                size_t len = _size + cpp_temp_str._size;
                if(len > _capacity)
                {
                    size_t new_capacity = len;
                    if(allocate_resources(new_capacity) != true)
                    {
                        std::cout << "开辟内存失败！" << std::endl;
                        return *this;
                    }
                }
                std::strncpy(_data+_size,cpp_temp_str._data,cpp_temp_str.size());
                _size =_size + cpp_temp_str._size;
                _data[_size] = '\0';
                return *this;
            }
            string& push_back(const char* c_temp_str)
            {
                if(c_temp_str == nullptr)
                {
                    return *this;
                }
                size_t len = strlen( c_temp_str );
                size_t new_capacity = len + _size ;
                if(new_capacity >_capacity)
                {
                    if(allocate_resources( new_capacity) != true)
                    {
                        std::cout << "开辟内存失败！" << std::endl;
                        return *this;
                    }
                }
                std::strncpy(_data+_size , c_temp_str,len);
                _size = _size + len;
                _data[_size] = '\0';
                return *this;
            }
            string& resize(const size_t& new_size ,const char& c_temp_str = '\0')
            {
                //扩展字符串长度
                if(new_size >_capacity)
                {
                    //长度大于容量，重新开辟内存
                    if(allocate_resources(new_size) != true)
                    {
                        std::cout << "开辟内存失败！" << std::endl;
                        return *this;
                    }
                    for(string::iterator originate = _data + _size;originate != _data + new_size;originate++)
                    {
                        *originate = c_temp_str;
                    }
                    _size = new_size;
                    _data[_size] = '\0';
                }
                else
                {
                    //如果新长度小于当前字符串长度，直接截断放'\0'
                    _size = new_size;
                    _data[_size] = '\0';
                }
                return *this;
            }
            iterator reserve(const size_t& new_capacity)
            {
                if(allocate_resources(new_capacity) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                }
                return _data;
                //返回首地址迭代器
            }
            string& swap(string& data_str)
            {
                template_container::algorithm::swap(_data,data_str._data);
                template_container::algorithm::swap(_size,data_str._size);
                template_container::algorithm::swap(_capacity,data_str._capacity);
                return *this;
            }
            string reverse()
            {
                if(_size == 0)
                {
                    std::cout << "回滚失败，字符串为空！" << std::endl;
                    return string();
                }
                string _rollback_temp;
    
                // for(size_t i = _size - 1; i != nops; i--)
                // {
                //     _rollback_temp.push_back(_data[i]);
                // }
                for(string::const_reverse_iterator reverse = rbegin();reverse != rend();reverse--)
                {
                    _rollback_temp.push_back(*reverse);
                }
                return _rollback_temp;
            }
            string reverse_sub_string(const size_t& limit_begin , const size_t& limit_end)
            {
                string _rollback_linit_temp;
                if(limit_begin > _size || limit_end > _size || limit_begin > limit_end ||_size == 0)
                {
                    std::cout << "回滚位置越界！" << std::endl;
                    return string();
                }
                // for(size_t i = limit_end - 1; i != limit_begin - 1; i--)
                // {
                //     //[]遍历
                //     _rollback_linit_temp.push_back(_data[i]);
                // } 
    
                for(string::const_reverse_iterator reverse = _data + limit_end - 1;reverse != _data + limit_begin - 1;reverse--)
                {
                    _rollback_linit_temp.push_back(*reverse);
                }
                return _rollback_linit_temp;
            }
            void string_print()
            {
                for(string::const_iterator originate = begin();originate != end();originate++)
                {
                    std::cout << *originate;
                }
                std::cout << std::endl;
            }
            void string_reverse_print()
            {
                for(string::const_reverse_iterator originate = rbegin();originate != rend();originate--)
                {
                    std::cout << *originate;
                }
                std::cout << std::endl;
            }
            friend std::ostream& operator<<(std::ostream& string_ostream,const string &data_str);
            friend std::ostream& operator<<(std::ostream& string_ostream,string &data_str);
            friend std::istream& operator>>(std::istream& string_istream,string &data_str);
            string& operator=(const string& data_str)
            {
                //防止无意义拷贝
                if(this != &data_str)
                {
                    delete [] _data;
                    size_t capacity = data_str._capacity;
                    _data = new char[capacity + 1];
                    std::strncpy(_data,data_str._data,data_str.size());
                    _capacity = data_str._capacity;
                    _size = data_str._size;
                    _data[_size] = '\0';
                }
                return *this;
            }
            string& operator=(string&& data_str)
            {
                if(this != &data_str)
                {
                    delete [] _data;
                    _size = std::move(data_str._size);
                    _capacity = std::move(data_str._capacity);
                    _data = std::move(data_str._data);
                }
                return *this;
            }
            string& operator+=(const string& data_str)
            {
                size_t len = _size + data_str._size;
                if(allocate_resources(len) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return *this;
                }
                std::strncpy(_data + _size,data_str._data,data_str.size());
                _size = _size + data_str._size;
                _data[_size] = '\0';
                return *this;
            }
            bool operator==(const string& data_str)
            {
                if(_size != data_str._size)
                {
                    return false;
                }
                for(size_t i = 0;i < _size;i++)
                {
                    if(_data[i]!= data_str._data[i])
                    {
                        return false;
                    }
                }
                return true;
            }
            bool operator==(const string& data_str)const
            {
                if(_size != data_str._size)
                {
                    return false;
                }
                for(size_t i = 0;i < _size;i++)
                {
                    if(_data[i]!= data_str._data[i])
                    {
                        return false;
                    }
                }
                return true;
            }
            bool operator<(const string& data_str)
            {
                size_t min_len = _size < data_str._size? _size : data_str._size;
                for(size_t i = 0;i < min_len;i++)
                {
                    if(_data[i]!= data_str._data[i])
                    {
                        return _data[i] < data_str._data[i];
                    }
                }
                return _size < data_str._size;
            }
            bool operator<(const string& data_str) const
            {
                size_t min_len = _size < data_str._size? _size : data_str._size;
                for(size_t i = 0;i < min_len;i++)
                {
                    if(_data[i]!= data_str._data[i])
                    {
                        return _data[i] < data_str._data[i];
                    }
                }
                return _size < data_str._size;
            }
            bool operator<(string& data_str) const
            {
                size_t min_len = _size < data_str._size? _size : data_str._size;
                for(size_t i = 0;i < min_len;i++)
                {
                    if(_data[i]!= data_str._data[i])
                    {
                        return _data[i] < data_str._data[i];
                    }
                }
                return _size < data_str._size;
            }
            bool operator<(string& data_str)
            {
                size_t min_len = _size < data_str._size? _size : data_str._size;
                for(size_t i = 0;i < min_len;i++)
                {
                    if(_data[i]!= data_str._data[i])
                    {
                        return _data[i] < data_str._data[i];
                    }
                }
                return _size < data_str._size;
            }
            bool operator>(const string& data_str)
            {
                size_t min_len = _size < data_str._size? _size : data_str._size;
                for(size_t i = 0;i < min_len;i++)
                {
                    if(_data[i]!= data_str._data[i])
                    {
                        return _data[i] > data_str._data[i];
                    }
                }
                return _size > data_str._size;
            }
            bool operator>(const string& data_str) const
            {
                size_t min_len = _size < data_str._size? _size : data_str._size;
                for(size_t i = 0;i < min_len;i++)
                {
                    if(_data[i]!= data_str._data[i])
                    {
                        return _data[i] > data_str._data[i];
                    }
                }
                return _size > data_str._size;
            }
            char& operator[](const size_t& ergodic_value)
            {
                //引用就是出了函数作用域还能用其他的变量名访问，不需要拷贝就能访问，所以可以直接返回引用减少内存开销
                //在函数创建的变量出了函数作用域就不能访问了，这下才要返回拷贝值，如果返回引用就会未定义
                // if(ergodic_value >= _size)
                // {
                //     //如果越界了就返回第一个元素的引用
                //     return _data[0];
                // }
                //暴力返回
                return _data[ergodic_value]; //返回第ergodic_value个元素的引用
                //就像_data在外面就能访问它以及它的成员，所以这种就可以理解成出了函数作用域还在，进函数之前也能访问的就是引用
            }
            const char& operator[](const size_t& ergodic_value)const
            {
                // if(ergodic_value >= _size)
                // {
                //     //如果越界了就返回第一个元素的引用
                //     return _data[0];
                // }
                return _data[ergodic_value]; 
            }
            string operator+(const string& cpp_str_)
            {
                string _str_temp;
                size_t _str_temp_len = _size + cpp_str_._size;
                if(_str_temp.allocate_resources(_str_temp_len) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return string();
                }
                std::strncpy(_str_temp._data , _data,size());
                std::strncpy(_str_temp._data + _size , cpp_str_._data,cpp_str_.size());
                _str_temp._size = _size + cpp_str_._size;
                _str_temp._data[_str_temp._size] = '\0';
                return _str_temp;
            }
        };
        std::ostream& operator<<(std::ostream& string_ostream,const string &data_str) 
        {
            for(size_t i = 0;i < data_str._size;i++)
            {
                string_ostream << data_str._data[i];
            }
            return string_ostream;
        }
        std::istream& operator>>(std::istream& string_istream, string &data_str)
        {
            while(true)
            {
                char C_istream_str = string_istream.get();
                //gat函数只读取一个字符
                if(C_istream_str == '\n' || C_istream_str == EOF)
                {
                    break;
                }
                else
                {
                    data_str.push_back(C_istream_str);
                }
            }
            return string_istream;
        }
        std::ostream& operator<<(std::ostream& string_ostream,string &data_str) 
        {
            //当前没实现【】访问.可以用迭代器
            for(template_container::string_container::string::const_iterator originate = data_str.begin();originate != data_str.end();originate++)
            {
                string_ostream << *originate;
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
            using reverse_iterator = vector_type*;
            using const_reverse_iterator = const vector_type*;
        private:
            iterator _data_pointer;     //指向数据的头
            iterator _size_pointer;     //指向数据的尾
            iterator _capacity_pointer; //指向容量的尾
        public:
            iterator begin()        {   return _data_pointer;   }

            iterator end()          {   return _size_pointer;   }

            size_t size()           {   return _data_pointer ? (_size_pointer - _data_pointer) : 0;  }

            size_t capacity()       {   return _data_pointer ? (_capacity_pointer - _data_pointer) : 0; }

            size_t size() const     {   return _data_pointer ? (_size_pointer - _data_pointer) : 0; }

            size_t capacity() const {   return _data_pointer ? (_capacity_pointer - _data_pointer) : 0; }

            vector_type& Front()    {   return Head();      }

            vector_type& back()     {   return Tail();      }

            bool empty()            {   return size() == 0; }

            vector_type& Head()     {   return *_data_pointer;  }

            vector_type& Tail()     {   return *(_size_pointer-1);  }

            vector()
            {
                _data_pointer = nullptr;
                _size_pointer = nullptr;
                _capacity_pointer = nullptr;
            }
            vector(const size_t& sum_size , const vector_type& data = vector_type())
            :_data_pointer(new vector_type[sum_size]),_size_pointer(_data_pointer + sum_size)
            ,_capacity_pointer(_data_pointer + sum_size)
            {
                for(size_t i = 0;i < sum_size;i++)
                {
                    _data_pointer[i] = data;
                }
            }
            vector(std::initializer_list<vector_type> list_temp)
            :_data_pointer(new vector_type[list_temp.size()]),_size_pointer(_data_pointer + list_temp.size())
            ,_capacity_pointer(_data_pointer + list_temp.size())
            {
                //链式拷贝
                size_t i = 0;
                for(auto& e:list_temp)
                {
                    _data_pointer[i] = e;
                    i++;
                }
            }
            vector_type& find(const size_t& find_size_)
            {
                if(find_size_ >= size())
                {
                    //先默认返回空数组,但是需要提前写该类型的默认构造函数
                    static vector_type dummy;
                    return dummy;
                }
                return _data_pointer[find_size_];
            }
            vector<vector_type>& completion(const size_t& Completion_size_ , const vector<vector_type>& Completion_temp_)
            {
                size_t Completion_temp_size_ =size();
                size_t Completion_capacity_  =capacity();
                if(Completion_size_ > Completion_capacity_)
                {
                    resize(Completion_size_);
                    for(size_t i = Completion_capacity_; i < Completion_size_ ; i++)
                    {
                        _data_pointer[i] = Completion_temp_;
                    }
                }
                else
                {
                    if(Completion_size_ > Completion_temp_size_)
                    {
                        for(size_t i = Completion_temp_size_; i < Completion_size_ ; i++)
                        {
                            _data_pointer[i] = Completion_temp_;
                        }
                    }
                    else if (Completion_size_ < Completion_temp_size_)
                    {
                        _size_pointer = _data_pointer + Completion_size_;
                    }
                }
                return *this;
            }
            vector(const vector<vector_type>& temp_data)
            :_data_pointer(temp_data.capacity() ? new vector_type[temp_data.capacity()] : nullptr),
            _size_pointer(_data_pointer + temp_data.size()),_capacity_pointer(_data_pointer + temp_data.capacity())
            {
                for(size_t i = 0; i < temp_data.size();i++)
                {
                    _data_pointer[i] = temp_data._data_pointer[i];
                }
            }
            vector(vector<vector_type>&& temp_data)
            {
                template_container::algorithm::swap(_data_pointer, temp_data._data_pointer);
                template_container::algorithm::swap(_size_pointer, temp_data._size_pointer);
                template_container::algorithm::swap(_capacity_pointer, temp_data._capacity_pointer);
            }
            ~vector()
            {
                delete[] _data_pointer;
                _data_pointer = _size_pointer =_capacity_pointer = nullptr;
            }
            void swap(vector<vector_type>& temp_data)
            {
                template_container::algorithm::swap(_data_pointer, temp_data._data_pointer);
                template_container::algorithm::swap(_size_pointer, temp_data._size_pointer);
                template_container::algorithm::swap(_capacity_pointer, temp_data._capacity_pointer);
            }
            iterator Erase(iterator pos)
            {
                //删除元素
                iterator temp = pos + 1;
                while (temp != _size_pointer)
                {
                    //(temp-1)就是pos的位置，从pos位置开始覆盖，覆盖到倒数第1个结束，最后一个会被--屏蔽掉
                    *(temp-1) = *temp;
                    temp++;
                }
                --_size_pointer;
                return temp;
                //返回下一个位置地址
            }
            vector<vector_type>& resize(const size_t& new_capacity, const vector_type& data = vector_type())
            {
                size_t old_size = size();  // 先保存原来的元素数量
                if ((size_t)(_capacity_pointer - _data_pointer) < new_capacity) 
                {
                    //涉及到迭代器失效问题，不能调用size()函数，会释放未知空间
                    iterator new_data = new vector_type[new_capacity]; 
                    // 复制原先的数据
                    for (size_t i = 0; i < old_size; i++) 
                    {
                        new_data[i] = _data_pointer[i];
                    }
                    for(size_t i = old_size; i < new_capacity; i++)
                    {
                        new_data[i] = data;
                    }
                    delete [] _data_pointer;
                    _data_pointer = new_data;
                    //对于自定义类型delete会释放资源，而new_data是新new出来的因该不会导致资源泄露
                    // if(old_size == 0)
                    // {
                    //     _size_pointer = _data_pointer + new_capacity;  // 使用 old_size 来重建 _size_pointer
                    // }
                    // else
                    // {
                    //     _size_pointer = _data_pointer + old_size;  // 使用 old_size 来重建 _size_pointer
                    // }
                    _size_pointer = _data_pointer + old_size;  // 使用 old_size 来重建 _size_pointer
                    _capacity_pointer = _data_pointer + new_capacity;
                }
                return *this;
            }
            vector<vector_type>& push_back(const vector_type& push_back_temp_)
            {
                if(_size_pointer == _capacity_pointer)
                {
                    size_t push_banck_size_ = _data_pointer == nullptr ? 10 : (size_t)(_capacity_pointer-_data_pointer)*2;
                    resize(push_banck_size_);
                }
                //注意—_size_pointer是原生迭代器指针，需要解引用才能赋值
                *_size_pointer = push_back_temp_;
                _size_pointer++;
                return *this;
            }
            vector<vector_type>& push_back(vector_type&& push_back_temp_)
            {
                if(_size_pointer == _capacity_pointer)
                {
                    size_t push_banck_size_ = _data_pointer == nullptr ? 10 : (size_t)(_capacity_pointer-_data_pointer)*2;
                    resize(push_banck_size_);
                }
                //注意—_size_pointer是原生迭代器指针，需要解引用才能赋值
                *_size_pointer = std::move(push_back_temp_);//转换移动语义
                _size_pointer++;
                return *this;
            }
            vector<vector_type>& pop_back() 
            {
                if (_size_pointer > _data_pointer) 
                { // 至少有一个元素
                    --_size_pointer; // 尾指针前移
                }
                return *this;
            }
            vector<vector_type>& push_front(const vector_type& pop_back_temp_)
            {
                //头插
                if(_size_pointer == _capacity_pointer)
                {
                    size_t pop_banck_size_ = _data_pointer == nullptr ? 10 : (size_t)(_capacity_pointer-_data_pointer)*2;
                    resize(pop_banck_size_);
                }
                for(size_t pop_back_for_size = size();pop_back_for_size>0;--pop_back_for_size)
                {
                    _data_pointer[pop_back_for_size] = _data_pointer[pop_back_for_size -1];
                }
                *_data_pointer = pop_back_temp_;
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
            vector_type& operator[](const size_t& _size_operator)
            {
                return _data_pointer[_size_operator];
            }
            const vector_type& operator[](const size_t& _size_operator)const 
            {
                return _data_pointer[_size_operator];
            }
            vector<vector_type>& operator=(const vector<vector_type>&vector_temp_)
            {
                if (this != &vector_temp_) 
                {
                    vector<vector_type> temp(vector_temp_); // 拷贝构造
                    swap(temp); // 交换资源，temp析构时会释放原资源
                }
                return *this;
            }
            vector<vector_type>& operator=(const vector<vector_type>&& _temp_)
            {
                if( this != &_temp_)
                {
                    template_container::algorithm::swap(_data_pointer, _temp_._data_pointer);
                    template_container::algorithm::swap(_size_pointer, _temp_._size_pointer);
                    template_container::algorithm::swap(_capacity_pointer, _temp_._capacity_pointer);
                }
                return *this;
            }
            vector<vector_type>& operator+=(const vector<vector_type>& _temp_)
            {
                if(_temp_.size() == 0|| _temp_._data_pointer == nullptr)
                {
                    return *this;
                }
                size_t _temp_size_ = _temp_.size();
                size_t _size_ = size();
                size_t _capacity_ = capacity();
                if(_temp_size_ + _size_ > _capacity_)
                {
                    resize(_temp_size_ + _size_);
                
                } 
                size_t sum = 0;
                for(size_t i = _size_ ; i < (_temp_size_ + _size_); i++)
                {
                    _data_pointer[i] = _temp_._data_pointer[sum++];
                }
                _size_pointer = _data_pointer + (_temp_size_ + _size_);
                return *this;
            }
            template <typename const_vector_output_templates>
            friend std::ostream& operator<< (std::ostream& vector_ostream, const vector<const_vector_output_templates>& Dynamic_arrays_data);
        };
        template <typename const_vector_output_templates>
        std::ostream& operator<<(std::ostream& vector_ostream, const vector<const_vector_output_templates>& Dynamic_arrays_data)
        {
            for(size_t i = 0; i < Dynamic_arrays_data.size(); i++)
            {
                vector_ostream << Dynamic_arrays_data[i] << " ";
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

                list_container_node(const list_type_function_node& data = list_type_function_node())
                :_prev(nullptr), _next(nullptr), _data(data)
                {
                    //列表初始化
                }
                
            };
            template <typename listNodeTypeIterator ,typename Ref ,typename Ptr >
            class list_iterator
            {
            public:
                //迭代器类
                using container_node      = list_container_node<listNodeTypeIterator> ;
                using iterator  = list_iterator<listNodeTypeIterator ,listNodeTypeIterator& ,listNodeTypeIterator*>;
                using reference = Ref ;
                using pointer   = Ptr ;
                container_node* _node;
                list_iterator(container_node* node)
                :_node(node)
                {
                    ;//拿一个指针来构造迭代器
                }
                Ref operator*()
                {
                    //返回该节点的自定义类型的数据
                    return _node->_data;
                }
                list_iterator& operator++()
                {
                    //先加在用
                    _node = _node -> _next;
                    return *this;
                    //返回类型名，如果为迭代器就会因为const 报错
                }
                list_iterator operator++(int)
                {
                    //先用在加
                    list_iterator temp(_node);
                    _node = _node->_next;
                    //把本体指向下一个位置
                    return temp;
                }
                list_iterator& operator--()
                {
                    _node = _node->_prev;
                    return *this;
                }
                list_iterator operator--(int)
                {
                    list_iterator temp (_node);
                    _node = _node->_prev;
                    return temp;
                }
                bool operator!= (const list_iterator& _iterator_temp_)
                {
                    //比较两个指针及其上一个和下一个指针地址
                    return _node != _iterator_temp_._node;
                }
                Ptr operator->()
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
                reverse_list_iterator(iterator it)
                :_it(it)
                {
                    ;
                } 
                Ref& operator*()
                {
                    //因为反向迭代器起始位置在哨兵节点所以通过指向上一个来找到准确位置
                    //正好到rend位置停下来的时候已经遍历到rend位置
                    iterator temp(_it);
                    --(temp);
                    return *temp;
                }
                Ptr operator->()
                {
                    //两者函数差不多可直接调用
                    return &(operator*());
                }
                reverse_list_iterator& operator++()
                {
                    --_it;
                    return *this;
                }
                reverse_list_iterator operator++(int)
                {
                    reverse_list_iterator _temp (_it);
                    --_it;
                    return _temp;
                }
                reverse_list_iterator& operator--()
                {
                    ++_it;
                    return *this;
                }
                reverse_list_iterator operator--(int)
                {
                    reverse_list_iterator _temp (_it);
                    ++_it;
                    return _temp;
                }
                bool operator!=(const const_reverse_list_iterator& _temp_)
                {
                    return _it != _temp_._it;
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
            list()
            {
                create_head();
            }
            ~list()
            {
                Clear();
                delete _head;
                _head = nullptr;
            }
            list(iterator first , iterator last)
            {
                //通过另一个list对象构建一个list
                create_head();
                //已经创建一个哨兵节点
                while (first != last)
                {
                    push_back(*first);
                    ++first;
                }
            }
            list(std::initializer_list<list_type> list_temp)
            {
                //通过初始化列表构建一个list
                create_head();
                for(auto& e:list_temp)
                {
                    push_back(e);
                }
            }
            list(const_iterator first , const_iterator last)
            {
                //通过另一个list对象构建一个list
                create_head();
                //已经创建一个哨兵节点
                while (first != last)
                {
                    push_back(*first);
                    ++first;
                }
            }
            list(const list<list_type>& _list_data)
            {
                //拷贝构造
                create_head();
                list<list_type> _temp_ (_list_data.cbegin(),_list_data.cend());
                swap(_temp_);
            }
            list(list<list_type>&& _list_data)
            {
                //移动构造
                create_head();
                _head = std::move(_list_data._head);
                _list_data._head = nullptr;
            }
            void swap(template_container::list_container::list<list_type>& _swap_temp)
            {
                template_container::algorithm::swap(_head,_swap_temp._head);
            }
            iterator begin()
            {
                //因为_head为哨兵位，所以哨兵下一个结点为有效数据
                return iterator(_head ->_next);
            }
            iterator end()
            {
                return iterator(_head);
            }
            const_iterator cbegin()const
            {
                //因为_head为哨兵位，所以哨兵下一个结点为有效数据
                return const_iterator(_head ->_next);
            }
            const_iterator cend()const
            {
                return const_iterator(_head);
            }
            size_t size()const
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
            bool empty()const
            {
                return _head->_next == _head;
            }
            reverse_iterator rbegin()
            {
                return reverse_iterator(_head->_prev);
            }
            reverse_iterator rend()
            {
                return reverse_iterator(_head);
            }
            reverse_const_iterator rcbegin()const
            {
                return reverse_const_iterator(cend());
            }
            reverse_const_iterator rcend()const
            {
                return reverse_const_iterator(cbegin());
            }
            /*
            元素访问操作
            */
            list_type& Front()
            {
                return _head->_next->_data;
            }

            const list_type& Front()const
            {
                return _head->_next->_data;
            }

            list_type& back()
            {
                return _head->_prev->_data;
            }

            const list_type& back()const
            {
                return _head->_prev->_data;
            }
            /*
            插入删除操作
            */
            void push_back(const list_type& push_back_data)
            {
                insert(end(),push_back_data);
            }
            void PushFront(const list_type& push_front_data)
            {
                //插入到头
                insert(begin(),push_front_data);
            }
            void pop_back() 
            { 
                //删除尾
                Erase(--end()); 
            }
            iterator pop_front() 
            { 
                //删除头
                return Erase(begin()); 
            }
            iterator insert(iterator pos ,const list_type& val)
            {
                container_node* Pnew_node = new container_node(val);
                //开辟新节点
                container_node* Pcur = pos._node;
                //保存pos位置的值
                Pnew_node->_prev = Pcur->_prev;
                Pnew_node->_next = Pcur;
                Pnew_node->_prev->_next = Pnew_node;
                Pcur->_prev = Pnew_node;
                return iterator(Pnew_node);
            }
            iterator Erase(iterator pos)
            {
                // 找到待删除的节点
                container_node* pDel = pos._node;
                container_node* pRet = pDel->_next;

                // 将该节点从链表中拆下来并删除
                pDel->_prev->_next = pDel->_next;
                pDel->_next->_prev = pDel->_prev;
                delete pDel;

                return iterator(pRet);
            }
            void resize(size_t newsize, const list_type& data = list_type())
            {
                //将data插入到链表中
                size_t oldsize = size();
                if (newsize <= oldsize)
                {
                    // 有效元素个数减少到newsize
                    while (newsize < oldsize)
                    {
                        pop_back();
                        oldsize--;
                    }
                }
                else
                {
                    while (oldsize < newsize)
                    {
                        push_back(data);
                        oldsize++;
                    }
                }
            }
            void Clear()
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
            list& operator=(list<list_type> _lsit_temp)
            {
                //运算符重载
                if( this != &_lsit_temp)
                {
                    swap(_lsit_temp);
                }
                return *this;
            }
            list operator+(const list<list_type>& _list_temp_)
            {
                list<list_type> _return_temp_ (cbegin(),cend());
                const_iterator _begin = _list_temp_.cbegin();
                const_iterator _end  = _list_temp_.cend();
                while(_begin != _end)
                {
                    _return_temp_.push_back(*_begin);
                    ++_begin;
                }
                return _return_temp_;
            }
            list& operator+=(const list<list_type>& _lsit_temp_)
            {
                const_iterator _begin = _lsit_temp_.cbegin();
                const_iterator _end  = _lsit_temp_.cend();
                while(_begin != _end)
                {
                    push_back(*_begin);
                    ++_begin;
                }
                return *this;
            }
            template <typename const_list_output_templates>
            friend std::ostream& operator<< (std::ostream& list_ostream, const list<const_list_output_templates>& Dynamic_arrays_data);
            
            template <typename ListOutputTemplates>
            friend std::ostream& operator<< (std::ostream& list_ostream, list<ListOutputTemplates>& Dynamic_arrays_data);
        };
        template <typename const_list_output_templates>
        std::ostream& operator<< (std::ostream& list_ostream, const list<const_list_output_templates>& Dynamic_arrays_data)
        {
            //typename声明这是一个类型而不是表达式
            typename list<const_list_output_templates>::const_iterator it = Dynamic_arrays_data.cbegin();
            while (it != Dynamic_arrays_data.cend()) 
            {
                list_ostream << *it << " ";
                ++it;
            }
            return list_ostream;
        }

        template <typename ListOutputTemplates>
        std::ostream& operator<< (std::ostream& list_ostream, list<ListOutputTemplates>& Dynamic_arrays_data)
        {
            //typename声明这是一个类型而不是表达式
            typename list<ListOutputTemplates>::iterator it = Dynamic_arrays_data.begin();
            while (it != Dynamic_arrays_data.end()) 
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
            vector_based_stack ContainerStackTemp;
        public:
            ~stack()
            {
                ;
            }
            void push(const stack_type& _stack_temp)
            {
                //插入尾
                ContainerStackTemp.push_back(_stack_temp);
            }
            void pop()
            {
                //删除尾
                ContainerStackTemp.pop_back();
            }
            size_t size()
            {
                return ContainerStackTemp.size();
            }
            bool empty()
            {
                return ContainerStackTemp.empty();
            } 
            stack_type& top()
            {
                return ContainerStackTemp.back();
            }
            stack(const stack<stack_type>& _stack_temp)
            {
                ContainerStackTemp = _stack_temp.ContainerStackTemp;
            }
            stack( stack<stack_type>&& _stack_temp)
            {
                ContainerStackTemp = std::move(_stack_temp.ContainerStackTemp);//std::move将对象转换为右值引用
            }
            stack(std::initializer_list<stack_type> _stack_temp)
            {
                for(auto& e:_stack_temp)
                {
                    ContainerStackTemp.push_back(e);
                }
            }
            stack(const stack_type& _stack_temp)
            {
                ContainerStackTemp.push_back(_stack_temp);
            }
            stack& operator= (const stack<stack_type>& _stack_temp)
            {
                if(this != &_stack_temp)
                {
                    ContainerStackTemp = _stack_temp.ContainerStackTemp;
                }
                return *this;
            }
            stack& operator=(stack<stack_type>&& _stack_temp)
            {
                if(this != &_stack_temp)
                {
                    ContainerStackTemp = std::move(_stack_temp.ContainerStackTemp);
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
            ~queue()
            {
                ;
            }
            void push(const queue_type& _queue_temp)
            {
                list_object.push_back(_queue_temp);
            }
            void pop ()
            {
                list_object.pop_front();
                //list返回的是指向下一个位置的正向迭代器
                //vector返回的是整个容器
            }
            size_t size()
            {
                //返回元素个数
                return list_object.size();
            }
            bool empty()
            {
                //判断容器是否为空
                return list_object.empty();
            }
            queue_type& Front()
            {
                //查看头数据
                return list_object.Front();
            }
            queue_type& back()
            {
                //查看尾数据
                return list_object.back();
            }
            queue(const queue<queue_type>& _queue_temp)
            {
                //拷贝构造
                list_object = _queue_temp.list_object;
            }
            queue(queue<queue_type>&& _queue_temp)
            {
                //移动构造
                list_object = std::move(_queue_temp.list_object);
            }
            queue(std::initializer_list<queue_type> _queue_temp)
            {
                //链式构造
                for(auto& e:_queue_temp)
                {
                    list_object.push_back(e);
                }
            }
            queue(const queue_type& _queue_temp)
            {
                list_object.push_back(_queue_temp);
            }
            queue() = default;
            queue& operator= (const queue<queue_type>& _queue_temp)
            {
                if(this != &_queue_temp)
                {
                    list_object = _queue_temp.list_object;
                }
                return *this;
            }
            queue& operator=(queue<queue_type>&& _queue_temp)
            {
                if(this != &_queue_temp)
                {
                    list_object = std::move(_queue_temp.list_object);
                }
                return *this;
            }
        };
        /*############################     priority_queue 适配器     ############################*/
        template <typename priority_queue_type,
        typename container_imitate_function = template_container::imitation_functions::less<priority_queue_type>,
        typename vector_based_priority_queue = template_container::vector_container::vector<priority_queue_type>>
        class priority_queue
        {
            //创建容器对象
            vector_based_priority_queue vector_container_object;
            container_imitate_function function_policy;
            //仿函数对象

            void PriorityQueueAdjustUpwards(int Adjust_upwards_child)
            {
                //向上调整算法
                int parent = (Adjust_upwards_child-1)/2;
                while(Adjust_upwards_child > 0)
                {
                    if(function_policy(vector_container_object[parent],vector_container_object[Adjust_upwards_child]))
                    {
                        template_container::algorithm::swap(vector_container_object[parent],vector_container_object[Adjust_upwards_child]);
                        Adjust_upwards_child = parent;
                        parent = (Adjust_upwards_child-1)/2;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            void PriorityQueueAdjustDownwards(int parent = 0)
            {
                int priority_queue_Adjust_downwards_child = (parent*2)+1;
                while(priority_queue_Adjust_downwards_child < (int)vector_container_object.size())
                {
                    int left = priority_queue_Adjust_downwards_child;
                    int right =left+1;
                    if( right < (int)vector_container_object.size() && function_policy(vector_container_object[left],vector_container_object[right]))
                    {
                        //大堆找出左右节点哪个孩子大
                        priority_queue_Adjust_downwards_child = right;
                    }
                    if(function_policy(vector_container_object[parent],vector_container_object[priority_queue_Adjust_downwards_child]))
                    {
                        //建大堆把小的换下去，建小堆把大的换下去
                        template_container::algorithm::swap( vector_container_object[parent] , vector_container_object[priority_queue_Adjust_downwards_child]);

                        //换完之后如果是大堆，则父亲节点是较大的值，需要更新孩子节点继续向下找比孩子节点大的值，如果有继续交换
                        parent = priority_queue_Adjust_downwards_child;
                        priority_queue_Adjust_downwards_child = (parent*2)+1;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        public:
            ~priority_queue()  = default;
            void push(const priority_queue_type& Function_templates_priority_queue_push_back)
            {
                vector_container_object.push_back(Function_templates_priority_queue_push_back);
                PriorityQueueAdjustUpwards((int)vector_container_object.size()-1);
            }
            priority_queue_type& top()
            {
                return vector_container_object.Front();
            }
            bool empty()
            {
                return vector_container_object.empty();
            }
            size_t size()
            {
                return vector_container_object.size();
            }
            void pop()
            {
                template_container::algorithm::swap(vector_container_object[0],vector_container_object[vector_container_object.size()-(size_t)1]);
                vector_container_object.pop_back();
                PriorityQueueAdjustDownwards();
            }
            priority_queue()
            {
                ;
            }
            priority_queue(std::initializer_list<priority_queue_type> list_temp)
            {
                //通过初始化列表构建一个list
                for(auto& e:list_temp)
                {
                    push(e);
                }
            }
            priority_queue(const priority_queue& _priority_queue_temp)
            {
                //拷贝构造
                vector_container_object = _priority_queue_temp.vector_container_object;
            }
            priority_queue(priority_queue&& _priority_queue_temp)
            :function_policy(_priority_queue_temp.function_policy)
            {
                //移动构造
                vector_container_object = std::move(_priority_queue_temp.vector_container_object);
            }
            priority_queue(const priority_queue_type& _priority_queue_temp)
            {
                vector_container_object.push_back(_priority_queue_temp);
                PriorityQueueAdjustUpwards((int)vector_container_object.size()-1);
            }
            priority_queue& operator=(priority_queue&& _priority_queue_temp)
            {
                //移动赋值
                if(this != &_priority_queue_temp)
                {
                    vector_container_object = std::move(_priority_queue_temp.vector_container_object);
                    function_policy = _priority_queue_temp.function_policy;
                }
                return *this;
            }
            priority_queue& operator=(const priority_queue& _priority_queue_temp)
            {
                //拷贝赋值
                if(this != &_priority_queue_temp)
                {
                    vector_container_object = _priority_queue_temp.vector_container_object;
                    function_policy = _priority_queue_temp.function_policy;
                }
                return *this;
            }
        };
    }
    namespace tree_container
    {
        /*############################     binary_search_tree 容器     ############################*/
        template <typename binary_search_tree_type,typename container_imitate_function = template_container::imitation_functions::less <binary_search_tree_type> >
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
                binary_search_tree_type_node(const binary_search_tree_type& data = binary_search_tree_type())
                :_left(nullptr),_right(nullptr),_data(data)
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
            container_node* _root;
            container_imitate_function function_policy;
            void interior_middle_order_traversal(container_node* _ROOT_Temp)
            {
                //中序遍历函数
                template_container::stack_adapter::stack<container_node*> _staic_temp_;
                while(_ROOT_Temp != nullptr || !_staic_temp_.empty())
                {
                    while(_ROOT_Temp!= nullptr)
                    {
                        _staic_temp_.push(_ROOT_Temp);
                        //压栈
                        _ROOT_Temp = _ROOT_Temp->_left;
                    }
                    // 访问栈顶节点
                    _ROOT_Temp = _staic_temp_.top();
                    //弹出栈顶元素，刷新栈顶元素，栈顶元素会变成之前压入栈的节点的父节点
                    
                    _staic_temp_.pop();
                    std::cout <<  _ROOT_Temp->_data << " ";
                    // std::cout << &_ROOT_Temp->_data << " ";
                    //检查地址是不是值拷贝
                    // 转向右子树
                    _ROOT_Temp = _ROOT_Temp->_right;
                }
            }
            size_t interior_middle_order_traversal(container_node* _ROOT_Temp,size_t& _size_temp_ )
            {
                template_container::stack_adapter::stack<container_node*> _staic_temp_;
                while(_ROOT_Temp != nullptr || !_staic_temp_.empty())
                {
                    while(_ROOT_Temp!= nullptr)
                    {
                        _staic_temp_.push(_ROOT_Temp);
                        //压栈
                        _ROOT_Temp = _ROOT_Temp->_left;
                    }
                    // 访问栈顶节点
                    _ROOT_Temp = _staic_temp_.top();
                    //弹出栈顶元素，刷新栈顶元素，栈顶元素会变成之前压入栈的节点的父节点
                    
                    _staic_temp_.pop();
                    _size_temp_++;
                    // 转向右子树
                    _ROOT_Temp = _ROOT_Temp->_right;
                }
                return _size_temp_;
            }
            void interior_pre_order_traversal(container_node* _ROOT_Temp )
            {
                //前序遍历，最外左子树全部压栈
                if(_ROOT_Temp == nullptr)
                {
                    return;
                }
                container_node* _Pre_order_traversal_test = _ROOT_Temp;
                template_container::stack_adapter::stack<container_node*> stack_Temp;
                stack_Temp.push(_Pre_order_traversal_test);
                //不能添加|| _Pre_order_traversal_test != nullptr ，因为最后一层循环后_Pre_order_traversal_test还是为真后面循环无意义，反之还会破环性质
                while( !stack_Temp.empty() )
                {
                    _Pre_order_traversal_test = stack_Temp.top();
                    stack_Temp.pop();

                    std::cout << _Pre_order_traversal_test->_data << " ";
                    if(_Pre_order_traversal_test->_right != nullptr)
                    {
                        stack_Temp.push(_Pre_order_traversal_test->_right);
                    }
                    if(_Pre_order_traversal_test->_left != nullptr)
                    {
                        stack_Temp.push(_Pre_order_traversal_test->_left);
                    }
                    //修改逻辑错误，先压右子树再压左子树，因为这是栈
                }
            }
            void Clear()
            {
                if(_root == nullptr)
                {
                    return;
                }
                //循环释放资源
                template_container::stack_adapter::stack<container_node*> _staic_clear_temp_;
                _staic_clear_temp_.push(_root);
                while(_staic_clear_temp_.empty() == false)
                {
                    container_node* _ROOT_Temp = _staic_clear_temp_.top();
                    //取出元素，把左右节点入进去
                    _staic_clear_temp_.pop();
                    if(_ROOT_Temp->_left!= nullptr)
                    {
                        _staic_clear_temp_.push(_ROOT_Temp->_left);
                    }
                    if(_ROOT_Temp->_right!= nullptr)
                    {
                        _staic_clear_temp_.push(_ROOT_Temp->_right);
                    }
                    delete _ROOT_Temp;
                }
                _root = nullptr;
            }
        public:
            ~binary_search_tree()
            {
                Clear();
            }
            // 构造函数，使用初始化列表来初始化二叉搜索树
            binary_search_tree(std::initializer_list<binary_search_tree_type> list_temp)
            {
                for(auto& e:list_temp)
                {
                    push(e);
                }
            }
            binary_search_tree(const binary_search_tree_type& BST_Temp = binary_search_tree_type(),container_imitate_function com_temp = container_imitate_function())
            :_root(nullptr),function_policy(com_temp)
            {   
                _root = new container_node(BST_Temp);
            }
            binary_search_tree(binary_search_tree&& _Binary_search_tree_temp)
            :function_policy(_Binary_search_tree_temp.function_policy),_root(nullptr)
            {
                _root = std::move(_Binary_search_tree_temp._root);
                _Binary_search_tree_temp._root = nullptr;
            }
            binary_search_tree(const binary_search_tree& _Binary_search_tree_temp)
            :_root(nullptr),function_policy(_Binary_search_tree_temp.function_policy)
            //这个拷贝构造不需要传模板参数，因为模板参数是在编译时确定的，而不是在运行时确定的，对于仿函数，直接拿传进来的引用初始化就可以了
            {
                //拷贝构造，时间复杂度为O(n)
                container_node* _Binary_search_tree_temp_copy = _Binary_search_tree_temp._root;
                if(_Binary_search_tree_temp_copy == nullptr)
                {
                    return;
                }
                template_container::stack_adapter::stack<template_container::practicality::pair<container_node*,container_node**> > _staic_temp_;
                //注意这里把本地_ROOT类型传过去，是因为要对本地的_ROOT进行操作，所以要传二级指针
                //这里传引用也不行，这里的对象是动态变化的，所以传引用也不行
                //如果是对全局的_ROOT进行操作，就传一级指针
                _staic_temp_.push(template_container::practicality::pair<container_node*,container_node**>(_Binary_search_tree_temp_copy,&_root));
                while( !_staic_temp_.empty() )
                {
                    auto _staic_temp_pair = _staic_temp_.top();
                    _staic_temp_.pop();
                    *(_staic_temp_pair.second) = new container_node(_staic_temp_pair.first->_data);
                    // container_node* _staic_temp_pair_second = *(_staic_temp_pair.second);
                    // if(_staic_temp_pair.first->_left!= nullptr)
                    // {
                    //     _staic_temp_.push(MY_Template::practicality::pair<container_node*,container_node**>(_staic_temp_pair.first->_left,&_staic_temp_pair_second->_left));
                    // }
                    // if(_staic_temp_pair.first->_right!= nullptr)
                    // {
                    //     _staic_temp_.push(MY_Template::practicality::pair<container_node*,container_node**>(_staic_temp_pair.first->_right,&_staic_temp_pair_second->_right));
                    // }
                    //移除临时变量，直接使用指针解引用
                    if(_staic_temp_pair.first->_right!= nullptr)
                    {
                        _staic_temp_.push(template_container::practicality::pair<container_node*,container_node**>(_staic_temp_pair.first->_right,&((*_staic_temp_pair.second)->_right)));
                    }
                    if(_staic_temp_pair.first->_left!= nullptr)
                    {
                        _staic_temp_.push(template_container::practicality::pair<container_node*,container_node**>(_staic_temp_pair.first->_left,&((*_staic_temp_pair.second)->_left)));
                    }
                }
            }
            void middle_order_traversal()
            {
                //中序遍历函数
                interior_middle_order_traversal(_root);
            }
            void pre_order_traversal()
            {
                interior_pre_order_traversal(_root);
            }
            bool push(const binary_search_tree_type& data)
            {
                //尾上插入函数
                if(_root == nullptr)
                {
                    _root = new container_node(data);
                    return true;
                }
                else
                {
                    container_node* _ROOT_Temp = _root;
                    container_node* _ROOT_Temp_Parent = nullptr;
                    while(_ROOT_Temp!= nullptr)
                    {
                        _ROOT_Temp_Parent = _ROOT_Temp;
                        if(!function_policy(data, _ROOT_Temp->_data) && !function_policy(_ROOT_Temp->_data, data))
                        {
                            //改用仿函数特性，判断是否有重复元素,防止自定义类型没有重载==运算符
                            return false;
                        }
                        else if(function_policy(data , _ROOT_Temp->_data))
                        {
                            _ROOT_Temp = _ROOT_Temp->_left;
                        }
                        else
                        {
                            _ROOT_Temp = _ROOT_Temp->_right;
                        }
                    }
                    //新开节点链接
                    container_node* _ROOT_Temp_Node = new container_node(data);
                    //链接节点
                    if(function_policy(data , _ROOT_Temp_Parent->_data))
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
            binary_search_tree& Pop(const binary_search_tree_type& data)
            {
                //删除节点
                container_node* _ROOT_Temp = _root;
                container_node* _ROOT_Temp_Parent = nullptr;
                while( _ROOT_Temp != nullptr )
                {
                    if(data == _ROOT_Temp->_data)
                    {
                        //找到节点
                        if(_ROOT_Temp->_left == nullptr)
                        {
                            //左子树为空,下面判断要删除的节点是父节点的左子树还是右子树，防止多删和误删
                            if (_ROOT_Temp_Parent == nullptr)
                            {
                                // 当前节点是根节点，直接更新 _root
                                _root = _ROOT_Temp->_right;
                            }
                            else
                            {
                                if(_ROOT_Temp_Parent->_left == _ROOT_Temp)
                                {
                                    //根节点
                                    _ROOT_Temp_Parent->_left = _ROOT_Temp->_right;
                                }   
                                else
                                {
                                    //非根节点
                                    _ROOT_Temp_Parent->_right = _ROOT_Temp->_right;
                                }
                            }
                            delete _ROOT_Temp;
                            _ROOT_Temp = nullptr;
                            return *this;
                        }
                        else if(_ROOT_Temp->_right == nullptr)
                        {
                            if (_ROOT_Temp_Parent == nullptr)
                            {
                                // 防止当前节点是根节点，无法解引用，直接更新 _root
                                _root = _ROOT_Temp->_left;
                            }
                            else
                            {
                                if(_ROOT_Temp_Parent->_left == _ROOT_Temp)
                                {
                                    _ROOT_Temp_Parent->_left = _ROOT_Temp->_left;
                                }
                                else
                                {
                                    _ROOT_Temp_Parent->_right = _ROOT_Temp->_left;
                                }
                            }
                            delete _ROOT_Temp;
                            _ROOT_Temp = nullptr;
                            return *this;	
                        }
                        else
                        {
                            //左右子树都不为空，找右子树的最左节点
                            container_node* _ROOT_Temp_right_min = _ROOT_Temp->_right;
                            container_node* _ROOT_Temp_test_Parent = _ROOT_Temp;
                            while(_ROOT_Temp_right_min->_left != nullptr)
                            {
                                _ROOT_Temp_test_Parent = _ROOT_Temp_right_min;
                                _ROOT_Temp_right_min = _ROOT_Temp_right_min->_left;
                            }
                            //找到最左节点	
                            template_container::algorithm::swap(_ROOT_Temp->_data,_ROOT_Temp_right_min->_data);
                            //因为右树最左节点已经被删，但是还需要把被删的上一节点的左子树指向被删节点的右子树，不管右子树有没有节点都要连接上
                            if(_ROOT_Temp_test_Parent == _ROOT_Temp)
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
                    else if(function_policy(data, _ROOT_Temp->_data))
                    {
                        _ROOT_Temp_Parent = _ROOT_Temp;
                        _ROOT_Temp = _ROOT_Temp->_left;
                    }
                    else
                    {
                        _ROOT_Temp_Parent = _ROOT_Temp;
                        _ROOT_Temp = _ROOT_Temp->_right;
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
                size_t _size = 0;
                return interior_middle_order_traversal(_root,_size);
            }
            container_node* find(const binary_search_tree_type& data)
            {
                //查找函数
                container_node* _ROOT_Find = _root;
                while(_ROOT_Find!= nullptr)
                {
                    if(data == _ROOT_Find->_data)
                    {
                        return _ROOT_Find;
                    }
                    else if(function_policy(data, _ROOT_Find->_data))
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
            void insert(const binary_search_tree_type& former_data,const binary_search_tree_type& latter_data)
            {
                //在former_data后面插入latter_data
                container_node* _ROOT_former_data = find(former_data);
                //插入节点
                if(_ROOT_former_data == nullptr)
                {
                    return;
                }
                else
                {
                    container_node* _ROOT_latter_data = new container_node(latter_data);
                    _ROOT_latter_data->_left = _ROOT_former_data->_right;
                    _ROOT_former_data->_right = _ROOT_latter_data;
                }
            }
            binary_search_tree& operator=(const binary_search_tree& _Binary_search_tree_temp)
            {
                //赋值运算符重载
                if(this != &_Binary_search_tree_temp)
                {
                    Clear();
                    function_policy = _Binary_search_tree_temp.function_policy;
                    binary_search_tree _Binary_search_tree_temp_copy = _Binary_search_tree_temp;
                    template_container::algorithm::swap(_Binary_search_tree_temp_copy._root,_root);
                }
                return *this;
            }
            binary_search_tree& operator=(binary_search_tree && _Binary_search_tree_temp)
            {
                //移动赋值运算符重载
                if(this != &_Binary_search_tree_temp)
                {
                    Clear();
                    function_policy = _Binary_search_tree_temp.function_policy;
                    _root = std::move(_Binary_search_tree_temp._root);
                    _Binary_search_tree_temp._root = nullptr;
                }
                return *this;
            }

        };
        /*############################     avl_tree 容器     ############################*/
        template <typename avl_tree_type_k,     typename avl_tree_type_v,
        typename container_imitate_function = template_container::imitation_functions::less < avl_tree_type_k >,
        typename avl_tree_node_pair = template_container::practicality::pair<avl_tree_type_k,avl_tree_type_v> >
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
                avl_tree_type_node(const avl_tree_type_k& Tree_Node_temp_ = avl_tree_type_k(),const avl_tree_type_v& Tree_Node_temp_2 = avl_tree_type_v())
                :_data(Tree_Node_temp_,Tree_Node_temp_2),_left(nullptr),_right(nullptr),_parent(nullptr),_balance_factor(0)
                {
                    ;
                }
                avl_tree_type_node(const avl_tree_node_pair& AVL_Tree_pair_temp)
                :_data(AVL_Tree_pair_temp),_left(nullptr),_right(nullptr),_parent(nullptr),_balance_factor(0)
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
                avl_tree_iterator(iterator_node* _Node_Temp)
                :_node_iterator_ptr(_Node_Temp)
                {
                    ;
                }
                Ptr operator->()
                {
                    return &(_node_iterator_ptr->_data);
                }
                Ref& operator*()
                {
                    return _node_iterator_ptr->_data;
                }
                bool operator!=(const self& Self_temp)
                {
                    return _node_iterator_ptr != Self_temp._node_iterator_ptr;
                }
                bool operator==(const self& Self_temp) 
                {
                    return _node_iterator_ptr == Self_temp._node_iterator_ptr;
                }
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
                        container_node* _Node_temp = _node_iterator_ptr;
                        while(_Node_temp->_parent != nullptr && _Node_temp == _Node_temp->_parent->_right)
                        {
                            _Node_temp = _Node_temp->_parent;
                        }
                        _node_iterator_ptr = _Node_temp->_parent;
                    }
                    return *this;
                }
                self operator++(int)
                {
                    self temp = *this;
                    ++(*this);
                    return temp;
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
                        container_node* _Node_temp = _node_iterator_ptr;
                        while(_Node_temp->_parent != nullptr && _Node_temp == _Node_temp->_parent->_left)
                        {
                            _Node_temp = _Node_temp->_parent;
                        }
                        _node_iterator_ptr = _Node_temp->_parent;
                    }
                    return *this;
                }
                self operator--(int)
                {
                    self temp = *this;
                    --(*this);
                    return temp;
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
                avl_tree_reverse_iterator(iterator _it_Temp)
                :_it(_it_Temp)
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
                bool operator!=(const self& Self_temp)
                {
                    return _it != Self_temp._it;
                }
                bool operator==(const self& Self_temp)
                {
                    return _it == Self_temp._it;
                }
                self& operator++()
                {
                    --_it;
                    return *this;
                }
                self operator++(int)
                {
                    self temp = *this;
                    --(*this);
                    return temp;
                }
                self& operator--()
                {
                    ++_it;
                    return *this;
                }
                self operator--(int)
                {
                    self temp = *this;
                    ++(*this);
                    return temp;
                }
                
            };
            using container_node = avl_tree_type_node;
            container_node* _root;

            container_imitate_function function_policy;
            void left_revolve(container_node*& parent_temp_Node)
            {
                //传进来的值是发现该树平衡性被破坏的节点地址
                //大致思想：因为这是左单旋，所以找传进来的父亲节点的右根节点来当调整节点
                //然后把调整节点的左根节点赋值给传进来的父亲节点的右根节点 (刚才已经用节点保存过调整节点，所以这里直接赋值)，
                //再把父亲节点赋值给调整节点的左根节点，！！注意：在旋转的过程中还要处理每个调整节点的父亲节点的指向和平衡因子

                // {
                //     container_node* Sub_right_temp = parent_temp_Node->_right;
                //     parent_temp_Node->_right = Sub_right_temp->_left;
                //     Sub_right_temp->_left = parent_temp_Node;
                //     //错误写法：未同步调整父亲节点和判断调整节点的左根节点是否为空，以及全部需要调整节点的父亲指针的指针的指向
                // }
                if(parent_temp_Node == nullptr|| parent_temp_Node->_right == nullptr)
                {
                    std::cout <<"left "<< "空指针"  <<std::endl;
                    return ;
                }
                container_node* Sub_right_temp = parent_temp_Node->_right;
                // container_node* Sub_right_left_temp = Sub_right_temp->_left;
                container_node* Sub_right_left_temp = (Sub_right_temp->_left)? Sub_right_temp->_left : nullptr;
                //防止空指针解引用
                parent_temp_Node->_right = Sub_right_left_temp;
                if(Sub_right_left_temp)
                {
                    Sub_right_left_temp->_parent = parent_temp_Node;
                    //如果Sub_right_left_temp(调整节点的左根节点)不等于空，还需要调整Sub_right_left_temp它的父亲节点
                }
                Sub_right_temp->_left = parent_temp_Node;
                //这里先保存一下parent_temp_Node的父亲地址，防止到下面else比较的时候丢失
                container_node* parent_parent_temp_Node = parent_temp_Node->_parent;
                parent_temp_Node->_parent = Sub_right_temp;
                //更新parent_temp_Node节点指向正确的地址

                if(_root == parent_temp_Node)
                {
                    //如果要调整的节点是根根节点，直接把调整节点赋值给根节点，然后把调整节点的父亲节点置空
                    _root = Sub_right_temp;
                    Sub_right_temp->_parent = nullptr;
                }
                else
                {
                    //调整前parent_temp_Node是这个树的根现在是Sub_right_temp是这个树的根
                    if(parent_parent_temp_Node->_left == parent_temp_Node)
                    {
                        parent_parent_temp_Node->_left = Sub_right_temp;
                    }
                    else
                    {
                        parent_parent_temp_Node->_right = Sub_right_temp;
                    }
                    Sub_right_temp->_parent = parent_parent_temp_Node;
                }
                parent_temp_Node->_balance_factor = Sub_right_temp->_balance_factor = 0;
            }

            void right_revolve(container_node*& parent_temp_Node)
            {
                //思路同左单旋思路差不多
                if(parent_temp_Node == nullptr|| parent_temp_Node->_left == nullptr)
                {
                    std::cout <<"right "<< "空指针"  <<std::endl; 
                    return ;
                }
                container_node* Sub_left_temp = parent_temp_Node->_left;
                container_node* Sub_left_right_temp = (Sub_left_temp->_right) ? Sub_left_temp->_right : nullptr;
                //防止空指针解引用
                parent_temp_Node->_left = Sub_left_right_temp;
                if(Sub_left_right_temp)
                {
                    Sub_left_right_temp->_parent = parent_temp_Node;
                }
                Sub_left_temp->_right = parent_temp_Node;
                //保存parent_temp_Node的父亲节点
                container_node* parent_parent_temp_Node = parent_temp_Node->_parent;
                parent_temp_Node->_parent = Sub_left_temp;

                if(_root == parent_temp_Node)
                {
                    _root = Sub_left_temp;
                    Sub_left_temp->_parent = nullptr;
                }
                else
                {
                    if(parent_parent_temp_Node->_left == parent_temp_Node)
                    {
                        parent_parent_temp_Node->_left = Sub_left_temp;
                    }
                    else
                    {
                        parent_parent_temp_Node->_right = Sub_left_temp;
                    }
                    Sub_left_temp->_parent = parent_parent_temp_Node;
                }
                parent_temp_Node->_balance_factor = Sub_left_temp->_balance_factor = 0;
            }
            void right_left_revolve(container_node*& parent_temp_Node)
            {
                if(parent_temp_Node==nullptr || parent_temp_Node->_right == nullptr)
                {
                    std::cout <<"right_left "<< "空指针"  <<std::endl;
                    return;
                }
                container_node* Sub_right_temp = parent_temp_Node->_right;
                container_node* Sub_right_left_temp = Sub_right_temp->_left;
                int Balance_factor_temp = Sub_right_left_temp->_balance_factor;

                right_revolve(parent_temp_Node->_right);
                //右旋
                left_revolve(parent_temp_Node);
                //左旋
                if(Balance_factor_temp == -1)
                {
                    parent_temp_Node->_balance_factor = 0;
                    Sub_right_temp->_balance_factor = 1;
                    Sub_right_left_temp->_balance_factor = 0;
                }
                else if(Balance_factor_temp == 1)
                {
                    parent_temp_Node->_balance_factor = -1;
                    Sub_right_temp->_balance_factor = 0;
                    Sub_right_left_temp->_balance_factor = 0;
                }
                else
                {
                    parent_temp_Node->_balance_factor = 0;
                    Sub_right_temp->_balance_factor = 0;
                    Sub_right_left_temp->_balance_factor = 0;
                }
            }
            void left_right_revolve(container_node*& parent_temp_Node)
            {   
                if(parent_temp_Node == nullptr || parent_temp_Node->_left == nullptr)
                {
                    std::cout << "left_right " << "空指针" << std::endl;
                    return ;
                }
                container_node* Sub_left_temp = parent_temp_Node->_left;
                container_node* Sub_left_right_temp = Sub_left_temp->_right;
                int Balance_factor_temp = Sub_left_right_temp->_balance_factor;

                left_revolve(parent_temp_Node->_left);
                //左旋
                right_revolve(parent_temp_Node);
                //右旋
                if(Balance_factor_temp == -1)
                {
                    parent_temp_Node->_balance_factor = 0;
                    Sub_left_temp->_balance_factor = 1;
                    Sub_left_right_temp->_balance_factor = 0;
                }
                else if(Balance_factor_temp == 1)
                {
                    parent_temp_Node->_balance_factor = -1;
                    Sub_left_temp->_balance_factor = 0;
                    Sub_left_right_temp->_balance_factor = 0;
                }
                else
                {
                    parent_temp_Node->_balance_factor = 0;
                    Sub_left_temp->_balance_factor = 0;
                    Sub_left_right_temp->_balance_factor = 0;
                }
            }
            void Clear()
            {
                //清空所有资源
                if(_root == nullptr)
                {
                    return;
                }
                else
                {
                    template_container::stack_adapter::stack<container_node*> _stack_temp;
                    //前序释放
                    _stack_temp.push(_root);
                    while(!_stack_temp.empty())
                    {
                        container_node* temp = _stack_temp.top();
                        _stack_temp.pop();
                        if(temp->_left != nullptr)
                        {
                            _stack_temp.push(temp->_left);
                        }
                        if(temp->_right != nullptr)
                        {
                            _stack_temp.push(temp->_right);
                        }
                        delete temp;
                        temp = nullptr;
                    }
                    _root = nullptr;
                }
            }
            //测试函数
            void interior_pre_order_traversal(container_node* _ROOT_Temp )
            {
                //前序遍历，最外左子树全部压栈
                if(_ROOT_Temp == nullptr)
                {
                    return;
                }
                container_node* _Pre_order_traversal_test = _ROOT_Temp;
                template_container::stack_adapter::stack<container_node*> stack_Temp;
                stack_Temp.push(_Pre_order_traversal_test);
                //不能添加|| _Pre_order_traversal_test != nullptr ，因为最后一层循环后_Pre_order_traversal_test还是为真后面循环无意义，反之还会破环性质
                while( !stack_Temp.empty() )
                {
                    _Pre_order_traversal_test = stack_Temp.top();
                    stack_Temp.pop();

                    std::cout << _Pre_order_traversal_test->_data << " ";
                    //修改逻辑错误，先压右子树再压左子树，因为这是栈
                    if(_Pre_order_traversal_test->_right != nullptr)
                    {
                        stack_Temp.push(_Pre_order_traversal_test->_right);
                    }
                    if(_Pre_order_traversal_test->_left != nullptr)
                    {
                        stack_Temp.push(_Pre_order_traversal_test->_left);
                    }
                }
            }
            void interior_middle_order_traversal(container_node* _ROOT_Temp)
            {
                //中序遍历函数
                template_container::stack_adapter::stack<container_node*> _staic_temp_;
                while(_ROOT_Temp != nullptr || !_staic_temp_.empty())
                {
                    while(_ROOT_Temp!= nullptr)
                    {
                        _staic_temp_.push(_ROOT_Temp);
                        //压栈
                        _ROOT_Temp = _ROOT_Temp->_left;
                    }
                    // 访问栈顶节点
                    _ROOT_Temp = _staic_temp_.top();
                    //弹出栈顶元素，刷新栈顶元素，栈顶元素会变成之前压入栈的节点的父节点
                    
                    _staic_temp_.pop();
                    std::cout <<  _ROOT_Temp->_data << " ";
                    // std::cout << &_ROOT_Temp->_data << " ";
                    //检查地址是不是值拷贝
                    // 转向右子树
                    _ROOT_Temp = _ROOT_Temp->_right;
                }
            }
            size_t _size()
            {
                size_t temp = 0; 
                if(_root == nullptr)
                {
                    return temp;
                }
                else
                {
                    container_node* _Pre_order_traversal_test = _root;
                    template_container::stack_adapter::stack<container_node*> stack_Temp;
                    stack_Temp.push(_Pre_order_traversal_test);
                    while( !stack_Temp.empty() )
                    {
                        _Pre_order_traversal_test = stack_Temp.top();
                        stack_Temp.pop();

                        temp++;

                        if(_Pre_order_traversal_test->_right != nullptr)
                        {
                            stack_Temp.push(_Pre_order_traversal_test->_right);
                        }
                        if(_Pre_order_traversal_test->_left != nullptr)
                        {
                            stack_Temp.push(_Pre_order_traversal_test->_left);
                        }
                    }
                }
                return temp;
            }
        public:
            using iterator = avl_tree_iterator<avl_tree_node_pair,avl_tree_node_pair&,avl_tree_node_pair*>;
            using const_iterator = avl_tree_iterator<avl_tree_node_pair,const avl_tree_node_pair&,const avl_tree_node_pair*>;

            using reverse_iterator = avl_tree_reverse_iterator<iterator>;
            using const_reverse_iterator = avl_tree_reverse_iterator<const_iterator>;

            iterator begin()                    
            {
                container_node* _begin_temp = _root;
                while(_begin_temp != nullptr && _begin_temp->_left!= nullptr)
                {
                    _begin_temp = _begin_temp->_left;
                }
                return iterator(_begin_temp);
            }
            iterator end()
            {
                return iterator(nullptr);
            }
            const_iterator cbegin() const
            {
                container_node* _begin_temp = _root;
                while(_begin_temp != nullptr && _begin_temp->_left!= nullptr)
                {
                    _begin_temp = _begin_temp->_left;
                }
                return const_iterator(_begin_temp);
            }
            const_iterator cend() const
            {
                return const_iterator(nullptr);
            }
            reverse_iterator rbegin()
            {
                container_node* _rbegin_temp = _root;
                while(_rbegin_temp!= nullptr && _rbegin_temp->_right!= nullptr)
                {
                    _rbegin_temp = _rbegin_temp->_right;
                }
                return reverse_iterator(iterator(_rbegin_temp));
            }
            reverse_iterator rend()
            {
                return reverse_iterator(iterator(nullptr));
            }
            const_reverse_iterator crbegin() const
            {
                container_node* _rbegin_temp = _root;
                while(_rbegin_temp!= nullptr && _rbegin_temp->_right!= nullptr)
                {
                    _rbegin_temp = _rbegin_temp->_right;
                }
                return const_reverse_iterator(const_iterator(_rbegin_temp));
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
            avl_tree(const avl_tree_type_k& Key_temp,const avl_tree_type_v& val_temp = avl_tree_type_v(),
            container_imitate_function com_temp = container_imitate_function())
            :_root(nullptr),function_policy(com_temp)
            {
                _root = new container_node(Key_temp,val_temp);
            }
            avl_tree(const avl_tree_node_pair& AVL_Tree_Pair_Temp,
            container_imitate_function com_temp = container_imitate_function())
            :_root(nullptr),function_policy(com_temp)
            {
                _root = new container_node(AVL_Tree_Pair_Temp.first,AVL_Tree_Pair_Temp.second);
            }
            avl_tree(const avl_tree& AVL_Tree_temp_)
            : _root(nullptr), function_policy(AVL_Tree_temp_.function_policy)
            {
                if (AVL_Tree_temp_._root == nullptr)
                {
                    return;
                }

                // 使用单栈，存储源节点和目标父节点（均为一级指针）
                template_container::stack_adapter::stack<template_container::practicality::pair<container_node*, container_node*>> stack;
                
                // 创建根节点
                _root = new container_node(AVL_Tree_temp_._root->_data);
                _root->_balance_factor = AVL_Tree_temp_._root->_balance_factor;
                _root->_parent = nullptr; // 根节点的父节点为nullptr
                
                // 初始化栈，将根节点的子节点压入（注意：这里父节点是 _ROOT，一级指针）
                if (AVL_Tree_temp_._root->_right != nullptr)
                {
                    stack.push(template_container::practicality::pair<container_node*, container_node*>(AVL_Tree_temp_._root->_right, _root));
                }
                if (AVL_Tree_temp_._root->_left != nullptr)
                {
                    stack.push(template_container::practicality::pair<container_node*, container_node*>(AVL_Tree_temp_._root->_left, _root));
                }

                // 遍历并复制剩余节点
                while (!stack.empty())
                {
                    auto [source_node, parent_node] = stack.top();
                    stack.pop();
                    
                    // 创建新节点并复制数据
                    container_node* new_node = new container_node(source_node->_data);
                    new_node->_balance_factor = source_node->_balance_factor;
                    
                    // 设置父节点关系（注意：parent_node 是一级指针）
                    new_node->_parent = parent_node;
                    
                    // 判断源节点在原树中是左子还是右子
                    bool is_left_child = false;
                    if (source_node->_parent != nullptr) 
                    {
                        is_left_child = (source_node->_parent->_left == source_node);
                    }
                    
                    // 将新节点链接到父节点的正确位置（注意：直接使用 parent_node）
                    if (is_left_child) 
                    {
                        parent_node->_left = new_node;
                    } 
                    else 
                    {
                        parent_node->_right = new_node;
                    }

                    // 处理子节点（注意：压栈时父节点是 new_node，一级指针）
                    if (source_node->_right != nullptr)
                    {
                        stack.push(template_container::practicality::pair<container_node*, container_node*>(source_node->_right, new_node));
                    }
                    if (source_node->_left != nullptr)
                    {
                        stack.push(template_container::practicality::pair<container_node*, container_node*>(source_node->_left, new_node));
                    }
                }
            }
            avl_tree(avl_tree&& _AVL_Tree_temp_)
            : _root(nullptr),function_policy(_AVL_Tree_temp_.function_policy)
            {
                _root = std::move(_AVL_Tree_temp_._root);
                _AVL_Tree_temp_._root = nullptr;
            }
            avl_tree& operator=(avl_tree&& _AVL_Tree_temp_)
            {
                if(this != &_AVL_Tree_temp_)
                {
                    Clear();
                    _root = std::move(_AVL_Tree_temp_._root);
                    function_policy  = std::move(_AVL_Tree_temp_.function_policy);
                    _AVL_Tree_temp_._root = nullptr;
                }
            }
            avl_tree& operator=(const avl_tree AVL_Tree_temp_)
            {
                Clear();
                if(&AVL_Tree_temp_ == this)
                {
                    return *this;
                }
                if (AVL_Tree_temp_._root == nullptr)
                {
                    return *this;
                }
                template_container::algorithm::swap(function_policy,AVL_Tree_temp_.function_policy);
                template_container::algorithm::swap(_root,AVL_Tree_temp_._root);
                return *this;
            }
            ~avl_tree()
            {
                //析构函数
                Clear();
            }
            size_t size() const
            {
                return _size();
            }
            size_t size()
            {
                return _size();
            }
            void Pre_order_traversal()
            {
                interior_pre_order_traversal(_root);
            }
            void middle_order_traversal()
            {
                interior_middle_order_traversal(_root);
            }
            bool push(const avl_tree_type_k& Key_temp,const avl_tree_type_v& val_temp = avl_tree_type_v())
            {
                //插入
                if(_root == nullptr)
                {
                    _root = new container_node(Key_temp,val_temp);
                    return true;
                }
                else
                {
                    container_node* _ROOT_temp = _root;
                    container_node* _ROOT_temp_parent = nullptr;
                    while(_ROOT_temp)
                    {
                        _ROOT_temp_parent = _ROOT_temp;
                        if(!function_policy(Key_temp,_ROOT_temp->_data.first) && !function_policy(_ROOT_temp->_data.first,Key_temp))
                        {
                            return false;
                        }
                        else if(function_policy(Key_temp,_ROOT_temp->_data.first))
                        {
                            _ROOT_temp = _ROOT_temp->_left;
                        }
                        else
                        {
                            _ROOT_temp = _ROOT_temp->_right;
                        }
                    }
                    _ROOT_temp = new container_node(Key_temp,val_temp);
                    if(function_policy(Key_temp,_ROOT_temp_parent->_data.first))
                    {
                        _ROOT_temp_parent->_left = _ROOT_temp;
                    }
                    else
                    {
                        _ROOT_temp_parent->_right = _ROOT_temp;
                    }
                    _ROOT_temp->_parent = _ROOT_temp_parent;

                    container_node* _ROOT_temp_test = _ROOT_temp;
                    container_node* _ROOT_temp_test_parent = _ROOT_temp_parent;

                    while(_ROOT_temp_test_parent)
                    {
                        if(_ROOT_temp_test_parent->_left == _ROOT_temp_test)
                        {
                            _ROOT_temp_test_parent->_balance_factor--;
                        }
                        else
                        {
                            _ROOT_temp_test_parent->_balance_factor++;
                        }

                        if(_ROOT_temp_test_parent->_balance_factor == 0)
                        {
                            break;
                        }
                        else if (_ROOT_temp_test_parent->_balance_factor == 1 || _ROOT_temp_test_parent->_balance_factor == -1)
                        {
                            _ROOT_temp_test = _ROOT_temp_test_parent;
                            _ROOT_temp_test_parent = _ROOT_temp_test_parent->_parent;
                        }
                        else if (_ROOT_temp_test_parent->_balance_factor == 2 || _ROOT_temp_test_parent->_balance_factor == -2)
                        {
                            if(_ROOT_temp_test_parent->_balance_factor == 2)
                            {
                                if(_ROOT_temp_test->_balance_factor == 1)
                                {
                                    left_revolve(_ROOT_temp_test_parent);
                                }
                                else
                                {
                                    right_left_revolve(_ROOT_temp_test_parent);
                                }
                            }
                            if(_ROOT_temp_test_parent->_balance_factor == -2)
                            {
                                if(_ROOT_temp_test->_balance_factor == -1)
                                {
                                    right_revolve(_ROOT_temp_test_parent);
                                }
                                else
                                {
                                    left_right_revolve(_ROOT_temp_test_parent);
                                }
                            }
                            _ROOT_temp_test = _ROOT_temp_test_parent;
                            _ROOT_temp_test_parent = _ROOT_temp_test_parent->_parent;
                        }
                    }
                }
                return true;
            }
            bool push(const avl_tree_node_pair& AVL_Tree_Pair_Temp)
            {
                //AVL树左子树比右子树高，则他俩的根节点的平衡因子为1，反之为-1，也就是说左加一，右减一，如果根节点为2和-2就要需要调整了
                if(_root == nullptr)
                {
                    _root = new container_node(AVL_Tree_Pair_Temp.first,AVL_Tree_Pair_Temp.second);
                    return true;
                }
                else
                {
                    container_node* _ROOT_Temp = _root;
                    container_node* _ROOT_Temp_parent = nullptr;
                    while(_ROOT_Temp != nullptr)
                    {
                        _ROOT_Temp_parent = _ROOT_Temp;
                        //找到first该在的节点
                        if(!function_policy(AVL_Tree_Pair_Temp.first,_ROOT_Temp->_data.first) && !function_policy(_ROOT_Temp->_data.first,AVL_Tree_Pair_Temp.first))
                        {
                            //不允许重复插入
                            return false;
                        } 
                        else if(function_policy(AVL_Tree_Pair_Temp.first,_ROOT_Temp->_data.first))
                        {
                            _ROOT_Temp = _ROOT_Temp->_left;
                        }
                        else
                        {
                            _ROOT_Temp = _ROOT_Temp->_right;
                        }
                    }
                    _ROOT_Temp = new container_node(AVL_Tree_Pair_Temp);
                    if(function_policy(AVL_Tree_Pair_Temp.first,_ROOT_Temp_parent->_data.first))
                    {
                        _ROOT_Temp_parent->_left = _ROOT_Temp;
                        //三叉链表，注意父亲节点指向
                    }
                    else
                    {
                        _ROOT_Temp_parent->_right = _ROOT_Temp;
                    }
                    _ROOT_Temp->_parent = _ROOT_Temp_parent;
                    container_node* _ROOT_Temp_test = _ROOT_Temp;
                    container_node* _ROOT_Temp_test_parent = _ROOT_Temp_parent;
                    //更新平衡因子
                    while(_ROOT_Temp_test_parent)
                    {
                        //更新到根节点跳出
                        if(_ROOT_Temp_test == _ROOT_Temp_test_parent->_right)
                        {
                            _ROOT_Temp_test_parent->_balance_factor++;
                        }
                        else
                        {
                            _ROOT_Temp_test_parent->_balance_factor--;
                        }

                        if(_ROOT_Temp_test_parent->_balance_factor == 0)
                        {
                            //平衡因子为0，无需平衡
                            break;
                        }
                        else if(_ROOT_Temp_test_parent->_balance_factor == 1 || _ROOT_Temp_test_parent->_balance_factor == -1)
                        {
                            _ROOT_Temp_test = _ROOT_Temp_test_parent;
                            _ROOT_Temp_test_parent = _ROOT_Temp_test_parent->_parent;
                            //向上更新，直到找到0或-2或2
                        }
                        else if(_ROOT_Temp_test_parent->_balance_factor == 2 || _ROOT_Temp_test_parent->_balance_factor == -2)
                        {
                            //平衡因子为2或者-2，需要平衡
                            if(_ROOT_Temp_test_parent->_balance_factor == 2)
                            {
                                if(_ROOT_Temp_test->_balance_factor == 1)
                                {
                                    //L，说明_ROOT_Temp_test是_ROOT_Temp_test_parent的左子节点，线形
                                    left_revolve(_ROOT_Temp_test_parent);
                                }
                                else
                                {
                                    //RL，证明_ROOT_Temp_test是_ROOT_Temp_test_parent的右子节点，在AVL树抽象图上就是折线型的
                                    right_left_revolve(_ROOT_Temp_test_parent);
                                }
                            }
                            else if (_ROOT_Temp_test_parent->_balance_factor == -2)
                            {
                                if(_ROOT_Temp_test->_balance_factor == -1)
                                {
                                    //R，说明_ROOT_Temp_test是_ROOT_Temp_test_parent的右子节点，线形
                                    right_revolve(_ROOT_Temp_test_parent);
                                }
                                else
                                {
                                    //LR，和上同理
                                    left_right_revolve(_ROOT_Temp_test_parent);
                                }
                            }
                            //旋转后继续向上调整，因为旋转后父节点的平衡因子可能发生变化，每个旋转的节点都可以当作一个子树，子树旋转后，父节点平衡因子可能发生变化
                            _ROOT_Temp_test = _ROOT_Temp_test_parent;
                            _ROOT_Temp_test_parent = _ROOT_Temp_test_parent->_parent;
                            //对于双旋的情况，相同方向先调整该节点，再调整整体
                        }
                    }
                }
                return true;
            }
            container_node* find(const avl_tree_type_k& _data_temp)
            {
                container_node* _ROOT_Temp = _root;
                while(_ROOT_Temp != nullptr)
                {
                    if(_ROOT_Temp->_data == _data_temp)
                    {
                        break;
                    }
                    else if (function_policy(_ROOT_Temp->_data,_data_temp))
                    {
                        _ROOT_Temp = _ROOT_Temp->_right;
                    }
                    else
                    {
                        _ROOT_Temp = _ROOT_Temp->_left;
                    }
                }
                return _ROOT_Temp;
            }
            avl_tree& pop(const avl_tree_type_k& _data_Temp)
            {
                if(_root == nullptr)
                {
                    return *this;
                }
                container_node* _ROOT_Temp = _root;
                container_node* _ROOT_Temp_parent = nullptr;
                while(_ROOT_Temp != nullptr)
                {
                    if(!function_policy(_data_Temp,_ROOT_Temp->_data.first) && !function_policy(_ROOT_Temp->_data.first,_data_Temp))
                    {
                        break;
                    }
                    _ROOT_Temp_parent = _ROOT_Temp;
                    if (function_policy(_ROOT_Temp->_data.first,_data_Temp))
                    {
                        _ROOT_Temp = _ROOT_Temp->_right;
                    }
                    else
                    {
                        _ROOT_Temp = _ROOT_Temp->_left;
                    }
                }
                if(_ROOT_Temp == nullptr)
                {
                    return *this;
                    //没有找到
                }
                //三种情况：左空，右空，左右都不空
                if (_ROOT_Temp->_left == nullptr) 
                {
                    if (_ROOT_Temp->_right != nullptr) 
                    {
                        _ROOT_Temp->_right->_parent = _ROOT_Temp_parent;
                    }
                    if (_ROOT_Temp_parent == nullptr) 
                    {
                        _root = _ROOT_Temp->_right;
                    } 
                    else 
                    {
                        if (_ROOT_Temp_parent->_left == _ROOT_Temp) 
                        {
                            _ROOT_Temp_parent->_left = _ROOT_Temp->_right;
                        } 
                        else 
                        {
                            _ROOT_Temp_parent->_right = _ROOT_Temp->_right;
                        }
                    }
                    delete _ROOT_Temp;
                    _ROOT_Temp = nullptr;
                }            
                else if (_ROOT_Temp->_right == nullptr)
                {
                    if(_ROOT_Temp->_left != nullptr)
                    {
                        _ROOT_Temp->_left->_parent = _ROOT_Temp_parent;
                    }
                    if(_ROOT_Temp_parent == nullptr)
                    {
                        _root = _ROOT_Temp->_left;
                    }
                    else
                    {
                        if(_ROOT_Temp_parent->_left == _ROOT_Temp)
                        {
                            _ROOT_Temp_parent->_left = _ROOT_Temp->_left;
                        }
                        else
                        {
                            _ROOT_Temp_parent->_right = _ROOT_Temp->_left; 
                        }
                        if(_ROOT_Temp->_left!= nullptr)
                        {
                            _ROOT_Temp->_left->_parent = _ROOT_Temp_parent;
                        }
                        //更新父节点
                    }
                    delete _ROOT_Temp;
                    _ROOT_Temp = nullptr;
                }
                else if(_ROOT_Temp->_right != nullptr && _ROOT_Temp->_left != nullptr)
                {
                    //找右子树最左节点
                    container_node* _right_min = _ROOT_Temp->_right;
                    container_node* _right_parent = _ROOT_Temp;
                    while(_right_min->_left != nullptr)
                    {
                        _right_parent = _right_min;
                        _right_min = _right_min->_left;
                    }
                    template_container::algorithm::swap(_right_min->_data,_ROOT_Temp->_data);
                    if (_right_parent == _ROOT_Temp) 
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
                container_node* parent_BF = _ROOT_Temp_parent;
                while(parent_BF != nullptr)
                {
                    if(parent_BF->_left == _ROOT_Temp)
                    {
                        parent_BF->_balance_factor--;
                    }
                    else
                    {
                        parent_BF->_balance_factor++;
                    }
                    if(parent_BF->_balance_factor == 0)
                    {
                        break;
                    }
                    else if(parent_BF->_balance_factor == 1 || parent_BF->_balance_factor == -1)
                    {
                        _ROOT_Temp = parent_BF;
                        parent_BF = parent_BF->_parent;
                    }
                    else if(parent_BF->_balance_factor == 2 || parent_BF->_balance_factor == -2)
                    {
                        if(parent_BF->_balance_factor == 2)
                        {
                            if(_ROOT_Temp->_balance_factor == 1)
                            {
                                left_revolve(parent_BF);
                            }
                            else
                            {
                                right_left_revolve(parent_BF);
                            }
                        }
                        else if(parent_BF->_balance_factor == -2)
                        {
                            if(_ROOT_Temp->_balance_factor == -1)
                            {
                                right_revolve(parent_BF);
                            }
                            else
                            {
                                left_right_revolve(parent_BF);
                            }
                        }
                        parent_BF = parent_BF->_parent;
                        _ROOT_Temp = parent_BF;
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
        typename CompareImitationFunctionsRB = template_container::imitation_functions::less<RBTreeTypeKey> >
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
                RBTreeNode(const RBTreeTypeVal& val_temp = RBTreeTypeVal())
                :_data(val_temp),_left(nullptr),_right(nullptr),_parent(nullptr),_color(RED)
                {
                    ;
                }
            };
            template<typename T, typename Ref, typename Ptr>
            class RBTreeiterator
            { 
                using self = RBTreeiterator<T,Ref,Ptr>;
                using Node_iterator = RBTreeNode;
                Node_iterator* _node_iterator_ptr;
            public:
                using reference = Ref;
                using pointer = Ptr;
                RBTreeiterator(Node_iterator* Node_temp_)
                :_node_iterator_ptr(Node_temp_)
                {
                    ;
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
                        container_node* Sub = _node_iterator_ptr->_right;
                        while(Sub->_left != nullptr)
                        {
                            Sub = Sub->_left;
                        }
                        _node_iterator_ptr = Sub;
                    }
                    else
                    {
                        //代表右子树已经走完，需要向上遍历，继续向上找右子树，如果停下来，说明走完整棵树或者是走到根节点
                        Node_iterator* parent_temp = _node_iterator_ptr->_parent;
                        Node_iterator* Sub_temp = _node_iterator_ptr;
                        while(parent_temp != nullptr && Sub_temp == parent_temp->_right)
                        {
                            Sub_temp = parent_temp;
                            parent_temp = parent_temp->_parent;
                        }
                        _node_iterator_ptr = parent_temp;
                        //如果跳出循环，说明走到了根节点，或者找到了右子树
                    }
                    return *this;
                }
                self operator++(int)
                {
                    self Temp = *this;
                    ++(*this);
                    return Temp;
                }
                self& operator--()
                {
                    if(_node_iterator_ptr->_left != nullptr)
                    {
                        Node_iterator* Sub = _node_iterator_ptr->_left;
                        while(Sub->_right != nullptr)
                        {
                            Sub = Sub->_right;
                        }
                        _node_iterator_ptr = Sub;
                    }
                    else
                    {
                        Node_iterator* parent_temp = _node_iterator_ptr->_parent;
                        Node_iterator* Sub_temp = _node_iterator_ptr;
                        while(parent_temp != nullptr && Sub_temp == parent_temp->_left)
                        {
                            Sub_temp = parent_temp;
                            parent_temp = parent_temp->_parent;
                        }
                        _node_iterator_ptr = parent_temp;
                    }
                    return *this;
                }
                self operator--(int)
                {
                    self Temp = *this;
                    --(*this);
                    return Temp;
                }
                bool operator==(const self& it_temp) const
                {
                    return _node_iterator_ptr == it_temp._node_iterator_ptr;
                }
                bool operator!=(const self& it_temp) const
                {
                    return _node_iterator_ptr != it_temp._node_iterator_ptr;
                }
            };
            template <typename iterator>
            class RBTreeReverseIterator
            {
                using self = RBTreeReverseIterator<iterator>;
                using Ref  = typename iterator::reference;
                using Ptr  = typename iterator::pointer;
                iterator _it;
            public:
                RBTreeReverseIterator(iterator it_temp)
                :_it(it_temp)
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
            container_node* _root;
            DataExtractionFunction Element;
            CompareImitationFunctionsRB function_policy;
            void left_revolve(container_node* parent_temp_Node)
            {
                //传进来的值是发现该树平衡性被破坏的节点地址
                //大致思想：因为这是左单旋，所以找传进来的父亲节点的右根节点来当调整节点
                //然后把调整节点的左根节点赋值给传进来的父亲节点的右根节点 (刚才已经用节点保存过调整节点，所以这里直接赋值)，
                //再把父亲节点赋值给调整节点的左根节点，！！注意：在旋转的过程中还要处理每个调整节点的父亲节点的指向和平衡因子

                // {
                //     container_node* Sub_right_temp = parent_temp_Node->_right;
                //     parent_temp_Node->_right = Sub_right_temp->_left;
                //     Sub_right_temp->_left = parent_temp_Node;
                //     //错误写法：未同步调整父亲节点和判断调整节点的左根节点是否为空，以及全部需要调整节点的父亲指针的指针的指向
                // }
                if(parent_temp_Node == nullptr|| parent_temp_Node->_right == nullptr)
                {
                    std::cout <<"left "<< "空指针"  <<std::endl;
                    return ;
                }
                container_node* Sub_right_temp = parent_temp_Node->_right;
                // container_node* Sub_right_left_temp = Sub_right_temp->_left;
                container_node* Sub_right_left_temp = (Sub_right_temp->_left)? Sub_right_temp->_left : nullptr;
                //防止空指针解引用
                parent_temp_Node->_right = Sub_right_left_temp;
                if(Sub_right_left_temp)
                {
                    Sub_right_left_temp->_parent = parent_temp_Node;
                    //如果Sub_right_left_temp(调整节点的左根节点)不等于空，还需要调整Sub_right_left_temp它的父亲节点
                }
                Sub_right_temp->_left = parent_temp_Node;
                //这里先保存一下parent_temp_Node的父亲地址，防止到下面else比较的时候丢失
                container_node* parent_parent_temp_Node = parent_temp_Node->_parent;
                parent_temp_Node->_parent = Sub_right_temp;
                //更新parent_temp_Node节点指向正确的地址

                if(_root == parent_temp_Node)
                {
                    //如果要调整的节点是根根节点，直接把调整节点赋值给根节点，然后把调整节点的父亲节点置空
                    _root = Sub_right_temp;
                    Sub_right_temp->_parent = nullptr;
                }
                else
                {
                    //调整前parent_temp_Node是这个树的根现在是Sub_right_temp是这个树的根
                    if(parent_parent_temp_Node->_left == parent_temp_Node)
                    {
                        parent_parent_temp_Node->_left = Sub_right_temp;
                    }
                    else
                    {
                        parent_parent_temp_Node->_right = Sub_right_temp;
                    }
                    Sub_right_temp->_parent = parent_parent_temp_Node;
                }
            }
            void right_revolve(container_node*& parent_temp_Node)
            {
                //思路同左单旋思路差不多,但是相反
                if(parent_temp_Node == nullptr|| parent_temp_Node->_left == nullptr)
                {
                    std::cout <<"right "<< "空指针"  <<std::endl; 
                    return ;
                }
                container_node* Sub_left_temp = parent_temp_Node->_left;
                container_node* Sub_left_right_temp = (Sub_left_temp->_right) ? Sub_left_temp->_right : nullptr;
                //防止空指针解引用
                parent_temp_Node->_left = Sub_left_right_temp;
                if(Sub_left_right_temp)
                {
                    Sub_left_right_temp->_parent = parent_temp_Node;
                }
                Sub_left_temp->_right = parent_temp_Node;
                //保存parent_temp_Node的父亲节点
                container_node* parent_parent_temp_Node = parent_temp_Node->_parent;
                parent_temp_Node->_parent = Sub_left_temp;

                if(_root == parent_temp_Node)
                {
                    _root = Sub_left_temp;
                    Sub_left_temp->_parent = nullptr;
                }
                else
                {
                    if(parent_parent_temp_Node->_left == parent_temp_Node)
                    {
                        parent_parent_temp_Node->_left = Sub_left_temp;
                    }
                    else
                    {
                        parent_parent_temp_Node->_right = Sub_left_temp;
                    }
                    Sub_left_temp->_parent = parent_parent_temp_Node;
                }
            }
            void Clear(container_node* _clear_Temp)
            {
                if(_clear_Temp == nullptr)
                {
                    return ;
                }
                else
                {
                    template_container::stack_adapter::stack<container_node*> _stack;
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
                    _root = nullptr;
                }
            }
            void interior_middle_order_traversal(container_node* _ROOT_Temp)
            {
                //中序遍历函数
                template_container::stack_adapter::stack<container_node*> _staic_temp_;
                while(_ROOT_Temp != nullptr || !_staic_temp_.empty())
                {
                    while(_ROOT_Temp!= nullptr)
                    {
                        _staic_temp_.push(_ROOT_Temp);
                        _ROOT_Temp = _ROOT_Temp->_left;
                    }
                    _ROOT_Temp = _staic_temp_.top();
                    _staic_temp_.pop();
                    std::cout <<  _ROOT_Temp->_data << " ";
                    // std::cout << _ROOT_Temp->_color <<" ";
                    _ROOT_Temp = _ROOT_Temp->_right;
                }
            }
            void interior_pre_order_traversal(container_node* _ROOT_Temp )
            {
                //前序遍历，最外左子树全部压栈
                if(_ROOT_Temp == nullptr)
                {
                    return;
                }
                container_node* _Pre_order_traversal_test = _ROOT_Temp;
                template_container::stack_adapter::stack<container_node*> stack_Temp;
                stack_Temp.push(_Pre_order_traversal_test);
                while( !stack_Temp.empty() )
                {
                    _Pre_order_traversal_test = stack_Temp.top();
                    stack_Temp.pop();

                    std::cout << _Pre_order_traversal_test->_data << " ";
                    // std::cout << _Pre_order_traversal_test->_color <<" ";
                    //修改逻辑错误，先压右子树再压左子树，因为这是栈
                    if(_Pre_order_traversal_test->_right != nullptr)
                    {
                        stack_Temp.push(_Pre_order_traversal_test->_right);
                    }
                    if(_Pre_order_traversal_test->_left != nullptr)
                    {
                        stack_Temp.push(_Pre_order_traversal_test->_left);
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
                container_node* _ROOT_Temp = _root;
                if(_ROOT_Temp == nullptr)
                {
                    return size;
                }
                container_node* _Pre_order_traversal_test = _ROOT_Temp;
                template_container::stack_adapter::stack<container_node*> stack_Temp;
                stack_Temp.push(_Pre_order_traversal_test);
                while( !stack_Temp.empty() )
                {
                    _Pre_order_traversal_test = stack_Temp.top();
                    stack_Temp.pop();

                    size++;
                    if(_Pre_order_traversal_test->_right != nullptr)
                    {
                        stack_Temp.push(_Pre_order_traversal_test->_right);
                    }
                    if(_Pre_order_traversal_test->_left != nullptr)
                    {
                        stack_Temp.push(_Pre_order_traversal_test->_left);
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
                _root = nullptr;
            }
            RBTree(const RBTreeTypeVal& RB_Tree_Temp)
            {
                _root = new container_node(RB_Tree_Temp);
                _root->_color = BLACK;
            }
            RBTree(RBTree&& RB_Tree_Temp)
            :function_policy(RB_Tree_Temp.function_policy),Element(RB_Tree_Temp.Element)
            {
                _root = std::move(RB_Tree_Temp._root);
                RB_Tree_Temp._root = nullptr;
            }
            RBTree(const RBTree& RB_Tree_Temp)
            :function_policy(RB_Tree_Temp.function_policy),Element(RB_Tree_Temp.Element)
            {
                if(_root != nullptr)
                {
                    Clear(_root);
                }
                else
                {
                    _root = nullptr;
                    if(RB_Tree_Temp._root == nullptr)
                    {
                        _root = nullptr;
                    }
                    else
                    {
                        // 使用单栈，存储源节点和目标父节点（均为一级指针）
                        template_container::stack_adapter::stack<template_container::practicality::pair<container_node*, container_node*>> stack;
                        
                        // 创建根节点
                        _root = new container_node(RB_Tree_Temp._root->_data);
                        _root->_color = RB_Tree_Temp._root->_color;
                        _root->_parent = nullptr; // 根节点的父节点为nullptr
                        
                        // 初始化栈，将根节点的子节点压入（注意：这里父节点是 _ROOT，一级指针）
                        if (RB_Tree_Temp._root->_right != nullptr)
                        {
                            stack.push(template_container::practicality::pair<container_node*, container_node*>(RB_Tree_Temp._root->_right, _root));
                        }
                        if (RB_Tree_Temp._root->_left != nullptr)
                        {
                            stack.push(template_container::practicality::pair<container_node*, container_node*>(RB_Tree_Temp._root->_left, _root));
                        }

                        // 遍历并复制剩余节点
                        while (!stack.empty())
                        {
                            auto [source_node, parent_node] = stack.top();
                            stack.pop();
                            
                            // 创建新节点并复制数据
                            container_node* new_node = new container_node(source_node->_data);
                            new_node->_color = source_node-> _color;
                            
                            // 设置父节点关系（注意：parent_node 是一级指针）
                            new_node->_parent = parent_node;
                            
                            // 判断源节点在原树中是左子还是右子
                            bool is_left_child = false;
                            if (source_node->_parent != nullptr) 
                            {
                                is_left_child = (source_node->_parent->_left == source_node);
                            }
                            
                            // 将新节点链接到父节点的正确位置（注意：直接使用 parent_node）
                            if (is_left_child) 
                            {
                                parent_node->_left = new_node;
                            } 
                            else 
                            {
                                parent_node->_right = new_node;
                            }

                            // 处理子节点（注意：压栈时父节点是 new_node，一级指针）
                            if (source_node->_right != nullptr)
                            {
                                stack.push(template_container::practicality::pair<container_node*, container_node*>(source_node->_right, new_node));
                            }
                            if (source_node->_left != nullptr)
                            {
                                stack.push(template_container::practicality::pair<container_node*, container_node*>(source_node->_left, new_node));
                            }
                        }
                    }
                }
            }
            RBTree& operator=(const RBTree RB_Tree_Temp)
            {
                if(this == &RB_Tree_Temp)
                {
                    return *this;
                }
                else
                {
                    Clear(_root);
                    template_container::algorithm::swap(RB_Tree_Temp._root,_root);
                    template_container::algorithm::swap(RB_Tree_Temp.Element,Element);
                    template_container::algorithm::swap(RB_Tree_Temp.function_policy,function_policy);
                    return *this;
                }
            }
            RBTree& operator=(RBTree&& RB_Tree_Temp)
            {
                if(this != &RB_Tree_Temp)
                {
                    Clear();
                    function_policy = std::move(RB_Tree_Temp.function_policy);
                    Element = std::move(RB_Tree_Temp.Element);
                    _root = std::move(RB_Tree_Temp._root);
                    RB_Tree_Temp._root = nullptr;
                }
                return *this;
            }
            ~RBTree()
            {
                Clear(_root);
            }
            insert_result push(const RBTreeTypeVal& Val_Temp_)
            {
                if(_root == nullptr)
                {
                    _root = new container_node(Val_Temp_);
                    _root->_color = BLACK;
                    return insert_result(iterator(_root),true);
                }
                else
                {
                    container_node* _ROOT_Temp = _root;
                    container_node* _ROOT_Temp_parent = nullptr;
                    while(_ROOT_Temp != nullptr)
                    {
                        _ROOT_Temp_parent = _ROOT_Temp;
                        if(!function_policy(Element(_ROOT_Temp->_data),Element(Val_Temp_)) && !function_policy(Element(Val_Temp_),Element(_ROOT_Temp->_data)))
                        {
                            //插入失败，找到相同的值，开始返回
                            return insert_result(iterator(_ROOT_Temp),false);
                        }
                        else if(function_policy(Element(_ROOT_Temp->_data),Element(Val_Temp_)))
                        {
                            _ROOT_Temp = _ROOT_Temp->_right;
                        }
                        else
                        {
                            _ROOT_Temp = _ROOT_Temp->_left;
                        }
                    }
                    //找到插入位置
                    _ROOT_Temp = new container_node(Val_Temp_);
                    if(function_policy(Element(_ROOT_Temp_parent->_data),Element(_ROOT_Temp->_data)))
                    {
                        _ROOT_Temp_parent->_right = _ROOT_Temp;
                    }
                    else
                    {
                        _ROOT_Temp_parent->_left = _ROOT_Temp;
                    }
                    _ROOT_Temp->_color = RED;
                    _ROOT_Temp->_parent = _ROOT_Temp_parent;
                    container_node* Return_Node_Push = _ROOT_Temp;
                    //保存节点
                    //开始调整，向上调整颜色节点
                    while(_ROOT_Temp_parent != nullptr && _ROOT_Temp_parent->_color == RED )
                    {
                        container_node* _ROOT_Temp_Grandfther = _ROOT_Temp_parent->_parent;
                        if(_ROOT_Temp_Grandfther->_left == _ROOT_Temp_parent)
                        {
                            //叔叔节点
                            // std::cout << "push" <<" ";
                            container_node* uncle = _ROOT_Temp_Grandfther->_right;
                            //情况1：uncle存在，且为红
                            //情况2: uncle不存在，那么_ROOT_Temp就是新增节点
                            //情况3：uncle存在且为黑，说明_ROOT_Temp不是新增节点
                            if(uncle && uncle->_color == RED)
                            {
                                //情况1：
                                _ROOT_Temp_parent->_color = uncle->_color = BLACK;
                                _ROOT_Temp_Grandfther->_color = RED;
                                //颜色反转完成
                                _ROOT_Temp = _ROOT_Temp_Grandfther;
                                _ROOT_Temp_parent = _ROOT_Temp->_parent;
                                //向上调整,继续从红色节点开始
                            }
                            else
                            {
                                //情况3：该情况双旋转单旋
                                if(_ROOT_Temp == _ROOT_Temp_parent->_right)
                                {
                                    left_revolve(_ROOT_Temp_parent);
                                    template_container::algorithm::swap(_ROOT_Temp,_ROOT_Temp_parent);
                                    // _ROOT_Temp = _ROOT_Temp_parent;
                                    //折线调整，交换位置调整为情况2
                                }
                                //情况2：直接单旋
                                right_revolve(_ROOT_Temp_Grandfther);
                                _ROOT_Temp_Grandfther->_color = RED;
                                _ROOT_Temp_parent->_color = BLACK;
                            }
                        }
                        else
                        {
                            container_node* uncle = _ROOT_Temp_Grandfther->_left;
                            //与上面相反
                            if(uncle && uncle->_color == RED)
                            {
                                //情况1：
                                _ROOT_Temp_parent->_color = uncle->_color = BLACK;
                                _ROOT_Temp_Grandfther->_color = RED;
                                //颜色反转完成
                                _ROOT_Temp = _ROOT_Temp_Grandfther;
                                _ROOT_Temp_parent = _ROOT_Temp->_parent;
                            }
                            else
                            {
                                //情况3：该情况双旋转单旋
                                if(_ROOT_Temp == _ROOT_Temp_parent->_left)
                                {
                                    right_revolve(_ROOT_Temp_parent);
                                    template_container::algorithm::swap(_ROOT_Temp,_ROOT_Temp_parent);
                                    // _ROOT_Temp = _ROOT_Temp_parent;
                                    //交换指针转换为单旋
                                }
                                //情况2：单旋
                                left_revolve(_ROOT_Temp_Grandfther);
                                _ROOT_Temp_Grandfther->_color = RED;
                                _ROOT_Temp_parent->_color = BLACK;
                            }
                        }
                    }
                    _root->_color = BLACK;
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
                while(cur != _root && (cur == nullptr || BLACK_Get(cur)))
                {
                    if(cur == _root)
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
                            left_revolve(parent);
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
                            right_revolve(brother);
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
                            left_revolve(parent);
                            cur = _root;
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
                            right_revolve(parent);
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
                            left_revolve(brother);
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
                            right_revolve(parent);
                            cur = _root;
                            parent = cur->_parent;
                        }
                    }
                }
                if(cur != nullptr)
                {
                    cur->_color = BLACK;
                }
            }
            insert_result pop(const RBTreeTypeVal& RB_Tree_Temp)
            {
                RBTreeColor Delete_color;
                if(_root == nullptr)
                {
                    return insert_result(iterator(nullptr),false);
                }
                else
                {
                    container_node* _ROOT_Temp = _root;
                    container_node* _ROOT_Temp_parent = nullptr;
                    container_node* _Adjust_Node = nullptr;
                    container_node* _Adjust_Node_parent = nullptr;
                    while(_ROOT_Temp != nullptr)
                    {
                        if(!function_policy(Element(_ROOT_Temp->_data),Element(RB_Tree_Temp)) && !function_policy(Element(RB_Tree_Temp),Element(_ROOT_Temp->_data)))
                        {
                            break;
                        }
                        //防止父亲自赋值
                        _ROOT_Temp_parent = _ROOT_Temp;
                        if(function_policy(Element(_ROOT_Temp->_data),Element(RB_Tree_Temp)))
                        {
                            _ROOT_Temp = _ROOT_Temp->_right;
                        }
                        else
                        {
                            _ROOT_Temp = _ROOT_Temp->_left;
                        }
                    }
                    if(_ROOT_Temp == nullptr )
                    {
                        return insert_result(iterator(nullptr),false);
                    }
                    //找到位置开始删除
                    Delete_color = _ROOT_Temp->_color;
                    if(_ROOT_Temp->_left == nullptr)
                    {
                        if(_ROOT_Temp->_right != nullptr)
                        {
                            //右节点有值
                            _ROOT_Temp->_right->_parent = _ROOT_Temp_parent;
                        }
                        if(_ROOT_Temp_parent == nullptr)
                        {
                            //根节点
                            _root = _ROOT_Temp->_right;
                        }
                        else
                        {
                            //不为空，代表要删除的数不是在根节点上
                            if(_ROOT_Temp_parent->_left == _ROOT_Temp)
                            {
                                _ROOT_Temp_parent->_left = _ROOT_Temp->_right;
                            }
                            else
                            {
                                _ROOT_Temp_parent->_right = _ROOT_Temp->_right;
                            }
                        }
                        _Adjust_Node = _ROOT_Temp->_right;
                        _Adjust_Node_parent = _ROOT_Temp_parent;
                        delete _ROOT_Temp;
                        _ROOT_Temp = nullptr;
                    }
                    else if (_ROOT_Temp->_right == nullptr)
                    {
                        if(_ROOT_Temp->_left != nullptr)
                        {
                            _ROOT_Temp->_left->_parent = _ROOT_Temp_parent;
                            //链接父节点
                        }
                        if(_ROOT_Temp_parent == nullptr)
                        {
                            //与上同理
                            _root = _ROOT_Temp->_left;
                        }
                        else
                        {
                            if(_ROOT_Temp_parent->_left == _ROOT_Temp)
                            {
                                _ROOT_Temp_parent->_left = _ROOT_Temp->_left;
                            }
                            else
                            {
                                _ROOT_Temp_parent->_right = _ROOT_Temp->_left;
                            }
                        }
                        _Adjust_Node = _ROOT_Temp->_left;
                        _Adjust_Node_parent = _ROOT_Temp_parent;
                        delete _ROOT_Temp;
                        _ROOT_Temp = nullptr;
                    }
                    else if(_ROOT_Temp->_right != nullptr && _ROOT_Temp->_left != nullptr)
                    {
                        container_node* _right_min = _ROOT_Temp->_right;
                        container_node* _right_parent = _ROOT_Temp;
                        while(_right_min->_left != nullptr)
                        {
                            _right_parent = _right_min;
                            _right_min = _right_min->_left;
                        }
                        Delete_color = _right_min->_color;

                        // 交换数据 AND 交换颜色
                        template_container::algorithm::swap(_right_min->_data,  _ROOT_Temp->_data);
                        template_container::algorithm::swap(_right_min->_color, _ROOT_Temp->_color);

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
                        _Adjust_Node        = _right_min->_right;
                        _Adjust_Node_parent = _right_parent;

                        // 最后再 delete 那个后继节点
                        delete _right_min;
                        _right_min = nullptr;
                    }
                    //更新颜色
                    if( Delete_color == BLACK )
                    {
                        //删除红色节点不影响性质
                        DeleteAdjust(_Adjust_Node,_Adjust_Node_parent);
                    }
                    if(_root != nullptr)
                    {
                        _root->_color = BLACK;
                    }
                    return insert_result(iterator(nullptr),false);
                }
            }
            iterator find(const RBTreeTypeVal& RB_Tree_Temp_)
            {
                if(_root == nullptr)
                {
                    return iterator(nullptr);
                }
                else
                {
                    container_node* _iterator_ROOT = _root;
                    while(_iterator_ROOT != nullptr)
                    {
                       if(!function_policy(Element(_iterator_ROOT->_data),Element(RB_Tree_Temp_)))
                       {
                           return iterator(_iterator_ROOT);
                       }
                       else if(function_policy(Element(_iterator_ROOT->_data),Element(RB_Tree_Temp_)))
                       {
                           _iterator_ROOT = _iterator_ROOT->_right;
                       }
                       else
                       {
                           _iterator_ROOT = _iterator_ROOT->_left;
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
            void Pre_order_traversal()
            {
                interior_pre_order_traversal(_root);
            }
            iterator begin()
            {
                container_node* _iterator_ROOT = _root;
                while(_iterator_ROOT != nullptr &&  _iterator_ROOT->_left != nullptr)
                {
                    _iterator_ROOT = _iterator_ROOT->_left;
                }
                return iterator(_iterator_ROOT);
            }
            iterator end()
            {
                return iterator(nullptr);
            }
            const_iterator cbegin() const
            {
                container_node* _iterator_ROOT = _root;
                while(_iterator_ROOT != nullptr &&  _iterator_ROOT->_left != nullptr)
                {
                    _iterator_ROOT = _iterator_ROOT->_left;
                }
                return const_iterator(_iterator_ROOT);
            }
            const_iterator cend() const
            {
                return const_iterator(nullptr);
            }
            reverse_iterator rbegin()
            {
                container_node* _iterator_Node = _root;
                while(_iterator_Node != nullptr && _iterator_Node->_right != nullptr)
                {
                    _iterator_Node = _iterator_Node->_right;
                }
                return reverse_iterator(_iterator_Node);
            }
            reverse_iterator rend()
            {
                return reverse_iterator(nullptr);
            }
            const_reverse_iterator crbegin() const
            {
                container_node* _iterator_Node = _root;
                while(_iterator_Node!= nullptr && _iterator_Node->_right!= nullptr)
                {
                    _iterator_Node = _iterator_Node->_right;
                }
                return const_reverse_iterator(_iterator_Node);
            }
            const_reverse_iterator crend() const
            {
                return const_reverse_iterator(nullptr);
            }
            iterator operator[](const RBTreeTypeVal& RB_Tree_Temp)
            {
                return find(RB_Tree_Temp);
            }
        };
        /*############################     hash 容器     ############################*/
        template <typename HashTableTypeKey, typename HashTableTypeVal,typename HashTableFunctor,typename DataExtractionFunction = std::hash<HashTableTypeVal> >
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
                HashTableNode(const HashTableTypeVal& Temp_Val)
                {
                    _data = Temp_Val;
                    _next = nullptr;
                    LinkPrev = nullptr;
                    LinkNext = nullptr;
                }
            };
            using container_node = HashTableNode;
            HashTableFunctor HashDataFunctor;                           //仿函数
            size_t _size;                                               //哈希表大小
            size_t LoadFactor;                                         //负载因子   
            size_t Capacity;                                            //哈希表容量
            template_container::vector_container::vector<container_node*> _HashTable;   //哈希表
            DataExtractionFunction DataExtractionFunction;           //哈希函数
            container_node* PreviousData = nullptr;                             //上一个数据
            container_node* HeadData = nullptr;                                 //插入头数据
            template <typename Hash_Table_iterator_Key, typename Hash_Table_iterator_Val>
            class Hash_iterator
            {
                using iterator_node = container_node;
                using Ref  = Hash_Table_iterator_Val&;
                using Ptr  = Hash_Table_iterator_Val*;
                using self = Hash_iterator<Hash_Table_iterator_Key,Hash_Table_iterator_Val>;
                iterator_node* HashTableIteratorNode;
            public:
                Hash_iterator(iterator_node* Temp_Node)      {      HashTableIteratorNode = Temp_Node;        }
                Ref operator*()                              {      return HashTableIteratorNode->_data;      }
                Ptr operator->()                             {      return &HashTableIteratorNode->_data;     }
                self operator++()                            {       HashTableIteratorNode = HashTableIteratorNode->LinkNext;     return *this;     }
                bool operator!=(const self& Temp_Self)       {   return HashTableIteratorNode != Temp_Self.HashTableIteratorNode;     }
                bool operator==(const self& Temp_Self)       {   return HashTableIteratorNode == Temp_Self.HashTableIteratorNode;     }
                self operator++(int)                         
                {       
                    self Temp_Self = *this;
                    HashTableIteratorNode = HashTableIteratorNode->LinkNext;
                    return Temp_Self;
                }
            };
            void parentJudgment(container_node*& _Temp_Node_parent,container_node*& _Temp_Node,size_t& Hash_Location_data)
            {
                if(_Temp_Node_parent!= nullptr)
                {
                    //父亲节点不为空，防止空指针错误
                    _Temp_Node_parent->_next = _Temp_Node->_next;
                }
                else
                {
                    //父亲节点为空，直接将映射位置置空
                    _HashTable[Hash_Location_data] = nullptr;
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
            HashTable(size_t Temp_capacity)
            {
                _size = 0;
                LoadFactor = 7;
                Capacity = Temp_capacity;
                _HashTable.resize(Capacity);
            }
            HashTable(const HashTable& Temp_Hash_Table)
            : HashDataFunctor(Temp_Hash_Table.HashDataFunctor),_size(Temp_Hash_Table._size),LoadFactor(Temp_Hash_Table.LoadFactor),Capacity(Temp_Hash_Table.Capacity),
            DataExtractionFunction(Temp_Hash_Table.DataExtractionFunction),PreviousData(nullptr),   HeadData(nullptr)
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
                    container_node* src_bucket_node = Temp_Hash_Table._HashTable[i];
                    // 桶内新表的尾节点（用于串联 _next）
                    container_node* last_in_bucket = nullptr;
        
                    // 逐节点深拷贝
                    while (src_bucket_node) 
                    {
                        // 2.1 创建新节点并拷贝数据
                        container_node* new_node = new container_node(src_bucket_node->_data);
                        // 2.2 插入到“桶内部”链表
                        if (last_in_bucket != nullptr) 
                        {
                            last_in_bucket->_next = new_node;
                        } 
                        else 
                        {
                            _HashTable[i] = new_node;
                        }
                        last_in_bucket = new_node;
        
                        // 2.3 插入到“全局插入
                        if(PreviousData != nullptr)
                        {
                            PreviousData->LinkNext = new_node;
                            new_node->LinkPrev = PreviousData;
                        } 
                        else 
                        {
                            // 第一个节点就是全局链表的头
                            HeadData = new_node;
                        }
                        PreviousData = new_node;
        
                        // 继续下一个源节点
                        src_bucket_node = src_bucket_node->_next;
                    }
                }
                if(PreviousData != nullptr)
                {
                    PreviousData->LinkNext = nullptr;
                }
            }
            HashTable(HashTable&& Temp_Hash_Table)
            {
                _HashTable = std::move(Temp_Hash_Table._HashTable);
                _size = std::move(Temp_Hash_Table._size);
                LoadFactor = std::move(Temp_Hash_Table.LoadFactor);
                Capacity = std::move(Temp_Hash_Table.Capacity);
                DataExtractionFunction = std::move(Temp_Hash_Table.DataExtractionFunction);
                PreviousData = std::move(Temp_Hash_Table.PreviousData);
                HeadData = std::move(Temp_Hash_Table.HeadData);
                HashDataFunctor = std::move(Temp_Hash_Table.HashDataFunctor);
            }
            ~HashTable()
            {
                for(size_t i = 0;i < _HashTable.size();++i)
                {
                    container_node* _Temp_Node = _HashTable[i];
                    while(_Temp_Node != nullptr)
                    {
                        container_node* _Temp_Node_prev = _Temp_Node;
                        _Temp_Node = _Temp_Node->_next;
                        delete _Temp_Node_prev;
                        _Temp_Node_prev = nullptr;
                    }
                }
            }
            bool ChangeLoadFactor(const size_t& Temp_Load_factor)
            {
                if(Temp_Load_factor < 1)
                {
                    return false;
                }
                LoadFactor = Temp_Load_factor;
                return true;
            }
            iterator operator[](const HashTableTypeKey& Temp_Key)
            {
                if( _size == 0)
                {
                    return iterator(nullptr);
                }
                else
                {
                    size_t Temp_Hash = DataExtractionFunction(Temp_Key);
                    size_t Hash_Location_data = Temp_Hash % Capacity;
                    //找到映射位置
                    container_node* _Temp_Node = _HashTable[Hash_Location_data];
                    while(_Temp_Node!= nullptr)
                    {
                        if(HashDataFunctor(_Temp_Node->_data) == HashDataFunctor(Temp_Key))
                        {
                            return iterator(_Temp_Node);
                        }
                        _Temp_Node = _Temp_Node->_next;
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

            bool push (const HashTableTypeVal& Temp_Val)
            {
                if( find(Temp_Val) != nullptr)
                {
                    return false;
                }
                //判断扩容
                if( _size * 10 >= Capacity * LoadFactor)
                {
                    //扩容
                    size_t NewCapacity = (Capacity == 0 && _HashTable.size() == 0) ? 10 : Capacity * 2;
                    //新容量
                    template_container::vector_container::vector<container_node*> _New_Hash_Table;
                    _New_Hash_Table.resize(NewCapacity,nullptr);
                    size_t _New_size = 0;
                    //重新映射,按照插入链表顺序
                    container_node* _Temp_Head_Node = nullptr;
                    container_node* _Temp_previous_data = nullptr;
                    container_node* _Temp_Node = HeadData;
                    while( _Temp_Node != nullptr)
                    {
                        size_t Temp_Hash = DataExtractionFunction(_Temp_Node->_data) % NewCapacity;
                        //重新计算映射值
                        container_node* New_Mapping_location = _New_Hash_Table[Temp_Hash];
                        if(New_Mapping_location == nullptr)
                        {
                            container_node* _push_Node = new container_node(_Temp_Node->_data);
                            if(_Temp_Head_Node == nullptr)
                            {
                                _push_Node->LinkPrev = nullptr;
                                _push_Node->LinkNext = nullptr;
                                _Temp_Head_Node = _Temp_previous_data =_push_Node;
                            }
                            else
                            {
                                _push_Node->LinkPrev = _Temp_previous_data;
                                _Temp_previous_data->LinkNext = _push_Node;
                                _Temp_previous_data = _push_Node;
                            }
                            _New_Hash_Table[Temp_Hash] = _push_Node;
                            //保存之前的遍历链表信息
                        }
                        else
                        {
                            container_node* _push_Node = new container_node(_Temp_Node->_data);
                            if(_Temp_Head_Node == nullptr)
                            {
                                _push_Node->LinkPrev = nullptr;
                                _Temp_Head_Node = _Temp_previous_data =_push_Node;
                            }
                            else
                            {
                                _push_Node->LinkPrev = _Temp_previous_data;
                                _Temp_previous_data->LinkNext = _push_Node;
                                _Temp_previous_data = _push_Node;
                            }
                            _push_Node->_next = New_Mapping_location;
                            _New_Hash_Table[Temp_Hash] = _push_Node;
                            //头插节点
                        }
                        ++_New_size;
                        _Temp_Node = _Temp_Node->LinkNext;
                    }
                    //释放旧哈希表
                    for(size_t i = 0;i < _HashTable.size(); ++i)
                    {
                        container_node* _Temp_Node = _HashTable[i];
                        while(_Temp_Node!= nullptr)
                        {
                            container_node* _Temp_Node_prev = _Temp_Node;
                            _Temp_Node = _Temp_Node->_next;
                            delete _Temp_Node_prev;
                            _Temp_Node_prev = nullptr;
                        }
                    }
                    _size = _New_size;
                    _HashTable.swap(_New_Hash_Table);
                    Capacity = NewCapacity;
                    HeadData = _Temp_Head_Node;
                    PreviousData = _Temp_previous_data;
                    //重新映射,按照插入链表顺序
                }
                size_t Temp_Hash = DataExtractionFunction(Temp_Val);
                size_t Hash_Location_data = Temp_Hash % Capacity;
                //找到映射位置
                container_node* _Temp_Node = _HashTable[Hash_Location_data];

                container_node* _push_Node = new container_node(Temp_Val);
                _push_Node->_next = _Temp_Node;
                _HashTable[Hash_Location_data] = _push_Node;
                if(_size == 0 && HeadData == nullptr)
                {
                    _push_Node->LinkPrev = nullptr;
                    HeadData = PreviousData = _push_Node;
                }
                else
                {
                    _push_Node->LinkPrev = PreviousData;
                    PreviousData->LinkNext = _push_Node;
                    PreviousData = _push_Node;
                }
                _size++;
                return true;
            }
            bool pop(const HashTableTypeVal& Temp_Val)
            {
                //空表判断
                if( find(Temp_Val) == nullptr)
                {
                    return false;
                }
                size_t Temp_Hash = DataExtractionFunction(Temp_Val);
                size_t Hash_Location_data = Temp_Hash % Capacity;
                //找到映射位置
                container_node* _Temp_Node = _HashTable[Hash_Location_data];
                container_node* _Temp_Node_parent = nullptr;
                while(_Temp_Node!= nullptr)
                {
                    //找到位置
                    if(HashDataFunctor(_Temp_Node->_data) == HashDataFunctor(Temp_Val))
                    {
                        if(HeadData == _Temp_Node)
                        {
                            //头节点删除情况
                            if(_Temp_Node == PreviousData)
                            {
                                //只有一个节点
                                HeadData = PreviousData = nullptr;
                                parentJudgment(_Temp_Node_parent,_Temp_Node,Hash_Location_data);
                            }
                            else
                            {
                                //是头节点，不是尾节点
                                parentJudgment(_Temp_Node_parent,_Temp_Node,Hash_Location_data);
                                HeadData = HeadData->LinkNext;
                                HeadData->LinkPrev = nullptr;
                            }
                        }
                        else if(_Temp_Node == PreviousData)
                        {
                            //尾节点删除情况
                            parentJudgment(_Temp_Node_parent,_Temp_Node,Hash_Location_data);
                            PreviousData = PreviousData->LinkPrev;
                            PreviousData->LinkNext = nullptr;
                        }
                        else
                        {
                            //中间节点删除情况
                            parentJudgment(_Temp_Node_parent,_Temp_Node,Hash_Location_data);
                            _Temp_Node->LinkPrev->LinkNext = _Temp_Node->LinkNext;
                            _Temp_Node->LinkNext->LinkPrev = _Temp_Node->LinkPrev;
                        }
                        delete _Temp_Node;
                        _Temp_Node = nullptr;
                        --_size;
                        return true;
                    }
                    _Temp_Node_parent = _Temp_Node;
                    _Temp_Node = _Temp_Node->_next;
                    //向下遍历
                }
                return false;
            }
            iterator find(const HashTableTypeVal& Temp_Val)
            {
                if( _size == 0)
                {
                    return iterator(nullptr);
                }
                else
                {
                    size_t Temp_Hash = DataExtractionFunction(Temp_Val);
                    size_t Hash_Location_data = Temp_Hash % Capacity;
                    //找到映射位置
                    container_node* _Temp_Node = _HashTable[Hash_Location_data];
                    while(_Temp_Node!= nullptr)
                    {
                        if(HashDataFunctor(_Temp_Node->_data) == HashDataFunctor(Temp_Val))
                        {
                            return iterator(_Temp_Node);
                        }
                        _Temp_Node = _Temp_Node->_next;
                    }
                    return iterator(nullptr);
                }
            }                             
        };
        /*############################     BitSet 容器     ############################*/
        class BitSet
        {
            template_container::vector_container::vector<int> _BitSet;
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
            void set(const size_t& Temp_Val)
            {
                //把数映射到BitSet上的函数
                size_t BitSet_Location = Temp_Val / 32; //定位到BitSet的位置在哪个int上
                size_t BitSet_Location_Val = Temp_Val % 32; //定位到BitSet的位置在哪个int上的第几位
                _BitSet[BitSet_Location] = _BitSet[BitSet_Location] | (1 << BitSet_Location_Val);
                //比较当前位置是否为1，若为1则不需要改变，若为0则需要改变，注意|只改变当前位不会改变其他位
                //|是两个条件满足一个条件就行，&是两个条件都满足才行
                //其他位如果是1那么就还是1，如果是0那么就还是0，因为|是两个条件满足一个条件就行
                _size++;
            }
            void reset(const size_t& Temp_Val)
            {
                //删除映射的位置的函数
                size_t BitSet_Location = Temp_Val / 32;
                size_t BitSet_Location_Val = Temp_Val % 32;
                _BitSet[BitSet_Location] = _BitSet[BitSet_Location] & (~(1 << BitSet_Location_Val));
                //&是两个条件都满足，~是取反，^是两个条件不同时满足
                //1取反关键位是0其他位是1，这样就成功与掉，&要求是两个条件都需要满足
                //其他位如果是1那么就不会改变原来的，如果是0那么还是为0，因为与是两个条件都需要满足
                _size--;
            }
            size_t size()       { return _size; }
            bool test(const size_t& Temp_Val)
            {
                if(_size == 0)
                {
                    return false;
                }
                size_t BitSet_Location = Temp_Val / 32;
                size_t BitSet_Location_Val = Temp_Val % 32;
                bool return_BitSet = _BitSet[BitSet_Location] & (1 << BitSet_Location_Val);
                //如果_BitSet[BitSet_Location]里对应的位是1那么就返回true，否则返回false
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
                const MapTypeK& operator()(const KeyValType& Temp_Key_)
                {
                    return Temp_Key_.first;
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
            tree_map& operator=(const tree_map& Map_Temp)
            {
                if(this != &Map_Temp)
                {
                    ROOTMap = Map_Temp.ROOTMap;
                }
                return *this;
            }
            tree_map& operator=(tree_map&& Map_Temp)
            {
                if(this != &Map_Temp)
                {
                    ROOTMap = std::move(Map_Temp.ROOTMap);
                }
                return *this;
            }
            tree_map()                                                   {  ;                                     }
            tree_map(const tree_map& Map_Temp)                                {  ROOTMap = Map_Temp.ROOTMap;       }
            tree_map(tree_map&& Map_Temp)                                     {  ROOTMap=std::move(Map_Temp.ROOTMap);}
            tree_map(const KeyValType& Map_Temp)                       {  ROOTMap.push(Map_Temp);             }
            Map_iterator push(const KeyValType& Map_Temp)         {  return ROOTMap.push(Map_Temp);      }
            Map_iterator pop(const KeyValType& Map_Temp)          {  return ROOTMap.pop(Map_Temp);       }
            iterator find(const KeyValType& Map_Temp)             {  return ROOTMap.find(Map_Temp);      }
            void middle_order_traversal()                           {  ROOTMap.middle_order_traversal();   }
            void Pre_order_traversal()                              {  ROOTMap.Pre_order_traversal();      }
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
            iterator operator[](const KeyValType& Map_Temp)       {  return ROOTMap[Map_Temp];           }
        };
        template <typename UnorderedMapTypeK,typename UnorderedMapTypeV>
        class hash_map
        {
            using KeyValType = template_container::practicality::pair<UnorderedMapTypeK,UnorderedMapTypeV>;
            struct Key_Val
            {
                const UnorderedMapTypeK& operator()(const KeyValType& Temp_Key_)
                {
                    return Temp_Key_.first;
                }
            };
            class Hash_Functor
            {
            public:
                size_t operator()(const KeyValType& Temp_Key_)
                {
                    size_t num_One =  template_container::imitation_functions::hash_imitation_functions()(Temp_Key_.first);
                    num_One = num_One * 31;
                    size_t num_Two =  template_container::imitation_functions::hash_imitation_functions()(Temp_Key_.second);
                    num_Two = num_Two * 31;
                    return (num_One + num_Two);
                }
            };
            using HashTable = base_class_c::HashTable<UnorderedMapTypeK,KeyValType,Key_Val,Hash_Functor>;
            HashTable HashMap;
        public:
            using iterator = typename HashTable::iterator;
            using const_iterator = typename HashTable::const_iterator;
            hash_map()                                     {   ;                                 }  
            ~hash_map()                                    {  HashMap.~HashTable();           }
            hash_map(const KeyValType& Temp_Key_)        {  HashMap.push(Temp_Key_);         }
            bool push(const KeyValType& Temp_Key_)            {  return HashMap.push(Temp_Key_);  }
            bool pop(const KeyValType& Temp_Key_)             {  return HashMap.pop(Temp_Key_);   }
            iterator find(const KeyValType& Temp_Key_)        {  return HashMap.find(Temp_Key_);  }
            size_t size()                                       {  return HashMap.size();           }
            size_t size() const                                 {  return HashMap.size();           }
            size_t capacity() const                             {  return HashMap.capacity();       } 
            bool empty()                                        {  return HashMap.empty();          }
            iterator begin()                                    {  return HashMap.begin();          }
            iterator end()                                      {  return HashMap.end();            }
            const_iterator cbegin()                             {  return HashMap.cbegin();         }
            const_iterator cend()                               {  return HashMap.cend();           }
            iterator operator[](const KeyValType& Temp_Key_)  {  return HashMap[Temp_Key_];       }
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
                const SetTypeK& operator()(const KeyValType& Temp_Key_)
                {
                    return Temp_Key_;
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
            tree_set& operator=(const tree_set& Set_Temp)             
            {  
                if(this!= &Set_Temp)                     
                {  
                    ROOTSet = Set_Temp.ROOTSet;      
                }  
                return *this; 
            }
            tree_set& operator=(tree_set&& Set_temp)
            {
                if(this!= &Set_temp)                     
                {  
                    ROOTSet = std::move(Set_temp.ROOTSet);
                }
                return *this;
            }
            tree_set()                                               {  ;                                        }
            ~tree_set()                                              {  ROOTSet.~RBTree();                    }
            tree_set(const tree_set& Set_Temp)                            {  ROOTSet = Set_Temp.ROOTSet;          }
            tree_set(tree_set&& Set_Temp)                                 {  ROOTSet=std::move(Set_Temp.ROOTSet); }
            tree_set(const KeyValType& Set_Temp)                   {  ROOTSet.push(Set_Temp);                }
            Set_iterator push(const KeyValType& Set_Temp)     {  return ROOTSet.push(Set_Temp);         }
            Set_iterator pop(const KeyValType& Set_Temp)      {  return ROOTSet.pop(Set_Temp);          }
            iterator find(const KeyValType& Set_Temp)         {  return ROOTSet.find(Set_Temp);         }
            void middle_order_traversal()                       {  ROOTSet.middle_order_traversal();      }    
            void Pre_order_traversal()                          {  ROOTSet.Pre_order_traversal();         }  
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
            iterator operator[](const KeyValType& Set_Temp)   {  return ROOTSet[Set_Temp];              }
        };
        template <typename UnorderedSetTypeK>
        class hash_set
        {
            using KeyValType = UnorderedSetTypeK;
            class Hash_Functor
            {
            public:
                size_t operator()(const KeyValType& Temp_Key_)
                {
                    return template_container::imitation_functions::hash_imitation_functions()(Temp_Key_)* 131;
                }
            };
            class Key_Val
            {
            public:
                const KeyValType& operator()(const KeyValType& Temp_Key_)
                {
                    return Temp_Key_;
                }
            };
            using HashTable = template_container::base_class_c::HashTable<UnorderedSetTypeK,KeyValType,Key_Val,Hash_Functor>;
            HashTable HashSet;
        public:
            using iterator = typename HashTable::iterator;
            using const_iterator = typename HashTable::const_iterator;
            hash_set()                                     {  ;                                        }
            ~hash_set()                                    {   HashSet.~HashTable();                }
            bool push(const KeyValType& Set_Temp)             {  return HashSet.push(Set_Temp);         }
            bool pop(const KeyValType& Set_Temp)              {  return HashSet.pop(Set_Temp);          }            
            iterator find(const KeyValType& Set_Temp)         {  return HashSet.find(Set_Temp);         }
            size_t size()                                       {  return HashSet.size();                 }
            bool empty()                                        {  return HashSet.empty();                }
            size_t capacity()                                   {  return HashSet.capacity();             }
            size_t size() const                                 {  return HashSet.size();                 }
            size_t capacity() const                             {  return HashSet.capacity();             }
            iterator begin()                                    {  return HashSet.begin();                }
            iterator end()                                      {  return HashSet.end();                  }
            const_iterator cbegin()                             {  return HashSet.cbegin();               }
            const_iterator cend()                               {  return HashSet.cend();                 }
            iterator operator[](const KeyValType& Set_Temp)   {  return HashSet[Set_Temp];              }
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
            bool test(const BloomFilterTypeVal& Temp_Val)
            {
                size_t num_One   = _Hash.Hash_SDBMHash(Temp_Val) % _Capacity;
                size_t num_Two   = _Hash.Hash_DJBHash (Temp_Val) % _Capacity;
                size_t num_Three = _Hash.Hash_PJWHash (Temp_Val) % _Capacity;
                if(VectorBitSet.test(num_One) == true && VectorBitSet.test(num_Two) == true && VectorBitSet.test(num_Three) && true)
                {
                    return true;
                    /* 有一个为0就返回false */
                }
                return false;
            }
            void set(const BloomFilterTypeVal& Temp_Val)
            {
                size_t num_One   = _Hash.Hash_SDBMHash(Temp_Val) % _Capacity;
                size_t num_Two   = _Hash.Hash_DJBHash (Temp_Val) % _Capacity;
                size_t num_Three = _Hash.Hash_PJWHash (Temp_Val) % _Capacity;
                VectorBitSet.set(num_One);
                VectorBitSet.set(num_Two);
                VectorBitSet.set(num_Three);
            }
            //布隆过滤器只支持插入和查找，不支持删除
        };
    }
}