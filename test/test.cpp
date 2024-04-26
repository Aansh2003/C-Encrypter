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
    int key[] = {35, 23, 47, 22, 45, 44, 43, 37, 50, 51, 5, 3, 9, 30, 41, 7, 26, 0, 40, 6, 19, 17, 25, 28, 46, 14, 4, 24, 42, 10, 16, 21, 48, 29, 36, 13, 31, 20, 34, 11, 49, 1, 39, 33, 27, 8, 32, 12, 2, 18, 15, 38};

    // Act
    std::string ciphertext = encrypt::monoalphabetic_cipher_encrypt(plaintext, key, encrypt::ALPHABET,true);
    std::string decrypted_text = encrypt::monoalphabetic_cipher_decrypt(ciphertext, key, encrypt::ALPHABET,true);

    // Assert
    EXPECT_EQ(plaintext, decrypted_text);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
