// when asked for a string which only contains the characters [, (, {, evaluate 
// the strings if they are valid. Valid meaning that each symbol is closed by their respective }, ), ], closing characters. ALSO order matters, [ should be immediatelly closed by a ].
// Push an opening character to the stack, when it peek() == the current closing character, pop the stack
// The string is valid if the stack is empty

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STRING_MAX 10

typedef struct node *nd;
struct node{
	char data;
	nd next;
} STACK;

void push(nd *top, char data);
char pop(nd *top);
char peek(nd *top);
bool isEmpty(nd *top);

void push(nd *top, char data) {
	nd temp = malloc(sizeof(STACK));
	temp->data = data;
	temp->next = *top;
	*top = temp;
}

char pop(nd *top) {
	if (isEmpty(top)) exit(1);
	else {
		int data = (*top)->data;
		nd temp = *top;
		*top = temp->next;
		free(temp);
		return data;
	}
}

char peek(nd *top) {
	return (*top)->data;
}

bool isEmpty(nd *top) {
	return *top == NULL;	
}

int main() {
	char code[STRING_MAX]; 
	nd top = NULL;

	printf("Give me string of symbols that only contain ( { [ and are closed right after\n");

	if (fgets(code, STRING_MAX, stdin)) {
	    size_t len = strlen(code);
	    if (len > 0 && code[len - 1] == '\n') {
		code[len - 1] = '\0';
	    }
	}

	int string_length = strlen(code);
	bool isValid = true;

	for(int i = 0; i < string_length; i++) {
		char current = code[i];

		if(current == '(' || current == '{' || current == '[') {
			push(&top, current);
		} 

		else if ((current == ')' || current == '}' || current == ']') || isValid != false) {
			switch (current) {
				case ')':
					if (peek(&top) == '(' && !isEmpty(&top)) {
						pop(&top);
					} else {
						isValid = false;
						break;
					}
					break;
				case '}':
					if (peek(&top) == '{' && !isEmpty(&top)) {
						pop(&top);
					} else {
						isValid = false;
						break;
					}
					break;
				case ']':
					if (peek(&top) == '[' && !isEmpty(&top)) {
						pop(&top);
					} else {
						isValid = false;
						break;
					}
					break;
			}
		}
	}

	(isValid) ? printf("valid\n") : printf("invalid\n");
}
