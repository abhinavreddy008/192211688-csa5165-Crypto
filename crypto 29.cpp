#include <stdio.h>
#include <stdlib.h>

#define LANES 25   
int check_all_nonzero(int lanes[]) {
    for (int i = 0; i < LANES; i++) {
        if (lanes[i] == 0) return 0;
    }
    return 1;
}
int main() {
    int lanes[LANES] = {0}; 
    int rounds = 0;
    while (!check_all_nonzero(lanes)) {
        for (int i = 0; i < LANES; i++) {
            lanes[i] |= rand() % 2; 
        }
        rounds++;
    }
    printf("It took %d rounds for all lanes to have at least one nonzero bit.\n", rounds);
    return 0;
}
Output:
It took 5 rounds for all lanes to have at least one nonzero bit.
