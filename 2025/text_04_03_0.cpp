#include <iostream>
#include <cstring>
//模拟string
namespace string_wanz
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
            :_data(nullptr),_size(0),_capacity(0)
            {
                size_t capacity = data_str._capacity;
                _data = new char[capacity + 1];
                strcpy(_data,data_str._data);
                _size = data_str._size;
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
                    _size = data_str._size;
                    _data[_size] = '\0';
                }
                return *this;
            }
    };
    std::ostream& operator<<(std::ostream& string_ostream,string &data_str) 
    {
        //当前没实现【】访问.可以用迭代器
        for(string_wanz::string::iterator originate = data_str.begin();originate != data_str.end();originate++)
        {
            string_ostream << *originate;
        }
        return string_ostream;
    }
}

int main()
{
    string_wanz::string s1;
    string_wanz::string s2("hello");
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    return 0;
}