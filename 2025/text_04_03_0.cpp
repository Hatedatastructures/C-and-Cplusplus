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
            // static const size_t nops = -1;
            iterator begin() 
            {
                return _data;
            }
            iterator end()
            {
                return _data + _size;
            }
            size_t size()const
            {
                return _size;
            }
            size_t capacity()const
            {
                return _capacity;
            }
            char* c_str()const
            {
                return _data;
            }
            string(const char* data_str = "")
            :_size(strlen(data_str)),_capacity(_size)
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
            string& operator=(const string &data_str)
            {
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
            void operator+=(const string& data_str)
            {
                size_t len = _size + data_str._size;
                if(Automatic_scaling(len) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return;
                }
                strcpy(_data + _size,data_str._data);
                _size = _size + data_str._size;
                _data[_size] = '\0';
            }
            char& operator[](const size_t& ergodic_value)
            {
                return _data[ergodic_value];
            }
            const char& operator[](const size_t& ergodic_value)const
            {
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
            void conversions_oldest()
            {
                //字符串转大写
                for(size_t i = 0; i < _size; ++i)
                {
                    if(_data[i] >= 'a' && _data[i] <= 'z')
                    {
                        _data[i] -= 32;
                    }
                }
            }
            void conversions_few()
            {
                //字符串转小写
                for(size_t i = 0; i < _size; ++i)
                {
                    if(_data[i] >= 'A' && _data[i] <= 'Z')
                    {
                        _data[i] += 32;
                    }
                }
            }
            // size_t str_substring_kmp(const char*& c_str_substring)
            // {
            //     //查找子串
            // }
            void nose_Insertion_substrings(const char*& c_str_substring)
            {
                //前部插入子串
                size_t len = strlen(c_str_substring);
                size_t new_nose_insert_substrings = _size + len;
                if(Automatic_scaling(new_nose_insert_substrings) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return;
                }
                char* _c_nose_insert_substrings_temp = new char[new_nose_insert_substrings + 1];
                //临时变量
                strcpy(_c_nose_insert_substrings_temp,_data);
                strcpy(_data , c_str_substring);
                strcpy(_data + len , _c_nose_insert_substrings_temp);
                _size = new_nose_insert_substrings;
                _data[_size] = '\0';
                delete [] _c_nose_insert_substrings_temp;
            }
            void interlocutory_Insertion_substrings(const char*& c_str_substring,size_t& oid_pos)
            {
                //中间位置插入子串
                size_t len = strlen(c_str_substring);
                size_t new_interlocutory_insert_substrings = _size + len;
                if(Automatic_scaling(new_interlocutory_insert_substrings) != true)
                {
                    std::cout << "开辟内存失败！" << std::endl;
                    return;
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
            }
            string str_withdraw(size_t& old_pos)
            {
                //提取字串到'\0'
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
            string str_withdraw_extremity(size_t& old_begin)
            {
                //提取字串到末尾
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
            string str_withdraw_detail(size_t& old_begin ,size_t& old_end)
            {
                //提取字串到指定位置
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
            bool Automatic_scaling(size_t& temporary_variable)
            {
                //检查string空间大小，来分配内存
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
            void push_back(const char& c_temp_str)
            {
                if(_size == _capacity)
                {
                    size_t newcapacity = _capacity == 0 ? 2 :_capacity*2;
                    if(Automatic_scaling(newcapacity) != true)
                    {
                        std::cout << "开辟内存失败！" << std::endl;
                        return;
                    }
                }
                _data[_size] = c_temp_str;
                ++_size;
                _data[_size] = '\0';
            }
            void push_back(const string& cpp_temp_str)
            {
                size_t len = _size + cpp_temp_str._size;
                if(len > _capacity)
                {
                    size_t new_capacity = len;
                    if(Automatic_scaling(new_capacity) != true)
                    {
                        std::cout << "开辟内存失败！" << std::endl;
                        return;
                    }
                }
                strcpy(_data+_size,cpp_temp_str._data);
                _size =_size + cpp_temp_str._size;
                _data[_size] = '\0';
            }
            void push_back(const char*& c_temp_str)
            {
                size_t len = strlen( c_temp_str );
                size_t new_capacity = len + _size ;
                if(new_capacity >_capacity)
                {
                    if(Automatic_scaling( new_capacity) != true)
                    {
                        std::cout << "开辟内存失败！" << std::endl;
                        return;
                    }
                }
                strcpy(_data+_size , c_temp_str);
                _size = _size + len;
                _data[_size] = '\0';
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