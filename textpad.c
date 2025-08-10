#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>

#define S 50

typedef struct node *nd;
struct node {
	char text[S];
	nd next;
} STACK;

bool isEmpty(nd *head) {
	return *head == NULL;
}

void push(nd *head, char *text) {
	nd temp = malloc(sizeof(STACK));
	strcpy(temp->text, text);
	temp->next = *head;
	*head = temp;
}

void pop(nd *head, char *out) {
    if (*head == NULL) {
        printf("Stack is empty!\n");
        return;
    }

    nd temp = *head;                   // store current top
    strcpy(out, temp->text);           // copy popped text to caller's buffer
    *head = temp->next;                // move head to next node
    free(temp);                        // free the removed node
}



int main(void) {
	nd head = NULL;

	while (true) {
		
	}

}
