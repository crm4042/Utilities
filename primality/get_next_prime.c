#include "get_next_prime.h"

#include <unistd.h>

natural* get_next_prime(natural* low, int trial_divisions, int witnesses){
	natural* one = get_natural_from_int(1);
	natural* candidate = subtract_natural(low, one);

	natural** divisions = (natural**)calloc(trial_divisions, 
			sizeof(natural**));

	if(trial_divisions > 0){
		divisions[0] = get_natural_from_int(2);
	}
	if(trial_divisions > 1){
		divisions[1] = get_natural_from_int(3);
	}

	int index1=2;
	int index2=5;
	while(index1<trial_divisions){
		natural* division_candidate = get_natural_from_int(index2);
		if(miller_rabin(division_candidate, witnesses)){
			divisions[index1] = division_candidate;
			index1 += 1;
		}
		else{
			free_natural(division_candidate);
		}
		index2 += 1;
	}
	free_natural(candidate);

	candidate = copy_natural(low);
	while(1){
		candidate = increment_natural(candidate, 1);

		int valid_trials = 1;
		// Does the trial divisions
		for(int index=0; index<trial_divisions; index++){
			natural* remainder = modulus_natural(candidate, 
					divisions[index]);
			if(is_zero_natural(remainder)){
				valid_trials = 0;
				break;
			}
			free_natural(remainder);
		}
		if(!valid_trials){
			continue;
		}

		// Uses a miller rabin
		if(miller_rabin(candidate, witnesses)){
			free_natural(one);
			for(int index=0; index<trial_divisions; index++){
				free_natural(divisions[index]);
			}
			free(divisions);
			return candidate;
		}
		natural* temp = add_natural(candidate, one);
		free_natural(candidate);
		candidate = temp;
	}
}

natural** get_next_primes(natural* low, int trial_divisions, int witnesses, 
		int num_primes){
	printf("Primes: %d\n", num_primes);
	natural** primes = (natural**)calloc(num_primes, sizeof(natural*));
	primes[0] = get_next_prime(low, trial_divisions, witnesses);
	for(int prime_index=1; prime_index<num_primes; prime_index++){
		primes[prime_index] = get_next_prime(primes[prime_index-1], 
				trial_divisions, witnesses);
	}
	return primes;
}

int main(){
	int num_primes = 5;
	int low_int = 1000000000;
	natural* low = get_natural_from_int(low_int);
	natural** results = get_next_primes(low, 10, 10, num_primes);
	for(int prime_index=0; prime_index<num_primes; prime_index++){
		printf("Index: %d; ", prime_index);
		print_natural_number(results[prime_index], 10);
	}
	return 0;
}
