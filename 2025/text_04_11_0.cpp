#include <iostream>
#include <cstring>
//模拟实现vector
namespace wang
{
    template <typename vector_t>
    class vector
    {
        public:
            typedef vector_t*       iterator;
            typedef const vector_t* const_iterator;
            typedef vector_t*       reverse_iterator;
            typedef const vector_t* const_reverse_iterator;
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
            size_t size_v()
            {
                return _size_pointer - _data_pointer;
            }
            size_t capacity_v()
            {
                return _capacity_pointer - _data_pointer;
            }
            vector()
            {
                _data_pointer = nullptr;
                _size_pointer = nullptr;
                _capacity_pointer = nullptr;
            }
            vector(const size_t& sum_size , const vector_t& data = vector_t())
            :_data_pointer(new vector_t[sum_size]),_size_pointer(_data_pointer + sum_size)
            ,_capacity_pointer(_data_pointer + sum_size)
            {
                for(size_t i = 0;i < sum_size;i++)
                {
                    _data_pointer[i] = data;
                }
            }
            
            vector(const vector<vector_t>& temp_data)
            {
                vector <vector_t> temp_data_copy(temp_data._size_pointer - temp_data._data_pointer , *temp_data._data_pointer);
                swap_v(temp_data);
            }
            ~vector()
            {
                delete[]_data_pointer;
                _data_pointer = nullptr;
                _size_pointer = nullptr;
                _data_pointer = nullptr;
            }
            void swap_v(vector<vector_t>& temp_data)
            {
                std::swap(_data_pointer, temp_data._data_pointer);
                std::swap(_size_pointer, temp_data._size_pointer);
                std::swap(_capacity_pointer, temp_data._capacity_pointer);
            }
            iterator erase(iterator pos)
            {
                //删除元素
                iterator temp = pos + 1;
                while (temp != _size_pointer)
                {
                    //(temp-1)就是pos的位置，从pos位置开始覆盖，覆盖到倒数第1个结束，最后一个会被--屏蔽掉
                    *(temp-1) = temp;
                    temp++;
                }
                --_size_pointer;
                return pos;
            }
            friend std::ostream& operator<<(std::ostream& vector_ostream,vector<vector_t>& Dynamic_arrays_data);
            vector_t& operator[](const size_t& _size_operator)
            {
                return _data_pointer[_size_operator];
            }
            const vector_t& operator[](const size_t& _size_operator)const 
            {
                return _data_pointer[_size_operator];
            }
    };
    template <typename vector_t>
    std::ostream& operator<<(std::ostream& vector_ostream, vector<vector_t>& Dynamic_arrays_data)
    {
        for(typename vector<vector_t>::const_iterator Output_iterators = Dynamic_arrays_data.begin();Output_iterators != Dynamic_arrays_data.end();Output_iterators++)
        {
            vector_ostream << *Output_iterators;
        }
    }
}
int main()
{
    wang::vector<int> test(5,1);
    for(auto i: test)
    {
        std::cout << i << " ";
    }
    std::cout << test << std::endl;
    return 0;
}