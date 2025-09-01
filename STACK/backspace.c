#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// cool

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

void reverse_str(char *string) {
	int len = strlen(string);
	for (int i = 0; i < len / 2; i++) {
		char temp = string[i];
		string[i] = string[len - i -1];
		string[len - i - 1] = temp;
	}
}

int main(void) {
	STACK stack;
	stack.tos = -1;

	char input[STRING_MAX] = "ab*c";
	char output[STRING_MAX] = "";

	for (int i = 0; i < strlen(input); i++) {
		char ch = input[i];
		if (ch != '*') {
			push(&stack, ch);
			printf("Pushed %c\n", ch);
		} 
		else if (ch == '*') {
			// pop(&stack);
			printf("Pop %c\n", pop(&stack));
		}
	}
	
	int i = 0;
	while (!isEmpty(stack)) {
		output[i++] = pop(&stack);
	}

	reverse_str(output);
	printf("%s\n", output);
}
