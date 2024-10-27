// no-comment.c
// IJC-DU1, příklad b), 23.3.2024
// Author: Jakub Lůčný, FIT
// Compiled with: gcc 11.4.0
/*
    Removes comments from any .c file
    Reads from file given as first command-line argument
    or from stdin when no argument is given
    Prints to stdout
    Undefined behavior if stdout is redirected to the input file
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "error.h"

int main(int argc, char *argv[]) {
    // Checking number of command-line arguments
    if (argc > 2) {
        warning("Expected single argument.\n");
    }

    FILE *input_f = NULL;

    if (argc > 1) {
        // Trying to open file given as the first command-line argument and redirect to stdin
        input_f = freopen(argv[1], "r", stdin);
        if (input_f == NULL) {
            error_exit("Could not open file.\n");
        }
        // Checking if input file != output (exit, if they are the same)
        struct stat inp_file_stat;
        struct stat out_stat;

        // Getting stdin info
        if (fstat(0, &inp_file_stat) == -1) {
            error_exit("Couldn't get file information.\n");
        }
        // Getting stdout info
        if (fstat(1, &out_stat) == -1) {
            error_exit("Couldn't get file information.\n");
        }

        if(inp_file_stat.st_ino == out_stat.st_ino) {
            error_exit("Output redirected to input file.\n");
        }
    }

    // Start of finite-state machine
    int state = 0; //initial state
    int c;
    while ((c = getchar()) != EOF) {
        switch(state) {
            case 0: //default case
                if (c == '/') state = 5;
                else if (c == '"') {state = 3; putchar(c); }
                else if (c == '\'') {state = 1; putchar(c); }
                else putchar(c);
                break;
            case 1: //inside ''
                if (c == '\\') {state = 2; putchar(c); }
                else if (c == '\'') {state = 0; putchar(c); }
                else putchar(c);
                break;
            case 2:
                state = 1;
                putchar(c);
                break;
            case 3: // inside ""
                if (c == '\\') {state = 4; putchar(c); }
                else if (c == '"') {state = 0; putchar(c); }
                else putchar(c);
                break;
            case 4:
                state = 3;
                putchar(c);
                break;
            case 5: // after one /
                if (c == '/') state = 6;
                else if (c == '*') state = 7;
                else {state = 0; putchar('/'); putchar(c); }
                break;
            case 6: // inside // comment
                if (c == '\n') {state = 0; putchar(c); }
                else if (c == '\\') state = 9;
                break;
            case 7: // inside /**/ comment
                if (c == '*') state = 8;
                break;
            case 8:
                if (c == '/') {putchar(' '); state = 0; }
                else if (c == '*') ;
                else state = 7;
                break;
            case 9:
                if (c == '\n') {state = 6; putchar(c);}
                else state = 6;
                break;
        }
    }

    fclose(input_f);

    if (state != 0) {
        error_exit("Something went wrong (didn't end in default state)!\n");
    }
}
