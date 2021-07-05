#include "integer.h"


/**
  * 	Creates a random integer with a certain number of decimals.
  *
  *		Parameter decimals:			The number of decimal digits
  *		Parameter base:				The base of the number
  *		Returns:					A random number with the specified length
  */
integer* create_random_integer(int decimals, int base){
	integer* num = (integer*)calloc(1, sizeof(integer));

	char* random_integer = (char*)calloc(decimals+1, sizeof(char));
	for(int index=0; index<decimals; index++){
		random_integer[index] = (char)(rand()%base+48);
	}

	mpz_init_set_str(num -> value, random_integer, base);
	free(random_integer);
	return num;
}

/**
  *		Creates an integer from an int
  *		
  *		Parameter num:			The number to create an integer from
  *		Returns:				An integer corresponding to the value of the int
  */
integer* create_integer_from_int(int num){
	unsigned char* num_char;
	if(num<0){
		num_char = get_str_b10(-num, 48);
	}
	else{
		num_char = get_str_b10(num, 48);
	}

	integer* output = (integer*)calloc(1, sizeof(integer));

	mpz_init_set_str(output -> value, (char*)num_char, 10);
	free(num_char);

	if(num < 0){
		mpz_neg(output -> value, output -> value);
	}

	return output;
}


integer* copy_integer(integer* num){
	integer* output = (integer*)calloc(1, sizeof(integer));
	mpz_init(output -> value);
	mpz_set(output -> value, num -> value);
	return output;
}

/**
  *		Frees an integer.
  *
  *		Parameter num:		integer*	The number to free
  *		Returns:			NULL
  */
void free_integer(integer* num){
	mpz_clear(num -> value);
	free(num);
}


/**
  *		Prints the integer
  *
  *		Parameter num:				The integer to print
  *		Returns:					NULL
  */
void print_integer(integer* num){
	mpz_out_str(stdout, 10, num -> value);
}


/**
  *		Compares two integers
  *		Parameter op1:				The first integer to compare
  *		Parameter op2:				The second integer to compare
  *		Returns:					1 if op1 is greater than op2
  *									-1 if op1 is less than op2
  *									0 if op1 is equal to op2
  */
int compare_integer(integer* op1, integer* op2){
	return mpz_cmp(op1 -> value, op2 -> value);
}

/**
  *		Determines wheter an integer is equal to zero
  *		
  *		Parameter op:				The operator to check whether or not it is
  *									zero
  *		Returns:					Whether or not op is equal to zero
  */
int is_zero_integer(integer* op){
	return mpz_cmp_d(op -> value, 0);
}

/**
  *		Negates an integer
  *		
  *		Parameter op:				The integer to negate
  *		Returns:					The negation of the integer
  */
integer* negate_integer(integer* op){
	integer* output = (integer*)calloc(1, sizeof(integer));
	mpz_init(output -> value);
	mpz_neg(output -> value, op -> value);
	return output;
}

/**
  *		Adds an integer to an integer
  *
  *		Parameter op1:				The integer operand
  *		Parameter op2:				The integer to add
  *		Returns:					The resulting sum
  */
integer* add_integer(integer* op1, integer* op2){
	integer* output = (integer*)calloc(1, sizeof(integer));
	mpz_init(output -> value);
	
	mpz_add(output -> value, op1 -> value, op2 -> value);
	return output;
}


/**
  *		Subtracts an integer from an integer
  *
  *		Parameter op1:				The integer to subtract from
  *		Parameter op2:				The integer to subtract
  *		Returns:					The difference between op1 and op2
  */
integer* subtract_integer(integer* op1, integer* op2){
	integer* output = (integer*)calloc(1, sizeof(integer));
	mpz_init(output -> value);

	mpz_sub(output -> value, op1 -> value, op2 -> value);
	return output;
}

/**
  *		Multiplies an integer and an integer
  *
  *		Parameter op1:			The first integer to multiply
  *		Parameter op2:			The second integer to multiply
  *		Returns:				The product of op1 and op2
  */
integer* multiply_integer(integer* op1, integer* op2){
	integer* output = (integer*)calloc(1, sizeof(integer));
	mpz_init(output -> value);

	mpz_mul(output -> value, op1 -> value, op2 -> value);
	return output;
}

/**
  *		Divides an integer by an integer
  *
  *		Parameter op1:			The first integer to divide
  *		Parameter op2:			The second integer to divide
  *		Returns:				The quotient of op1 and op2
  */
integer* divide_integer(integer* op1, integer* op2){
	integer* output = (integer*)calloc(1, sizeof(integer));
	mpz_init(output -> value);

	mpz_fdiv_q(output -> value, op1 -> value, op2 -> value);
	return output;
}

