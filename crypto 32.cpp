#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int generate_k() {
    return rand() % 1000 + 1;
}
void dsa_signature(const char *message, unsigned int *k) {
    *k = generate_k();  // Generate a new random `k` for each signature
    printf("DSA Signature for message '%s': k = %u\n", message, *k);
}
void rsa_signature(const char *message) {
    static unsigned int k = 1234;
    printf("RSA Signature for message '%s': k = %u\n", message, k);
}
int main() {
    srand(time(NULL));
    char message[] = "Hello, World!";
    unsigned int k;
    dsa_signature(message, &k);
    dsa_signature(message, &k);
    rsa_signature(message);
    rsa_signature(message);
    return 0;
}
Output:
DSA Signature for message 'Hello, World!': k = 767
DSA Signature for message 'Hello, World!': k = 945
RSA Signature for message 'Hello, World!': k = 1234
RSA Signature for message 'Hello, World!': k = 1234
