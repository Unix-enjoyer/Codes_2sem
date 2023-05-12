#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "deque.h"
#include <stdio.h>



int main()
{
    char s[10];

    Deque deque = NULL; // Указатель на дек
    int val = 0; // Переменная для задания новых элементов

    printf("\nPrint 'help' for more information\n\n"); // Выводим подсказку при запуске программы
    while (1) {
        scanf("%9s", s); // Ввод с клавиатуры
        if (!strcmp(s, "create")) {
            if (deque == NULL) {
                deque = dq_create();
                printf("\nDeque succesfully created\n\n");
            }
        } else if (!strcmp(s, "pushback")) {
            if (!deque) {
                printf("Tree doesnt exist, use command 'help'\n");
            } else {
                scanf("%d", &val);
                dq_push_back(deque, val);
            }
        } else if (!strcmp(s, "pushfront")) {
            if(!deque) {
                printf("Tree doesnt exist, use command 'help'\n"); //Если нет дерева, выводим подсказку
            } else {
                scanf("%d", &val);
                dq_push_front(deque, val);
            }
            
        } else if (!strcmp(s, "popback")) {
            if(!deque) {
                printf("Tree doesnt exist, use command 'help'\n"); //Если нет дерева, выводим подсказку
            } else {
                dq_pop_back(deque);
            }

        } else if (!strcmp(s, "popfront")) {
            if(!deque) {
                printf("Tree doesnt exist, use command 'help'\n"); //Если нет дерева, выводим подсказку
            } else {
                dq_pop_front(deque);
            }

        } else if (!strcmp(s, "print")) {
            if(!deque) {
                printf("Tree doesnt exist, use command 'help'\n"); //Если нет дерева, выводим подсказку
            } else {
                dq_print(deque);
            }

        } else if (!strcmp(s, "empty")) {
            if(!deque) {
                printf("Tree doesnt exist, use command 'help'\n"); //Если нет дерева, выводим подсказку
            } else {
                is_empty(deque);
            }

        } else if (!strcmp(s, "size")) {
            if(!deque) {
                printf("Tree doesnt exist, use command 'help'\n"); //Если нет дерева, выводим подсказку
            } else {
                printf("%d\n", dq_size(deque));
            }

        } else if (!strcmp(s, "sortrise")) {
            if(!deque) {
                printf("Tree doesnt exist, use command 'help'\n"); //Если нет дерева, выводим подсказку
            } else {
                deque = linear_choose_rise(deque);
            }

        } else if (!strcmp(s, "quit")) {
            if (deque) {
                dq_destroy(deque);
            }
            break;

        } else if (!strcmp(s, "help")) { // Помощник
            printf("Command 'create' - make new deque\n\n");
            printf("Command 'pushback' - adds vertices in the end of deque\n\n");
            printf("Command 'pushfront' - adds vertices in the begin of deque\n\n");
            printf("Command 'popback' - remove vertices from the end of deque\n\n");
            printf("Command 'popfront' - remove vertices from the begin of deque\n\n");
            printf("Command 'print' prints the vertices of the deque\n\n");
            printf("Command 'empty' checks if the deque is empty\n\n");
            printf("Command 'quit' stops the program\n\n");
        } else {
            printf("\n\nThat command doesnt exist, try command 'help' \n\n");
        }
    }
    return 0;
}