// QUEUE - Circular 

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
	q.q_rear = 0;
	return q;
}

QUEUE enqueue(QUEUE q, int value) {
	q.adtque[q.q_rear] = value;
	q.q_rear = (q.q_rear + 1) % MAX_SIZE;
	return q;
}

int dequeue(QUEUE *q) {
	int r;
	r = q->adtque[q->q_front];
	q->q_front = (q->q_front + 1) % MAX_SIZE;
	return r;
}

bool isFull(int q_front, int q_rear) {
	if (q_front == ((q_rear + 1) % MAX_SIZE)) {
		return true;	
	} else {
		return false;
	}
}

bool isEmpty(int q_front, int q_rear) {
	if (q_front == q_rear) {
		return true;	
	} else {
		return false;
	}
}

int main() {
    QUEUE queue;
    queue = create_queue(queue);

    // Fill half of the queue
    for (int i = 1; i <= 10; i++) {
        queue = enqueue(queue, i);
    }

    // Dequeue a few elements (freeing up slots at the front)
    printf("Dequeued: %d\n", dequeue(&queue)); // 1
    printf("Dequeued: %d\n", dequeue(&queue)); // 2
    printf("Dequeued: %d\n", dequeue(&queue)); // 3
    printf("Dequeued: %d\n", dequeue(&queue)); // 4
    printf("Dequeued: %d\n", dequeue(&queue)); // 5

    // Enqueue more values, should wrap around to the start
    queue = enqueue(queue, 100);
    queue = enqueue(queue, 200);
    queue = enqueue(queue, 300);
    queue = enqueue(queue, 400);
    queue = enqueue(queue, 500);

    // Now dequeue everything to show order is preserved
    printf("\nRemaining queue contents:\n");
    while (!isEmpty(queue.q_front, queue.q_rear)) {
        printf("%d ", dequeue(&queue));
    }
    printf("\n");

    return 0;
}
