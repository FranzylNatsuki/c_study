// QUEUE - REGULAR [NOT CIRCULAR]

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 20

typedef struct queue {
	int adtque[MAX_SIZE];
	int q_front;
	int q_rear;
} QUEUE;

QUEUE create_queue(QUEUE q) {
	for (int j = 0; j < MAX_SIZE; j++) {
		q.adtque[j] = 0; // Dawg what tf he mean NULL?
	}
	q.q_front = 0;
	q.q_rear = -1;
	return q;
}

QUEUE enqueue(QUEUE q, int value) {
	q.q_rear++;
	q.adtque[q.q_rear] = value;
	return q;
}

int dequeue(QUEUE *q) {
	int r;
	r = q->adtque[q->q_front];
	q->q_front++;
	return r;
}

bool isFull(QUEUE q) {
	if (q.q_rear == MAX_SIZE - 1) {
		return true;	
	} else {
		return false;
	}
}

bool isEmpty(QUEUE q) {
	if (q.q_front > q.q_rear) {
		return true;	
	} else {
		return false;
	}
}

int main() {
	QUEUE queue;
	queue = create_queue(queue);
	
	queue = enqueue(queue, 10);
	queue = enqueue(queue, 20);
	queue = enqueue(queue, 30);

	printf("Dequeued: %d\n", dequeue(&queue)); // should print 10
	printf("Dequeued: %d\n", dequeue(&queue)); // should print 20
	printf("Dequeued: %d\n", dequeue(&queue)); // should print 30
	printf("Dequeued: %d\n", dequeue(&queue)); // underflow -> -1

	return 0;
}
