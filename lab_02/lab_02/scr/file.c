#include <stdlib.h>
#include <stdio.h>

#include "../inc/file.h"
#include "../inc/struct.h"

int read_file(FILE *file, country_info_t *array, int *size)
{
    size_t temp_size = 0;
    
    while (fscanf(file, "%s%d%s%s%d%d", array[temp_size].country, &array[temp_size].count_people, array[temp_size].capital,
            array[temp_size].mainland, &array[temp_size].PCR, &array[temp_size].tourism) == 6)
    {
        if (array[temp_size].tourism == 1)
            if (fscanf(file, "%d%s\n", &array[temp_size].holiday_kind_t.excursion_holiday.number_objects,
                    array[temp_size].holiday_kind_t.excursion_holiday.main_view) != 2)
                return EXIT_FAILURE;
                
        if (array[temp_size].tourism == 2)
            if (fscanf(file, "%s%d%d%d\n", array[temp_size].holiday_kind_t.beach_holiday.season, &array[temp_size].holiday_kind_t.beach_holiday.temperature_air,
                    &array[temp_size].holiday_kind_t.beach_holiday.temperature_water, &array[temp_size].holiday_kind_t.beach_holiday.flight_time) != 4)
                return EXIT_FAILURE;
        
        if (array[temp_size].tourism == 3)
            if (fscanf(file, "%s%d\n", array[temp_size].holiday_kind_t.sports_holiday.view_sports,
                    &array[temp_size].holiday_kind_t.sports_holiday.minimum_cost) != 2)
                return EXIT_FAILURE;
                
        temp_size++;
        
        if (temp_size == 99)
      	    return 1;
    }
    
    *size = temp_size;
    
    return EXIT_SUCCESS;
}
