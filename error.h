// error.h
// IJC-DU1, příklad b), 23.3.2024
// Author: Jakub Lůčný, FIT
// Compiled with: gcc 11.4.0

#ifndef ERROR_H
#define ERROR_H

void warning(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif  // ERROR_H
