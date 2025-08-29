#ifndef STRUCTURE_H
#define STRUCTURE_H

#define MAX 5


typedef struct data {
	int id;
	char name[50];
} DATA;


typedef struct stack {
	int data[MAX];
	DATA dbmaster;
	int tos;
} STACK;

#endif // STRUCTURE_H
