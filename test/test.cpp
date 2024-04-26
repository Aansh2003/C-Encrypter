#include <gtest/gtest.h>
#include "Encrypt/symmetric.hpp"  // Include headers from your library
#include <iostream>

// Test suite for symmetric encryption functions
class SymmetricEncryptionTest : public ::testing::Test {
protected:
    // Set up common resources needed for the test cases
    void SetUp() override {
        // Perform any initialization before each test case
    }

    // Clean up resources after each test case
    void TearDown() override {
        // Perform any cleanup after each test case
    }
};

// Test case to verify encryption and decryption
TEST_F(SymmetricEncryptionTest, EncryptDecrypt) {
    // Arrange
    std::string plaintext(10000000,'a');
    // std::string plaintext = "Goodbyeaaaa";
    std::string key = "hello";
    // Act
    std::string ciphertext = encrypt::caeser_cipher_encrypt(plaintext, 5, encrypt::ALPHABET,false);
    // std::string decrypted_text = encrypt::playfair_cipher_encrypt(ciphertext, key, encrypt::ALPHABET,true);
    // if(plaintext.length()%2==1){
    //     decrypted_text.pop_back();
    // }
    // std::cout<<plaintext<<" "<<decrypted_text;
    // EXPECT_EQ(plaintext, decrypted_text);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
