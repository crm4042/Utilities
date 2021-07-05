C=gcc
C_FLAGS=-c -std=c99 -Wall -Wextra
A_FLAGS=ar cr
O_FLAGS=-lgmp -o


directory: fermat.o lucas_lehmer.o miller_rabin.o get_next_prime.o
	$(A_FLAGS) primality.a fermat.o lucas_lehmer.o miller_rabin.o get_next_prime.o

fermat.o:
	$(C) $(C_FLAGS) fermat.c

lucas_lehmer.o:
	$(C) $(C_FLAGS) lucas_lehmer.c

miller_rabin.o:
	$(C) $(C_FLAGS) miller_rabin.c

get_next_prime.o:
	$(C) $(C_FLAGS) get_next_prime.c

clean:
	rm -f *.o
	rm -f *.a
	clear
