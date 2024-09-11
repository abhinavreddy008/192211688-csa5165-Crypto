#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 2 
void matrix_multiply(int a[MATRIX_SIZE][MATRIX_SIZE], int b[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += a[i][k] * b[k][j];
                result[i][j] %= 26;
            }
        }
    }
}
int matrix_inverse(int key[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    det = (det % 26 + 26) % 26;
    int inv_det = 0;
    for (int i = 1; i < 26; i++) {
        if ((det * i) % 26 == 1) {
            inv_det = i;
            break;
        }
    }
    if (inv_det == 0) return -1;
    inverse[0][0] = key[1][1] * inv_det % 26;
    inverse[1][1] = key[0][0] * inv_det % 26;
    inverse[0][1] = -key[0][1] * inv_det % 26;
    inverse[1][0] = -key[1][0] * inv_det % 26;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            inverse[i][j] = (inverse[i][j] % 26 + 26) % 26;
        }
    }
    return 0;
}
void encrypt(int plaintext[MATRIX_SIZE][MATRIX_SIZE], int key[MATRIX_SIZE][MATRIX_SIZE], int ciphertext[MATRIX_SIZE][MATRIX_SIZE]) {
    matrix_multiply(plaintext, key, ciphertext);
}
void decrypt(int ciphertext[MATRIX_SIZE][MATRIX_SIZE], int key[MATRIX_SIZE][MATRIX_SIZE], int plaintext[MATRIX_SIZE][MATRIX_SIZE]) {
    int key_inverse[MATRIX_SIZE][MATRIX_SIZE];
    if (matrix_inverse(key, key_inverse) != 0) {
        printf("Inverse matrix calculation failed.\n");
        return;
    }
    matrix_multiply(ciphertext, key_inverse, plaintext);
}
int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {{6, 24}, {1, 16}};
    int plaintext[MATRIX_SIZE][MATRIX_SIZE] = {{0, 1}, {2, 3}}; 
    int ciphertext[MATRIX_SIZE][MATRIX_SIZE];
    int decrypted[MATRIX_SIZE][MATRIX_SIZE];
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", ciphertext[i][j]);
        }
        printf("\n");
    }
    decrypt(ciphertext, key, decrypted);
    printf("Decrypted:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", decrypted[i][j]);
        }
        printf("\n");
    }
    return 0;
}
Output:
Ciphertext:
1 16
15 18
Inverse matrix calculation failed.
Decrypted:
4201264 0
16 0
