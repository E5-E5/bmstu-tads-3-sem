#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

#include "../inc/struct.h"
#include "../inc/file.h"
#include "../inc/search.h"
#include "../inc/sort.h"

int bubble_sort_country(country_info_t *array, int size)
{
    if (size == 0)
    {
        puts("Таблица пустая");
        return 1; 
    }

    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            //if (flats_arr[j].square > flats_arr[j + 1].square)
            if (strcmp(array[j].country, array[j + 1].country) > 0)
                swap_country(array, j, j + 1);
                
    return 0;
}

void swap_keys(keys_t *keys, int i, int j)
{
    keys_t tmp;

    tmp = keys[i];
    keys[i] = keys[j];
    keys[j] = tmp;
}

int bubble_sort_keys(keys_t *key, int size)
{

    if (size == 0)
    {
        puts("Таблица пустая");
        return 1;
    }  
    
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (strcmp(key[j].country, key[j + 1].country) > 0)
                swap_keys(key, j, j + 1);

    //puts("Таблица ключей сортировкой пузырьком успешно отсортирована");
}

int comparator_table(const void *val1, const void *val2)
{
    return strcmp(((country_info_t*)(val1))->country, ((country_info_t*)(val2))->country);
}

void qsort_table(country_info_t *array, int size)
{
    if (size == 0)
    {
        puts("Таблица пустая");
        return;
    }
    
    qsort(array, size, sizeof(country_info_t), comparator_table);

    //puts("Таблица сортировкой qsort успешно отсортирована");
}

int comparator_keys(const void *val1, const void *val2)
{
    return (strcmp(((keys_t*)(val1))->country, ((keys_t*)(val2))->country));
}

void qsort_table_keys(keys_t *key, int size)
{   
    if (size == 0)
    {
        puts("Таблица пустая");
        return;
    }
	
    qsort(key, size, sizeof(keys_t), comparator_keys);

    //puts("Таблица ключей сортировкой qsort успешно отсортирована");
}

uint64_t tick_count(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}


void print_result(int64_t res)
{
    printf("\n %.10lf секунд\n\n", (double)(res)/GHZ);
}

short int compare_sorts(FILE *file)
{
    int64_t start1, end1, start2, end2, start3, end3, start4, end4;

    country_info_t country_info[100];
    keys_t keys[100];
    int size = 0;
    int rc = read_file(file, country_info, &size);
    printf("\n\nСортировка файла из %d записей\n\n", size);
    puts("-------------------------------------------------------------------------");
///////////////////////////////////
    int64_t result = 0;
    for (int i = 0; i < 20; i++)
    {
        int rc = read_file(file, country_info, &size);
        start1 = tick_count();
        bubble_sort_country(country_info, size);
        end1 = tick_count();
        result += end1 - start1;
        rewind(file);
    }

    puts("Сортировка таблицы пузырьком: ");
    print_result(result / 20);
    puts("-------------------------------------------------------------------------");
//////////////////////////////////////////////  
    rewind(file);
    size = 0; 
    result = 0;
    for (int i = 0; i < 30; i++)
    {
        int rc = read_file(file, country_info, &size);
        for (int i = 0; i < size ; i++)
        {
            strncpy(keys[i].country, country_info[i].country, 50);
            keys[i].id = i;
        }
        start2 = tick_count();
        bubble_sort_keys(keys, size);
        end2 = tick_count();
        result += end2 - start2;
        rewind(file);
    }

    puts("Сортировка таблицы ключей пузырьком: ");
    print_result(result / 30);
    puts("-------------------------------------------------------------------------");
//////////////////////////////////////////////   
    size = 0;  
    result = 0;
    rc = read_file(file, country_info, &size); 
    for (int i = 0; i < 20; i++)
    {     
        int rc = read_file(file, country_info, &size);     
        start3 = tick_count();
        qsort_table(country_info, size);
        end3 = tick_count();
        result += end3 - start3;
        rewind(file);
    }    
    rewind(file);
    puts("Сортировка таблицы qsort: ");
    print_result(result / 20);
    puts("-------------------------------------------------------------------------");
//////////////////////////////////////////////////
    rewind(file);
    size = 0;    
    
    result = 0;
    rc = read_file(file, country_info, &size);
    for (int i = 0; i < size ; i++)
    {
        strncpy(keys[i].country, country_info[i].country, 50);
        keys[i].id = i;
    }
    for (int i = 0; i < 20; i++)
    {     
        int rc = read_file(file, country_info, &size);
        for (int i = 0; i < size ; i++)
        {
            strncpy(keys[i].country, country_info[i].country, 50);
            keys[i].id = i;
        }
        start4= tick_count();
        qsort_table_keys(keys, size);
        end4 = tick_count();
        result += end4 - start4;
        rewind(file);
    }       

    puts("Сортировка таблицы qsort c ключами: ");
    print_result(result / 20);
    puts("-------------------------------------------------------------------------");
    

    printf("\n%lu размер таблицы (в байтах)\n\n", sizeof(*country_info) * size);
    printf("\n%lu размер таблицы ключей (в байтах)\n\n", sizeof(*keys) * size);
    
    return 0;
}
