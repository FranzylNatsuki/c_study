// Code by Franzyl Bjorn L. Macalua CCS4 - B

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define S 50

typedef struct
{
	char stack[S];
	int tos;
}STACK;

void push(STACK *stack, int data);
int pop(STACK *stack);
bool isFull(STACK stack);
bool isEmpty(STACK stack);
int precedence_stack(char operator); 
void infixToPostFix(char* exp, STACK *stack,char* output);

void push(STACK *stack, int data) {
	if (isFull(*stack)) {
		printf("Stack Overflow\n");
		return;
	}
	stack->tos = stack->tos + 1;
	stack->stack[stack->tos] = data;
}

int pop(STACK *stack) {
	int data = stack->stack[stack->tos];
	stack->tos = stack->tos - 1;
	return data;
}

bool isFull(STACK stack) {
    bool isFull = false;
    if (stack.tos == S - 1) {
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

int precedence_stack(char operator) {
	int precedence;

	if (operator == '/' || operator == '*') {
		precedence = 2;
	}

	else if (operator == '+' || operator == '-') {
		precedence = 1;
	}

	else {
		precedence = -1;
	}

	return precedence;
}

void infixToPostFix(char* exp, STACK *stack,char* output) {
	int len = strlen(exp);
	int j = 0;

	for (int i = 0; i < len; i++) {
		char c = exp[i];

		if(isdigit(c)) {
			output[j++] = c;
		}

		else if (c == '(') {
			push(stack, '(');
		}

		else if (c == ')') {
			while (!isEmpty(*stack) && stack->stack[stack->tos] != '(') {
				output[j++] = pop(stack);
			}
			if (!isEmpty(*stack)) {
				pop(stack);
			}
		}

		else {
			while (!isEmpty(*stack)) {
				char tos = stack->stack[stack->tos];
				int precedence = precedence_stack(c);
				int tos_precedence = precedence_stack(tos);

				if (precedence <= tos_precedence) {
					output[j++] = pop(stack);
				} else {
					break;
				}
			}
			push(stack, c);
		}
	}

	while (!isEmpty(*stack)) {
		output[j++] = pop(stack);
	}
	output[j] = '\0';
}

int main() {
	STACK stack;

	stack.tos = -1;
	char input[S];
	char output[S] = "";

	printf("Please give me an infix expression to convert:");
	fflush(stdout);
	gets(input); 

	infixToPostFix(input, &stack, output);
	printf("Postfix: %s\n", output);
}
