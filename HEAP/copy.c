#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FULL_CAP 100

#define Flush while(getchar() != '\n')

typedef struct print_job {
    int pages;
    char doc_title[FULL_CAP];
    char mac_address[FULL_CAP];
} PRINT;

typedef struct heap {
    PRINT heap[20];
    int size;
}HEAP;

void menu(void);
char input(void);
PRINT create_print(void);
void heapify(int i, PRINT heap[], int size);
void swap(PRINT *a, PRINT *b);
void insert(PRINT x, HEAP *pq);
PRINT deleteMax(HEAP *pq);
void Delete_Report(PRINT deleted);
void Display(HEAP H);
void Build_Heap(HEAP *H);

void menu(void) {
    printf("Print Job Simulation\n");
    printf("A] Submit a print job\n");
    printf("B] Print the Print Job at the Front of the Queue\n");
    printf("C] View All the Jobs in the Queue\n");
    printf("D] Terminate\n");
}

char input(void) {
    char choice;
    printf("Enter choice: ");
    scanf("%c", &choice);
    Flush;
    return choice;
}

bool isFull(HEAP H) {
	return H.size == FULL_CAP;
}

bool isEmpty(HEAP H) {
	return H.size == 0;
}

PRINT create_print(void) {
    PRINT print_job;

    printf("How many Pages?\n");
    scanf("%d", &print_job.pages);
    Flush;

    printf("Document Title:\n");
    gets(print_job.doc_title);
    print_job.doc_title[strcspn(print_job.doc_title, "\n")] = 0;

    printf("Mac Address:\n");
    gets(print_job.mac_address);
    print_job.doc_title[strcspn(print_job.doc_title, "\n")] = 0;

    return print_job;
}

void heapify(int i, PRINT heap[], int size) {
    int l, r, larger;
    l = 2 * i;
    r = 2 * i + 1;

    if ((l <= size) && (heap[l].pages > heap[i].pages))
        larger = l;
    else
	larger = i;
    if ((r <= size) && (heap[r].pages > heap[larger].pages))
        larger = r;
    if (larger != i) {
        swap(&heap[i], &heap[larger]);
        heapify(larger, heap, size);
    }
}

void swap(PRINT *a, PRINT *b) {
    PRINT temp = *a;
    *a = *b;
    *b = temp;
}

void insert(PRINT x, HEAP *pq) {
    int i = ++(pq->size);
    while (i > 1 && pq->heap[i/2].pages < x.pages) {
        pq->heap[i] = pq->heap[i/2];
        i = i / 2;
    }
    pq->heap[i] = x;
}

PRINT deleteMax(HEAP *pq) {
    PRINT max = pq->heap[1];
    pq->heap[1] = pq->heap[pq->size];
    pq->size--;

    heapify(1, pq->heap, pq->size);
    return max;
}

void Delete_Report(PRINT deleted) {
    printf("Successfully Deleted Print Job: %s with %d page/s of MAC address: %s\n", deleted.doc_title, deleted.pages, deleted.mac_address);
}

void Display(HEAP H) {
    printf("%-5s %-5s %-20s %-20s\n", "Index", "Pages", "Title", "Mac Address");
    printf("---------------------------------------------------------\n");

    HEAP Display_Struct;
    Display_Struct = H;
    int i = 1;

    while (Display_Struct.size != 0) {
	PRINT job = deleteMax(&Display_Struct);
	printf("%-5d %-5d %-20s %-20s\n", i, job.pages , job.doc_title, job.mac_address);
    }
}

void Display_Linear(HEAP H) {
    printf("%-5s %-5s %-20s %-20s\n", "Index", "Pages", "Title", "Mac Address");
    printf("---------------------------------------------------------\n");
    for (int i = 1; i <= H.size; i++) {
	printf("%-5d %-5d %-20s %-20s\n", i, H.heap[i].pages , H.heap[i].doc_title, H.heap[i].mac_address);
    }
}

void Build_Heap(HEAP *H) {
    for (int i = H->size / 2; i >= 1; i--) {
        heapify(i, H->heap, H->size);
    }
}

int main(void) {
    char choice;
    HEAP priority_queue;
    priority_queue.size = 0;
    priority_queue.heap[0].pages = 0;
    bool isRepeat = true;

    while (isRepeat) {
        menu();
        choice = input();

        switch (choice) {
            case 'A':
            case 'a': {
                PRINT print_job;
                print_job = create_print();
                insert(print_job, &priority_queue);
                printf("Input Successful!\n");
            }
		Build_Heap(&priority_queue);
                isRepeat = true;
                break;
            case 'B':
            case 'b':
		if (priority_queue.size > 0) {
        		Delete_Report(deleteMax(&priority_queue));
			Build_Heap(&priority_queue);
		} else {
			printf("Heap is Empty!\n");
		}
		isRepeat = true;
                break;
            case 'C':
            case 'c':
                Display(priority_queue);
                isRepeat = true;
                break;
            case 'D':
            case 'd':
                isRepeat = false;
                exit(0);
		break;
	    case 'E':
	    case 'e':
		Build_Heap(&priority_queue);
		Display_Linear(priority_queue);
		isRepeat = true;
		break;
	    default:
		printf("Incorrect Input!\n");
        }
    }
}
