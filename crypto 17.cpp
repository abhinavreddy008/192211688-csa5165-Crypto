#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define KEY_SIZE 8
#define ROUND_KEY_SIZE 6
#define NUM_ROUNDS 16
const int PC1[] = {57, 49, 41, 33, 25, 17, 9,
                   1, 58, 50, 42, 34, 26, 18,
                   10, 2, 59, 51, 43, 35, 27,
                   19, 11, 3, 60, 52, 44, 36,
                   63, 55, 47, 39, 31, 23, 15,
                   7, 62, 54, 46, 38, 30, 22,
                   14, 6, 61, 53, 45, 37, 29,
                   21, 13, 5, 28, 20, 12, 4};
const int PC2[] = {14, 17, 11, 24, 1, 5,
                   3, 28, 15, 6, 21, 10,
                   23, 19, 12, 4, 26, 8,
                   16, 7, 27, 20, 13, 2,
                   41, 52, 31, 37, 47, 55,
                   30, 40, 51, 45, 33, 48,
                   44, 49, 39, 56, 34, 53,
                   46, 42, 50, 36, 29, 32};
const int SHIFT_COUNT[NUM_ROUNDS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
void permuteKey(const uint8_t *key, uint8_t *permutedKey) {
    memset(permutedKey, 0, 56);
    for (int i = 0; i < 56; ++i) {
        int bit = (key[(PC1[i] - 1) / 8] >> (7 - (PC1[i] - 1) % 8)) & 1;
        permutedKey[i] = bit;
    }
}
void circularLeftShift(uint8_t *key, int bits) {
    uint8_t temp[4] = {0};
    memcpy(temp, key, 4);
    for (int i = 0; i < 4; ++i) {
        key[i] = (temp[i] << (bits % 8)) | (temp[(i + 1) % 4] >> (8 - (bits % 8)));
    }
}
void generateRoundKeys(const uint8_t *key, uint8_t roundKeys[NUM_ROUNDS][ROUND_KEY_SIZE]) {
    uint8_t permutedKey[56];
    permuteKey(key, permutedKey);
    uint8_t C[4] = {0}, D[4] = {0};
    for (int i = 0; i < 28; ++i) {
        C[i / 8] |= (permutedKey[i] << (7 - (i % 8)));
    }
    for (int i = 28; i < 56; ++i) {
        D[(i - 28) / 8] |= (permutedKey[i] << (7 - ((i - 28) % 8)));
    }
    for (int round = 0; round < NUM_ROUNDS; ++round) {
        circularLeftShift(C, SHIFT_COUNT[round]);
        circularLeftShift(D, SHIFT_COUNT[round]);
        for (int i = 0; i < 28; ++i) {
            permutedKey[i] = (C[i / 8] >> (7 - (i % 8))) & 1;
        }
        for (int i = 28; i < 56; ++i) {
            permutedKey[i] = (D[(i - 28) / 8] >> (7 - ((i - 28) % 8))) & 1;
        }
        memset(roundKeys[round], 0, ROUND_KEY_SIZE);
        for (int i = 0; i < 48; ++i) {
            int bit_position = PC2[i] - 1;
            int byte_position = bit_position / 8;
            int bit_mask = 1 << (7 - (bit_position % 8));
            roundKeys[round][i / 8] |= (permutedKey[bit_position] << (7 - (i % 8)));
        }
    }
}
int main() {
    uint8_t key[KEY_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9A, 0xBC, 0xDE, 0xF0}; // Example key
    uint8_t roundKeys[NUM_ROUNDS][ROUND_KEY_SIZE] = {0};
    generateRoundKeys(key, roundKeys);
    for (int i = 0; i < NUM_ROUNDS; ++i) {
        printf("Round Key %d: ", i + 1);
        for (int j = 0; j < ROUND_KEY_SIZE; ++j) {
            printf("%02X ", roundKeys[i][j]);
        }
        printf("\n");
    }
    return 0;
}
Output:
Round Key 1: 1A 02 EF FC 70 72
Round Key 2: 78 AE D1 DB C8 E5
Round Key 3: 54 FC 02 42 CE 99
Round Key 4: 63 A5 5E 9B 35 1D
Round Key 5: 6D C4 8F AB 53 A0
Round Key 6: 72 89 B2 50 6B 27
Round Key 7: BC A8 33 F2 09 9C
Round Key 8: A7 26 1E C1 33 9B
Round Key 9: 20 77 CF AD A7 C1
Round Key 10: 71 55 61 3A C6 47
Round Key 11: C0 C9 F9 5E C5 86
Round Key 12: 95 E3 17 88 64 C9
Round Key 13: 27 1F 83 EE F3 01
Round Key 14: 7B 30 E5 B6 47 6A
Round Key 15: 99 C4 D0 D8 9A 42
Round Key 16: C4 68 5A 49 80 FC
