#include <stdio.h>
int extended_gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extended_gcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}
int mod_inverse(int e, int phi) {
    int x, y;
    int gcd = extended_gcd(e, phi, &x, &y);
    if (gcd != 1) {
        printf("No modular inverse\n");
        return -1;
    }
    return (x % phi + phi) % phi;
}
void factorize(int n, int *p, int *q) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            *p = i;
            *q = n / i;
            return;
        }
    }
}
int main() {
    int e = 31;
    int n = 3599;
    int p, q;

    factorize(n, &p, &q);
    printf("p = %d, q = %d\n", p, q);
    int phi = (p - 1) * (q - 1);
    printf("φ(n) = %d\n", phi);

    int d = mod_inverse(e, phi);
    if (d != -1) {
        printf("Private key d = %d\n", d);
    }
    return 0;
}
Output:
p = 59, q = 61
f(n) = 3480
Private key d = 3031
