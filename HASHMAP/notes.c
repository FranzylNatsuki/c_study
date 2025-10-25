#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

typedef struct node *nd;
struct node {
	int data;
	nd next;
} NODE;

typedef struct hash {
	nd next;
} HASH;

int modular_arithmetic(int key) {
	int index = key % MAX;
	return index;
}

void init_hash(HASH hash[]) {
	int j;
	for (j = 0; j < MAX; j++) {
		hash[j].next = NULL;
	}
}

void add_Data(HASH hash[], int x) {
	int index;
	nd temp = malloc(sizeof(NODE));
	temp->data = x;
	temp->next = NULL;

	index = modular_arithmetic(x);
	if (hash[index].next == NULL)
		temp->next = hash[index].next;
	hash[index].next = temp;

	return;	
}

bool search(HASH hash[], int key) {
	bool found = false;
	int index;
	nd ptr;
	index = modular_arithmetic(key);
	ptr = hash[index].next;

	while (ptr != NULL) {
		if (ptr->data == key) {
			found = true;
			break;
		} else {
			ptr = ptr->next;
		}
	}

	return found;
}

bool deleted(HASH hash[], int key) {
	bool deleted = false;
	int index = modular_arithmetic(key);
	nd ptr = hash[index].next, ptr1 = NULL;

	while (ptr != NULL) {
		if (ptr->data == key) {
			if (ptr1 == NULL) {
				hash[index].next = NULL;
				break;
			} else {
				ptr1->next = ptr->next;
				break;
			}

			free(ptr);
			deleted = true;
		} else {
			ptr1 = ptr;
			ptr = ptr->next;
		}
	}

	return deleted;
}

int main() {

}
