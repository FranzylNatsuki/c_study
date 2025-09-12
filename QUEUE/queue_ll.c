// QUEUE - REGULAR [NOT CIRCULAR]

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 20

typedef struct node *nd;
struct node {
	int data; // or structure idk
	nd next;
} QUEUE_LL;


void create_queue(nd *front, nd *rear);
void enqueue(nd *front, nd *rear, int value);
int dequeue(nd *front, nd *rear);
bool isEmpty(nd *rear);

void create_queue(nd *front, nd *rear) {
	(*front) = NULL;
	(*rear) = NULL;
	return;
}

void enqueue(nd *front, nd *rear, int value) {
	nd temp = malloc(sizeof(QUEUE_LL)); // create temp
	temp->data = value;
	temp->next = NULL;
	if ((*rear) == NULL) {
		(*rear) = temp;
		(*front) = (*rear);
	} else {
		(*rear)->next = temp;
		*rear = temp;
	}
}

int dequeue(nd *front, nd *rear) {
	if (isEmpty(rear)) { // ignore para mu work
		return -1;   // ignore para mu work
	}		     // ignore para mu work

	int r;
	nd temp;
	temp = (*front);
	r = (*front)->data;
	(*front) = (*front)->next;
	if ((*front) == NULL) {
		(*rear) = NULL;
	}

	free(temp);
	return r; 
}

bool isEmpty(nd *rear) {
	if ((*rear) == NULL) {
		return true;	
	} else {
		return false;
	}
}

int main() {
	nd front, rear;
	create_queue(&front, &rear);

	// Enqueue some elements
	enqueue(&front, &rear, 10);
	enqueue(&front, &rear, 20);
	enqueue(&front, &rear, 30);
	enqueue(&front, &rear, 40);

	// Dequeue all elements
	printf("Dequeued: %d\n", dequeue(&front, &rear)); // 10
	printf("Dequeued: %d\n", dequeue(&front, &rear)); // 20
	printf("Dequeued: %d\n", dequeue(&front, &rear)); // 30
	printf("Dequeued: %d\n", dequeue(&front, &rear)); // 40

	// Try dequeue on empty queue
	printf("Dequeued: %d\n", dequeue(&front, &rear)); // underflow -> -1

	// Enqueue again to show queue still works after empty
	enqueue(&front, &rear, 100);
	enqueue(&front, &rear, 200);

	printf("Dequeued: %d\n", dequeue(&front, &rear)); // 100
	printf("Dequeued: %d\n", dequeue(&front, &rear)); // 200

	return 0;
}
