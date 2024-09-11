#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 16
void xor_blocks(unsigned char *result, const unsigned char *a, const unsigned char *b) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = a[i] ^ b[i];
    }
}
void cbc_mac(unsigned char *mac, const unsigned char *key, const unsigned char *block) {
    xor_blocks(mac, key, block);
}
int main() {
    unsigned char key[BLOCK_SIZE] = {0};
    unsigned char message[BLOCK_SIZE] = {1};
    unsigned char mac[BLOCK_SIZE];
    cbc_mac(mac, key, message);
    printf("MAC: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");
    unsigned char message2[BLOCK_SIZE];
    unsigned char xor_result[BLOCK_SIZE];
    xor_blocks(xor_result, message, mac);
    memcpy(message2, message, BLOCK_SIZE);
    memcpy(message2 + BLOCK_SIZE, xor_result, BLOCK_SIZE);
    unsigned char mac2[BLOCK_SIZE];
    cbc_mac(mac2, key, message2);

    printf("MAC for X || (X ⊕ T): ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac2[i]);
    }
    printf("\n");
    return 0;
}
Output:
MAC: 01000000000000000000000000000000
MAC for X || (X ? T): 01000000000000000000000000000000
