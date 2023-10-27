#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#include "mathparser.h"


#define STR_SIZE 100

////Стек

Stack* stack_create() // создаем дерево, указатель на левое и правое звено по нулям, длина - ноль
{
    Stack* stack = (Stack*) malloc(sizeof(*stack));
    stack->size = 0;
    stack->top = NULL;

    return stack;
}

int st_size(Stack* stack) // длина стека
{
    return stack->size;
}
//с выр-ия только с числами, буквенные константы - только постф форма
StackElem* stackElem_create(char symbol, int number) // создаст элемент СТЕКА (с указателем на соседа)
{
    StackElem* element = (StackElem*) malloc(sizeof(*element));

    if (symbol != ' ') {

        Operator* operator = op_create(symbol);
        element->operator = operator; // теперь элемент стека содержит значение (оператор)
        element->number = INT_MAX;
    } else if (number != INT_MAX) {

        element->number = number;
        element->operator = NULL;
    }

    element->next = NULL; // ссыдка на соседа налл
    return element;
}

void stack_push(Stack* stack, char symbol, int number) // положить в стек
{
    if (!stack) { // если стека нет - создать
        stack = stack_create();
    }
    
    StackElem* elemSt = stackElem_create(symbol, number); // сделать из символа элемент стека(с указателем)

    if (st_size(stack) == 0) { // если пуст
        stack->top = elemSt;
    } else { // не пуст
        elemSt->next = stack->top; // новый ссылается на старый
        stack->top = elemSt; // новый - это верх
    }
    stack->size += 1;

    elemSt = NULL;
}

StackElem* stack_pop(Stack* stack) // мы его отвязали, не забыть почистить //////////////////////////////////////////
{
    StackElem* tmp = stack->top; // влюбом случае вытаскиваем верхий
    if (stack->top->next) { // указатель ибо обновляем, либо нет
        stack->top = tmp->next;
        tmp->next = NULL;

    } else if (st_size(stack) == 1) {
        stack->top = NULL;
    } else {
        return NULL;
    }
    stack->size -= 1;
    return tmp;
}

void freeStackElem(StackElem* stackElem) // очистка вытащенного элемента
{ 
    free(stackElem->operator);
    free(stackElem);
}

void stack_destroy(Stack* stack) // kill the stack
{
    while (stack->size > 0) {
        StackElem* deleted = stack_pop(stack);
        freeStackElem(deleted);
    }
    free(stack);
}

void stack_reverse(Stack* stack, Stack* reversed) // разворот стека
{
    while (st_size(stack) > 0) {
    
        StackElem* popEl = stack_pop(stack);
        
        if (popEl->number != INT_MAX) {
            stack_push(reversed, ' ', popEl->number);
        } else if (popEl->operator) {
            stack_push(reversed, popEl->operator->symbol, INT_MAX);
        }
         // из стека в строку
         // пишем в итоговую строку
        freeStackElem(popEl); // из стека вытащили, он ни на кого не ссылается
        // на него тоже, надо удалить его, нам этот элемент не нужен больше
    }
}

bool isNumSt(StackElem* elem) // определяет, с чем работаем (элемент стека): с числом или с оператором
{
    if (elem->number != INT_MAX) {
        return true;
    } else {
        return false;
    }
}

/////////////Оператор
Operator* op_create(char symbol) // создаст объект типа оператор и 
{               // по считанному символу определяет его приоритет
    Operator* operator = (Operator*) malloc(sizeof(*operator));
    operator->symbol = symbol;
    operator->priority = checkPriority(symbol);

    return operator;
}

int checkPriority(char symbol) // проверит приоритет символа
{
    switch (symbol) {
        case '+':
            return 1;     break;
        case '-':
            return 1;     break;
        case '/':
            return 2;     break;
        case '*':
            return 2;     break;
        case '^':
            return 3;     break;
        case '(':
            return 0;     break;
        case ')':
            return 0;     break;
        case ' ': 
            return -1;    break;
        default:
            return INT_MIN;
    }
}

// Дерево
TreeItem* treeElem_create(int num, char symb) // создание узла (оператора или числа), смотря 
{                // какое поле не пусто
    TreeItem* item = (TreeItem*) malloc(sizeof(*item));
    if (num != INT_MAX) {
        item->number = num;
        item->Operator = NULL;
    } else if (symb != ' ') {
        item->Operator = op_create(symb);
        item->number = INT_MAX;
    }
}

