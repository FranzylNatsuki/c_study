#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CAPACITY 15

typedef struct queue {
	int queue[CAPACITY];
	int front;
	int rear;
} QUEUE;

bool isEmpty(QUEUE *queue) {
	return queue->rear < queue->front;
}

void enqueue(QUEUE *queue, int data) {
	if (queue->rear < CAPACITY - 1) {
		queue->queue[++queue->rear] = data;
	}
}

void dequeue(QUEUE *queue) {
	if (!isEmpty(queue)) {
		queue->front++;
	}
}

int getFront(QUEUE *queue) {
	if (isEmpty(queue)) {
		return -1;
	} else {
		return queue->queue[queue->front];
	}
} 

void printQueue(QUEUE *queue) {
	if (isEmpty(queue)) {
		printf("Queue is empty!\n");
		return;
	}

	printf("Current Queue: \n");
	for (int i = queue->front; i <= queue->rear; i++) {
		printf("%d\n", queue->queue[i]);
	}
}

int main() {
	QUEUE queue;
	queue.front = 0;
	queue.rear = 0;

	enqueue(&queue, 10);
	printQueue(&queue);
	
	enqueue(&queue, 20);
	printQueue(&queue);

	enqueue(&queue, 30);
	printQueue(&queue);

	printf("Front element: %d\n", getFront(&queue));

	// Dequeue an element
	dequeue(&queue);
	printQueue(&queue);

	// Peek front element after dequeue
	printf("Front element after dequeue: %d\n", getFront(&queue));

	return 0;
}
