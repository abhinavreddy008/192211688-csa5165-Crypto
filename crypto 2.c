#include <stdio.h>
#include <string.h>
void encrypt(char *plaintext, char *key) {
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = key[plaintext[i] - 'a'];
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = key[plaintext[i] - 'A'] - 'a' + 'A';
        }
    }
}
void decrypt(char *ciphertext, char *key) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            ciphertext[i] = key[ciphertext[i] - 'a'] - 'a' + 'a';
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            ciphertext[i] = key[ciphertext[i] - 'A'] - 'A' + 'A';
        }
    }
}
int main() {
    char plaintext[100];
    char key[26] = "zyxwvutsrqponmlkjihgfedcba"; 
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; 
    encrypt(plaintext, key);
    printf("Ciphertext: %s\n", plaintext);
    decrypt(plaintext, key);
    printf("Decrypted text: %s\n", plaintext);
    return 0;
}