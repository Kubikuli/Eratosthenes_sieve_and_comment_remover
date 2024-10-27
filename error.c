// error.c
// IJC-DU1, příklad b), 23.3.2024
// Author: Jakub Lůčný, FIT
// Compiled with: gcc 11.4.0

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"

// Prints out warning message
void warning(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, args);

    va_end(args);
}

// Prints out error message and ends the program
void error_exit(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);

    va_end(args);

    exit(1);
}
