# Eratosthenes sieve and comment remover
VUT FIT 2023/24 - IJC proj1  

Includes 2 different programs:

## primes (primes-i)
First one is for finding largest prime numbers using eratosthenes sieve algorithm and bitfields for effectivity.

## no-comment
Second one removes comments from C source code file.

## Usage
`make all` to compile all the programs  
`make run` to find 10 largest prime numbers from 1 to N (N is 666000001 by default, can be manually changed in primes.c)  
`./primes`  
`./primes-i` using inlining  
`./no-comment {input_file}` to remove comment from input_file, by default prints to stdout and reads from stdin

Points: 14/15
