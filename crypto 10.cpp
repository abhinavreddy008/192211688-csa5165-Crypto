#include <stdio.h>
#include <string.h>

#define SIZE 5

char matrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};
void findPosition(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I';
    for (*row = 0; *row < SIZE; (*row)++)
        for (*col = 0; *col < SIZE; (*col)++)
            if (matrix[*row][*col] == ch) return;
}
void encryptDigraph(char digraph[2], char cipher[2]) {
    int r1, c1, r2, c2;
    findPosition(digraph[0], &r1, &c1);
    findPosition(digraph[1], &r2, &c2);
    if (r1 == r2) {
        cipher[0] = matrix[r1][(c1 + 1) % SIZE];
        cipher[1] = matrix[r2][(c2 + 1) % SIZE];
    }
    else if (c1 == c2) {
        cipher[0] = matrix[(r1 + 1) % SIZE][c1];
        cipher[1] = matrix[(r2 + 1) % SIZE][c2];
    }
    else {
        cipher[0] = matrix[r1][c2];
        cipher[1] = matrix[r2][c1];
    }
}
void playfairEncrypt(char *message) {
    char digraph[2], cipher[2];
    int len = strlen(message);
    for (int i = 0; i < len; i++) {
        if (message[i] == 'J') message[i] = 'I';
        if (i + 1 < len && message[i] == message[i + 1]) {
            memmove(message + i + 2, message + i + 1, len - i - 1);
            message[i + 1] = 'X';
            len++;
        }
    }
    for (int i = 0; i < len; i += 2) {
        digraph[0] = message[i];
        digraph[1] = (i + 1 < len) ? message[i + 1] : 'X';
        encryptDigraph(digraph, cipher);
        printf("%c%c", cipher[0], cipher[1]);
    }
    printf("\n");
}
int main() {
    char message[] = "MUSTSEEYOUOVERCADOGANWESTCOMINGATONCE";

    printf("Original Message: %s\n", message);
    printf("Encrypted Message: ");
    playfairEncrypt(message);

    return 0;
}
