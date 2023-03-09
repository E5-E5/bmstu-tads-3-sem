#include"../inc/ddp_avl.h"


void free_tree(node_t *tree)
{
    if (tree)
    {
        free_tree(tree->left);
        free_tree(tree->right);
    }

    free(tree);
}


node_t *tree_init_node(int num, int height)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
    {
        return NULL;
    }

    node->data = num;
    node->height = height;
    node->left = NULL;
    node->right = NULL;

    return node;
}


node_t *add_ddp(node_t *ddp, int data, int *height, int *comp)
{
    (*height)++;
    (*comp)++;

    if (!ddp)
    {
        ddp = tree_init_node(data, *height);
    }
    else if (data < ddp->data)
    {
        ddp->left = add_ddp(ddp->left, data, height, comp);
    }
    else if (data > ddp->data)
    {
        ddp->right = add_ddp(ddp->right, data, height, comp);
    }

    return ddp;
}


int fill_ddp(node_t **ddp, arr_t arr)
{
    for (int i = 0; i < arr.len; i++)
    {
        int height = -1;

        int comp = 0;

        *ddp = add_ddp(*ddp, arr.data[i], &height, &comp);
    }

    return OK_FILL_DDP;
}

void print_tree(node_t *tree, int place, int *head, int *head_count)
{
    int space = 5;

    if (tree)
    {
        place += space;

        print_tree(tree->right, place, head, head_count);
        
        puts("");

        for (int i = space; i < place; i++)
        {
            printf(" ");
        }

        printf("( %d )\n", tree->data);
        
	if (*head_count < tree->height)
		*head_count = tree->height;
	head[tree->height] = head[tree->height] + 1;
		
        print_tree(tree->left, place, head, head_count);
    }
}
