#include "deque.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct _item { // структура элемента дека
    DqItem value;
    Item left;
    Item right;
};

struct _deque { // дек
    Item leftEnd;
    Item rightEnd;
    int size;
};

Deque dq_create() // создаем дерево, указатель на левое и правое звено по нулям, длина - ноль
{
    Deque deque = (Deque) malloc(sizeof(*deque));
    deque->leftEnd = NULL;
    deque->rightEnd = NULL;
    deque->size = 0;
    return deque;
}

void dq_push_back(Deque deque, DqItem data) // вставка в конец, последний становится предпоследним, новый - последним
{                                           // если дек непуст, иначе в нем один элемент(и хвост, и голова)
    Item elem = (Item) malloc(sizeof(*elem));
    elem->value = data;
    elem->left = NULL;
    elem->right = NULL;
    if (deque->size != 0) {
        elem->left = deque->rightEnd;
        deque->rightEnd->right = elem;
        deque->rightEnd = elem;
    } else {
        deque->leftEnd = elem;
        deque->rightEnd = elem;
    }
    deque->size += 1;
}

void dq_push_front(Deque deque, DqItem data) // аналогично
{
    Item elem = (Item) malloc(sizeof(*elem));
    elem->value = data;
    elem->left = NULL;
    elem->right = NULL;
    if (deque->size != 0) {
        elem->right = deque->leftEnd;
        deque->leftEnd->left = elem;
        deque->leftEnd = elem;
    } else {
        deque->leftEnd = elem;
        deque->rightEnd = elem;
    }
    deque->size += 1;
}
void dq_print(Deque deque) // идем по деку, начиная с первого элемента, пока указатель не нуль - 
{                          // дек закончился
    if (deque->size != 0) {
        Item start = deque->leftEnd;
        while (start) {
            printf("%d\t", start->value);
            start = start->right;
        }
    } else {
        printf("Deque is empty");
    }
    printf("\n");
}

void is_empty(Deque deque) // надо посмотреть size
{
    if (deque->size == 0) {
        printf("Deque is empty\n");
    } else {
        printf("Deque is not empty\n");
    }
}

int dq_size(Deque deque) // надо вернуть size
{
    return deque->size;
}

void dq_destroy(Deque deque)
{
    Item start = deque->leftEnd;
    while (start != NULL) {
        dq_pop_front(deque);
        start = deque->leftEnd;
    }
    free(deque);
}

void dq_pop_back(Deque deque) // обнулим ссылку на удаляемый, создав резервную, чтобы не потерять объект
{                             //счистим его и меняем указатель на конец, элемент 1 - тогда удаляем его, 
    if (deque->size > 1) {    // и зануляем хвост и голову
        Item tmp = deque->rightEnd;
        Item newRightEnd = deque->rightEnd->left;
        deque->rightEnd->left->right = NULL;
        free(tmp);
        deque->rightEnd = newRightEnd;
    } else if (deque->size == 1) {
        //printf("%p", deque->rightEnd);
        //printf("%p", deque->leftEnd);
        free(deque->leftEnd);
        deque->rightEnd = NULL;
        deque->leftEnd = NULL;
    } else {
        printf("Deque was empty\n");
    }
    deque->size -= 1;
}
void dq_pop_front(Deque deque) // аналогично
{
    if (deque->size > 1) {
        Item tmp = deque->leftEnd;
        Item newLeftEnd = deque->leftEnd->right;
        deque->leftEnd->right->left = NULL;
        free(tmp);
        deque->leftEnd = newLeftEnd;
    } else if (deque->size == 1) {
        free(deque->rightEnd);
        deque->rightEnd = NULL;
        deque->leftEnd = NULL;
    } else { 
        printf("Deque was empty\n");
    }
    deque->size -= 1;
}

Deque linear_choose_rise(Deque deque) // последовательно: ищем min в деке, удаляем и вставляем его в конец, 
{                                     // дальше ищем до deque->size-1. И так пока элементы не кончатся
    Item min;
    for (int i = deque->size - 1; i >= 0; --i) { // поиск минимума в указанном отрезке
        min = deque->leftEnd;
        Item next = deque->leftEnd->right;
        for (int j = 0; j < i; ++j) {
            
            if (next->value < min->value) {
                min = next;
            }
            next = next->right;   
        }
        

        if (min->left != NULL && min->right != NULL) { // если элемент внутри, делаем левому и првому соседу 
            Item tmp = min;                            // ссылки друг на друга
            min->right->left = min->left;
            min->left->right = min->right;
            dq_push_back(deque, tmp->value);
            free(min);
            deque->size -= 1;
        } else if (min->right != NULL) {               // дошли до правого края, не надо проваливаться в Null
            Item tmp = min;
            min->right->left = NULL;
            dq_push_back(deque, tmp->value);
            if (min->left == NULL) { // элемент первый, слева никого нет, двигаем левую границу дека
                deque->leftEnd = tmp->right;
            }
            free(tmp);
            deque->size -= 1;
        }

    }
    return deque;
}