#include "dlinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>


dlinkedList* dlinkedList_create() // создаем список, указатель на левое и правое звено по нулям, длина - ноль
{
    dlinkedList* dlList = (dlinkedList*) malloc(sizeof(dlinkedList));
    dlList->back = NULL;
    dlList->front = NULL; // (back)=()=()=(front)=(*\_/*) // она не грустит
    dlList->size = 0;
    return dlList;
}

item* nodeCreate(char data)
{
    item* elem = (item*) malloc(sizeof(item));
    elem->value = data;
    elem->left = NULL;
    elem->right = NULL;
    return elem;
}
item* get(dlinkedList* dlinkedList, int position)
{
    if (position > dlinkedList->size || position < 0) {
        return NULL;
    }
    item* current = dlinkedList->back;

    for (int i = 0; i < position; i++) {
        current = current->right;
    }
    return current;
}

void printList(dlinkedList* dlinkedList)
{
    if (dlinkedList->size > 0) {
        item* current = dlinkedList->back;

        while (current->right != NULL) {
            printf("%c ", current->value);
            current = current->right;
        }
        printf("%c ", current->value);
        printf("\n");
    } else {
        printf("List is embty, you should add any elements\n");
    }
}

void dlinkedList_pushback(dlinkedList* dlinkedList, char data) {
    item* elem  = nodeCreate(data);
    if (dlinkedList->back) {
        dlinkedList->back->left = elem;
        elem->right = dlinkedList->back;
        dlinkedList->back = elem;
    } else {
        dlinkedList->back = elem;
        dlinkedList->front = elem;
    }
    dlinkedList->size++;
}

void dlinkedList_pushfront(dlinkedList* dlinkedList, char data) {
    item* elem  = nodeCreate(data);
    if (dlinkedList->front) {
        dlinkedList->front->right = elem;
        elem->left = dlinkedList->front;
        dlinkedList->front = elem;
    } else {
        dlinkedList->front = elem;
        dlinkedList->back = elem;
    }
    dlinkedList->size++;
}

void dlinkedList_insert(dlinkedList* dlinkedList, int position, char data) // вставка в конец, последний становится предпоследним, новый - последним
{                                           // если список непуст, иначе в нем один элемент(и хвост, и голова

    item* current = get(dlinkedList, position);

    if (current) { // элемент в центр
        if (!current->left) { // вставка на место хвоста
            int val = current->value;
            item* elem  = nodeCreate(val);
            current->left = elem;
            current->value = data;
            elem->right = current;
            dlinkedList->back = elem;
        } else if (!current->right) {
            int val = current->value;
            item* elem  = nodeCreate(val);
            current->right = elem;
            current->value = data;
            elem->left = current;
            dlinkedList->front = elem;
        } else {
            item* elem  = nodeCreate(data);
            elem->left = current->left;
            current->left->right = elem;
            elem->right = current;
            current->left = elem;
        }
    } else {
        dlinkedList->size -= 1;
        dlinkedList_pushback(dlinkedList, data);
    }
    dlinkedList->size += 1;
}

void ListRm_front(dlinkedList* dlinkedList) // обнулим ссылку на удаляемый, создав резервную, чтобы не потерять объект
{                             //счистим его и меняем указатель на конец, элемент 1 - тогда удаляем его, 
    if (dlinkedList->size > 1) {    // и зануляем хвост и голову
        item* tmp = dlinkedList->front;
        item* newRightEnd = dlinkedList->front->left;
        dlinkedList->front->left->right = NULL;
        free(tmp);
        dlinkedList->front = newRightEnd;
        newRightEnd = NULL;
        tmp = NULL;
        dlinkedList->size -= 1;
    } else if (dlinkedList->size == 1) {
        free(dlinkedList->back);
        dlinkedList->front = NULL;
        dlinkedList->back = NULL;
        dlinkedList->size -= 1;
    } else {
        printf("List was empty\n");
    }
}

void ListRm_back(dlinkedList* dlinkedList) // обнулим ссылку на удаляемый, создав резервную, чтобы не потерять объект
{                             //счистим его и меняем указатель на конец, элемент 1 - тогда удаляем его, 
    if (dlinkedList->size > 1) {    // и зануляем хвост и голову
        item* tmp = dlinkedList->back;
        item* newRightEnd = dlinkedList->back->right;
        dlinkedList->back->right->left = NULL;
        free(tmp);
        dlinkedList->back = newRightEnd;
        newRightEnd = NULL;
        tmp = NULL;
        dlinkedList->size -= 1;
    } else if (dlinkedList->size == 1) {
        free(dlinkedList->back);
        dlinkedList->front = NULL;
        dlinkedList->back = NULL;
        dlinkedList->size -= 1;
    } else {
        printf("List was empty\n");
    }
}

void dlinkedList_delete(dlinkedList* dlinkedList, int position)
{
    item* current = get(dlinkedList, position);

    if (current) { // элемент в центр
        if (!current->left) { // вставка на место хвоста
            ListRm_back(dlinkedList);
        } else if (!current->right) {
            ListRm_front(dlinkedList);
        } else {
            current->left->right = current->right;
            current->right->left = current->left;
            free(current);
            current = NULL;
        }
    } else {
        printf("List was empty\n");
        return;
    }
    dlinkedList->size -= 1;
}

void dlinkedList_destroy(dlinkedList* dlinkedList)
{
    if (dlinkedList->size > 0) {
        item* current = dlinkedList->back;

        while (current->right != NULL) {
            ListRm_back(dlinkedList);
            current = current->right;
        }
        ListRm_back(dlinkedList);
        free(dlinkedList);
        current = NULL;
    }
    if (dlinkedList) {
        dlinkedList = NULL;
    }
}

void ListChangePairs(dlinkedList* dlinkedList)
{
    char swap;
    item* current = dlinkedList->back;
    item* curNext = dlinkedList->back->right;
    for (int i = 0; i < (dlinkedList->size) / 2; ++i) {
        swap = current->value;
        current->value = curNext->value;
        curNext->value = swap;
        if (curNext->right && curNext->right->right) {
            current = current->right->right;
            curNext = curNext->right->right;
        }
    }
    current = NULL;
    curNext = NULL;

}

/*int main()
{
    char s;
    scanf("%c", &s);
    dlinkedList* dlDlist = dlinkedList_create();
    dlinkedList_pushfront(dlDlist, s);
    dlinkedList_pushfront(dlDlist, 'A');
    dlinkedList_pushfront(dlDlist, 'W');
    dlinkedList_insert(dlDlist, 0, 'F');
    dlinkedList_insert(dlDlist, 3, 'C');
    dlinkedList_insert(dlDlist, 2, 'Y');
    //printList(dlDlist);
    ListRm_front(dlDlist);
    //printDlist(dlDlist);
    //dlinkedDlist_delete(dlDlist, 3);
    printList(dlDlist);

    ListChangePairs(dlDlist);
    printList(dlDlist);

    dlinkedList_destroy(dlDlist);
}*/