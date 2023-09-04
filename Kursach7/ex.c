#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "vector.h"

///////////
void create(Vector vector, int size) { // создание вектора

    vector->value = (int*) calloc(size, sizeof(int)); // выделить память под него
    vector->size = size; // размер в соответствии с вводом
}

bool empty(Vector vector) { // пустой ли?
    if (vector->size == 0) {
        return 1;
    } else {
        return 0;
    }
}

int size(Vector vector) { // вернуть длину (обрааем внимание на моменте создания - не выделить лишнего, 
    return vector->size; // а то длина будет равно кол-ву элементов, а не ненулевых значений)
}

void print(Vector vector) {
    for (int i = 0; i < vector->size; i++) {
        printf("%d ", vector->value[i]);
    }
    printf("\n");
}

void paste(Vector vector, int element) { // если индекс существует и знач не 0, то вставить в вектор

    if (element!= 0) {
        for (int i = 0; i < vector->size; i++) { // если не 0, значит место свободно, ставим его
            if (vector->value[i] == 0) {
                vector->value[i] = element;
                return; // и выходим из функции
            }
        }
        vector->value = (int*) realloc(vector->value, (vector->size + 1) * sizeof(int)); // дошли сюда - значит
        vector->value[vector->size] = 0;
        vector->size++; // места не нашлось, довыделим память под новый элемент
        paste(vector, element); // размер увеличился, теперь спокойно ставим его
    }
}

void pasteZero(Vector vector, int element) {
    for (int i = 0; i < vector->size; i++) { // если не 0, значит место свободно, ставим его
            if (vector->value[i] == -9999) {
                vector->value[i] = element;
                return; // и выходим из функции
            }
        }
        vector->value = (int*) realloc(vector->value, (vector->size + 1) * sizeof(int)); // дошли сюда - значит
        vector->value[vector->size] = -9999;
        vector->size++; // места не нашлось, довыделим память под новый элемент
        pasteZero(vector, element); // размер увеличился, теперь спокойно ставим его
}
///////////

int main()
{
    char file1Name[16];
    printf("Введите имя 1 файла входных данных, не более 16 символов:\n");
    scanf(" %s", file1Name); // ввод имени входного файла

    FILE* file1_p; // инициализация файла
    file1_p = fopen(file1Name, "r");

    int strings1, columns1; // считываем размер матрицы в отдельную строку, там будет кол-во стр и стлб черех пробел
    char str_col[6]; // потом разобьем их по пробелу, функция вызывается 2 раза - на 1 она разбивает один раз по разделителю
    fgets(str_col, 6, file1_p); // на 2 - запомнив, где закончила, делает это еще раз

    char* istr = strtok(str_col, " "); // потом преобразование в инт
    strings1 = atoi(istr);

    istr = strtok(NULL, " ");
    columns1 = atoi(istr);
    printf("%d %d\n", strings1, columns1);
    
    Vector elements = (Vector) malloc(sizeof(*elements)); // массив для значений и для их слепленных индексов
    Vector indexes = (Vector) malloc(sizeof(*indexes));

    int elem = 0, i = 0, j = 0, index;
    char ch;
    
    while ((ch = getc(file1_p)) != EOF) {

        if (!(isspace(ch))) { //продолжаем чтение, текущее число не закончилось
            elem = elem*10 + (ch - '0');
        }
        if (isspace(ch)) { // пробел - значит, закончилось
            paste(elements, elem); // вставляем в массив значений
            //printf("elem = %d ", elem);
            
            // играемся с индексами...
            // сложение матриц надо будет
            //printf("str = %d stlb = %d\n", i, j % columns1);

            if (elem != 0) {
                index = i * 10 + j % columns1;
                pasteZero(indexes, i * 10 + j % columns1);
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
    printf("\n");
    print(elements);
    printf("\n");
    print(indexes);
    printf("\n");
    if (elements->size > indexes->size) {
        pasteZero(indexes, i * 10 + j % columns1);
        //print(indexes);
        //printf("elem = %d str = %d stlb = %d\n", elem, i, j % columns1);// из-за eof цикл не дорабатывает последнюю итерацию !!//paste(indexes, )
    }

    fclose(file1_p);

//*/
























/*
    char file2Name[16];
    printf("Введите имя 2 файла входных данных, не более 16 символов:\n");
    scanf("%s", file2Name); // ввод имени входного файла

    FILE* file2_p; // инициализация файла
    file2_p = fopen(file2Name, "r");
    
    int strings2, columns2; // считываем размер матрицы в отдельную строку, там будет кол-во стр и стлб черех пробел
    //char str_col[6]; // потом разобьем их по пробелу, функция вызывается 2 раза - на 1 она разбивает один раз по разделителю
    fgets(str_col, 6, file2_p); // на 2 - запомнив, где закончила, делает это еще раз
    
    istr = strtok(str_col, " "); // потом преобразование в инт
    strings2 = atoi(istr);

    istr = strtok(NULL, " ");
    columns2 = atoi(istr);

    fclose(file2_p);*/
    return 0;
}