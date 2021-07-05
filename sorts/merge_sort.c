#include "merge_sort.h"

int min(int op1, int op2){
	if(op1 < op2){
		return op1;
	}
	else{
		return op2;
	}
}

void merge_sort(void** list, int length, int(*compare)(void*, void*)){
	int depth = 0;

	int delta=1;
	void** sorted = (void**)calloc(length, sizeof(void*));
	while(delta < length){
		int sorted_index=0;
		for(int index=0; index<length; index+=2*delta){
			int left=index;
			int middle=min(index+delta, length);
			int middle_fixed = min(index+delta, length);
			int right = min(index+2*delta, length);

			while(left != middle_fixed || middle != right){
				if(left == middle_fixed){
					sorted[sorted_index] = list[middle];
					sorted_index += 1;
					middle += 1;
				}

				else if(middle == right){
					sorted[sorted_index] = list[left];
					sorted_index += 1;
					left += 1;
				}

				else{
					if(compare(list[left], list[middle]) >= 0){
						sorted[sorted_index]=list[middle];
						sorted_index += 1;
						middle += 1;
					}
					else{
						sorted[sorted_index] = list[left];
						sorted_index += 1;
						left += 1;
					}
				}
			}
		}

		void** temp = list;
		list = sorted;
		sorted = temp;
		
		depth += 1;

		delta *= 2;
	}

	if(depth%2 == 1){
		for(int index=0; index<length; index++){
			sorted[index] = list[index];
		}
	}
}

int compare_int(void* op1, void* op2){
	return *((int*)op1)-*((int*)op2);
}

int main(){
	int length = 40;
	int** list = (int**)calloc(length, sizeof(int*));
	for(int index=0; index<length; index++){
		int random_number = rand()%1000;
		list[index] = (int*)calloc(1, sizeof(int));
		*(list[index]) = random_number;
		printf("%d ", *(list[index]));
	}
	printf("\n");

	merge_sort((void**)list, length, compare_int);

	for(int index=0; index<length; index++){
		printf("%d ", *((int*)(list[index])));
	}
	printf("\n");

	return 0;
}
