// eratosthenes.c
// IJC-DU1, příklad a), 23.3.2024
// Author: Jakub Lůčný, FIT
// Compiled with: gcc 11.4.0
/*
    Definition of eratosthenes function which performs Sieve of Eratosthenes
    to find prime numbers using the bitset array and functions 
*/

#include <stdio.h>
#include <math.h>

#include "bitset.h"
#include "eratosthenes.h"

// 1 = prime number, 0 = not a prime
void eratosthenes(bitset_t jmeno_pole) {
    bitset_index_t size = bitset_size(jmeno_pole);
    bitset_index_t max = sqrt(size);

    // Sets all bit values in array to 1
    bitset_fill(jmeno_pole, 1);
    // Numbers 0 and 1 are not primes
    bitset_setbit(jmeno_pole, 0, 0);
    bitset_setbit(jmeno_pole, 1, 0);

    // Sets all even numbers (except for 2) to 0
    for (bitset_index_t i = 2, end = (size+1)/2; i < end; i++) {
        bitset_setbit(jmeno_pole, 2*i, 0);
    }

    // Finds the smallest prime number and sets all it's multiples to 0
    for (bitset_index_t i = 3; i <= max; i+=2) {
        if (bitset_getbit(jmeno_pole, i)) {
            for (bitset_index_t j = 3, end = size/i; j <= end; j+=2) {
                bitset_setbit(jmeno_pole, i*j, 0);
            }
        }
    }
}
