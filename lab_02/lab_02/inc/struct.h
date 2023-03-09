#ifndef STRUCT_H

#define STRUCT_H
#define MAX_LEN 50

typedef struct
{
    int number_objects;
    char main_view[MAX_LEN];
} excursion_t;

typedef struct
{
    char season[MAX_LEN];
    int temperature_air;
    int temperature_water;
    int flight_time;
} beach_t;

typedef struct
{
    char view_sports[MAX_LEN];
    int minimum_cost;
} sports_t;

typedef struct
{
    char country[MAX_LEN];
    int count_people;
    char capital[MAX_LEN];
    char mainland[MAX_LEN];
    int PCR;
    int tourism;
    
    union
    {
        excursion_t excursion_holiday;
        beach_t beach_holiday;
        sports_t sports_holiday;        
    } holiday_kind_t;
    
} country_info_t;

typedef struct
{
    char country[50];
    int id;
} keys_t;

#endif
