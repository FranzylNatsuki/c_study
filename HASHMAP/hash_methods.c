#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define B_CAP 10 
#define FOLDING_CAP 10001
// bucket cap meaning capacity of hashmap
#define K 31 
// Any prime number that's bigger than your bucket
#define INCR 7 
// any prime number less than bucket (for double hash)


typedef struct {
	int key;
	char state;
} DATA;

// if string input
typedef struct {
	char key[20];
	char state;
} DATA_STRING;

int option1(char num[]) {
	int length = strlen(num);
	int key = 0;

	for (int i = 0; i < length; i++) {
		key += num[i];
	}

	return key;
}

int option2_firstletter(char num[]) {
	int key = 0;
	key = num[0] + (27 * num[1]) + ((int)pow(27, 2) * num[2]);
	return key;
}

int option2_lastletter(char num[]) {
	int key = 0;
	int L = strlen(num);
	key = num[L - 3] + (27 * num[L - 2]) + ((int)pow(27, 2) * num[L-1]);
	return key;
}

int option3(char num[]) {
	int key = 0;
	int L = strlen(num);

	for (int i = 0; i < L; i++) {
		key += num[L - i - 1] * (int)pow(K, i);
	}

	return key;
}

int modular_arithmetic(int key) {
	int index = key % B_CAP;
	return index;
}

int truncation(int key) {
	int index = key % 1000;
	return index;
}

int folding(int key) {
	int index, temp, first, second, third;
	third = key % 100;
	temp = (key - third) / 100;
	second = temp % 1000;
	temp = temp - second;
	first = temp / 1000;
	index = first + second + third;
	return index;
}

int radix(int key) {
	int base = 11;
	int convert = 0;
	int exp = 1;

	while (key > 0) {
		convert += (key % base) * exp;
		key /= base;
		exp *= 10;
	}

	return convert % B_CAP;
}

int linear_probing(int P) {
	P = (P + 1) % B_CAP;
	return P;
}

int double_hash(int index, int value) {
	int increment = 1 + (value % INCR);
	return (index + increment) % B_CAP;
}

// adding using double hash as a collision fix
void add_double(DATA hash[], int data) {
	int index , index2 = -1;

	index = modular_arithmetic(data);

	// stops when index2 cycle's back to index 1
	while(index2 != index) {
		if (index2 == -1) {
			// begin at the starting index
			// index 2 takes over and is the main locator
			index2 = index;
		}
		// if theres an empty or deleted slot
		if((hash[index2].state == 'e') ||(hash[index2].state == 'd')){
			hash[index2].key = data;
			hash[index2].state = 'o';
			break;
		} else {
			// if its occupied, use your collision algo
			index2 = double_hash(index2, data);
		}
	}
}

void add_linear(DATA hash[], int data) {
	int index , index2 = -1;

	index = modular_arithmetic(data);

	// stops when index2 cycle's back to index 1
	while(index2 != index) {
		if (index2 == -1) {
			// begin at the starting index
			// index 2 takes over and is the main locator
			index2 = index;
		}
		// if theres an empty or deleted slot
		if((hash[index2].state == 'e') ||(hash[index2].state == 'd')){
			hash[index2].key = data;
			hash[index2].state = 'o';
			break;
		} else {
			// if its occupied, use your collision algo
			index2 = linear_probing(index2);
		}
	}
}

bool search(DATA hash[], int key) {
	int index , index2 = -1;
	bool found = false;

	index = modular_arithmetic(key);
	// MUST be the same method

	// stops when index2 cycle's back to index 1
	while(index2 != index) {
		if (index2 == -1) {
			// begin at the starting index
			// index 2 takes over and is the main locator
			index2 = index;
		}
		// check if its occupied to not accidentally return deleted content
		if((hash[index2].state == 'o') && hash[index2].key == key){
			found = true;
			// return a boolean or return a struct, up to u twin
			break;
		} else {
			// if its occupied, use your collision algo
			index2 = double_hash(index2, key);
		}
	}

	return found;
}

bool delete(DATA hash[], int key) {
	int index , index2 = -1;
	bool deleted = false;

	index = modular_arithmetic(key);
	// MUST be the same method

	// stops when index2 cycle's back to index 1
	while(index2 != index) {
		if (index2 == -1) {
			// begin at the starting index
			// index 2 takes over and is the main locator
			index2 = index;
		}
		// check if its occupied to not accidentally return deleted content
		if((hash[index2].state == 'o') && hash[index2].key == key){
			hash[index2].key = 0; // or something, just make it empty;
			hash[index2].state = 'd'; // flag as deleted
			deleted = true;
			break;
		} else {
			// if its occupied, use your collision algo
			index2 = double_hash(index2, key);
		}
	}

	return deleted;
}

int main() {
	char option_string[20] = "abcd";
	int option1_number = option1(option_string);
	int option2_f = option2_firstletter(option_string);
	int option2_l = option2_lastletter(option_string);
	int option3_ = option3(option_string);

	printf("Original String: %s\n", option_string);
	printf("%d\n", option1_number);
	printf("%d\n", option2_f);
	printf("%d\n", option2_l);
	printf("%d\n", option3_);

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

	DATA hashmap[B_CAP];
	
	// initialize
	for (int i = 0; i < B_CAP; i++) {
		hashmap[i].key = 0;
		hashmap[i].state = 'e';
	}

	add_double(hashmap, option1_number);
	add_linear(hashmap, option2_l);
	add_double(hashmap, 123);
	add_double(hashmap, 124);
	add_double(hashmap,125);


	if (search(hashmap, option1_number)) {
		printf("It's there twin\n");
	} else {
		printf("It's gone twin\n");
	}

	if (delete(hashmap, option2_l))
		printf("Success\n");
	else
		printf("Failed\n");

	if (search(hashmap, option2_l)) {
		printf("It's there twin\n");
	} else {
		printf("It's gone twin\n");
	}

	for (int i = 0; i < B_CAP; i++) {
		printf("%d: %d - %c\n", i + 1, hashmap[i].key, hashmap[i].state);
	}
}
