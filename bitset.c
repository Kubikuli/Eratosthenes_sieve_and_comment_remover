// bitset.c
// IJC-DU1, příklad a), 23.3.2024
// Author: Jakub Lůčný, FIT
// Compiled with: gcc 11.4.0
/*
    Declaratios for inline functions
*/

#ifdef USE_INLINE

#include "bitset.h"

    extern void bitset_free(bitset_index_t *jmeno_pole);

    extern bitset_index_t bitset_size(bitset_index_t *jmeno_pole);

    extern void bitset_fill(bitset_index_t *jmeno_pole, int bool_vyraz);

    extern void bitset_setbit(bitset_index_t *jmeno_pole, bitset_index_t index, int bool_vyraz);

    extern bitset_index_t bitset_getbit(bitset_index_t *jmeno_pole, bitset_index_t index);

#endif
