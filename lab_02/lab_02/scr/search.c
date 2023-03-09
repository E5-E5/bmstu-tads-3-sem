#include <stdlib.h>
#include <stdio.h>

#include "../inc/struct.h"
#include "../inc/search.h"

void print_table()
{
    puts("------------------------------------------------------------------------------------------------------------------------------------------------------");
    puts("| № |   Страна   | Кол-во людей |   Столица   |  Материк  | ПЦР |      Тип     | Объекты |   Вид   | Сезон | t_a | t_w | Перелет | Спорт | Стоимость |");
    puts("------------------------------------------------------------------------------------------------------------------------------------------------------");
}

void print_table_key()
{
    puts("--------------------");
    puts("| № |    Страна    |");
    puts("--------------------");
}

void print_string(country_info_t array, int index)
{  
    printf("|%3d. %-13s %-15d %-13s %-11s", index + 1, array.country, array.count_people, array.capital, array.mainland);
    if (array.PCR == 1)
        printf("+ "); 
    else
        printf("- "); 
    
    if (array.tourism == 1)
        printf("%15s %8d %10s %7c %5c %5c %9c %8c %8c   |\n", "Sightseeing:", array.holiday_kind_t.excursion_holiday.number_objects,
            array.holiday_kind_t.excursion_holiday.main_view, '-', '-', '-', '-', '-', '-');
    else if (array.tourism == 2)
        printf("%15s %8c %10c %7s %5d %5d %9d %8c %8c   |\n", "Beach:", '-', '-', array.holiday_kind_t.beach_holiday.season, array.holiday_kind_t.beach_holiday.temperature_air,
            array.holiday_kind_t.beach_holiday.temperature_water, array.holiday_kind_t.beach_holiday.flight_time, '-', '-');
    else if (array.tourism == 3)
        printf("%15s %8c %10c %7c %5c %5c %9c %8s %8d   |\n", "Sports", '-', '-', '-', '-', '-', '-', array.holiday_kind_t.sports_holiday.view_sports, array.holiday_kind_t.sports_holiday.minimum_cost);
}

void print_key_table(country_info_t *array, keys_t *key, int size)
{  
    print_table();
    for (int i = 0; i < size; i++)
    {
    	print_string(array[key[i].id], i);
    }
    puts("------------------------------------------------------------------------------------------------------------------------------------------------------");
}

void print_string_key(keys_t key)
{  
    printf("|%3d. %-13s|\n", key.id, key.country);
}

