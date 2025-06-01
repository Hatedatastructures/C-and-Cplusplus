//本文件都是自己造的轮子
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
//优化每个容器插入函数右值引用，调整每个容器扩容逻辑，减少深拷贝，尽量用移动拷贝，对于开辟空间和错误处理，使用异常处理，对于简单函数使用lambda表达式
//添加每个容器完美转发，减少开销,整理每个容器,哈希表扩容导致size指针问题
namespace Ex  
{
    class customize_exception :public std::exception
    {
    private:
        const char* message;
        const char* function_name;
        size_t line_number;
    public:
        customize_exception(const char* _Message,const char* _FunctionName,const size_t& _LineNumber) noexcept 
        {
            message = _Message;
            function_name = _FunctionName;
            line_number = _LineNumber;
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
namespace MyTemplate
{
    namespace ImitationFunctions
    {
        //仿函数命名空间
        template<typename imitation_functions_less>
        class less
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
        class HashImitationFunctions
        {
        public:
            size_t operator()(const int StrData) noexcept                               {       return StrData;                }
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
            
  
            // size_t operator()(const MY_Template::StringContainer::string& data_string)
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
    namespace Algorithm
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
        source_sequence_find Find(source_sequence_find begin,source_sequence_find end,const target_sequence_find& value) noexcept
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
        void Swap(swap_data_type& a,swap_data_type& b) noexcept
        {
            swap_data_type temp = a;
            a = b;
            b = temp;
        }
        namespace HashAlgorithm
        {
            template <typename hash_algorithm_type ,typename hash_if = MyTemplate::ImitationFunctions::HashImitationFunctions>
            class HashFunction
            {
            public:
                hash_if HashImitationFunctionsObject;
                size_t Hash_SDBMHash(const hash_algorithm_type& DataHash) noexcept
                {
                    size_t return_value = HashImitationFunctionsObject(DataHash);
                    return_value = 65599 * return_value;
                    return return_value;
                }
                size_t Hash_BKDRHash(const hash_algorithm_type& DataHash) noexcept
                {
                    size_t return_value = HashImitationFunctionsObject(DataHash);
                    return_value = 131 * return_value;
                    return return_value;
                }
                size_t Hash_DJBHash(const hash_algorithm_type& DataHash) noexcept
                {
                    size_t return_value = HashImitationFunctionsObject(DataHash);
                    return_value = 33 * return_value;
                    return return_value;
                }
                size_t Hash_APHash(const hash_algorithm_type& DataHash) noexcept
                {
                    size_t return_value = HashImitationFunctionsObject(DataHash);
                    return_value = return_value * 1031;
                    return return_value;
                }
                size_t Hash_PJWHash(const hash_algorithm_type& DataHash) noexcept
                {
                    size_t return_value = HashImitationFunctionsObject(DataHash);
                    return_value = (return_value << 2) + return_value;
                    return return_value;
                }
            };
        }
    }
    namespace Practicality
    {
        template<typename pair_data_type_example_t,typename pair_data_type_example_k>
        class Pair
        {
            using T = pair_data_type_example_t;
            using K = pair_data_type_example_k;
            //处理指针类型
        public:
            //链接两个相同或不同的类型为一个类型，方便使用
            T first;
            K second;
            Pair() noexcept 
            {
                first  = T();
                second = K();
            } 

            Pair(const T& _First,const K& _Second) noexcept
            {
                first  = _First;
                second = _Second;
            }
            Pair(const Pair& Other) noexcept
            {
                first  = Other.first;
                second = Other.second;
            }

            Pair(T&& _First,K&& _Second) noexcept
            {
                first  = std::move(_First);
                second = std::move(_Second);
            }
            Pair(Pair&& Other) noexcept
            {
                first  = std::move(Other.first);
                second = std::move(Other.second);
            }
            Pair& operator=(const Pair& Other) noexcept
            {
                if(this != &Other)
                {
                    first = Other.first;
                    second = Other.second;
                }
                return *this;
            }
            Pair& operator=(Pair&& Other) noexcept
            {
                if(this != &Other)
                {
                    first = std::move(Other.first);
                    second = std::move(Other.second);
                }
                return *this;
            }
            bool operator==(const Pair& Other) const  noexcept  
            {       
                return (this == &Other) ? true : (first == Other.first && second == Other.second);  
            }
            bool operator==(const Pair& Other) noexcept         
            {       
                return this == &Other ? true : (first == Other.first && second == Other.second);    
            }
            bool operator!=(const Pair& Other) noexcept         
            {       
                return !(*this == Other);   
            }
            Pair* operator->() noexcept                         {       return this;        }
            const Pair* operator->()const  noexcept             {       return this;        }
            template<typename pair_ostream_t,typename pair_ostream_k>
            friend std::ostream& operator<<(std::ostream& os,const Pair<pair_ostream_t,pair_ostream_k>& p);
        };
        template<typename pair_ostream_t,typename pair_ostream_k>
        std::ostream& operator<<(std::ostream& os,const Pair<pair_ostream_t,pair_ostream_k>& p)
        {
            os << "(" << p.first << ":" << p.second << ")";
            return os;
        }
        /*                               类分隔                                   */
        template<typename make_pair_t,typename make_pair_k>
        Pair<make_pair_t,make_pair_k> make_pair (const make_pair_t& _First,const make_pair_k& _Second)
        {
            return Pair<make_pair_t,make_pair_k>(_First,_Second);
        }
    }

    /*############################     string容器     ############################*/
    namespace StringContainer
    {
        class String
        {
        private:
            char* _data;
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

            reverse_iterator rbegin() noexcept              {   return Empty() ? reverse_iterator(end()) : reverse_iterator(end() - 1);  }

            reverse_iterator rend() noexcept                {   return Empty() ? reverse_iterator(begin()) : reverse_iterator(begin() - 1);  }

            const_reverse_iterator crbegin()const noexcept  {   return const_reverse_iterator(cend()- 1);   }

            const_reverse_iterator crend()const noexcept    {   return const_reverse_iterator(cbegin()- 1); }

            bool Empty() noexcept                           {   return _size == 0;  }

            size_t size()const noexcept                     {   return _size;       }

            size_t capacity()const noexcept                 {   return _capacity;   }

            char* C_Str()const noexcept                     {   return _data;       } //返回C风格字符串

            char Back() noexcept                            {   return _size > 0 ? _data[_size - 1] : '\0';    }

            char Front() noexcept                           {   return _data[0];    }//返回尾字符

            String(const char* StrData = " ")
            :_size(StrData == nullptr ? 0 : strlen(StrData)),_capacity(_size)
            {
                //传进来的字符串是常量字符串，不能直接修改，需要拷贝一份，并且常量字符串在数据段(常量区)浅拷贝会导致程序崩溃
                if(StrData != nullptr) 
                {
                    _data = new char[_capacity + 1];
                    std::strncpy(_data,StrData,std::strlen(StrData));
                    // strcpy(_data,StrData);
                    _data[_size] = '\0';
                }
                else
                {
                    _data = new char[1];
                    _data[0] = '\0';
                }
            }
            String(char*&& StrData) noexcept
            :_data(nullptr),_size(StrData == nullptr ? 0 : strlen(StrData)),_capacity(_size)
            {
                //移动构造函数，拿传入对象的变量初始化本地变量，对于涉及开辟内存的都要深拷贝
                if(StrData != nullptr)
                {
                    _data = StrData;
                    StrData = nullptr;
                }
                else
                {
                    _data = new char[1];
                    _data[0] = '\0';
                }
            }
            String(const String& StrData)
            :_data(nullptr),_size(StrData._size),_capacity(StrData._capacity)
            {
                //拷贝构造函数，拿传入对象的变量初始化本地变量，对于涉及开辟内存的都要深拷贝
                size_t capacity = StrData._capacity;
                _data = new char[capacity + 1];
                // algorithm::copy(_data,_data+capacity,StrData._data); const对象出错
                std::strcpy(_data, StrData._data);
            }
            String(String&& StrData) noexcept
            :_data(nullptr),_size(StrData._size),_capacity(StrData._capacity)
            {
                //移动构造函数，拿传入对象的变量初始化本地变量，对于涉及开辟内存的都要深拷贝
                MyTemplate::Algorithm::Swap(StrData._data,_data);
                ////////////////////////////////////////////////////////////////////////////////////////////问题：为什么move函数不行？
            }
            String(std::initializer_list<char> StrData)
            {
                //初始化列表构造函数
                _size = StrData.size();
                _capacity = _size;
                _data = new char[_capacity + 1];
                MyTemplate::Algorithm::copy(StrData.begin(), StrData.end(), _data);
                _data[_size] = '\0';
            }
            ~String() noexcept
            {
                delete [] _data;
                _data = nullptr;
                _capacity = _size = 0;
            }
            String& Uppercase() noexcept
            {
                //字符串转大写
                for(String::iterator StartPosition = _data; StartPosition != _data + _size; StartPosition++)
                {
                    if(*StartPosition >= 'a' && *StartPosition <= 'z')
                    {
                        *StartPosition -= 32;
                    }
                }
                return *this;
            }
            String& Lowercase() noexcept
            {
                //字符串转小写
                for(String::iterator StartPosition = _data; StartPosition != _data + _size; StartPosition++)
                {
                    if(*StartPosition >= 'A' && *StartPosition <= 'Z')
                    {
                        *StartPosition += 32;
                    }
                }
                return *this;
            }
            // size_t str_substring_kmp(const char*& Substring)
            // {
            //     //查找子串
            // }
            String& Prepend(const char*& Substring)
            {
                //前部插入子串
                size_t Len = strlen(Substring);
                size_t NewSize = _size + Len;
                AllocateResources(NewSize);
                char* TemporaryBuffers = new char[_capacity + 1];
                //临时变量
                memmove(TemporaryBuffers , _data , _size + 1);
                memmove(_data , Substring , Len);
                memmove(_data + Len , TemporaryBuffers , _size + 1);
                //比memcpy更安全，memcpy会覆盖原有数据，memmove会先拷贝到临时变量再拷贝到目标地址
                _size = NewSize;
                _data[_size] = '\0';
                delete [] TemporaryBuffers;
                return *this;
            }
            String& InsertSubstring(const char*& Substring,const size_t& StartPosition)
            {
                try
                {
                    //中间位置插入子串
                    if(StartPosition > _size)
                    {
                        throw Ex::customize_exception("传入参数位置越界","InsertSubstring",__LINE__);
                    }
                    size_t Len = strlen(Substring);
                    size_t NewSize = _size + Len;
                    AllocateResources(NewSize);
                    char* TemporaryBuffers = new char[NewSize + 1];
                    //临时变量
                    memmove(TemporaryBuffers, _data, _size + 1);
                    //从oid_pos开始插入
                    memmove(_data + StartPosition + Len, TemporaryBuffers + StartPosition, _size - StartPosition + 1);
                    memmove(_data + StartPosition, Substring, Len);
                    _size = NewSize;
                    _data[_size] = '\0';
                    delete [] TemporaryBuffers;
                    return *this;
                }
                catch(const Ex::customize_exception& Process)
                {
                    std::cerr << Process.what() << " " << Process.function_name_get() << " " << Process.line_number_get() << std::endl;
                    return *this; 
                }
            }
            String SubString(const size_t& StartPosition)
            {
                //提取字串到'\0'
                try
                {
                    if(StartPosition > _size)
                    {
                        throw Ex::customize_exception("传入参数位置越界","SubString",__LINE__);
                    }
                }
                catch(const Ex::customize_exception& Process)
                {
                    std::cerr << Process.what() << " " << Process.function_name_get() << " " << Process.line_number_get() << std::endl;
                    return *this;                
                }
                String result;
                size_t SubLen = _size - StartPosition;
                result.AllocateResources(SubLen);
                std::strncpy(result._data , _data + StartPosition,SubLen);
                result._size = SubLen;
                result._data[result._size] = '\0';
                return result;
            }
            String SubStringFrom(const size_t& StartPosition)
            {
                //提取字串到末尾
                try
                {
                    if(StartPosition > _size)
                    {
                        throw Ex::customize_exception("传入参数位置越界","SubStringFrom",__LINE__);
                    }
                }
                catch(const Ex::customize_exception& Process)
                {
                    std::cerr << Process.what() << " " << Process.function_name_get() << " " << Process.line_number_get() << std::endl;
                    return *this;
                }
                String result;
                size_t SubLen = _size - StartPosition;
                result.AllocateResources(SubLen);
                std::strncpy(result._data , _data + StartPosition,SubLen);
                result._size = SubLen;
                result._data[result._size] = '\0';
                return result;
            }
            String SubString(const size_t& StartPosition ,const size_t& EndPosition)
            {
                //提取字串到指定位置
                try
                {
                    if(StartPosition > _size || EndPosition > _size || StartPosition > EndPosition)
                    {
                        throw Ex::customize_exception("传入参数位置越界","SubString",__LINE__);
                    }
                }
                catch(const Ex::customize_exception& Process)
                {
                    std::cerr << Process.what() << " " << Process.function_name_get() << " " << Process.line_number_get() << std::endl;
                    return *this;
                }
                String result;
                size_t SubLen = EndPosition - StartPosition;
                result.AllocateResources(SubLen);
                //strncpy更安全
                std::strncpy(result._data , _data + StartPosition,SubLen);
                result._size = SubLen;
                result._data[result._size] = '\0';
                return result;
            }
            void AllocateResources(const size_t& NewInaugurateCapacity)
            {
                //检查string空间大小，来分配内存
                if(NewInaugurateCapacity <= _capacity)
                {
                    //防止无意义频繁拷贝
                    return;
                }
                char* temporary_ = new char[NewInaugurateCapacity+1];
                std::memcpy(temporary_,_data,_size+1);
                
                temporary_[_size] = '\0';
                delete[] _data;
                _data = temporary_;
                _capacity = NewInaugurateCapacity;
            }
            String& PushBack(const char& TemporaryData)
            {
                if(_size == _capacity)
                {
                    size_t newcapacity = _capacity == 0 ? 2 :_capacity*2;
                    AllocateResources(newcapacity);
                }
                _data[_size] = TemporaryData;
                ++_size;
                _data[_size] = '\0';
                return *this;
            }
            String& PushBack(const String& TemporaryData)
            {
                size_t Len = _size + TemporaryData._size;
                if(Len > _capacity)
                {
                    size_t NewCapacity = Len;
                    AllocateResources(NewCapacity);
                }
                std::strncpy(_data+_size,TemporaryData._data,TemporaryData.size());
                _size =_size + TemporaryData._size;
                _data[_size] = '\0';
                return *this;
            }
            String& PushBack(const char* TemporaryData)
            {
                if(TemporaryData == nullptr)
                {
                    return *this;
                }
                size_t Len = strlen( TemporaryData );
                size_t NewCapacity = Len + _size ;
                if(NewCapacity >_capacity)
                {
                   AllocateResources(NewCapacity);
                }
                std::strncpy(_data+_size , TemporaryData,Len);
                _size = _size + Len;
                _data[_size] = '\0';
                return *this;
            }
            String& Resize(const size_t& InaugurateSize ,const char& DefaultData = '\0')
            {
                //扩展字符串长度
                if(InaugurateSize >_capacity)
                {
                    //长度大于容量，重新开辟内存
                    try
                    {
                        AllocateResources(InaugurateSize);
                    }
                    catch(const std::bad_alloc& New_char)
                    {
                        std::cerr << New_char.what() << " ";
                    }
                    for(String::iterator StartPosition = _data + _size;StartPosition != _data + InaugurateSize;StartPosition++)
                    {
                        *StartPosition = DefaultData;
                    }
                    _size = InaugurateSize;
                    _data[_size] = '\0';
                }
                else
                {
                    //如果新长度小于当前字符串长度，直接截断放'\0'
                    _size = InaugurateSize;
                    _data[_size] = '\0';
                }
                return *this;
            }
            iterator Reserve(const size_t& NewCapacity)
            {
                AllocateResources(NewCapacity);
                return _data;
                //返回首地址迭代器
            }
            String& Swap(String& StrData)
            {
                MyTemplate::Algorithm::Swap(_data,StrData._data);
                MyTemplate::Algorithm::Swap(_size,StrData._size);
                MyTemplate::Algorithm::Swap(_capacity,StrData._capacity);
                return *this;
            }
            String Reverse()
            {
                try
                {
                    if(_size == 0)
                    {
                        throw Ex::customize_exception("字符串为空","Reserve",__LINE__);
                    }
                }
                catch(const Ex::customize_exception& Process)
                {
                    std::cerr << Process.what() << " " << Process.function_name_get() << " " << Process.line_number_get() << std::endl;
                    return *this;
                }
                String ReversedString;
                for(String::const_reverse_iterator Reverse = rbegin();Reverse != rend();Reverse--)
                {
                    ReversedString.PushBack(*Reverse);
                }
                return ReversedString;
            }
            String ReverseSubstring(const size_t& StartPosition , const size_t& EndPosition)
            {
                try
                {
                    if(StartPosition > _size || EndPosition > _size || StartPosition > EndPosition || _size == 0)
                    {
                        throw Ex::customize_exception("回滚位置异常","ReverseSubstring",__LINE__);
                    }
                }
                catch(const Ex::customize_exception& Process)
                {
                    std::cerr << Process.what() << " " << Process.function_name_get() << " " << Process.line_number_get() << std::endl;
                    return *this;
                } 
                String reversedResult;
                for(String::const_reverse_iterator Reverse = _data + EndPosition - 1;Reverse != _data + StartPosition - 1;Reverse--)
                {
                    reversedResult.PushBack(*Reverse);
                }
                return reversedResult;
            }
            void StringPrint()
            {
                for(String::const_iterator StartPosition = begin();StartPosition != end();StartPosition++)
                {
                    std::cout << *StartPosition;
                }
                std::cout << std::endl;
            }
            void StringPrintReverse()
            {
                for(String::const_reverse_iterator StartPosition = rbegin();StartPosition != rend();StartPosition--)
                {
                    std::cout << *StartPosition;
                }
                std::cout << std::endl;
            }
            friend std::ostream& operator<<(std::ostream& Stringostream,const String &StrData);
            friend std::istream& operator>>(std::istream& Stringistream,String &StrData);
            String& operator=(const String& StrData)
            {
                //防止无意义拷贝
                try
                {
                    if(this != &StrData)
                    {
                        delete [] _data;
                        size_t capacity = StrData._capacity;
                        _data = new char[capacity + 1];
                        std::strncpy(_data,StrData._data,StrData.size());
                        _capacity = StrData._capacity;
                        _size = StrData._size;
                        _data[_size] = '\0';
                    }
                }
                catch(const std::bad_alloc& Process)
                {
                    std::cout << "开辟内存失败！" << Process.what()<< std::endl;
                    return *this;
                }
                return *this;
            }
            String& operator=(String&& StrData) noexcept
            {
                if(this != &StrData)
                {
                    delete [] _data;
                    _size = std::move(StrData._size);
                    _capacity = std::move(StrData._capacity);
                    _data = std::move(StrData._data);
                    StrData._data = nullptr;
                }
                return *this;
            }
            String& operator+=(const String& StrData)
            {
                size_t Len = _size + StrData._size;
                AllocateResources(Len);
                std::strncpy(_data + _size,StrData._data,StrData.size());
                _size = _size + StrData._size;
                _data[_size] = '\0';
                return *this;
            }
            bool operator==(const String& StrData)const
            {
                if(_size != StrData._size)
                {
                    return false;
                }
                for(size_t i = 0;i < _size;i++)
                {
                    if(_data[i]!= StrData._data[i])
                    {
                        return false;
                    }
                }
                return true;
            }
            bool operator<(const String& StrData) const
            {
                size_t MinLen = _size < StrData._size ? _size : StrData._size;
                for(size_t i = 0;i < MinLen;i++)
                {
                    if(_data[i]!= StrData._data[i])
                    {
                        return _data[i] < StrData._data[i];
                    }
                }
                return _size < StrData._size;
            }
            bool operator>(const String& StrData) const
            {
                size_t MinLen = _size < StrData._size? _size : StrData._size;
                for(size_t i = 0;i < MinLen;i++)
                {
                    if(_data[i]!= StrData._data[i])
                    {
                        return _data[i] > StrData._data[i];
                    }
                }
                return _size > StrData._size;
            }
            char& operator[](const size_t& AccessLocation)
            {
                try
                {
                    if(AccessLocation <= _size)
                    {
                        return _data[AccessLocation]; //返回第ergodic_value个元素的引用
                    }
                    else
                    {
                        throw Ex::customize_exception("越界访问","String::operator[]",__LINE__);
                    }
                }
                catch(const Ex::customize_exception& ExceptionStr)
                {
                    std::cerr << ExceptionStr.what() << " " << ExceptionStr.function_name_get() << " " << ExceptionStr.line_number_get() << std::endl;
                    return _data[0];
                }
                //就像_data在外面就能访问它以及它的成员，所以这种就可以理解成出了函数作用域还在，进函数之前也能访问的就是引用
            }
            const char& operator[](const size_t& AccessLocation)const
            {
                try
                {
                    if(AccessLocation <= _size)
                    {
                        return _data[AccessLocation]; //返回第ergodic_value个元素的引用
                    }
                    else
                    {
                        throw Ex::customize_exception("越界访问","String::operator[]const",__LINE__);
                    }
                }
                catch(const Ex::customize_exception& ExceptionStr)
                {
                    std::cerr << ExceptionStr.what() << " " << ExceptionStr.function_name_get() << " " << ExceptionStr.line_number_get() << std::endl;
                    return _data[0];
                }
            }
            String operator+(const String& CppStr)
            {
                String StrTemp;
                size_t StrTempLen = _size + CppStr._size;
                StrTemp.AllocateResources(StrTempLen);
                std::strncpy(StrTemp._data , _data,size());
                std::strncpy(StrTemp._data + _size , CppStr._data,CppStr.size());
                StrTemp._size = _size + CppStr._size;
                StrTemp._data[StrTemp._size] = '\0';
                return StrTemp;
            }
        };
        std::istream& operator>>(std::istream& Stringistream,String& StrData)
        {
            while(true)
            {
                char CIstreamStr = Stringistream.get();
                //gat函数只读取一个字符
                if(CIstreamStr == '\n' || CIstreamStr == EOF)
                {
                    break;
                }
                else
                {
                    StrData.PushBack(CIstreamStr);
                }
            }
            return Stringistream;
        }
        std::ostream& operator<<(std::ostream& Stringostream,const String &StrData) 
        {
            for(MyTemplate::StringContainer::String::const_iterator StartPosition = StrData.cbegin();StartPosition != StrData.cend();StartPosition++)
            {
                Stringostream << *StartPosition;
            }
            return Stringostream;
        }
    }
    /*############################     vector容器     ############################*/
    namespace VectorContainer
    {
        template <typename VectorType>
        class Vector
        {
        public:
            using iterator = VectorType*;
            using const_iterator = const VectorType*;
            using reverse_iterator = VectorType*;
            using const_reverse_iterator = const VectorType*;
        private:
            iterator _DataPointer;     //指向数据的头
            iterator _SizePointer;     //指向数据的尾
            iterator _CapacityPointer; //指向容量的尾
        public:
            iterator begin() noexcept       {   return _DataPointer;   }

            iterator end()  noexcept        {   return _SizePointer;   }

            size_t size() const  noexcept   {   return _DataPointer ? (_SizePointer - _DataPointer) : 0; }

            size_t capacity() const noexcept{   return _DataPointer ? (_CapacityPointer - _DataPointer) : 0; }

            VectorType& Front() noexcept    {   return Head();      }

            VectorType& Back() noexcept     {   return Tail();      }

            bool Empty() noexcept           {   return size() == 0; }

            VectorType& Head() noexcept     {   return *_DataPointer;  }

            VectorType& Tail() noexcept     {   return *(_SizePointer-1);  }

            Vector() noexcept
            {
                _DataPointer = nullptr;
                _SizePointer = nullptr;
                _CapacityPointer = nullptr;
            }
            Vector(const size_t& VectorSumSize , const VectorType& Data = VectorType())
            :_DataPointer(new VectorType[VectorSumSize]),_SizePointer(_DataPointer + VectorSumSize)
            ,_CapacityPointer(_DataPointer + VectorSumSize)
            {
                for(size_t i = 0;i < VectorSumSize;i++)
                {
                    _DataPointer[i] = Data;
                }
            }
            Vector(std::initializer_list<VectorType> ListTemp)
            :_DataPointer(new VectorType[ListTemp.size()]),_SizePointer(_DataPointer + ListTemp.size())
            ,_CapacityPointer(_DataPointer + ListTemp.size())
            {
                //链式拷贝
                size_t i = 0;
                for(auto& e:ListTemp)
                {
                    _DataPointer[i] = e;
                    i++;
                }
            }
            VectorType& Find(const size_t& FindSize)
            {
                try
                {
                    if(FindSize >= size())
                    {
                        throw Ex::customize_exception("传入数据超出容器范围","Vector::Find",__LINE__);
                    }
                    else
                    {
                        return _DataPointer[FindSize];
                    }
                }
                catch(const Ex::customize_exception& Process)
                {
                    std::cerr << Process.what() << " " << Process.function_name_get() << " " << Process.line_number_get() << std::endl;
                    return _DataPointer[0];
                }
            }
            Vector<VectorType>& Completion(const size_t& CompletionSize , const Vector<VectorType>& CompletionTemp)
            {
                size_t CompletionTempSize = size();
                size_t CompletionCapacity  = capacity();
                if(CompletionSize > CompletionCapacity)
                {
                    Resize(CompletionSize);
                    for(size_t i = CompletionCapacity; i < CompletionSize ; i++)
                    {
                        _DataPointer[i] = CompletionTemp;
                    }
                }
                else
                {
                    if(CompletionSize > CompletionTempSize)
                    {
                        for(size_t i = CompletionTempSize; i < CompletionSize ; i++)
                        {
                            _DataPointer[i] = CompletionTemp;
                        }
                    }
                    else if (CompletionSize < CompletionTempSize)
                    {
                        _SizePointer = _DataPointer + CompletionSize;
                    }
                }
                return *this;
            }
            Vector(const Vector<VectorType>& TempData)
            :_DataPointer(TempData.capacity() ? new VectorType[TempData.capacity()] : nullptr),
            _SizePointer(_DataPointer + TempData.size()),_CapacityPointer(_DataPointer + TempData.capacity())
            {
                for(size_t i = 0; i < TempData.size();i++)
                {
                    _DataPointer[i] = TempData._DataPointer[i];
                }
            }
            Vector(Vector<VectorType>&& TempData) noexcept
            {
                _DataPointer = std::move(TempData._DataPointer);
                _SizePointer = std::move(TempData._SizePointer);
                _CapacityPointer = std::move(TempData._CapacityPointer);
                TempData._DataPointer = TempData._SizePointer = TempData._CapacityPointer = nullptr;
            }
            ~Vector()
            {
                delete[] _DataPointer;
                _DataPointer = _SizePointer =_CapacityPointer = nullptr;
            }
            void Swap(Vector<VectorType>& TempData) noexcept
            {
                MyTemplate::Algorithm::Swap(_DataPointer, TempData._DataPointer);
                MyTemplate::Algorithm::Swap(_SizePointer, TempData._SizePointer);
                MyTemplate::Algorithm::Swap(_CapacityPointer, TempData._CapacityPointer);
            }
            iterator Erase(iterator Pos) noexcept
            {
                //删除元素
                iterator temp = Pos + 1;
                while (temp != _SizePointer)
                {
                    //(temp-1)就是pos的位置，从pos位置开始覆盖，覆盖到倒数第1个结束，最后一个会被--屏蔽掉
                    *(temp-1) = *temp;
                    temp++;
                }
                --_SizePointer;
                return temp;
                //返回下一个位置地址
            }
            Vector<VectorType>& Resize(const size_t& NewCapacity, const VectorType& Data = VectorType())
            {
                try 
                {
                    size_t OldSize = size();  // 先保存原来的元素数量
                    if ((size_t)(_CapacityPointer - _DataPointer) < NewCapacity) 
                    {
                        //涉及到迭代器失效问题，不能调用size()函数，会释放未知空间
                        iterator NewData = new VectorType[NewCapacity]; 
                        // 复制原先的数据
                        for (size_t i = 0; i < OldSize; i++) 
                        {
                            NewData[i] = std::move(_DataPointer[i]);
                        }
                        for(size_t i = OldSize; i < NewCapacity; i++)
                        {
                            NewData[i] = Data;
                        }
                        delete [] _DataPointer;
                        _DataPointer = NewData;
                        _SizePointer = _DataPointer + OldSize;  // 使用 OldSize 来重建 _SizePointer
                        _CapacityPointer = _DataPointer + NewCapacity;
                    }
                }
                catch(const std::bad_alloc& Process)
                {
                    std::cerr << Process.what() << std::endl;
                    delete [] _DataPointer;
                    _DataPointer = _SizePointer = _CapacityPointer = nullptr;
                }
                return *this;
            }
            Vector<VectorType>& PushBack(const VectorType& PushBackTemp)
            {
                if(_SizePointer == _CapacityPointer)
                {
                    size_t PushBackSize = _DataPointer == nullptr ? 10 : (size_t)(_CapacityPointer-_DataPointer)*2;
                    Resize(PushBackSize);
                }
                //注意—_size_pointer是原生迭代器指针，需要解引用才能赋值
                *_SizePointer = PushBackTemp;
                _SizePointer++;
                return *this;
            }
            Vector<VectorType>& PushBack(VectorType&& PushBackTemp)
            {
                if(_SizePointer == _CapacityPointer)
                {
                    size_t PushBackSize = _DataPointer == nullptr ? 10 : (size_t)(_CapacityPointer-_DataPointer)*2;
                    Resize(PushBackSize);
                }
                //注意_size_pointer是原生迭代器指针，需要解引用才能赋值
                *_SizePointer = std::move(PushBackTemp);
                // new (_DataPointer) VectorType(std::forward<VectorType>(PushBackTemp));
                _SizePointer++;
                return *this;
            }
            Vector<VectorType>& PopBack() 
            {
                if (_SizePointer > _DataPointer) 
                { // 至少有一个元素
                    --_SizePointer; // 尾指针前移
                }
                return *this;
            }
            Vector<VectorType>& PushFront(const VectorType& PopBackTemp)
            {
                //头插
                if(_SizePointer == _CapacityPointer)
                {
                    size_t PopBanckSize = _DataPointer == nullptr ? 10 : (size_t)(_CapacityPointer-_DataPointer)*2;
                    Resize(PopBanckSize);
                }
                for(size_t PopBackForSize = size();PopBackForSize>0;--PopBackForSize)
                {
                    _DataPointer[PopBackForSize] = _DataPointer[PopBackForSize -1];
                }
                *_DataPointer = PopBackTemp;
                ++_SizePointer;
                return *this;
            }
            Vector<VectorType>& PopFront()
            {
                if( size() > 0 )
                {
                    for(size_t i = 1;i<size();i++)
                    {
                        _DataPointer[i-1] = _DataPointer[i];
                    }
                    --_SizePointer;
                }
                return *this;
            }
            VectorType& operator[](const size_t& SizeOperator)
            {
                // return _DataPointer[SizeOperator];
                try 
                {
                    if( SizeOperator >= capacity())
                    {
                        throw Ex::customize_exception("传入参数越界","Vector::operatot[]",__LINE__);
                    }
                    else
                    {
                        return _DataPointer[SizeOperator];
                    }
                }
                catch(const Ex::customize_exception& Process)
                {
                    std::cerr << Process.what() << " " << Process.function_name_get() << " " << Process.line_number_get() << std::endl;
                    return _DataPointer[0];
                }
            }
            const VectorType& operator[](const size_t& SizeOperator)const 
            {
                // return _DataPointer[SizeOperator];
                try 
                {
                    if( SizeOperator >= capacity())
                    {
                        throw Ex::customize_exception("传入参数越界","Vector::operatot[]",__LINE__);
                    }
                    else
                    {
                        return _DataPointer[SizeOperator];
                    }
                }
                catch(const Ex::customize_exception& Process)
                {
                    std::cerr << Process.what() << " " << Process.function_name_get() << " " << Process.line_number_get() << std::endl;
                    return _DataPointer[0];
                }
            }
            Vector<VectorType>& operator=(const Vector<VectorType>&VectorTemp)
            {
                if (this != &VectorTemp) 
                {
                    Vector<VectorType> temp(VectorTemp); // 拷贝构造
                    Swap(temp); // 交换资源，temp析构时会释放原资源
                }
                return *this;
            }
            Vector<VectorType>& operator=(Vector<VectorType>&& Temp) noexcept
            {
                if( this != &Temp)
                {
                   _DataPointer = std::move(Temp._DataPointer);
                   _SizePointer = std::move(Temp._SizePointer);
                   _CapacityPointer = std::move(Temp._CapacityPointer);
                   Temp._DataPointer = Temp._SizePointer = Temp._CapacityPointer = nullptr;
                }
                return *this;
            }
            Vector<VectorType>& operator+=(const Vector<VectorType>& Temp)
            {
                if(Temp.size() == 0|| Temp._DataPointer == nullptr)
                {
                    return *this;
                }
                size_t TempSize = Temp.size();
                size_t Size = size();
                size_t _capacity_ = capacity();
                if(TempSize + Size > _capacity_)
                {
                    Resize(TempSize + Size);
                } 
                size_t sum = 0;
                for(size_t i = Size ; i < (TempSize + Size); i++)
                {
                    _DataPointer[i] = Temp._DataPointer[sum++];
                }
                _SizePointer = _DataPointer + (TempSize + Size);
                return *this;
            }
            template <typename const_vector_output_templates>
            friend std::ostream& operator<< (std::ostream& VectorOstream, const Vector<const_vector_output_templates>& DynamicArraysData);
        };
        template <typename const_vector_output_templates>
        std::ostream& operator<<(std::ostream& VectorOstream, const Vector<const_vector_output_templates>& DynamicArraysData)
        {
            for(size_t i = 0; i < DynamicArraysData.size(); i++)
            {
                VectorOstream << DynamicArraysData[i] << " ";
            }
            return VectorOstream;
        }
    }

    /*############################     list容器     ############################*/
    namespace list_container
    {
        template <typename list_type>
        class List
        {
            template<typename list_type_function_node>
            struct ListNode
            {
                //节点类
                ListNode<list_type_function_node>* _prev;
                ListNode<list_type_function_node>* _next;
                list_type_function_node _data;

                ListNode(const list_type_function_node& Data = list_type_function_node()) noexcept
                :_prev(nullptr), _next(nullptr), _data(Data)
                {
                    //列表初始化
                }
                ListNode(const list_type_function_node&& data) noexcept
                :_prev(nullptr), _next(nullptr)
                {
                    _data = std::move(data);
                }
            };
            template <typename listNodeTypeIterator ,typename Ref ,typename Ptr >
            class ListIterator
            {
            public:
                //迭代器类
                using Node      = ListNode<listNodeTypeIterator> ;
                using iterator  = ListIterator<listNodeTypeIterator ,listNodeTypeIterator& ,listNodeTypeIterator*>;
                using reference = Ref ;
                using pointer   = Ptr ;
                Node* _node;
                ListIterator(Node* node) noexcept
                :_node(node)
                {
                    ;//拿一个指针来构造迭代器
                }
                Ref operator*() noexcept
                {
                    //返回该节点的自定义类型的数据
                    return _node->_data;
                }
                ListIterator& operator++() noexcept
                {
                    //先加在用
                    _node = _node -> _next;
                    return *this;
                    //返回类型名，如果为迭代器就会因为const 报错
                }
                ListIterator operator++(int) noexcept
                {
                    //先用在加
                    ListIterator temp(_node);
                    _node = _node->_next;
                    //把本体指向下一个位置
                    return temp;
                }
                ListIterator& operator--() noexcept
                {
                    _node = _node->_prev;
                    return *this;
                }
                ListIterator operator--(int) noexcept
                {
                    ListIterator temp (_node);
                    _node = _node->_prev;
                    return temp;
                }
                bool operator!= (const ListIterator& IteratorTemp) noexcept
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
            class ReverselistIterator
            {
                //创建反向迭代器
                using  Ref = typename iterator::reference;
                using  Ptr = typename iterator::pointer ;
                using  ConstReverseListIterator = ReverselistIterator<iterator>;
            public:
                iterator _it;
                ReverselistIterator(iterator it) noexcept
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
                ReverselistIterator& operator++() noexcept
                {
                    --_it;
                    return *this;
                }
                ReverselistIterator operator++(int) noexcept
                {
                    ReverselistIterator _temp (_it);
                    --_it;
                    return _temp;
                }
                ReverselistIterator& operator--() noexcept
                {
                    ++_it;
                    return *this;
                }
                ReverselistIterator operator--(int) noexcept
                {
                    ReverselistIterator _temp (_it);
                    ++_it;
                    return _temp;
                }
                bool operator!=(const ConstReverseListIterator& Temp) noexcept
                {
                    return _it != Temp._it;
                }
            };
            using Node = ListNode<list_type>;

            Node* _head;
            //_head为哨兵位
            void CreateHead()
            {
                _head = new Node;
                _head -> _prev = _head;
                _head -> _next = _head;
            }
        public:
            using iterator = ListIterator<list_type,list_type& ,list_type*>;
            using const_iterator = ListIterator<list_type,const list_type&,const list_type*>;

            //拿正向迭代器构造反向迭代器，可以直接调用 iterator 已经重载的运算符和函数，相当于在封装一层类
            using reverse_iterator = ReverselistIterator<iterator> ;
            using reverse_const_iterator = ReverselistIterator<const_iterator>;
            List()      {       CreateHead();       }
            ~List()
            {
                Clear();
                delete _head;
                _head = nullptr;
            }
            List(iterator first , iterator last)
            {
                //通过另一个list对象构建一个list
                CreateHead();
                //已经创建一个哨兵节点
                while (first != last)
                {
                    PushBack(*first);
                    ++first;
                }
            }
            List(std::initializer_list<list_type> ListTemp)
            {
                //通过初始化列表构建一个list
                CreateHead();
                for(auto& e:ListTemp)
                {
                    PushBack(std::move(e));
                }
            }
            List(const_iterator first , const_iterator last)
            {
                //通过另一个list对象构建一个list
                CreateHead();
                //已经创建一个哨兵节点
                while (first != last)
                {
                    PushBack(*first);
                    ++first;
                }
            }
            List(const List<list_type>& ListData)
            {
                //拷贝构造
                CreateHead();
                List<list_type> Temp (ListData.cbegin(),ListData.cend());
                Swap(Temp);
            }
            List(List<list_type>&& ListData)
            {
                //移动构造
                CreateHead();
                _head = std::move(ListData._head);
                ListData._head = nullptr;
            }
            void Swap(MyTemplate::list_container::List<list_type>& SwapTemp)
            {
                MyTemplate::Algorithm::Swap(_head,SwapTemp._head);
            }
            iterator begin() noexcept                       {   return iterator(_head ->_next);  }

            iterator end() noexcept                         {   return iterator(_head);     }

            const_iterator cbegin()const noexcept           {   return const_iterator(_head ->_next);   }

            const_iterator cend()const noexcept             {   return const_iterator(_head);   }
            
            bool Empty() const noexcept                     {   return _head->_next == _head;   }

            reverse_iterator rbegin() noexcept              {   return reverse_iterator(_head->_prev);  }

            reverse_iterator rend() noexcept                {   return reverse_iterator(_head); }

            reverse_const_iterator rcbegin()const noexcept  {   return reverse_const_iterator(cend());  }

            reverse_const_iterator rcend()const noexcept    {   return reverse_const_iterator(cbegin());  }

            size_t size()const noexcept
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
            /*
            元素访问操作
            */
            const list_type& Front()const noexcept       {       return _head->_next->_data;         }

            const list_type& Back()const noexcept        {       return _head->_prev->_data;         }
            list_type& Front()noexcept
            {
                return _head->_next->_data;
            }

            list_type& Back()noexcept
            {
                return _head->_prev->_data;
            }
            /*
            插入删除操作
            */
            void PushBack(const list_type& PushBackData)     {       Insert(end(),PushBackData);     }

            void PushFront(const list_type& PushfrontData)   {       Insert(begin(),PushfrontData);  }

            void PushBack(list_type&& PushBackData)          {       Insert(end(),std::forward<list_type>(PushBackData)); }

            void PushFront(list_type&& PushfrontData)        {       Insert(begin(),std::forward<list_type>(PushfrontData));  }

            void PopBack()                                  {       Erase(--end());     }

            iterator PopFront()                             {       return Erase(begin());  }

            iterator Insert(iterator Pos ,const list_type& Val)
            {
                Node* PNewNode = new Node(Val);
                //开辟新节点
                Node* PCur = Pos._node;
                //保存pos位置的值
                PNewNode->_prev = PCur->_prev;
                PNewNode->_next = PCur;
                PNewNode->_prev->_next = PNewNode;
                PCur->_prev = PNewNode;
                return iterator(PNewNode);
            }
            iterator Insert(iterator Pos ,list_type&& Val)
            {
                Node* PNewNode = new Node(std::forward<list_type>(Val));
                Node* PCur = Pos._node;
                PNewNode->_prev = PCur->_prev;
                PNewNode->_next = PCur;
                PNewNode->_prev->_next = PNewNode;
                PCur->_prev = PNewNode;
                return iterator(PNewNode);
            }
            iterator Erase(iterator Pos) noexcept
            {
                // 找到待删除的节点
                Node* pDel = Pos._node;
                Node* pRet = pDel->_next;

                // 将该节点从链表中拆下来并删除
                pDel->_prev->_next = pDel->_next;
                pDel->_next->_prev = pDel->_prev;
                delete pDel;

                return iterator(pRet);
            }
            void Resize(size_t newsize, const list_type& Data = list_type())
            {
                //将data插入到链表中
                size_t OldSize = size();
                if (newsize <= OldSize)
                {
                    // 有效元素个数减少到newsize
                    while (newsize < OldSize)
                    {
                        PopBack();
                        OldSize--;
                    }
                }
                else
                {
                    while (OldSize < newsize)
                    {
                        PushBack(Data);
                        OldSize++;
                    }
                }
            }
            void Clear() noexcept
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
            List& operator=(List<list_type> ListTemp) noexcept
            {
                //运算符重载
                if( this != &ListTemp)
                {
                    Swap(ListTemp);
                }
                return *this;
            }
            List& operator=(List<list_type>&& ListTemp) noexcept
            {
                //运算符重载
                if( this != &ListTemp)
                {
                    _head = std::move(ListTemp._head);
                }
                return *this;
            }
            List operator+(const List<list_type>& ListTemp)
            {
                List<list_type> ReturnTemp (cbegin(),cend());
                const_iterator _begin = ListTemp.cbegin();
                const_iterator _end  = ListTemp.cend();
                while(_begin != _end)
                {
                    ReturnTemp.PushBack(*_begin);
                    ++_begin;
                }
                return ReturnTemp;
            }
            List& operator+=(const List<list_type>& ListTemp)
            {
                const_iterator _begin = ListTemp.cbegin();
                const_iterator _end  = ListTemp.cend();
                while(_begin != _end)
                {
                    PushBack(*_begin);
                    ++_begin;
                }
                return *this;
            }
            template <typename const_list_output_templates>
            friend std::ostream& operator<< (std::ostream& ListOstream, const List<const_list_output_templates>& DynamicArraysData);
        };
        template <typename const_list_output_templates>
        std::ostream& operator<< (std::ostream& ListOstream, const List<const_list_output_templates>& DynamicArraysData)
        {
            //typename声明这是一个类型而不是表达式
            typename List<const_list_output_templates>::const_iterator it = DynamicArraysData.cbegin();
            while (it != DynamicArraysData.cend()) 
            {
                ListOstream << *it << " ";
                ++it;
            }
            return ListOstream;
        }
    }
    /*############################     stack适配器     ############################*/
    namespace StackAdapter
    {
        template <typename stack_type,typename vector_based_stack = MyTemplate::VectorContainer::Vector<stack_type>>
        class Stack
        {
        private:
            vector_based_stack ContainerStackTemp;
        public:
            ~Stack()
            {
                ;
            }
            void Push(const stack_type& StackTemp)
            {
                //插入尾
                ContainerStackTemp.PushBack(StackTemp);
            }
            void Pop()
            {
                //删除尾
                ContainerStackTemp.PopBack();
            }
            size_t size() noexcept
            {
                return ContainerStackTemp.size();
            }
            bool Empty() noexcept
            {
                return ContainerStackTemp.Empty();
            } 
            stack_type& top() noexcept
            {
                return ContainerStackTemp.Back();
            }
            Stack(const Stack<stack_type>& StackTemp)
            {
                ContainerStackTemp = StackTemp.ContainerStackTemp;
            }
            Stack( Stack<stack_type>&& StackTemp) noexcept
            {
                ContainerStackTemp = std::move(StackTemp.ContainerStackTemp);//std::move将对象转换为右值引用
            }
            Stack(std::initializer_list<stack_type> StackTemp)
            {
                for(auto& e:StackTemp)
                {
                    ContainerStackTemp.PushBack(e);
                }
            }
            Stack(const stack_type& StackTemp)
            {
                ContainerStackTemp.PushBack(StackTemp);
            }
            Stack& operator= (const Stack<stack_type>& StackTemp)
            {
                if(this != &StackTemp)
                {
                    ContainerStackTemp = StackTemp.ContainerStackTemp;
                }
                return *this;
            }
            Stack& operator=(Stack<stack_type>&& StackTemp) noexcept
            {
                if(this != &StackTemp)
                {
                    ContainerStackTemp = std::move(StackTemp.ContainerStackTemp);
                }
                return *this;
            }
            Stack() = default;
        };
    }
    /*############################     queue适配器     ############################*/
    namespace QueueAdapter
    {
        template <typename queue_type ,typename list_based_queue = MyTemplate::list_container::List<queue_type> >
        class Queue
        {
            //注意队列适配器不会自动检测队列有没有元素，为学异常，注意空间元素
            list_based_queue ContainerQueueTemp;
        public:
            ~Queue()
            {
                ;
            }
            void Push(const queue_type& QueueTemp)
            {
                ContainerQueueTemp.PushBack(QueueTemp);
            }
            void Pop()
            {
                ContainerQueueTemp.PopFront();
                //list返回的是指向下一个位置的正向迭代器
                //vector返回的是整个容器
            }
            size_t size() noexcept
            {
                //返回元素个数
                return ContainerQueueTemp.size();
            }
            bool Empty() noexcept
            {
                //判断容器是否为空
                return ContainerQueueTemp.Empty();
            }
            queue_type& Front() noexcept
            {
                //查看头数据
                return ContainerQueueTemp.Front();
            }
            queue_type& Back() noexcept
            {
                //查看尾数据
                return ContainerQueueTemp.Back();
            }
            Queue(const Queue<queue_type>& QueueTemp)
            {
                //拷贝构造
                ContainerQueueTemp = QueueTemp.ContainerQueueTemp;
            }
            Queue(Queue<queue_type>&& QueueTemp) noexcept
            {
                //移动构造
                ContainerQueueTemp = std::move(QueueTemp.ContainerQueueTemp);
            }
            Queue(std::initializer_list<queue_type> QueueTemp)
            {
                //链式构造
                for(auto& e:QueueTemp)
                {
                    ContainerQueueTemp.PushBack(e);
                }
            }
            Queue(const queue_type& QueueTemp)
            {
                ContainerQueueTemp.PushBack(QueueTemp);
            }
            Queue() = default;
            Queue& operator= (const Queue<queue_type>& QueueTemp)
            {
                if(this != &QueueTemp)
                {
                    ContainerQueueTemp = QueueTemp.ContainerQueueTemp;
                }
                return *this;
            }
            Queue& operator=(Queue<queue_type>&& QueueTemp) noexcept
            {
                if(this != &QueueTemp)
                {
                    ContainerQueueTemp = std::move(QueueTemp.ContainerQueueTemp);
                }
                return *this;
            }
        };
        /*############################     PriorityQueue 适配器     ############################*/
        template <typename priority_queue_type,typename container_imitate_function = MyTemplate::ImitationFunctions::less<priority_queue_type>,
        typename vector_based_priority_queue = MyTemplate::VectorContainer::Vector<priority_queue_type>>
        class PriorityQueue
        {
            //创建容器对象
            vector_based_priority_queue ContainerPriorityQueueTemp;
            container_imitate_function com;
            //仿函数对象

            void PriorityQueueAdjustUpwards(int AdjustUpwardsChild) noexcept
            {
                //向上调整算法
                int parent = (AdjustUpwardsChild-1)/2;
                while(AdjustUpwardsChild > 0)
                {
                    if(com(ContainerPriorityQueueTemp[parent],ContainerPriorityQueueTemp[AdjustUpwardsChild]))
                    {
                        MyTemplate::Algorithm::Swap(ContainerPriorityQueueTemp[parent],ContainerPriorityQueueTemp[AdjustUpwardsChild]);
                        AdjustUpwardsChild = parent;
                        parent = (AdjustUpwardsChild-1)/2;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            void PriorityQueueAdjustDownwards(int parent = 0) noexcept
            {
                int PriorityQueueAdjustDownwardsChild = (parent*2)+1;
                while(PriorityQueueAdjustDownwardsChild < (int)ContainerPriorityQueueTemp.size())
                {
                    int left = PriorityQueueAdjustDownwardsChild;
                    int right =left+1;
                    if( right < (int)ContainerPriorityQueueTemp.size() && com(ContainerPriorityQueueTemp[left],ContainerPriorityQueueTemp[right]))
                    {
                        //大堆找出左右节点哪个孩子大
                        PriorityQueueAdjustDownwardsChild = right;
                    }
                    if(com(ContainerPriorityQueueTemp[parent],ContainerPriorityQueueTemp[PriorityQueueAdjustDownwardsChild]))
                    {
                        //建大堆把小的换下去，建小堆把大的换下去
                        MyTemplate::Algorithm::Swap( ContainerPriorityQueueTemp[parent] , ContainerPriorityQueueTemp[PriorityQueueAdjustDownwardsChild]);

                        //换完之后如果是大堆，则父亲节点是较大的值，需要更新孩子节点继续向下找比孩子节点大的值，如果有继续交换
                        parent = PriorityQueueAdjustDownwardsChild;
                        PriorityQueueAdjustDownwardsChild = (parent*2)+1;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        public:
            ~PriorityQueue()  
            {
                ContainerPriorityQueueTemp.~Vector();
            }
            void Push(const priority_queue_type& FunctionTemplatesPriorityQueuePushBack)
            {
                ContainerPriorityQueueTemp.PushBack(FunctionTemplatesPriorityQueuePushBack);
                PriorityQueueAdjustUpwards((int)ContainerPriorityQueueTemp.size()-1);
            }
            priority_queue_type& top() noexcept
            {
                return ContainerPriorityQueueTemp.Front();
            }
            bool Empty() noexcept
            {
                return ContainerPriorityQueueTemp.Empty();
            }
            size_t size() noexcept
            {
                return ContainerPriorityQueueTemp.size();
            }
            void Pop()
            {
                MyTemplate::Algorithm::Swap(ContainerPriorityQueueTemp[0],ContainerPriorityQueueTemp[ContainerPriorityQueueTemp.size()-(size_t)1]);
                ContainerPriorityQueueTemp.PopBack();
                PriorityQueueAdjustDownwards();
            }
            PriorityQueue() 
            {
                ;
            }
            PriorityQueue(std::initializer_list<priority_queue_type> ListTemp)
            {
                //通过初始化列表构建一个list
                for(auto& e:ListTemp)
                {
                    Push(e);
                }
            }
            PriorityQueue(const PriorityQueue& PriorityQueueTemp)
            {
                //拷贝构造
                ContainerPriorityQueueTemp = PriorityQueueTemp.ContainerPriorityQueueTemp;
            }
            PriorityQueue(PriorityQueue&& PriorityQueueTemp) noexcept
            :com(PriorityQueueTemp.com)
            {
                //移动构造
                ContainerPriorityQueueTemp = std::move(PriorityQueueTemp.ContainerPriorityQueueTemp);
            }
            PriorityQueue(const priority_queue_type& PriorityQueueTemp)
            {
                ContainerPriorityQueueTemp.PushBack(PriorityQueueTemp);
                PriorityQueueAdjustUpwards((int)ContainerPriorityQueueTemp.size()-1);
            }
            PriorityQueue& operator=(PriorityQueue&& PriorityQueueTemp) noexcept
            {
                //移动赋值
                if(this != &PriorityQueueTemp)
                {
                    ContainerPriorityQueueTemp = std::move(PriorityQueueTemp.ContainerPriorityQueueTemp);
                    com = PriorityQueueTemp.com;
                }
                return *this;
            }
            PriorityQueue& operator=(const PriorityQueue& PriorityQueueTemp)
            {
                //拷贝赋值
                if(this != &PriorityQueueTemp)
                {
                    ContainerPriorityQueueTemp = PriorityQueueTemp.ContainerPriorityQueueTemp;
                    com = PriorityQueueTemp.com;
                }
                return *this;
            }
        };
    }
    namespace tree_c
    {
        /*############################     binary_search_tree 容器     ############################*/
        template <typename binary_search_tree_type,typename container_imitate_function = MyTemplate::ImitationFunctions::less <binary_search_tree_type> >
        class binary_search_tree
        {
        private:
            class BSTreeTypeNode
            {
            public:
                //节点类
                BSTreeTypeNode* _left;
                BSTreeTypeNode* _right;
                binary_search_tree_type _data;
                BSTreeTypeNode(const binary_search_tree_type& Data = binary_search_tree_type())
                :_left(nullptr),_right(nullptr),_data(Data)
                {
                    ;
                }
                ~BSTreeTypeNode()
                {
                    _left  = nullptr;
                    _right = nullptr;
                }
            };
            using Node = BSTreeTypeNode;
            Node* _ROOT;
            container_imitate_function com;
            void interior_middle_order_traversal(Node* ROOT_Temp)
            {
                //中序遍历函数
                MyTemplate::StackAdapter::Stack<Node*> StackTemp;
                while(ROOT_Temp != nullptr || !StackTemp.Empty())
                {
                    while(ROOT_Temp!= nullptr)
                    {
                        StackTemp.Push(ROOT_Temp);
                        //压栈
                        ROOT_Temp = ROOT_Temp->_left;
                    }
                    // 访问栈顶节点
                    ROOT_Temp = StackTemp.top();
                    //弹出栈顶元素，刷新栈顶元素，栈顶元素会变成之前压入栈的节点的父节点
                    
                    StackTemp.Pop();
                    std::cout <<  ROOT_Temp->_data << " ";
                    // std::cout << &ROOT_Temp->_data << " ";
                    //检查地址是不是值拷贝
                    // 转向右子树
                    ROOT_Temp = ROOT_Temp->_right;
                }
            }
            size_t interior_middle_order_traversal(Node* ROOT_Temp,size_t& SizeTemp )
            {
                MyTemplate::StackAdapter::Stack<Node*> StackTemp;
                while(ROOT_Temp != nullptr || !StackTemp.Empty())
                {
                    while(ROOT_Temp!= nullptr)
                    {
                        StackTemp.Push(ROOT_Temp);
                        //压栈
                        ROOT_Temp = ROOT_Temp->_left;
                    }
                    // 访问栈顶节点
                    ROOT_Temp = StackTemp.top();
                    //弹出栈顶元素，刷新栈顶元素，栈顶元素会变成之前压入栈的节点的父节点
                    
                    StackTemp.Pop();
                    SizeTemp++;
                    // 转向右子树
                    ROOT_Temp = ROOT_Temp->_right;
                }
                return SizeTemp;
            }
            void interior_pre_order_traversal(Node* ROOT_Temp )
            {
                //前序遍历，最外左子树全部压栈
                if(ROOT_Temp == nullptr)
                {
                    return;
                }
                Node* _PreOrderTraversalTest = ROOT_Temp;
                MyTemplate::StackAdapter::Stack<Node*> stack_Temp;
                stack_Temp.Push(_PreOrderTraversalTest);
                //不能添加|| _PreOrderTraversalTest != nullptr ，因为最后一层循环后_Pre_order_traversal_test还是为真后面循环无意义，反之还会破环性质
                while( !stack_Temp.Empty() )
                {
                    _PreOrderTraversalTest = stack_Temp.top();
                    stack_Temp.Pop();

                    std::cout << _PreOrderTraversalTest->_data << " ";
                    if(_PreOrderTraversalTest->_right != nullptr)
                    {
                        stack_Temp.Push(_PreOrderTraversalTest->_right);
                    }
                    if(_PreOrderTraversalTest->_left != nullptr)
                    {
                        stack_Temp.Push(_PreOrderTraversalTest->_left);
                    }
                    //修改逻辑错误，先压右子树再压左子树，因为这是栈
                }
            }
            void Clear()
            {
                if(_ROOT == nullptr)
                {
                    return;
                }
                //循环释放资源
                MyTemplate::StackAdapter::Stack<Node*> StaicClearTemp;
                StaicClearTemp.Push(_ROOT);
                while(StaicClearTemp.Empty() == false)
                {
                    Node* ROOT_Temp = StaicClearTemp.top();
                    //取出元素，把左右节点入进去
                    StaicClearTemp.Pop();
                    if(ROOT_Temp->_left!= nullptr)
                    {
                        StaicClearTemp.Push(ROOT_Temp->_left);
                    }
                    if(ROOT_Temp->_right!= nullptr)
                    {
                        StaicClearTemp.Push(ROOT_Temp->_right);
                    }
                    delete ROOT_Temp;
                }
                _ROOT = nullptr;
            }
        public:
            ~binary_search_tree()
            {
                Clear();
            }
            // 构造函数，使用初始化列表来初始化二叉搜索树
            binary_search_tree(std::initializer_list<binary_search_tree_type> ListTemp)
            {
                for(auto& e:ListTemp)
                {
                    Push(e);
                }
            }
            binary_search_tree(const binary_search_tree_type& BST_Temp = binary_search_tree_type(),container_imitate_function com_temp = container_imitate_function())
            :_ROOT(nullptr),com(com_temp)
            {   
                _ROOT = new Node(BST_Temp);
            }
            binary_search_tree(binary_search_tree&& BinarySearchTreeTemp)
            :com(BinarySearchTreeTemp.com),_ROOT(nullptr)
            {
                _ROOT = std::move(BinarySearchTreeTemp._ROOT);
                BinarySearchTreeTemp._ROOT = nullptr;
            }
            binary_search_tree(const binary_search_tree& BinarySearchTreeTemp)
            :_ROOT(nullptr),com(BinarySearchTreeTemp.com)
            //这个拷贝构造不需要传模板参数，因为模板参数是在编译时确定的，而不是在运行时确定的，对于仿函数，直接拿传进来的引用初始化就可以了
            {
                //拷贝构造，时间复杂度为O(n)
                Node* BinarySearchTreeTempCopy = BinarySearchTreeTemp._ROOT;
                if(BinarySearchTreeTempCopy == nullptr)
                {
                    return;
                }
                MyTemplate::StackAdapter::Stack<MyTemplate::Practicality::Pair<Node*,Node**> > StackTemp;
                //注意这里把本地_ROOT类型传过去，是因为要对本地的_ROOT进行操作，所以要传二级指针
                //这里传引用也不行，这里的对象是动态变化的，所以传引用也不行
                //如果是对全局的_ROOT进行操作，就传一级指针
                StackTemp.Push(MyTemplate::Practicality::Pair<Node*,Node**>(BinarySearchTreeTempCopy,&_ROOT));
                while( !StackTemp.Empty() )
                {
                    auto StacKTempPair = StackTemp.top();
                    StackTemp.Pop();
                    *(StacKTempPair.second) = new Node(StacKTempPair.first->_data);
                    // Node* _staic_temp_pair_second = *(StacKTempPair.second);
                    // if(StacKTempPair.first->_left!= nullptr)
                    // {
                    //     StackTemp.Push(MY_Template::Practicality::Pair<Node*,Node**>(StacKTempPair.first->_left,&_staic_temp_pair_second->_left));
                    // }
                    // if(StacKTempPair.first->_right!= nullptr)
                    // {
                    //     StackTemp.Push(MY_Template::Practicality::Pair<Node*,Node**>(StacKTempPair.first->_right,&_staic_temp_pair_second->_right));
                    // }
                    //移除临时变量，直接使用指针解引用
                    if(StacKTempPair.first->_right!= nullptr)
                    {
                        StackTemp.Push(MyTemplate::Practicality::Pair<Node*,Node**>(StacKTempPair.first->_right,&((*StacKTempPair.second)->_right)));
                    }
                    if(StacKTempPair.first->_left!= nullptr)
                    {
                        StackTemp.Push(MyTemplate::Practicality::Pair<Node*,Node**>(StacKTempPair.first->_left,&((*StacKTempPair.second)->_left)));
                    }
                }
            }
            void middle_order_traversal()
            {
                //中序遍历函数
                interior_middle_order_traversal(_ROOT);
            }
            void pre_order_traversal()
            {
                interior_pre_order_traversal(_ROOT);
            }
            bool Push(const binary_search_tree_type& Data)
            {
                //尾上插入函数
                if(_ROOT == nullptr)
                {
                    _ROOT = new Node(Data);
                    return true;
                }
                else
                {
                    Node* ROOT_Temp = _ROOT;
                    Node* _ROOT_Temp_Parent = nullptr;
                    while(ROOT_Temp!= nullptr)
                    {
                        _ROOT_Temp_Parent = ROOT_Temp;
                        if(!com(Data, ROOT_Temp->_data) && !com(ROOT_Temp->_data, Data))
                        {
                            //改用仿函数特性，判断是否有重复元素,防止自定义类型没有重载==运算符
                            return false;
                        }
                        else if(com(Data , ROOT_Temp->_data))
                        {
                            ROOT_Temp = ROOT_Temp->_left;
                        }
                        else
                        {
                            ROOT_Temp = ROOT_Temp->_right;
                        }
                    }
                    //新开节点链接
                    Node* _ROOT_Temp_Node = new Node(Data);
                    //链接节点
                    if(com(Data , _ROOT_Temp_Parent->_data))
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
            binary_search_tree& Pop(const binary_search_tree_type& Data)
            {
                //删除节点
                Node* ROOT_Temp = _ROOT;
                Node* _ROOT_Temp_Parent = nullptr;
                while( ROOT_Temp != nullptr )
                {
                    if(Data == ROOT_Temp->_data)
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
                            Node* _ROOT_Temp_right_min = ROOT_Temp->_right;
                            Node* _ROOT_Temp_test_Parent = ROOT_Temp;
                            while(_ROOT_Temp_right_min->_left != nullptr)
                            {
                                _ROOT_Temp_test_Parent = _ROOT_Temp_right_min;
                                _ROOT_Temp_right_min = _ROOT_Temp_right_min->_left;
                            }
                            //找到最左节点	
                            MyTemplate::Algorithm::Swap(ROOT_Temp->_data,_ROOT_Temp_right_min->_data);
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
                    else if(com(Data, ROOT_Temp->_data))
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
                return interior_middle_order_traversal(_ROOT,_size);
            }
            size_t size()const
            {
                size_t _size = 0;
                return interior_middle_order_traversal(_ROOT,_size);
            }
            Node* Find(const binary_search_tree_type& Data)
            {
                //查找函数
                Node* _ROOT_Find = _ROOT;
                while(_ROOT_Find!= nullptr)
                {
                    if(Data == _ROOT_Find->_data)
                    {
                        return _ROOT_Find;
                    }
                    else if(com(Data, _ROOT_Find->_data))
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
            void Insert(const binary_search_tree_type& FormerData,const binary_search_tree_type& LatterData)
            {
                //在former_data后面插入latter_data
                Node* ROOTFormerData = Find(FormerData);
                //插入节点
                if(ROOTFormerData == nullptr)
                {
                    return;
                }
                else
                {
                    Node* _ROOT_latter_data = new Node(LatterData);
                    _ROOT_latter_data->_left = ROOTFormerData->_right;
                    ROOTFormerData->_right = _ROOT_latter_data;
                }
            }
            binary_search_tree& operator=(const binary_search_tree& BinarySearchTreeTemp)
            {
                //赋值运算符重载
                if(this != &BinarySearchTreeTemp)
                {
                    Clear();
                    com = BinarySearchTreeTemp.com;
                    binary_search_tree BinarySearchTreeTempCopy = BinarySearchTreeTemp;
                    MyTemplate::Algorithm::Swap(BinarySearchTreeTempCopy._ROOT,_ROOT);
                }
                return *this;
            }
            binary_search_tree& operator=(binary_search_tree && BinarySearchTreeTemp)
            {
                //移动赋值运算符重载
                if(this != &BinarySearchTreeTemp)
                {
                    Clear();
                    com = BinarySearchTreeTemp.com;
                    _ROOT = std::move(BinarySearchTreeTemp._ROOT);
                    BinarySearchTreeTemp._ROOT = nullptr;
                }
                return *this;
            }

        };
        /*############################     AVLTree 容器     ############################*/
        template <typename AVLTreeTypeK,typename AVLTreeTypeV,typename CompareImitationFunctionsAVL = MyTemplate::ImitationFunctions::less <AVLTreeTypeK>,
        typename AVLSyntheticClass = MyTemplate::Practicality::Pair<AVLTreeTypeK,AVLTreeTypeV> >
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
                        Node* NodeTemp = _Node;
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
                        Node* NodeTemp = _Node;
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
            using Node = AVLTreeTypeNode;
            Node* _ROOT;

            CompareImitationFunctionsAVL com;
            void LeftRevolve(Node*& ParentTempNode)
            {
                //传进来的值是发现该树平衡性被破坏的节点地址
                //大致思想：因为这是左单旋，所以找传进来的父亲节点的右根节点来当调整节点
                //然后把调整节点的左根节点赋值给传进来的父亲节点的右根节点 (刚才已经用节点保存过调整节点，所以这里直接赋值)，
                //再把父亲节点赋值给调整节点的左根节点，！！注意：在旋转的过程中还要处理每个调整节点的父亲节点的指向和平衡因子

                // {
                //     Node* SubRightTemp = ParentTempNode->_right;
                //     ParentTempNode->_right = SubRightTemp->_left;
                //     SubRightTemp->_left = ParentTempNode;
                //     //错误写法：未同步调整父亲节点和判断调整节点的左根节点是否为空，以及全部需要调整节点的父亲指针的指针的指向
                // }
                if(ParentTempNode == nullptr|| ParentTempNode->_right == nullptr)
                {
                    std::cout <<"left "<< "空指针"  <<std::endl;
                    return ;
                }
                Node* SubRightTemp = ParentTempNode->_right;
                // Node* SubRightLeftTemp = SubRightTemp->_left;
                Node* SubRightLeftTemp = (SubRightTemp->_left)? SubRightTemp->_left : nullptr;
                //防止空指针解引用
                ParentTempNode->_right = SubRightLeftTemp;
                if(SubRightLeftTemp)
                {
                    SubRightLeftTemp->_parent = ParentTempNode;
                    //如果Sub_right_left_temp(调整节点的左根节点)不等于空，还需要调整Sub_right_left_temp它的父亲节点
                }
                SubRightTemp->_left = ParentTempNode;
                //这里先保存一下parent_temp_Node的父亲地址，防止到下面else比较的时候丢失
                Node* ParentParentTempNode = ParentTempNode->_parent;
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

            void RightRevolve(Node*& ParentTempNode)
            {
                //思路同左单旋思路差不多
                if(ParentTempNode == nullptr|| ParentTempNode->_left == nullptr)
                {
                    std::cout <<"right "<< "空指针"  <<std::endl; 
                    return ;
                }
                Node* SubLeftTemp = ParentTempNode->_left;
                Node* SubLeftRightTemp = (SubLeftTemp->_right) ? SubLeftTemp->_right : nullptr;
                //防止空指针解引用
                ParentTempNode->_left = SubLeftRightTemp;
                if(SubLeftRightTemp)
                {
                    SubLeftRightTemp->_parent = ParentTempNode;
                }
                SubLeftTemp->_right = ParentTempNode;
                //保存parent_temp_Node的父亲节点
                Node* ParentParentTempNode = ParentTempNode->_parent;
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
            void RightLeftRevolve(Node*& ParentTempNode)
            {
                if(ParentTempNode==nullptr || ParentTempNode->_right == nullptr)
                {
                    std::cout <<"right_left "<< "空指针"  <<std::endl;
                    return;
                }
                Node* SubRightTemp = ParentTempNode->_right;
                Node* SubRightLeftTemp = SubRightTemp->_left;
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
            void LeftRightRevolve(Node*& ParentTempNode)
            {   
                if(ParentTempNode == nullptr || ParentTempNode->_left == nullptr)
                {
                    std::cout << "left_right " << "空指针" << std::endl;
                    return ;
                }
                Node* SubLeftTemp = ParentTempNode->_left;
                Node* SubLeftRightTemp = SubLeftTemp->_right;
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
            void Clear()
            {
                //清空所有资源
                if(_ROOT == nullptr)
                {
                    return;
                }
                else
                {
                    MyTemplate::StackAdapter::Stack<Node*> StackTemp;
                    //前序释放
                    StackTemp.Push(_ROOT);
                    while(!StackTemp.Empty())
                    {
                        Node* temp = StackTemp.top();
                        StackTemp.Pop();
                        if(temp->_left != nullptr)
                        {
                            StackTemp.Push(temp->_left);
                        }
                        if(temp->_right != nullptr)
                        {
                            StackTemp.Push(temp->_right);
                        }
                        delete temp;
                        temp = nullptr;
                    }
                    _ROOT = nullptr;
                }
            }
            //测试函数
            void interior_pre_order_traversal(Node* ROOT_Temp )
            {
                //前序遍历，最外左子树全部压栈
                if(ROOT_Temp == nullptr)
                {
                    return;
                }
                Node* _PreOrderTraversalTest = ROOT_Temp;
                MyTemplate::StackAdapter::Stack<Node*> stack_Temp;
                stack_Temp.Push(_PreOrderTraversalTest);
                //不能添加|| _PreOrderTraversalTest != nullptr ，因为最后一层循环后_Pre_order_traversal_test还是为真后面循环无意义，反之还会破环性质
                while( !stack_Temp.Empty() )
                {
                    _PreOrderTraversalTest = stack_Temp.top();
                    stack_Temp.Pop();

                    std::cout << _PreOrderTraversalTest->_data << " ";
                    //修改逻辑错误，先压右子树再压左子树，因为这是栈
                    if(_PreOrderTraversalTest->_right != nullptr)
                    {
                        stack_Temp.Push(_PreOrderTraversalTest->_right);
                    }
                    if(_PreOrderTraversalTest->_left != nullptr)
                    {
                        stack_Temp.Push(_PreOrderTraversalTest->_left);
                    }
                }
            }
            void interior_middle_order_traversal(Node* ROOT_Temp)
            {
                //中序遍历函数
                MyTemplate::StackAdapter::Stack<Node*> StackTemp;
                while(ROOT_Temp != nullptr || !StackTemp.Empty())
                {
                    while(ROOT_Temp!= nullptr)
                    {
                        StackTemp.Push(ROOT_Temp);
                        //压栈
                        ROOT_Temp = ROOT_Temp->_left;
                    }
                    // 访问栈顶节点
                    ROOT_Temp = StackTemp.top();
                    //弹出栈顶元素，刷新栈顶元素，栈顶元素会变成之前压入栈的节点的父节点
                    
                    StackTemp.Pop();
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
                    Node* _PreOrderTraversalTest = _ROOT;
                    MyTemplate::StackAdapter::Stack<Node*> stack_Temp;
                    stack_Temp.Push(_PreOrderTraversalTest);
                    while( !stack_Temp.Empty() )
                    {
                        _PreOrderTraversalTest = stack_Temp.top();
                        stack_Temp.Pop();

                        temp++;

                        if(_PreOrderTraversalTest->_right != nullptr)
                        {
                            stack_Temp.Push(_PreOrderTraversalTest->_right);
                        }
                        if(_PreOrderTraversalTest->_left != nullptr)
                        {
                            stack_Temp.Push(_PreOrderTraversalTest->_left);
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
                Node* BeginTemp = _ROOT;
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
                Node* BeginTemp = _ROOT;
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
                Node* RbeginTemp = _ROOT;
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
                Node* RbeginTemp = _ROOT;
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
            bool Empty()
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
                _ROOT = new Node(KeyTemp,ValTemp);
            }
            AVLTree(const AVLSyntheticClass& AVLTreePairTemp,
            CompareImitationFunctionsAVL com_temp = CompareImitationFunctionsAVL())
            :_ROOT(nullptr),com(com_temp)
            {
                _ROOT = new Node(AVLTreePairTemp.first,AVLTreePairTemp.second);
            }
            AVLTree(const AVLTree& AVLTreeTemp)
            : _ROOT(nullptr), com(AVLTreeTemp.com)
            {
                if (AVLTreeTemp._ROOT == nullptr)
                {
                    return;
                }

                // 使用单栈，存储源节点和目标父节点（均为一级指针）
                MyTemplate::StackAdapter::Stack<MyTemplate::Practicality::Pair<Node*, Node*>> Stack;
                
                // 创建根节点
                _ROOT = new Node(AVLTreeTemp._ROOT->_data);
                _ROOT->_BalanceFactor = AVLTreeTemp._ROOT->_BalanceFactor;
                _ROOT->_parent = nullptr; // 根节点的父节点为nullptr
                
                // 初始化栈，将根节点的子节点压入（注意：这里父节点是 _ROOT，一级指针）
                if (AVLTreeTemp._ROOT->_right != nullptr)
                {
                    Stack.Push(MyTemplate::Practicality::Pair<Node*, Node*>(AVLTreeTemp._ROOT->_right, _ROOT));
                }
                if (AVLTreeTemp._ROOT->_left != nullptr)
                {
                    Stack.Push(MyTemplate::Practicality::Pair<Node*, Node*>(AVLTreeTemp._ROOT->_left, _ROOT));
                }

                // 遍历并复制剩余节点
                while (!Stack.Empty())
                {
                    auto [SourceNode, parent_node] = Stack.top();
                    Stack.Pop();
                    
                    // 创建新节点并复制数据
                    Node* NewNode = new Node(SourceNode->_data);
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
                        Stack.Push(MyTemplate::Practicality::Pair<Node*, Node*>(SourceNode->_right, NewNode));
                    }
                    if (SourceNode->_left != nullptr)
                    {
                        Stack.Push(MyTemplate::Practicality::Pair<Node*, Node*>(SourceNode->_left, NewNode));
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
                    Clear();
                    _ROOT = std::move(AVLTreeTemp._ROOT);
                    com  = std::move(AVLTreeTemp.com);
                    AVLTreeTemp._ROOT = nullptr;
                }
            }
            AVLTree& operator=(const AVLTree AVLTreeTemp)
            {
                Clear();
                if(&AVLTreeTemp == this)
                {
                    return *this;
                }
                if (AVLTreeTemp._ROOT == nullptr)
                {
                    return *this;
                }
                MyTemplate::Algorithm::Swap(com,AVLTreeTemp.com);
                MyTemplate::Algorithm::Swap(_ROOT,AVLTreeTemp._ROOT);
                return *this;
            }
            ~AVLTree()
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
            void pre_order_traversal()
            {
                interior_pre_order_traversal(_ROOT);
            }
            void middle_order_traversal()
            {
                interior_middle_order_traversal(_ROOT);
            }
            bool Push(const AVLTreeTypeK& KeyTemp,const AVLTreeTypeV& ValTemp = AVLTreeTypeV())
            {
                //插入
                if(_ROOT == nullptr)
                {
                    _ROOT = new Node(KeyTemp,ValTemp);
                    return true;
                }
                else
                {
                    Node* _ROOT_temp = _ROOT;
                    Node* ROOT_Temp_Parent = nullptr;
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
                    _ROOT_temp = new Node(KeyTemp,ValTemp);
                    if(com(KeyTemp,ROOT_Temp_Parent->_data.first))
                    {
                        ROOT_Temp_Parent->_left = _ROOT_temp;
                    }
                    else
                    {
                        ROOT_Temp_Parent->_right = _ROOT_temp;
                    }
                    _ROOT_temp->_parent = ROOT_Temp_Parent;

                    Node* _ROOT_temp_test = _ROOT_temp;
                    Node* _ROOT_temp_test_parent = ROOT_Temp_Parent;

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
            bool Push(const AVLSyntheticClass& AVLTreePairTemp)
            {
                //AVL树左子树比右子树高，则他俩的根节点的平衡因子为1，反之为-1，也就是说左加一，右减一，如果根节点为2和-2就要需要调整了
                if(_ROOT == nullptr)
                {
                    _ROOT = new Node(AVLTreePairTemp.first,AVLTreePairTemp.second);
                    return true;
                }
                else
                {
                    Node* ROOT_Temp = _ROOT;
                    Node* ROOT_Temp_Parent = nullptr;
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
                    ROOT_Temp = new Node(AVLTreePairTemp);
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
                    Node* ROOTTempTest = ROOT_Temp;
                    Node* _ROOT_Temp_test_parent = ROOT_Temp_Parent;
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
            Node* Find(const AVLTreeTypeK& DataTemp)
            {
                Node* ROOT_Temp = _ROOT;
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
            AVLTree& Pop(const AVLTreeTypeK& DataTemp)
            {
                if(_ROOT == nullptr)
                {
                    return *this;
                }
                Node* ROOT_Temp = _ROOT;
                Node* ROOT_Temp_Parent = nullptr;
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
                    Node* _right_min = ROOT_Temp->_right;
                    Node* _right_parent = ROOT_Temp;
                    while(_right_min->_left != nullptr)
                    {
                        _right_parent = _right_min;
                        _right_min = _right_min->_left;
                    }
                    MyTemplate::Algorithm::Swap(_right_min->_data,ROOT_Temp->_data);
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
                Node* parent_BF = ROOT_Temp_Parent;
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
    namespace BaseClassContainer
    {
        /*############################     RBTree 容器     ############################*/
        template <typename RBTreeTypeKey, typename RBTreeTypeVal, typename DataExtractionFunction,
        typename CompareImitationFunctionsRB = MyTemplate::ImitationFunctions::less<RBTreeTypeKey> >
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
                        Node* Sub = _Node->_right;
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
                bool operator==(const RBTreeReverseIterator& Other) const 
                { 
                    return _it == Other._it; 
                }
                bool operator!=(const RBTreeReverseIterator& Other) const 
                { 
                    return _it != Other._it; 
                }
            };
            using Node = RBTreeNode;
            Node* _ROOT;
            DataExtractionFunction Element;
            CompareImitationFunctionsRB com;
            void LeftRevolve(Node* ParentTempNode)
            {
                //传进来的值是发现该树平衡性被破坏的节点地址
                //大致思想：因为这是左单旋，所以找传进来的父亲节点的右根节点来当调整节点
                //然后把调整节点的左根节点赋值给传进来的父亲节点的右根节点 (刚才已经用节点保存过调整节点，所以这里直接赋值)，
                //再把父亲节点赋值给调整节点的左根节点，！！注意：在旋转的过程中还要处理每个调整节点的父亲节点的指向和平衡因子

                // {
                //     Node* SubRightTemp = ParentTempNode->_right;
                //     ParentTempNode->_right = SubRightTemp->_left;
                //     SubRightTemp->_left = ParentTempNode;
                //     //错误写法：未同步调整父亲节点和判断调整节点的左根节点是否为空，以及全部需要调整节点的父亲指针的指针的指向
                // }
                if(ParentTempNode == nullptr|| ParentTempNode->_right == nullptr)
                {
                    std::cout <<"left "<< "空指针"  <<std::endl;
                    return ;
                }
                Node* SubRightTemp = ParentTempNode->_right;
                // Node* SubRightLeftTemp = SubRightTemp->_left;
                Node* SubRightLeftTemp = (SubRightTemp->_left)? SubRightTemp->_left : nullptr;
                //防止空指针解引用
                ParentTempNode->_right = SubRightLeftTemp;
                if(SubRightLeftTemp)
                {
                    SubRightLeftTemp->_parent = ParentTempNode;
                    //如果Sub_right_left_temp(调整节点的左根节点)不等于空，还需要调整Sub_right_left_temp它的父亲节点
                }
                SubRightTemp->_left = ParentTempNode;
                //这里先保存一下parent_temp_Node的父亲地址，防止到下面else比较的时候丢失
                Node* ParentParentTempNode = ParentTempNode->_parent;
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
            void RightRevolve(Node*& ParentTempNode)
            {
                //思路同左单旋思路差不多,但是相反
                if(ParentTempNode == nullptr|| ParentTempNode->_left == nullptr)
                {
                    std::cout <<"right "<< "空指针"  <<std::endl; 
                    return ;
                }
                Node* SubLeftTemp = ParentTempNode->_left;
                Node* SubLeftRightTemp = (SubLeftTemp->_right) ? SubLeftTemp->_right : nullptr;
                //防止空指针解引用
                ParentTempNode->_left = SubLeftRightTemp;
                if(SubLeftRightTemp)
                {
                    SubLeftRightTemp->_parent = ParentTempNode;
                }
                SubLeftTemp->_right = ParentTempNode;
                //保存parent_temp_Node的父亲节点
                Node* ParentParentTempNode = ParentTempNode->_parent;
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
            void Clear(Node* _clear_Temp)
            {
                if(_clear_Temp == nullptr)
                {
                    return ;
                }
                else
                {
                    MyTemplate::StackAdapter::Stack<Node*> _stack;
                    _stack.Push(_clear_Temp);
                    while ( !_stack.Empty() )
                    {
                        _clear_Temp = _stack.top();
                        _stack.Pop();
                        if(_clear_Temp->_right != nullptr)
                        {
                            _stack.Push(_clear_Temp->_right);
                        }
                        if(_clear_Temp->_left  != nullptr)
                        {
                            _stack.Push(_clear_Temp->_left);
                        }
                        delete _clear_Temp;
                    }
                    _ROOT = nullptr;
                }
            }
            void interior_middle_order_traversal(Node* ROOT_Temp)
            {
                //中序遍历函数
                MyTemplate::StackAdapter::Stack<Node*> StackTemp;
                while(ROOT_Temp != nullptr || !StackTemp.Empty())
                {
                    while(ROOT_Temp!= nullptr)
                    {
                        StackTemp.Push(ROOT_Temp);
                        ROOT_Temp = ROOT_Temp->_left;
                    }
                    ROOT_Temp = StackTemp.top();
                    StackTemp.Pop();
                    std::cout <<  ROOT_Temp->_data << " ";
                    // std::cout << ROOT_Temp->_color <<" ";
                    ROOT_Temp = ROOT_Temp->_right;
                }
            }
            void interior_pre_order_traversal(Node* ROOT_Temp )
            {
                //前序遍历，最外左子树全部压栈
                if(ROOT_Temp == nullptr)
                {
                    return;
                }
                Node* _PreOrderTraversalTest = ROOT_Temp;
                MyTemplate::StackAdapter::Stack<Node*> stack_Temp;
                stack_Temp.Push(_PreOrderTraversalTest);
                while( !stack_Temp.Empty() )
                {
                    _PreOrderTraversalTest = stack_Temp.top();
                    stack_Temp.Pop();

                    std::cout << _PreOrderTraversalTest->_data << " ";
                    // std::cout << _PreOrderTraversalTest->_color <<" ";
                    //修改逻辑错误，先压右子树再压左子树，因为这是栈
                    if(_PreOrderTraversalTest->_right != nullptr)
                    {
                        stack_Temp.Push(_PreOrderTraversalTest->_right);
                    }
                    if(_PreOrderTraversalTest->_left != nullptr)
                    {
                        stack_Temp.Push(_PreOrderTraversalTest->_left);
                    }
                }
            }
            static inline RBTreeColor Get_color(Node* cur)
            {
                return cur == nullptr ? BLACK : cur->_color;
            }
            static inline bool RED_Get(Node* cur)
            {
                return Get_color(cur) == RED;
            }
            static inline bool BLACK_Get(Node* cur)
            {
                return Get_color(cur) == BLACK;
            }
            size_t _size() const 
            {
                size_t size = 0;
                Node* ROOT_Temp = _ROOT;
                if(ROOT_Temp == nullptr)
                {
                    return size;
                }
                Node* _PreOrderTraversalTest = ROOT_Temp;
                MyTemplate::StackAdapter::Stack<Node*> stack_Temp;
                stack_Temp.Push(_PreOrderTraversalTest);
                while( !stack_Temp.Empty() )
                {
                    _PreOrderTraversalTest = stack_Temp.top();
                    stack_Temp.Pop();

                    size++;
                    if(_PreOrderTraversalTest->_right != nullptr)
                    {
                        stack_Temp.Push(_PreOrderTraversalTest->_right);
                    }
                    if(_PreOrderTraversalTest->_left != nullptr)
                    {
                        stack_Temp.Push(_PreOrderTraversalTest->_left);
                    }
                }
                return size;
            }
        public:
            using iterator = RBTreeiterator<RBTreeTypeVal,RBTreeTypeVal&,RBTreeTypeVal*>; 
            using const_iterator =  RBTreeiterator<RBTreeTypeVal const,RBTreeTypeVal const&,RBTreeTypeVal const*>;

            using reverse_iterator = RBTreeReverseIterator<iterator>;
            using const_reverse_iterator = RBTreeReverseIterator<const_iterator>;

            using insert_result = MyTemplate::Practicality::Pair<iterator,bool>;
            RBTree()
            {
                _ROOT = nullptr;
            }
            RBTree(const RBTreeTypeVal& RBTreeTemp)
            {
                _ROOT = new Node(RBTreeTemp);
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
                    Clear(_ROOT);
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
                        MyTemplate::StackAdapter::Stack<MyTemplate::Practicality::Pair<Node*, Node*>> Stack;
                        
                        // 创建根节点
                        _ROOT = new Node(RBTreeTemp._ROOT->_data);
                        _ROOT->_color = RBTreeTemp._ROOT->_color;
                        _ROOT->_parent = nullptr; // 根节点的父节点为nullptr
                        
                        // 初始化栈，将根节点的子节点压入（注意：这里父节点是 _ROOT，一级指针）
                        if (RBTreeTemp._ROOT->_right != nullptr)
                        {
                            Stack.Push(MyTemplate::Practicality::Pair<Node*, Node*>(RBTreeTemp._ROOT->_right, _ROOT));
                        }
                        if (RBTreeTemp._ROOT->_left != nullptr)
                        {
                            Stack.Push(MyTemplate::Practicality::Pair<Node*, Node*>(RBTreeTemp._ROOT->_left, _ROOT));
                        }

                        // 遍历并复制剩余节点
                        while (!Stack.Empty())
                        {
                            auto [SourceNode, parent_node] = Stack.top();
                            Stack.Pop();
                            
                            // 创建新节点并复制数据
                            Node* NewNode = new Node(SourceNode->_data);
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
                                Stack.Push(MyTemplate::Practicality::Pair<Node*, Node*>(SourceNode->_right, NewNode));
                            }
                            if (SourceNode->_left != nullptr)
                            {
                                Stack.Push(MyTemplate::Practicality::Pair<Node*, Node*>(SourceNode->_left, NewNode));
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
                    Clear(_ROOT);
                    MyTemplate::Algorithm::Swap(RBTreeTemp._ROOT,_ROOT);
                    MyTemplate::Algorithm::Swap(RBTreeTemp.Element,Element);
                    MyTemplate::Algorithm::Swap(RBTreeTemp.com,com);
                    return *this;
                }
            }
            RBTree& operator=(RBTree&& RBTreeTemp)
            {
                if(this != &RBTreeTemp)
                {
                    Clear();
                    com = std::move(RBTreeTemp.com);
                    Element = std::move(RBTreeTemp.Element);
                    _ROOT = std::move(RBTreeTemp._ROOT);
                    RBTreeTemp._ROOT = nullptr;
                }
                return *this;
            }
            ~RBTree()
            {
                Clear(_ROOT);
            }
            insert_result Push(const RBTreeTypeVal& Val_Temp_)
            {
                if(_ROOT == nullptr)
                {
                    _ROOT = new Node(Val_Temp_);
                    _ROOT->_color = BLACK;
                    return insert_result(iterator(_ROOT),true);
                }
                else
                {
                    Node* ROOT_Temp = _ROOT;
                    Node* ROOT_Temp_Parent = nullptr;
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
                    ROOT_Temp = new Node(Val_Temp_);
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
                    Node* Return_Node_Push = ROOT_Temp;
                    //保存节点
                    //开始调整，向上调整颜色节点
                    while(ROOT_Temp_Parent != nullptr && ROOT_Temp_Parent->_color == RED )
                    {
                        Node* ROOT_Temp_Grandfther = ROOT_Temp_Parent->_parent;
                        if(ROOT_Temp_Grandfther->_left == ROOT_Temp_Parent)
                        {
                            //叔叔节点
                            // std::cout << "Push" <<" ";
                            Node* Uncle = ROOT_Temp_Grandfther->_right;
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
                                    MyTemplate::Algorithm::Swap(ROOT_Temp,ROOT_Temp_Parent);
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
                            Node* Uncle = ROOT_Temp_Grandfther->_left;
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
                                    MyTemplate::Algorithm::Swap(ROOT_Temp,ROOT_Temp_Parent);
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
            void DeleteAdjust(Node* cur ,Node* parent)
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
                        Node* brother = parent->_right;
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
                        Node* brother = parent->_left;
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
            insert_result Pop(const RBTreeTypeVal& RBTreeTemp)
            {
                RBTreeColor DeleteColor;
                if(_ROOT == nullptr)
                {
                    return insert_result(iterator(nullptr),false);
                }
                else
                {
                    Node* ROOT_Temp = _ROOT;
                    Node* ROOT_Temp_Parent = nullptr;
                    Node* AdjustNode = nullptr;
                    Node* AdjustNodeParent = nullptr;
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
                        Node* _right_min = ROOT_Temp->_right;
                        Node* _right_parent = ROOT_Temp;
                        while(_right_min->_left != nullptr)
                        {
                            _right_parent = _right_min;
                            _right_min = _right_min->_left;
                        }
                        DeleteColor = _right_min->_color;

                        // 交换数据 AND 交换颜色
                        MyTemplate::Algorithm::Swap(_right_min->_data,  ROOT_Temp->_data);
                        MyTemplate::Algorithm::Swap(_right_min->_color, ROOT_Temp->_color);

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
            iterator Find(const RBTreeTypeVal& RB_Tree_Temp_)
            {
                if(_ROOT == nullptr)
                {
                    return iterator(nullptr);
                }
                else
                {
                    Node* iterator_ROOT = _ROOT;
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
            bool Empty()
            {
                return _ROOT == nullptr;
            }
            void middle_order_traversal()
            {
                interior_middle_order_traversal(_ROOT);
            }
            void pre_order_traversal()
            {
                interior_pre_order_traversal(_ROOT);
            }
            iterator begin()
            {
                Node* iterator_ROOT = _ROOT;
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
                Node* iterator_ROOT = _ROOT;
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
                Node* iterator_Node = _ROOT;
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
                Node* iterator_Node = _ROOT;
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
                return Find(RBTreeTemp);
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
            using Node = HashTableNode;
            DataExtractionFunction HashDataFunctor;                   //仿函数
            size_t _size;                                             //哈希表大小
            size_t LoadFactor;                                        //负载因子   
            size_t Capacity;                                          //哈希表容量
            MyTemplate::VectorContainer::Vector<Node*> _HashTable;    //哈希表
            HashTableFunction HashFunction;                           //哈希函数
            Node* PreviousData = nullptr;                             //上一个数据
            Node* HeadData = nullptr;                                 //插入头数据
            template <typename Hash_Table_iterator_Key, typename Hash_Table_iterator_Val>
            class Hash_iterator
            {
                using iterator_Node = Node;
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
            void parentJudgment(Node*& TempNodeParent,Node*& _TempNode,size_t& HashLocationData)
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
                _HashTable.Resize(Capacity);
            }
            HashTable(size_t TempCapacity)
            {
                _size = 0;
                LoadFactor = 7;
                Capacity = TempCapacity;
                _HashTable.Resize(Capacity);
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
                _HashTable.Resize(Capacity, nullptr);
        
                // 2. 遍历原表的每一个桶
                for (size_t i = 0; i < Capacity; ++i) 
                {
                    Node* SrcBucketNode = TempHashTable._HashTable[i];
                    // 桶内新表的尾节点（用于串联 _next）
                    Node* last_in_bucket = nullptr;
        
                    // 逐节点深拷贝
                    while (SrcBucketNode) 
                    {
                        // 2.1 创建新节点并拷贝数据
                        Node* NewNode = new Node(SrcBucketNode->_data);
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
                HashFunction= std::move(TempHashTable.DataExtractionFunction);
                PreviousData = std::move(TempHashTable.PreviousData);
                HeadData = std::move(TempHashTable.HeadData);
                HashDataFunctor = std::move(TempHashTable.HashDataFunctor);
            }
            ~HashTable()
            {
                for(size_t i = 0;i < _HashTable.size();++i)
                {
                    Node* _TempNode = _HashTable[i];
                    while(_TempNode != nullptr)
                    {
                        Node* _Temp_Node_prev = _TempNode;
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
                    Node* _TempNode = _HashTable[HashLocationData];
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
            bool   Empty()                      {   return _size == 0;                  }
            size_t capacity()                   {   return Capacity;                    }
            size_t capacity() const             {   return Capacity;                    }

            bool Push (const HashTableTypeVal& TempVal)
            {
                if( Find(TempVal) != nullptr)
                {
                    return false;
                }
                //判断扩容
                if( _size * 10 >= Capacity * LoadFactor)
                {
                    //扩容
                    size_t NewCapacity = (Capacity == 0 && _HashTable.size() == 0) ? 10 : Capacity * 2;
                    //新容量
                    MyTemplate::VectorContainer::Vector<Node*> _NewHashTable;
                    _NewHashTable.Resize(NewCapacity,nullptr);
                    size_t _New_size = 0;
                    //重新映射,按照插入链表顺序
                    Node* _TempHeadNode = nullptr;
                    Node* _TempPreviousData = nullptr;
                    Node* _TempNode = HeadData;
                    while( _TempNode != nullptr)
                    {
                        size_t Temp_Hash = HashFunction(_TempNode->_data) % NewCapacity;
                        //重新计算映射值
                        Node* New_Mapping_location = _NewHashTable[Temp_Hash];
                        if(New_Mapping_location == nullptr)
                        {
                            Node* PushNode = new Node(_TempNode->_data);
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
                            Node* PushNode = new Node(_TempNode->_data);
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
                        Node* _TempNode = _HashTable[i];
                        while(_TempNode!= nullptr)
                        {
                            Node* _Temp_Node_prev = _TempNode;
                            _TempNode = _TempNode->_next;
                            delete _Temp_Node_prev;
                            _Temp_Node_prev = nullptr;
                        }
                    }
                    _size = _New_size;
                    _HashTable.Swap(_NewHashTable);
                    Capacity = NewCapacity;
                    HeadData = _TempHeadNode;
                    PreviousData = _TempPreviousData;
                    //重新映射,按照插入链表顺序
                }
                size_t Temp_Hash = HashFunction(TempVal);
                size_t HashLocationData = Temp_Hash % Capacity;
                //找到映射位置
                Node* _TempNode = _HashTable[HashLocationData];

                Node* PushNode = new Node(TempVal);
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
            bool Pop(const HashTableTypeVal& TempVal)
            {
                //空表判断
                if( Find(TempVal) == nullptr)
                {
                    return false;
                }
                size_t Temp_Hash = HashFunction(TempVal);
                size_t HashLocationData = Temp_Hash % Capacity;
                //找到映射位置
                Node* _TempNode = _HashTable[HashLocationData];
                Node* TempNodeParent = nullptr;
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
            iterator Find(const HashTableTypeVal& TempVal)
            {
                if( _size == 0)
                {
                    return iterator(nullptr);
                }
                else
                {
                    size_t Temp_Hash = HashFunction(TempVal);
                    size_t HashLocationData = Temp_Hash % Capacity;
                    //找到映射位置
                    Node* _TempNode = _HashTable[HashLocationData];
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
            MyTemplate::VectorContainer::Vector<int> _BitSet;
            size_t _size;
        public:
            BitSet() {  ;  }
            BitSet(const size_t& Temp_size)
            {
                _size = 0;
                _BitSet.Resize((Temp_size / 32) + 1,0);
                //多开一个int的空间，防止不够
            }
            void Resize(const size_t& Temp_size)
            {
                _size = 0;
                _BitSet.Resize((Temp_size / 32) + 1,0);
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
    /*############################     Map 容器     ############################*/
    namespace MapContainer
    {
        template <typename MapTypeK,typename MapTypeV>
        class Map
        {
            using KeyValType = MyTemplate::Practicality::Pair<MapTypeK,MapTypeV>;
            struct Key_Val
            {
                const MapTypeK& operator()(const KeyValType& TempKey)
                {
                    return TempKey.first;
                }
            };
            using RBTREE = BaseClassContainer::RBTree <MapTypeK,KeyValType,Key_Val>;
            RBTREE ROOTMap;
        public:
            using iterator = typename RBTREE::iterator;
            using const_iterator = typename RBTREE::const_iterator;
            using reverse_iterator = typename RBTREE::reverse_iterator;
            using const_reverse_iterator = typename RBTREE::const_reverse_iterator;
            
            using Map_iterator = MyTemplate::Practicality::Pair<iterator,bool>;
            ~Map()
            {
                ROOTMap.~RBTree();
            }
            Map& operator=(const Map& Map_Temp)
            {
                if(this != &Map_Temp)
                {
                    ROOTMap = Map_Temp.ROOTMap;
                }
                return *this;
            }
            Map& operator=(Map&& Map_Temp)
            {
                if(this != &Map_Temp)
                {
                    ROOTMap = std::move(Map_Temp.ROOTMap);
                }
                return *this;
            }
            Map()                                                   {  ;                                   }
            Map(const Map& Map_Temp)                                {  ROOTMap = Map_Temp.ROOTMap;         }
            Map(Map&& Map_Temp)                                     {  ROOTMap=std::move(Map_Temp.ROOTMap);}
            Map(const KeyValType& Map_Temp)                         {  ROOTMap.Push(Map_Temp);             }
            Map_iterator Push(const KeyValType& Map_Temp)           {  return ROOTMap.Push(Map_Temp);      }
            Map_iterator Pop(const KeyValType& Map_Temp)            {  return ROOTMap.Pop(Map_Temp);       }
            iterator Find(const KeyValType& Map_Temp)               {  return ROOTMap.Find(Map_Temp);     }
            void middle_order_traversal()                             {  ROOTMap.middle_order_traversal();     }
            void pre_order_traversal()                                {  ROOTMap.pre_order_traversal();        }
            size_t size() const                                     {  return ROOTMap.size();              }
            bool Empty()                                            {  return ROOTMap.Empty();             }
            iterator begin()                                        {  return ROOTMap.begin();             }
            iterator end()                                          {  return ROOTMap.end();               }
            const_iterator cbegin()                                 {  return ROOTMap.cbegin();            }
            const_iterator cend()                                   {  return ROOTMap.cend();              }
            reverse_iterator rbegin()                               {  return ROOTMap.rbegin();            }
            reverse_iterator rend()                                 {  return ROOTMap.rend();              }
            const_reverse_iterator crbegin()                        {  return ROOTMap.crbegin();           }
            const_reverse_iterator crend()                          {  return ROOTMap.crend();             }
            iterator operator[](const KeyValType& Map_Temp)         {  return ROOTMap[Map_Temp];           }
        };
        template <typename UnorderedMapTypeK,typename UnorderedMapTypeV>
        class UnorderedMap
        {
            using KeyValType = MyTemplate::Practicality::Pair<UnorderedMapTypeK,UnorderedMapTypeV>;
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
                    size_t num_One =  MyTemplate::ImitationFunctions::HashImitationFunctions()(TempKey.first);
                    num_One = num_One * 31;
                    size_t num_Two =  MyTemplate::ImitationFunctions::HashImitationFunctions()(TempKey.second);
                    num_Two = num_Two * 31;
                    return (num_One + num_Two);
                }
            };
            using HashTable = BaseClassContainer::HashTable<UnorderedMapTypeK,KeyValType,Key_Val,Hash_Functor>;
            HashTable HashMap;
        public:
            using iterator = typename HashTable::iterator;
            using const_iterator = typename HashTable::const_iterator;
            UnorderedMap()                                      {   ;                               }  
            ~UnorderedMap()                                     {  HashMap.~HashTable();            }
            UnorderedMap(const KeyValType& TempKey)             {  HashMap.Push(TempKey);           }
            bool Push(const KeyValType& TempKey)                {  return HashMap.Push(TempKey);    }
            bool Pop(const KeyValType& TempKey)                 {  return HashMap.Pop(TempKey);     }
            iterator Find(const KeyValType& TempKey)            {  return HashMap.Find(TempKey);    }
            size_t size()                                       {  return HashMap.size();           }
            size_t size() const                                 {  return HashMap.size();           }
            size_t capacity() const                             {  return HashMap.capacity();       } 
            bool Empty()                                        {  return HashMap.Empty();          }
            iterator begin()                                    {  return HashMap.begin();          }
            iterator end()                                      {  return HashMap.end();            }
            const_iterator cbegin()                             {  return HashMap.cbegin();         }
            const_iterator cend()                               {  return HashMap.cend();           }
            iterator operator[](const KeyValType& TempKey)      {  return HashMap[TempKey];         }
        };
    }
    /*############################     Set 容器     ############################*/
    namespace SetContainer
    {
        template <typename SetTypeK>
        class Set
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
            using RBTREE = BaseClassContainer::RBTree<SetTypeK,KeyValType,Key_Val>;
            RBTREE ROOTSet;
        public:
            using iterator = typename RBTREE::iterator;
            using const_iterator = typename RBTREE::const_iterator;
            using reverse_iterator = typename RBTREE::reverse_iterator;
            using const_reverse_iterator = typename RBTREE::const_reverse_iterator;
            
            using Set_iterator = MyTemplate::Practicality::Pair<iterator,bool>;
            Set& operator=(const Set& SetTemp)             
            {  
                if(this!= &SetTemp)                     
                {  
                    ROOTSet = SetTemp.ROOTSet;      
                }  
                return *this; 
            }
            Set& operator=(Set&& SetTemp)
            {
                if(this!= &SetTemp)                     
                {  
                    ROOTSet = std::move(SetTemp.ROOTSet);
                }
                return *this;
            }
            Set()                                               {  ;                                      }
            ~Set()                                              {  ROOTSet.~RBTree();                     }
            Set(const Set& SetTemp)                             {  ROOTSet = SetTemp.ROOTSet;             }
            Set(Set&& SetTemp)                                  {  ROOTSet=std::move(SetTemp.ROOTSet);    }
            Set(const KeyValType& SetTemp)                      {  ROOTSet.Push(SetTemp);                 }
            Set_iterator Push(const KeyValType& SetTemp)        {  return ROOTSet.Push(SetTemp);          }
            Set_iterator Pop(const KeyValType& SetTemp)         {  return ROOTSet.Pop(SetTemp);           }
            iterator Find(const KeyValType& SetTemp)            {  return ROOTSet.Find(SetTemp);          }
            void middle_order_traversal()                         {  ROOTSet.middle_order_traversal();        }    
            void pre_order_traversal()                            {  ROOTSet.pre_order_traversal();           }  
            size_t size() const                                 {  return ROOTSet.size();                 }
            bool Empty()                                        {  return ROOTSet.Empty();                }  
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
        class UnorderedSet
        {
            using KeyValType = UnorderedSetTypeK;
            class Hash_Functor
            {
            public:
                size_t operator()(const KeyValType& TempKey)
                {
                    return MyTemplate::ImitationFunctions::HashImitationFunctions()(TempKey)* 131;
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
            using HashTable = MyTemplate::BaseClassContainer::HashTable<UnorderedSetTypeK,KeyValType,Key_Val,Hash_Functor>;
            HashTable HashSet;
        public:
            using iterator = typename HashTable::iterator;
            using const_iterator = typename HashTable::const_iterator;
            UnorderedSet()                                      {  ;                                     }
            ~UnorderedSet()                                     {   HashSet.~HashTable();                }
            bool Push(const KeyValType& SetTemp)                {  return HashSet.Push(SetTemp);         }
            bool Pop(const KeyValType& SetTemp)                 {  return HashSet.Pop(SetTemp);          }            
            iterator Find(const KeyValType& SetTemp)            {  return HashSet.Find(SetTemp);         }
            size_t size()                                       {  return HashSet.size();                 }
            bool Empty()                                        {  return HashSet.Empty();                }
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
    namespace BloomFilterContainer
    {
        template <typename BloomFilterTypeVal,typename HashFunctorBloomFilter = MyTemplate::Algorithm::HashAlgorithm::HashFunction<BloomFilterTypeVal> >
        class BloomFilter
        {
            HashFunctorBloomFilter   _Hash;
            using BitSet = MyTemplate::BaseClassContainer::BitSet;
            BitSet VectorBitSet;
            size_t _Capacity;
        public:
            BloomFilter()
            {
                _Capacity = 1000;
                VectorBitSet.Resize(_Capacity);
            }
            BloomFilter(const size_t& Temp_Capacity)
            {
                _Capacity = Temp_Capacity;
                VectorBitSet.Resize(_Capacity);
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