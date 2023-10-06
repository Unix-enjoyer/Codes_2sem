#ifndef _MATHPARSER_H_ // инициализация
#define _MATHPARSER_H_

#define STR_SIZE 100

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


/*typedef enum Operator {
    ADD          = '+',
    SUBSTRACT    = '-',
    MILTIPLY     = '*',
    DIVIDE       = '/',
    LEFTBRACKET  = '(',
    RIGHTBRACKET = ')',
    POWER        = '^',
} Operator;

typedef enum Priority
{
    ADD          = 1,
    SUBSTRACT    = 1,
    MILTIPLY     = 2,
    DIVIDE       = 2,
    LEFTBRACKET  = 0,
    RIGHTBRACKET = 0,
    POWER        = 4,
} Priority;*/


//Оператор
typedef struct _Operator { // тип оператор, имеет приоритет и значение мат оператора
    char symbol; //= ' ';
    short priority;// = -1; 
} Operator;

Operator* op_create(char symbol); // создаст объект типа оператор и определит его приоритет
int checkPriority(char symbol); // проверит приоритет символа

//Элемент дерева - оператор, либо число (определяется по факту)
typedef struct _treeItem { // элемент дерева, в задаче это или опреатор или число
    Operator* Operator; // в зависимости от того, какое поле заполнено
    int number; // будем работать или как с оператором, или как с числом
} TreeItem;

typedef struct _tree { // структура - дерево, rootvalue явл указателем на корневой узел(дерево)
    TreeItem* value;
    struct _tree* left;
    struct _tree* right;
} _tree;

_tree* tree_create(); // инициализация дерева
TreeItem* treeElem_create(int num, char symb); // создание узла (оператора или числа), смотря какое поле пусто


// стек
typedef struct _stackElem StackElem;
typedef struct _stackElem { // структура элемента стека
    Operator* operator; // указатель на сам оператор(на значение элемента)
    int number;
    StackElem* next; // указатель на след элемент
} StackElem;

typedef struct _stack { // стек
    StackElem* top; // верхушка и размер
    int size;
} Stack;

Stack* stack_create(); // инициализация стека
StackElem* stackElem_create(char symbol, int number); // создание эл-та дерева с указателями на соседей
void stack_push(Stack* stack, char symbol, int number); // положить символ в стек, а по нему создастся элемент стека
int st_size(Stack* stack); // длина стека
StackElem* stack_pop(Stack* stack); // вытащить элемент сверху
void freeStackElem(StackElem* stackElem); // очистка вытащенного элемента


void dijkstra(Stack* stack, Stack* resstack, char expression[STR_SIZE], Stack* reversedstack);


//_tree* tree_create(TreeItem rootValue);

_tree* tree_find(_tree* tree, TreeItem findVal);

_tree* tree_min_node(_tree* tree);

void tree_remove(_tree* tree, TreeItem remoVal);

void tree_add(_tree* tree, TreeItem value);

void tree_print_node(_tree* tree, int indent);

void tree_print(_tree* tree);

//int deep(_tree* tree, int c);

//bool is_avl(_tree* tree);

void tree_destroy(_tree* tree);

//bool avl(_tree* tree, bool flag);

#endif // _MATHPARSER_H_
