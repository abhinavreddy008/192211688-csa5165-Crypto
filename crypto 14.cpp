#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
void encrypt(char* plaintext, int* key, char* ciphertext) {
    int length = strlen(plaintext);
    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            int shift = key[i];
            char offset = islower(plaintext[i]) ? 'a' : 'A';
            ciphertext[i] = ((plaintext[i] - offset + shift) % ALPHABET_SIZE) + offset;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';
}
void decrypt(char* ciphertext, int* key, char* decrypted) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {
            int shift = key[i];
            char offset = islower(ciphertext[i]) ? 'a' : 'A';
            decrypted[i] = ((ciphertext[i] - offset - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + offset;
        } else {
            decrypted[i] = ciphertext[i];
        }
    }
    decrypted[length] = '\0';
}
void find_key(char* ciphertext, char* target_plaintext, int* key) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i]) && isalpha(target_plaintext[i])) {
            char offset = islower(ciphertext[i]) ? 'a' : 'A';
            key[i] = (ciphertext[i] - target_plaintext[i] + ALPHABET_SIZE) % ALPHABET_SIZE;
        } else {
            key[i] = 0;
        }
    }
}
int main() {
    char plaintext[] = "send more money";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[50];
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted ciphertext: %s\n", ciphertext);
    char target_plaintext[] = "cash not needed";
    int new_key[50];
    find_key(ciphertext, target_plaintext, new_key);
    printf("Key for decryption to 'cash not needed': ");
    for (int i = 0; i < strlen(target_plaintext); i++) {
        printf("%d ", new_key[i]);
    }
    printf("\n");
    return 0;
}