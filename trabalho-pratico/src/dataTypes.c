#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dataTypes.h"


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
    struct time * birth_date;
    char * sex;
    char * passport;
    char * country_code;
    char * address;
    struct time * account_creation;
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
    struct time * schedule_departure_date;
    struct time * schedule_arrival_date;
    struct time * real_departure_date;
    struct time * real_arrival_date;
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
    struct time * begin_date;
    struct time * end_date;
    double price_per_night;
    bool includes_breakfast;
    char * room_details;                  
    unsigned int rating;
    char * comment;
} Reservation;


typedef struct passanger{
    char * flight_id;
    char * user_id;
} Passanger;




// *** Time related functions ***

static void initTime(Time * tempo){
    tempo->hour = 0;
    tempo->min = 0;
    tempo->sec = 0;
    tempo->mday = 0;
    tempo->year = 0;
    tempo->mon = 0;
}

static void destroyTime(Time *time) {
    time->hour = 0;
    time->min = 0;
    time->sec = 0;
    time->mday = 0;
    time->year = 0;
    time->mon = 0;
    free(time);
}

static Time * createTime(){
    Time * t = malloc(sizeof(struct time));
    initTime(t);
    return t;
}

static void setTime(Time * t,Time * aux){
    t->year = aux->year;
    t->mday = aux->mday;
    t->mon = aux->mon;
    t->hour = aux->hour;
    t->min = aux->min;
    t->sec = aux->sec;
}






// *** User Related Functions ***


static User * createUser(){
    User * u = malloc(sizeof(struct user));
    initUser(u);    
    return u;

}

static void initUser(User * user){
    user->id = NULL;
    user->name = NULL;
    user->email = NULL;
    user->phone_number = NULL;
    user->birth_date->hour = 0;
    user->birth_date->min = 0;
    user->birth_date->sec = 0;
    user->birth_date->mday = 0;
    user->birth_date->year = 0;
    user->birth_date->mon = 0;
    user->sex = NULL;
    user->passport = NULL;
    user->country_code = NULL;
    user->address = NULL;
    user->account_creation->hour = 0;
    user->account_creation->min = 0;
    user->account_creation->sec = 0;
    user->account_creation->mday = 0;
    user->account_creation->year = 0;
    user->account_creation->mon = 0;
    user->pay_method = NULL;
    user->account_status = false;
}

static void destroyUser(User *user) {
    if(user) {
        free(user->id);
        free(user->name);
        free(user->email);
        free(user->phone_number);
        free(user->sex);
        free(user->passport);
        free(user->country_code);
        free(user->address);
        free(user->pay_method);
        destroyTime(user->account_creation);
        destroyTime(user->birth_date);
        free(user);
    }
}



static void setUserId(User * user,const char * id){
    if(user->id) free(user->id);
    user->id = strdup(id);
}

static char * getUserId(User * user){
    if(user->id){
        char * aux = strdup(user->id);
        return aux;
    }
    return NULL;
}


static void setUserName(User * user,const char * name){
    if(user->name) free(user->name);
    user->name = strdup(name);
}

static char * getUserName(User * user){
     if(user->name){
        char * aux = strdup(user->name);
        return aux;
    }
    return NULL;
}


static void setUserEmail(User * user,const char * email){
    if(user->email) free(user->email);
    user->email = strdup(email);
}

static char * getUserEmail(User * user){
    if(user->email){
        char * aux = strdup(user->email);
        return aux;
    }
    return NULL;
}


static void setUserBday(User * user ,Time * tempo){
    if(!user->birth_date) user->birth_date = createTime();
    setTime(user->birth_date,tempo);
}

static Time * getUserBday(User * user){
    if(user->birth_date){
        Time * aux = createTime();
        setTime(aux,user->birth_date);
        return aux;
    }
    return NULL;
}


static void setUserSex(User * user ,const char * sexo){
    if(user->sex) free(user->sex);
    user->sex = strdup(sexo);
}

static char * getUserSex(User * user){
     if(user->sex){
        char * aux = strdup(user->sex);
        return aux;
    }
    return NULL;
}


static void setUserPassport(User * user ,const char * line){
    if(user->passport) free(user->passport);
    user->passport = strdup(line);
}

static char * getUserPassaport(User * user){
    if(user->passport){
        char * aux = strdup(user->passport);
        return aux;
    }
    return NULL;
}


static void setUserCountryCode(User * user ,const char * line){
    if(user->country_code) free(user->country_code);
    user->country_code = strdup(line);
}

static char * getUserCountryCode(User * user){
    if(user->country_code){
        char * aux = strdup(user->country_code);
        return aux;
    }
    return NULL;
}


static void setUserAddress(User * user ,const char * line){
    if(user->address) free(user->address);
    user->address = strdup(line);
}

