#include <time.h>
#include <stdbool.h>


typedef struct user{
    unsigned int id;
    char* name;
    char* email;
    unsigned int phone_number;
    struct tm birth_date; //ponderar time_t is
    bool sex;
    unsigned int passport;
    unsigned int country_code;
    char* address;
    struct tm account_creation;
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
    struct tm schedule_departure_date;
    struct tm schedule_arrival_date;
    struct tm real_departure_date;
    struct tm real_arrival_date;
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
    struct tm begin_date;
    struct tm end_date;
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