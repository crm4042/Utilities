#include "natural.h"


#define BASE 2

char* get_str_b2(natural* num){
	unsigned char* num_char =
            (unsigned char*)calloc(num -> length*8*sizeof(mp_limb_t)+1,
            sizeof(unsigned char));

    mp_size_t size= mpn_get_str(num_char, base, num -> value, num -> length);
	
	char* str_b2 = (char*)calloc(size, sizeof(char));
	for(int index=0; index<size; index++){
		str_b2[index] = (char)((int)num_char[index]+48);
	}

	free(num_char);

	return str_b2;
}


/**
  *		Prints a natural number
  *		
  *		Parameter num:			The natural number to print
  *		Returns:				NULL
  */
void print_natural_number(natural* num, int base){
	unsigned char* num_char = 
			(unsigned char*)calloc(num -> length*8*sizeof(mp_limb_t)+1, 
			sizeof(unsigned char));

	mp_size_t size= mpn_get_str(num_char, base, num -> value, num -> length);

	printf("Size: %ld Num: ", size);
	print_number(num_char, size);
	printf("\n");

	free(num_char);
}


/**
  *		Gets a natural number from a character array
  *	
  *		Parameter num_char:		The number to create a natural number of
  *		Parameter decimals:		The number of decimals in the number string
  *		Returns:				The corresponding natural number
  */
natural* get_natural_b2(unsigned char* num_char, int decimals){
	// Initialize the natural number
	natural* num = (natural*)calloc(1, sizeof(natural));
	num -> length = ceil(((float)decimals)/(8*sizeof(mp_limb_t)));
	num -> occupied_bits = decimals;
	num -> value = (mp_limb_t*)calloc(num -> length, sizeof(mp_limb_t));
	
	// Set the string
	mpn_set_str(num -> value, num_char, decimals, 2);

	return num;
}

/**
  *		Gets the corresponding natural number from an integer
  *
  *		Parameter int:			The number to turn into a natural number
  *		Returns:				A natural number corresponding to the integer
  */
natural* get_natural_from_int(int num){
	unsigned char* num_char = get_binary(num);
	int num_length;
	if(num == 0){
		num_length = 1;
	}
	else{
		num_length = floor(logbase(2, num)+1);
	}
	return get_natural_b2(num_char, num_length);
}

/**
  *		Gets a random natural value of a certain length
  *
  *		Parameter decimals:		The number of decimals in the number
  *		Parameter base:			The base the number is written in
  */
natural* get_random_natural_b2(int decimals){
	unsigned char* random_char = (unsigned char*)calloc(decimals, 
			sizeof(unsigned char));

	for(int index=0; index<decimals; index++){
		if(index == 0){
			random_char[index] = 1;
		}
		else{
			random_char[index] = (unsigned char)rand()%2;
		}
	}

	natural* num = get_natural_b2(random_char, decimals);

	free(random_char);
	return num;
}

natural* get_random_natural_in_range(natural* low, natural* high){
	natural* difference = subtract_natural(high, low);
	
	unsigned char* num_char = 
			(unsigned char*)calloc(8*sizeof(mp_limb_t)*difference -> length, 
			sizeof(unsigned char));
	size_t size = 
			mpn_get_str(num_char, 2, difference -> value, difference -> length);

	for(int index=0; index<(int)size; index++){
		num_char[index] = rand()%2;
	}

	natural* random = get_natural_b2(num_char, size);
	natural* random_in_range = modulus_natural(random, difference);
	
	natural* result = add_natural(random_in_range, low);
	
	free(num_char);
	free_natural(random);
	free_natural(random_in_range);

	return result;
}

/**
  *		Copies a natural number
  *		
  *		Parameter original:			The original natural number to calculate
  *		Returns:					A copy of original
  */
natural* copy_natural(natural* original){
	natural* copy = (natural*)calloc(1, sizeof(natural));
	copy -> length = original -> length;
	copy -> value = (mp_limb_t*)calloc(original -> length, sizeof(mp_limb_t));
	mpn_copyi(copy -> value, original -> value, original -> length);
	return copy;
}

/**
  *		Frees a natural number
  *		
  *		Parameter num:			The natural number to free
  *		Returns:				NULL
  */