static char * getUserAddress(User * user){
    if(user->address){
        char * aux = strdup(user->address);
        return aux;
    }
    return NULL;
}


static void setUserAccountCreation(User * user ,Time *tempo){
    if(!user->account_creation) user->account_creation = createTime();
    setTime(user->account_creation,tempo);
}

static Time * getUserAccountCreation(User * user){
    if(user->account_creation){
        Time * t = createTime();
        setTime(t,user->account_creation);
        return t;
    }
    return NULL;
}


static void setUserPayMethod(User * user ,const char * line){
    if(user->pay_method) free(user->pay_method);
    user->pay_method = strdup(line);
}

static char * getUserPayMethod(User * user){
    if(user->pay_method){
        char * aux = strdup(user->pay_method);
        return aux;
    }
    return NULL;
}


static void setUserAccountStatus(User * user ,const bool status){
    user->account_status = status;

}

static bool getUserAccountStatus(User * user){
    if(user){
        return user->account_status;
    }
} 














// *** Flight related functions ***

static Flight * createFlight(){
    Flight * f = malloc(sizeof(struct flight));
    initFlight(f);
    return f;
}

static void initFlight(Flight * flight){
    flight->id = NULL;
    flight->airline = NULL;
    flight->plane_model = NULL;
    flight->total_seats = 0;
    flight->origin = NULL;
    flight->destination = NULL;
    flight->schedule_departure_date->hour = 0;
    flight->schedule_departure_date->min = 0;
    flight->schedule_departure_date->sec = 0;
    flight->schedule_departure_date->mday = 0;
    flight->schedule_departure_date->year = 0;
    flight->schedule_departure_date->mon = 0;
    flight->schedule_arrival_date->hour = 0;
    flight->schedule_arrival_date->min = 0;
    flight->schedule_arrival_date->sec = 0;
    flight->schedule_arrival_date->mday = 0;
    flight->schedule_arrival_date->year = 0;
    flight->schedule_arrival_date->mon = 0;
    flight->real_departure_date->hour = 0;
    flight->real_departure_date->min = 0;
    flight->real_departure_date->sec = 0;
    flight->real_departure_date->mday = 0;
    flight->real_departure_date->year = 0;
    flight->real_departure_date->mon = 0;
    flight->real_arrival_date->hour = 0;
    flight->real_arrival_date->min = 0;
    flight->real_arrival_date->sec = 0;
    flight->real_arrival_date->mday = 0;
    flight->real_arrival_date->year = 0;
    flight->real_arrival_date->mon = 0;
    flight->pilot = NULL;
    flight->copilot = NULL;
    flight->notes = NULL;
}

static void destroyFlight(Flight * f) {
    if (f != NULL) {
        free(f->id); 
        free(f->airline); 
        free(f->plane_model); 
        free(f->origin); 
        free(f->destination); 
        destroyTime(f->schedule_departure_date); 
        destroyTime(f->schedule_arrival_date); 
        destroyTime(f->real_departure_date); 
        destroyTime(f->real_arrival_date); 
        free(f->pilot); 
        free(f->copilot); 
        free(f->notes); 
        free(f); 
    }
}



static void setFlightId(Flight * flight,const char * line){
    if(flight->id) free(flight->id);
    flight->id = strdup(line);
}

static char *getFlightId(Flight * flight){
    if(flight->id){
        char * id = strdup(flight->id);
        return id;
    }
    return NULL;
}

  
static void setFlightAirline(Flight * flight,const char * line){
    if(flight->airline) free(flight->airline);
    flight->airline = strdup(line);
}

static char *getFlightAirline(Flight * flight){
    if(flight->airline){
        char * airline = strdup(flight->airline);
        return airline;
    }
    return NULL;
}


static void setFlightPlaneModel(Flight * flight,const char * line){
    if(flight->plane_model) free(flight->plane_model);
    flight->plane_model = strdup(line);
}

static char *getFlightPlaneModel(Flight * flight){
    if(flight->plane_model){
        char * plane_model = strdup(flight->plane_model);
        return plane_model;
    }
    return NULL;
}


static void setFlightTotalSeats(Flight * flight,const unsigned int n){
    flight->total_seats = n;
}

static unsigned int getFlightTotalSeats(Flight * flight){
    return flight->total_seats;
}


static void setFlightOrigin(Flight * flight,const char * line){
    if(flight->origin) free(flight->origin);
    flight->origin = strdup(line);
}

static char *getFlightOrigin(Flight * flight){
    if(flight->origin){
        char * origin = strdup(flight->origin);
        return origin;
    }
    return NULL;
}


static void setFlightDestination(Flight * flight,const char * line){
    if(flight->destination) free(flight->destination);
    flight->destination = strdup(line);
}

static char *getFlightDestination(Flight * flight){
    if(flight->destination){
        char * destination = strdup(flight->destination);
        return destination;
    }
    return NULL;
}


