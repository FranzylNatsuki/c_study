#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
	int value;
} DATA;

typedef struct node *StackPtr;
struct node {
	DATA info;
	StackPtr next;
} NODE;

void push(StackPtr *tos, DATA value) {
	StackPtr temp = malloc(sizeof(DATA));
	temp->info = value;
	temp->next = *tos;
	(*tos) = temp;
}

DATA pop(StackPtr *tos) {
	StackPtr temp = *tos;
	DATA value = (*tos)->info;
	(*tos) = temp->next;
	free(*tos);
	return value;
}

DATA peek(StackPtr *tos) {
	return (*tos)->info;
}

int main() {

}
