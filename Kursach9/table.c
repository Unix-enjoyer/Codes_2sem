#include <stdio.h>
#include <string.h>
#include "table.h"
#include <stdlib.h>
#include <stdbool.h>

#define STRSIZE 100

table* createTable(int size) // создает таблицу указанноого размера
{
    table* tabl = (table*) malloc(sizeof(table)); // под структуру
    tabl->elem = NULL;
    tabl->size = size;
    tabl->elem = (element*) malloc(size * sizeof(element)); // выделение под ее элементы
    return tabl;
}

int sizeTable(table* tabl) // размер
{
    return tabl->size;
}

table* resizeTable(table* tabl) { // увеличить таблиццу на 1 ячейку
    int mem = (sizeTable(tabl) + 1) * sizeof(element)/*sizeof((tabl->elem[0]))*/; // текущий размер + 1
    element* resized = (element*) realloc(tabl->elem, mem); // меняется размер хранилища элементов
    tabl->elem = resized;
    resized = NULL;
    tabl->size++;
    return tabl; // но возвращаем новый указатель на таблицу
}

void fileRead(table* tabl, char filenameKeys[STRSIZE], char filenameVal[STRSIZE])
{
    FILE* keys = fopen(filenameKeys, "r");
    FILE* values = fopen(filenameVal, "r");
    
    char string[STRSIZE]; // построчно читаем файл значений, из каждой такой строки
    //float key; // вставляем всю строку в таблицу
    int i = 0; // построчно читаем другой файл, пишем в таблицу флоаты
    while ((fgets(string, STRSIZE, keys)) != NULL) {
        
        /*if (!( &(tabl->elem[i]) )) {
            resizeTable(tabl);
        }*/
        sscanf(string, "%g", &(tabl->elem[i].key));
        //printf("%f", tabl->elem[i].key);
        i++;
    }
    i = 0;
    while ((fgets(string, STRSIZE, values)) != NULL) {
        //sscanf(string, "%s", tabl->elem[i].value);
        string[strlen(string)-1] = '\0';
        strcpy(tabl->elem[i].value, string);

        //printf("%s", string);/*tabl->elem[i].value);*/
        i++;
    }
    fclose(keys);
    fclose(values);
}

void writeToFile(table* tabl, char filenameKeys[STRSIZE], char filenameValues[STRSIZE])
{
    FILE* keys = fopen("keys.txt"/*filenameKeys*/, "w");
    FILE* values = fopen("values.txt"/*filenameVal*/, "w");

    for (int i = 0; i < sizeTable(tabl); i++) { // пишем в файл из таблицы
        fprintf(keys, "%g\n", tabl->elem[i].key);
        fprintf(values, "%s\n", tabl->elem[i].value);
    }
    fclose(keys);
    fclose(values);
}

void addToTable(table* tabl, int position, float key, char value[STRSIZE])
{ 
    if (position < sizeTable(tabl) && position >= 0) { // если в пределах, все норм, заменяем уже сущ-щий
        strcpy(tabl->elem[position].value, value);
        tabl->elem[position].key = key;
    } else { // если позиция за пределами таблицы, выделяем память под еще один элемент в конце

        tabl = resizeTable(tabl); // ставим на его место
        position = sizeTable(tabl)-1;
        strcpy(tabl->elem[position].value, value);
        tabl->elem[position].key = key;
        printf("Элемент вставлен в конец таблицы\n");
    }
}

void printTable(table* tabl) // форматный вывод
{
    printf(" ____________________________________________ \n");
    printf("|   Ключ   | Значение                        |\n");
    printf("|__________|_________________________________|\n");
    printf("|          |                                 |\n");
    for (int i = 0; i < sizeTable(tabl); i++) {
        printf("| %6g | %-41s \n", tabl->elem[i].key, tabl->elem[i].value);
    }
    printf("|__________|_________________________________|\n");
}

