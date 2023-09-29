#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "table.h"
int main()
{
    char s[10];
    char keys[STRSIZE];
    char values[STRSIZE];
    table* tabl = NULL;
    //char val; // Переменная для задания новых элементов
    int pos;
    char insert[STRSIZE];
    float key;
    int num;

    printf("\nPrint 'help' for more information\n\n"); // Выводим подсказку при запуске программы
    while (1) {
        scanf("%9s", s); // Ввод с клавиатуры
        if (!strcmp(s, "create")) {
                printf("Сколько строк будет в таблице?\n");
                scanf("%d", &num);
                tabl = createTable(num);
                printf("Введите имя файла с ключами\n");
                scanf("%s", keys);
                printf("Введите имя файла со значениями\n");
                scanf("%s", values);
                fileRead(tabl, keys, values);
                printf("\nTable succesfully created\n\n");

        } else if (!strcmp(s, "insert")) {
            if (!tabl) {
                printf("tabl doesnt exist, use command 'help'\n");
            } else {
                getchar();
                printf("Позиция для вставки: \n");
                scanf("%d", &pos);
                printf("Ключ для вставки: \n");
                scanf("%f", &key);
                printf("Значение для вставки: \n");
                scanf("%99s\n", insert);
                //printf("\n");
                addToTable(tabl, pos, key, insert);
            }

        } else if (!strcmp(s, "print")) {
            if(!tabl) {
                printf("tabl doesnt exist, use command 'help'\n"); 
            } else {
                getchar();
                printTable(tabl);
            }
            
        } else if (!strcmp(s, "find")) {
            if(!tabl) {
                printf("tabl doesnt exist, use command 'help'\n");
            } else {
                printf("Введите ключ для поиска по таблице: \n");
                scanf("%f", &key);
                element* el = getValue(tabl, key);
                /*if (el = NULL) {
                    printf("idi nahren");
                }*/
                //printf("%s\n", el->value);
                if (el) {
                    //printf("idi nahren");
                    printf("Найденное значение: \n");
                    printf("%s\n", el->value);
                } else {
                    printf("Ты данные отсортировал, дядя?\n");
                }
            }

        } else if (!strcmp(s, "reverse")) {
            if(!tabl) {
                printf("tabl doesnt exist, use command 'help'\n"); 
            } else {
                reverseTable(tabl);
            }

        } else if (!strcmp(s, "sort")) {
            if(!tabl) {
                printf("tabl doesnt exist, use command 'help'\n"); 
            } else {
                if (!checkSortTable(tabl)) {
                    sortShell(tabl);
                }

            }

        } else if (!strcmp(s, "overwrite")) {
            if(!tabl) {
                printf("tabl doesnt exist, use command 'help'\n"); 
            } else {
                writeToFile(tabl, keys, values);
            }

        } else if (!strcmp(s, "quit")) {
            if (tabl) {
                destroyTable(tabl);
            }
            break;
        } else if (!strcmp(s, "help")) { // Помощник
            printf("Command 'create' - make new tabl\n\n");
            printf("Command 'print' prints the line of the tabl\n\n");
            printf("Command 'quit' stops the program\n\n");
            printf("Command 'insert' paste an element by index\n\n");
            printf("Command 'overwrite' overwrite the file by table\n\n");
            printf("Command 'sort' make the Shell`s sort for table\n\n");
            printf("Command 'reverse' fills in the table backwards\n\n");
            printf("Command 'find' finds the valuy by key in the table\n\n");
            printf("Command 'quit' stops the program\n\n");

            printf("Example of command with parameters: \n");
            printf("insert\n");
            printf("Индекс для вставки: 3\n");
            printf("Значение для вставки: AAAAAAAAAAA\n\n");
        } else {
            printf("\n\nThat command doesnt exist, try command 'help' \n\n");
        }
    }
    return 0;
}