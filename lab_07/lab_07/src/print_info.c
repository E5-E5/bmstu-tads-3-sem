#include"../inc/print_info.h"


void flush_input(void)
{
    char c;
    while((scanf("%c", &c) == 1) && (c != '\n'))
        ;
}


void print_menu(void)
{
    puts("\n\n      Меню   \
    \n1. Ввести данные из файла \
    \n2. Вывести двоичное дерево поиска \
    \n3. Вывести АВЛ дерево \
    \n4. Вывести ХЕШ таблицу \
    \n5. Добавить элемент в ДДП, АВЛ, ХЕШ таблицу и файл \
    \n6. Найти элемент в ДДП, АВЛ, ХЕШ-таблице \
    \n0. Выйти из программы");

    printf("\nВведите пункт меню: ");
}