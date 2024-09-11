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
    long long p = 23;
    long long g = 5;
    long long a = 6; 
    long long b = 15;
    long long A = mod_exp(g, a, p);
    printf("Alice sends: %lld\n", A);

    long long B = mod_exp(g, b, p);
    printf("Bob sends: %lld\n", B);

    long long shared_secret_Alice = mod_exp(B, a, p);
    printf("Shared secret (Alice): %lld\n", shared_secret_Alice);

    long long shared_secret_Bob = mod_exp(A, b, p);
    printf("Shared secret (Bob): %lld\n", shared_secret_Bob);
    return 0;
}
Output:
Alice sends: 8
Bob sends: 19
Shared secret (Alice): 2
Shared secret (Bob): 2