bool isNumNd(Tree* node) // определяет, с чем работаем (узел дерева): с числом или с оператором
{
    if (!node->value->Operator) {
        return true;
    } else {
        return false;
    }
}

TreeItem* ValueCreateByStack(Stack* stack) 
{
    StackElem* stElem = stack_pop(stack);
    TreeItem* item;

    if(isNumSt(stElem)) {
        item = treeElem_create(stElem->number, ' ');
    } else {
        item = treeElem_create(INT_MAX, stElem->operator->symbol); // нода создана
    }
    freeStackElem(stElem);
    return item;
}
Tree* tree_create() 
{  // так как значение узла - структура, нужно его иниц-ать 
// а потом уже сделать узел, присвоив значению структуру, указателям на соседей - указатели
    Tree* tree = (Tree*) malloc(sizeof(*tree));
    tree->value = NULL; // переданы нужные значения для создания нужной структуры
    tree->left = NULL;
    tree->right = NULL;
    tree->parent = NULL;

    return tree;
}

Tree* findVoid(Tree* node, Tree* place) // (куда<-откуда) ищет место для ноды
{
    if (!isNumNd(node)) { // нода - оператор

        if (!place->right) { // справа свободно?
            place->right = node; // указ на ноду
            node->parent = place; // указ на родителя
            return node;

        } else if (!place->left) { // а слева?
            place->left = node;
            node->parent = place;
            return node;

        } else {

            while (place->left != NULL && place->right != NULL) {
                if (place->parent) {
                    place = place->parent;
                } else if (place->left) { //ROOT  вдруг нету левого?
                    place = place->left; // есть - идем влево
                } else {//иначе остаемся
                }
            }
            if (!place->right) { // справа свободно?
                place->right = node; // указ на ноду
                node->parent = place; // указ на родителя
                return node;

            } else if (!place->left) { // а слева?
                place->left = node;
                node->parent = place;
                return node;

            }

        }

    } else if (isNumNd(node)) { // нода - число

        if (!place->right) { // справа свободно?
            place->right = node; // указ на ноду
            node->parent = place; // указ на родителя

            return node->parent;

        } else if (!place->left) { // а слева?
            place->left = node;
            node->parent = place;

            return node->parent;

        } else {

            while (place->left != NULL && place->right != NULL) {
                if (place->parent) {
                    place = place->parent;
                } else if (place->left) { //ROOT  вдруг нету левого?
                    place = place->left; // есть - идем влево
                } else {//иначе остаемся
                }
            }
            if (!place->right) { // справа свободно?
                place->right = node; // указ на ноду
                node->parent = place; // указ на родителя
                return node->parent;

            } else if (!place->left) { // а слева?
                place->left = node;
                node->parent = place;
                return node->parent;

            }
        }
    }
}

Tree* make_tree(Stack* stack) // строит дерево по стеку
{
    Tree* tree = tree_create(); // 
    tree->parent = NULL;

    TreeItem* value = ValueCreateByStack(stack);
    tree->value = value; //корень создан

    Tree* justPaste = tree;

    while (st_size(stack) > 0) {
//                                         left/  ^  |right
        value = ValueCreateByStack(stack);//   par|          элемент создан, нужно найти ему место
        Tree* node = tree_create();//           node
        node->value = value;//             left/     |right
        justPaste = findVoid(node, justPaste); // сделает tree нужную ссылку(лефт/райт) на созданный элемент

    }
    return tree;
}

void tree_print_node(Tree* tree, int indent) // Вывод на экран терминала узлы
{
    int i = 0;
    for (int i = 0; i < indent; ++i) { // Уменьшаем кол-во отступов \t
        printf("\t");
    }

    if (isNumNd(tree)) {
        printf("%d\n", tree->value->number); // Значение узла
    } else {
        printf("%c\n", tree->value->Operator->symbol); // Значение узла
    }
    if(tree->right != NULL) {
        tree_print_node(tree->right, indent + 1); // Если соседний то значение узла + отступ
    }

    if(tree->left != NULL) {
        tree_print_node(tree->left, indent + 1); // Если дочерний узел выводим его + отступ+1
    }
    
}

void tree_print(Tree* tree) // Рекурсивный вызов функции
{
    tree_print_node(tree, 0);
}

