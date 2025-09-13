#include <iso646.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
// #include <stdlib.h>
// #include <string.h>

#define MAX_SIZE 6 
#define P 20
#define TA 10


typedef struct data {
	char prName[P];
	int prDur;
} PR;

typedef struct queue {
	PR adtque[MAX_SIZE];
	int front;
	int rear;
} QUEUE;

bool isFull(QUEUE q);


int create_queue(void) {	
	int ptr = 0;
	return ptr; // redundant af choi
}

void enqueue(QUEUE *q, PR value) {
	if (isFull(*q)) {
		return;
	} else {
		q->adtque[q->rear] = value;
		q->rear = (q->rear + 1)  % MAX_SIZE;
	}
}

PR dequeue(QUEUE *q) {
	PR pr = q->adtque[q->front];
	q->front = (q->front + 1) % MAX_SIZE;
	return pr;
}

bool isFull(QUEUE q) {
	if (q.front == (q.rear + 1) % MAX_SIZE) {
		return true;	
	} else {
		return false;
	}
}

bool isEmpty(QUEUE q) {
	if (q.front == q.rear ) {
		return true;	
	} else {
		return false;
	}
}

PR inputProcess(void) {
	PR pr;
	printf("\nProcess Name: ");
	fgets(pr.prName, 20, stdin);
	printf("\nDuration? ");
	scanf("%d", &pr.prDur);
	while (getchar() != '\n');
	return pr;
}

bool time_Share(void) {
	bool done = true;
	bool full, empty;
	int timetopProc;
	PR pr;
	QUEUE q;

	q.front = create_queue();
	q.rear = create_queue();
	
	while (!isFull(q)) {
		pr = inputProcess();
		enqueue(&q, pr);
	}

	while (!isEmpty(q)) {
		bool complete = false;
		pr = dequeue(&q);
		printf("\nProcessing %s", pr.prName);
		printf("\nDuration %d", pr.prDur);
		if (pr.prDur <= TA) {
			timetopProc = pr.prDur;
			complete = true;
		} else {
			timetopProc = TA;
			pr.prDur -= TA;
		}

		for (int i = 1; i <= timetopProc; i++) {	
			printf("\n%d has elapsed", i);
			fflush(stdout);
			sleep(1);
		}

		if (complete) printf("\nProcess %s is done", pr.prName);
		else {
			printf("\nProcess %s has %d seconds left", pr.prName, pr.prDur);
			if (isFull(q)) {
				done = false;
				break;
			} else {
				enqueue(&q, pr);
			}
		}
	}
	return done;
}

int main(void) {
	bool done;
	done = time_Share();
	if (done) 
		printf("\nAll Processes are complete...\n");
	else 
		printf("\nError");
	return 0;
}
