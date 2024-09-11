#include <iostream>
#include <cstring>
#include <cstdint>

#define BLOCK_SIZE 8
void xor_blocks(uint8_t *dest, const uint8_t *src) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        dest[i] ^= src[i];
    }
}
void ecb_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, const uint8_t *key) {
    std::memcpy(ciphertext, plaintext, BLOCK_SIZE); 
}
void cbc_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, const uint8_t *key, const uint8_t *iv) {
    uint8_t block[BLOCK_SIZE];
    std::memcpy(block, plaintext, BLOCK_SIZE);
    xor_blocks(block, iv);
    ecb_encrypt(block, ciphertext, key);
}
void cfb_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, const uint8_t *key, const uint8_t *iv) {
    uint8_t block[BLOCK_SIZE];
    std::memcpy(block, iv, BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ block[i];
        block[i] = ciphertext[i]; 
    }
}
int main() {
    uint8_t key[BLOCK_SIZE] = {0};
    uint8_t iv[BLOCK_SIZE] = {0};  
    uint8_t plaintext[BLOCK_SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' }; 
    uint8_t ciphertext[BLOCK_SIZE] = {0};
    std::cout << "Plaintext: ";
    for (int i = 0; i < BLOCK_SIZE; i++) {
        std::cout << std::hex << static_cast<int>(plaintext[i]) << " ";
    }
    std::cout << std::endl;
    ecb_encrypt(plaintext, ciphertext, key);
    std::cout << "ECB Ciphertext: ";
    for (int i = 0; i < BLOCK_SIZE; i++) {
        std::cout << std::hex << static_cast<int>(ciphertext[i]) << " ";
    }
    std::cout << std::endl;
    cbc_encrypt(plaintext, ciphertext, key, iv);
    std::cout << "CBC Ciphertext: ";
    for (int i = 0; i < BLOCK_SIZE; i++) {
        std::cout << std::hex << static_cast<int>(ciphertext[i]) << " ";
    }
    std::cout << std::endl;
    cfb_encrypt(plaintext, ciphertext, key, iv);
    std::cout << "CFB Ciphertext: ";
    for (int i = 0; i < BLOCK_SIZE; i++) {
        std::cout << std::hex << static_cast<int>(ciphertext[i]) << " ";
    }
    std::cout << std::endl;
    return 0;
}
Output:
Plaintext: 41 42 43 44 45 46 47 48
ECB Ciphertext: 41 42 43 44 45 46 47 48
CBC Ciphertext: 41 42 43 44 45 46 47 48
CFB Ciphertext: 41 42 43 44 45 46 47 48
