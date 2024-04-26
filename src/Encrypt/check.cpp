#include "Encrypt/check.hpp"
#include <unordered_map>
#include <iostream>

bool encrypt::check_duplicate(int keys[],int length)
{
    std::unordered_map<int,int> mapper;
    for(int i=0;i<length;i++)
    {
        if(mapper[keys[i]] == 0)
        {
            mapper[keys[i]] += 1;
        }
        else
            return true;
    }

    return false;
}

bool encrypt::check_completeness(int keys[],int length)
{
    // std::cout<<length;
    for(int i=0;i<length;i++)
    {
        if(keys[i] < 0 || keys[i] > length-1)
        {
            return false;
        }
    }

    return true;
}
