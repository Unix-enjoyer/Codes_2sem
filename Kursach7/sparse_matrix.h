#ifndef _SPARSE_MATRIX_ // Инициализация
#define _SPARSE_MATRIX_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "vector.h"

struct _sparsedM {
    Vector elements;
    Vector indexes;
};

typedef struct _sparsedM* sparsedM;

sparsedM constructor();

void makeTwoVectors(char fileName[16], Vector elements, Vector indexes);
void matrixSumm(Vector elements1, Vector indexes1, Vector elements2, Vector indexes2, Vector elementsRes, Vector indelementRes, char fileName[16]);
void printNorm(Vector elements, Vector indexes, char filename[16]);
bool issim(Vector elements, Vector indexes, char fileName[16]);
void freeMatr(sparsedM _sparsedMatr);

#endif // _SPARSE_MATRIX_