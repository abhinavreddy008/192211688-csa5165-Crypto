#include <stdio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int main() {
    int n = 3599;
    int m = 120;
    int factor = gcd(m, n);
    if (factor > 1 && factor < n) {
        printf("Common factor: %d\n", factor);
        printf("Other factor: %d\n", n / factor);
    } else {
        printf("No useful factor found.\n");
    }
    return 0;
}
Output:
No useful factor found.
