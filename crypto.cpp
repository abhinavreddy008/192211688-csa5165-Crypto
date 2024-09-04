#include <stdio.h>
#include <string.h>
void caesar_cipher(char *plaintext, int shift) {
    int i;
    for (i = 0; i < strlen(plaintext); i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
        }
    }
}
int main() {
    char plaintext[100];
    int shift;
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; 
    printf("Enter the shift (1-25): ");
    scanf("%d", &shift);
    caesar_cipher(plaintext, shift); 
    printf("Ciphertext: %s\n", plaintext);
    return 0;
}