static void setFlightSDepartureDate(Flight * flight,Time * tempo){
    if(!flight->schedule_departure_date) flight->schedule_departure_date = createTime();
    setTime(flight->schedule_departure_date,tempo);
}

static Time *getFlightSDepartureDate(Flight * flight){
    if(flight->schedule_departure_date){
        Time * tempo = createTime();
        setTime(tempo,flight->schedule_departure_date);
        return tempo;
    }
    return NULL;
}


static void setFlightSArrivalDate(Flight * flight,Time * tempo){
    if(!flight->schedule_arrival_date) flight->schedule_arrival_date = createTime();
    setTime(flight->schedule_arrival_date,tempo);
}

static Time *getFlightSArrivalDate(Flight * flight){
    if(flight->schedule_arrival_date){
        Time * tempo = createTime();
        setTime(tempo,flight->schedule_arrival_date);
        return tempo;
    }
    return NULL;
}


static void setFlightRDepartureDate(Flight * flight, Time * tempo){
    if(!flight->real_departure_date) flight->real_departure_date = createTime();
    setTime(flight->real_departure_date,tempo);
}

static Time *getFlightRDepartureDate(Flight * flight){
    if(flight->real_departure_date){
        Time * tempo = createTime();
        setTime(tempo,flight->real_departure_date);
        return tempo;
    }
    return NULL;
}


static void setFlightRArrivalDate(Flight * flight,Time * tempo){
    if(!flight->real_arrival_date) flight->real_arrival_date = createTime();
    setTime(flight->real_arrival_date,tempo);
}

static Time *getFlightRArrivalDate(Flight * flight){
    if(flight->real_arrival_date){
        Time * tempo = createTime();
        setTime(tempo,flight->real_arrival_date);
        return tempo;
    }
    return NULL;
}


static void setFlightPilot(Flight * flight,const char * line){
    if(flight->pilot) free(flight->pilot);
    flight->pilot = strdup(line);
}

static char *getFlightPilot(Flight * flight){
    if(flight->pilot){
        char * pilot = strdup(flight->pilot);
        return pilot;
    }
    return NULL;
}


static void setFlightCopilot(Flight * flight,const char * line){
    if(flight->copilot) free(flight->copilot);
    flight->copilot = strdup(line);
}

static char *getFlightCopilot(Flight * flight){
    if(flight->copilot){
        char * copilot = strdup(flight->copilot);
        return copilot;
    }
    return NULL;
}


static void setFlightNotes(Flight * flight,const char * line){
    if(flight->notes) free(flight->notes);
    flight->notes = strdup(line);
}

static char *getFlightNotes(Flight * flight){
    if(flight->notes){
        char * notes = strdup(flight->notes);
        return notes;
    }
    return NULL;
}










// *** Reservation related functions ***
static Reservation * createReservation(){
    Reservation * r = malloc(sizeof(struct reservation));
    initReservation(r);
    return r;
}

static void initReservation(Reservation * reservation){
    reservation->id = NULL;
    reservation->user_id = NULL;
    reservation->hotel_id = NULL;
    reservation->hotel_name = NULL;
    reservation->hotel_stars = 0;
    reservation->city_tax = 0.0;
    reservation->address = NULL;
    reservation->begin_date->hour = 0;
    reservation->begin_date->min = 0;
    reservation->begin_date->sec = 0;
    reservation->begin_date->mday = 0;
    reservation->begin_date->year = 0;
    reservation->begin_date->mon = 0;
    reservation->end_date->hour = 0;
    reservation->end_date->min = 0;
    reservation->end_date->sec = 0;
    reservation->end_date->mday = 0;
    reservation->end_date->year = 0;
    reservation->end_date->mon = 0;
    reservation->price_per_night = 0.0;
    reservation->includes_breakfast = false;
    reservation->room_details = NULL;
    reservation->rating = 0;
    reservation->comment = NULL;
}

static void destroyReservation(Reservation * r) {
    if (r != NULL) {
        free(r->id); 
        free(r->user_id); 
        free(r->hotel_id); 
        free(r->hotel_name); 
        free(r->address); 
        destroyTime(r->begin_date); 
        destroyTime(r->end_date); 
        free(r->room_details); 
        free(r->comment); 
        free(r); 
    }
}


static void setReservId(Reservation * reserv,const char * line){
    if(reserv->id) free(reserv->id);
    reserv->id = strdup(line);
}

static char *getReservId(Reservation * reserv){
    if(reserv->id){
        char * id = strdup(reserv->id);
        return id;
    }
    return NULL;
}


static void setReservUserId(Reservation * reserv,const char * line){
    if(reserv->user_id) free(reserv->user_id);
    reserv->user_id = strdup(line);
}

