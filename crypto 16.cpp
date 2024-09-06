#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TEXT 10000
#define ALPHABET_SIZE 26
#define TOP_N 10
char english_frequency[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
void calculate_frequency(const char *text, int *frequency) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (ch >= 'A' && ch <= 'Z') {
            frequency[ch - 'A']++;
        } else if (ch >= 'a' && ch <= 'z') {
            frequency[ch - 'a']++;
        }
    }
}
void sort_by_frequency(int *frequency, char *sorted_letters) {
    int count[ALPHABET_SIZE];
    memcpy(count, frequency, sizeof(int) * ALPHABET_SIZE);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        int max_idx = -1;
        int max_freq = -1;
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (count[j] > max_freq) {
                max_freq = count[j];
                max_idx = j;
            }
        }
        sorted_letters[i] = 'A' + max_idx;
        count[max_idx] = -1; // Mark as used
    }
}
void generate_plaintext(const char *ciphertext, const char *substitution, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (ch >= 'A' && ch <= 'Z') {
            plaintext[i] = substitution[ch - 'A'];
        } else if (ch >= 'a' && ch <= 'z') {
            plaintext[i] = substitution[ch - 'a'] + 32; 
        } else {
            plaintext[i] = ch;
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
void print_top_plaintexts(const char *ciphertext, const char *sorted_cipher_freq, int top_n) {
    char substitution[ALPHABET_SIZE];
    char plaintext[MAX_TEXT];
    for (int n = 0; n < top_n; n++) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            substitution[sorted_cipher_freq[i] - 'A'] = english_frequency[(i + n) % ALPHABET_SIZE];
        }
        generate_plaintext(ciphertext, substitution, plaintext);
        printf("\nPossible Plaintext #%d:\n%s\n", n + 1, plaintext);
    }
}
int main() {
    char ciphertext[MAX_TEXT];
    int frequency[ALPHABET_SIZE] = {0};
    char sorted_cipher_freq[ALPHABET_SIZE];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    calculate_frequency(ciphertext, frequency);
    sort_by_frequency(frequency, sorted_cipher_freq);
    printf("\nTop %d possible plaintexts:\n", TOP_N);
    print_top_plaintexts(ciphertext, sorted_cipher_freq, TOP_N);
    return 0;
}