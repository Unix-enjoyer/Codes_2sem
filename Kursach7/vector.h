#ifndef _VECTOR_H_ // Инициализация
#define _VECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct _vector* Vector;

struct _vector {
    int size;
    int* value;
};


void paste(Vector vector, int element, bool parametr);
int size(Vector vector);
void print(Vector vector);

#endif // _VECTOR_H_