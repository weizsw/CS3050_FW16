#include "../include/stack.h"

void init_stack(struct stack* st)
{
	st->data = malloc(sizeof(unsigned int) * INIT_STACK_SIZE);
	st->topindex = -1;
	st->capacity = INIT_STACK_SIZE;
}


unsigned int top(struct stack *st)
{
	if (st->topindex == -1)
		return -1;
	return st->data[st->topindex];
}

void push(struct stack *st, unsigned int element_to_push)
{
	if(st->capacity == st->topindex+1)
	{
		st->data = realloc(st->data, sizeof(int) * st->capacity * 2);
		st->capacity *= 2;
	}
       st->topindex+=1;
       st->data[st->topindex] = element_to_push;
	
}

unsigned int isempty(struct stack* st)
{
    if (st->topindex == -1) return 1;
    return 0;
}

unsigned int pop(struct stack* st)
{
    if (st->topindex!=-1)
    {
        return st->data[st->topindex--];
    }
	return OUT_OF_BOUNDS_STACK;
}

void free_stack(struct stack* st)
{
	free(st->data);
	st->topindex = 0;
    st->capacity = 0;
}



void print_stack(struct stack* st)
{   unsigned int i;
    for (i=0; i<=st->topindex; i++)
        printf("%u\n",st->data[i]);
}

