#include "miller_rabin.h"

int miller_rabin(natural* p, int witnesses){
	// Finds the factors
	natural* one=get_natural_from_int(1);
	natural* two=get_natural_from_int(2);
	natural* power=get_natural_from_int(0);
	natural* subtraction=subtract_natural(p, one);
	natural* subtraction_two = subtract_natural(p, two);
	while(1){
		natural* temp_var1 = add_natural(power, one);
		free_natural(power);
		power = temp_var1;

		natural* exponentiation = exponentiation_natural(two, power);
		natural* remainder = modulus_natural(subtraction, exponentiation);

		if(!is_zero_natural(remainder)){
			natural* temp_var2 = subtract_natural(power, one);
			free_natural(power);
			power = temp_var2;
			break;
		}

		free_natural(exponentiation);
		free_natural(remainder);
	}

	natural* exponentiation = exponentiation_natural(two, power);
	natural* multiplier = divide_natural(subtraction, exponentiation);
	
	// The witness loop
	for(int index=0; index<witnesses; index++){		
		natural* witness = get_random_natural_in_range(two, subtraction_two);

		natural* exponentiation = modular_exponentiation_natural(witness, 
				multiplier, p);

		if(compare_natural(exponentiation, one)==0 || 
				compare_natural(exponentiation, subtraction)==0){
			continue;
		}

		natural* iteration = subtract_natural(power, one);
		int success = 0;
		while(!is_zero_natural(iteration)){
			natural* temp_var2 = modular_multiply_natural(exponentiation, 
					exponentiation, p);
			free_natural(exponentiation);
			exponentiation = temp_var2;
			if(compare_natural(exponentiation, subtraction) == 0){
				success = 1;
				break;
			}
			natural* temp_var1 = subtract_natural(iteration, one);
			free_natural(iteration);
			iteration = temp_var1;
		}
		if(success){
			continue;
		}
		return 0;
	}
	return 1;
}

/*int main(){
	int p_int = 5;
	natural* p = get_natural_from_int(p_int);
	printf("Primality: %d\n", miller_rabin(p, 100));
}*/