/**
  *		Gets the modulus of an integer with respect to another integer
  *		
  *		Parameter op1:			The first integer to get the modulus of
  *		Parameter op2:			The second integer to get the modulus with 
  *								respect to
  *		Returns:				The modulus of op1 with respect to op2
  */
integer* modulus_integer(integer* op1, integer* op2){
	integer* output = (integer*)calloc(1, sizeof(integer));
	mpz_init(output -> value);

	mpz_mod(output -> value, op1 -> value, op2 -> value);
	return output;
}

/**
  *		Gets The exponentiation of one integer to another integer.
  *
  *		Parameter op1:			The base integer
  *		Parameter op2:			The exponent integer
  *		Returns:				The base to the exponent
  */
integer* exponentiation_integer(integer* op1, integer* op2){
	int length = mpz_sizeinbase(op2 -> value, 2);
	char* exponent = (char*)calloc(length+1, sizeof(char));
	mpz_get_str(exponent, 2, op2 -> value);

	integer* output = create_integer_from_int(1);
	
	for(int index=0; index<length; index++){
		integer* temp1 = multiply_integer(output, output);
		free_integer(output);
		if(exponent[index] == '1'){
			integer* temp2 = multiply_integer(op1, temp1);
			output = temp2;
			free_integer(temp1);
		}
		else{
			output = temp1;
		}
	}

	return output;
}

/**
  *		Adds an integer to another integer with respect to a modulus
  *		
  *		Parameter op1:			The first integer to add
  *		Parameter op2:			The second integer to add
  *		Parameter modulus:		The modulus to add with respect to
  *		Returns:				The modular addition of op1 and op2 with
  *								respect to the modulus
  */
integer* modular_add_integer(integer* op1, integer* op2, integer* modulus){
	integer* intermediate = add_integer(op1, op2);
	integer* output = modulus_integer(intermediate, modulus);
	
	free_integer(intermediate);
	
	return output;
}

/**
  *		Subtracts an integer from another integer with respect to a modulus
  *
  *		Parameter op1:			The operator to subtract from
  *		Parameter op2:			The operator to subtract
  *		Parameter modulus:		The modulus to subtract with respect to
  *		Returns:				The subtraction of op2 from op1 with respect
  *								to the modulus
  */
integer* modular_subtract_integer(integer* op1, integer* op2, integer* modulus){
	integer* intermediate = subtract_integer(op1, op2);
	integer* output = modulus_integer(intermediate, modulus);
	
	free_integer(intermediate);
	
	return output;
}

/**
  *		Multiplies an integer with another integer with respect to a modulus
  *		
  *		Parameter op1:			The first operator to multiply
  *		Parameter op2:			The second operator to multiply
  *		Parameter modulus:		The modulus to multiply with respect to
  *		Returns:				The product of op1 and op2 with respect to 
  *								the modulus
  */
integer* modular_multiply_integer(integer* op1, integer* op2, integer* modulus){
	integer* intermediate = multiply_integer(op1, op2);
	integer* output = modulus_integer(intermediate, modulus);
	
	free_integer(intermediate);
	
	return output;
}

/**
  *		Exponentiates an integer from another integer with respect to a modulus
  *		
  *		Parameter op1:			The base integer
  *		Parameter op2:			The exponent integer
  *		Parameter modulus:		The modulus to exponentiate with respect to
  *		Returns:				The base exponentiated by the exponent with
  *								respect to the modulus
  */
integer* modular_exponentiation_integer(integer* op1, integer* op2, 
		integer* modulus){
	integer* output = (integer*)calloc(1, sizeof(integer));
	mpz_init(output -> value);
	
	mpz_powm(output -> value, op1 -> value, op2 -> value, modulus -> value);
	return output;
}

/**
  *		Gets the modular inverse of an integer with respect to a modulus
  */
