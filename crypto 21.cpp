#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 8
void xor_encrypt(const uint8_t *input, uint8_t *output, const uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; ++i) {
        output[i] = input[i] ^ key[i];
    }
}
void print_bytes(const char *label, const uint8_t *data, size_t length) {
    printf("%s: ", label);
    for (size_t i = 0; i < length; ++i) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
void ecb_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, size_t length, const uint8_t *key) {
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        xor_encrypt(plaintext + i, ciphertext + i, key);
    }
}
void cbc_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, size_t length, const uint8_t *key, const uint8_t *iv) {
    uint8_t prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        uint8_t block[BLOCK_SIZE];
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            block[j] = plaintext[i + j] ^ prev_block[j];
        }
        xor_encrypt(block, ciphertext + i, key);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}
void cfb_encrypt(const uint8_t *plaintext, uint8_t *ciphertext, size_t length, const uint8_t *key, const uint8_t *iv) {
    uint8_t shift_reg[BLOCK_SIZE];
    memcpy(shift_reg, iv, BLOCK_SIZE);
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        uint8_t block[BLOCK_SIZE];
        xor_encrypt(shift_reg, block, key);
        for (int j = 0; j < BLOCK_SIZE; ++j) {
            ciphertext[i + j] = plaintext[i + j] ^ block[j];
        }
        memcpy(shift_reg, ciphertext + i, BLOCK_SIZE);
    }
}
void pad_plaintext(uint8_t *plaintext, size_t *length) {
    size_t padded_length = ((*length / BLOCK_SIZE) + 1) * BLOCK_SIZE;
    uint8_t *padded = (uint8_t *)malloc(padded_length);
    memset(padded, 0, padded_length);
    memcpy(padded, plaintext, *length);
    padded[*length] = 0x80; // Padding bit
    *length = padded_length;
    memcpy(plaintext, padded, *length);
    free(padded);
}
int main() {
    uint8_t plaintext[] = "12345678abcdefgh";
    size_t length = sizeof(plaintext) - 1;
    
    uint8_t key[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    uint8_t ciphertext[BLOCK_SIZE * ((length / BLOCK_SIZE) + 1)];
    uint8_t decrypted[BLOCK_SIZE * ((length / BLOCK_SIZE) + 1)];
    pad_plaintext(plaintext, &length);

    memset(ciphertext, 0, sizeof(ciphertext));
    ecb_encrypt(plaintext, ciphertext, length, key);
    print_bytes("ECB Ciphertext", ciphertext, length);

    memset(decrypted, 0, sizeof(decrypted));
    ecb_encrypt(ciphertext, decrypted, length, key);
    print_bytes("ECB Decrypted", decrypted, length);

    memset(ciphertext, 0, sizeof(ciphertext));
    cbc_encrypt(plaintext, ciphertext, length, key, iv);
    print_bytes("CBC Ciphertext", ciphertext, length);

    memset(decrypted, 0, sizeof(decrypted));
    cbc_encrypt(ciphertext, decrypted, length, key, iv);
    print_bytes("CBC Decrypted", decrypted, length);

    memset(ciphertext, 0, sizeof(ciphertext));
    cfb_encrypt(plaintext, ciphertext, length, key, iv);
    print_bytes("CFB Ciphertext", ciphertext, length);

    memset(decrypted, 0, sizeof(decrypted));
    cfb_encrypt(ciphertext, decrypted, length, key, iv);
    print_bytes("CFB Decrypted", decrypted, length);
    return 0;
}
Output:
ECB Ciphertext: 30 11 76 53 BC 9D FA D7 60 41 26 03 EC CD AA 87 81 23 45 67 89 AB CD EF
ECB Decrypted: 31 32 33 34 35 36 37 38 61 62 63 64 65 66 67 68 80 00 00 00 00 00 00 00
CBC Ciphertext: 30 00 54 60 F8 C8 9C A0 50 41 72 63 14 05 36 27 D1 62 37 04 9D AE FB C8
CBC Decrypted: 31 32 33 34 35 36 37 38 60 50 04 30 A8 98 CC F0 B0 11 76 53 BC 9D FA D7
CFB Ciphertext: 30 00 54 60 F8 C8 9C A0 50 41 72 63 14 05 36 27 D1 62 37 04 9D AE FB C8
CFB Decrypted: 31 32 33 34 35 36 37 38 60 50 04 30 A8 98 CC F0 B0 11 76 53 BC 9D FA D7
