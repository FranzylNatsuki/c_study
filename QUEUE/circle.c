#include <stdbool.h>
#define MAXSIZE 100

// Data structure for the stored data
typedef struct {
    int value;   // replace with any type you need
} Data;

// Circular queue structure
typedef struct {
    Data items[MAXSIZE];  // array to store elements
    int front;            // index of the front element
    int rear;             // index of the rear element
} CircularQueue;

void enqueue(CircularQueue queue, Data value) {
	queue.items[queue.rear] = value;
	queue.rear = ((queue.rear + 1) % MAXSIZE);
}

Data dequeue(CircularQueue queue) {
	Data value = queue.items[queue.front]; 
	queue.front = ((queue.front + 1) % MAXSIZE);
	return value;
}

bool isEmpty(int front, int rear) {
	if (front == rear) {
		return true;
	} else {
		return false;
	}
}

bool isFull(int front, int rear) {
	if (front == ((rear + 1) % MAXSIZE)) {
		return true;
	} else {
		return false;
	}
}
