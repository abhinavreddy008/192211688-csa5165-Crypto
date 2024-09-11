#include <stdio.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
void encrypt_affine(const char *plaintext, char *ciphertext, int a, int b) {
    int i = 0;
    while (plaintext[i] != '\0') {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int p = plaintext[i] - base;
            ciphertext[i] = (a * p + b) % ALPHABET_SIZE + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
        i++;
    }
    ciphertext[i] = '\0';
}
void decrypt_affine(const char *ciphertext, char *plaintext, int a, int b) {
    int i = 0;
    int a_inv = 0;
    for (int t = 0; t < ALPHABET_SIZE; t++) {
        if ((a * t) % ALPHABET_SIZE == 1) {
            a_inv = t;
            break;
        }
    }
    while (ciphertext[i] != '\0') {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int c = ciphertext[i] - base;
            plaintext[i] = (a_inv * (c - b + ALPHABET_SIZE)) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
        i++;
    }
    plaintext[i] = '\0';
}
int main() {
    char plaintext[] = "HELLO WORLD";
    char ciphertext[sizeof(plaintext)];
    char decrypted[sizeof(plaintext)];
    int a = 5;
    int b = 8; 
    encrypt_affine(plaintext, ciphertext, a, b);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt_affine(ciphertext, decrypted, a, b);
    printf("Decrypted: %s\n", decrypted);
    return 0;
}
Output:
Ciphertext: RCLLA OAPLX
Decrypted: HELLO WORLD
