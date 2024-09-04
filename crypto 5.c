#include <stdio.h>
#include <stdbool.h>
bool is_one_to_one(int a) {
    for (int i = 0; i < 26; i++) {
        for (int j = i + 1; j < 26; j++) {
            if ((a * i) % 26 == (a * j) % 26) {
                return false;
            }
        }
    }
    return true;
}
char encrypt(char p, int a, int b) {
    return (a * (p - 'a') + b) % 26 + 'a';
}
char decrypt(char c, int a, int b) {
    int x = (c - 'a' - b) % 26;
    int inv_a = 1; 
    for (int i = 0; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            inv_a = i;
            break;
        }
    }
    return (inv_a * x) % 26 + 'a';
}

int main() {
    int a, b;

    printf("Enter the value of a: ");
    scanf("%d", &a);

    printf("Enter the value of b: ");
    scanf("%d", &b);

    if (!is_one_to_one(a)) {
        printf("a is not one-to-one. Choose a different value.\n");
        return 1;
    }

    char plaintext[100];
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    char ciphertext[strlen(plaintext)];
    for (int i = 0; i < strlen(plaintext); i++) {
        ciphertext[i] = encrypt(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';

    printf("Ciphertext: %s\n", ciphertext);

    char decrypted[strlen(ciphertext)];
    for (int i = 0; i < strlen(ciphertext); i++) {
        decrypted[i] = decrypt(ciphertext[i], a, b);
    }
    decrypted[strlen(ciphertext)] = '\0';

    printf("Decrypted text: %s\n", decrypted);

    return 0;
}