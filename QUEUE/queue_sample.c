#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node *nd;
struct node {
	int data;
	nd next;
} QUEUE;

typedef struct queue *node;
struct queue {
	nd front;
	nd rear;
} FUNC;

void enqueue(nd *front, nd *rear, int data) {
	if ((*front) == NULL) { 
		(*front) = malloc(sizeof(QUEUE));
		(*rear) = (*front);
		(*rear)->data = data;
	} else {	
		nd temp = malloc(sizeof(QUEUE));
		(*rear)->next = temp;
		(*rear) = temp;
		(*rear)->data = data;
		(*rear)->next = NULL;
	}
}

void dequeue(nd *front, nd *rear) {
	
}

int main(void) {

}
