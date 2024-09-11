#include <stdio.h>

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
    long long n = 2537;      
    long long e = 13;        
    long long d = 937;        

    int message = 7;    
    long long encrypted = mod_exp(message, e, n);
    printf("Encrypted: %lld\n", encrypted);

    long long decrypted = mod_exp(encrypted, d, n);
    printf("Decrypted: %lld\n", decrypted);
    return 0;
}
Output:
Encrypted: 1125
Decrypted: 7
