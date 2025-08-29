#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node *nd; 
struct node {
	int data;
	nd next;
} STACK;

void push(nd *stack, int item);
int pop(nd *stack);
int peek(nd *stack);
bool isEmpty(nd *stack);

void push(nd *stack, int item) {
	nd temp = malloc(sizeof(STACK)); // DONT FORGET TO MAKE THE NODE ITSELF
	temp->data = item; // assign the value
	temp->next = *stack; // insert to the last item added
	// [temp] -> [*stack (tos)] -> [] -> []
	*stack = temp;
}

int pop(nd *stack) {
	if (isEmpty(stack)) return -1; // check first before popping

	nd temp = *stack; // set temp as stack because we will remove it
	int val = (*stack)->data; // store the data
	*stack = temp->next; // move the stack backwards
	// [*stack / temp] -> [] -> [] -> []
	free(temp); // remove
	return val;
}

int peek(nd *stack) {
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

int readLine(void) {
	int var;
	scanf("%d",&var);
	return var;
}

void empty(nd *stack) {
	while (!isEmpty(stack)) {
		printf("Popped: %d\n", pop(stack));
	}
}

int main() {
	nd s = NULL;
	int choice;

	while (choice != 5) {
		printf("1: Push\n");
		printf("2: Pop\n");
		printf("3: Peek\n");
		printf("4: Empty\n");
		printf("5: Stop\n");
		fflush(stdout);
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("Push: \n");
				int input;
				scanf("%d", &input);
				push(&s, input);
				break;
			case 2:
				printf("Popped: %d\n", pop(&s));
				break;
			case 3:
				printf("Peek: %d \n", peek(&s));	
				break;
			case 4:
				printf("Empty: \n");
				empty(&s);
				break;	
			case 5:
				return 0;	
		}
	}
}
/*
int main() {
    nd s = NULL;

    printf("Pushing elements...\n");
    for (int i = 1; i <= 6; i++) {
        push(&s, i * 10);
    }
    
    if (!isEmpty(&s))
        printf("Top element: %d\n", peek(&s));

    printf("Popping elements...\n");
    int val;
    while (!isEmpty(&s)) {
        val = pop(&s);   // ✅ actually pop here
        printf("Popped: %d\n", val);
    }

    // try popping when empty
    val = pop(&s);

    return 0;
}
*/
