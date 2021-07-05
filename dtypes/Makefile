C=gcc
C_FLAGS=-c -std=c99 -Wall -Wextra
O_FLAGS=-lgmp -o

NAT=natural
INT=integer
MISC=misc

directory: clean misc_math.o misc_numbers.o natural.o integer.o list.o
	ar cr dtypes.a misc_math.o misc_numbers.o natural.o integer.o list.o`

natural.o:
	$(C) $(C_FLAGS) natural.c

misc: clean misc_math.o misc_numbers.o
	gcc -o misc misc_math.o misc_numbers.o

misc_math.o:
	$(C) $(C_FLAGS) misc_math.c

misc_numbers.o:
	$(C) $(C_FLAGS) misc_numbers.c

integer: clean integer.o misc_math.o misc_numbers.o list.o
	gcc $(O_FLAGS) integer integer.o misc_math.o misc_numbers.o list.o
integer.o:
	$(C) $(C_FLAGS) integer.c

list: clean list.o
	gcc $(O_FLAGS) list list.o
list.o:
	$(C) $(C_FLAGS) list.c

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.out
	rm -f natural
	rm -f integer
	rm -f list
	rm -f misc
	clear
