#include <string>
#include "Encrypt/symmetric.hpp"
#include "Encrypt/data_types.hpp"
#include "Encrypt/check.hpp"
#include "omp.h"
#include <algorithm>

#include <iostream>

std::string removeCharacters(std::string str, char ch) {
    std::string new_string = "";
    for(char letter: str)
    {
        if(!letter != 'J')
            new_string += std::string(1,letter);
    }
    return new_string;
}

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

void findPosition(const char matrix[5][5], char ch, int& row, int& col) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (matrix[i][j] == ch) {
                row = i;
                col = j;
                return;
            }
        }
    }
}

std::string encrypt::playfair_cipher_encrypt(std::string plaintext, std::string key, DataType datatype, bool boost) {
    if (key.length() > 24) {
        throw std::runtime_error("Key length must be less than 25");
    }

    // Sanitize and transform key to uppercase
    std::string sanitizedKey;
    for (char c : key) {
        if (std::isalpha(c) && sanitizedKey.find(std::toupper(c)) == std::string::npos) {
            sanitizedKey.push_back(std::toupper(c));
        }
    }
    sanitizedKey = removeCharacters(sanitizedKey, 'J'); // Remove 'J' from the sanitized key

    // Check if sanitized key length is less than 25
    if (sanitizedKey.length() > 25) {
        throw std::runtime_error("Sanitized key length must be less than or equal to 25");
    }

    // Generate the Playfair matrix
    char matrix[5][5];
    int index = 0;

    for (char c : sanitizedKey) {
        matrix[index / 5][index % 5] = c;
        ++index;
    }

    // Fill the remaining matrix cells with the alphabet (excluding 'J')
    std::string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    for (char c : alphabet) {
        if (sanitizedKey.find(c) == std::string::npos) {
            matrix[index / 5][index % 5] = c;
            ++index;
        }
    }

    // Process the plaintext and generate ciphertext
    std::string processedText = "";
    for (size_t i = 0; i < plaintext.length(); i += 2) {
        char first = plaintext[i];
        char second = (i + 1 < plaintext.length()) ? plaintext[i + 1] : 'X'; // Handle odd-length plaintext

        // Ensure both characters are alphabetic and convert to uppercase
        if (std::isalpha(first)) {
            first = std::toupper(first);
        } else {
            throw std::runtime_error("Invalid character encountered in plaintext");
        }
        if (std::isalpha(second)) {
            second = std::toupper(second);
        } else {
            throw std::runtime_error("Invalid character encountered in plaintext");
        }

        int row1, col1, row2, col2;
        findPosition(matrix, first, row1, col1);
        findPosition(matrix, second, row2, col2);

        if (row1 == row2) {
            // Same row: shift columns to the right (wrap around)
            processedText += matrix[row1][(col1 + 1) % 5];
            processedText += matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            // Same column: shift rows downward (wrap around)
            processedText += matrix[(row1 + 1) % 5][col1];
            processedText += matrix[(row2 + 1) % 5][col2];
        } else {
            // Form a rectangle: use the corners of the rectangle
            processedText += matrix[row1][col2];
            processedText += matrix[row2][col1];
        }
    }

    return processedText;
}

std::string encrypt::playfair_cipher_decrypt(std::string ciphertext,std::string key, DataType datatype, bool boost) {
    if (key.length() > 24) {
        throw std::runtime_error("Key length must be less than 25");
    }

    // Sanitize and transform key to uppercase
    std::string sanitizedKey;
    for (char c : key) {
        if (std::isalpha(c) && sanitizedKey.find(std::toupper(c)) == std::string::npos) {
            sanitizedKey.push_back(std::toupper(c));
        }
    }
    sanitizedKey = removeCharacters(sanitizedKey, 'J'); // Remove 'J' from the sanitized key

    // Check if sanitized key length is less than 25
    if (sanitizedKey.length() > 25) {
        throw std::runtime_error("Sanitized key length must be less than or equal to 25");
    }

    // Generate the Playfair matrix
    char matrix[5][5];
    int index = 0;

    for (char c : sanitizedKey) {
        matrix[index / 5][index % 5] = c;
        ++index;
    }

    // Fill the remaining matrix cells with the alphabet (excluding 'J')
    std::string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    for (char c : alphabet) {
        if (sanitizedKey.find(c) == std::string::npos) {
            matrix[index / 5][index % 5] = c;
            ++index;
        }
    }

    std::string decryptedText = "";

    // Decrypt the ciphertext using the Playfair cipher rules
    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        char first = ciphertext[i];
        char second = (i + 1 < ciphertext.length()) ? ciphertext[i + 1] : 'X'; // Handle odd-length ciphertext

        // Ensure both characters are alphabetic and convert to uppercase
        if (std::isalpha(first)) {
            first = std::toupper(first);
        } else {
            throw std::runtime_error("Invalid character encountered in ciphertext");
        }
        if (std::isalpha(second)) {
            second = std::toupper(second);
        } else {
            throw std::runtime_error("Invalid character encountered in ciphertext");
        }

        int row1, col1, row2, col2;
        findPosition(matrix, first, row1, col1);
        findPosition(matrix, second, row2, col2);

        if (row1 == row2) {
            // Same row: shift columns to the left (wrap around)
            decryptedText += matrix[row1][(col1 + 4) % 5];
            decryptedText += matrix[row2][(col2 + 4) % 5];
        } else if (col1 == col2) {
            // Same column: shift rows upward (wrap around)
            decryptedText += matrix[(row1 + 4) % 5][col1];
            decryptedText += matrix[(row2 + 4) % 5][col2];
        } else {
            // Form a rectangle: use the corners of the rectangle
            decryptedText += matrix[row1][col2];
            decryptedText += matrix[row2][col1];
        }
    }

    return decryptedText;
}