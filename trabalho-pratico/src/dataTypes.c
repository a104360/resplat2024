#include <stdbool.h>
#include "../include/dataTypes.h"


typedef struct time{
    int tm_sec;         /* seconds,  range 0 to 59          */
    int tm_min;         /* minutes, range 0 to 59           */
    int tm_hour;        /* hours, range 0 to 23             */
    int tm_mday;        /* day of the month, range 1 to 31  */
    int tm_mon;         /* month, range 0 to 11             */
    int tm_year;        /* The number of years since 0      */
} Time;



typedef struct user{
    char* id;
    char* name;
    char* email;
    unsigned int phone_number;
    struct time birth_date;
    bool sex;
    unsigned int passport;
    unsigned int country_code;
    char* address;
    struct time account_creation;
    unsigned int pay_method;
    bool account_status;
} User;

typedef struct flight{
    unsigned int id;
    char* airline;
    char* plane_model;
    unsigned int total_seats;
    char* origin;
    char* destination;
    struct time schedule_departure_date;
    struct time schedule_arrival_date;
    struct time real_departure_date;
    struct time real_arrival_date;
    char* pilot;
    char* copilot;
    char* notes;
} Flight;

typedef struct reservation{
    unsigned int id;
    unsigned int user_id;
    unsigned int hotel_id;
    char* hotel_name;
    unsigned int hotel_stars;
    double city_tax;
    char* address;
    struct time begin_date;
    struct time end_date;
    double price_per_night;
    bool includes_breakfast;
    char* room_details;                 //********substituir por uma struct******* 
    unsigned int rating;
    char* comment;
} Reservation;


typedef struct passanger{
    unsigned int flight_id;
    unsigned int user_id;
} Passanger;