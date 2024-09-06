#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
const double ENGLISH_FREQ[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};
void calculate_letter_frequency(const char *text, double freq[]) {
    int letter_count[ALPHABET_SIZE] = {0};
    int total_letters = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char letter = tolower(text[i]);
            letter_count[letter - 'a']++;
            total_letters++;
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (double)letter_count[i] / total_letters * 100;
    }
}
void decrypt(char *result, const char *ciphertext, int key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            result[i] = (ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            result[i] = ciphertext[i];
        }
    }
    result[strlen(ciphertext)] = '\0';
}
double calculate_fitness(const double freq[]) {
    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += (freq[i] - ENGLISH_FREQ[i]) * (freq[i] - ENGLISH_FREQ[i]);
    }
    return score;
}
typedef struct {
    char plaintext[1024];
    double fitness;
} DecryptedText;
int compare(const void *a, const void *b) {
    DecryptedText *textA = (DecryptedText *)a;
    DecryptedText *textB = (DecryptedText *)b;
    return (textA->fitness > textB->fitness) - (textA->fitness < textB->fitness);
}
int main() {
    char ciphertext[1024];
    int topN;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    printf("How many top plaintexts would you like to see? ");
    scanf("%d", &topN);
    DecryptedText results[ALPHABET_SIZE];
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        char decrypted[1024];
        double freq[ALPHABET_SIZE];
        decrypt(decrypted, ciphertext, key);
        calculate_letter_frequency(decrypted, freq);
        double fitness = calculate_fitness(freq);

        strcpy(results[key].plaintext, decrypted);
        results[key].fitness = fitness;
    }
    qsort(results, ALPHABET_SIZE, sizeof(DecryptedText), compare);
    printf("\nTop %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        printf("%2d. Plaintext: %s\n", i + 1, results[i].plaintext);
    }
    return 0;
}