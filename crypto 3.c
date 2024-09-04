#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char plaintext[], char key[], char ciphertext[]) {
    int i, j;
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);
    char keyStream[textLen];
    for (i = 0, j = 0; i < textLen; i++, j++) {
        if (j == keyLen) {
            j = 0;
        }
        keyStream[i] = key[j];
    }
    for (i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            if (isupper(plaintext[i])) {
                ciphertext[i] = ((plaintext[i] + keyStream[i]) % 26) + 'A';
            } else {
                ciphertext[i] = ((plaintext[i] + keyStream[i] - 2 * 'a') % 26) + 'a';
            }
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[textLen] = '\0'; 
}

int main() {
    char plaintext[100], key[100], ciphertext[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 
    for (int i = 0; i < strlen(key); i++) {
        key[i] = tolower(key[i]);
    }
    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