integer* modular_inverse_integer(integer* op1, integer* modulus){
	// Swaps so the higher of the two is in the modulus
	integer* higher;
	integer* lower;
	if(compare_integer(op1, modulus) < 0){
		higher = modulus;
		lower = op1;
	}
	else{
		higher = op1;
		lower = modulus;
	}

	list* a = create_list(10);
	list* b = create_list(10);
	list* q = create_list(10);
	list* r = create_list(10);

	append_list(a, (void*)higher);
	append_list(b, (void*)lower);
	append_list(q, (void*)divide_integer(higher, lower));
	append_list(r, (void*)modulus_integer(higher, lower));

	while(is_zero_integer((integer*)get_list(r, -1))){
		higher = copy_integer((integer*)get_list(b, -1));
		lower = copy_integer((integer*)get_list(r, -1));

		append_list(a, (void*)higher);
		append_list(b, (void*)lower);
		append_list(q, (void*)divide_integer(higher, lower));
		append_list(r, (void*)modulus_integer(higher, lower));
	}

	// Removes the last elements
	free_integer((integer*)pop_list(a, -1));
	free_integer((integer*)pop_list(b, -1));
	free_integer((integer*)pop_list(q, -1));
	free_integer((integer*)pop_list(r, -1));

	for(int index=0; index<a -> length; index++){
		print_integer((integer*)get_list(a, index));
		printf("=");
		print_integer((integer*)get_list(q, index));
		printf("(");
		print_integer((integer*)get_list(b, index));
		printf(")+");
		print_integer((integer*)get_list(r, index));
		printf("\n");
	}

	// Builds up using the extended euclidean algorithm
	integer* u = create_integer_from_int(1);
	integer* x = (integer*)pop_list(a, -1);
	integer* v = (integer*)pop_list(q, -1);
	integer* temp = negate_integer(v);
	free_integer(v);
	v = temp;
	integer* y = (integer*)pop_list(b, -1);

	while(a -> length > 0){
		integer* temp1 = copy_integer(v);

		integer* temp21 = (integer*)pop_list(q, -1);
		integer* temp22 = negate_integer(temp21);
		integer* temp23 = multiply_integer(v, temp22);
		integer* temp24 = add_integer(u, temp23);

		integer* temp3 = copy_integer(x);

		integer* temp4 = (integer*)pop_list(a, -1);

		free_integer(u);
		free_integer(v);
		free_integer(x);
		free_integer(y);
		free_integer(temp21);
		free_integer(temp22);
		free_integer(temp23);

		u = temp1;
		v = temp24;
		y = temp3;
		x = temp4;
	}

	//while(b -> length > 0){
	//	free_integer((integer*)pop_list(b, -1));
	//}
	while(r -> length > 0){
		free_integer((integer*)pop_list(r, -1));
	}


	// Returns the inverse
	if(compare_integer(x, op1) == 0){
		free_integer(v);
		free_integer(x);
		//free_integer(y);
		return u;
	}
	else{
		free_integer(u);
		free_integer(x);
		//free_integer(y);
		return v;
	}
}

int main(){
	srand(time(NULL));
	
	integer* op1 = create_random_integer(5, 10);
	printf("Operator 1: ");
	print_integer(op1);
	printf("\n");
	
	integer* op2 = create_random_integer(2, 10);
	printf("Operator 2: ");
	print_integer(op2);
	printf("\n");

	integer* sum = add_integer(op1, op2);
	printf("Sum: ");
	print_integer(sum);
	printf("\n");

	integer* difference = subtract_integer(op1, op2);
	printf("Difference: ");
	print_integer(difference);
	printf("\n");

	integer* product = multiply_integer(op1, op2);
	printf("Product: ");
	print_integer(product);
	printf("\n");

	integer* quotient = divide_integer(op1, op2);
	printf("Quotient: ");
	print_integer(quotient);
	printf("\n");

	integer* remainder = modulus_integer(op1, op2);
	printf("Remiander: ");
	print_integer(remainder);
	printf("\n");

	//integer* modulus = create_random_integer(2, 10);
	integer* modulus = create_integer_from_int(8);
	printf("Modulus: ");
	print_integer(modulus);
	printf("\n");

	integer* exponent = exponentiation_integer(op1, modulus);
	printf("Exponent: ");
	print_integer(exponent);
	printf("\n");

	integer* modular_add = modular_add_integer(op1, op2, modulus);
	printf("Modular add: ");
	print_integer(modular_add);
	printf("\n");

	integer* modular_subtract = modular_subtract_integer(op1, op2, modulus);
	printf("Moduluar subtract: ");
	print_integer(modular_subtract);
	printf("\n");

	integer* modular_multiply = modular_multiply_integer(op1, op2, modulus);
	printf("Modular multiply: ");
	print_integer(modular_multiply);
	printf("\n");

	integer* modular_exponentiation = modular_exponentiation_integer(op1, op2, 
			modulus);
	printf("Modular exponentiation: ");
	print_integer(modular_exponentiation);
	printf("\n");

	integer* op = create_integer_from_int(11213);
	integer* mod = create_integer_from_int(12034);
	integer* inverse = modular_inverse_integer(mod, op);
	printf("Modular inverse of ");
	print_integer(mod);
	printf(" mod ");
	print_integer(op);
	printf(":\n");
	print_integer(inverse);
	printf("\n");

	free_integer(op1);
	free_integer(op2);
	free_integer(sum);
	free_integer(difference);
	free_integer(product);
	free_integer(quotient);
	free_integer(remainder);
	free_integer(modular_add);
	free_integer(modular_subtract);
	free_integer(modular_multiply);
	free_integer(modular_exponentiation);
}
