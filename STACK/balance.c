#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 20

typedef struct node *nd; 
struct node {
	char data;
	nd next;
} STACK;

void push(nd *stack, int item);
char pop(nd *stack);
char peek(nd *stack);
bool isEmpty(nd *stack);

void push(nd *stack, int item) {
	nd temp = malloc(sizeof(STACK)); // DONT FORGET TO MAKE THE NODE ITSELF
	temp->data = item; // assign the value
	temp->next = *stack; // insert to the last item added
	// [temp] -> [*stack (tos)] -> [] -> []
	*stack = temp;
}

char pop(nd *stack) {
	if (isEmpty(stack)) return -1; // check first before popping

	nd temp = *stack; // set temp as stack because we will remove it
	int val = (*stack)->data; // store the data
	*stack = temp->next; // move the stack backwards
	// [*stack / temp] -> [] -> [] -> []
	free(temp); // remove
	return val;
}

char peek(nd *stack) {
	if (isEmpty(stack)) return -1; // check first before peeking
	return (*stack)->data;
}

bool isEmpty(nd *stack) {
	if (*stack == NULL) {
		return true;
	} else {
		return false;
	}
}

int main() {
	printf("Test\n");
	char test[MAX] = "((a+b)*(c-d))";
	nd top;
	top = NULL;

	for (int i = 0; i < strlen(test); i++) {
		if (test[i] == '(') {
			push(&top, test[i]);
		}
		else if (test[i] == ')') {
			pop(&top);
		}
	}

	if (isEmpty(&top)) {
		printf("Balanced\n");
	} 
	else if (!isEmpty(&top)) {
		printf("Not Balanced\n");
	}
}
