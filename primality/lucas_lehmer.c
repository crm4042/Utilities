#include "lucas_lehmer.h"

int lucas_lehmer(natural* p){

	// Constants
	natural* one = get_natural_from_int(1);
	natural* two = get_natural_from_int(2);

	// The s value
	natural* residue = get_natural_from_int(4);
	
	// The base of the exponentiation
	natural* base = get_natural_from_int(2);
	
	// Generates 2^p-1 into number
	natural* exponent = exponentiation_natural(base, p);
	natural* number = subtract_natural(exponent, one);

	// The index for the main loop
	natural* index = copy_natural(p);
	natural* new_index = subtract_natural(index, two);
	free(index);
	index = new_index;
	
	//printf("Iterations: 0; Number: ");
	//print_natural_number(residue, 2);

	// The main loop
	while(!is_zero_natural(index)){
		// Gets the residue^2
		natural* temp_var1 = modular_multiply_natural(residue, residue, 
				number);
		// Gets the residue^2-2 mod number
		natural* temp_var2 = modular_subtract_natural(temp_var1, 
				two, number);

		// Frees temporary stuff
		free_natural(residue);
		free_natural(temp_var1);

		residue = temp_var2;

		// Decrement the index
		new_index = subtract_natural(index, one);
		free(index);
		index = new_index;
	}

	// Finds if residue=0
	int comparison = is_zero_natural(residue);
	
	
	free_natural(one);
	free_natural(two);
	free_natural(base);
	free_natural(exponent);
	free_natural(number);
	free_natural(index);
	free_natural(residue);

	return comparison;
}

/*int main(){
	int p_int = 11213;
	natural* p = get_natural_from_int(p_int);
	printf("P %d; Primality %d\n", p_int, lucas_lehmer(p));
	free_natural(p);

	return 1;
}*/