int add_country(country_info_t *array, int *size)
{
    country_info_t new_country;
    
    puts("\nВведите страну (одно слово без пробелов):");
    if (scanf("%s", new_country.country) != 1)
    {
        puts("Ошибка: неверно введёна страна");
        return EXIT_FAILURE;
    }

    puts("\nВведите количество людей:");
    if (scanf("%d", &new_country.count_people) != 1)
    {
        puts("Ошибка: неверно введено кол-во людей");
        return EXIT_FAILURE;
    }

    puts("\nВведите столицу (одно слово без пробелов):");
    if (scanf("%s", new_country.capital) != 1)
    {
        puts("Ошибка: неверно введена столица");
        return EXIT_FAILURE;
    }

    puts("\nВведите материк (одно слово без пробелов):");
    if (scanf("%s", new_country.mainland) != 1)
    {
        puts("Ошибка: неверно введен материк");
        return EXIT_FAILURE;
    }
    
    puts("\nВведите необходиомсть ПЦР теста (0 - не нужен; 1 - нужен):");
    if ((scanf("%d", &new_country.PCR) != 1) || (new_country.PCR != 0) && (new_country.PCR != 1))
    {
        puts("Ошибка: неверно введена необходиомсть ПЦР теста");
        return EXIT_FAILURE;
    }
    
    puts("\nВведите вид туризма (1 - экскурсионный, 2 - пляжный, 3 - спортивный):");
    if (scanf("%d", &new_country.tourism) != 1)
    {
        puts("Ошибка: неверно введен вид туризма");
        return EXIT_FAILURE;
    }

    if (new_country.tourism == 1)
    {
        puts("\nВведите количество исторических объектов:");
        if ((scanf("%d", &new_country.holiday_kind_t.excursion_holiday.number_objects) != 1) || (new_country.holiday_kind_t.excursion_holiday.number_objects < 0))
        {
            puts("Ошибка: неверно введено количество исторических объектов");
            return EXIT_FAILURE;
        }
        
        puts("\nВведите основной вид (природа, история, искусство):");
        if (scanf("%s", new_country.holiday_kind_t.excursion_holiday.main_view) != 1)
        {
            puts("Ошибка: неверно введен основной вид");
            return EXIT_FAILURE;
        }
    }                
    else if (new_country.tourism == 2)
    {
        puts("\nВведите сезон:");
        if (scanf("%s", new_country.holiday_kind_t.beach_holiday.season) != 1)
        {
            puts("Ошибка: неверно введён сезон");
            return EXIT_FAILURE;
        }

        puts("\nВведите температуру воздуха:");
        if (scanf("%d", &new_country.holiday_kind_t.beach_holiday.temperature_air) != 1)
        {
            puts("Ошибка: неверно введена температуру воздуха");
            return EXIT_FAILURE;
        }

        puts("\nВведите температуру воды:");
        if (scanf("%d", &new_country.holiday_kind_t.beach_holiday.temperature_water) != 1)
        {
            puts("Ошибка: неверно введена температура воды");
            return EXIT_FAILURE;
        }

        puts("\nВведите время перелета:");
        if ((scanf("%d", &new_country.holiday_kind_t.beach_holiday.flight_time) != 1) || (new_country.holiday_kind_t.beach_holiday.flight_time <= 0))
        {
            puts("Ошибка: неверно введено время перелета");
            return EXIT_FAILURE;
        }
    }
    else if (new_country.tourism == 3)
    {
        puts("\nВведите вид спорта:");
        if (scanf("%s", new_country.holiday_kind_t.sports_holiday.view_sports) != 1)
        {
            puts("Ошибка: неверно введён вид спорта");
            return EXIT_FAILURE;
        }

        puts("\nВведите минимальную стоимость:");
        if ((scanf("%d", &new_country.holiday_kind_t.sports_holiday.minimum_cost) != 1) || (new_country.holiday_kind_t.sports_holiday.minimum_cost < 0))
        {
            puts("Ошибка: неверно введена минимальная стоимость");
            return EXIT_FAILURE;
        }
    }
    else
       return EXIT_FAILURE; 
    
    array[*size] = new_country;     
    (*size)++;
    
    if (*size > 100)
    {
        puts("Ошибка: количество записей переполнено");
        return EXIT_FAILURE;
    }
    
    puts("Страна была успешно добавлена\n");
    return 0;
}    

void swap_country(country_info_t *array, int i, int j)
{
    country_info_t tmp;

    tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

void del_by_pos(country_info_t *array, int size, int flat)
{
    for (int i = flat; i < size; i++)
        swap_country(array, i, i + 1);
}

short int delete_by_country(country_info_t *array, int *size)
{
    if (*size == 0)
    {
        puts("\nТаблица пустая\n");
        return 0;
    }
    puts("Введите страну, информация по которым будет удалена:");

    char del_country[100];
    int rc = scanf("%s", del_country);
    int size_arr = *size;

    if ((rc != 1) || (strlen(del_country) < 1))
    {
        puts("Ошибка: неверно введена страна");
        return 1;
    }
    
    int flag = 1;
    for (int i = 0; i < *size; i++)
        for (int j = 0; j < size_arr; j++)
            if (strcmp (array[j].country, del_country) == 0 && (j < *size))
            {   
                flag = 0;
                del_by_pos(array, *size, j);
                *size -= 1;
                size_arr--;
            }

    if (flag)
        puts("Не найдены указанные страны");
    else
        puts("Успешно удалены страны из таблицы");

    return 0;
}

int search(country_info_t *array, int size)
{

    if (size == 0)
    {
        puts("Таблица пустая");
        return 1;
    }

    char land[50], sport[50];

    puts("Введите название материка:");
    int rc = scanf("%s", land);

    if ((rc != 1) || (strlen(land) < 1))
    {
        puts("Ошибка: неверно введен материк");
        return 1;
    }
    
    puts("Введите название спорта:");
    rc = scanf("%s", sport);

    if ((rc != 1) || (strlen(sport) < 1))
    {
        puts("Ошибка: неверно введен спорт");
        return 1;
    }
    
    int check = 1;
    for (int i = 0; i < size; i++)
        if ((strcmp(array[i].mainland, land) == 0) && (array[i].tourism == 3) && (strcmp(array[i].holiday_kind_t.sports_holiday.view_sports, sport) == 0))
        {
            if (check)
                print_table();
            print_string(array[i], i);
            check = 0;
        }
    if (check)
        puts("Ничего не было найдено");
    else
        puts("------------------------------------------------------------------------------------------------------------------------------------------------------");


    return 0;
}

