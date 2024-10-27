// bitset.h
// IJC-DU1, příklad a), 23.3.2024
// Author: Jakub Lůčný, FIT
// Compiled with: gcc 11.4.0
/*
    Defines macros as default
    if USE_INLINE is defined - defines inline functions instead of macros
*/

#ifndef BITSET_H
#define BITSET_H

#include <assert.h>
#include <limits.h> // for ULONG_MAX, CHAR_BIT
#include <stdbool.h> // Just in case we wanted to use TRUE/FALSE to set bits instead of 1/0
#include <stdlib.h>
#include "error.h"

#define BITS_IN_UL ((sizeof(unsigned long)) * CHAR_BIT)     //size of unsigned long (in bits)

// Type for bit array
typedef unsigned long *bitset_t;

// Type for index of bit array
typedef unsigned long bitset_index_t;

// Macros:
// Statically created array with all values set to 0
#define bitset_create(jmeno_pole, velikost) \
    static_assert(velikost > 0, "bitset_create: Size must be bigger than 0!\n");\
    bitset_index_t jmeno_pole[((velikost - 1) / BITS_IN_UL) + 2] = {velikost,}

// Dynamically allocated array
#define bitset_alloc(jmeno_pole, velikost) \
    static_assert(velikost > 0, "bitset_alloc: Size must be bigger than 0!\n");\
    bitset_t jmeno_pole = calloc(((velikost - 1) / BITS_IN_UL) + 2, sizeof(unsigned long));\
    if (jmeno_pole == NULL) {error_exit("bitset_alloc: Failed to allocate memory!\n");}\
    jmeno_pole[0] = (unsigned long)velikost

// Inline versions of functions
#ifdef USE_INLINE
    // Frees dynamically allocated memory
    inline void bitset_free(bitset_index_t *jmeno_pole) {
        free(jmeno_pole);
    }

    // Returns size of array in bits
    inline bitset_index_t bitset_size(bitset_index_t *jmeno_pole) {
        return jmeno_pole[0];
    }

    // Sets all the bits in array to 0 or 1
    inline void bitset_fill(bitset_index_t *jmeno_pole, int bool_vyraz) {
        if (bool_vyraz) {
            for (bitset_index_t i = 1; i < ((jmeno_pole[0] - 1) / BITS_IN_UL) + 2; i++) {
                jmeno_pole[i] = ULONG_MAX;
            }
        }

        else {
            for (bitset_index_t i = 1; i < ((jmeno_pole[0] - 1) / BITS_IN_UL) + 2; i++) {
                jmeno_pole[i] = 0;
            }
        }
    }

    // Sets given bit in array to the given value (0/1)
    inline void bitset_setbit(bitset_index_t *jmeno_pole, bitset_index_t index, int bool_vyraz) {
        // function takes index only as UL, so we don't have to check for: index < 0
        if (index > bitset_size(jmeno_pole)) {
            error_exit("(inline)_bitset_setbit: Index %lu out of bounds 0..%lu\n",(unsigned long)index, bitset_size(jmeno_pole));
        }
        if (bool_vyraz) {
            jmeno_pole[(index / BITS_IN_UL) + 1UL] |= ((unsigned long) 1 << index % BITS_IN_UL);
        }

        else {
            jmeno_pole[(index / BITS_IN_UL) + 1UL] &= ~((unsigned long) 1 << index % BITS_IN_UL);
        }
    }

    // Returns value of given bit
    inline bitset_index_t bitset_getbit(bitset_index_t *jmeno_pole, bitset_index_t index) {
        // function takes index only as UL, so we don't have to check for: index < 0
        if (index > bitset_size(jmeno_pole)) {
            error_exit("(inline)_bitset_getbit: Index %lu out of bounds 0..%lu\n",(unsigned long)index, bitset_size(jmeno_pole));
        }
        return (jmeno_pole[(index / BITS_IN_UL) + 1] & ((unsigned long) 1 << (index % BITS_IN_UL)));
    }

#else
// Macro versions of functions
    // Frees dynamically allocated memory
    #define bitset_free(jmeno_pole) \
        do {free(jmeno_pole);}\
        while(0)

    // Gives size of array in bits
    #define bitset_size(jmeno_pole) \
        jmeno_pole[0]

    // Sets all the bits in array to 0 or 1
    #define bitset_fill(jmeno_pole, bool_vyraz) \
        do{\
            if (bool_vyraz) {\
                for (unsigned i = 1; i < ((jmeno_pole[0] - 1) / BITS_IN_UL) + 2; i++) {\
                    jmeno_pole[i] = ULONG_MAX;\
                }\
            }\
            else {\
                for (unsigned i = 1; i < ((jmeno_pole[0] - 1) / BITS_IN_UL) + 2; i++) {\
                    jmeno_pole[i] = 0;\
                }\
            }\
        }\
        while(0)

    // Sets given bit in array to the given value (0/1)
    #define bitset_setbit(jmeno_pole, index, bool_vyraz) \
        do{\
            if (index < 0 || index > bitset_size(jmeno_pole)) {\
                error_exit("(macro)_bitset_setbit: Index %lu out of bounds 0..%lu\n",(unsigned long)index, bitset_size(jmeno_pole));\
            }\
            if (bool_vyraz) {\
                jmeno_pole[(index / BITS_IN_UL) + 1] |= ((unsigned long) 1 << index % BITS_IN_UL);\
            }\
            else {\
                jmeno_pole[(index / BITS_IN_UL) + 1] &= ~((unsigned long) 1 << index % BITS_IN_UL);\
            }\
        }\
        while(0)

    // Gives value of given bit
    #define bitset_getbit(jmeno_pole, index) \
        (index < 0 || (index > bitset_size(jmeno_pole)) ?\
            error_exit("(macro)_bitset_getbit: Index %lu out of bounds 0..%lu\n",(unsigned long)index, bitset_size(jmeno_pole)), 0 :\
            ((jmeno_pole)[(index / BITS_IN_UL) + 1] & ((unsigned long) 1 << (index % BITS_IN_UL))))

#endif // USE_INLINE

#endif // BITSET_H
