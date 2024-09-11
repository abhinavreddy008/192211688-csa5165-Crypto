#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 10 
#define IV_SIZE 8 

void generateKeys(const uint8_t *key, uint8_t *k1, uint8_t *k2) {
    memcpy(k1, key, KEY_SIZE / 2);  
    memcpy(k2, key + KEY_SIZE / 2, KEY_SIZE / 2);
}
uint8_t sdes_encrypt(uint8_t block, const uint8_t *key) {
    return block ^ key[0];
}
void xor_blocks(uint8_t *block, const uint8_t *iv, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        block[i] ^= iv[i];
    }
}
void print_bytes(const char *label, const uint8_t *data, size_t length) {
    printf("%s: ", label);
    for (size_t i = 0; i < length; ++i) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
void cbc_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, size_t length, const uint8_t *key, const uint8_t *iv) {
    uint8_t k1[KEY_SIZE / 2], k2[KEY_SIZE / 2];
    generateKeys(key, k1, k2);
    uint8_t prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        uint8_t block[BLOCK_SIZE];
        memcpy(block, plaintext + i, BLOCK_SIZE);
        xor_blocks(block, prev_block, BLOCK_SIZE);
        ciphertext[i] = sdes_encrypt(block[0], k1);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}
void cbc_decrypt(const uint8_t *ciphertext, uint8_t *plaintext, size_t length, const uint8_t *key, const uint8_t *iv) {
    uint8_t k1[KEY_SIZE / 2], k2[KEY_SIZE / 2];
    generateKeys(key, k1, k2);
    uint8_t prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        uint8_t block[BLOCK_SIZE];
        uint8_t decrypted_block = sdes_encrypt(ciphertext[i], k1);
        block[0] = decrypted_block;
        xor_blocks(block, prev_block, BLOCK_SIZE);
        memcpy(plaintext + i, block, BLOCK_SIZE);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}
int main() {
    uint8_t plaintext[] = {0x00, 0x01, 0x02, 0x03};
    uint8_t key[KEY_SIZE] = {0x01, 0x11, 0x01, 0x11, 0x11};
    uint8_t iv[IV_SIZE] = {0x0A, 0x0A};
    size_t length = sizeof(plaintext);
    uint8_t ciphertext[length];
    uint8_t decrypted[length];

    cbc_encrypt(plaintext, ciphertext, length, key, iv);
    print_bytes("Ciphertext", ciphertext, length);

    cbc_decrypt(ciphertext, decrypted, length, key, iv);
    print_bytes("Decrypted", decrypted, length);

    return 0;
}
Output:
ECB Ciphertext: 30 11 76 53 BC 9D FA D7 60 41 26 03 EC CD AA 87 81 23 45 67 89 AB CD EF
ECB Decrypted: 31 32 33 34 35 36 37 38 61 62 63 64 65 66 67 68 80 00 00 00 00 00 00 00
CBC Ciphertext: 30 00 54 60 F8 C8 9C A0 50 41 72 63 14 05 36 27 D1 62 37 04 9D AE FB C8
CBC Decrypted: 31 32 33 34 35 36 37 38 60 50 04 30 A8 98 CC F0 B0 11 76 53 BC 9D FA D7
CFB Ciphertext: 30 00 54 60 F8 C8 9C A0 50 41 72 63 14 05 36 27 D1 62 37 04 9D AE FB C8
CFB Decrypted: 31 32 33 34 35 36 37 38 60 50 04 30 A8 98 CC F0 B0 11 76 53 BC 9D FA D7
