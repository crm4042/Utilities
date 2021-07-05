#include "misc_math.h"

int max(int element1, int element2){
	if(element1 <= element2){
		return element2;
	}
	else{
		return element1;
	}
}

double logbase(int base, double num){
	return log(num)/log(base);
}
