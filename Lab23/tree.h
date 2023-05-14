#ifndef _TREE_H_ // инициализация
#define _TREE_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int TreeItem;
typedef struct _tree* Tree; 

Tree tree_create(TreeItem rootValue);

Tree tree_find(Tree tree, TreeItem findVal);

Tree tree_min_node(Tree tree);

void tree_remove(Tree tree, TreeItem remoVal);

void tree_add(Tree tree, TreeItem value);

void tree_print_node(Tree tree, int indent);

void tree_print(Tree tree);

int deep(Tree tree, int c);

bool is_avl(Tree tree);

void tree_destroy(Tree tree);

bool avl(Tree tree, bool flag);

#endif // _TREE_H_
