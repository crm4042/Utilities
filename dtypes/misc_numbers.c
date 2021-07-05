#include "misc_numbers.h"


unsigned char* get_binary(int num){
	if(num == 0){
		int length = 1;
		unsigned char* num_bin = (unsigned char*)calloc(length, 
				sizeof(unsigned char));
		num_bin[0] = 0;
		return num_bin;
	}

	int length = floor(logbase(2, num)+1);
	unsigned char* num_bin = (unsigned char*)calloc(length, 
			sizeof(unsigned char));

	for(int index=length-1; index>=0; index--){
		num_bin[index] = num%2;
		num /= 2;
	}

	return num_bin;
}

unsigned char* get_str_b10(int num, int start_index){
	int digits = floor(logbase(10, num))+1;
	unsigned char* num_b10 = 
			(unsigned char*)calloc(digits, sizeof(unsigned char));
	
	for(int index=digits-1; index>=0; index--){
		num_b10[index] = (unsigned char)((num % 10)+start_index);
		num /= 10;
	}
	return num_b10;
}

/**
  *		Gets a random number with specified length in a specified base
  *
  *		Parameter length:			The number of digits to generate
  *		Parameter base:				The base to generate the number for
  *		Returns:					The random number
  */
unsigned char* get_random_number(int length, int base){
	unsigned char* random_number = (unsigned char*)calloc(length, 
			sizeof(unsigned char*));
	for(int index=0; index<length; index++){
		random_number[index] = rand()%base;
	}
	return random_number;
}

/**
  *		Prints a number.
  *		Note that the number is not written in ascii but rather as strict 
  *		numbers.
  *
  *		Parameter num:			The number to print
  *		Parameter length:		The length of the number
  */
void print_number(unsigned char* num, int length){
	for(int index=0; index<length; index++){
		printf("%d", num[index]);
	}
}

/**
  *		Converts a bitmap between little and big endianness
  *
  *		Parameter bits:			The bits to convert endianness of
  *		Parameter length:		The number of bits to convert
  *		Parameter block_size:	The size of the block of integers (often 64)
  *		Returns:				The converted bitmap
  */
unsigned char* convert_endianness(unsigned char*  bits, int length, 
		int block_size){

	// The conversion
	unsigned char* conversion = (unsigned char*)calloc(length, 
			sizeof(unsigned char));
	// The total number of blocks
	int num_blocks = ceil(((float)length)/block_size);
	// The number of elements in the first block
	int elements_in_first_block = length % block_size;
	if(elements_in_first_block == 0){
		elements_in_first_block = block_size;
	}

	// Goes through each index
	for(int block=0; block<num_blocks; block++){
		for(int element_in_block=0; 
				element_in_block<elements_in_first_block*(block == 0)+
						block_size*(block != 0);
				element_in_block++){

			int conversion_block = num_blocks-1-block;
			int bits_index = max(block-1, 0)*block_size+
					elements_in_first_block*(block > 0)+element_in_block;
			int conversion_index = conversion_block*block_size+element_in_block;

			
			conversion[conversion_index] = bits[bits_index];
		}
	}
	return conversion;
}

/**
  *		Partitions a number's digits into blocks of a certain maximum
  *		size
  *
  *		Parameter num:			The number to convert
  *		Parameter decimals:		The length of the number
  *		Parameter size:			The size of the blocks to partition 
  *								the bits into
  *		Returns:				The partitions
  */
unsigned char** partition_char_num(unsigned char* num, int decimals, int size){
	int num_partitions = (int)ceil(((float)decimals)/size);
	unsigned char** partitions = (unsigned char**)calloc(num_partitions, 
			sizeof(unsigned char**));

	// Loop through each partition starting with the last
	for(int partition=num_partitions-1; partition >= 0; partition--){

		partitions[partition] = (unsigned char*)calloc(size, 
				sizeof(unsigned char));
		
		int start = decimals-(num_partitions-partition)*size;

		// Loop through each byte
		for(int byte=64; byte >= 0 && start+byte >= 0; byte--){
			partitions[partition][byte] = num[start+byte];
		}
	}
	return partitions;
}

int find_leading_1(unsigned char* num, int length){
	for(int index=0; index<length; index++){
		if((int)num[index] == 1){
			return index;
		}
	}
	return length;
}



/*int main(){
	int num = rand();
	int length = floor(logbase(10, num))+1;
	printf("Initial: %d\nResult: ", num);
	print_number(get_str_b10(num), length);
	printf("\n");
}*/
