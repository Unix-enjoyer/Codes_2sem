#include "vector.h"


int size(Vector vector) { // вернуть длину (обрааем внимание на моменте создания - не выделить лишнего, 
    return vector->size; // а то длина будет равно кол-ву элементов, а не ненулевых значений)
}

void print(Vector vector) { // вывести подряд элементы вектора
    printf("[ ");
    for (int i = 0; i < vector->size; i++) {
        printf("%d ", vector->value[i]);
    }
    printf("]\n\n");
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

void pasteZero(Vector vector, int element) { // вставляет нули, в отличии от предыдущей
    for (int i = 0; i < vector->size; i++) { // нужна для заполнения индексов, шде могут встретиться нули
            if (vector->value[i] == -9999) { // пример: 01 запишется как 1, 00 как 0
                vector->value[i] = element;
                return; // и выходим из функции
            }
        }
        vector->value = (int*) realloc(vector->value, (vector->size + 1) * sizeof(int)); // дошли сюда - значит
        vector->value[vector->size] = -9999;
        vector->size++; // места не нашлось, довыделим память под новый элемент
        pasteZero(vector, element); // размер увеличился, теперь спокойно ставим его
}