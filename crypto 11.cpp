#include <stdio.h>
#include <math.h>
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
int main() {
    int n = 25;
    unsigned long long totalKeys = factorial(n);
    double log2TotalKeys = log2((double)totalKeys);
    printf("Total possible keys (ignoring identical keys): %llu\n", totalKeys);
    printf("Approximate power of 2: 2^%.2f\n", log2TotalKeys);
    double uniqueKeysLog2 = log2TotalKeys - 21;
    printf("Approximate number of unique keys (taking symmetries into account): 2^%.2f\n", uniqueKeysLog2);
    return 0;
}
