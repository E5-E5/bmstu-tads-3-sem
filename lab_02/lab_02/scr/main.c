#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/struct.h"
#include "../inc/search.h"
#include "../inc/sort.h"
#include "../inc/file.h"

void print_menu()
{
    puts("\n     Пункты программы:\n");
    puts("1. Загрузить список стран из файла");
    puts("2. Добавить страну в список");
    puts("3. Удалить информацию о стране по самой стране");
    puts("4. Удалить информацию о стране по ее номеру в списке");
    puts("5. Найти все страны по указанному материку и виду спорта");
    puts("6. Отсортировать таблицу пузырьком по странам");
    puts("7. Отсортировать таблицу ключей пузырьком по странам");
    puts("8. Отсортировать таблицу qsort по странам");
    puts("9. Отсортировать таблицу ключей qsort по странам");
    puts("10. Вывести сравнение сортировок пузырьком и qsort");
    puts("11. Вывести таблицу");
    puts("12. Вывести таблицу ключей");
    puts("13. Вывести отсортированную таблицу по таблице ключей");
    puts("14. Очистить таблицу");
    puts("0. Выйти из программы\n");

    printf("Введите желаемый пункт меню: ");
}

int main(void)
{
    country_info_t country_info[100];
    int size = 0, number, rc;
    keys_t keys[100];
    
    print_menu();    
    while ((scanf("%d", &number) == 1) && number != 0)
    {
        if (number == 1)
        {
            FILE *file;
            char name_file[15];
            
            puts("Введите имя файла:");
            
            if (!scanf("%s", name_file))
            {
                puts("Ошибка: Неверно указано имя файла");
                return 1;
            }
            
            file = fopen(name_file, "r");
    		if (!file)
    		{
    			puts("Ошибка: Такого файла не существует");
    			return 1;
    		}
    		
            rc = read_file(file, country_info, &size);
		    fclose(file);
		    
            if (rc)
                return rc;
                
            puts("Список был успешно прочитан");
            for (int i = 0; i < size ; i++)
		    {
		        strncpy(keys[i].country, country_info[i].country, 50);
		        keys[i].id = i;
		    }
        }        
        else if (number == 2)
        {
            rc = add_country(country_info, &size);

            if (rc)
                return rc;
            for (int i = 0; i < size ; i++)
	        {
	            strncpy(keys[i].country, country_info[i].country, 50);
	            keys[i].id = i;
	        }
        }        
        else if (number == 3)
        {
            rc = delete_by_country(country_info, &size);

            if (rc != 0)
                return rc;
            for (int i = 0; i < size ; i++)
	        {
	            strncpy(keys[i].country, country_info[i].country, 50);
	            keys[i].id = i;
	        }
        }        
        else if (number == 4)
        {
            puts("Введите инедкс страны, информация о которой будет удалена:");
            int index;
            int rc = scanf("%d", &index);

            if ((rc != 1) || (index < 1) || (index > size))
            {
                puts("Ошибка: неверно введен индекс");
                return 1;
            }
            del_by_pos(country_info, size, index - 1);
            size--;
            puts("Страна была успешно удалена");
            for (int i = 0; i < size ; i++)
	        {
	            strncpy(keys[i].country, country_info[i].country, 50);
	            keys[i].id = i;
	        }
        } 
        else if (number == 5)
            search(country_info, size); 
        else if (number == 6)
        {
            int rc = bubble_sort_country(country_info, size);
            if (!rc)
                puts("\n Таблица успешно отсортированна \n");
            for (int i = 0; i < size ; i++)
            {
                strncpy(keys[i].country, country_info[i].country, 50);
                keys[i].id = i;
            }
        }
        else if (number == 7)
        {
            int rc = bubble_sort_keys(keys, size);
            if (!rc)
                puts("\n Таблица успешно отсортированна \n");
        }
        else if (number == 8)
        {
            qsort_table(country_info, size);
            for (int i = 0; i < size ; i++)
	        {
	            strncpy(keys[i].country, country_info[i].country, 50);
	            keys[i].id = i;
	        }
	    }
        else if (number == 9)
        {
            qsort_table_keys(keys, size);
        }
        else if (number == 10)
        {
            FILE *file;
            char name_file[15];
            
            puts("Введите имя файла:");
            
            if (!scanf("%s", name_file))
            {
                puts("Ошибка: Неверно указано имя файла");
                return 1;
            }
            
            file = fopen(name_file, "r");
    		if (!file)
    		{
    			puts("Ошибка: Такого файла не существует");
    			return 1;
    		}
            rc = compare_sorts(file);
		    fclose(file);
		    
            if (rc != 0)
                return rc;
        }     
        else if (number == 11)
        {
            if (size == 0)
                puts("Таблица пустая");
            else
            {
            	print_table();
                for (int i = 0; i < size; i++)
                    print_string(country_info[i], i);
                puts("------------------------------------------------------------------------------------------------------------------------------------------------------");
            }
        }   
        else if (number == 12)
        {
            if (size == 0)
                puts("Таблица пустая");
            else
            {
            	print_table_key();
                for (int i = 0; i < size; i++)
                    print_string_key(keys[i]);
                    puts("--------------------");
            }
        }       
        else if (number == 13)
        {
            if (size == 0)
                puts("Таблица пустая");
            else
                print_key_table(country_info, keys, size);
        }  
        else if (number == 14)
        {
            size = 0;
            puts("Таблица успешно очищена");
        }       
        else
            return 1;
            
        print_menu();
    }
    
    return 0;
}

