#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structure.h"
#include "datastructs.h"

#define MAX 5

int main() {
	STACK s;
	s.tos = -1;
	// DO NOT FORGET THAT TOS SHOULD BE INIT TO -1;

	printf("Pushing elements...\n");
	for (int i = 1; i <= 6; i++) {
	 	push(&s, i * 10);
	}

	int val;
	if (!isEmpty(s)) printf("Top element: %d\n", peek(s));

	printf("Popping elements...\n");
	while (!isEmpty(s)) {
		val = pop(&s);
        	printf("Popped: %d\n", val);
	}

    // try popping when empty
    	val = pop(&s);

    	return 0;
}
