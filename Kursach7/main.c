#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "vector.h"
#include "functions.h"

int main()
{
    char file1Name[16];
    printf("Введите имя 1 файла входных данных, не более 16 символов:\n");
    scanf(" %s", file1Name); // ввод имени входного файла 1
    Vector elements1 = (Vector) malloc(sizeof(*elements1)); // массив для значений и для их слепленных индексов
    Vector indexes1 = (Vector) malloc(sizeof(*indexes1));

    char file2Name[16];
    printf("Введите имя 2 файла входных данных, не более 16 символов:\n");
    scanf(" %s", file2Name); // ввод имени входного файла 2
    Vector elements2 = (Vector) malloc(sizeof(*elements2)); // массив для значений и для их слепленных индексов
    Vector indexes2 = (Vector) malloc(sizeof(*indexes2));

    Vector elements = (Vector) malloc(sizeof(*elements));
    Vector indexes = (Vector) malloc(sizeof(*indexes));

    makeTwoVectors(file1Name, elements1, indexes1);
    printNorm(elements1, indexes1);
    print(elements1);

    makeTwoVectors(file2Name, elements2, indexes2);
    printNorm(elements2, indexes2);
    print(elements2);
    
    matrixSumm(elements1, indexes1, elements2, indexes2, elements, indexes);
    printNorm(elements, indexes);
    print(elements);
    if (issim(elements, indexes)) {
        printf("Матрица симметрическая\n");
    } else {
        printf("Матрица не симметрическая\n");
    }
        
    free(elements2->value);
    free(elements2);

    free(indexes2->value);
    free(indexes2);

    free(elements1->value);
    free(elements1);

    free(indexes1->value);
    free(indexes1);

    free(elements->value);
    free(elements);

    free(indexes->value);
    free(indexes);
}
