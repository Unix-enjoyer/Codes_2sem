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
typedef struct TreeItem { // элемент дерева, в задаче это или опреатор или число
    Operator* Operator; // в зависимости от того, какое поле заполнено
    int number; // будем работать или как с оператором, или как с числом
} TreeItem;

typedef struct Tree { // структура - дерево, rootvalue явл указателем на корневой узел(дерево)
    TreeItem* value;
    struct Tree* left;
    struct Tree* right;
    struct Tree* parent;
} Tree;

Tree* tree_create(); // инициализация дерева
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
void stack_destroy(Stack* stack); // удаление стека

void dijkstra(Stack* stack, Stack* resstack, char expression[STR_SIZE], Stack* reversedstack);


//Tree* tree_create(TreeItem rootValue);

Tree* tree_find(Tree* tree, TreeItem findVal);

Tree* tree_min_node(Tree* tree);

void tree_remove(Tree* tree, TreeItem remoVal);

void tree_add(Tree* tree, TreeItem value);

void tree_print_node(Tree* tree, int indent);

void tree_print(Tree* tree);

//int deep(Tree* tree, int c);

//bool is_avl(Tree* tree);

void tree_destroy(Tree* tree);

//bool avl(Tree* tree, bool flag);

#endif // _MATHPARSER_H_
