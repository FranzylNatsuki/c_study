#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node *nd;
struct node{
	int data;
	int index; //represent's the stacked numbers locator in the array
	nd next;
} STACK;

typedef struct pairs {
	int value;
	int nextGreater;
} PAIRS;

void push(nd *top, int data, int index);
int pop(nd *top);
int peak(nd *top);
bool isEmpty(nd *top);

void push(nd *top, int data, int index) {
	nd temp = malloc(sizeof(STACK));
	temp->data = data;
	temp->index = index;
	temp->next = *top;
	*top = temp;
}

int pop(nd *top) {
	if (isEmpty(top)) exit(1);
	else {
		int data = (*top)->data;
		nd temp = *top;
		*top = temp->next;
		free(temp);
		return data;
	}
}

int peek(nd *top) {
	return (*top)->data;
}

bool isEmpty(nd *top) {
	return *top == NULL;	
}

int main(void) {
	nd top = NULL;
	PAIRS pairs[6];

	int array[6] = {4, 2, 5, 3, 1, 6};

	for (int i = 0; i < 6; i++) {
		pairs[i].value = array[i]; // initialize output for those with no small numbers
		pairs[i].nextGreater = -1; // no next greater
		if (isEmpty(&top)) {
			push(&top, array[i], i);
		}
		else {
			while (!isEmpty(&top) && array[i] > peek(&top)) {
				int current_index = top->index;
				int popped_value = pop(&top);
				pairs[current_index].value = popped_value;
				pairs[current_index].nextGreater = array[i];
			}	// else push(&top, array[i], i);
			push(&top, array[i], i);
		}
	}

	while (!isEmpty(&top)) { // for elements with no next greater
		int current_index = top->index;
		int popped_value = pop(&top);
		pairs[current_index].value = popped_value;
		pairs[current_index].nextGreater = -1;		
	}

	for (int i = 0; i < 6; i++) {
		if (pairs[i].nextGreater == -1) { 
			printf("%d -> %s\n", pairs[i].value, "None");
		} else {
			printf("%d -> %d\n", pairs[i].value, pairs[i].nextGreater);
		}
	}
}
