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
}

StackElem* stack_pop(Stack* stack) // мы его отвязали, не забыть почистить ///////////////////
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

void freeStackElem(StackElem* stackElem) { // очистка вытащенного элемента
    free(stackElem->operator);
    free(stackElem);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
/*void dq_print(Deque deque) // идем по деку, начиная с первого элемента, пока указатель не нуль - 
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

void dq_destroy(Deque deque)
{
    Item start = deque->leftEnd;
    while (start != NULL) {
        dq_pop_front(deque);
        start = deque->leftEnd;
    }
    free(deque);
}

void dq_erase(Deque deque) {
    Item start = deque->leftEnd;
    while (start != NULL) {
        dq_pop_front(deque);
        start = deque->leftEnd;
    }
}

DqItem dq_pop_max(Deque deque)
{
    Deque ddeque = dq_create();
    Item start = deque->leftEnd;
    DqItem max = deque->leftEnd->value;
    int n = deque->size;
    if (deque) {
        for (int i = 0; i < n; i++) {
            dq_push_back(ddeque, start->value);
            if (start->value > max) {
                max = start->value;
            }
            start = start->right;
        }

        dq_erase(deque);
        start = ddeque->leftEnd;
        for (int i = 0; i < n; i++) {
            if (start->value != max) {
                dq_push_back(deque, start->value);
            }
            start = start->right;
        }
        dq_destroy(ddeque);
    }
    return max;
}

*/
/////////////////////////////////////////////////////////////////////////////////////////////////
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
            return -1;    break; // -1 значит, что это число, а не оператор
        default:
            //printf("Неправильный ввод, ведите другое мат выражение с допустимым набором операций\n");
            return INT_MIN;
    }
}
/*poka nahren
TreeItem* treeElem_create(int num, char symb) // создание узла (оператора или числа), смотря 
{                // какое поле не пусто
    TreeItem* item = (TreeItem*) malloc(sizeof(*item));
    if (symb == ' ') {
        item->number = num;
        item->Operator = op_create(' '); // не оператор, а число
    } else {
        item->Operator = op_create(symb);
        item->number = INT_MAX;
    }
}

_tree* tree_create() 
{  // так как значение узла - структура, нужно его иниц-ать 
// а потом уже сделать узел, присвоив значению структуру, указателям на соседей - указатели
    _tree* tree = (_tree*) malloc(sizeof(*tree));
    tree->value = NULL; // переданы нужные значения для создания нужной структуры
    tree->left = NULL;
    tree->right = NULL;

    return tree;
}

bool isNum(TreeItem* item) // определяет, с чем работаем: с числом или с оператором
{
    if (item->number != INT_MAX) {
        return true;
    } else {
        return false;
    }
}
*/

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
                    ///////////////////////////freeStackElem(popEl); // из стека вытащили, он ни на кого не ссылается
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
                ////////////////////////////////////////freeStackElem(popEl); // из стека вытащили, он ни на кого не ссылается
                // на него тоже, надо удалить его, нам этот элемент не нужен больше
                popEl = stack_pop(opstack); // берем новый
            }
            //freeStackElem(popEl); // 1 раз недоработал, надо скобку еще очистить
            symbol = ' ';
        }

    }    

    while (st_size(opstack) > 0) {
    
        StackElem* popEl = stack_pop(opstack);
        
        stack_push(resstack, popEl->operator->symbol, INT_MAX);
         // из стека в строку
         // пишем в итоговую строку
        //////////////////////////////////////////////freeStackElem(popEl); // из стека вытащили, он ни на кого не ссылается
        // на него тоже, надо удалить его, нам этот элемент не нужен больше
    }
    while (st_size(resstack) > 0) {
    
        StackElem* popEl = stack_pop(resstack);
        
        if (popEl->number != INT_MAX) {
            stack_push(reversedstack, ' ', popEl->number);
        } else if (popEl->operator) {
            stack_push(reversedstack, popEl->operator->symbol, INT_MAX);
        }
         // из стека в строку
         // пишем в итоговую строку
        //////////////////////////////////////////////freeStackElem(popEl); // из стека вытащили, он ни на кого не ссылается
        // на него тоже, надо удалить его, нам этот элемент не нужен больше
    }

}


int main()
{
    Stack* opstack = stack_create();
    Stack* resstack = stack_create();
    Stack* reversedstack = stack_create();
    char expression[100];
    printf("Введите мат выражение, в конце нажмите энтер:\n");
    fgets(expression, 100, stdin);
    expression[strlen(expression)-1] = '\0'; // теперь у нас норм строка с пробелами, без лишнего
    //printf("%s", expression);

    dijkstra(opstack, resstack, expression, reversedstack);

    while(st_size(reversedstack) > 0) {

        StackElem* elem = stack_pop(reversedstack);
        if (elem->number != INT_MAX) {
            printf("%d\t", elem->number);
        } else if (elem->operator) {
            printf("%c\t", elem->operator->symbol);
        }
    }


    
}

