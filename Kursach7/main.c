#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "vector.h"
#include "sparse_matrix.h"

int main()
{
    char file1Name[16];
    printf("Введите имя 1 файла входных данных, не более 16 символов:\n");
    scanf(" %s", file1Name); // ввод имени входного файла 1

    sparsedM sparsedMatr1 = constructor();

    char file2Name[16];
    printf("Введите имя 2 файла входных данных, не более 16 символов:\n");
    scanf(" %s", file2Name); // ввод имени входного файла 2

    sparsedM sparsedMatr2 = constructor();
    
    sparsedM sparsedMatr = constructor();


    makeTwoVectors(file1Name, sparsedMatr1->elements, sparsedMatr1->indexes);
    printNorm(sparsedMatr1->elements, sparsedMatr1->indexes, file1Name);
    print(sparsedMatr1->indexes);

    makeTwoVectors(file2Name, sparsedMatr2->elements, sparsedMatr2->indexes);
    printNorm(sparsedMatr2->elements, sparsedMatr2->indexes, file2Name);
    print(sparsedMatr2->elements);
    
    matrixSumm(sparsedMatr1->elements, sparsedMatr1->indexes, sparsedMatr2->elements, sparsedMatr2->indexes, sparsedMatr->elements, sparsedMatr->indexes, file1Name);
    printNorm(sparsedMatr->elements, sparsedMatr->indexes, file1Name);
    print(sparsedMatr->elements);

    if (issim(sparsedMatr->elements, sparsedMatr->indexes, file1Name)) {
        printf("Матрица симметрическая\n");
    } else {
        printf("Матрица не симметрическая\n");
    }
    
    freeMatr(sparsedMatr1);
    freeMatr(sparsedMatr2);
    freeMatr(sparsedMatr);

}
