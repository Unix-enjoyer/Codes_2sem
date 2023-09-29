#ifndef _TABLE_H_
#define _TABLE_H_

#include <stdbool.h>

#define STRSIZE 100

typedef struct _element {
    float key;
    char value[STRSIZE];
} element;

typedef struct _table {
    int size;
    element* elem;
} table;

table* createTable(int size);
//int sizeTable(table* tabl);
//table* resizeTable(table* tabl);
void fileRead(table* tabl, char filenameKeys[STRSIZE], char filenameVal[STRSIZE]);
void writeToFile(table* tabl, char filenameKeys[STRSIZE], char filenameValues[STRSIZE]);
void addToTable(table* tabl, int position, float key, char value[STRSIZE]);
void printTable(table* tabl);
//bool isMoreOther(element* elem1, element* elem2);
bool checkSortTable(table* tabl);
//bool checkReverseSortTable(table* tabl);
element* getValue(table* tabl, float key);
void reverseTable(table* tabl);
void sortShell(table* tabl);
void destroyTable(table* tabl);

#endif //_TABLE_H_