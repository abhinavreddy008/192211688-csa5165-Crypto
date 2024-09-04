#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void remove_duplicates(char str[]) {
    int len = strlen(str);
    int index = 0;

    for (int i = 0; i < len; i++) {
        int j;
        for (j = 0; j < i; j++) {
            if (str[i] == str[j]) {
                break;
            }
        }
        if (j == i) {
            str[index++] = str[i];
        }
    }
    str[index] = '\0';
}

void create_matrix(char key[], char matrix[SIZE][SIZE]) {
    char used[26] = {0};
    int key_len = strlen(key);
    int x = 0, y = 0;

    for (int i = 0; i < key_len; i++) {
        if (!used[key[i] - 'a']) {
            matrix[x][y++] = key[i];
            used[key[i] - 'a'] = 1;
            if (y == SIZE) {
                y = 0;
                x++;
            }
        }
    }

    for (char ch = 'a'; ch <= 'z'; ch++) {
        if (ch == 'j') continue;  
        if (!used[ch - 'a']) {
            matrix[x][y++] = ch;
            if (y == SIZE) {
                y = 0;
                x++;
            }
        }
    }
}

void format_plaintext(char plaintext[]) {
    int len = strlen(plaintext);
    int index = 0;

    for (int i = 0; i < len; i++) {
        if (plaintext[i] == ' ') continue;

        plaintext[index++] = tolower(plaintext[i]);
    }
    plaintext[index] = '\0';

    for (int i = 0; i < index; i += 2) {
        if (plaintext[i] == plaintext[i + 1]) {
            memmove(plaintext + i + 1, plaintext + i, index - i);
            plaintext[i + 1] = 'x';
            index++;
        }
    }

    if (index % 2 != 0) {
        plaintext[index++] = 'x';  
    }
    plaintext[index] = '\0';
}

void find_position(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'j') ch = 'i';  

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt(char plaintext[], char matrix[SIZE][SIZE], char ciphertext[]) {
    int len = strlen(plaintext);
    int row1, col1, row2, col2;

    for (int i = 0; i < len; i += 2) {
        find_position(matrix, plaintext[i], &row1, &col1);
        find_position(matrix, plaintext[i + 1], &row2, &col2);

        if (row1 == row2) {
           
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
           
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';  
}

int main() {
    char key[50], plaintext[100], ciphertext[100];
    char matrix[SIZE][SIZE];

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  

    remove_duplicates(key);
    create_matrix(key, matrix);
    format_plaintext(plaintext);

    encrypt(plaintext, matrix, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
