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

int numStrings(char fileName[6]);
int numColumns(char fileName[6]);
void delete_el(Vector vector, int element);
int first(Vector vector);
bool inMatrix(Vector matrix, int val);
int indMatrix(Vector matrix, int val);
void makeTwoVectors(char fileName[16], Vector elements, Vector indexes);
void matrixSumm(Vector elements1, Vector indexes1, Vector elements2, Vector indexes2, Vector elementsRes, Vector indelementRes, char fileName[16]);
void printNorm(Vector elements, Vector indexes, char filename[16]);
bool issim(Vector elements, Vector indexes, char fileName[16]);


#endif // _VECTOR_H_