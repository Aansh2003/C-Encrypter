#include <string>
#include "Encrypt/symmetric.hpp"
#include "Encrypt/data_types.hpp"
#include "Encrypt/check.hpp"
#include "omp.h"

#include <iostream>

std::string encrypt::caeser_cipher_encrypt(std::string plaintext,int private_key,DataType datatype, bool boost){
    std::string ciphertext (plaintext.length(),' ');
    #pragma omp parallel for if(boost) num_threads(16)
    for(int i=0;i<plaintext.length();i++)
    {
        int remapped = encrypt::remap(int(plaintext[i]),datatype);
        ciphertext[i] = encrypt::unmap((remapped + private_key ) % int(datatype),datatype);
    } 
    return ciphertext;
}

std::string encrypt::caeser_cipher_decrypt(std::string ciphertext, int private_key, DataType datatype, bool boost){
    std::string plaintext(ciphertext.length(),' ');
    #pragma omp parallel for if(boost) num_threads(16)
    for(int i=0;i<ciphertext.length();i++)
    {
        int remapped = encrypt::remap(int(ciphertext[i]),datatype);
        int unmapped = remapped - private_key;
        if(unmapped < 0)
            unmapped += int(datatype);
        plaintext[i] = encrypt::unmap(unmapped,datatype);
    }
    return plaintext;
}

std::string encrypt::monoalphabetic_cipher_encrypt(std::string plaintext,int key[],DataType datatype,bool boost)
{
    if(encrypt::check_duplicate(key,int(datatype)) || !encrypt::check_completeness(key,int(datatype)))
    {
        throw "Invalid key";
    }
        
    std::string ciphertext (plaintext.length(),' ');
    #pragma omp parallel for if(boost) num_threads(16)
    for(int i=0;i<plaintext.length();i++)
    {
        int map = key[encrypt::remap(int(plaintext[i]),datatype)];
        ciphertext[i] = encrypt::unmap(map,datatype);
    }
    return ciphertext;
}

std::string encrypt::monoalphabetic_cipher_decrypt(std::string ciphertext,int key[],DataType datatype,bool boost)
{
    int reverse[int(datatype)];
    for(int i=0;i<int(datatype);i++)
    {
        reverse[key[i]] = i;
    }

    if(encrypt::check_duplicate(key,int(datatype)) || !encrypt::check_completeness(key,int(datatype)))
    {
        throw "Invalid key";
    }
        
    std::string plaintext (ciphertext.length(),' ');
    #pragma omp parallel for if(boost) num_threads(16)
    for(int i=0;i<ciphertext.length();i++)
    {
        int map = reverse[encrypt::remap(int(ciphertext[i]),datatype)];
        plaintext[i] = encrypt::unmap(map,datatype);
    }
    return plaintext;
}