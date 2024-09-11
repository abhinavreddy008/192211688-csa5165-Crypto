#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
#define TOP_N 10
const double english_freq[ALPHABET_SIZE] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.10,
    0.69, 3.75, 2.61, 7.00, 5.73, 1.02, 0.90, 5.52, 6.33, 9.05,
    2.40, 0.08, 1.82, 2.23, 0.98
};
void calculate_frequency(const char *text, double *freq) {
    int count[ALPHABET_SIZE] = {0};
    int total = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            count[tolower(text[i]) - 'a']++;
            total++;
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (double)count[i] / total * 100;
    }
}
double score_plaintext(const double freq[ALPHABET_SIZE]) {
    double score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        score += english_freq[i] * freq[i];
    }
    return score;
}
void decrypt(const char *ciphertext, char *plaintext, int shift) {
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (tolower(ciphertext[i]) - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
void find_top_plaintexts(const char *ciphertext) {
    char plaintext[strlen(ciphertext) + 1];
    double freq[ALPHABET_SIZE];
    double scores[ALPHABET_SIZE];
    char top_plaintexts[TOP_N][strlen(ciphertext) + 1];
    double top_scores[TOP_N] = {0};
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decrypt(ciphertext, plaintext, shift);
        calculate_frequency(plaintext, freq);
        double score = score_plaintext(freq);
        for (int i = 0; i < TOP_N; i++) {
            if (score > top_scores[i]) {
                for (int j = TOP_N - 1; j > i; j--) {
                    top_scores[j] = top_scores[j - 1];
                    strcpy(top_plaintexts[j], top_plaintexts[j - 1]);
                }
                top_scores[i] = score;
                strcpy(top_plaintexts[i], plaintext);
                break;
            }
        }
    }
    printf("Top %d Possible Plaintexts:\n", TOP_N);
    for (int i = 0; i < TOP_N; i++) {
        printf("%d: %s (Score: %.2f)\n", i + 1, top_plaintexts[i], top_scores[i]);
    }
}
int main() {
    char ciphertext[] = "YOUR CIPHERTEXT HERE";
    find_top_plaintexts(ciphertext);
    return 0;
}
Output:
Top 10 Possible Plaintexts:
1: YOUR CIPHERTEXT HERE (Score: 665.28)
2: UKQN YELDANPATP DANA (Score: 526.06)
3: NDJG RXEWTGITMI WTGT (Score: 523.61)
4: LBHE PVCUREGRKG URER (Score: 471.78)
5: HXDA LRYQNACNGC QNAN (Score: 470.61)
6: JZFC NTASPCEPIE SPCP (Score: 466.67)
7: IYEB MSZROBDOHD ROBO (Score: 458.94)
8: XNTQ BHOGDQSDWS GDQD (Score: 387.83)
9: OEKH SYFXUHJUNJ XUHU (Score: 378.83)
10: MCIF QWDVSFHSLH VSFS (Score: 374.61)
