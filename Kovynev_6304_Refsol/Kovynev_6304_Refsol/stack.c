#include <stdlib.h>
#include <stdio.h>
#include "stack.h"


void push(Stack** head, int value)
{
	Stack *tmp = (Stack*)malloc(sizeof(struct Stack));
	tmp->value = value;
	tmp->next = *head;
	*head = tmp;
}

void pop(struct Stack **head)
{
	if (*head)
	{
		*head = (*head)->next;
	}
}

int top(struct Stack *head)
{
	return head->value;
}

int empty(struct Stack *head)
{
	if (head == NULL)
	{
		return 1;
	}

	else
	{
		return 0;
	}

}
