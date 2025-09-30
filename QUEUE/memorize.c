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

QUEUE create_queue(QUEUE q) {
	// bertbert quirk: set all array index content to 0 or NULL?

	for (int j = 0; j < MAX; j++) {
		q.queue[j] = 0; // flushes all content 
	}	

	q.q_front = 0; //set front to 0 for NON-CIRCULAR 
	q.q_rear = -1; //set rear to -1 for NON-CIRCULAR
	return q; // either return a struct, or keep it as void
}

QUEUE create_circular(QUEUE q) {
	q.q_front = 0;
	q.q_rear = 0;
	// Always remember that circular is BOTH set to 0
	return q;
}

QUEUE enqueue(QUEUE q, int value) {
	q.q_rear++; // Increment the rear first to make it 0, unlike circular. This will put it in the first box
	q.queue[q.q_rear] = value; // set this to the data, based on the rear position
	//
	return q;
}

QUEUE enqueue_circular(QUEUE q, int value) {
	q.queue[q.q_rear] = value; // immediately set the value because it's already on the correct spot
	q.q_rear = (q.q_rear + 1) % MAX;
	// do the math of setting the rear to
	// (rear + 1) modulo to the MAX capacity
	return q;
}

int dequeue(QUEUE *q) {
	int r; // temporary variable
	r = q->queue[q->q_front]; // r's value is the array's index at the front of the queue, removing what's on front
	q->q_front++; // now move the front because that value is now gone
	return r;
}

int dequeue_circular(QUEUE *q) {	
	int r;
	r = q->queue[q->q_front];
	q->q_front = (q->q_front + 1) % MAX;
	// basically take enqueue and swap  the variables from rear to front
	return r;
}

bool isFull(int q_front, int q_rear) {
	if (q_rear == MAX - 1) {
	// in is Full, check if the rear has reached MAX - 1
		return true;
		// if it is then it's FULL
	}
		return false;
}

bool isFull_circular(int q_front, int q_rear) {
	if (q_front == ((q_rear + 1) % MAX)) {
	// if front is equal to the equation 
	// (rear + 1) % MAX
		return true;	
	} else {
		return false;
	}
}

bool isEmpty(int q_front, int q_rear) {
	if (q_front > q_rear) {
	// check if front is BIGGER than rear
	// in the start 0 front is bigger than -1 rear,
		// making it emptyh
		return true;
	} else {
		return false;
	}
}

bool isEmpty_circular(int q_front, int q_rear) {
	if (q_front == q_rear) {
	// for is empty, check if both are EQUAL
		return true;
	} else {
		return false;
	}
}


