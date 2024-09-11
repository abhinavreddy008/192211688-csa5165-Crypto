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
void calculate_frequency(const char *ciphertext, double *freq) {
    int count[ALPHABET_SIZE] = {0};
    int total = 0;
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            count[tolower(ciphertext[i]) - 'a']++;
            total++;
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (double)count[i] / total * 100;
    }
}
void decrypt(const char *ciphertext, char *plaintext, int shift) {
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (tolower(ciphertext[i]) - 'a' + shift) % ALPHABET_SIZE;
            if (plaintext[i] < 0) plaintext[i] += ALPHABET_SIZE;
            plaintext[i] += base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
void generate_plaintexts(const char *ciphertext) {
    char plaintext[strlen(ciphertext) + 1];
    for (int shift = 0; shift < TOP_N; shift++) {
        decrypt(ciphertext, plaintext, shift);
        printf("Possible Plaintext %d: %s\n", shift + 1, plaintext);
    }
}
int main() {
    char ciphertext[] = "YOUR CIPHERTEXT HERE"; 
    printf("Ciphertext: %s\n", ciphertext);
    generate_plaintexts(ciphertext);
    return 0;
}
Output:
Ciphertext: YOUR CIPHERTEXT HERE
Possible Plaintext 1: YOUR CIPHERTEXT HERE
Possible Plaintext 2: ZPVS DJQIFSUFYU IFSF
Possible Plaintext 3: AQWT EKRJGTVGZV JGTG
Possible Plaintext 4: BRXU FLSKHUWHAW KHUH
Possible Plaintext 5: CSYV GMTLIVXIBX LIVI
Possible Plaintext 6: DTZW HNUMJWYJCY MJWJ
Possible Plaintext 7: EUAX IOVNKXZKDZ NKXK
Possible Plaintext 8: FVBY JPWOLYALEA OLYL
Possible Plaintext 9: GWCZ KQXPMZBMFB PMZM
Possible Plaintext 10: HXDA LRYQNACNGC QNAN
