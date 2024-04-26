#pragma once

namespace encrypt
{
    enum DataType{
        ALPHABET = 52,
        UTF8 = 1112064,
        ASCII = 128
    };


    int remap(int, DataType = ASCII);
    int unmap(int, DataType = ASCII);
};