void free_natural(natural* num){
	free(num -> value);
	free(num);
}

/**
  *		Simplifies the limbs of a natural number by removing excess zero
  *		limbs
  *		
  *		Parameter num:			The number to simplify
  *		Returns:				NULL
  */
void simplify_natural(natural* num){
	while(num -> length >= 1){
		if(mpn_zero_p(&(num -> value[num -> length-1]), 1)){
			num -> length -= 1;
		}
		else{
			break;
		}
	}
}

/**
  *		Compares two natural numbers
  *
  *		Parameter op1:			The first natural number to compare
  *		Parameter op2:			The second natural number to compare
  *		Returns:				1 if op1>op2, -1 if op1<op2, 0 if op1=op2
  */
int compare_natural(natural* op1, natural* op2){
	simplify_natural(op1);
	simplify_natural(op2);
	if(op1 -> length > op2 -> length){
		return 1;
	}
	else if(op2 -> length > op1 -> length){
		return -1;
	}
	return mpn_cmp(op1 -> value, op2 -> value, op1 -> length);
}

/**
  *		Returns whether or not a natural number is equal to zero
  *		
  *		Parameter op:			The natural number to check if it's zero
  *		Returns:				Whether or not op is zero.
  */
int is_zero_natural(natural* op){
	return mpn_zero_p(op -> value, op -> length);
}

/**
  *		Performs a bit carry
  *		
  *		Parameter sum:			The sum to perform a carry on
  *		Returns:				NULL
  */
void carry(natural* sum){
	
	// Creates a new value array
	mp_limb_t* new_value = (mp_limb_t*)calloc(sum -> length+1, 
			sizeof(mp_limb_t));

	// Shifts the values over so there is a new significant digit
	for(int index=0; index<sum -> length; index++){
		new_value[index] = sum -> value[index]; 
	}

	unsigned char carry_bit = (unsigned char)1;

	mpn_set_str(&(new_value[sum -> length]), &carry_bit, 1, 2);

	free(sum -> value);
	sum -> value = new_value;
	sum -> occupied_bits += 1;
	sum -> length += 1;
}

/**
  *		Performs a borrow on a difference (this will round to zero)
  *
  *		Parameter difference:		The difference to perform a borrow on
  *		Returns:					NULL
  */
void borrow(natural* difference){
	free(difference -> value);
	difference -> length = 1;
	difference -> value = (mp_limb_t*)calloc(difference -> length, 
			sizeof(mp_limb_t));

	mpn_zero(difference -> value, difference -> length);
}


/**
  *		Adds two natural numbers
  *
  *		Parameter op1:			The first natural number to add
  *		Parameter op2:			The second natural number to add
  *		Returns:				The sum of op1 and op2
  */
natural* add_natural(natural* op1, natural* op2){
	// Initializes the sum
	natural* sum = (natural*)calloc(1, sizeof(natural));
	sum -> length = max(op1 -> length, op2 -> length);
	sum -> value = (mp_limb_t*)calloc(sum -> length, sizeof(mp_limb_t));

	// Adds the required values
	mp_limb_t carry_bit = mpn_add_n(sum -> value, op1 -> value,
			op2 -> value, 2);

	// Carries the carry
	if(!mpn_zero_p(&carry_bit, 1)){
		carry(sum);
	}

	return sum;
}

/**
  *		Subtracts one operator from another
  *i
  *		Parameter op1:			The base natural number to subtract from
  *		Parameter op2:			The second natural number to subtract
  *		Returns:				The difference between op1 and op2
  */
natural* subtract_natural(natural* op1, natural* op2){
	natural* difference = (natural*)calloc(1, sizeof(natural));
	difference -> length = max(op1 -> length, op2 -> length);
	difference -> value = (mp_limb_t*)calloc(difference -> length, 
			sizeof(mp_limb_t));
	
	mp_limb_t borrow_bit = mpn_sub(difference -> value, op1 -> value, 
			op1 -> length, op2->value, op2 -> length);

	if(!mpn_zero_p(&borrow_bit, 1)){
		borrow(difference);
	}

	return difference;
}


/**
  *		Multiplies two natural numbers together
  *		
  *		Parameter op1:			The first natural number to multiply
  *		Parameter op2:			The second natural number to multiply
  *		Returns:				The result of multiplying op1 and op2
  */
