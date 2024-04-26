#include "Encrypt/data_types.hpp"

int encrypt::remap(int current_key, DataType datatype)
{
    if(datatype==ALPHABET)
    {
        int remap = 0;
        if(current_key<91 && current_key > 64)
        {
            remap = current_key - 65;
        }
        else if(current_key > 96 && current_key < 123)
        {
            remap = current_key - 71;
        }
        else throw "Invalid key received for datatype";
        return remap;
    }
    return current_key;
}

int encrypt::unmap(int current_key, DataType datatype)
{
    if(datatype==ALPHABET)
    {
        int remap = 0;
        if(current_key<26 && current_key > -1)
        {
            remap = current_key + 65;
        }
        else if(current_key > 25 && current_key < 52)
        {
            remap = current_key + 71;
        }
        else throw "Invalid key received for datatype";
        return remap;
    }
    return current_key;
}