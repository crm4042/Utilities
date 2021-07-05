#ifndef INSERTION_SORT
#define INSERTION_SORT

#include <stdio.h>
#include <stdlib.h>

void insertion_sort(void** list, int length, int(*compare)(void*, void*));

#endif