natural* multiply_natural(natural* op1, natural* op2){
	natural* product = (natural*)calloc(1, sizeof(natural));
	product -> length = op1 -> length+op2 -> length;
	product -> value = (mp_limb_t*)calloc(product -> length, sizeof(mp_limb_t));

	if(mpn_cmp(op1 -> value, op2 -> value, max(op1 -> length, op2 -> length))){
		mpn_mul(product -> value, op1 -> value, op1 -> length, op2 -> value, 
				op2 -> length);
	}
	else{
		mpn_sqr(product -> value, op1 -> value, op1 -> length);
	}

	return product;
}

/**
  *		Divides two natural numbers
  *
  *		Parameter op1:			The divisor natural number
  *		Parameter op2:			The dividend natural number
  *		Returns:				The result of op1 divided by op2
  */
natural* divide_natural(natural* op1, natural* op2){
	natural* quotient = (natural*)calloc(1, sizeof(natural));
	quotient -> length = op1 -> length-op2 -> length+1;
	quotient -> value = (mp_limb_t*)calloc(quotient -> length, 
			sizeof(mp_limb_t));

	natural* remainder = (natural*)calloc(1, sizeof(natural));
	remainder -> length = op2 -> length;
	remainder -> value = (mp_limb_t*)calloc(remainder -> length, 
			sizeof(mp_limb_t));

	mpn_tdiv_qr(quotient -> value, remainder -> value, 0, op1 -> value, 
			op1 -> length, op2 -> value, op2 -> length);

	free_natural(remainder);

	return quotient;
}

/**
  *		Gets the remainder of the ficision of two natural numbers
  *
  *		Parameter op1:			The divisor
  *		Parameter op2:			The dividend
  *		Returns:				The remainder of op1 divided by op2
  */
natural* modulus_natural(natural* op1, natural* op2){
	// qp=quotient -> value
	// rp=remainder -> value
	// qxn=fraction limbs=0
	// np=op1 -> value
	// nn=op1 -> length
	// dp=op2 -> value
	// dn=op2 -> length

	// Note that:
	// quotient -> length=op1 -> length-op2 -> length+1
	// remainder -> length=op2 -> length

	simplify_natural(op2);

	if(compare_natural(op1, op2)<0){
		return copy_natural(op1);
	}

	natural* quotient = (natural*)calloc(1, sizeof(natural));
	quotient -> length = op1 -> length-op2 -> length+1;
	quotient -> value = (mp_limb_t*)calloc(quotient -> length, 
			sizeof(mp_limb_t));

	natural* remainder = (natural*)calloc(1, sizeof(natural));
	remainder -> length = op2 -> length;
	remainder -> value = (mp_limb_t*)calloc(remainder -> length,
			sizeof(mp_limb_t));

	mpn_tdiv_qr(quotient -> value, remainder -> value, 0, op1 -> value, 
			op1 -> length, op2 -> value, op2 -> length);

	free_natural(quotient);

	return remainder;
}

/**
  *		Performs exponentiation with two natural numbers
  *		
  *		Parameter op1:			The base of the exponentiation
  *		Parameter op2:			The exponent of the exponentiation
  *		Returns:				op1 raised to the op2
  */
natural* exponentiation_natural(natural* op1, natural* op2){
	// Initializes the result to 1
	unsigned char one_char = (unsigned char)1;
	natural* result = get_natural_b2(&one_char, 1);

	// Gets the exponent in binary
	unsigned char* op2_bin =
			(unsigned char*)calloc(op2 -> length*8*sizeof(mp_limb_t)+1,
			sizeof(unsigned char));
	mp_size_t size= mpn_get_str(op2_bin, 2, op2 -> value, op2 -> length);

	// The main square-multiply loop
	for(int index=0; index<size; index++){
		// Squares the result
		natural* temp_result_1 = multiply_natural(result, result);

		// Multiplies the result
		if((int)op2_bin[index] == 1){
			natural* temp_result_2 = multiply_natural(temp_result_1, op1);

			free_natural(result);
			free_natural(temp_result_1);
			result = temp_result_2;
		}
		else{
			free_natural(result);
			result = temp_result_1;
		}

		if(index != 0 && index % 4 == 0){
			simplify_natural(result);
		}
	}

	simplify_natural(result);
	return result;
}

