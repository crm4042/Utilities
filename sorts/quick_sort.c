#include "quick_sort.h"

void quick_sort_helper(void** list, int start, int end, 
		int(*compare)(void*, void*)){

	// Basis case
	if(end-start <= 0){
		return;
	}

	// Gets a random pivot
	int pivot_index = rand()%(end+1-start)+start;

	// Pushes the pivot to the end
	void* temp = list[pivot_index];
	list[pivot_index] = list[end];
	list[end] = temp;

	// The indices of the left and right
	int left = start;
	int right = end;

	// Main loop
	while(left <= right && left < end){
		// Swap two elements and change both left and right
		if(compare(list[end], list[left]) < 0 && 
				compare(list[end], list[right]) > 0){
		
			temp = list[left];
			list[left] = list[right];
			list[right] = temp;

			left += 1;
			right -= 1;
		}

		// Decrement right
		else if(compare(list[end], list[left]) < 0){
			right -= 1;
		}

		// Increment left
		else if(compare(list[end], list[right]) > 0){
			left += 1;
		}

		// Change both
		else{
			left += 1;
			right -= 1;
		}
	}
	
	// Left is now the start of the bigger array and right is the 
	// end of the lower array. Swap the pivot into place.
	temp = list[left];
	list[left] = list[end];
	list[end] = temp;

	quick_sort_helper(list, start, left-1, compare);
	quick_sort_helper(list, left+1, end, compare);
}

void quick_sort(void** list, int length, int(*compare)(void*, void*)){
	quick_sort_helper(list, 0, length-1, compare);
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

    quick_sort((void**)list, length, compare_int);

    for(int index=0; index<length; index++){
        printf("%d ", *((int*)(list[index])));
    }
    printf("\n");

    return 0;
}
