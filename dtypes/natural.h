#ifndef NATURAL
#define NATURAL

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

#include "list.h"
#include "misc.h"

typedef struct naturals{
	mp_limb_t* value;
	mp_size_t length;
	mp_size_t occupied_bits;
}natural;

void print_natural_number(natural* num, int base);
natural* get_natural_b2(unsigned char* num_char, int decimals);
natural* get_natural_from_int(int num);
natural* get_random_natural_b2(int decimals);
natural* get_random_natural_in_range(natural* low, natural* high);
natural* copy_natural(natural* original);
void free_natural(natural* num);
void simplify_natural(natural* num);
int compare_natural(natural* op1, natural* op2);
int is_zero_natural(natural* op);
void carry(natural* sum);
void borrow(natural* difference);
natural* add_natural(natural* op1, natural* op2);
natural* subtract_natural(natural* op1, natural* op2);
natural* multiply_natural(natural* op1, natural* op2);
natural* divide_natural(natural* op1, natural* op2);
natural* modulus_natural(natural* op1, natural* op2);
natural* exponentiation_natural(natural* op1, natural* op2);
natural* increment_natural(natural* op1, int op2);
natural* modular_add_natural(natural* op1, natural* op2, natural* modulus);
natural* modular_subtract_natural(natural* op1, natural* op2, natural* modulus);
natural* modular_multiply_natural(natural* op1, natural* op2,
        natural* modulus);
natural* modular_exponentiation_natural(natural* op1, natural* op2,
        natural* modulus);

#endif
