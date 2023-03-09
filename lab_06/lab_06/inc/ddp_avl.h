#include<stdio.h>
#include<stdlib.h>
#include"../inc/structs.h"


#ifndef DDP_AVL_H
#define DDP_AVL_H

#define OK_FILL_DDP 0

int fill_ddp(node_t **ddp, arr_t arr);

void print_tree(node_t *tree, int place, int *head, int *head_count);

void free_tree(node_t *tree);

node_t *add_ddp(node_t *ddp, int data, int *height, int *comp);

#endif
