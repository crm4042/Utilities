#ifndef MISC_NUMBERS
#define MISC_NUMBERS

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "misc_math.h"


unsigned char* get_binary(int num);
unsigned char* get_str_b10(int num, int start);
void print_number(unsigned char* binary, int length);
unsigned char* get_random_number(int length, int base);
unsigned char** partition_char_num(unsigned char* num, int decimals, int size);
unsigned char* convert_endianness(unsigned char* num, int length, 
		int block_size);
int find_leading_1(unsigned char* num, int length);

#endif
