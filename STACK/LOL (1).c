#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    int arr[MAX_SIZE];
    int top;
} STACK;

void push(STACK *sk, int value);
int pop(STACK *sk);
int peek(STACK *sk);
bool isEmpty(STACK *sk);
bool isFull(STACK *sk);
int evaluatePostfix(char *expression, STACK *sk);

int main(void) {
    STACK sk = {{0}, -1};
    char expression[MAX_SIZE];
    printf("Enter a postfix expression (no spaces, single digits): ");
    fgets(expression, MAX_SIZE, stdin);
    expression[strcspn(expression, "\n")] = '\0';  

    int result = evaluatePostfix(expression, &sk);
    printf("Result: %d\n", result);

    return 0;
}

void push(STACK *sk, int value) {
    if (isFull(sk)) {
        printf("Stack Overflow!\n");
        return;
    }
    sk->arr[++sk->top] = value;
}

int pop(STACK *sk) {
    if (isEmpty(sk)) {
        printf("Stack Underflow!\n");
        exit(1);
    }
    return sk->arr[sk->top--];
}

int peek(STACK *sk) {
    if (isEmpty(sk)) {
        printf("Stack is empty!\n");
        exit(1);
    }
    return sk->arr[sk->top];
}

bool isEmpty(STACK *sk) {
    return sk->top == -1;
}

bool isFull(STACK *stk) {
    return stk->top == MAX_SIZE - 1;
}

int evaluatePostfix(char *expression, STACK *sk) {
    int i = 0;
    while (expression[i] != '\0') {
        char ch = expression[i];
        
        if (isdigit(ch)) {
            push(sk, ch - '0');  
        } else {
            int num2 = pop(sk);  
            int num1 = pop(sk);  
            int result;

            switch (ch) {
                case '+':
                    result = num1 + num2;
                    break;
                case '-':
                    result = num1 - num2;
                    break;
                case '*':
                    result = num1 * num2;
                    break;
                case '/':
                    if (num2 == 0) {
                        printf("Error: Division by zero\n");
                        exit(1);
                    }
                    result = num1 / num2;
                    break;
                default:
                    printf("Unknown operator: %c\n", ch);
                    exit(1);
            }

            push(sk, result); 
        }
        i++;  
    }

    return pop(sk);  
}
