#include "list.h"

list* create_list(int length){
	list* arr = (list*)calloc(1, sizeof(list));
	arr -> length = 0;
	arr -> max_length = length;
	arr -> list = (void**)calloc(length, sizeof(void*));
	return arr;
}

void free_list(list* arr){
	free(arr -> list);
	free(arr);
}

void print_int_list(list* arr){
	for(int index=0; index<arr -> length; index++){
		printf("%d ", *((int*)(arr -> list[index])));
	}
	printf("\n");
}

void extend_list(list* arr, int new_max_length){
	void** new_list = (void**)calloc(new_max_length, sizeof(void*));
	for(int index=0; index<arr -> length; index++){
		new_list[index] = arr -> list[index];
	}
	free(arr -> list);
	arr -> max_length = new_max_length;
	arr -> list = new_list;
}

void append_list(list* arr, void* element){
	if(arr -> length == arr -> max_length){
		extend_list(arr, 2*arr -> length);
	}
	arr -> list[arr -> length] = element;
	arr -> length += 1;
}

void insert_list(list* arr, void* element, int index){
	if(arr -> length == arr -> max_length){
		extend_list(arr, 2*arr -> length);
	}
	for(int shift_index=arr -> length-1; shift_index>=index; shift_index--){
		arr -> list[shift_index+1] = arr -> list[shift_index];
	}
	arr -> list[index] = element;
	arr -> length += 1;
}

void* get_list(list* arr, int index){
	if(index < 0){
		//printf("Get index: %d\n", arr -> length+index);
		return arr -> list[arr -> length+index];
	}
	return arr -> list[index];
}

void* pop_list(list* arr, int index){
	if(index < 0){
		index = arr -> length+index;
		//printf("Pop index: %d\n", index);
	}

	void* element = arr -> list[index];

	for(int shift_index=index+1; shift_index<arr -> length; shift_index++){
		arr -> list[shift_index-1] = arr -> list[shift_index];
	}
	arr -> length -= 1;
	return element;
}

void remove_list(list* arr, int index){
	pop_list(arr, index);
}


/*int main(){
	int length = 10;
	int** nums = (int**)calloc(length, sizeof(int*));
	for(int index=0; index<length; index++){
		int* random_int = (int*)calloc(1, sizeof(int));
		*random_int = rand()%100;
		nums[index] = random_int;
	}

	list* arr = create_list(length);

	for(int index=0; index<length; index++){
		printf("Appending %d\n", *(nums[index]));
		append_list(arr, (void*)nums[index]);
	}

	print_int_list(arr);

	int* appended_int = (int*)calloc(1, sizeof(int));
	*appended_int = rand()%100;
	printf("Inserting %d at 1\n", *appended_int);
	insert_list(arr, appended_int, 1);

	print_int_list(arr);

	printf("%d at index 4\n", *((int*)get_list(arr, 4)));

	printf("%d removed at 5\n", *((int*)pop_list(arr, 5)));
	print_int_list(arr);

	while(arr -> length > 0){
		printf("%d removed at -1\n", *((int*)pop_list(arr, -1)));
		print_int_list(arr);
	}
	
	printf("Finished\n");
}*/
