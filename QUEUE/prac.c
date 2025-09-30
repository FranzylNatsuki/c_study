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
	*front = NULL;
	*rear = NULL;
}

void enqueue(nd *front, nd *rear, int value) {
	nd temp = malloc(sizeof(QUEUE_LL));
	temp->data = value;
	temp->next = NULL;
	if ((*rear) == NULL) {
		(*rear) = temp;
		(*front) = (*rear);
	} else {
		(*rear)->next = temp;
		(*rear) = temp;
	}
	return;
}

int dequeue(nd *front, nd *rear) {
	nd temp = *front;
	int val = temp->data;
	(*front) = (*front)->next;
	if ((*front) == NULL) {
		(*rear) = NULL;
	}
	free(temp);
	return val;
}

bool isEmpty(nd *rear) {
}
