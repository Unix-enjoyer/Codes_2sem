#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "vector.h"

///////////////////////////////
int numStrings(char fileName[6]) //да, это считывание кол-ва строк матрицы, я запарился
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
    return strings;

}

int numColumns(char fileName[6]) //да, это считывание кол-ва столбцов матрицы, я запарился
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
    return columns;
}

void delete(Vector vector, int element) // для суммирования матриц
{ // типо удаление элемента, не двусвязный, неудобно, двигать еще все
    for (int i = 0; i < vector->size; i++) {
        if (vector->value[i] == element) {
            vector->value[i] = -9999;
            return; // выход - нет лишним итерациям
        }
    }
}

int first(Vector vector) // для суммирования матриц
{
    for (int i = 0; i < vector->size; i++) {
        if (vector->value[i] != -9999) {
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
            break;
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
            paste(elements, elem); // вставляем в массив значений

            if (elem != 0) {
                index = i * 10 + j % columns;
                pasteZero(indexes, i * 10 + j % columns);
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

    paste(elements, elem); // из-за eof цикл не дорабатывает последнюю итерацию

    if (elements->size > indexes->size) { // если не совпадает длина, значит в массив индексов не добавлено последнее значение
        pasteZero(indexes, i * 10 + j % columns);
    }

    fclose(file_p);

}

void matrixSumm(Vector elements1, Vector indexes1, Vector elements2, Vector indexes2, Vector elementsRes, Vector indelementRes) // складывает и проверяет, явл ли симметрич.
{ // у
    int strings = numStrings("matr1");
    int columns = numColumns("matr1");
    int indexx = 0;
    for (int i = 0; i < numStrings("matr1");i++) {
        for (int j = 0; j < numColumns("matr1");j++) {
            indexx = i * 10 + j % columns;
            //printf("%d ", indexx);
            if (inMatrix(indexes1, indexx) && inMatrix(indexes2, indexx)) {
                paste(elementsRes, first(elements1) + first(elements2));
                delete(elements1, first(elements1));
                delete(elements2, first(elements2));
                pasteZero(indelementRes, indexx);
            } else if (inMatrix(indexes1, indexx)) {
                paste(elementsRes, first(elements1));
                delete(elements1, first(elements1));
                pasteZero(indelementRes, indexx);
            } else if (inMatrix(indexes2, indexx)) {
                paste(elementsRes, first(elements2));
                delete(elements2, first(elements2));
                pasteZero(indelementRes, indexx);
            }
        }
    }
}

void printNorm(Vector elements, Vector indexes) 
{
    int strings = numStrings("matr1");
    int columns = numColumns("matr1");
    int indexx;
    for (int i = 0; i < numStrings("matr1"); i++) {
        for (int j = 0; j < numColumns("matr1");j++) {
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

bool issim(Vector elements, Vector indexes)
{
    int strings = numStrings("matr1");
    int columns = numColumns("matr1");
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
}
