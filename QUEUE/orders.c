#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ORDERS 5

typedef struct order {
	bool served;
	char name[20];
	char ordertype[20];
} ORDER;

typedef struct node *nd;
struct node {
	ORDER data; // or structure idk
	nd next;
} QUEUE_LL;

void create_queue(nd *front, nd *rear);
void enqueue(nd *front, nd *rear, ORDER obj);
ORDER dequeue(nd *front, nd *rear);
bool isEmpty(nd *rear);

void create_queue(nd *front, nd *rear) {
	(*front) = NULL;
	(*rear) = NULL;
	return;
}

void enqueue(nd *front, nd *rear, ORDER obj) {
	nd temp = malloc(sizeof(QUEUE_LL)); // create temp
	temp->data = obj;
	temp->next = NULL;
	if ((*rear) == NULL) {
		(*rear) = temp;
		(*front) = (*rear);
	} else {
		(*rear)->next = temp;
		*rear = temp;
	}
}

ORDER dequeue(nd *front, nd *rear) {
	if (isEmpty(rear)) { // ignore para mu work
		exit(1);   // ignore para mu work
	}		     // ignore para mu work

	ORDER r;
	nd temp;
	temp = (*front);
	r = (*front)->data;
	(*front) = (*front)->next;
	if ((*front) == NULL) {
		(*rear) = NULL;
	}

	free(temp);
	return r; 
}

bool isEmpty(nd *rear) {
	if ((*rear) == NULL) {
		return true;	
	} else {
		return false;
	}
}

void take_orders(nd *front, nd *rear) {
	for (int i = 0; i < MAX_ORDERS; i++) {
		ORDER instance;
		char enum_key[20];
		printf("\nName: ");
		fgets(instance.name, 20, stdin);
		instance.name[strcspn(instance.name, "\n")] = 0;
		printf("\nOrder Type: | --c1 or --c2 or --c3: ");
		fgets(instance.ordertype, 20, stdin);
		instance.ordertype[strcspn(instance.ordertype, "\n")] = 0;
		instance.served = false;
		enqueue(front, rear, instance);
	}
}

void fill_set(ORDER set[]) {
	strcpy(set[0].ordertype, "--c1");
	strcpy(set[1].ordertype, "--c2");
	strcpy(set[2].ordertype, "--c1");
	strcpy(set[3].ordertype, "--c3");
	strcpy(set[4].ordertype, "--c2");
	strcpy(set[5].ordertype, "--c1");
	strcpy(set[6].ordertype, "--c1");
	strcpy(set[7].ordertype, "--c2");
	strcpy(set[8].ordertype, "--c2");
	strcpy(set[9].ordertype, "--c3");
	strcpy(set[10].ordertype, "--c2");
	strcpy(set[11].ordertype, "--c2");
	strcpy(set[12].ordertype, "--c1");
	strcpy(set[13].ordertype, "--c3");
	strcpy(set[14].ordertype, "--c2");
}

int main() {
	// take orders, chef makes a pre-defined set of meals, those who don't get the right order will have to be re-enqueued
	ORDER set[15];
	fill_set(set);

	nd rear, front;

	take_orders(&front, &rear);

	int order_count = 0;
	while (!isEmpty(&rear) && order_count < 15) {
		ORDER current = dequeue(&front, &rear);

		if (strcmp(set[order_count].ordertype, current.ordertype) == 0) {
			current.served = true;
			printf("Finished %s's order: %s\n", current.name, current.ordertype);
		} else {
			printf("Wrong order for %s, recieved: %s\n", current.name, set[order_count].ordertype);
			enqueue(&front, &rear, current);
		}
		order_count++;
	}

	while (!isEmpty(&rear)) {
		if (!front->data.served) {
			printf("%s has not been served, fam they aint happy\n", front->data.name);
		}
		dequeue(&front, &rear);
	}
}
