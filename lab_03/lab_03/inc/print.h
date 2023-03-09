#include<stdlib.h>
#include<stdio.h>
#include<inttypes.h>
#include"../inc/macrologger.h"
#include"../inc/structs.h"
#include"../inc/memory_work.h"


#ifndef PRINT_H

#define PRINT_H

#define GHZ 3500000000

void print_info(void);

void print_matrix(static_matrix_t matrix);

void print_list(list_t list);

void print_parsed_matrix(matrix_t matrix);

void print_time(int64_t res);

void print_result(matrix_t parsed_matrix, static_matrix_t matrix_stat, int64_t res, int64_t res_p);

void print_parsed_list(list_t list);

#endif
