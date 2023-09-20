#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dlinkedList.h"
int main()
{
    char s[10];
    dlinkedList* Dlist = NULL;
    char val; // Переменная для задания новых элементов

    printf("\nPrint 'help' for more information\n\n"); // Выводим подсказку при запуске программы
    while (1) {
        scanf("%9s", s); // Ввод с клавиатуры
        if (!strcmp(s, "create")) {
                Dlist = dlinkedList_create();
                printf("\nList succesfully created\n\n");

        } else if (!strcmp(s, "pushback")) {
            if (!Dlist) {
                printf("List doesnt exist, use command 'help'\n");
            } else {
                getchar();
                printf("Значение для вставки: ");
                scanf("%c", &val);
                printf("\n");
                dlinkedList_pushback(Dlist, val);
            }

        } else if (!strcmp(s, "pushfront")) {
            if(!Dlist) {
                printf("List doesnt exist, use command 'help'\n"); 
            } else {
                getchar();
                printf("Значение для вставки: ");
                scanf("%c", &val);
                printf("\n");
                dlinkedList_pushfront(Dlist, val);
            }
            
        } else if (!strcmp(s, "popback")) {
            if(!Dlist) {
                printf("List doesnt exist, use command 'help'\n");
            } else {
                ListRm_back(Dlist);
            }

        } else if (!strcmp(s, "popfront")) {
            if(!Dlist) {
                printf("List doesnt exist, use command 'help'\n"); 
            } else {
                ListRm_front(Dlist);
            }

        } else if (!strcmp(s, "print")) {
            if(!Dlist) {
                printf("List doesnt exist, use command 'help'\n"); 
            } else {
                printf("\nThe list: ");
                printList(Dlist);
            }

        } else if (!strcmp(s, "change")) {
            if(!Dlist) {
                printf("List doesnt exist, use command 'help'\n"); 
            } else {
                ListChangePairs(Dlist);
            }

        } else if (!strcmp(s, "quit")) {
            if (Dlist) {
                dlinkedList_destroy(Dlist);
            }
            break;
        } else if (!strcmp(s, "insert")) {
            if(!Dlist) {
                printf("List doesnt exist, use command 'help'\n"); 
            } else {
                int ind;
                printf("Индекс для вставки: ");
                scanf("%d", &ind);
                printf("\n");
                getchar();
                printf("Значение для вставки: ");
                scanf("%c", &val);
                printf("\n");
                dlinkedList_insert(Dlist, ind, val);
            }

        } else if (!strcmp(s, "delete")) {
            if(!Dlist) {
                printf("List doesnt exist, use command 'help'\n"); 
            } else {
                int ind;
                printf("Индекс для удаления: ");
                scanf(" %d", &ind);
                dlinkedList_delete(Dlist, ind);
                printf("\n");
            }
            
        } else if (!strcmp(s, "help")) { // Помощник
            printf("Command 'create' - make new Dlist\n\n");
            printf("Command 'pushback' - adds vertices in the end of list\n\n");
            printf("Command 'pushfront' - adds vertices in the begin of list\n\n");
            printf("Command 'popback' - remove vertices from the end of list\n\n");
            printf("Command 'popfront' - remove vertices from the begin of list\n\n");
            printf("Command 'print' prints the vertices of the list\n\n");
            printf("Command 'quit' stops the program\n\n");
            printf("Command 'change' changes the pairs in list\n\n");
            printf("Command 'delete' delete an element by index\n\n");
            printf("Command 'insert' paste an element by index\n\n");
            printf("Example of command with parameters: \n");
            printf("insert\n");
            printf("Индекс для вставки: 3\n");
            printf("Значение для вставки: A\n\n");
        } else {
            printf("\n\nThat command doesnt exist, try command 'help' \n\n");
        }
    }
    return 0;
    /*dlinkedDlist* dlDlist = dlinkedDlist_create();
    dlinkedDlist_pushfront(dlDlist, 'Q');
    dlinkedDlist_pushfront(dlDlist, 'A');
    dlinkedDlist_pushfront(dlDlist, 'W');
    dlinkedDlist_insert(dlDlist, 0, 'F');
    dlinkedDlist_insert(dlDlist, 3, 'C');
    dlinkedDlist_insert(dlDlist, 2, 'Y');
    //printDlist(dlDlist);
    DlistRm_front(dlDlist);
    //printDlist(dlDlist);
    //dlinkedDlist_delete(dlDlist, 3);
    printDlist(dlDlist);

    DlistChangePairs(dlDlist);
    printDlist(dlDlist);

    dlinkedDlist_destroy(dlDlist);*/
}