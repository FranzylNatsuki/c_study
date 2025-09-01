#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define S 6
#define P 20
#define TA 10

typedef struct {
    char prName[P];
    int prDur;
} PR;

typedef struct node *nd;
struct node {
    PR data;
    nd next;
} NODE;

void createQueue(nd *front, nd *rear);
void enQueue(nd *front, nd *rear, PR data );
PR deQueue(nd *front, nd *rear);
bool isEmpty(nd *rear);


void createQueue(nd *front, nd *rear) {
    *front = NULL;
    *rear = NULL;
}

void enQueue(nd *front, nd *rear, PR data ) {
    nd temp = malloc(sizeof(NODE));
    temp->data = data;
    temp->next = NULL;
    if (*rear == NULL) {
        *rear = temp;
        *front = *rear;
    }
    else {
        (*rear)->next = temp;
        *rear = temp;
    }
}

PR deQueue(nd *front, nd *rear) {
    PR data;
    data = (*front)->data;
    nd temp = *front;
    *front = temp->next;
    if (*front == NULL) {
        *rear = NULL;
    }
    free(temp);
    return data;
}

bool isEmpty(nd *rear) {
    if (*rear == NULL) {
        return true;
    }
    else {
        return false;
    }
}

PR inputProcess(void);
bool time_share(void);

PR inputProcess(void) {
    	PR process;
	for (int i = 0; i <= S; i++) {
	    printf("Process Name:\n");
	    fgets(process.prName, P, stdin);
	    fflush(stdin);
	    printf("Process Dur:\n");
	    scanf(" %d", &process.prDur);
	}
	    return process;
}

bool time_share(void) {
    int timetoProc;
    nd front, rear;
	bool done;
    createQueue(&front, &rear);

    PR process = inputProcess();
    enQueue(&front, &rear, process);
    bool empty = isEmpty(&rear);
    while (!empty) {
        bool complete = false;
        process = deQueue(&front, &rear);
        printf("Processing: %s\n", process.prName);
        printf("Process Dur: %d\n", process.prDur);
        if (process.prDur <= 10) {
            timetoProc = process.prDur;
            complete = true;
        } else {
            timetoProc = TA;
            process.prDur -= TA;
        }
        // timetoProc *= 1000;
        sleep(timetoProc);
        if (complete == true) {
            printf("Process complete\n");
        } else {
            printf("Process %s has %d seconds left\n", process.prName, process.prDur);
            enQueue(&front, &rear, process);
        }
        empty = isEmpty(&rear);
        done = complete;
    }
    return done;
}

int main() {
    bool done = time_share();

    if (done) {
        printf("All processes are complete\n");
    } else {
        printf("an error was encountered\n");
    }
    getchar();
    return 0;
}