Tree* tree_findPow(Tree* tree) // ищет указанное значение в дереве "^" и 
{                             // возвращает указатель на него

    if (!isNumNd(tree) && tree->value->Operator->symbol == '^') {
        return tree;
    }

    if (tree->right) {
        Tree* treeRes = tree_findPow(tree->right);
        if (treeRes) {
            return treeRes;
        }

    }
    if (tree->left) {
        Tree* treeRes = tree_findPow(tree->left);
        if (treeRes) {
            return treeRes;
        }

    }

    return NULL;
}

void freeTreeSheet(Tree* node) // чистит одну ноду
{
    node->parent = NULL;
    if (node->value->Operator) {
        free(node->value->Operator);
    }
    free(node->value);
}

void tree_destroy(Tree* tree) // удаляет дерево от листов к корню
{
    if (tree->left) {
        tree_destroy(tree->left);
    }
    if (tree->right) {
        tree_destroy(tree->right);
    }
    freeTreeSheet(tree);
}

int poww(int num, int pow) // целочисл степень
{
    int res = 1;
    for (int i = 0; i < pow; ++i) {
        res *= num;
    }
    return res;
}

void calcPow(Tree* node)
{
    int calculated = poww(node->left->value->number, node->right->value->number);
    node->value->number = calculated; // посчитана степень
    free(node->value->Operator); // уже не оператор
    node->value->Operator = NULL; // вот

    freeTreeSheet(node->left); // избавляемся от операндов
    freeTreeSheet(node->right);
    node->left = NULL; 
    node->right = NULL;
}

void dijkstra(Stack* opstack, Stack* resstack, char expression[STR_SIZE], Stack* reversedstack)
{
    int number = 0;
    ///printf("expres = %s", expression);
    char symbol = ' ';
    ///printf("\n\nstrlen = %ld\n\n",strlen(expression));
    for (int i = 0; i < strlen(expression); i++) {
        ///printf("%c", expression[i]);
        if (isdigit(expression[i])) { // если текущая и след - цифры => еще собираем число
            if (isdigit(expression[i + 1])) {
                number = number*10 + (expression[i] - '0');

            } else { // число уже собрали, надо заврешать и парсить
                number = number*10 + (expression[i] - '0');
                stack_push(resstack, ' ', number); // в результирующую "строку"

                number = 0;
            }
        /* /*else if (isalpha(expression[i])) { // буква (константа) - сразу парсим
            symbol = expression[i];
            // возможно лучше убрать
            stack_push(resstack, symbol, INT_MAX); // пишем в итоговую строку
            symbol = ' ';
*/
        } else if (isspace(expression[i])) { // встречен пробел
            continue;

        } else if (ispunct(expression[i]) && expression[i]!= '(' && expression[i] != ')') { // знак мат операции
            symbol = expression[i];

            int topPriority;
            if (opstack->top) {
                topPriority = opstack->top->operator->priority; // приоритет верха стека < чем у текщуго
            } else {
                topPriority = -1;
            }
            int preliminaryPriority = checkPriority(symbol); 

            if ((st_size(opstack)) == 0 || (topPriority < preliminaryPriority)) { // либо стек пустой
                stack_push(opstack, symbol, INT_MAX); // кладем элемент

            } else if (topPriority >= preliminaryPriority) {

                while (topPriority >= preliminaryPriority) {
                    StackElem* popEl = stack_pop(opstack); // берем новый

                    stack_push(resstack, popEl->operator->symbol, INT_MAX);
                     // из стека в строку
                     // пишем в итоговую строку

                    if (opstack->top) {
                        topPriority = opstack->top->operator->priority;
                    } else {
                        break;
                    }
                    freeStackElem(popEl); // из стека вытащили, он ни на кого не ссылается
                    // на него тоже, надо удалить его, нам этот элемент не нужен больше

                }
                stack_push(opstack, symbol, INT_MAX); // вытаскивать, пока приоритет >=
            } // а пото еще и положить текущий надо
            symbol = ' ';

        } else if (expression[i] == '(') { // положить в стек
            symbol = expression[i];
            stack_push(opstack, symbol, INT_MIN);
            symbol = ' ';

        } else if (expression[i] == ')') { // ложить в стек, пока 1)
            StackElem* popEl = stack_pop(opstack);

            while (popEl->operator->symbol != '(') {

                stack_push(resstack, popEl->operator->symbol, INT_MAX);
                 // из стека в строку
                 // пишем в итоговую строку
                freeStackElem(popEl); // из стека вытащили, он ни на кого не ссылается
                // на него тоже, надо удалить его, нам этот элемент не нужен больше
                popEl = stack_pop(opstack); // берем новый
            }
            freeStackElem(popEl); // 1 раз недоработал, надо скобку еще очистить
            symbol = ' ';
        }

    }    

    while (st_size(opstack) > 0) { // развернуть для вывода
    
        StackElem* popEl = stack_pop(opstack);
        
        stack_push(resstack, popEl->operator->symbol, INT_MAX);
         // из стека в строку
         // пишем в итоговую строку
        freeStackElem(popEl); // из стека вытащили, он ни на кого не ссылается
        // на него тоже, надо удалить его, нам этот элемент не нужен больше
    }

    /////stack_reverse(resstack, reversedstack); // развернуть стек

}

