#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct queue {
	int queue[MAX]; // start with data type
	int q_front;
	int q_rear;
} QUEUE;

 // BERTBERT METHODOLOGIES

QUEUE create_queue(QUEUE q);
QUEUE enqueue(QUEUE q, int value);
int dequeue(QUEUE *q);
bool isFull(int q_front, int q_rear);
bool isEmpty(int q_front, int q_rear);

QUEUE create_queue(QUEUE q) {
	for (int i = 0; i < MAX; i++) {
		q.queue[i] = 0;	
	}	
	q.q_front = 0;
	q.q_rear = -1;
	return q;
}

QUEUE enqueue(QUEUE q, int value) {
	q.q_rear++;
	q.queue[q.q_rear] = value;
	return q;
}

int dequeue(QUEUE *q) {
	int r;
	r = q->queue[q->q_front];
	q->q_front++;
	return r;
}

bool isFull(int q_front, int q_rear) {
	if (q_front == MAX - 1) {
		return true;
	} else {
		return false;
	}
}

bool isEmpty(int q_front, int q_rear) {
	if (q_rear < q_front) {
		return true;
	} else {
		return false;
	}
}


