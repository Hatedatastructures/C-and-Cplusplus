#include <iostream>
#include <cstring>
#include <random>
#include <algorithm>
namespace Wang
{
    namespace STL_Imitation_functions
    {
        //仿函数命名空间
        template<typename Imitation_functions_less>
        class less
        {
        public:
            bool operator()(const Imitation_functions_less& _test1 ,const Imitation_functions_less& _test2)
            {
                return _test1 < _test2;
            }
        };
        template<typename Imitation_functions_greater>
        class greater
        {
        public:
            bool operator()(const Imitation_functions_greater& _test1 ,const Imitation_functions_greater& _test2)
            {
                return _test1 > _test2;
            }
        };
    }
    namespace STL_Demand_class_Helper_functions
    {
        template<typename pair_pointer_T>
        std::ostream& print_pointer_or_nullptr(std::ostream& os, pair_pointer_T* ptr) 
        {
            if (ptr == nullptr) 
            {
                os << "nullptr";
            } 
            else
            {
                os << *ptr;
            }
            return os;
        }
    }
    namespace STL_Demand_class
    {
        template<typename Data_Type_example_pair_T,typename Data_Type_example_pair_K>
        class pair
        {
            using T = Data_Type_example_pair_T;
            using K = Data_Type_example_pair_K;
            //处理指针类型
        public:
            //链接两个相同或不同的类型为一个类型，方便使用
            T first;
            K second;
            pair() : first(T()), second(K()) 
            {
                ;
            }
            pair(const T& _first,const K& _second) 
            : first(_first), second(_second)
            {
                ;
            }
            pair(const pair& other) 
            : first(other.first), second(other.second)
            {
                ;
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
            bool operator==(const pair& other) const
            {
                return (this == &other) ? true : (first == other.first && second == other.second);
            }
            bool operator==(const pair& other)
            {
                return this == &other ? true : (first == other.first && second == other.second);
            }
            bool operator!=(const pair& other)
            {
                return !(*this == other);
            }
            pair* operator->()
            {
                return this;
            }
            const pair* operator->()const
            {
                return this;
            }
            template<typename pair_ostream_T,typename pair_ostream_K>
            friend std::ostream& operator<<(std::ostream& os,const pair<pair_ostream_T,pair_ostream_K>& p);
        };
        template<typename pair_ostream_T,typename pair_ostream_K>
        std::ostream& operator<<(std::ostream& os,const pair<pair_ostream_T,pair_ostream_K>& p)
        {
            os << "(" << p.first << ":" << p.second << ")";
            return os;
        }
        /*                               类分隔                                   */
        template<typename make_pair_T,typename make_pair_K>
        pair<make_pair_T,make_pair_K> make_pair (const make_pair_T& _first,const make_pair_K& _second)
        {
            return pair<make_pair_T,make_pair_K>(_first,_second);
        }
    }
    namespace algorithm
    {
        template <typename Source_sequence_copy,typename Target_sequence_copy>
        Target_sequence_copy copy(Source_sequence_copy begin,Source_sequence_copy end,Target_sequence_copy first)
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
        template<typename Source_sequence_find,typename Target_sequence_find>
        Source_sequence_find find(Source_sequence_find begin,Source_sequence_find end,const Target_sequence_find& value)
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
        template<typename data_type_swap>
        void swap(data_type_swap& a,data_type_swap& b)
        {
            data_type_swap temp = a;
            a = b;
            b = temp;
        }
    }
    /*############################     string容器     ############################*/
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
        iterator begin() 
        {  
            return _data; 
        }
        iterator end()
        {  
            return _data + _size; 
        }
        const_iterator cbegin()const
        { 
            return const_iterator(_data);
        }
        const_iterator cend()const
        { 
            return const_iterator(_data + _size); 
        }
        reverse_iterator rbegin()
        {
            return empty() ? reverse_iterator(end()) : reverse_iterator(end() - 1);
        }
        reverse_iterator rend()
        {
            return empty() ? reverse_iterator(begin()) : reverse_iterator(begin() - 1);
        }
        const_reverse_iterator crbegin()const
        {
            return const_reverse_iterator(cend()- 1);
        }
        const_reverse_iterator crend()const
        {
            return const_reverse_iterator(cbegin()- 1);
        }
        bool empty()
        {
            return _size == 0;
        }
        size_t size()
        {
            //返回有效字符串长度
            return _size;
        }
        size_t capacity()
        {
            //返回容量
            return _capacity;
        }
        size_t size()const
        {
            //返回有效字符串长度
            return _size;
        }
        size_t capacity()const
        {
            //返回容量
            return _capacity;
        }
        char* c_str()const
        {
            //返回C风格字符串
            return _data;
        }
        char back()
        {
            //返回尾字符
            return _size > 0 ? _data[_size - 1] : '\0'; // 添加越界检查（可选）
        }
        char front()
        {
            return _data[0];
        }
        string(const char* data_str = "")
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
        string(const string &data_str)
        :_data(nullptr),_size(data_str._size),_capacity(data_str._capacity)
        {
            //拷贝构造函数，拿传入对象的变量初始化本地变量，对于涉及开辟内存的都要深拷贝
            size_t capacity = data_str._capacity;
            _data = new char[capacity + 1];
            // algorithm::copy(_data,_data+capacity,data_str._data); const对象出错
            std::strcpy(_data, data_str._data);
        }
        string(std::initializer_list<char> data_str)
        {
            //初始化列表构造函数
            _size = data_str.size();
            _capacity = _size;
            _data = new char[_capacity + 1];
            Wang::algorithm::copy(data_str.begin(), data_str.end(), _data);
            _data[_size] = '\0';
        }
        ~string()
        {
            delete [] _data;
            _data = nullptr;
            _capacity = _size = 0;
        }
        string& conversions_oldest()
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
        string& nose_Insertion_substrings(const char*& c_str_substring)
        {
            //前部插入子串
            size_t len = strlen(c_str_substring);
            size_t new_nose_insert_substrings = _size + len;
            if(Automatic_scaling(new_nose_insert_substrings) != true)
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
        string& interlocutory_Insertion_substrings(const char*& c_str_substring,const size_t& oid_pos)
        {
            //中间位置插入子串
            if(oid_pos > _size)
            {
                std::cout << "插入位置越界！" << std::endl;
                return *this;
            }
            size_t len = strlen(c_str_substring);
            size_t new_interlocutory_insert_substrings = _size + len;
            if(Automatic_scaling(new_interlocutory_insert_substrings) != true)
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
        string str_withdraw(const size_t& old_pos)
        {
            //提取字串到'\0'
            if(old_pos > _size)
            {
                std::cout << "提取位置越界！" << std::endl;
                return string();
            }
            string _str_withdraw_temp;
            size_t _str_withdraw_temp_len = _size - old_pos;
            if(_str_withdraw_temp.Automatic_scaling(_str_withdraw_temp_len) != true)
            {
                std::cout << "开辟内存失败！" << std::endl;
                return string();
            }
            strncpy(_str_withdraw_temp._data , _data + old_pos,_str_withdraw_temp_len);
            _str_withdraw_temp._size = _str_withdraw_temp_len;
            _str_withdraw_temp._data[_str_withdraw_temp._size] = '\0';
            return _str_withdraw_temp;
        }
        string str_withdraw_extremity(const size_t& old_begin)
        {
            //提取字串到末尾
            if(old_begin > _size)
            {
                std::cout << "提取位置越界！" << std::endl;
                return string();
            }
            string _str_withdraw_extremity_temp;
            size_t _str_withdraw_extremity_temp_len = _size - old_begin;
            if(_str_withdraw_extremity_temp.Automatic_scaling(_str_withdraw_extremity_temp_len) != true)
            {
                std::cout << "开辟内存失败！" << std::endl;
                return string();
            }
            strncpy(_str_withdraw_extremity_temp._data , _data + old_begin,_str_withdraw_extremity_temp_len);
            _str_withdraw_extremity_temp._size = _str_withdraw_extremity_temp_len;
            _str_withdraw_extremity_temp._data[_str_withdraw_extremity_temp._size] = '\0';
            return _str_withdraw_extremity_temp;
        }
        string str_withdraw_detail(const size_t& old_begin ,const size_t& old_end)
        {
            //提取字串到指定位置
            if(old_begin > _size || old_end > _size || old_begin > old_end)
            {
                std::cout << "提取位置越界！" << std::endl;
                return string();
            }
            string _str_withdraw_detail_temp;
            size_t _str_withdraw_detail_temp_len = old_end - old_begin;
            if(_str_withdraw_detail_temp.Automatic_scaling(_str_withdraw_detail_temp_len) != true)
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
        bool Automatic_scaling(const size_t& temporary_variable)
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
                if(Automatic_scaling(newcapacity) != true)
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
                if(Automatic_scaling(new_capacity) != true)
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
                if(Automatic_scaling( new_capacity) != true)
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
                if(Automatic_scaling(new_size) != true)
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
            if(Automatic_scaling(new_capacity) != true)
            {
                std::cout << "开辟内存失败！" << std::endl;
            }
            return _data;
            //返回首地址迭代器
        }
        string& swap(string& data_str)
        {
            Wang::algorithm::swap(_data,data_str._data);
            Wang::algorithm::swap(_size,data_str._size);
            Wang::algorithm::swap(_capacity,data_str._capacity);
            return *this;
        }
        string rollback()
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
            for(string::const_reverse_iterator rollback = rbegin();rollback != rend();rollback--)
            {
                _rollback_temp.push_back(*rollback);
            }
            return _rollback_temp;
        }
        string rollback_limit(const size_t& limit_begin , const size_t& limit_end)
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

            for(string::const_reverse_iterator rollback = _data + limit_end - 1;rollback != _data + limit_begin - 1;rollback--)
            {
                _rollback_linit_temp.push_back(*rollback);
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
        void string_print_reverse()
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
        string& operator=(const string &data_str)
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
        string& operator+=(const string& data_str)
        {
            size_t len = _size + data_str._size;
            if(Automatic_scaling(len) != true)
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
        bool operator==(string& data_str) const
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
        bool operator==(string& data_str)
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
            if(_str_temp.Automatic_scaling(_str_temp_len) != true)
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
        for(Wang::string::const_iterator originate = data_str.begin();originate != data_str.end();originate++)
        {
            string_ostream << *originate;
        }
        return string_ostream;
    }
    /*############################     vector容器     ############################*/
    template <typename vector_Type>
    class vector
    {
    public:
        using iterator = vector_Type*;
        using const_iterator = const vector_Type*;
        using reverse_iterator = vector_Type*;
        using const_reverse_iterator = const vector_Type*;
    private:
        iterator _data_pointer;     //指向数据的头
        iterator _size_pointer;     //指向数据的尾
        iterator _capacity_pointer; //指向容量的尾
    public:
        iterator begin()
        {
            return _data_pointer;
        }
        iterator end()
        {
            return _size_pointer;
        }
        size_t size()
        {
            return _data_pointer ? (_size_pointer - _data_pointer) : 0;
        }
        size_t capacity()
        {
            return _data_pointer ? (_capacity_pointer - _data_pointer) : 0;
        }
        size_t size() const
        {
            return _data_pointer ? (_size_pointer - _data_pointer) : 0;
        }
        size_t capacity() const 
        {
            return _data_pointer ? (_capacity_pointer - _data_pointer) : 0;
        }
        vector_Type& front()
        {
            return head();
        }
        vector_Type& back()
        {
            return tail();
        }
        vector()
        {
            _data_pointer = nullptr;
            _size_pointer = nullptr;
            _capacity_pointer = nullptr;
        }
        vector(const size_t& sum_size , const vector_Type& data = vector_Type())
        :_data_pointer(new vector_Type[sum_size]),_size_pointer(_data_pointer + sum_size)
        ,_capacity_pointer(_data_pointer + sum_size)
        {
            for(size_t i = 0;i < sum_size;i++)
            {
                _data_pointer[i] = data;
            }
        }
        vector(std::initializer_list<vector_Type> list_temp)
        :_data_pointer(new vector_Type[list_temp.size()]),_size_pointer(_data_pointer + list_temp.size())
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
        bool empty()
        {
            return size() == 0; // 直接通过 size() 判断
        }
        vector_Type& head()
        {
            return *_data_pointer;
        }
        vector_Type& tail()
        {
            return *(_size_pointer-1);
        }
        vector_Type& find(const size_t& find_size_)
        {
            if(find_size_ >= size())
            {
                //先默认返回空数组,但是需要提前写该类型的默认构造函数
                static vector_Type dummy;
                return dummy;
            }
            return _data_pointer[find_size_];
        }
        vector<vector_Type>& Completion(const size_t& Completion_size_ , const vector<vector_Type>& Completion_temp_)
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
        vector(const vector<vector_Type>& temp_data)
        :_data_pointer(temp_data.capacity() ? new vector_Type[temp_data.capacity()] : nullptr),
        _size_pointer(_data_pointer + temp_data.size()),_capacity_pointer(_data_pointer + temp_data.capacity())
        {
           for(size_t i = 0; i < temp_data.size();i++)
           {
                _data_pointer[i] = temp_data._data_pointer[i];
           }
        }
        ~vector()
        {
            delete[] _data_pointer;
            _data_pointer = _size_pointer =_capacity_pointer = nullptr;
        }
        void swap(vector<vector_Type>& temp_data)
        {
            Wang::algorithm::swap(_data_pointer, temp_data._data_pointer);
            Wang::algorithm::swap(_size_pointer, temp_data._size_pointer);
            Wang::algorithm::swap(_capacity_pointer, temp_data._capacity_pointer);
        }
        iterator erase(iterator pos)
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
        vector<vector_Type>& resize(const size_t& new_capacity)
        {
            size_t old_size = size();  // 先保存原来的元素数量
            if ((size_t)(_capacity_pointer - _data_pointer) < new_capacity) 
            {
                //涉及到迭代器失效问题，不能调用size()函数，会释放未知空间
                iterator new_data = new vector_Type[new_capacity]; 
                // 复制原先的数据
                for (size_t i = 0; i < old_size; i++) 
                {
                    new_data[i] = _data_pointer[i];
                }
                delete [] _data_pointer;
                _data_pointer = new_data;
                //对于自定义类型delete会释放资源，而new_data是新new出来的因该不会导致资源泄露
                _size_pointer = _data_pointer + old_size;  // 使用 old_size 来重建 _size_pointer
                _capacity_pointer = _data_pointer + new_capacity;
            }
            return *this;
        }
        vector<vector_Type>& push_back(const vector_Type& push_back_temp_)
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
        vector<vector_Type>& pop_back() 
        {
            if (_size_pointer > _data_pointer) 
            { // 至少有一个元素
                --_size_pointer; // 尾指针前移
            }
            return *this;
        }
        vector<vector_Type>& push_front(const vector_Type& pop_back_temp_)
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
        vector<vector_Type>& pop_front()
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
        vector_Type& operator[](const size_t& _size_operator)
        {
            return _data_pointer[_size_operator];
        }
        const vector_Type& operator[](const size_t& _size_operator)const 
        {
            return _data_pointer[_size_operator];
        }
        vector<vector_Type>& operator=(const vector<vector_Type>&vector_temp_)
        {
            if (this != &vector_temp_) 
            {
                vector<vector_Type> temp(vector_temp_); // 拷贝构造
                swap(temp); // 交换资源，temp析构时会释放原资源
            }
            return *this;
        }
        vector<vector_Type>& operator+=(const vector<vector_Type>& _temp_)
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
        template <typename const_vector_Output_templates>
        friend std::ostream& operator<< (std::ostream& vector_ostream, const vector<const_vector_Output_templates>& Dynamic_arrays_data);
    };
    template <typename const_vector_Output_templates>
    std::ostream& operator<<(std::ostream& vector_ostream, const vector<const_vector_Output_templates>& Dynamic_arrays_data)
    {
        for(size_t i = 0; i < Dynamic_arrays_data.size(); i++)
        {
            vector_ostream << Dynamic_arrays_data[i] << " ";
        }
        return vector_ostream;
    }
    /*############################     list容器     ############################*/
    
    template <typename list_Type>
    class list
    {
        template<typename list_Type_Function_Node>
        struct listNode
        {
            //节点类
            listNode<list_Type_Function_Node>* _prev;
            listNode<list_Type_Function_Node>* _next;
            list_Type_Function_Node _data;

            listNode(const list_Type_Function_Node& data = list_Type_Function_Node())
            :_prev(nullptr), _next(nullptr), _data(data)
            {
                //列表初始化
            }
            
        };
        template <typename list_Node_Type_iterator ,typename Ref ,typename Ptr >
        class _list_iterator_
        {
        public:
            //迭代器类
            using Node      = listNode<list_Node_Type_iterator> ;
            using iterator  = _list_iterator_<list_Node_Type_iterator ,list_Node_Type_iterator& ,list_Node_Type_iterator*>;
            using reference = Ref ;
            using pointer   = Ptr ;
            Node* _node;
            _list_iterator_(Node* node)
            :_node(node)
            {
                //拿一个指针来构造迭代器
            }
            Ref operator*()
            {
                //返回该节点的自定义类型的数据
                return _node->_data;
            }
            _list_iterator_& operator++()
            {
                //先加在用
                _node = _node -> _next;
                return *this;
                //返回类型名，如果为迭代器就会因为const 报错
            }
            _list_iterator_ operator++(int)
            {
                //先用在加
                _list_iterator_ temp(_node);
                _node = _node->_next;
                //把本体指向下一个位置
                return temp;
            }
            _list_iterator_& operator--()
            {
                _node = _node->_prev;
                return *this;
            }
            _list_iterator_ operator--(int)
            {
                _list_iterator_ temp (_node);
                _node = _node->_prev;
                return temp;
            }
            bool operator!= (const _list_iterator_& _iterator_temp_)
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
        class _Reverse_list_iterator_
        {
            //创建反向迭代器
            using  Ref = typename iterator::reference;
            using  Ptr = typename iterator::pointer ;
            using  _const_reverse_list_iterator = _Reverse_list_iterator_<iterator>;
        public:
            iterator _it;
            _Reverse_list_iterator_(iterator it)
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
            _Reverse_list_iterator_& operator++()
            {
                --_it;
                return *this;
            }
            _Reverse_list_iterator_ operator++(int)
            {
                _Reverse_list_iterator_ _temp (_it);
                --_it;
                return _temp;
            }
            _Reverse_list_iterator_& operator--()
            {
                ++_it;
                return *this;
            }
            _Reverse_list_iterator_ operator--(int)
            {
                _Reverse_list_iterator_ _temp (_it);
                ++_it;
                return _temp;
            }
            bool operator!=(const _const_reverse_list_iterator& _temp_)
            {
                return _it != _temp_._it;
            }
        };
        using Node = listNode<list_Type>;

        Node* _head;
        //_head为哨兵位
        void CreateHead()
        {
            _head = new Node;
            _head -> _prev = _head;
            _head -> _next = _head;
        }
    public:
        using iterator = _list_iterator_<list_Type,list_Type& ,list_Type*>;
        using const_iterator = _list_iterator_<list_Type,const list_Type&,const list_Type*>;

        //拿正向迭代器构造反向迭代器，可以直接调用 iterator 已经重载的运算符和函数，相当于在封装一层类
        using reverse_iterator = _Reverse_list_iterator_<iterator> ;
        using reverse_const_iterator = _Reverse_list_iterator_<const_iterator>;
        list()
        {
            CreateHead();
        }
        ~list()
        {
            clear();
            delete _head;
            _head = nullptr;
        }
        list(iterator first , iterator last)
        {
            //通过另一个list对象构建一个list
            CreateHead();
            //已经创建一个哨兵节点
            while (first != last)
            {
                push_back(*first);
                ++first;
            }
        }
        list(std::initializer_list<list_Type> list_temp)
        {
            //通过初始化列表构建一个list
            CreateHead();
            for(auto& e:list_temp)
            {
                push_back(e);
            }
        }
        list(const_iterator first , const_iterator last)
        {
            //通过另一个list对象构建一个list
            CreateHead();
            //已经创建一个哨兵节点
            while (first != last)
            {
                push_back(*first);
                ++first;
            }
        }
        list(const list<list_Type>& _list_data)
        {
            //拷贝构造
            CreateHead();
            list<list_Type> _temp_ (_list_data.cbegin(),_list_data.cend());
            swap(_temp_);
        }
        void swap(Wang::list<list_Type>& _swap_temp)
        {
            Wang::algorithm::swap(_head,_swap_temp._head);
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
			Node* cur = _head->_next;
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
        list_Type& front()
		{
			return _head->_next->_data;
		}

		const list_Type& front()const
		{
			return _head->_next->_data;
		}

		list_Type& back()
		{
			return _head->_prev->_data;
		}

		const list_Type& back()const
		{
			return _head->_prev->_data;
		}
        /*
        插入删除操作
        */
        void push_back(const list_Type& push_back_data)
        {
            insert(end(),push_back_data);
        }
        void push_front(const list_Type& push_front_data)
        {
            //插入到头
            insert(begin(),push_front_data);
        }
        void pop_back() 
		{ 
            //删除尾
			erase(--end()); 
		}
        iterator pop_front() 
		{ 
            //删除头
			return erase(begin()); 
		}
        iterator insert(iterator pos ,const list_Type& val)
        {
            Node* Pnew_node = new Node(val);
            //开辟新节点
            Node* Pcur = pos._node;
            //保存pos位置的值
            Pnew_node->_prev = Pcur->_prev;
            Pnew_node->_next = Pcur;
            Pnew_node->_prev->_next = Pnew_node;
            Pcur->_prev = Pnew_node;
            return iterator(Pnew_node);
        }
        iterator erase(iterator pos)
		{
			// 找到待删除的节点
			Node* pDel = pos._node;
			Node* pRet = pDel->_next;

			// 将该节点从链表中拆下来并删除
			pDel->_prev->_next = pDel->_next;
			pDel->_next->_prev = pDel->_prev;
			delete pDel;

			return iterator(pRet);
		}
        void resize(size_t newsize, const list_Type& data = list_Type())
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
        void clear()
		{
            //循环释放资源
			Node* cur = _head->_next;
			// 采用头删除
			while (cur != _head)
			{
				_head->_next = cur->_next;
				delete cur;
				cur = _head->_next;
			}

			_head->_next = _head->_prev = _head;
		}
        list& operator=(list<list_Type> _lsit_temp)
        {
            //运算符重载
            if( this != &_lsit_temp)
            {
                swap(_lsit_temp);
            }
            return *this;
        }
        list operator+(const list<list_Type>& _list_temp_)
        {
            list<list_Type> _return_temp_ (cbegin(),cend());
            const_iterator _begin = _list_temp_.cbegin();
            const_iterator _end  = _list_temp_.cend();
            while(_begin != _end)
            {
                _return_temp_.push_back(*_begin);
                ++_begin;
            }
            return _return_temp_;
        }
        list& operator+=(const list<list_Type>& _lsit_temp_)
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
        template <typename const_list_Output_templates>
        friend std::ostream& operator<< (std::ostream& list_ostream, const list<const_list_Output_templates>& Dynamic_arrays_data);
        
        template <typename list_Output_templates>
        friend std::ostream& operator<< (std::ostream& list_ostream, list<list_Output_templates>& Dynamic_arrays_data);
    };
    template <typename const_list_Output_templates>
    std::ostream& operator<< (std::ostream& list_ostream, const list<const_list_Output_templates>& Dynamic_arrays_data)
    {
        //typename声明这是一个类型而不是表达式
        typename list<const_list_Output_templates>::const_iterator it = Dynamic_arrays_data.cbegin();
        while (it != Dynamic_arrays_data.cend()) 
        {
            list_ostream << *it << " ";
            ++it;
        }
        return list_ostream;
    }

    template <typename list_Output_templates>
    std::ostream& operator<< (std::ostream& list_ostream, list<list_Output_templates>& Dynamic_arrays_data)
    {
        //typename声明这是一个类型而不是表达式
        typename list<list_Output_templates>::iterator it = Dynamic_arrays_data.begin();
        while (it != Dynamic_arrays_data.end()) 
        {
            list_ostream << *it << " ";
            ++it;
        }
        return list_ostream;
    }
    /*############################     staic适配器     ############################*/
    template <typename staic_Type,typename Container_staic = Wang::vector<staic_Type>>
    class stack
    {
    private:
        Container_staic Container_stack_temp_;
    public:
        ~stack()
        {
            ;
        }
        void push(const staic_Type& _stack_temp)
        {
            //插入尾
            Container_stack_temp_.push_back(_stack_temp);
        }
        void pop()
        {
            //删除尾
            Container_stack_temp_.pop_back();
        }
        size_t size()
        {
            return Container_stack_temp_.size();
        }
        bool empty()
        {
            return Container_stack_temp_.empty();
        } 
        staic_Type& top()
        {
            return Container_stack_temp_.back();
        }
        stack(const stack<staic_Type>& _stack_temp)
        {
            Container_stack_temp_ = _stack_temp.Container_stack_temp_;
        }
        stack(std::initializer_list<staic_Type> _stack_temp)
        {
            for(auto& e:_stack_temp)
            {
                Container_stack_temp_.push_back(e);
            }
        }
        stack(const staic_Type& _stack_temp)
        {
            Container_stack_temp_.push_back(_stack_temp);
        }
        stack()
        {
            ;
        }
    };
    /*############################     queue适配器     ############################*/
    template <typename queue_Type ,typename Container_queue = Wang::list<queue_Type> >
    class queue
    {
        //注意队列适配器不会自动检测队列有没有元素，为学异常，注意空间元素
        Container_queue Container_queue_temp_;
    public:
        ~queue()
        {
            ;
        }
        void push(const queue_Type& _queue_temp)
        {
            Container_queue_temp_.push_back(_queue_temp);
        }
        void pop ()
        {
            Container_queue_temp_.pop_front();
            //list返回的是指向下一个位置的正向迭代器
            //vector返回的是整个容器
        }
        size_t size()
        {
            //返回元素个数
            return Container_queue_temp_.size();
        }
        bool empty()
        {
            //判断容器是否为空
            return Container_queue_temp_.empty();
        }
        queue_Type& front()
        {
            //查看头数据
            return Container_queue_temp_.front();
        }
        queue_Type& back()
        {
            //查看尾数据
            return Container_queue_temp_.back();
        }
        queue(const queue<queue_Type>& _queue_temp)
        {
            //拷贝构造
            Container_queue_temp_ = _queue_temp.Container_queue_temp_;
        }
        queue(std::initializer_list<queue_Type> _queue_temp)
        {
            //初始化列表
            for(auto& e:_queue_temp)
            {
                Container_queue_temp_.push_back(e);
            }
        }
        queue(const queue_Type& _queue_temp)
        {
            //拷贝构造
            Container_queue_temp_.push_back(_queue_temp);
        }
        queue()
        {
            ;
        }
    };
    /*############################     priority_queue适配器     ############################*/
    template <typename priority_queue_Type,
    typename Imitation_function_parameter_function = Wang::STL_Imitation_functions::less<priority_queue_Type>,
    typename Container_priority_queue = Wang::vector<priority_queue_Type>>
    class priority_queue
    {
        //创建容器对象
        Container_priority_queue Container_priority_queue_temp;
        Imitation_function_parameter_function com;
        //仿函数对象

        void priority_queue_Adjust_upwards(int Adjust_upwards_child)
        {
            //向上调整算法
            int parent = (Adjust_upwards_child-1)/2;
            while(Adjust_upwards_child > 0)
            {
                if(com(Container_priority_queue_temp[parent],Container_priority_queue_temp[Adjust_upwards_child]))
                {
                    Wang::algorithm::swap(Container_priority_queue_temp[parent],Container_priority_queue_temp[Adjust_upwards_child]);
                    Adjust_upwards_child = parent;
                    parent = (Adjust_upwards_child-1)/2;
                }
                else
                {
                    break;
                }
            }
        }
        void priority_queue_Adjust_downwards(int parent = 0)
        {
            int priority_queue_Adjust_downwards_child = (parent*2)+1;
            while(priority_queue_Adjust_downwards_child < (int)Container_priority_queue_temp.size())
            {
                int left = priority_queue_Adjust_downwards_child;
                int right =left+1;
                if( right < (int)Container_priority_queue_temp.size() && com(Container_priority_queue_temp[left],Container_priority_queue_temp[right]))
                {
                    //大堆找出左右节点哪个孩子大
                    priority_queue_Adjust_downwards_child = right;
                }
                if(com(Container_priority_queue_temp[parent],Container_priority_queue_temp[priority_queue_Adjust_downwards_child]))
                {
                    //建大堆把小的换下去，建小堆把大的换下去
                    Wang::algorithm::swap( Container_priority_queue_temp[parent] , Container_priority_queue_temp[priority_queue_Adjust_downwards_child]);

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
        ~priority_queue()
        {
            ;
        }
        void push(const priority_queue_Type Function_templates_priority_queue_push_back)
        {
            Container_priority_queue_temp.push_back(Function_templates_priority_queue_push_back);
            priority_queue_Adjust_upwards((int)Container_priority_queue_temp.size()-1);
        }
        priority_queue_Type& top()
        {
            return Container_priority_queue_temp.front();
        }
        bool empty()
        {
            return Container_priority_queue_temp.empty();
        }
        size_t size()
        {
            return Container_priority_queue_temp.size();
        }
        void pop()
        {
            Wang::algorithm::swap(Container_priority_queue_temp[0],Container_priority_queue_temp[Container_priority_queue_temp.size()-(size_t)1]);
            Container_priority_queue_temp.pop_back();
            priority_queue_Adjust_downwards();
        }
        priority_queue()
        {
            ;
        }
        priority_queue(std::initializer_list<priority_queue_Type> list_temp)
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
            Container_priority_queue_temp = _priority_queue_temp.Container_priority_queue_temp;
            priority_queue_Adjust_upwards((int)Container_priority_queue_temp.size()-1);
        }
        priority_queue(const priority_queue_Type& _priority_queue_temp)
        {
            //拷贝构造
            Container_priority_queue_temp.push_back(_priority_queue_temp);
            priority_queue_Adjust_upwards((int)Container_priority_queue_temp.size()-1);
        }
    };
    /*############################     Binary_search_tree 容器     ############################*/
    template <typename BS_Tree_Type,typename Imitation_function_parameter_function_BS_Tree = Wang::STL_Imitation_functions::less <BS_Tree_Type> >
    class BS_Tree
    {
    private:
        template <typename BS_Tree_Type_Function_Node>
        class BS_Tree_Type_Node
        {
        public:
            //节点类
            BS_Tree_Type_Node* _left;
            BS_Tree_Type_Node* _right;
            BS_Tree_Type_Function_Node _data;
            BS_Tree_Type_Node(const BS_Tree_Type_Function_Node& data = BS_Tree_Type_Function_Node())
            :_left(nullptr),_right(nullptr),_data(data)
            {
                ;
            }
            ~BS_Tree_Type_Node()
            {
                _left  = nullptr;
                _right = nullptr;
            }
        };
        using BS_Tree_Node = BS_Tree_Type_Node <BS_Tree_Type>;
        BS_Tree_Node* _ROOT;
        Imitation_function_parameter_function_BS_Tree com;
        void _Middle_order_traversal(BS_Tree_Node* _ROOT_Temp)
        {
            //中序遍历函数
            Wang::stack<BS_Tree_Node*> _staic_temp_;
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
        size_t _Middle_order_traversal(BS_Tree_Node* _ROOT_Temp,size_t& _size_temp_ )
        {
            Wang::stack<BS_Tree_Node*> _staic_temp_;
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
        void _Pre_order_traversal(BS_Tree_Node* _ROOT_Temp )
        {
            //前序遍历，最外左子树全部压栈
            if(_ROOT_Temp == nullptr)
            {
                return;
            }
            BS_Tree_Node* _Pre_order_traversal_test = _ROOT_Temp;
            Wang::stack<BS_Tree_Node*> stack_Temp;
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
        void clear()
        {
            if(_ROOT == nullptr)
            {
                return;
            }
            //循环释放资源
            Wang::stack<BS_Tree_Node*> _staic_clear_temp_;
            _staic_clear_temp_.push(_ROOT);
            while(_staic_clear_temp_.empty() == false)
            {
                BS_Tree_Node* _ROOT_Temp = _staic_clear_temp_.top();
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
            _ROOT = nullptr;
        }
    public:
        ~BS_Tree()
        {
            clear();
        }
        // 构造函数，使用初始化列表来初始化二叉搜索树
        BS_Tree(std::initializer_list<BS_Tree_Type> list_temp)
        {
            for(auto& e:list_temp)
            {
                push(e);
            }
        }
        BS_Tree(const BS_Tree_Type& BST_Temp = BS_Tree_Type(),Imitation_function_parameter_function_BS_Tree com_temp = Imitation_function_parameter_function_BS_Tree())
        :_ROOT(nullptr),com(com_temp)
        {   
            _ROOT = new BS_Tree_Node(BST_Temp);
        }
        BS_Tree(const BS_Tree& _Binary_search_tree_temp)
        :_ROOT(nullptr),com(_Binary_search_tree_temp.com)
        //这个拷贝构造不需要传模板参数，因为模板参数是在编译时确定的，而不是在运行时确定的，对于仿函数，直接拿传进来的引用初始化就可以了
        {
            //拷贝构造，时间复杂度为O(n)
            BS_Tree_Node* _Binary_search_tree_temp_copy = _Binary_search_tree_temp._ROOT;
            if(_Binary_search_tree_temp_copy == nullptr)
            {
                return;
            }
            Wang::stack<Wang::STL_Demand_class::pair<BS_Tree_Node*,BS_Tree_Node**> > _staic_temp_;
            //注意这里把本地_ROOT类型传过去，是因为要对本地的_ROOT进行操作，所以要传二级指针
            //这里传引用也不行，这里的对象是动态变化的，所以传引用也不行
            //如果是对全局的_ROOT进行操作，就传一级指针
            _staic_temp_.push(Wang::STL_Demand_class::pair<BS_Tree_Node*,BS_Tree_Node**>(_Binary_search_tree_temp_copy,&_ROOT));
            while( !_staic_temp_.empty() )
            {
                auto _staic_temp_pair = _staic_temp_.top();
                _staic_temp_.pop();
                *(_staic_temp_pair.second) = new BS_Tree_Node(_staic_temp_pair.first->_data);
                // BS_Tree_Node* _staic_temp_pair_second = *(_staic_temp_pair.second);
                // if(_staic_temp_pair.first->_left!= nullptr)
                // {
                //     _staic_temp_.push(Wang::STL_Demand_class::pair<BS_Tree_Node*,BS_Tree_Node**>(_staic_temp_pair.first->_left,&_staic_temp_pair_second->_left));
                // }
                // if(_staic_temp_pair.first->_right!= nullptr)
                // {
                //     _staic_temp_.push(Wang::STL_Demand_class::pair<BS_Tree_Node*,BS_Tree_Node**>(_staic_temp_pair.first->_right,&_staic_temp_pair_second->_right));
                // }
                //移除临时变量，直接使用指针解引用
                if(_staic_temp_pair.first->_right!= nullptr)
                {
                    _staic_temp_.push(Wang::STL_Demand_class::pair<BS_Tree_Node*,BS_Tree_Node**>(_staic_temp_pair.first->_right,&((*_staic_temp_pair.second)->_right)));
                }
                if(_staic_temp_pair.first->_left!= nullptr)
                {
                    _staic_temp_.push(Wang::STL_Demand_class::pair<BS_Tree_Node*,BS_Tree_Node**>(_staic_temp_pair.first->_left,&((*_staic_temp_pair.second)->_left)));
                }
            }
        }
        void Middle_order_traversal()
        {
            //中序遍历函数
            _Middle_order_traversal(_ROOT);
        }
        void Pre_order_traversal()
        {
            _Pre_order_traversal(_ROOT);
        }
        bool push(const BS_Tree_Type& data)
        {
            //尾上插入函数
            if(_ROOT == nullptr)
            {
                _ROOT = new BS_Tree::BS_Tree_Type_Node<BS_Tree_Type>(data);
                return true;
            }
            else
            {
                BS_Tree_Node* _ROOT_Temp = _ROOT;
                BS_Tree_Node* _ROOT_Temp_Parent = nullptr;
                while(_ROOT_Temp!= nullptr)
                {
                    _ROOT_Temp_Parent = _ROOT_Temp;
                    if(!com(data, _ROOT_Temp->_data) && !com(_ROOT_Temp->_data, data))
                    {
                        //改用仿函数特性，判断是否有重复元素,防止自定义类型没有重载==运算符
                        return false;
                    }
                    else if(com(data , _ROOT_Temp->_data))
                    {
                        _ROOT_Temp = _ROOT_Temp->_left;
                    }
                    else
                    {
                        _ROOT_Temp = _ROOT_Temp->_right;
                    }
                }
                //新开节点链接
                BS_Tree_Node* _ROOT_Temp_Node = new BS_Tree::BS_Tree_Type_Node<BS_Tree_Type>(data);
                //链接节点
                if(com(data , _ROOT_Temp_Parent->_data))
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
        BS_Tree& pop(const BS_Tree_Type& data)
        {
            //删除节点
            BS_Tree_Node* _ROOT_Temp = _ROOT;
            BS_Tree_Node* _ROOT_Temp_Parent = nullptr;
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
                            // 当前节点是根节点，直接更新 _ROOT
                            _ROOT = _ROOT_Temp->_right;
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
                            // 防止当前节点是根节点，无法解引用，直接更新 _ROOT
                            _ROOT = _ROOT_Temp->_left;
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
                    	BS_Tree_Node* _ROOT_Temp_right_min = _ROOT_Temp->_right;
                        BS_Tree_Node* _ROOT_Temp_test_Parent = _ROOT_Temp;
                        while(_ROOT_Temp_right_min->_left != nullptr)
                        {
                            _ROOT_Temp_test_Parent = _ROOT_Temp_right_min;
                            _ROOT_Temp_right_min = _ROOT_Temp_right_min->_left;
                        }
                        //找到最左节点	
                        Wang::algorithm::swap(_ROOT_Temp->_data,_ROOT_Temp_right_min->_data);
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
                else if(com(data, _ROOT_Temp->_data))
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
            return _Middle_order_traversal(_ROOT,_size);
        }
        size_t size()const
        {
            size_t _size = 0;
            return _Middle_order_traversal(_ROOT,_size);
        }
        BS_Tree_Node* find(const BS_Tree_Type& data)
        {
            //查找函数
            BS_Tree_Node* _ROOT_Find = _ROOT;
            while(_ROOT_Find!= nullptr)
            {
                if(data == _ROOT_Find->_data)
                {
                    return _ROOT_Find;
                }
                else if(com(data, _ROOT_Find->_data))
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
        void insert(const BS_Tree_Type& former_data,const BS_Tree_Type& latter_data)
        {
            //在former_data后面插入latter_data
            BS_Tree_Node* _ROOT_former_data = find(former_data);
            //插入节点
            if(_ROOT_former_data == nullptr)
            {
                return;
            }
            else
            {
                BS_Tree_Node* _ROOT_latter_data = new BS_Tree_Node(latter_data);
                _ROOT_latter_data->_left = _ROOT_former_data->_right;
                _ROOT_former_data->_right = _ROOT_latter_data;
            }
        }
        BS_Tree& operator=(const BS_Tree& _Binary_search_tree_temp)
        {
            //赋值运算符重载
            if(this != &_Binary_search_tree_temp)
            {
                clear();
                com = _Binary_search_tree_temp.com;
                BS_Tree _Binary_search_tree_temp_copy = _Binary_search_tree_temp;
                Wang::algorithm::swap(_Binary_search_tree_temp_copy._ROOT,_ROOT);
            }
            return *this;
        }
    };
    /*############################     AVL_Tree 容器     ############################*/
    template <typename AVL_Tree_Type_K,     typename AVL_Tree_Type_V,
    typename Imitation_function_parameter_function_AVL_Tee = Wang::STL_Imitation_functions::less < AVL_Tree_Type_K >,
    typename AVL_Tree_Synthetic_class = Wang::STL_Demand_class::pair<AVL_Tree_Type_K,AVL_Tree_Type_V> >
    class AVL_Tree
    {
    private:
        template<typename AVL_Tree_Type_Node_K,typename AVL_Tree_Type_Node_V>
        class AVL_Tree_Type_Node
        {
        public:
            AVL_Tree_Synthetic_class _data;

            AVL_Tree_Type_Node<AVL_Tree_Type_Node_K,AVL_Tree_Type_Node_V>* _left;
            AVL_Tree_Type_Node<AVL_Tree_Type_Node_K,AVL_Tree_Type_Node_V>* _right;
            AVL_Tree_Type_Node<AVL_Tree_Type_Node_K,AVL_Tree_Type_Node_V>* _parent;
            //平衡因子
            int _Balance_factor;
            AVL_Tree_Type_Node(const AVL_Tree_Type_K& Tree_Node_temp_ = AVL_Tree_Type_K(),const AVL_Tree_Type_V& Tree_Node_temp_2 = AVL_Tree_Type_V())
            :_data(Tree_Node_temp_,Tree_Node_temp_2),_left(nullptr),_right(nullptr),_parent(nullptr),_Balance_factor(0)
            {
                ;
            }
            AVL_Tree_Type_Node(const AVL_Tree_Synthetic_class& AVL_Tree_pair_temp)
            :_data(AVL_Tree_pair_temp),_left(nullptr),_right(nullptr),_parent(nullptr),_Balance_factor(0)
            {
                ;
            }
        };
        using AVL_Node = AVL_Tree_Type_Node<AVL_Tree_Type_K,AVL_Tree_Type_V>;
        AVL_Node* _ROOT;

        Imitation_function_parameter_function_AVL_Tee com;
        void _left_revolve(AVL_Node* parent_temp_Node)
        {
            //传进来的值是发现该树平衡性被破坏的节点地址
            //大致思想：因为这是左单旋，所以找传进来的父亲节点的右根节点来当调整节点
            //然后把调整节点的左根节点赋值给传进来的父亲节点的右根节点 (刚才已经用节点保存过调整节点，所以这里直接赋值)，
            //再把父亲节点赋值给调整节点的左根节点，！！注意：在旋转的过程中还要处理每个调整节点的父亲节点的指向和平衡因子

            // {
            //     AVL_Node* Sub_right_temp = parent_temp_Node->_right;
            //     parent_temp_Node->_right = Sub_right_temp->_left;
            //     Sub_right_temp->_left = parent_temp_Node;
            //     //错误写法：未同步调整父亲节点和判断调整节点的左根节点是否为空，以及全部需要调整节点的父亲指针的指针的指向
            // }
            if(parent_temp_Node == nullptr|| parent_temp_Node->_right == nullptr)
            {
                std::cout <<"left "<< "空指针"  <<std::endl;
                return ;
            }
            AVL_Node* Sub_right_temp = parent_temp_Node->_right;
            // AVL_Node* Sub_right_left_temp = Sub_right_temp->_left;
            AVL_Node* Sub_right_left_temp = (Sub_right_temp->_left)? Sub_right_temp->_left : nullptr;
            //防止空指针解引用
            parent_temp_Node->_right = Sub_right_left_temp;
            if(Sub_right_left_temp)
            {
                Sub_right_left_temp->_parent = parent_temp_Node;
                //如果Sub_right_left_temp(调整节点的左根节点)不等于空，还需要调整Sub_right_left_temp它的父亲节点
            }
            Sub_right_temp->_left = parent_temp_Node;
            //这里先保存一下parent_temp_Node的父亲地址，防止到下面else比较的时候丢失
            AVL_Node* parent_parent_temp_Node = parent_temp_Node->_parent;
            parent_temp_Node->_parent = Sub_right_temp;
            //更新parent_temp_Node节点指向正确的地址

            if(_ROOT == parent_temp_Node)
            {
                //如果要调整的节点是根根节点，直接把调整节点赋值给根节点，然后把调整节点的父亲节点置空
                _ROOT = Sub_right_temp;
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
            parent_temp_Node->_Balance_factor = Sub_right_temp->_Balance_factor = 0;
        }

        void _right_revolve(AVL_Node* parent_temp_Node)
        {
            //思路同左单旋思路差不多
            if(parent_temp_Node == nullptr|| parent_temp_Node->_left == nullptr)
            {
                std::cout <<"right "<< "空指针"  <<std::endl; 
                return ;
            }
            AVL_Node* Sub_left_temp = parent_temp_Node->_left;
            AVL_Node* Sub_left_right_temp = (Sub_left_temp->_right) ? Sub_left_temp->_right : nullptr;
            //防止空指针解引用
            parent_temp_Node->_left = Sub_left_right_temp;
            if(Sub_left_right_temp)
            {
                Sub_left_right_temp->_parent = parent_temp_Node;
            }
            Sub_left_temp->_right = parent_temp_Node;
            //保存parent_temp_Node的父亲节点
            AVL_Node* parent_parent_temp_Node = parent_temp_Node->_parent;
            parent_temp_Node->_parent = Sub_left_temp;

            if(_ROOT == parent_temp_Node)
            {
                _ROOT = Sub_left_temp;
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
            parent_temp_Node->_Balance_factor = Sub_left_temp->_Balance_factor = 0;
        }
        void _right_left_revolve(AVL_Node* parent_temp_Node)
        {
            if(parent_temp_Node==nullptr || parent_temp_Node->_right == nullptr)
            {
                std::cout <<"right_left "<< "空指针"  <<std::endl;
                return;
            }
            AVL_Node* Sub_right_temp = parent_temp_Node->_right;
            AVL_Node* Sub_right_left_temp = Sub_right_temp->_left;
            int Balance_factor_temp = Sub_right_left_temp->_Balance_factor;

            _right_revolve(parent_temp_Node->_right);
            //右旋
            _left_revolve(parent_temp_Node);
            //左旋
            if(Balance_factor_temp == -1)
            {
                parent_temp_Node->_Balance_factor = 0;
                Sub_right_temp->_Balance_factor = 1;
                Sub_right_left_temp->_Balance_factor = 0;
            }
            else if(Balance_factor_temp == 1)
            {
                parent_temp_Node->_Balance_factor = -1;
                Sub_right_temp->_Balance_factor = 0;
                Sub_right_left_temp->_Balance_factor = 0;
            }
            else
            {
                parent_temp_Node->_Balance_factor = 0;
                Sub_right_temp->_Balance_factor = 0;
                Sub_right_left_temp->_Balance_factor = 0;
            }
        }
        void _left_right_revolve(AVL_Node* parent_temp_Node)
        {   
            if(parent_temp_Node == nullptr || parent_temp_Node->_left == nullptr)
            {
                std::cout << "left_right " << "空指针" << std::endl;
                return ;
            }
            AVL_Node* Sub_left_temp = parent_temp_Node->_left;
            AVL_Node* Sub_left_right_temp = Sub_left_temp->_right;
            int Balance_factor_temp = Sub_left_right_temp->_Balance_factor;

            _left_revolve(parent_temp_Node->_left);
            //左旋
            _right_revolve(parent_temp_Node);
            //右旋
            if(Balance_factor_temp == -1)
            {
                parent_temp_Node->_Balance_factor = 0;
                Sub_left_temp->_Balance_factor = 1;
                Sub_left_right_temp->_Balance_factor = 0;
            }
            else if(Balance_factor_temp == 1)
            {
                parent_temp_Node->_Balance_factor = -1;
                Sub_left_temp->_Balance_factor = 0;
                Sub_left_right_temp->_Balance_factor = 0;
            }
            else
            {
                parent_temp_Node->_Balance_factor = 0;
                Sub_left_temp->_Balance_factor = 0;
                Sub_left_right_temp->_Balance_factor = 0;
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
                Wang::stack<AVL_Node*> _stack_temp;
                //前序释放
                _stack_temp.push(_ROOT);
                while(!_stack_temp.empty())
                {
                    AVL_Node* temp = _stack_temp.top();
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
                _ROOT = nullptr;
            }
        }
        //测试函数
        void _Pre_order_traversal(AVL_Node* _ROOT_Temp )
        {
            //前序遍历，最外左子树全部压栈
            if(_ROOT_Temp == nullptr)
            {
                return;
            }
            AVL_Node* _Pre_order_traversal_test = _ROOT_Temp;
            Wang::stack<AVL_Node*> stack_Temp;
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
        void _Middle_order_traversal(AVL_Node* _ROOT_Temp)
        {
            //中序遍历函数
            Wang::stack<AVL_Node*> _staic_temp_;
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
            if(_ROOT == nullptr)
            {
                return temp;
            }
            else
            {
                AVL_Node* _Pre_order_traversal_test = _ROOT;
                Wang::stack<AVL_Node*> stack_Temp;
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
        AVL_Tree()
        {
            _ROOT = nullptr;
        }
        AVL_Tree(const AVL_Tree_Type_K& Key_temp,const AVL_Tree_Type_V& val_temp = AVL_Tree_Type_V(),
        Imitation_function_parameter_function_AVL_Tee com_temp = Imitation_function_parameter_function_AVL_Tee())
        :_ROOT(nullptr),com(com_temp)
        {
            _ROOT = new AVL_Node(Key_temp,val_temp);
        }
        AVL_Tree(const AVL_Tree_Synthetic_class& AVL_Tree_Pair_Temp,
        Imitation_function_parameter_function_AVL_Tee com_temp = Imitation_function_parameter_function_AVL_Tee())
        :_ROOT(nullptr),com(com_temp)
        {
            _ROOT = new AVL_Node(AVL_Tree_Pair_Temp.first,AVL_Tree_Pair_Temp.second);
        }
        AVL_Tree(const AVL_Tree& AVL_Tree_temp_)
        : _ROOT(nullptr), com(AVL_Tree_temp_.com)
    {
        if (AVL_Tree_temp_._ROOT == nullptr)
        {
            return;
        }
    
        Wang::stack<Wang::STL_Demand_class::pair<AVL_Node*, AVL_Node**>> _stack_temp;
        _stack_temp.push(Wang::STL_Demand_class::pair<AVL_Node*, AVL_Node**>(AVL_Tree_temp_._ROOT, &_ROOT));
    
        while (!_stack_temp.empty())
        {
            auto AVL_pair_temp = _stack_temp.top();
            _stack_temp.pop();
    
            // 创建新节点并复制数据
            AVL_Node* new_node = new AVL_Node(AVL_pair_temp.first->_data);
            new_node->_Balance_factor = AVL_pair_temp.first->_Balance_factor;
            *AVL_pair_temp.second = new_node; // 将新节点赋值给目标位置
    
            // 处理右子节点
            if (AVL_pair_temp.first->_right != nullptr)
            {
                _stack_temp.push(Wang::STL_Demand_class::pair<AVL_Node*, AVL_Node**>(
                    AVL_pair_temp.first->_right, &new_node->_right));
            }
    
            // 处理左子节点
            if (AVL_pair_temp.first->_left != nullptr)
            {
                _stack_temp.push(Wang::STL_Demand_class::pair<AVL_Node*, AVL_Node**>(
                    AVL_pair_temp.first->_left, &new_node->_left));
            }
    
            // 设置子节点的父指针
            if (new_node->_left != nullptr)
            {
                new_node->_left->_parent = new_node;
            }
            if (new_node->_right != nullptr)
            {
                new_node->_right->_parent = new_node;
            }
        }
    }
        ~AVL_Tree()
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
        void Pre_order_traversal()
        {
            _Pre_order_traversal(_ROOT);
        }
        void Middle_order_traversal()
        {
            _Middle_order_traversal(_ROOT);
        }
        bool push(const AVL_Tree_Type_K& Key_temp,const AVL_Tree_Type_V& val_temp = AVL_Tree_Type_V())
        {
            //插入
            if(_ROOT == nullptr)
            {
                _ROOT = new AVL_Node(Key_temp,val_temp);
                return true;
            }
            else
            {
                AVL_Node* _ROOT_temp = _ROOT;
                AVL_Node* _ROOT_temp_parent = nullptr;
                while(_ROOT_temp)
                {
                    _ROOT_temp_parent = _ROOT_temp;
                    if(!com(Key_temp,_ROOT_temp->_data.first) && !com(_ROOT_temp->_data.first,Key_temp))
                    {
                        return false;
                    }
                    else if(com(Key_temp,_ROOT_temp->_data.first))
                    {
                        _ROOT_temp = _ROOT_temp->_left;
                    }
                    else
                    {
                        _ROOT_temp = _ROOT_temp->_right;
                    }
                }
                _ROOT_temp = new AVL_Node(Key_temp,val_temp);
                if(com(Key_temp,_ROOT_temp_parent->_data.first))
                {
                    _ROOT_temp_parent->_left = _ROOT_temp;
                }
                else
                {
                    _ROOT_temp_parent->_right = _ROOT_temp;
                }
                _ROOT_temp->_parent = _ROOT_temp_parent;

                AVL_Node* _ROOT_temp_test = _ROOT_temp;
                AVL_Node* _ROOT_temp_test_parent = _ROOT_temp_parent;

                while(_ROOT_temp_test_parent)
                {
                    if(_ROOT_temp_test_parent->_left == _ROOT_temp_test)
                    {
                        _ROOT_temp_test_parent->_Balance_factor--;
                    }
                    else
                    {
                        _ROOT_temp_test_parent->_Balance_factor++;
                    }

                    if(_ROOT_temp_test_parent->_Balance_factor == 0)
                    {
                        break;
                    }
                    else if (_ROOT_temp_test_parent->_Balance_factor == 1 || _ROOT_temp_test_parent->_Balance_factor == -1)
                    {
                        _ROOT_temp_test = _ROOT_temp_test_parent;
                        _ROOT_temp_test_parent = _ROOT_temp_test_parent->_parent;
                    }
                    else if (_ROOT_temp_test_parent->_Balance_factor == 2 || _ROOT_temp_test_parent->_Balance_factor == -2)
                    {
                        if(_ROOT_temp_test_parent->_Balance_factor == 2)
                        {
                            if(_ROOT_temp_test->_Balance_factor == 1)
                            {
                                _left_revolve(_ROOT_temp_test_parent);
                            }
                            else
                            {
                                _right_left_revolve(_ROOT_temp_test_parent);
                            }
                        }
                        if(_ROOT_temp_test_parent->_Balance_factor == -2)
                        {
                            if(_ROOT_temp_test->_Balance_factor == -1)
                            {
                                _right_revolve(_ROOT_temp_test_parent);
                            }
                            else
                            {
                                _left_right_revolve(_ROOT_temp_test_parent);
                            }
                        }
                        _ROOT_temp_test = _ROOT_temp_test_parent;
                        _ROOT_temp_test_parent = _ROOT_temp_test_parent->_parent;
                    }
                }
            }
            return true;
        }
        bool push(const AVL_Tree_Synthetic_class& AVL_Tree_Pair_Temp)
        {
            //AVL树左子树比右子树高，则他俩的根节点的平衡因子为1，反之为-1，也就是说左加一，右减一，如果根节点为2和-2就要需要调整了
            if(_ROOT == nullptr)
            {
                _ROOT = new AVL_Node(AVL_Tree_Pair_Temp.first,AVL_Tree_Pair_Temp.second);
                return true;
            }
            else
            {
                AVL_Node* _ROOT_Temp = _ROOT;
                AVL_Node* _ROOT_Temp_parent = nullptr;
                while(_ROOT_Temp != nullptr)
                {
                    _ROOT_Temp_parent = _ROOT_Temp;
                    //找到first该在的节点
                    if(!com(AVL_Tree_Pair_Temp.first,_ROOT_Temp->_data.first) && !com(_ROOT_Temp->_data.first,AVL_Tree_Pair_Temp.first))
                    {
                        //不允许重复插入
                        return false;
                    } 
                    else if(com(AVL_Tree_Pair_Temp.first,_ROOT_Temp->_data.first))
                    {
                        _ROOT_Temp = _ROOT_Temp->_left;
                    }
                    else
                    {
                        _ROOT_Temp = _ROOT_Temp->_right;
                    }
                }
                _ROOT_Temp = new AVL_Node(AVL_Tree_Pair_Temp);
                if(com(AVL_Tree_Pair_Temp.first,_ROOT_Temp_parent->_data.first))
                {
                    _ROOT_Temp_parent->_left = _ROOT_Temp;
                    //三叉链表，注意父亲节点指向
                }
                else
                {
                    _ROOT_Temp_parent->_right = _ROOT_Temp;
                }
                _ROOT_Temp->_parent = _ROOT_Temp_parent;
                AVL_Node* _ROOT_Temp_test = _ROOT_Temp;
                AVL_Node* _ROOT_Temp_test_parent = _ROOT_Temp_parent;
                //更新平衡因子
                while(_ROOT_Temp_test_parent)
                {
                    //更新到根节点跳出
                    if(_ROOT_Temp_test == _ROOT_Temp_test_parent->_right)
                    {
                        _ROOT_Temp_test_parent->_Balance_factor++;
                    }
                    else
                    {
                        _ROOT_Temp_test_parent->_Balance_factor--;
                    }

                    if(_ROOT_Temp_test_parent->_Balance_factor == 0)
                    {
                        //平衡因子为0，无需平衡
                        break;
                    }
                    else if(_ROOT_Temp_test_parent->_Balance_factor == 1 || _ROOT_Temp_test_parent->_Balance_factor == -1)
                    {
                        _ROOT_Temp_test = _ROOT_Temp_test_parent;
                        _ROOT_Temp_test_parent = _ROOT_Temp_test_parent->_parent;
                        //向上更新，直到找到0或-2或2
                    }
                    else if(_ROOT_Temp_test_parent->_Balance_factor == 2 || _ROOT_Temp_test_parent->_Balance_factor == -2)
                    {
                        //平衡因子为2或者-2，需要平衡
                        if(_ROOT_Temp_test_parent->_Balance_factor == 2)
                        {
                            if(_ROOT_Temp_test->_Balance_factor == 1)
                            {
                                //L，说明_ROOT_Temp_test是_ROOT_Temp_test_parent的左子节点，线形
                                _left_revolve(_ROOT_Temp_test_parent);
                            }
                            else
                            {
                                //RL，证明_ROOT_Temp_test是_ROOT_Temp_test_parent的右子节点，在AVL树抽象图上就是折线型的
                                _right_left_revolve(_ROOT_Temp_test_parent);
                            }
                        }
                        else if (_ROOT_Temp_test_parent->_Balance_factor == -2)
                        {
                            if(_ROOT_Temp_test->_Balance_factor == -1)
                            {
                                //R，说明_ROOT_Temp_test是_ROOT_Temp_test_parent的右子节点，线形
                                _right_revolve(_ROOT_Temp_test_parent);
                            }
                            else
                            {
                                //LR，和上同理
                                _left_right_revolve(_ROOT_Temp_test_parent);
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
        AVL_Node* find(const AVL_Tree_Type_K& _data_temp)
        {
            AVL_Node* _ROOT_Temp = _ROOT;
            while(_ROOT_Temp != nullptr)
            {
                if(_ROOT_Temp->_data == _data_temp)
                {
                    break;
                }
                else if (com(_ROOT_Temp->_data,_data_temp))
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
        void pop(const AVL_Tree_Type_K& _data_Temp)
        {

        }
    };
    //pair类指针特化版本，析构函数
    //AVL树其余函数，拷贝构，，迭代器配置
}
int main()
{  
    // /*            string测试             */
    // {
    //     std::cout << " string 测试 " << std::endl << std::endl;
    //     Wang::string string_test1("hello");
    //     Wang::string string_test2("world");
        
    //     Wang::string string_test3 = string_test1 + string_test2;
    //     std::cout << "string_test3: " << string_test3 << std::endl;
    //     string_test3.push_back('!');
    //     const char* insert_str = "inserted";
    //     string_test3.nose_Insertion_substrings(insert_str);
    //     std::cout << "str3 after insertion: " << string_test3 << std::endl;

    //     size_t old_pos = strlen(insert_str);
    //     Wang::string string_test4 = string_test3.str_withdraw(old_pos);
    //     std::cout << "string_test4: " << string_test4 << std::endl;

    //     std::cout << string_test3.conversions_oldest() << std::endl;
    //     std::cout << string_test3.conversions_few() << std::endl;

    //     Wang::string string_test5 = string_test3.str_withdraw_extremity(5);
    //     std::cout << "string_test5: " << string_test5 << std::endl;

    //     Wang::string string_test6 = string_test3.str_withdraw_detail(5, 10);
    //     std::cout << "string_test6: " << string_test6 << std::endl;

    //     std::cout << "str3 size: " << string_test3.size() << std::endl;
    //     std::cout << "str3 capacity: " << string_test3.capacity() << std::endl;
    //     std::cout << "string_test3 after resize: " << string_test3.resize(21, '*') << std::endl;

    //     std::cout << "string_test3 after rollback: " << string_test3.rollback() << std::endl;

    //     std::cout << "string_test3 after rollback_limit: " << string_test3.rollback_limit(5, 10) << std::endl;

    //     string_test3.string_print();
    //     string_test3.string_print_reverse();

    //     for(auto i :string_test3)
    //     {
    //         std::cout << i << " ";
    //     }
    //     std::cout << std::endl;

    //     for(Wang::string::const_iterator i = string_test3.begin();i != string_test3.end();i++)
    //     {
    //         std::cout << *i << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // /*            vector测试             */
    // {
    //     std::cout << " vector 测试 " << std::endl << std::endl;
    //     Wang::vector<int> vector_test(5,1);
    //     for(auto i: vector_test)
    //     {
    //         std::cout << i << " ";
    //     }
    //     std::cout << std::endl;
    //     Wang::vector<int> vector_test1(vector_test);
    //     for(const  auto& i  : vector_test1 )
    //     {
    //         std::cout << i << " ";
    //     }
    //     std::cout << std::endl;
    //     Wang::vector<int> test2 = vector_test1;
    //     for(const auto i : test2)
    //     {
    //         std::cout << i << " ";
    //     }
    //     Wang::string s2 = "name";
    //     std::cout << std::endl;
    //     Wang::vector<Wang::string> name_test(10,s2);
    //     for(const auto& i : name_test )
    //     {
    //         std::cout << i << " ";
    //     }
    //     std::cout << std::endl;
    //     Wang::vector<Wang::string> name_test1 =name_test ;
    //     for(const auto& i : name_test1 )
    //     {
    //         std::cout << i << " ";
    //     }
    //     std::cout << std::endl;
    //     Wang::string s3 = "hello word!";
    //     name_test1.push_back(s3);
    //     for(const auto& i : name_test1 )
    //     {
    //         std::cout << i << " ";
    //     }
    //     std::cout << std::endl;

    //     name_test1.push_front(s3);
    //     for(const auto& i : name_test1 )
    //     {
    //         std::cout << i << " ";
    //     }
    //     std::cout << std::endl;

    //     name_test1+=name_test;
    //     for(const auto& i : name_test1 )
    //     {
    //         std::cout << i << " ";
    //     }
    //     std::cout << std::endl;

    //     std::cout << name_test1 << std::endl;
    //     std::cout << name_test1.pop_back() << std::endl;
    // }


    // /*            list测试             */
    // {
    //     std::cout << " list 测试 " << std::endl << std::endl;
    //     Wang::list<int> list_test1;
    //     for(size_t i = 1; i < 10; i++)
    //     {
    //         list_test1.push_back(i);
    //     }
    //     Wang::list<int>::const_iterator it =list_test1.cbegin();
    //     while(it != list_test1.cend())
    //     {
    //         std::cout << *it  << " ";
    //         it++;
    //     }
    //     std::cout << std::endl;
    //     Wang::list<int>::reverse_const_iterator i = list_test1.rcbegin();
    //     while(i != list_test1.rcend())
    //     {
    //         std::cout << *i << " ";
    //         i++;
    //     }
    //     std::cout <<std::endl;

    //     list_test1.pop_back(); 
    //     Wang::list<int>::const_iterator j =list_test1.cbegin();
    //     while(j != list_test1.cend())
    //     {
    //         std::cout << *j  << " ";
    //         j++;
    //     }
    //     std::cout << std::endl;
    //     std::cout << list_test1.size() << std::endl;

    //     Wang::list<int> list_test2 = list_test1;
    //     Wang::list<int>::const_iterator p =list_test2.cbegin();
    //     while(p != list_test2.cend())
    //     {
    //         std::cout << *p  << " ";
    //         p++;
    //     }
    //     std::cout << std::endl;
    //     std::cout << list_test2.size() << std::endl;

    //     Wang::list<int> list_test3 = list_test2 + list_test1;
    //     Wang::list<int>::const_iterator k =list_test3.cbegin();
    //     while(k != list_test3.cend())
    //     {
    //         std::cout << *k  << " ";
    //         k++;
    //     }
    //     std::cout << std::endl;
    //     std::cout << list_test3.size() << std::endl;

    //     Wang::list<int> list_test4 = list_test3 + list_test1;
    //     Wang::list<int>::const_iterator kp =list_test4.cbegin();
    //     while(kp != list_test4.cend())
    //     {
    //         std::cout << *kp  << " ";
    //         kp++;
    //     }
    //     std::cout << std::endl;
    //     std::cout << list_test4.size() << std::endl;
    //     std::cout << list_test4 << std::endl;
    // }

    // /*            staic测试             */
    // {
    //     std::cout << " staic 测试 " << std::endl << std::endl;
    //     Wang::string staic_test_str1 = "hello";
    //     Wang::string staic_test_str2 = "word";
    //     Wang::string staic_test_str3 = "  ";
    //     Wang::stack<Wang::string> staic_test1;

    //     staic_test1.push(staic_test_str1);
    //     staic_test1.push(staic_test_str3);
    //     staic_test1.push(staic_test_str2);

    //     std::cout << staic_test1.top() << std::endl;
    //     staic_test1.pop();
    //     std::cout << staic_test1.top() << std::endl;
    //     staic_test1.pop();
    //     std::cout << staic_test1.top() << std::endl;
    //     staic_test1.pop();
    // }

    // /*            queue测试             */
    // {
    //     std::cout << " queue 测试 " << std::endl << std::endl;
    //     Wang::string queue_test_str1 = "hello";
    //     Wang::string queue_test_str2 = "word";
    //     Wang::string queue_test_str3 = "  ";
    //     Wang::queue<Wang::string,Wang::list<Wang::string>> queue_test1;

    //     queue_test1.push(queue_test_str1);
    //     queue_test1.push(queue_test_str3);
    //     queue_test1.push(queue_test_str2);

    //     std::cout << queue_test1.front() << std::endl;
    //     std::cout << queue_test1.back()  << std::endl;

    //     std::cout << queue_test1.front() << " ";
    //     queue_test1.pop();
    //     std::cout << queue_test1.front() << " ";
    //     queue_test1.pop();
    //     std::cout << queue_test1.front() << " ";
    //     queue_test1.pop();
    // }

    // /*            priority_queue测试             */
    // {
    //     time_t num1 = clock();
    //     std::cout << " priority_queue 测试 " << std::endl << std::endl;
    //     Wang::priority_queue<int> priority_queue_test;
    //     for(int i = 0; i < 10000 ; i++)
    //     {
    //         priority_queue_test.push(i);
    //     }

    //     std::cout << priority_queue_test.size() << std::endl;

    //     for(size_t i = 0; i < 10000; i++)
    //     {
    //         std::cout << priority_queue_test.top() << " ";
    //         priority_queue_test.pop();
    //     }
    //     std::cout << std::endl;
    //     time_t num2 = clock();
    //     std::cout << num2-num1 << std::endl;
    // }

    // /*            BS_Tree 测试             */
    // {
    //     time_t Binary_search_tree_num1 = clock();
    //     Wang::BS_Tree<int,Wang::STL_Imitation_functions::greater<int>> Binary_search_tree_test;
    //     for(size_t i = 100; i > 0; i--)
    //     {
    //         //相对来说这算是有序插入导致二叉树相乘时间复杂度为O(N)的链表
    //         Binary_search_tree_test.push(i);
    //     }
    //     time_t Binary_search_tree_num2 = clock();

    //     time_t Binary_search_tree_num3 = clock();
    //     std::cout << Binary_search_tree_test.find(58) << std::endl;
    //     time_t Binary_search_tree_num4 = clock();
    //     // Binary_search_tree_test.Middle_order_traversal();
    //     std::cout << "退化链表插入时间" << Binary_search_tree_num2-Binary_search_tree_num1 << std::endl;
    //     std::cout << "退化链表查找时间" << Binary_search_tree_num4-Binary_search_tree_num3 << std::endl;
    //     std::cout << std::endl << std::endl;
    // }

    // {
    //     Wang::BS_Tree<int, Wang::STL_Imitation_functions::greater<int>> bst;
    //     bst.push(5);
    //     bst.push(4);
    //     bst.push(3);
    //     bst.push(2);
    //     bst.push(1);
    //     bst.Middle_order_traversal(); 
    //     std::cout << std::endl << std::endl;
    // }

    // {
    //     const size_t Binary_search_tree_arraySize = 10;
    //     Wang::vector<int> Binary_search_tree_array(Binary_search_tree_arraySize);
    //     for (size_t i = 0; i < Binary_search_tree_arraySize; ++i) 
    //     {
    //         Binary_search_tree_array[i] = i;
    //     }

    //     // 创建随机数引擎和分布
    //     std::random_device rd;
    //     std::mt19937 g(rd());
    //     std::shuffle(Binary_search_tree_array.begin(), Binary_search_tree_array.end(), g);
    //     //输出打乱后的数组
    //     // for(auto& i : Binary_search_tree_array)
    //     // {
    //     //     std::cout << i << " ";
    //     // }

    //     //打乱数组元素顺序
    //     size_t size = 0;
    //     time_t Binary_search_tree_num1 = clock();
    //     Wang::BS_Tree<int,Wang::STL_Imitation_functions::greater<int>> Binary_search_tree_test;
    //     for(const auto& Binary_search_tree_for_test: Binary_search_tree_array)
    //     {
    //         if(Binary_search_tree_test.push(Binary_search_tree_for_test))
    //         {
    //             size++;
    //         }
    //     }
    //     time_t Binary_search_tree_num2 = clock();

    //     const int Binary_search_tree_find = Binary_search_tree_array[Binary_search_tree_arraySize/2];

    //     time_t Binary_search_tree_num3 = clock();
    //     Binary_search_tree_test.find(Binary_search_tree_find);
    //     time_t Binary_search_tree_num4 = clock();
    //     // Binary_search_tree_test.Middle_order_traversal();
    //     std::cout << "插入个数" << size << std::endl;
    //     std::cout << "插入时间" << Binary_search_tree_num2-Binary_search_tree_num1 << std::endl;
    //     std::cout << "查找时间" << Binary_search_tree_num4-Binary_search_tree_num3 << std::endl;
    //     /*              查找数据时间不稳定时间复杂度是O(logN)        */
    //     std::cout << std::endl << std::endl;
    // }

    // {
    //     const size_t Binary_search_tree_arraySize = 20;
    //     Wang::vector<int> Binary_search_tree_array(Binary_search_tree_arraySize);
    //     for (size_t i = 0; i < Binary_search_tree_arraySize; ++i) 
    //     {
    //         Binary_search_tree_array[i] = i;
    //     }

    //     // 创建随机数引擎和分布
    //     std::random_device rd;
    //     std::mt19937 g(rd());
    //     std::shuffle(Binary_search_tree_array.begin(), Binary_search_tree_array.end(), g);
    //     //输出打乱后的数组
    //     // for(auto& i : Binary_search_tree_array)
    //     // {
    //     //     std::cout << i << " ";
    //     // }

    //     //打乱数组元素顺序
    //     size_t size = 0;
    //     time_t Binary_search_tree_num1 = clock();
    //     Wang::BS_Tree<int,Wang::STL_Imitation_functions::greater<int>> Binary_search_tree_test;
    //     for(const auto& Binary_search_tree_for_test: Binary_search_tree_array)
    //     {
    //         if(Binary_search_tree_test.push(Binary_search_tree_for_test))
    //         {
    //             size++;
    //             std::cout << size << " ";
    //         }
    //     }
    //     std::cout << std::endl;
    //     time_t Binary_search_tree_num2 = clock();
    //     Wang::BS_Tree<int,Wang::STL_Imitation_functions::greater<int>> Binary_search_tree_test1 = Binary_search_tree_test;
    //     time_t Binary_search_tree_num3 = clock();
    //     std::cout << "拷贝构造没问题 " << std::endl;

    //     Binary_search_tree_test.pop(Binary_search_tree_array[2]);
    //     std::cout << "pop(1)函数没问题 " << std::endl;
    //     Binary_search_tree_test.pop(Binary_search_tree_array[0]);
    //     std::cout << "pop(2)函数没问题 " << std::endl;
    //     Binary_search_tree_test.pop(Binary_search_tree_array[1]);
    //     std::cout << "pop(3)函数没问题 " << std::endl;
    //     Binary_search_tree_test.pop(Binary_search_tree_array[3]);
    //     std::cout << "pop(4)函数没问题 " << std::endl;


    //     Binary_search_tree_test.Middle_order_traversal();
    //     std::cout << std::endl;
    //     Binary_search_tree_test1.Middle_order_traversal();

    //     std::cout << "前序遍历 "<< std::endl;
    //     Binary_search_tree_test.Pre_order_traversal();
    //     std::cout << std::endl;
    //     Binary_search_tree_test1.Pre_order_traversal();
    //     std::cout << std::endl;
    //     std::cout << "插入个数" << size << std::endl;
    //     std::cout << "插入时间" << Binary_search_tree_num2-Binary_search_tree_num1 << std::endl;
    //     std::cout << "拷贝时间" << Binary_search_tree_num3-Binary_search_tree_num2 << std::endl;
    // }

    // {
    //     Wang::string str1 = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    //     std::cout << str1 << std::endl;
    //     Wang::vector <Wang::string> vector_str = {"西瓜","樱桃","苹果","西瓜","樱桃","苹果","樱桃","西瓜","樱桃","西瓜","樱桃","苹果","樱桃","苹果","樱桃"};
    //     Wang::BS_Tree< Wang::string > BST_temp;
    //     size_t _BST_size = vector_str.size();
    //     for(size_t i = 0 ; i < _BST_size;i++)
    //     {
    //         if(BST_temp.push(vector_str[i]))
    //         {
    //             std::cout << "插入成功" << std::endl;
    //         }
    //         else
    //         {
    //             //当前未实现累加功能
    //             std::cout << "插入失败" << std::endl;
    //         }
    //     }
    //     BST_temp.Middle_order_traversal();
    //     std::cout << BST_temp.size() << std::endl;
    // }
    // /*            pair类 测试             */
    // {
    //     const int i = 31; const int j = 28;
    //     Wang::STL_Demand_class::pair<int,int> pair_test =Wang::STL_Demand_class::make_pair(i,j);
    //     std::cout << pair_test << std::endl;
    // }
    /*            AVL_Tree 测试             */
    // {
    //     Wang::AVL_Tree<Wang::STL_Demand_class::pair<int,int>,int> AVL_Tree_test_pair(Wang::STL_Demand_class::pair(9,0), 10);
    //     Wang::STL_Demand_class::pair<Wang::STL_Demand_class::pair<int,int>,int> pair_test_ (Wang::STL_Demand_class::pair(9,0), 10);
    //     Wang::AVL_Tree<Wang::STL_Demand_class::pair<int,int>,int> AVL_Tree_test(pair_test_);
    //     //两个构造函数，根据传值调用来查看调用情况
    //     Wang::AVL_Tree<Wang::string,int> AVL_Tree_test2;
    //     AVL_Tree_test2.~AVL_Tree();
    // }
    // {
    //     Wang::AVL_Tree<int,int> AVL_Tree_test_pair;
    //     Wang::vector<Wang::STL_Demand_class::pair<int,int>> AVL_Tree_array_pair = {{22,0},{16,0},{13,0},{15,0},{11,0},{12,0},{14,0},{10,0},{2,0},{10,0}};
    //     for(auto& i : AVL_Tree_array_pair)
    //     {
    //         AVL_Tree_test_pair.push(i);
    //     }
    //     std::cout << "前序遍历 "<< std::endl;
    //     AVL_Tree_test_pair.Pre_order_traversal();
    //     std::cout << std::endl;
    //     std::cout << "中序遍历 "<< std::endl;
    //     AVL_Tree_test_pair.Middle_order_traversal();
    //     std::cout << std::endl;
    // }
    {
        Wang::AVL_Tree<int,int> AVL_Tree_test_pair;
        Wang::vector<Wang::STL_Demand_class::pair<int,int>> AVL_Tree_array_pair = {{22,0},{16,0},{13,0},{15,0},{11,0},{12,0},{14,0},{10,0},{2,0},{10,0}};
        for(auto& i : AVL_Tree_array_pair)
        {
            AVL_Tree_test_pair.push(i);
        }
        std::cout << "前序遍历 "<< std::endl;
        AVL_Tree_test_pair.Pre_order_traversal();
        std::cout << std::endl;
        std::cout << "中序遍历 "<< std::endl;
        AVL_Tree_test_pair.Middle_order_traversal();
        std::cout << std::endl; 
        Wang::AVL_Tree<int,int>AVL_Tree_test_pair1(AVL_Tree_test_pair);
        std::cout << "前序遍历 "<< std::endl;
        AVL_Tree_test_pair1.Pre_order_traversal();
        std::cout << std::endl;
        std::cout << "中序遍历 "<< std::endl;
        AVL_Tree_test_pair1.Middle_order_traversal();
        std::cout << std::endl; 
        Wang::BS_Tree<char> BS_Tr;
        Wang::string str1 = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        for(auto& i :str1)
        {
            BS_Tr.push(i);
        }
        BS_Tr.Middle_order_traversal();
        std::cout << std::endl;
        Wang::BS_Tree<char> BS_TREE(BS_Tr);
        BS_TREE.Middle_order_traversal();
        std::cout << std::endl;
    }
    // {
    //     //性能测试
    //     /*                   pair 类型                */
    //     Wang::AVL_Tree<size_t,int> AVL_Tree_test_pair;
    //     Wang::vector<Wang::STL_Demand_class::pair<size_t,int>> AVL_Tree_array_pair;
    //     size_t size = 100000;
    //     for(size_t i = 0; i < size; i++)
    //     {
    //         AVL_Tree_array_pair.push_back(Wang::STL_Demand_class::pair<size_t,int>(i,0));
    //     }
    //     time_t AVL_Tree_num1 = clock();
    //     for(auto& i : AVL_Tree_array_pair)
    //     {
    //         AVL_Tree_test_pair.push(i);
    //     }
    //     time_t AVL_Tree_num2 = clock();
    //     std::cout << "插入个数:" << AVL_Tree_test_pair.size()  << " " << " 插入时间:" << AVL_Tree_num2 - AVL_Tree_num1 << std::endl;

    //     /*                  非pair 类型               */
    //     Wang::AVL_Tree<size_t,int> AVL_Tree_test;
    //     Wang::vector<size_t> AVL_Tree_array;
    //     for(size_t j = 0; j < size ; j++)
    //     {
    //         AVL_Tree_array.push_back(j);
    //     }
    //     time_t AVL_Tree_num3 = clock();
    //     for(auto& j : AVL_Tree_array)
    //     {
    //         AVL_Tree_test.push(j);
    //     }
    //     time_t AVL_Tree_num4 = clock();
    //     std::cout << "插入个数:" << AVL_Tree_test.size()  << " " << " 插入时间:" << AVL_Tree_num4 - AVL_Tree_num3 << std::endl;
    // }
    return 0;
}