#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define BLOCK_SIZE 8
void xor_blocks(uint8_t *block1, const uint8_t *block2) {
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        block1[i] ^= block2[i];
    }
}
void des_encrypt(const uint8_t *input, uint8_t *output, const uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        output[i] = input[i] ^ key[i];
    }
}
void cbc_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, size_t length, const uint8_t *key, const uint8_t *iv) {
    uint8_t previous_block[BLOCK_SIZE];
    memcpy(previous_block, iv, BLOCK_SIZE);
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        uint8_t block[BLOCK_SIZE];
        memcpy(block, plaintext + i, BLOCK_SIZE);
        
        xor_blocks(block, previous_block);
        des_encrypt(block, block, key);
        memcpy(ciphertext + i, block, BLOCK_SIZE);
        memcpy(previous_block, block, BLOCK_SIZE);
    }
}
int main() {
    const uint8_t plaintext[] = "This is a test.";
    size_t length = sizeof(plaintext);
    
    uint8_t ciphertext[BLOCK_SIZE * ((length + BLOCK_SIZE - 1) / BLOCK_SIZE)];
    uint8_t key[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    
    cbc_encrypt(plaintext, ciphertext, length, key, iv);
    printf("Ciphertext:\n");
    for (size_t i = 0; i < sizeof(ciphertext); ++i) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");
    return 0;
}
Output:
Ciphertext:
55 4A 2E 17 AD C7 B8 C8 35 49 1F 15 57 18 5B 27
