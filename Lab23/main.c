#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"
#include <stdio.h>



int main()
{
    char s[8];

    Tree tree = NULL; // Указатель на корень дерева
    int root = 0, ver = 0; // Переменные для новых узлов дерева

    printf("\nPrint 'help' for more information\n\n"); // Выводим подсказку при запуске программы
    while (1) {
        scanf("%7s", s); // Ввод символа с клавиатуры
        if (!strcmp(s, "insert")) { // Задаем корень дерева
            if (tree == NULL) {
                scanf("%d", &root);
                tree = tree_create(root);
            }
            while (scanf("%d", &ver)) {
                tree_add(tree, ver);
            }
        } else if (!strcmp(s, "delete")) { // Если команда delete
            if(!tree) {
                printf("Tree doesnt exist, use command 'help'\n"); //Если нет дерева, выводим подсказку
            } else {
                scanf("%d", &ver);
                tree_remove(tree, ver); // Удаляем зачение
            }
        } else if (!strcmp(s, "quit")) { // Если команда quit
            if (tree) {
                tree_destroy(tree);
                } // Рушим дерево 
                break;
        } else if (!strcmp(s, "avl")) { // Если команда run, начинаем проверку на avl tree
            if(!tree) printf("Tree doesnt exist, use command 'help'\n"); 
            else {
                if (avl(tree, 1)) {
                    printf("Yes\n");
                } else {
                    printf("NOOOOO\n");
                }
            }
        } else if (!strcmp(s, "print")) { // Если команда print, выводим дерево
            if (!tree) printf("Tree doesnt exist, use command 'help'\n");
            else {
                printf("\n\n");
                tree_print(tree);
                printf("\n\n");
            }
        } else if (!strcmp(s, "destroy")) { // Удаляем дерево
            if (!tree) printf("Tree doesnt exist, use command 'help'\n");
            else {
                tree_destroy(tree);
                tree = NULL;
            }
        } else if (!strcmp(s, "help")) { // Помощник
            printf("\n\nCommand 'insert' - if the tree doesnt exist, makes a tree. If tree was made, adds vertices in the tree\n\n");
            printf("Command 'delete num' deletes all the vertices and all her children\n\n");
            printf("Command 'print' prints the vertices of the tree\n\n");
            printf("Command 'avl' checks if the tree is avl-tree\n\n");
            printf("Command 'quit' stops the program\n\n");
            printf("Command 'destroy' deletes the tree completely\n\n");
        } else {
            printf("\n\nThat command doesnt exist, try command 'help' \n\n");
        }
    }
    return 0;
}