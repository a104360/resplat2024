#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dataTypes.h"

enum structs {USER,FLIGHT,RESERVATION,PASSANGER};


typedef struct time{
    int sec;         /* seconds,  range 0 to 59          */
    int min;         /* minutes, range 0 to 59           */
    int hour;        /* hours, range 0 to 23             */
    int mday;        /* day of the month, range 1 to 31  */
    int mon;         /* month, range 0 to 11             */
    int year;        /* The number of years since 0      */
} Time;


typedef struct user{
    char * id;
    char * name;
    char * email;
    char * phone_number;
    struct time birth_date;
    char * sex;
    char * passport;
    char * country_code;
    char * address;
    struct time account_creation;
    char * pay_method;
    bool account_status;
} User;



typedef struct flight{
    char * id;
    char * airline;
    char * plane_model;
    unsigned int total_seats;
    char * origin;
    char * destination;
    struct time schedule_departure_date;
    struct time schedule_arrival_date;
    struct time real_departure_date;
    struct time real_arrival_date;
    char * pilot;
    char * copilot;
    char * notes;
} Flight;

typedef struct reservation{
    char * id;
    char * user_id;
    char * hotel_id;
    char * hotel_name;
    unsigned int hotel_stars;
    double city_tax;
    char * address;
    struct time begin_date;
    struct time end_date;
    double price_per_night;
    bool includes_breakfast;
    char * room_details;                 //********substituir por uma struct******* 
    unsigned int rating;
    char * comment;
} Reservation;


typedef struct passanger{
    char * flight_id;
    char * user_id;
} Passanger;



void initUser(User * user){
    user->id = NULL;
    user->name = NULL;
    user->email = NULL;
    user->phone_number = NULL;
    user->birth_date.hour = 0;
    user->birth_date.min = 0;
    user->birth_date.sec = 0;
    user->birth_date.mday = 0;
    user->birth_date.year = 0;
    user->birth_date.mon = 0;
    user->sex = NULL;
    user->passport = NULL;
    user->country_code = NULL;
    user->address = NULL;
    user->account_creation.hour = 0;
    user->account_creation.min = 0;
    user->account_creation.sec = 0;
    user->account_creation.mday = 0;
    user->account_creation.year = 0;
    user->account_creation.mon = 0;
    user->pay_method = NULL;
    user->account_status = false;
}

void initFlight(Flight * flight){
    flight->id = NULL;
    flight->airline = NULL;
    flight->plane_model = NULL;
    flight->total_seats = 0;
    flight->origin = NULL;
    flight->destination = NULL;
    flight->schedule_departure_date.hour = 0;
    flight->schedule_departure_date.min = 0;
    flight->schedule_departure_date.sec = 0;
    flight->schedule_departure_date.mday = 0;
    flight->schedule_departure_date.year = 0;
    flight->schedule_departure_date.mon = 0;
    flight->schedule_arrival_date.hour = 0;
    flight->schedule_arrival_date.min = 0;
    flight->schedule_arrival_date.sec = 0;
    flight->schedule_arrival_date.mday = 0;
    flight->schedule_arrival_date.year = 0;
    flight->schedule_arrival_date.mon = 0;
    flight->real_departure_date.hour = 0;
    flight->real_departure_date.min = 0;
    flight->real_departure_date.sec = 0;
    flight->real_departure_date.mday = 0;
    flight->real_departure_date.year = 0;
    flight->real_departure_date.mon = 0;
    flight->real_arrival_date.hour = 0;
    flight->real_arrival_date.min = 0;
    flight->real_arrival_date.sec = 0;
    flight->real_arrival_date.mday = 0;
    flight->real_arrival_date.year = 0;
    flight->real_arrival_date.mon = 0;
    flight->pilot = NULL;
    flight->copilot = NULL;
    flight->notes = NULL;
}

void initReservation(Reservation * reservation){
    reservation->id = NULL;
    reservation->user_id = NULL;
    reservation->hotel_id = NULL;
    reservation->hotel_name = NULL;
    reservation->hotel_stars = 0;
    reservation->city_tax = 0.0;
    reservation->address = NULL;
    reservation->begin_date.hour = 0;
    reservation->begin_date.min = 0;
    reservation->begin_date.sec = 0;
    reservation->begin_date.mday = 0;
    reservation->begin_date.year = 0;
    reservation->begin_date.mon = 0;
    reservation->end_date.hour = 0;
    reservation->end_date.min = 0;
    reservation->end_date.sec = 0;
    reservation->end_date.mday = 0;
    reservation->end_date.year = 0;
    reservation->end_date.mon = 0;
    reservation->price_per_night = 0.0;
    reservation->includes_breakfast = false;
    reservation->room_details = NULL;
    reservation->rating = 0;
    reservation->comment = NULL;
}

void initPassanger(Passanger * passanger){
    passanger->flight_id = NULL;
    passanger->user_id = NULL;
}




User * createUser(){
    User * u = malloc(sizeof(struct user));
    initUser(u);
    return u;
}

Flight * createFlight(){
    Flight * f = malloc(sizeof(struct flight));
    initFlight(f);
    return f;
}

Reservation * createReservation(){
    Reservation * r = malloc(sizeof(struct reservation));
    initReservation(r);
    return r;
}

Passanger * createPassanger(){
    Passanger * p = malloc(sizeof(struct passanger));
    initPassanger(p);
    return p;
}


void setUserId(User * user,char * id){
    if(user->id) free(user->id);
    user->id = strdup(id);
}
/*void setId(void * tipo,const char * id,enum structs type){
    switch (type)
    {
    case USER: // User 
        User * u = (User *) tipo;
        if(u->id) free(u->id);
        u->id = strdup(id);
        break;

    case FLIGHT: // Flight 
        Flight * f = (Flight *) tipo;
        if(f->id) free(f->id);
        f->id = strdup(id);
        break;

    case RESERVATION: // Reservation
        Reservation * r = (Reservation *) tipo;
        if(r->id) free(r->id);
        r->id = strdup(id);
        break;
    }
}*/

void setUserName(User * user, char * name){
    if(user->name) free(user->name);
    user->name = strdup(name);
}

void setUserEmail(User * user,char * email){
    if(user->email) free(user->email);
    user->email = strdup(email);
}

void setUserBday(User * user ,Time * tempo){
    user->birth_date = *tempo;
}

void setUserSex(User * user ,char * sexo){
    if(user->sex) free(user->sex);
    user->sex = strdup(sexo);
}

void setUserPassport(User * user ,char * line){
    if(user->passport) free(user->passport);
    user->passport = strdup(line);
}

void setUserCountryCode(User * user ,char * line){
    if(user->country_code) free(user->country_code);
    user->country_code = strdup(line);
}

void setUserAddress(User * user ,char * line){
    if(user->address) free(user->address);
    user->address = strdup(line);
}

void setUserAccountCreation(User * user ,Time *tempo){
    user->account_creation = *tempo;
}

void setUserPayMethod(User * user ,char * line){
    
}

void setUserAccountStatus(User * user ,bool);