#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define NUM 3
#define B_CAP 10
#define K 31
#define INCR 7

typedef struct {
	int item_number;
	char state;
} ITEMS;

int key_cast(char num[]){
	int key = 0;
	int L = strlen(num);

	for (int i = 0; i < L; i++) {
		key += num[L - i - 1] * pow(K, i);
	}

	return key;
}

int hash_trunc(int key) {
	int index = key % 10;
	return index;
}

int double_hash(int index, int value) {
	int increment = 1 + (value % INCR);
	return (index + increment) % B_CAP;
}

void add_inventory(ITEMS hash_inv[], int data) {
	bool stored = false;
	int index , index2 = -1;

	index = hash_trunc(data);

	while(index2 != index) {
		if (index2 == -1)
			index2 = index;
		if((hash_inv[index2].state == 'e') ||(hash_inv[index2].state == 'd')){
			hash_inv[index2].item_number = data;
			hash_inv[index2].state = 'o';
			stored = true;
			break;
		} else {
			index2 = double_hash(index2, data);
		}
	}

	if (stored) {
		printf("Inventory Added\n");
	} else {
		printf("Storage is full\n");
	}
}

int main() {
	ITEMS hash[B_CAP];

	while (true) {
		int cho


		char key[20];
		printf("Enter a number:");
		fgets(key, 20, stdin);

		printf("Key into an integer: %d\n", key_cast(key));
		printf("Truncated index: %d\n", hash_trunc(key_cast(key)));
		add_inventory(hash, key_cast(key));
	}
}
