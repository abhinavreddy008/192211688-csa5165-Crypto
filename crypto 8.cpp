#include <stdio.h>
#include <string.h>
#include <ctype.h>
void generateCipherSequence(const char *keyword, char *cipherSeq) {
    int used[26] = {0};
    int j = 0;
    for (int i = 0; keyword[i]; i++) {
        char c = toupper(keyword[i]);
        if (isalpha(c) && !used[c - 'A']) {
            cipherSeq[j++] = c;
            used[c - 'A'] = 1;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (!used[i]) cipherSeq[j++] = 'A' + i;
    }
    cipherSeq[j] = '\0';
}
void encryptMonoalphabetic(char *text, const char *cipherSeq) {
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            text[i] = cipherSeq[toupper(text[i]) - 'A'];
        }
    }
}
int main() {
    char keyword[] = "CIPHER";
    char plaintext[100], cipherSeq[27];
    generateCipherSequence(keyword, cipherSeq);
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    encryptMonoalphabetic(plaintext, cipherSeq);
    printf("Encrypted string: %s\n", plaintext);
    return 0;
}
