#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100
#define INPUT_SIZE 200

typedef struct Stack {
    int data[STACK_SIZE];
    int size;
} Stack;

void init(Stack* stack);

void push(Stack* stack, int val);

int pop(Stack* stack, int* val);

void print(Stack* stack);

int main() {
    char* arr = (char*) malloc(INPUT_SIZE * sizeof(char));
    fgets(arr, INPUT_SIZE, stdin);

    Stack* stack = (Stack*) malloc(sizeof(Stack));
    init(stack);

    int val = 0;
    char opp;

    int a = 0;
    int b = 0;

    for(char* tok = strtok(arr, " "); tok != NULL; tok = strtok(NULL, " ")) {
        if(sscanf(tok, "%d", &val)) {
            push(stack, val);
        } else {
            sscanf(tok, "%c", &opp);
            if(pop(stack, &val)) {
                b = val;
            } else {
                printf("error\n");
                return 0;
            }
            if(pop(stack, &val)) {
                a = val;
            } else {
                printf("error\n");
                return 0;
            }
            switch(opp) {
                case '+':
                    push(stack, a + b);
                    break;
                case '-':
                    push(stack, a - b);
                    break;
                case '*':
                    push(stack, a * b);
                    break;
                case '/':
                    if(b != 0) {
                        push(stack, a / b);
                        break;
                    }
                default:
                    printf("error\n");
                    return 0;
            }
        }
    }
    if(stack->size > 1) {
        printf("error");
    } else {
        print(stack);
    }
}

void init(Stack* stack) {
    stack->size = 0;
}

void push(Stack* stack, int val) {
    stack->data[stack->size++] = val;
}

int pop(Stack* stack, int* val) {
    if(stack->size == 0) {
        return 0;
    } else {
        *val = stack->data[--stack->size];
        return 1;
    }
}

void print(Stack* stack) {
    for(int i = 0; i < stack->size; i++) {
        printf("%d ", stack->data[i]);
    }
}