static char *getReservUserId(Reservation * reserv){
     if(reserv->user_id){
        char * user_id = strdup(reserv->user_id);
        return user_id;
    }
    return NULL;
}


static void setReservHotelId(Reservation * reserv,const char * line){
    if(reserv->hotel_id) free(reserv->hotel_id);
    reserv->hotel_id = strdup(line);
}

static char *getReservHotelId(Reservation * reserv){
     if(reserv->hotel_id){
        char * hotel_id = strdup(reserv->hotel_id);
        return hotel_id;
    }
    return NULL;
}


static void setReservHotelName(Reservation * reserv,const char * line){
    if(reserv->hotel_name) free(reserv->hotel_name);
    reserv->hotel_name = strdup(line);
}

static char *getReservHotelName(Reservation * reserv){
     if(reserv->hotel_name){
        char * hotel_name = strdup(reserv->hotel_name);
        return hotel_name;
    }
    return NULL;
}


static void setReservHotelStars(Reservation * reserv,const unsigned int n){
    reserv->hotel_stars = n;
}

static unsigned int getReservHotelStars(Reservation * reserv){
    return reserv->hotel_stars;
}


static void setReservCityTax(Reservation * reserv,const double n){
    reserv->city_tax = n;
}

static double getReservCityTax(Reservation * reserv){
    return reserv->city_tax;
}


static void setReservHotelAddress(Reservation * reserv,const char * line){
    if(reserv->address) free(reserv->address);
    reserv->address = strdup(line);
}

static char *getReservHotelAddress(Reservation * reserv){
    if(reserv->address){
        char * address = strdup(reserv->address);
        return address;
    }
    return NULL;
}


static void setReservBeginDate(Reservation * reserv,Time * tempo){
    if(!reserv->begin_date) reserv->begin_date = createTime();
    setTime(reserv->begin_date,tempo);
}

static Time * getReservBeginDate(Reservation * reserv){
    if(reserv->begin_date){
        Time * tempo = createTime();
        setTime(tempo,reserv->begin_date);
        return tempo;
    }
    return NULL;
}


static void setReservEndDate(Reservation * reserv,Time * tempo){
    if(!reserv->end_date) reserv->end_date = createTime();
    setTime(reserv->end_date,tempo);
}

static Time *getReservEndDate(Reservation * reserv){
    if(reserv->end_date){
        Time * tempo = createTime();
        setTime(tempo,reserv->end_date);
        return tempo;
    }
    return NULL;
}


static void setReservPricePerNight(Reservation * reserv,const double n){
    reserv->price_per_night = n;
}

static double getReservPricePerNight(Reservation * reserv){
    return reserv->price_per_night;
}


static void setReservBreakfast(Reservation * reserv,const bool x){
    reserv->includes_breakfast = x;
}

static bool getReservBreakfast(Reservation * reserv){
    return reserv->includes_breakfast;
}


static void setReservRoomDetails(Reservation * reserv,const char * line){
    if(reserv->room_details) free(reserv->room_details);
    reserv->room_details = strdup(line);
}

static char *getReservRoomDetails(Reservation * reserv){
    if(reserv->room_details){
        char * room_details = strdup(reserv->room_details);
        return room_details;
    }
    return NULL;
}


static void setReservRating(Reservation * reserv,const unsigned int n){
    reserv->rating = n;
}

static unsigned int getReservRating(Reservation * reserv){
    return reserv->rating;
}


static void setReservComment(Reservation * reserv,const char * line){
    if(reserv->comment) free(reserv->comment);
    reserv->comment = strdup(line);
}

static char *getReservComment(Reservation * reserv){
    if(reserv->comment){
        char * comment = strdup(reserv->comment);
        return comment;
    }
    return NULL;
}



// *** Passanger related functions *** 

static Passanger * createPassanger(){
    Passanger * p = malloc(sizeof(struct passanger));
    initPassanger(p);
    return p;
}

static void initPassanger(Passanger * passanger){
    passanger->flight_id = NULL;
    passanger->user_id = NULL;
}

static void destroyPassanger(Passanger * p) {
    if (p != NULL) {
        free(p->flight_id); 
        free(p->user_id); 
        free(p); 
    }
}

static void setPassangerFlightId(Passanger * passanger,const char * line){
    if(passanger->flight_id) free(passanger->flight_id);
    passanger->flight_id = strdup(line);
}

static char *getPassangerFlightId(Passanger * passanger){
    if(passanger->flight_id){
        char * flight_id = strdup(passanger->flight_id);
        return flight_id;
    }
    return NULL;
}


static void setPassangerUserId(Passanger * passanger,const char * line){
    if(passanger->user_id) free(passanger->user_id);
    passanger->user_id = strdup(line);
}

static char *getPassangerUserId(Passanger * passanger){
    if(passanger->user_id){
        char * user_id = strdup(passanger->user_id);
        return user_id;
    }
}

