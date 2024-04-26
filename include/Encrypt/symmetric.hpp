#pragma once

#include "Encrypt/data_types.hpp"

namespace encrypt{
    std::string caeser_cipher_encrypt(std::string,int,DataType=ASCII,bool = false);
    std::string caeser_cipher_decrypt(std::string,int,DataType=ASCII,bool = false);

    // std::string monoalphabetic_cipher_encrypt(std::string,int[],DataType=ASCII,bool = false);
    // std::string monoalphabetic_cipher_encrypt(std::string,int[],DataType=ASCII,bool = false);
};
