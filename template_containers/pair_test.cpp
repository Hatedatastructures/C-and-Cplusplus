#include "template_container.hpp"
#include <windows.h>
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
            AVL_Tree_test_pair.push(i); //性能大头
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
        using Vector_pair =  template_container::vector_container::vector<template_container::practicality::pair<size_t,size_t>>;
        template_container::vector_container::vector<Vector_pair> array_vector;
        size_t size = 20000;
        auto t1 = std::chrono::high_resolution_clock::now();
        for(size_t i = 0; i < size; i++)
        {
            Vector_pair temp;
            for(size_t j = 0; j < size; j++)
            {
                temp.push_back(template_container::practicality::pair<size_t,size_t>(j,j));
            }
            array_vector.push_back(std::move(temp));
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::cout << "push_back函数时间：" << std::chrono::duration<double, std::milli>(t2 - t1).count() << std::endl;
    }
    return 0;
}