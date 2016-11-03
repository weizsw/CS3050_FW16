#ifndef H_VECTOR_H
#define H_VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INIT_VECTOR_SIZE 512

enum vector_errors
{
	OUT_OF_BOUNDS = 0,
};

struct vector
{
	unsigned int* data;
	unsigned int size;
	unsigned int capacity;
};

void init_vector(struct vector* v);
int access_element_vector(struct vector* v, unsigned int index);
void insert_element_vector(struct vector* v, unsigned int element_to_insert);
void free_vector(struct vector* v);
unsigned int size_vector(struct vector* v);
void print_vector(struct vector *v);
#endif
