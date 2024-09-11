#include <stdio.h>
#include <stdint.h>
#define BLOCK_SIZE 128
#define CONSTANT_128 0x87
#define CONSTANT_64 0x1B

void left_shift_and_xor(uint8_t *block, uint8_t constant) {
    int i;
    uint8_t carry = block[0] >> 7;
    for (i = 0; i < 16; ++i) { 
        block[i] <<= 1;
        if (i < 15 && block[i + 1] & 0x80) {
            block[i] |= 1;
        }
    }
    if (carry) {
        block[15] ^= constant;
    }
}
int main() {
    uint8_t block[16] = {0};
    uint8_t constant = (BLOCK_SIZE == 128) ? CONSTANT_128 : CONSTANT_64;
    left_shift_and_xor(block, constant);
    printf("Subkey: ");
    for (int i = 0; i < 16; ++i) {
        printf("%02X ", block[i]);
    }
    printf("\n");
    return 0;
}
Output:
Subkey: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
