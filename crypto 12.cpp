#include <stdio.h>
#include <string.h>
#define SIZE 2 
void hillCipherEncrypt(int plaintext[], int ciphertext[], int key[SIZE][SIZE], int length) {
    for (int i = 0; i < length; i += SIZE) {
        for (int j = 0; j < SIZE; j++) {
            ciphertext[i + j] = 0;
            for (int k = 0; k < SIZE; k++) {
                ciphertext[i + j] += key[j][k] * plaintext[i + k];
            }
            ciphertext[i + j] %= 26; 
        }
    }
}
void displayCiphertext(int ciphertext[], int length) {
    printf("Ciphertext: ");
    for (int i = 0; i < length; i++) {
        printf("%c", ciphertext[i] + 'A'); 
    }
    printf("\n");
}
int main() {
    char message[] = "MEETMEATTHEUSUALPLACEATTENRATHERTHANEIGHTOCLOCK";
    int plaintext[100];
    int ciphertext[100];
    int key[SIZE][SIZE] = {{3, 3}, {2, 5}}; 
    int length = strlen(message);
        for (int i = 0; i < length; i++) {
        plaintext[i] = message[i] - 'A';
    }
    hillCipherEncrypt(plaintext, ciphertext, key, length);
    displayCiphertext(ciphertext, length);
    
    return 0;
}
