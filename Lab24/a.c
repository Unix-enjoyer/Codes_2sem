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

StackElem* stackElem_create(char symbol) // создаст элемент СТЕКА (с указателем на соседа)
{
    StackElem* element = (StackElem*) malloc(sizeof(*element));
    Operator* operator = op_create(symbol);
    
    element->value = operator; // теперь элемент стека содержит значение (оператор)
    element->next = NULL; // ссыдка на соседа налл
    return element;
}

void stack_push(Stack* stack, char symbol) // положить в стек
{
    if (!stack) { // если стека нет - создать
        stack = stack_create();
    }
    StackElem* elemSt = stackElem_create(symbol); // сделать из символа элемент стека(с указателем)

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

    return tmp;
}

void freeStackElem(StackElem* stackElem) { // очистка вытащенного элемента
    free(stackElem->value);
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
            printf("Неправильный ввод, ведите другое мат выражение с допустимым набором операций\n");
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
void dijkstra(Stack* stack, char expression[STR_SIZE], char parsedExpr[STR_SIZE]) 
{
    int number = INT_MAX;
    //printf("\nexpres = %s", expression);
    //printf("\nparsed = %s\n", parsedExpr);
    char symbol = ' ';
    //printf("\n\nstrlen = %ld\n\n",strlen(expression));

    for (int i = 0; i < strlen(expression); i++) {
        printf("el = %c\n", expression[i]);
        if (isdigit(expression[i])) { // если текущая и след - цифры => еще собираем число
            
            if (number == INT_MAX) {
                number = 0;
            }
            //printf("number vnach = %d", number);
            if (isdigit(expression[i + 1])) {
                //printf("raznost  = %d",expression[i] - '0');
                number = number*10 + (expression[i] - '0');
                //printf("number  = %d\n",number);
            } else { // число уже собрали, надо заврешать и парсить
                //printf("raznost  = %d",expression[i] - '0');
                number = number*10 + (expression[i] - '0');
                
                printf("number  = %d\n",number);
                
                if (number != INT_MAX) { // число
                    char buf[STR_SIZE] = "";
                    snprintf(buf, STR_SIZE, "%d", number);
                    strncat(parsedExpr, buf, STR_SIZE); // пишем в итоговую строку
                    printf("tekush itog = %s", parsedExpr);
                }

                number = INT_MAX;
            }

        } /*else if (isalpha(expression[i])) { // буква (константа) - сразу парсим
            symbol = expression[i];
            
            char buf[STR_SIZE] = "";
            snprintf(buf, STR_SIZE, "%c", symbol);
            strncat(parsedExpr, buf, STR_SIZE); // пишем в итоговую строку

        } else if (isspace(expression[i])) { // встречен пробел
            continue;

        } else if (ispunct(expression[i])) { // знак мат операции
            symbol = expression[i];

            int topPriority = stack->top->value->priority; // приоритет верха стека < чем у текщуго
            int preliminaryPriority = checkPriority(symbol); 

            if ((st_size(stack)) == 0 || (topPriority < preliminaryPriority)) { // либо стек пустой
                stack_push(stack, symbol); // кладем элемент

            } else if (topPriority >= preliminaryPriority) {

                while (topPriority >= preliminaryPriority) {
                    StackElem* popEl = stack_pop(stack); // берем новый

                    topPriority = stack->top->value->priority;

                    char buf[STR_SIZE] = "";
                    snprintf(buf, STR_SIZE, "%c", popEl->value->symbol); // из стека в строку
                    strncat(parsedExpr, buf, STR_SIZE); // пишем в итоговую строку
                    freeStackElem(popEl); // из стека вытащили, он ни на кого не ссылается
                    // на него тоже, надо удалить его, нам этот элемент не нужен больше

                }

            }


        } else if (symbol == '(') { // положить в стек
            stack_push(stack, symbol);

        } else if (symbol == ')') { // ложить в стек, пока 1)
            StackElem* popEl = stack_pop(stack);

            while (popEl->value->symbol != '(') {

                char buf[STR_SIZE] = "";
                snprintf(buf, STR_SIZE, "%c", popEl->value->symbol); // из стека в строку
                strncat(parsedExpr, buf, STR_SIZE); // пишем в итоговую строку
                freeStackElem(popEl); // из стека вытащили, он ни на кого не ссылается
                // на него тоже, надо удалить его, нам этот элемент не нужен больше
                popEl = stack_pop(stack); // берем новый
            }
            freeStackElem(popEl); // 1 раз недоработал, надо скобку еще очистить

        }
        printf("%s\n", parsedExpr);*/
    }    

    /*while (st_size(stack) > 0) {
    
        StackElem* popEl = stack_pop(stack);
        
        char buf[STR_SIZE] = "";
        snprintf(buf, STR_SIZE, "%c", popEl->value->symbol); // из стека в строку
        strncat(parsedExpr, buf, STR_SIZE); // пишем в итоговую строку
        freeStackElem(popEl);
    }*/

}


int main()

{
    /*char c;
    while ((c = getchar()) != '\n') {
    printf("%c ", c);
    }*/
    /*int hi = 2;
    char hii[100] = "";

    snprintf(hii, 100, "%d", hi);// 2
    char barbie[100] = "Barbie";
    char cc[100];
    strncat(cc, hii, 100);
    strncat(cc, barbie, 100);
    printf("%s", cc);*/

    /*
    char parsedExpr[100];
    int number = 12345;
    char buf[100] = "";
    snprintf(buf, 100, "%d", number);
    strncat(parsedExpr, buf, 100);
    printf("%s", parsedExpr);*/
    /*int i;
    for (i = 0; i < 10; i++) {

        if (i == 3) {
            for (i; i != 8; i++) {
                printf("\t%d\t", i);
            }
        }
        printf("%d\n", i);
    }*/

    Stack* stack = stack_create();
    char expression[100];
    char parsedExpression[100];
    printf("Введите мат выражение, в конце нажмите энтер:\n");
    fgets(expression, 100, stdin);
    expression[strlen(expression)-1] = '\0'; // теперь у нас норм строка с пробелами, без лишнего
    printf("%s\n", expression);
    dijkstra(stack, expression, parsedExpression);
    //printf("\ns = %s", parsedExpression);
}