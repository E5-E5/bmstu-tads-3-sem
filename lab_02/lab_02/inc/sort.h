#include<stdio.h>
#include<string.h>
#include <stdint.h>

#ifndef SORT_H
#define SORT_H

#define GHZ 3500000000

int bubble_sort_country(country_info_t *array, int size);
void swap_keys(keys_t *keys, int i, int j);
int bubble_sort_keys(keys_t *key, int size);
int comparator_table(const void *val1, const void *val2);
void qsort_table(country_info_t *array, int size);
int comparator_keys(const void *val1, const void *val2);
void qsort_table_keys(keys_t *key, int size);
uint64_t tick_count(void);
void print_result(int64_t result);
short int compare_sorts(FILE *flats_file);

#endif
