#include "insertion_sort.h"

void insertion_sort(void** list, int length, int(*compare)(void*, void*)){
	for(int index1=0; index1<length; index1++){
		for(int index2=0; index2<index1; index2++){
			if(compare(list[index2], list[index1])>=0){
				void* temp = list[index1];
				for(int index3=index1-1; index3>=index2; index3--){
					list[index3+1] = list[index3];
				}
				list[index2] = temp;
			}
		}
	}
}

int compare_int(void* op1, void* op2){
	return *((int*)op1)-*((int*)op2);
}

int main(){
	int length = 20;
	int** list = (int**)calloc(length, sizeof(int*));
	for(int index=0; index<length; index++){
		int random_number = rand()%1000;
		printf("%d ", random_number);
		list[index] = (int*)calloc(1, sizeof(int));
		*(list[index]) = random_number;
	}
	printf("\n");

	insertion_sort((void**)list, length, compare_int);

	for(int index=0; index<length; index++){
		printf("%d ", *((int*)(list[index])));
	}
	printf("\n");

	return 0;
}
