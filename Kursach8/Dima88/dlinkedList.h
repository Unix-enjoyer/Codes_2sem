#ifndef _DLINKED_LIST_H_
#define _DLINKED_LIST_H_

typedef struct _item { // структура элемента 2-св списка
    char value;
    struct _item* left;
    struct _item* right;
} item;


typedef struct _dlinkedList { // 2-св список
    item* back; // левый край
    item* front; // правый край
    int size; // размер
} dlinkedList;


dlinkedList* dlinkedList_create();

item* nodeCreate(char data);
item* get(dlinkedList* dlinkedList, int position);

void printList(dlinkedList* dlinkedList);
void dlinkedList_pushback(dlinkedList* dlinkedList, char data);
void dlinkedList_pushfront(dlinkedList* dlinkedList, char data);
void dlinkedList_insert(dlinkedList* dlinkedList, int position, char data);
void ListRm_front(dlinkedList* dlinkedList);
void ListRm_back(dlinkedList* dlinkedList);
void dlinkedList_delete(dlinkedList* dlinkedList, int position);
void dlinkedList_destroy(dlinkedList** dlinkedList);
void ListChangePairs(dlinkedList* dlinkedList);



#endif
