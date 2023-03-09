#include"../inc/main_inc.h"


int main(void)
{
    int option = -1;
    arr_t arr = {.data = NULL, .len = 0, .capacity = 0, .max_cap = 0};
    node_t *ddp = NULL;
    char filename[250];

    while (option != 0)
    {
        print_menu();

        int rc = scanf("%d", &option);

        if (rc != 1)
        {
            puts("Ошибка: неверно введен пункт меню, повторите попытку");
            flush_input();
            continue;
        }


        flush_input();

        if (option == 1)
        {
            rc = read_file(&arr, filename);

            if (rc != NO_MISTAKES)
                continue;

            fill_ddp(&ddp, arr);
        }

        if (option == 2)
        {
            int head[1000] = {0};
            int head_count = 0;
            
            print_tree(ddp, 0, head, &head_count);            
            printf("\n");
            
            for ( int i = 0; i <= head_count; i++)
            	printf("Уровень %d - %d узел(-ла)\n", i + 1, head[i]);
        }

        if (option == 3)
            add_all(&ddp, &arr, filename);
    }

    free_tree(ddp);
    free(arr.data);

    return OK;
}
