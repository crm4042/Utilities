#ifndef INTEGER
#define INTEGER

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

#include "misc_numbers.h"
#include "misc_math.h"
#include "list.h"

typedef struct integers{
	mpz_t value;
}integer;

integer* create_random_integer(int decimals, int base);
integer* create_integer_from_int(int num);
void free_integer(integer* num);
void print_integer(integer* num);
int compare_integer(integer* op1, integer* op2);
int is_zero_integer(integer* op);
integer* negate_integer(integer* op);
integer* add_integer(integer* op1, integer* op2);
integer* subtract_integer(integer* op1, integer* op2);
integer* multiply_integer(integer* op1, integer* op2);
integer* divide_integer(integer* op1, integer* op2);
integer* modulus_integer(integer* op1, integer* op2);
integer* exponentiation_integer(integer* op1, integer* op2);
integer* modular_add_integer(integer* op1, integer* op2, integer* modulus);
integer* modular_subtract_integer(integer* op1, integer* op2, integer* modulus);
integer* modular_multiply_integer(integer* op1, integer* op2, integer* modulus);
integer* modular_exponentiation_integer(integer* op1, integer* op2,
        integer* modulus);
integer* modular_inverse_integer(integer* op1, integer* modulus);


#endif
