#include "../template_container.hpp"
using namespace template_container;
int main()
{
    {
        map_container::tree_map<int,std::string> m;
        m.push({1,"one"});
        m.push({2,"two"});
        for(auto it=m.begin(); it!=m.end(); ++it)
        {
            std::cout<<it->first<<":"<<it->second<<" ";
        }
    }
    {
        map_container::hash_map<int,std::string,template_container::imitation_functions::hash_imitation_functions,std::hash<std::string>> hm;
        hm.push({1,"one"});
        hm.push({2,"two"});
        for(auto it=hm.begin(); it!=hm.end(); ++it)
        {
            std::cout<<*it<<" ";
        }
    }
    return 0;
}