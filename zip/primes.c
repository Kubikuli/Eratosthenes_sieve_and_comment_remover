// primes.c
// IJC-DU1, příklad a), 23.3.2024
// Author: Jakub Lůčný, FIT
// Compiled with: gcc 11.4.0
/*
    Finds and prints out up to 10 biggest prime numbers from 2 to N
*/

#include <stdio.h>
#include <time.h>

#include "bitset.h"
#include "eratosthenes.h"

#define N 666000001LU       // <---- You can change the limit here

int main() {

    clock_t start;
    start = clock();

    bitset_create(jmeno_pole, N);
    // bitset_alloc(jmeno_pole, N);         // <---- Choose create or alloc

    eratosthenes(jmeno_pole);

    // Saves the last 10 prime numbers into an array
    bitset_index_t primes[10] = {0,};
    for (bitset_index_t i = (bitset_size(jmeno_pole) - 1UL), counter = 0; counter < 10 && i >= 2; i--) {
        if (bitset_getbit(jmeno_pole, i)) {
            primes[counter] = i;
            counter++;
        }
    }

    // Prints out the prime numbers and time it took to get them
    for (int i = 0; i < 10; i++) {
        printf("%lu\n", primes[9-i]);
    }
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);

    // free(jmeno_pole);    // <---- Use this ONLY if dynamically allocating array
}
