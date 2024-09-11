#include <stdio.h>
#include <ctype.h>
#define MAX_LENGTH 100
void encrypt_vigenere(const char *plaintext, const int *key, char *ciphertext, int key_length) {
    int i = 0;
    while (plaintext[i] != '\0') {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int shift = key[i % key_length];
            ciphertext[i] = (plaintext[i] - base + shift) % 26 + base;
        } else {
            ciphertext[i] = plaintext[i]; 
        }
        i++;
    }
    ciphertext[i] = '\0'; 
}
int main() {
    char plaintext[MAX_LENGTH] = "HELLO WORLD";
    int key[] = {3, 19, 5};
    int key_length = sizeof(key) / sizeof(key[0]);
    char ciphertext[MAX_LENGTH];
    encrypt_vigenere(plaintext, key, ciphertext, key_length);
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}
Output:
Plaintext: HELLO WORLD
Ciphertext: KXQOH ZHWOW
