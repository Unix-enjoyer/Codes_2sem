#include "sparse_matrix.h"
#include <limits.h>

///////////////////////////////
sparsedM constructor()
{
    sparsedM sparsedMatr = (sparsedM) malloc(sizeof(*sparsedMatr));

    Vector elements = (Vector) calloc(1, sizeof(*elements)); // массив для значений и для их слепленных индексов
    Vector indexes = (Vector) calloc(1, sizeof(*indexes));

    sparsedMatr->elements = elements;
    sparsedMatr->indexes = indexes;

    return sparsedMatr;

}

void freeMatr(sparsedM sparsedMatr)
{
    free(sparsedMatr->elements->value);
    free(sparsedMatr->elements);
    free(sparsedMatr->indexes->value);
    free(sparsedMatr->indexes);
    sparsedM tmp = sparsedMatr;
    sparsedMatr = NULL;
    free(tmp);
}

int numStrings(char fileName[6]) //да, это считывание кол-ва строк матрицы, я запарился
{
    FILE* file_p; // инициализация файла
    file_p = fopen(fileName, "r");

    int strings; // считываем размер матрицы в отдельную строку, там будет кол-во стр и стлб черех пробел
    char str_col[6]; // потом разобьем их по пробелу, функция вызывается 2 раза - на 1 она разбивает один раз по разделителю
    fgets(str_col, 6, file_p); // на 2 - запомнив, где закончила, делает это еще раз

    char* istr = strtok(str_col, " "); // потом преобразование в инт
    strings = atoi(istr);

    fclose(file_p);
    return strings;

}

int numColumns(char fileName[6]) //да, это считывание кол-ва столбцов матрицы, я запарился
{
    FILE* file_p; // инициализация файла
    file_p = fopen(fileName, "r");

    int columns; // считываем размер матрицы в отдельную строку, там будет кол-во стр и стлб черех пробел
    char str_col[6]; // потом разобьем их по пробелу, функция вызывается 2 раза - на 1 она разбивает один раз по разделителю
    fgets(str_col, 6, file_p); // на 2 - запомнив, где закончила, делает это еще раз

    char* istr = strtok(str_col, " "); // потом преобразование в инт

    istr = strtok(NULL, " ");
    columns = atoi(istr);
    fclose(file_p);
    return columns;
}

void delete_el(Vector vector, int element) // для суммирования матриц
{ // типо удаление элемента, не двусвязный, неудобно, двигать еще все
    for (int i = 0; i < vector->size; i++) {
        if (vector->value[i] == element) {
            vector->value[i] = INT_MAX;
            return; // выход - нет лишним итерациям
        }
    }
}

int first(Vector vector) // для суммирования матриц
{
    for (int i = 0; i < vector->size; i++) {
        if (vector->value[i] != INT_MAX) {
            //printf("%d", vector->value[i]);
            return vector->value[i];
        }
    }
}

bool inMatrix(Vector matrix, int val) 
{
    
    for (int k = 0; k < matrix->size; k++) {
        if (matrix->value[k] == val) {
            return true;
        }
    }
    return false;
}

int indMatrix(Vector matrix, int val) 
{
    for (int k = 0; k < matrix->size; k++) {
        if (matrix->value[k] == val) {
            return k;
        }
    }
    return -1;
}


void makeTwoVectors(char fileName[16], Vector elements, Vector indexes) // обрабатывает файл, делает 2 нужных по условию массива
{

    FILE* file_p; // инициализация файла
    file_p = fopen(fileName, "r");

    int strings, columns; // считываем размер матрицы в отдельную строку, там будет кол-во стр и стлб черех пробел
    char str_col[6]; // потом разобьем их по пробелу, функция вызывается 2 раза - на 1 она разбивает один раз по разделителю
    fgets(str_col, 6, file_p); // на 2 - запомнив, где закончила, делает это еще раз

    char* istr = strtok(str_col, " "); // потом преобразование в инт
    strings = atoi(istr);

    istr = strtok(NULL, " ");
    columns = atoi(istr);

    int elem = 0, i = 0, j = 0, index;
    char ch;
    
    while ((ch = getc(file_p)) != EOF) {

        if (!(isspace(ch))) { //продолжаем чтение, текущее число не закончилось
            elem = elem*10 + (ch - '0');
        }
        if (isspace(ch)) { // пробел - значит, закончилось
            paste(elements, elem, 1); // вставляем в массив значений

            if (elem != 0) {
                index = i * 10 + j % columns;
                paste(indexes, i * 10 + j % columns, 0);
            }
            elem = 0;

            if (ch == 040) { // пробел
                j++; // строка та же, только горизонтальный
            }
            if (ch == 012) { // ентер
                i++; // тк и то, и то увеличилось
                j++;
            }

        }

    }

    paste(elements, elem, 1); // из-за eof цикл не дорабатывает последнюю итерацию

    if (elements->size > indexes->size) { // если не совпадает длина, значит в массив индексов не добавлено последнее значение
        paste(indexes, i * 10 + j % columns, 0);
    }

    fclose(file_p);

}

void matrixSumm(Vector elements1, Vector indexes1, Vector elements2, Vector indexes2, Vector elementsRes, Vector indelementRes, char filename[16]) // складывает и проверяет, явл ли симметрич.
{ // у
    int strings = numStrings(filename);
    int columns = numColumns(filename);
    int indexx = 0;
    for (int i = 0; i < strings; i++) {
        for (int j = 0; j < columns;j++) {
            indexx = i * 10 + j % columns;
            //printf("%d ", indexx);
            if (inMatrix(indexes1, indexx) && inMatrix(indexes2, indexx)) {
                paste(elementsRes, first(elements1) + first(elements2), 1);
                delete_el(elements1, first(elements1));
                delete_el(elements2, first(elements2));
                paste(indelementRes, indexx, 0);
            } else if (inMatrix(indexes1, indexx)) {
                paste(elementsRes, first(elements1), 1);
                delete_el(elements1, first(elements1));
                paste(indelementRes, indexx, 0);
            } else if (inMatrix(indexes2, indexx)) {
                paste(elementsRes, first(elements2), 1);
                delete_el(elements2, first(elements2));
                paste(indelementRes, indexx, 0);
            }
        }
    }
}

void printNorm(Vector elements, Vector indexes, char filename[16]) 
{
    int strings = numStrings(filename);
    int columns = numColumns(filename);
    int indexx;
    for (int i = 0; i < numStrings(filename); i++) {
        for (int j = 0; j < numColumns(filename);j++) {
            indexx = i * 10 + j % columns;
            if (inMatrix(indexes, indexx)) {
                printf("%d ", elements->value[indMatrix(indexes, indexx)]);
            } else {
                printf("0 ");
            } 
        }
        printf("\n");
    }
    printf("\n");
}

bool issim(Vector elements, Vector indexes, char filename[16])
{
    int strings = numStrings(filename);
    int columns = numColumns(filename);
    if (strings != columns) {
        return false;
    }  

    int indexx = 0;
    int index = 0;
    for (int k = 0; k < strings; k++) {
        for (int i = 0 + k; i < strings; i++) {
            for (int j = 0 + k; j < columns; j++) {

                indexx = i * 10 + j % columns;
                index = j * 10 + i % columns;

                if (inMatrix(indexes, indexx) && inMatrix(indexes, index)) {
                    if (elements->value[indMatrix(indexes, indexx)] != elements->value[indMatrix(indexes, index)]) {
                        return false;
                    }
                } else if (inMatrix(indexes, indexx) || inMatrix(indexes, index)) {
                    return false;
                }

            }
            break;
        }
    }
    return true;
}
////////////////////////////