void parsedPrint(Stack* resstack)
{
    Stack* reversed = stack_create();
    stack_reverse(resstack, reversed);

    while(st_size(reversed) > 0) {

        StackElem* elem = stack_pop(reversed);
        if (elem->number != INT_MAX) {
            printf("%d ", elem->number);
        } else if (elem->operator) {
            printf("%c ", elem->operator->symbol);
        }
        freeStackElem(elem);
    }
    printf("\n");
    stack_destroy(resstack);
    stack_destroy(reversed);
}


void print_node(Tree* tree, int l, int r) 
{ //печать узла

    if (isNumNd(tree)){
        for (int i = 0; i < l; i++)
            printf("(");
        if (isNumNd(tree))
            printf("%d", tree->value->number);
        else
            printf("%c", tree->value->Operator->symbol);
        for (int i = 0; i < r; i++)
            printf(")");
        return;
    }

    if (!isNumNd(tree->left) && tree->left->value->Operator->priority < tree->value->Operator->priority) {
        print_node(tree->left, l + 1, 1);
    } else if (!isNumNd(tree->left)) {
        print_node(tree->left, l, 0);
    } else {
        print_node(tree->left, l, 0);
    }

    if (!isNumNd(tree)) {
        printf("%c", tree->value->Operator->symbol);
    } else if (isNumNd(tree)) {
        printf("%d", tree->value->number);
    }
    
    if (!isNumNd(tree->right) && tree->right->value->Operator->priority < tree->value->Operator->priority) {
        print_node(tree->right, 1, r + 1);
    } else if (!isNumNd(tree->right)) {
        print_node(tree->right, 0, r);
    } else {
        print_node(tree->right, 0, r);
    }
}

void print_expression(Tree* tree) { //печать выражения в обычном виде
    print_node(tree, 0, 0);
    printf("\t");
}



int main()
{
    Stack* opstack1 = stack_create();
    Stack* opstack2 = stack_create();
    Stack* resstack1 = stack_create();
    Stack* resstack2 = stack_create();
    Stack* reversedstack = stack_create();
    char expression[100];
    printf("Введите мат выражение, в конце нажмите энтер:\n");
    fgets(expression, 100, stdin);
    expression[strlen(expression)-1] = '\0'; // теперь у нас норм строка с пробелами, без лишнего
    //printf("%s", expression);

    dijkstra(opstack1, resstack1, expression, reversedstack); // стек для вывода
///// для печати надо развернуть стек
    /*while(st_size(resstack) > 0) {

        StackElem* elem = stack_pop(resstack);
        if (elem->number != INT_MAX) {
            printf("%d\t", elem->number);
        } else if (elem->operator) {
            printf("%c\t", elem->operator->symbol);
        }
        freeStackElem(elem);
    }*/
    //Tree* tree = tree_create();
    parsedPrint(resstack1);

    dijkstra(opstack2, resstack2, expression, reversedstack); // стек для дерева

    Tree* tree = make_tree(resstack2);
    //printf("%c", tree->value->Operator->symbol);
    tree_print(tree);

    Tree* item;

    while ((item = tree_findPow(tree)) != NULL) {
        calcPow(item);
    }

    ///////tree_print(tree);
    //printf("%c", item->value->Operator->symbol); //
    printf("\n");
    /////////////exprPrint(tree);
   /* Tree* node = tree;
    while (node->left) {
        node = node->left;
    }
    while(node) {
        exprPrint(node);
    }*/
    print_expression(tree);
    stack_destroy(opstack2);
    stack_destroy(resstack2);
    tree_destroy(tree);


    
}