/**
  *		Increments a natural number. Note that this will free the previous
  *		number so this can be more easily used for loops.
  *
  *		Parameter op1:			The operator to increment
  *		Parameter op2:			The increment amount
  *		Returns:				The sum of op1 and op2
  */
natural* increment_natural(natural* op1, int op2){
	natural* incrementer = get_natural_from_int(op2);
	natural* result = add_natural(op1, incrementer);
	
	free_natural(op1);
	free_natural(incrementer);
	return result;
}

/**
  *		Performs modular addition on natural numbers
  *
  *		Parameter op1:			The first operator for addition
  *		Parameter op2:			The second operator for addition
  *		Parameter modulus:		The modulus that modular addition is defined on
  *		Returns:				The modular addition of op1 and op2 over 
  *								the modulus
  */
natural* modular_add_natural(natural* op1, natural* op2, natural* modulus){
	natural* sum = add_natural(op1, op2);
	natural* remainder = modulus_natural(sum, modulus);
	free_natural(sum);
	return remainder;
}

/**
  *		Performs modular subtraction on natural numbers
  *		Parameter op1:			The value being subtracted from
  *		Parameter op2:			The subtracted value
  *		Parameter modulus:		The modulus that modular subtraction is 
  *								defined on
  *		Returns:				The modular subtraction of op2 from op1 over
  *								the modulus
  */
natural* modular_subtract_natural(natural* op1, natural* op2, natural* modulus){
	if(compare_natural(op1, op2)<0){
		natural* temp = subtract_natural(op2, op1);
		natural* result = subtract_natural(modulus, temp);
		free_natural(temp);
		return result;
	}
	else{
		return subtract_natural(op1, op2);
	}
}

/**
  *		Performs modular multiplication
  *
  *		Parameter op1:			The first operand for modular multiplication
  *		Parameter op2:			The second operand for modular multiplication
  *		Parameter modulus:		The modulus the operation is defined over
  */
natural* modular_multiply_natural(natural* op1, natural* op2, 
		natural* modulus){
	natural* product = multiply_natural(op1, op2);
	natural* remainder = modulus_natural(product, modulus);
	free_natural(product);
	return remainder;
}


/**
  *		Performs modular exponentiation
  *		
  *		Parameter op1:			The base of the modular exponentiation
  *		Parameter op2:			The exponent of the modular exponentiation
  *		Parameter modulus:		The modulus of the modular exponentiation
  *		Returns:				The remainder of op1 raised to op2 over 
  *								modulus
  */
natural* modular_exponentiation_natural(natural* op1, natural* op2, 
		natural* modulus){

	// Initializes the result to 1
	unsigned char one_char = (unsigned char)1;
	natural* result = get_natural_b2(&one_char, 1);

	// Gets the exponent in binary
	unsigned char* op2_bin =
			(unsigned char*)calloc(op2 -> length*8*sizeof(mp_limb_t)+1,
			sizeof(unsigned char));
	mp_size_t size= mpn_get_str(op2_bin, 2, op2 -> value, op2 -> length);
	
	// The main square-multiply loop
	for(int index=0; index<size; index++){
		// Squares the result
		natural* temp_result_1 = modular_multiply_natural(result, result, 
				modulus);

		// Multiplies the result
		if((int)op2_bin[index] == 1){
			natural* temp_result_2 = modular_multiply_natural(temp_result_1, 
					op1, modulus);

			free_natural(result);
			free_natural(temp_result_1);
			result = temp_result_2;
		}
		else{
			free_natural(result);
			result = temp_result_1;
		}
	}

	return result;
}

natural* modular_inverse(natural* op, natural* modulus){
	integer* op_integer = ;
	integer* modulus_integer = ;
}


/*int main(){
	srand(0);

	//int op1_int = 3;
	//natural* op1 = get_natural_from_int(op1_int);
	
	//int op2_int = 128;
	//natural* op2 = get_natural_from_int(op2_int);

	//int modulus_int = 29;
	//natural* modulus = get_natural_from_int(modulus_int);

	//natural* result = exponentiation_natural(op1, op2);
	//print_natural_number(result);
	//printf("\n");
}*/
