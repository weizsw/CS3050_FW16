#ifndef H_STACK_H
#define H_STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INIT_STACK_SIZE 32

enum stack_errors
{
	OUT_OF_BOUNDS_STACK = -1,
};

struct stack
{
	unsigned int* data;
	unsigned int  topindex;
	unsigned int  capacity;
};

void init_stack(struct stack* st);
unsigned int top(struct stack *st);
void push(struct stack *st, unsigned int element_to_push);
unsigned int isempty (struct stack *st);
unsigned int pop (struct stack *st);
void free_stack(struct stack *st);
void print_stack(struct stack *st);
#endif
