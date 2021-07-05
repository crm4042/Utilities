#ifndef SELECTION_SORT
#define SELECTION_SORT

#include <stdio.h>
#include <stdlib.h>

void selection_sort(void** list, int length, int(*compare)(void*, void*));

#endif
