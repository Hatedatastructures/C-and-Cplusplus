#include "template_container.hpp"
#include <windows.h>
namespace imitation_functions
{
    using map_pair = template_container::practicality::pair<size_t,size_t>;
    class comparators       //map比较器
    {   
    public:
        bool operator()(const map_pair& a,const map_pair& b)
        {
            return a.first < b.first;
        }
    };
}
int main()
{
    {
        //性能测试
        SetConsoleOutputCP(CP_UTF8);
        /*                   pair 类型                */
        template_container::tree_container::avl_tree<size_t,int> AVL_Tree_test_pair;
        template_container::vector_container::vector<template_container::practicality::pair<size_t,int>> AVL_Tree_array_pair;
        size_t size = 100000;
        for(size_t i = 0; i < size; i++)
        {
            AVL_Tree_array_pair.push_back(template_container::practicality::pair<size_t,int>(std::move(i),std::move(0)));
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        for(auto& i : AVL_Tree_array_pair)
        {
            AVL_Tree_test_pair.push(i); //性能大头,优化？
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << "插入个数:" << AVL_Tree_test_pair.size()  << " " << " 插入时间:" << std::chrono::duration<double, std::milli>(t2 - t1).count() << std::endl;

        /*                  非pair 类型               */
        template_container::tree_container::avl_tree<size_t,int> AVL_Tree_test;
        template_container::vector_container::vector<size_t> AVL_Tree_array;
        for(size_t j = 0; j < size ; j++)
        {
            AVL_Tree_array.push_back(j);
        }
        auto t3 = std::chrono::high_resolution_clock::now();
        for(auto& j : AVL_Tree_array)
        {
            AVL_Tree_test.push(j);
        }
        auto t4 = std::chrono::high_resolution_clock::now();
        std::cout << "插入个数:" << AVL_Tree_test.size()  << " " << " 插入时间:" <<  std::chrono::duration<double, std::milli>(t4 - t3).count()  << std::endl;
    }
    {
        //尝试构建线程池来测试给个容器性能开销
        using vector_pair =  template_container::vector_container::vector<template_container::practicality::pair<size_t,size_t>>;
        template_container::vector_container::vector<vector_pair> array_vector;
        size_t size = 20000;
        auto t1 = std::chrono::high_resolution_clock::now();
        for(size_t i = 0; i < size; i++)
        {
            vector_pair temp;
            for(size_t j = 0; j < size; j++)
            {
                temp.push_back(template_container::practicality::pair<size_t,size_t>(j,j));
            }
            array_vector.push_back(std::move(temp));
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << "push_back优化函数时间：" << std::chrono::duration<double, std::milli>(t2 - t1).count() << std::endl;
    }
    {
        //map性能测试 优化；
        using map_pair = template_container::practicality::pair<size_t,size_t>;
        using map_string = template_container::string_container::string;
        using map_data = template_container::practicality::pair<map_pair,map_string>;
        template_container::map_container::tree_map<map_pair,map_string,imitation_functions::comparators> map_pair_test;
        size_t size = 100000;
        template_container::vector_container::vector<map_pair> map_pair_array;
        template_container::vector_container::vector<map_string> map_string_array;
        template_container::vector_container::vector<map_data> map_data_array;
        for(size_t i = 0; i < size; i++)
        {
            map_pair_array.push_back(map_pair(i,i));
            map_string_array.push_back(map_string("hello world"));
            map_data_array.push_back(map_data(std::move(map_pair_array[i]),std::move(map_string_array[i])));
        }
        auto t0 = std::chrono::high_resolution_clock::now();
        for(size_t j = 0; j < size; j++)
        {
            map_pair_test.push(std::move(map_data_array[j]));
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "插入个数:" << map_pair_test.size() << " " << "优化插入时间:" << std::chrono::duration<double, std::milli>(t1 - t0).count() << std::endl;
        //未优化；
        template_container::map_container::tree_map<map_pair,map_string,imitation_functions::comparators>  no_optimized_map;
        auto t2 = std::chrono::high_resolution_clock::now();
        for(size_t k = 0; k < size; k++)
        {
            no_optimized_map.push(map_data_array[k]);
        }
        auto t3 = std::chrono::high_resolution_clock::now();
        std::cout << "插入个数:" << no_optimized_map.size() << " " << "未优化插入时间:" << std::chrono::duration<double, std::milli>(t3 - t2).count() << std::endl;
        //时间为什么一样？
    }
    return 0;
}