#include <stdio.h>
#include <stdint.h>

static const int PC1[] = {2, 4, 1, 6, 3, 9, 0, 8, 5, 7};
static const int PC2[] = {5, 2, 6, 3, 7, 4, 9, 8};
static const uint64_t KEY = 0x0000FFFFFFFFFFFF;
uint64_t permute(uint64_t input, const int *table, int size) {
    uint64_t result = 0;
    for (int i = 0; i < size; i++) {
        result |= ((input >> (64 - table[i] - 1)) & 1) << (size - 1 - i);
    }
    return result;
}
void generate_subkeys(uint64_t key, uint64_t *subkeys) {
    uint64_t permutedKey = permute(key, PC1, 10);
    uint64_t C = permutedKey >> 10;
    uint64_t D = permutedKey & 0x3FF;
    for (int i = 0; i < 16; i++) {
        C = ((C << 1) | (C >> 9)) & 0x1F;
        D = ((D << 1) | (D >> 9)) & 0x1F;
        uint64_t combined = (C << 5) | D;
        subkeys[i] = permute(combined, PC2, 8);
    }
}
int main() {
    uint64_t subkeys[16];
    generate_subkeys(KEY, subkeys);
    printf("Generated Subkeys:\n");
    for (int i = 0; i < 16; i++) {
        printf("K%d: 0x%08llX\n", i + 1, subkeys[i]);
    }
    return 0;
}
Output:
Generated Subkeys:
K1: 0x00000000
K2: 0x00000000
K3: 0x00000000
K4: 0x00000000
K5: 0x00000000
K6: 0x00000000
K7: 0x00000000
K8: 0x00000000
K9: 0x00000000
K10: 0x00000000
K11: 0x00000000
K12: 0x00000000
K13: 0x00000000
K14: 0x00000000
K15: 0x00000000
K16: 0x00000000
