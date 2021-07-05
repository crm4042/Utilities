#include "selection_sort.h"

void selection_sort(void** list, int length, int(*compare)(void*, void*)){
	for(int index1=0; index1<length; index1++){
		int smallest_index = index1;
		for(int index2=index1+1; index2<length; index2++){
			if(compare(list[index2], list[smallest_index])<0){
				smallest_index = index2;
			}
		}
		
		void* temp = list[index1];
		list[index1] = list[smallest_index];
		list[smallest_index] = temp;
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

	selection_sort((void**)list, length, compare_int);

	for(int index=0; index<length; index++){
		printf("%d ", *((int*)(list[index])));
	}
	printf("\n");

	return 0;
}
