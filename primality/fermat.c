#include "fermat.h"

int single_test(natural* base, natural* p){
	natural* one = get_natural_from_int(1);
	natural* exponent = subtract_natural(p, one);
	natural* exponentiation = modular_exponentiation_natural(base, exponent, p);

	int comparison = compare_natural(exponentiation, one);
	
	free(one);
	free(exponent);
	free(exponentiation);

	return comparison == 0;
}

int fermat(natural* p, int witnesses){
	natural* one = get_natural_from_int(1);
	natural* low = get_natural_from_int(2);
	natural* high = subtract_natural(p, one);
	for(int index=0; index<witnesses; index++){
		natural* witness = get_random_natural_in_range(low, high);
		
		if(!single_test(witness, p)){
			return 0;
		}
		free_natural(witness);
	}
	free_natural(one);
	free_natural(low);
	free_natural(high);

	return 1;
}

/*int main(){
	srand(time(NULL));
	natural* p = get_natural_from_int(464158883);
	printf("Prime: %d\n", fermat(p, 100));
	free_natural(p);
}*/
