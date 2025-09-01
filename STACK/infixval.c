#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX 20

typedef struct stack {
	char data[MAX];
	int tos;
} STACK;

void push(STACK *stack, int item);
char pop(STACK *stack);
char peek(STACK stack);
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

char pop(STACK *stack) {
	if (isEmpty(*stack)) {
		return '\0';
	}
	int val = stack->data[stack->tos];
	stack->tos--;
	return val;
}
// always check booleans
// NOTES: store data first, increment - 1, then return

char peek(STACK stack) {
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

int main() {
	
}
