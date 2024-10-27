# Makefile
# IJC-DU1, 23.3.2024
# Author: Jakub Lůčný, FIT

CC = gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra -fsanitize=address
LDFLAGS = -lm -fsanitize=address


all: primes-i primes no-comment

primes-i: primes-i.o eratosthenes-i.o bitset-i.o error.o
	$(CC) -DUSE_INLINE primes-i.o eratosthenes-i.o bitset-i.o error.o -o primes-i $(LDFLAGS)

primes-i.o: primes.c bitset.h eratosthenes.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o

bitset-i.o: bitset.c bitset.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c bitset.c -o bitset-i.o


primes: primes.o eratosthenes.o error.o
	$(CC) primes.o eratosthenes.o error.o -o primes $(LDFLAGS)

primes.o: primes.c eratosthenes.h bitset.h error.h
	$(CC) $(CFLAGS) -c primes.c -o primes.o

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h error.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o


no-comment: no-comment.o error.o
	$(CC) no-comment.o error.o -o no-comment $(LDFLAGS)

no-comment.o: no-comment.c error.h
	$(CC) $(CFLAGS) -c no-comment.c -o no-comment.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c -o error.o

run: primes-i primes
	ulimit -s 90000 && ./primes-i
	ulimit -s 90000 && ./primes

clean:
	rm *.o

clean-all: clean
	rm primes
	rm primes-i
	rm no-comment

