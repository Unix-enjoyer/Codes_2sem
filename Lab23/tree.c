#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

struct _tree { // структура - дерево, Tree явл указателем на узел(дерево)
    TreeItem value;
    Tree left;
    Tree right;
};

Tree tree_create(TreeItem rootValue) // создание узла по переданному значению
{
    Tree tree = (Tree) malloc(sizeof(*tree));
    
    tree->value = rootValue;
    tree->left = NULL;
    tree->right = NULL;

    return tree;
}

Tree tree_find(Tree tree, TreeItem findVal) // ищет указанное значение в дереве и 
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

Tree tree_min_node(Tree tree)
{
    if (tree->left != NULL) {
        return tree_min_node(tree->left);
    } else {
        return tree;
    }
}

void tree_destroy(Tree tree) // удаляет дерево от листов к корню
{
    if (tree->left) {
        tree_destroy(tree->left);
    }
    if (tree->right) {
        tree_destroy(tree->right);
    }
    free(tree);
}

void tree_remove(Tree tree, TreeItem remoVal) // удаляет элемент дерева
{
    if (tree != NULL) {

        if (tree->left != NULL) { // 3 случая
            if (tree->left->value == remoVal) { // для левого потомка

                if (tree->left->left == NULL && tree->left->right == NULL) { // лист - потомки NULL`евые
                    Tree tmp = tree->left;
                    tree->left = NULL;
                    free(tmp);
                    free(tree->left);
                    return;
                }

                if (tree->left->left != NULL && tree->left->right == NULL) { // узел 1 потомок - левый
                    Tree tmp = tree->left;
                    tree->left = tree->left->left;
                    free(tmp);
                    return;
                }

                if (tree->left->left == NULL && tree->left->right != NULL) { // узел 1 потомок - левый
                    Tree tmp = tree->left;
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
                    Tree tmp = tree->right;
                    tree->right = NULL;
                    free(tmp);
                    free(tree->right);
                    return;
                }

                if (tree->right->left != NULL && tree->right->right == NULL) { // узел 1 потомок - левый
                    Tree tmp = tree->right;
                    tree->right = tree->right->left;
                    free(tmp);
                    return;
                }

                if (tree->right->left == NULL && tree->right->right != NULL) { // узел 1 потомок - левый
                    Tree tmp = tree->right;
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
void tree_add(Tree tree, TreeItem value) // добавляет  потомка
{
    Tree parent = tree_find(tree, tree->value); // с сохранением порядка в дереве
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

void tree_print_node(Tree tree, int indent) // Вывод на экран терминала узлы
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

void tree_print(Tree tree) // Рекурсивный вызов функции
{
    tree_print_node(tree, 0);
}

int deep(Tree tree, int c) // идет на дно и меряет глубину дна
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


bool avl_tree(Tree tree)
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

bool avl(Tree tree, bool flag)
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

}