#include <stdio.h>
#include <string.h>
#define KEY_SIZE 5
void decodePlayfair(const char *code) {
    char key[KEY_SIZE][KEY_SIZE] = {
        {'K', 'X', 'J', 'E', 'Y'},
        {'U', 'R', 'B', 'E', 'Z'},
        {'W', 'H', 'Y', 'F', 'S'},
        {'A', 'C', 'D', 'G', 'I'},
        {'M', 'N', 'O', 'P', 'Q'}
    };
    for (int i = 0; i < strlen(code); i += 2) {
        char first = code[i], second = code[i + 1];
        int row1, col1, row2, col2;
        for (int r = 0; r < KEY_SIZE; r++) {
            for (int c = 0; c < KEY_SIZE; c++) {
                if (key[r][c] == first) { row1 = r; col1 = c; }
                if (key[r][c] == second) { row2 = r; col2 = c; }
            }
        }
        if (row1 == row2) {
            printf("%c%c", key[row1][(col1 + 4) % KEY_SIZE], key[row2][(col2 + 4) % KEY_SIZE]);
        } else if (col1 == col2) { // Same column
            printf("%c%c", key[(row1 + 4) % KEY_SIZE][col1], key[(row2 + 4) % KEY_SIZE][col2]);
        } else { // Rectangle
            printf("%c%c", key[row1][col2], key[row2][col1]);
        }
    }
    printf("\n");
}
int main() {
    char code[] = "KSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    printf("Decoded Message: ");
    decodePlayfair(code);
    return 0;
}
