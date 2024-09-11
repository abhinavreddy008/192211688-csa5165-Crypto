#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 
#define KEY_SIZE 10   
#define COUNTER_SIZE 8 
uint8_t sdes_encrypt(uint8_t block, const uint8_t *key) {
    return block ^ key[0];
}
void increment_counter(uint8_t *counter) {
    for (int i = COUNTER_SIZE - 1; i >= 0; --i) {
        if (++counter[i] != 0) break;
    }
}
void ctr_encrypt_decrypt(const uint8_t *input, uint8_t *output, size_t length, const uint8_t *key, uint8_t *counter) {
    uint8_t ctr_block[BLOCK_SIZE];
    
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(ctr_block, counter, BLOCK_SIZE);
        uint8_t encrypted_ctr_block = sdes_encrypt(ctr_block[0], key);

        for (int j = 0; j < BLOCK_SIZE && i + j < length; ++j) {
            output[i + j] = input[i + j] ^ encrypted_ctr_block;
        }

        increment_counter(counter);
    }
}
void print_bytes(const char *label, const uint8_t *data, size_t length) {
    printf("%s: ", label);
    for (size_t i = 0; i < length; ++i) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}
int main() {
    uint8_t plaintext[] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x04};
    uint8_t key[KEY_SIZE] = {0x01, 0x11, 0x01, 0x11, 0x11};
    uint8_t counter[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    size_t length = sizeof(plaintext);
    uint8_t ciphertext[length];
    uint8_t decrypted[length];

    ctr_encrypt_decrypt(plaintext, ciphertext, length, key, counter);
    print_bytes("Ciphertext", ciphertext, length);

    memset(counter, 0, BLOCK_SIZE);
    ctr_encrypt_decrypt(ciphertext, decrypted, length, key, counter);
    print_bytes("Decrypted", decrypted, length);

    return 0;
}
Output:
Ciphertext: 01 00 01 03 01 05
Decrypted: 00 01 00 02 00 04