bool isMoreOther(element* elem1, element* elem2)
{
    return elem1->key > elem2->key;
}

bool checkSortTable(table* tabl) // хотя бы одна пара: первый меньше второго
{ // по убыванию
    for (int i = 0; i < sizeTable(tabl) - 1; i++) {

        if ( !(isMoreOther( &(tabl->elem[i]), &(tabl->elem[i + 1])) ) ) {
            //printf("%f %f", tabl->elem[i].key, tabl->elem[i + 1].key);
            return false;
        }
    }
    return true;
}

bool checkReverseSortTable(table* tabl) // хотя бы одна пара: первый больше второго
{ // по возрастанию
    for (int i = 0; i < sizeTable(tabl) - 1; i++) {

        if (isMoreOther( &(tabl->elem[i]), &(tabl->elem[i + 1])) ) {
            return false;
        }
    }
    return true;
}

element* getValue(table* tabl, float key)
{
    if (checkReverseSortTable(tabl)) { // сортировано по возрастанию

        int left = 0;
        int right = sizeTable(tabl) - 1;
        int ind;
        element elemm;

        while (true) {

            ind = (left + right) / 2;
            elemm = tabl->elem[ind];
            
            if (elemm.key == key) {
                return &(tabl->elem[ind]);

            } else if (key > elemm.key) {
                left = (left + right) / 2;
            } else {
                right = (left + right) / 2;
            }
        }
    } else if (checkSortTable(tabl)) { // сортировано по убыванию(normalno)
        //float currentKey;

        int left = 0;
        int right = sizeTable(tabl) - 1;
        int ind;
        element elemm;

        while (true) {

            ind = (left + right) / 2;
            elemm = tabl->elem[ind];

            if (elemm.key == key) {
                return &(tabl->elem[ind]);

            } else if (key > elemm.key) {
                right = (left + right) / 2;
            } else {
                left = (left + right) / 2;
            }
        }
    } else {
        //printf("Ты данные отсортировал, дядя?");
        return NULL;
    }
}

void reverseTable(table* tabl) // не нравится, как отсортировали
{ // хотим наоборот
    float swapKey;
    char swapValue[STRSIZE];

    element elemm1;
    //element elemm2;
    for (int i = 0; i < sizeTable(tabl) / 2; i++) { // меняем местами начало-конец до n/2

        int pos = sizeTable(tabl) -1-i;
        elemm1 = tabl->elem[i];
        //elemm2 = tabl->elem[pos];

        swapKey = elemm1.key;
        strcpy(swapValue, elemm1.value);

        tabl->elem[i].key = tabl->elem[pos].key;
        strcpy(tabl->elem[i].value, tabl->elem[pos].value);
        tabl->elem[pos].key = swapKey;
        strcpy(tabl->elem[pos].value, swapValue);

    }
}
void sortShell(table* tabl) // сортировка шелла
{ // меняем местами элементы находящиеся на расстоянии n/2, n/4, ..., 2
    element elemm1;
    element elemm2;
    float swapKey;
    char swapValue[STRSIZE];
    for (int i = sizeTable(tabl) / 2; i > 0; i = i / 2) {
        for (int j = 0; i + j < sizeTable(tabl); j++) {

            elemm1 = tabl->elem[j];
            elemm2 = tabl->elem[i+j];
            if (elemm1.key < elemm2.key) { // а можно было просто 1 раз своп написать
                swapKey = elemm1.key; // умные мысли в час ночи приходят с опозданием
                strcpy(swapValue, elemm1.value);
                tabl->elem[j].key = tabl->elem[i+j].key;
                strcpy(tabl->elem[j].value, tabl->elem[i+j].value);
                tabl->elem[i+j].key = swapKey;
                strcpy(tabl->elem[i+j].value, swapValue);
            }
        }
    }
}

void destroyTable(table* tabl)
{
    tabl->size = 0;
    free(tabl->elem);
    tabl->elem = NULL;
    free(tabl);
}
