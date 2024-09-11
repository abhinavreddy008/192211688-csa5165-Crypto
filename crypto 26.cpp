#include <stdio.h>
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
int main() {
    long long p = 61, q = 53; 
    long long n = p * q;    
    long long phi = (p - 1) * (q - 1); 
    long long e = 17;       
    long long d = 2753;      
    long long message = 42;
    long long encrypted = mod_exp(message, e, n);
    printf("Encrypted: %lld\n", encrypted);
    long long decrypted = mod_exp(encrypted, d, n);
    printf("Decrypted: %lld\n", decrypted);
    return 0;
}
Output:
Encrypted: 2557
Decrypted: 42