/*_tree* tree_find(_tree* tree, TreeItem findVal) // ищет указанное значение в дереве и 
{                                           // возвращает указатель на него
    if (tree == NULL) {
        return NULL;
    }

    if (tree->value == findVal) {
        return tree;
    }

    if (findVal < tree->value) {
        return tree_find(tree->left, findVal);
    }

    if (findVal > tree->value) {
        return tree_find(tree->right, findVal);
    }
    return NULL;
}

_tree* tree_min_node(_tree* tree)
{
    if (tree->left != NULL) {
        return tree_min_node(tree->left);
    } else {
        return tree;
    }
}

void tree_destroy(_tree* tree) // удаляет дерево от листов к корню
{
    if (tree->left) {
        tree_destroy(tree->left);
    }
    if (tree->right) {
        tree_destroy(tree->right);
    }
    free(tree);
}

void tree_remove(_tree* tree, TreeItem remoVal) // удаляет элемент дерева
{
    if (tree != NULL) {

        if (tree->left != NULL) { // 3 случая
            if (tree->left->value == remoVal) { // для левого потомка

                if (tree->left->left == NULL && tree->left->right == NULL) { // лист - потомки NULL`евые
                    _tree* tmp = tree->left;
                    tree->left = NULL;
                    free(tmp);
                    free(tree->left);
                    return;
                }

                if (tree->left->left != NULL && tree->left->right == NULL) { // узел 1 потомок - левый
                    _tree* tmp = tree->left;
                    tree->left = tree->left->left;
                    free(tmp);
                    return;
                }

                if (tree->left->left == NULL && tree->left->right != NULL) { // узел 1 потомок - правый
                    _tree* tmp = tree->left;
                    tree->left = tree->left->right;
                    free(tmp);
                    return;
                }

                if (tree->left->left != NULL && tree->left->right != NULL) { // узел 2 потомка
                    TreeItem tmp = tree_min_node(tree->left->right)->value;
                    tree_remove(tree, tree_min_node(tree->left->right)->value);
                    tree->left->value = tmp;
                    return;
                }

            }
        }

        if (tree->right != NULL) {
            if (tree->right->value == remoVal) { // для правого потомка

                if (tree->right->left == NULL && tree->right->right == NULL) {
                    _tree* tmp = tree->right;
                    tree->right = NULL;
                    free(tmp);
                    free(tree->right);
                    return;
                }

                if (tree->right->left != NULL && tree->right->right == NULL) { // узел 1 потомок - левый
                    _tree* tmp = tree->right;
                    tree->right = tree->right->left;
                    free(tmp);
                    return;
                }

                if (tree->right->left == NULL && tree->right->right != NULL) { // узел 1 потомок - правый
                    _tree* tmp = tree->right;
                    tree->right = tree->right->right;
                    free(tmp);
                    return;
                }
                
                if (tree->right->left != NULL && tree->right->right != NULL) { // узел 2 потомка
                    TreeItem tmp = tree_min_node(tree->right->right)->value;
                    tree_remove(tree, tree_min_node(tree->right->right)->value);
                    tree->right->value = tmp;
                    return;
                }

            }
        }

    }

    if (tree->value == remoVal) {
        tree_remove(tree, remoVal);
    } else if (tree->value < remoVal) {
        tree_remove(tree->right, remoVal);
    } else {
        tree_remove(tree->left, remoVal);
    }
}
void tree_add(_tree* tree, TreeItem value) // добавляет  потомка
{
    _tree* parent = tree_find(tree, tree->value); // с сохранением порядка в дереве
    if (value < parent->value) {
        if (parent->left == NULL) {
            parent->left = tree_create(value);
        } else {
            tree_add(parent->left, value);
        }
    } else if (value > parent->value) {
        if (parent->right == NULL) {
            parent->right = tree_create(value);
        } else {
            tree_add(parent->right, value);
        }
    }
}

void tree_print_node(_tree* tree, int indent) // Вывод на экран терминала узлы
{
    int i = 0;
    for (int i = 0; i < indent; ++i) { // Уменьшаем кол-во отступов \t
        printf("\t");
    }
    printf("%d\n", tree->value); // Значение узла

    if(tree->left != NULL) {
        tree_print_node(tree->left, indent + 1); // Если дочерний узел выводим его + отступ+1
    }

    if(tree->right != NULL) {
        tree_print_node(tree->right, indent + 1); // Если соседний то значение узла + отступ
    }
}

void tree_print(_tree* tree) // Рекурсивный вызов функции
{
    tree_print_node(tree, 0);
}
*/
/*int deep(_tree* tree, int c) // идет на дно и меряет глубину дна
{
    if (!tree) {
        return 0;
    }
    if (tree->left == NULL && tree->right == NULL) {
        return c;
    }
    int l = 0, r = 0;

    if (tree->left != NULL) {
        l = deep(tree->left, c + 1);
    }
    if (tree->right != NULL) {
        r = deep(tree->right, c + 1);
    }

    if (r >= l) { // дно левого и ли правого больше?
        return r;
    } else {
        return l;
    }
}


bool avl_tree(_tree* tree)
{
    if (!(tree->left) && !(tree->right)) {

        return true;

    } else if (tree->left && tree->right) {

        if (avl_tree(tree->left) && avl_tree(tree->right)) {
            if (abs((deep(tree->left, 0) - deep(tree->right, 0))) <= 1) {
                return true;
            } else {
                return false;
            }
        }

    } else if (tree->left) {

        if (deep(tree->left, 0) == 0) {
            return true;
        } else {
            return false;
        }

    } else if (tree->right) {

        if (deep(tree->right, 0) == 0) {
            return true;
        } else {
            return false;
        }
        
    }
    
    
}

bool avl(_tree* tree, bool flag)
{
    if (tree->left && flag) {
        avl(tree->left, flag);
    }

    if (tree->right && flag) {
        avl(tree->right, flag);
    }

    if (avl_tree(tree)) {
        return 1;
    } else {
        return 0;
    }

}*/