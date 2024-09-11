#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8
void xor_encrypt(const uint8_t *input, uint8_t *output, const uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        output[i] = input[i] ^ key[i];
    }
}
void ecb_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, size_t length, const uint8_t *key) {
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        xor_encrypt(plaintext + i, ciphertext + i, key);
    }
}
void ecb_decrypt(const uint8_t *ciphertext, uint8_t *plaintext, size_t length, const uint8_t *key) {
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        xor_encrypt(ciphertext + i, plaintext + i, key);
    }
}
int main() {
    const uint8_t plaintext[] = "12345678abcdefgh";
    size_t length = sizeof(plaintext);
    
    uint8_t key[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t ciphertext[BLOCK_SIZE * (length / BLOCK_SIZE)];
    uint8_t decrypted[BLOCK_SIZE * (length / BLOCK_SIZE)];
    
    ecb_encrypt(plaintext, ciphertext, length, key);
    ecb_decrypt(ciphertext, decrypted, length, key);
    
    printf("Ciphertext:\n");
    for (size_t i = 0; i < length; ++i) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");
    
    printf("Decrypted Text:\n");
    for (size_t i = 0; i < length; ++i) {
        printf("%c", decrypted[i]);
    }
    printf("\n");
    return 0;
}
Output:
Ciphertext:
00 00 00 00 00 00 00 00 60 41 26 03 EC CD AA 87 01
Decrypted Text:
12345678abcdefgh
