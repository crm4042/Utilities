C=gcc
C_FLAGS=-c -std=c99 -Wall -Wextra

directory: insertion_sort.o quick_sort.o merge_sort.o selection_sort.o
	ar cr insertion_sort.o quick_sort.o merge_sort.o selection_sort.o

insertion_sort.o:
	$(C) $(C_FLAGS) insertion_sort.c

quick_sort.o:
	$(C) $(C_FLAGS) quick_sort.c

merge_sort.o:
	$(C) $(C_FLAGS) merge_sort.c

selection_sort.o:
	$(C) $(C_FLAGS) selection_sort.c


