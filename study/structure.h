#ifndef STRUCTURE_H
#define STRUCTURE_H

#define MAX 5

/*
typedef struct data {
	int data;
	char name[50];
} DATA;
*/

typedef struct stack {
	int data[MAX];
	int tos;
} STACK;

#endif // STRUCTURE_H
