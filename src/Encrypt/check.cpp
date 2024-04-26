#include "Encrypt/check.hpp"
#include <unordered_map>

bool encrypt::check_duplicate(int keys[],int length, bool boost)
{
    std::unordered_map<int,int> mapper;
    for(int i=0;i<length;i++)
    {
        if(mapper[keys[i]] == 0)
        {
            mapper[keys[i]] += 1;
        }
        else
            return false;
    }

    return true;
}