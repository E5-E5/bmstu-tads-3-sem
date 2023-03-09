#include<stdio.h>
#include<stdlib.h>
#include"../inc/structs.h"
#include"../inc/matrix_work.h"
#include"../inc/memory_work.h"
#include"../inc/multiplicate.h"
#include"../inc/timer.h"

#define OK 0

#define NO_MISTAKES 0

int main(void)
{
    setbuf(stdout, NULL);

    //print_info
    // ! Fgfgfgfgfgfgf
    // * SDSDSDS
    // TODO lol

    //// dfdfdfdfdf

    print_info();

    static_matrix_t matrix_stat = {.matrix = NULL, .x_len = 0, .y_len = 0, .no_zeroes = 0};
    list_t list = {.arr = NULL, .len = 0};

    int rc = NO_MISTAKES;

    rc = create_matrix(&matrix_stat, &list);

    if (rc != NO_MISTAKES)
    {
        free_matrix(matrix_stat);
        free_list(list);
        LOG_ERROR("Ошибка: %d", rc);
        return rc;
    }

    matrix_t parsed_matrix;

    rc = convert_matrix(matrix_stat, &parsed_matrix);

    if (rc != NO_MISTAKES)
    {
        free_all(parsed_matrix, matrix_stat, list);
        LOG_ERROR("Ошибка: %d", rc);
        return rc;
    }

    //free_all(parsed_matrix, matrix_stat, list);

    list_t result = {.arr = NULL, .len = matrix_stat.x_len};;

    rc = allocate_list(&result);

    if (rc != NO_MISTAKES)
    {
        puts("Ошибка: не удалось выделить память под массив результата");
        return ERR_ALLOCATE_MEMORY;
    }

    //free_matrix(matrix_stat.matrix, matrix_stat.x_len);
    int64_t start1, end1, start2, end2;
    int64_t res = 0;
    for (int i = 0; i < 10; i++)
    {
        static_matrix_t matrix_stat_temp = matrix_stat;
        list_t list_temp = list;
        start1 = tick();
        rc = multiplicate_ordinary(matrix_stat_temp, list_temp, &result);
        end1 = tick();
        res += end1 - start1;
    }
    

    puts("\n\nРезультат вычислений: ");
    print_list(result);

    puts("\n\nРезультат вычислений (в разреженном виде): ");
    print_parsed_list(result);

    if (rc != NO_MISTAKES)
    {
        free_list(result);
        free_all(parsed_matrix, matrix_stat, list);
        LOG_ERROR("Ошибка: %d", rc);
        return rc;
    }

    list_t result_parsed = {.arr = NULL, .len = parsed_matrix.ia_len};;

    rc = allocate_list(&result_parsed);

    if (rc != NO_MISTAKES)
    {
        puts("Ошибка: не удалось выделить память под массив результата");
        return ERR_ALLOCATE_MEMORY;
    }
    int64_t res_p = 0;
    for (int i = 0; i < 10; i++)
    {
        matrix_t parsed_matrix_temp = parsed_matrix;
        list_t list_temp = list;
        start2 = tick();
        rc = multiplicate_parsed_matrix(parsed_matrix_temp, list_temp, &result_parsed);
        end2 = tick();
        res_p += end2 - start2;
    }
    
    print_result(parsed_matrix, matrix_stat, res / 10, res_p / 10);


    if (rc != NO_MISTAKES)
    {
        free_list(result_parsed);
        free_list(result);
        free_all(parsed_matrix, matrix_stat, list);
        LOG_ERROR("Ошибка: %d", rc);
        return rc;
    }


    rc = compare_vectors(result, result_parsed);
    
    if (rc != NO_MISTAKES)
    {
        return rc;
    }

    free_list(result_parsed);
    free_list(result);
    free_all(parsed_matrix, matrix_stat, list);

    //free_all(parsed_matrix, matrix_stat, list);

    return OK;
}
