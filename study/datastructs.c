#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structure.h"

#define MAX 5

void push(STACK *stack, int item);
int pop(STACK *stack);
int peek(STACK stack);
bool isFull(STACK stack);
bool isEmpty(STACK stack);

void push(STACK *stack, int item) {
	if (isFull(*stack)) {
		return;
	}
	stack->tos++;
	stack->data[stack->tos] = item;
}

// NOTES: Remember to add tos first before inputting
// When handling array type data fields, do not forget to use tos as the index locator.
// When handling sub structs, remember that they are not pointers so express as stack->substack.data or stack->substack.data[stack-tos]

int pop(STACK *stack) {
	if (isEmpty(*stack)) {
		return -1;
	}
	int val = stack->data[stack->tos];
	stack->tos--;
	return val;
}
// always check booleans
// NOTES: store data first, increment - 1, then return

int peek(STACK stack) {
	return stack.data[stack.tos];
}

// REMINDER: When not using *pointers for peek, always use .

bool isFull(STACK stack) {
	if (stack.tos == MAX - 1) {
		return true;
	} else {
		return false;
	}
}

// REMINDER: Always use MAX - 1 (in C atleast)

bool isEmpty(STACK stack) {
	if (stack.tos == -1) {
		return true;
	} else {
		return false;
	}
}

// REMINDER: Empty always is -1 (in C atleast)

