#include <stdio.h>
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}
int matrixDeterminantMod26(int matrix[2][2]) {
    int det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    return (det % 26 + 26) % 26; 
}
void inverseMatrixMod26(int matrix[2][2], int invMatrix[2][2]) {
    int det = matrixDeterminantMod26(matrix);
    int invDet = modInverse(det, 26);

    if (invDet == -1) {
        printf("The key matrix is not invertible mod 26.\n");
        return;
    }
    invMatrix[0][0] = (matrix[1][1] * invDet) % 26;
    invMatrix[0][1] = (-matrix[0][1] * invDet) % 26;
    invMatrix[1][0] = (-matrix[1][0] * invDet) % 26;
    invMatrix[1][1] = (matrix[0][0] * invDet) % 26;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (invMatrix[i][j] < 0) {
                invMatrix[i][j] += 26;
            }
        }
    }
}
void multiplyMatrixMod26(int matrix1[2][2], int matrix2[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] %= 26;
        }
    }
}
void printMatrix(int matrix[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int main() {
    int plaintext[2][2] = {{7, 8}, {11, 12}}; 
    int ciphertext[2][2] = {{19, 7}, {3, 23}}; 
    int invPlaintext[2][2];
    inverseMatrixMod26(plaintext, invPlaintext);
    printf("Inverse of the plaintext matrix (mod 26):\n");
    printMatrix(invPlaintext);
    int keyMatrix[2][2];
    multiplyMatrixMod26(invPlaintext, ciphertext, keyMatrix);

    printf("\nRecovered key matrix:\n");
    printMatrix(keyMatrix);

    return 0;
}
