#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 15
#define MAKE_NODE malloc(sizeof(ND))

typedef struct node *nd;
struct node {
	int key;
	nd next;
} ND;

typedef struct {
	nd elements[MAX_SIZE];
} HASHMAP;

void init(HASHMAP *map) {
	for (int i = 0; i < MAX_SIZE; i++) {
		map->elements[i] = NULL;
	}
}

int hash(int key) {
	int index = key % MAX_SIZE;
	return index;
}

void insert(HASHMAP *map, int key) {
	int index = hash(key);

	nd temp = MAKE_NODE;
	temp->key = key;
	temp->next = NULL;
	
	// If it's the main entry, not a collision
	if (map->elements[index] == NULL) {
		map->elements[index] = temp;
		map->elements[index]->key = key;
	} else {
		nd ptr = map->elements[index];

		while (ptr->next != NULL) {
			ptr = ptr->next;
		}

		ptr->next = temp;
	}
}

bool search(HASHMAP *map, int s_key) {
	int index = hash(s_key);
	bool found = false;

	nd ptr = map->elements[index];

	while (ptr != NULL) {
		if (ptr->key == s_key) {
			found = true;
			break;
		}
		ptr = ptr->next;
	}
	return found;
}

void delete(HASHMAP *map, int s_key) {
	int index = hash(s_key);
	
	nd ptr1 = NULL, ptr = map->elements[index];

	while (ptr != NULL) {
		if (ptr->key == s_key){
			if (ptr1 == NULL)
				map->elements[index] = ptr->next;
			else 
				ptr1->next = ptr->next;
			free(ptr);
			break;
		}
		ptr1 = ptr;
		ptr = ptr->next;
	}
}

int main() {
	HASHMAP map;
	init(&map);

	insert(&map, 10);
	insert(&map, 25);
	insert(&map, 40);

	printf("Searching 25: %s\n", search(&map, 25) ? "Found" : "Not found");
	printf("Searching 10: %s\n", search(&map, 10) ? "Found" : "Not found");
	delete(&map, 10);
	printf("Searching 10: %s\n", search(&map, 10) ? "Found" : "Not found");
	printf("Searching 11: %s\n", search(&map, 11) ? "Found" : "Not found");

	return 0;
}
