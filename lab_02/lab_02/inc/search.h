#include<stdio.h>
#include<string.h>

#ifndef SEARCH_H
#define SEARCH_H

void print_table();
void print_table_key();
void print_string_key(keys_t key);
void print_key_table(country_info_t *array, keys_t *key, int size);
void print_string(country_info_t array, int index);
int add_country(country_info_t *array, int *size);
void swap_country(country_info_t *array, int i, int j);
void del_by_pos(country_info_t *array, int size, int flat);
short int delete_by_country(country_info_t *array, int *size);
int search(country_info_t *array, int size);

#endif
