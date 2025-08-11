#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STRING_MAX 15

typedef struct stack {
	int tos;
	char stack[STRING_MAX];
} STACK;

void push(STACK *stack, char data);
char pop(STACK *stack);
bool isFull(STACK stack);
bool isEmpty(STACK stack);

void push(STACK *stack, char data) {
	if (isFull(*stack)) {
		printf("Stack Overflow\n");
		return;
	}
	stack->tos = stack->tos + 1;
	stack->stack[stack->tos] = data;
}

char pop(STACK *stack) {
	int data = stack->stack[stack->tos];
	stack->tos = stack->tos - 1;
	return data;
}

bool isFull(STACK stack) {
    bool isFull = false;
    if (stack.tos == STRING_MAX - 1) {
        isFull = true;
    }
    return isFull;
}

bool isEmpty(STACK stack) {
    bool isEmpty = false;
    if (stack.tos < 0) {
        isEmpty = true;
    }
    return isEmpty;
}

int main(void) {
	STACK stack;
	stack.tos = -1;

	char input[STRING_MAX] = "ab*c";
	char output[STRING_MAX] = "";

	for (int i = 0; i < strlen(input); i++) {
		char ch = input[i];
		if (ch != '*' && isdigit(ch)) {
			push(&stack, ch);
		} 
		else if (ch == '*') {
			pop(&stack);
		}
	}

	while (!isEmpty(stack)) {
		int i;
		output[i++] = pop(&stack);
	}

	printf("%s", output);
}
