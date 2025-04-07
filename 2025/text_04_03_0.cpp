#include <iostream>
#include <cstring>
//模拟string
namespace wz
{
    class string
    {
        private:
            char *_data;
            size_t _size;
            size_t _capacity;
        public:
            //创建迭代器
            typedef char* iterator;
            //限定字符串最大值
            static const size_t nops = -1;
            iterator begin() 
            {
                //返回第一个元素的地址
                return _data;
            }
            iterator end()
            {
                //返回最后一个元素的下一个位置
                return _data + _size;
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
            string(const char* data_str = "")
            :_size(data_str == nullptr ? 0 : strlen(data_str)),_capacity(_size)
            {
                //传进来的字符串是常量字符串，不能直接修改，需要拷贝一份，并且常量字符串在数据段(常量区)浅拷贝会导致程序崩溃
                if(data_str != nullptr)
                {
                    _data = new char[_capacity + 1];
                    strcpy(_data,data_str);
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
                strcpy(_data,data_str._data);
                _data[_size] = '\0';
            }
            ~string()
            {
                delete [] _data;
                _capacity = _size = 0;
            }
            friend std::ostream& operator<<(std::ostream& string_ostream,string &data_str);
            friend std::iostream& operator>>(std::iostream& string_istream,string &data_str);
            string& operator=(const string &data_str)
            {
                //防止无意义拷贝
                if(this != &data_str)
                {
                    delete [] _data;
                    size_t capacity = data_str._capacity;
                    _data = new char[capacity + 1];
                    strcpy(_data,data_str._data);
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
                strcpy(_data + _size,data_str._data);
                _size = _size + data_str._size;
                _data[_size] = '\0';
                return *this;
            }
            char& operator[](const size_t& ergodic_value)
            {
                //引用就是出了函数作用域还能用其他的变量名访问，不需要拷贝就能访问，所以可以直接返回引用减少内存开销
                //在函数创建的变量出了函数作用域就不能访问了，这下才要返回拷贝值，如果返回引用就会未定义
                if(ergodic_value >= _size)
                {
                    //如果越界了就返回第一个元素的引用
                    return _data[0];
                }
                return _data[ergodic_value]; //返回第ergodic_value个元素的引用
                //就像_data在外面就能访问它以及它的成员，所以这种就可以理解成出了函数作用域还在，进函数之前也能访问的就是引用
            }
            const char& operator[](const size_t& ergodic_value)const
            {
                if(ergodic_value >= _size)
                {
                    //如果越界了就返回第一个元素的引用
                    return _data[0];
                }
                return _data[ergodic_value]; 
            }
            string operator+(const string& cpp_str_)
            {
                string _str_temp;
                size_t _str_temp_len = _size + cpp_str_._size;
                if(_str_temp.Automatic_scaling(_str_temp_len) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return _str_temp;
                }
                strcpy(_str_temp._data , _data);
                strcpy(_str_temp._data + _size , cpp_str_._data);
                _str_temp._size = _size + cpp_str_._size;
                _str_temp._data[_str_temp._size] = '\0';
                return _str_temp;
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
                char* _c_nose_insert_substrings_temp = new char[new_nose_insert_substrings + 1];
                //临时变量
                strcpy(_c_nose_insert_substrings_temp,_data);
                strcpy(_data , c_str_substring);
                strcpy(_data + len , _c_nose_insert_substrings_temp);
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
                strcpy(_c_interlocutory_insert_substrings_temp,_data);
                //从oid_pos开始插入
                strcpy(_data + oid_pos, c_str_substring);
                strcpy(_data + oid_pos + len , _c_interlocutory_insert_substrings_temp + oid_pos);
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
                    return *this;
                }
                string _str_withdraw_temp;
                size_t _str_withdraw_temp_len = _size - old_pos;
                if(_str_withdraw_temp.Automatic_scaling(_str_withdraw_temp_len) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return _str_withdraw_temp;
                }
                strcpy(_str_withdraw_temp._data , _data + old_pos);
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
                    return *this;
                }
                string _str_withdraw_extremity_temp;
                size_t _str_withdraw_extremity_temp_len = _size - old_begin;
                if(_str_withdraw_extremity_temp.Automatic_scaling(_str_withdraw_extremity_temp_len) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return _str_withdraw_extremity_temp;
                }
                strcpy(_str_withdraw_extremity_temp._data , _data + old_begin);
                _str_withdraw_extremity_temp._size = _str_withdraw_extremity_temp_len;
                _str_withdraw_extremity_temp._data[_str_withdraw_extremity_temp._size] = '\0';
                return _str_withdraw_extremity_temp;
            }
            string str_withdraw_detail(const size_t& old_begin ,const size_t& old_end)
            {
                //提取字串到指定位置
                if(old_begin > _size || old_end > _size)
                {
                    std::cout << "提取位置越界！" << std::endl;
                    return *this;
                }
                string _str_withdraw_detail_temp;
                size_t _str_withdraw_detail_temp_len = old_end - old_begin;
                if(_str_withdraw_detail_temp.Automatic_scaling(_str_withdraw_detail_temp_len) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return _str_withdraw_detail_temp;
                }
                strcpy(_str_withdraw_detail_temp._data , _data + old_begin);
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
                    strcpy(temporary_,_data);
                    delete[] _data;
                    _data = temporary_;
                    _capacity = temporary_variable;
                    return true;
                }
                else
                {
                    return false;
                }
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
                strcpy(_data+_size,cpp_temp_str._data);
                _size =_size + cpp_temp_str._size;
                _data[_size] = '\0';
                return *this;
            }
            string& push_back(const char*& c_temp_str)
            {
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
                strcpy(_data+_size , c_temp_str);
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
            string& swap_s(string& data_str)
            {
                std::swap(_data,data_str._data);
                std::swap(_size,data_str._size);
                std::swap(_capacity,data_str._capacity);
                return *this;
            }
    };
    // class string_C_return
    // {
    //     public:
    //         typedef char Temporary_needs;

        
    // };
    std::ostream& operator<<(std::ostream& string_ostream,string &data_str) 
    {
        //当前没实现【】访问.可以用迭代器
        for(wz::string::iterator originate = data_str.begin();originate != data_str.end();originate++)
        {
            string_ostream << *originate;
        }
        return string_ostream;
    }
    std::istream& operator>>(std::istream& string_istream,string &data_str)
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
}

int main()
{
    wz::string str1("hello");
    wz::string str2("world");
    wz::string str3 = str1 + str2;
    std::cout << "str3: " << str3 << std::endl;
    str3.push_back('!');
    const char* insert_str = "inserted";
    str3.nose_Insertion_substrings(insert_str);
    std::cout << "str3 after insertion: " << str3 << std::endl;
    size_t old_pos = strlen(insert_str);
    wz::string str4 = str3.str_withdraw(old_pos);
    std::cout << "str4: " << str4 << std::endl;
    return 0;
}