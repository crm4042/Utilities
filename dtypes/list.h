#ifndef LIST
#define LIST

#include <stdio.h>
#include <stdlib.h>

typedef struct lists{
	void** list;
	int length;
	int max_length;
}list;

list* create_list(int length);
void free_list(list* arr);
void extend_list(list* arr, int new_max_length);
void append_list(list* arr, void* element);
void insert_list(list* arr, void* element, int index);
void* get_list(list* arr, int index);
void* pop_list(list* arr, int index);
void remove_list(list* arr, int index);

#endif
