#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dataTypes.h"
#include "../include/catalogs.h"
#include "../include/utils.h"
#include <glib.h>


typedef struct time{
    int sec;         /* seconds,  range 0 to 59          */
    int min;         /* minutes, range 0 to 59           */
    int hour;        /* hours, range 0 to 23             */
    int mday;        /* day of the month, range 1 to 31  */
    int mon;         /* month, range 0 to 11             */
    int year;        /* The number of years since 0      */
} ;


typedef struct user{
    char * id;
    char * name;
    char * email;
    char * phone_number;
    struct time * birth_date;
    char sex;
    char * passport;
    char * country_code;
    char * address;
    struct time * account_creation;
    char * pay_method;
    bool account_status;
} ;



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
} ;

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
} ;


typedef struct passanger{
    char * flight_id;
    char * user_id;
} ;




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
    initTime(time);
    g_free(time);
}

static Time * createTime(){
    Time * t = g_malloc(sizeof(struct time));
    initTime(t);
    return t;
}

static void setTime(Time *t,int year,int mon,int mday,int hour,int min,int sec){
    t->year = year;
    t->mon = mon;
    t->mday = mday;
    t->hour = hour;
    t->min = min;
    t->sec = sec;
}

static void copyTime(Time * t,Time * aux){
    t->year = aux->year;
    t->mday = aux->mday;
    t->mon = aux->mon;
    t->hour = aux->hour;
    t->min = aux->min;
    t->sec = aux->sec;
}






// *** User Related Functions ***


static User * createUser(){
    User * u = g_malloc(sizeof(struct user));
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
        if(user->id) g_free(user->id);
        if(user->name) g_free(user->name);
        if(user->email) g_free(user->email);
        if(user->phone_number) g_free(user->phone_number);
        if(user->sex) g_free(user->sex);
        if(user->passport) g_free(user->passport);
        if(user->country_code) g_free(user->country_code);
        if(user->address) g_free(user->address);
        if(user->pay_method) g_free(user->pay_method);
        if(user->account_creation) destroyTime(user->account_creation);
        if(user->birth_date) destroyTime(user->birth_date);
        g_free(user);
    }
}



static void setUserId(User * user,const char * id){
    if(user->id) g_free(user->id);
    user->id = g_strdup(id);
}

static char * getUserId(User * user){
    if(user->id){
        char * aux = g_strdup(user->id);
        return aux;
    }
    return NULL;
}


static void setUserName(User * user,const char * name){
    if(user->name) g_free(user->name);
    user->name = g_strdup(name);
}

static char * getUserName(User * user){
     if(user->name){
        char * aux = g_strdup(user->name);
        return aux;
    }
    return NULL;
}


static void setUserEmail(User * user,const char * email){
    if(user->email) g_free(user->email);
    user->email = g_strdup(email);
}

static char * getUserEmail(User * user){
    if(user->email){
        char * aux = g_strdup(user->email);
        return aux;
    }
    return NULL;
}

static void setUserPhone(User * user,const char * line){
    if(user->phone_number) g_free(user->phone_number);
    user->phone_number = g_strdup(line);
}
static char * getUserPhone(User * user){
    if(user->phone_number){
        char * aux = g_strdup(user->phone_number);
        return aux;
    }
    return NULL;
}



static void setUserBday(User * user ,Time * tempo){
    if(!user->birth_date) user->birth_date = createTime();
    copyTime(user->birth_date,tempo);
}

static Time * getUserBday(User * user){
    if(user->birth_date){
        Time * aux = createTime();
        copyTime(aux,user->birth_date);
        return aux;
    }
    return NULL;
}


static void setUserSex(User * user ,const char line){
    user->sex = line;
}

static char getUserSex(User * user){
    return user->sex;
}


static void setUserPassport(User * user ,const char * line){
    if(user->passport) g_free(user->passport);
    user->passport = g_strdup(line);
}

static char * getUserPassaport(User * user){
    if(user->passport){
        char * aux = g_strdup(user->passport);
        return aux;
    }
    return NULL;
}


static void setUserCountryCode(User * user ,const char * line){
    if(user->country_code) g_free(user->country_code);
    user->country_code = g_strdup(line);
}

static char * getUserCountryCode(User * user){
    if(user->country_code){
        char * aux = g_strdup(user->country_code);
        return aux;
    }
    return NULL;
}


static void setUserAddress(User * user ,const char * line){
    if(user->address) g_free(user->address);
    user->address = g_strdup(line);
}

static char * getUserAddress(User * user){
    if(user->address){
        char * aux = g_strdup(user->address);
        return aux;
    }
    return NULL;
}


static void setUserAccountCreation(User * user ,Time *tempo){
    if(!user->account_creation) user->account_creation = createTime();
    copyTime(user->account_creation,tempo);
}

static Time * getUserAccountCreation(User * user){
    if(user->account_creation){
        Time * t = createTime();
        copyTime(t,user->account_creation);
        return t;
    }
    return NULL;
}


static void setUserPayMethod(User * user ,const char * line){
    if(user->pay_method) g_free(user->pay_method);
    user->pay_method = g_strdup(line);
}

static char * getUserPayMethod(User * user){
    if(user->pay_method){
        char * aux = g_strdup(user->pay_method);
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
    Flight * f = g_malloc(sizeof(struct flight));
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
        if(f->id) g_free(f->id); 
        if(f->airline) g_free(f->airline); 
        if(f->plane_model) g_free(f->plane_model); 
        if(f->origin) g_free(f->origin); 
        if(f->destination) g_free(f->destination); 
        if(f->schedule_departure_date) destroyTime(f->schedule_departure_date); 
        if(f->schedule_arrival_date) destroyTime(f->schedule_arrival_date); 
        if(f->real_departure_date) destroyTime(f->real_departure_date); 
        if(f->real_arrival_date) destroyTime(f->real_arrival_date); 
        if(f->pilot) g_free(f->pilot); 
        if(f->copilot) g_free(f->copilot); 
        if(f->notes) g_free(f->notes); 
        g_free(f); 
    }
}



static void setFlightId(Flight * flight,const char * line){
    if(flight->id) g_free(flight->id);
    flight->id = g_strdup(line);
}

static char *getFlightId(Flight * flight){
    if(flight->id){
        char * id = g_strdup(flight->id);
        return id;
    }
    return NULL;
}

  
static void setFlightAirline(Flight * flight,const char * line){
    if(flight->airline) g_free(flight->airline);
    flight->airline = g_strdup(line);
}

static char *getFlightAirline(Flight * flight){
    if(flight->airline){
        char * airline = g_strdup(flight->airline);
        return airline;
    }
    return NULL;
}


static void setFlightPlaneModel(Flight * flight,const char * line){
    if(flight->plane_model) g_free(flight->plane_model);
    flight->plane_model = g_strdup(line);
}

static char *getFlightPlaneModel(Flight * flight){
    if(flight->plane_model){
        char * plane_model = g_strdup(flight->plane_model);
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
    if(flight->origin) g_free(flight->origin);
    flight->origin = g_strdup(line);
}

static char *getFlightOrigin(Flight * flight){
    if(flight->origin){
        char * origin = g_strdup(flight->origin);
        return origin;
    }
    return NULL;
}


static void setFlightDestination(Flight * flight,const char * line){
    if(flight->destination) g_free(flight->destination);
    flight->destination = g_strdup(line);
}

static char *getFlightDestination(Flight * flight){
    if(flight->destination){
        char * destination = g_strdup(flight->destination);
        return destination;
    }
    return NULL;
}


static void setFlightSDepartureDate(Flight * flight,Time * tempo){
    if(!flight->schedule_departure_date) flight->schedule_departure_date = createTime();
    copyTime(flight->schedule_departure_date,tempo);
}

static Time *getFlightSDepartureDate(Flight * flight){
    if(flight->schedule_departure_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->schedule_departure_date);
        return tempo;
    }
    return NULL;
}


static void setFlightSArrivalDate(Flight * flight,Time * tempo){
    if(!flight->schedule_arrival_date) flight->schedule_arrival_date = createTime();
    copyTime(flight->schedule_arrival_date,tempo);
}

static Time *getFlightSArrivalDate(Flight * flight){
    if(flight->schedule_arrival_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->schedule_arrival_date);
        return tempo;
    }
    return NULL;
}


static void setFlightRDepartureDate(Flight * flight, Time * tempo){
    if(!flight->real_departure_date) flight->real_departure_date = createTime();
    copyTime(flight->real_departure_date,tempo);
}

static Time *getFlightRDepartureDate(Flight * flight){
    if(flight->real_departure_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->real_departure_date);
        return tempo;
    }
    return NULL;
}


static void setFlightRArrivalDate(Flight * flight,Time * tempo){
    if(!flight->real_arrival_date) flight->real_arrival_date = createTime();
    copyTime(flight->real_arrival_date,tempo);
}

static Time *getFlightRArrivalDate(Flight * flight){
    if(flight->real_arrival_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->real_arrival_date);
        return tempo;
    }
    return NULL;
}


static void setFlightPilot(Flight * flight,const char * line){
    if(flight->pilot) g_free(flight->pilot);
    flight->pilot = g_strdup(line);
}

static char *getFlightPilot(Flight * flight){
    if(flight->pilot){
        char * pilot = g_strdup(flight->pilot);
        return pilot;
    }
    return NULL;
}


static void setFlightCopilot(Flight * flight,const char * line){
    if(flight->copilot) g_free(flight->copilot);
    flight->copilot = g_strdup(line);
}

static char *getFlightCopilot(Flight * flight){
    if(flight->copilot){
        char * copilot = g_strdup(flight->copilot);
        return copilot;
    }
    return NULL;
}


static void setFlightNotes(Flight * flight,const char * line){
    if(flight->notes) g_free(flight->notes);
    flight->notes = g_strdup(line);
}

static char *getFlightNotes(Flight * flight){
    if(flight->notes){
        char * notes = g_strdup(flight->notes);
        return notes;
    }
    return NULL;
}










// *** Reservation related functions ***
static Reservation * createReservation(){
    Reservation * r = g_malloc(sizeof(struct reservation));
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
        if(r->id) g_free(r->id); 
        if(r->user_id) g_free(r->user_id); 
        if(r->hotel_id) g_free(r->hotel_id); 
        if(r->hotel_name) g_free(r->hotel_name); 
        if(r->address) g_free(r->address); 
        if(r->begin_date) destroyTime(r->begin_date); 
        if(r->end_date) destroyTime(r->end_date); 
        if(r->room_details) g_free(r->room_details); 
        if(r->comment) g_free(r->comment); 
        g_free(r); 
    }
}


static void setReservId(Reservation * reserv,const char * line){
    if(reserv->id) g_free(reserv->id);
    reserv->id = g_strdup(line);
}

static char *getReservId(Reservation * reserv){
    if(reserv->id){
        char * id = g_strdup(reserv->id);
        return id;
    }
    return NULL;
}


static void setReservUserId(Reservation * reserv,const char * line){
    if(reserv->user_id) g_free(reserv->user_id);
    reserv->user_id = g_strdup(line);
}

static char *getReservUserId(Reservation * reserv){
     if(reserv->user_id){
        char * user_id = g_strdup(reserv->user_id);
        return user_id;
    }
    return NULL;
}


static void setReservHotelId(Reservation * reserv,const char * line){
    if(reserv->hotel_id) g_free(reserv->hotel_id);
    reserv->hotel_id = g_strdup(line);
}

static char *getReservHotelId(Reservation * reserv){
     if(reserv->hotel_id){
        char * hotel_id = g_strdup(reserv->hotel_id);
        return hotel_id;
    }
    return NULL;
}


static void setReservHotelName(Reservation * reserv,const char * line){
    if(reserv->hotel_name) g_free(reserv->hotel_name);
    reserv->hotel_name = g_strdup(line);
}

static char *getReservHotelName(Reservation * reserv){
     if(reserv->hotel_name){
        char * hotel_name = g_strdup(reserv->hotel_name);
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
    if(reserv->address) g_free(reserv->address);
    reserv->address = g_strdup(line);
}

static char *getReservHotelAddress(Reservation * reserv){
    if(reserv->address){
        char * address = g_strdup(reserv->address);
        return address;
    }
    return NULL;
}


static void setReservBeginDate(Reservation * reserv,Time * tempo){
    if(!reserv->begin_date) reserv->begin_date = createTime();
    copyTime(reserv->begin_date,tempo);
}

static Time * getReservBeginDate(Reservation * reserv){
    if(reserv->begin_date){
        Time * tempo = createTime();
        copyTime(tempo,reserv->begin_date);
        return tempo;
    }
    return NULL;
}


static void setReservEndDate(Reservation * reserv,Time * tempo){
    if(!reserv->end_date) reserv->end_date = createTime();
    copyTime(reserv->end_date,tempo);
}

static Time *getReservEndDate(Reservation * reserv){
    if(reserv->end_date){
        Time * tempo = createTime();
        copyTime(tempo,reserv->end_date);
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
    if(reserv->room_details) g_free(reserv->room_details);
    reserv->room_details = g_strdup(line);
}

static char *getReservRoomDetails(Reservation * reserv){
    if(reserv->room_details){
        char * room_details = g_strdup(reserv->room_details);
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
    if(reserv->comment) g_free(reserv->comment);
    reserv->comment = g_strdup(line);
}

static char *getReservComment(Reservation * reserv){
    if(reserv->comment){
        char * comment = g_strdup(reserv->comment);
        return comment;
    }
    return NULL;
}



// *** Passanger related functions *** 

static Passanger * createPassanger(){
    Passanger * p = g_malloc(sizeof(struct passanger));
    initPassanger(p);
    return p;
}

static void initPassanger(Passanger * passanger){
    passanger->flight_id = NULL;
    passanger->user_id = NULL;
}

static void destroyPassanger(Passanger * p) {
    if (p) {
        if(p->flight_id) g_free(p->flight_id); 
        if(p->user_id) g_free(p->user_id); 
        g_free(p); 
    }
}

static void setPassangerFlightId(Passanger * passanger,const char * line){
    if(passanger->flight_id) g_free(passanger->flight_id);
    passanger->flight_id = g_strdup(line);
}

static char *getPassangerFlightId(Passanger * passanger){
    if(passanger->flight_id){
        char * flight_id = g_strdup(passanger->flight_id);
        return flight_id;
    }
    return NULL;
}


static void setPassangerUserId(Passanger * passanger,const char * line){
    if(passanger->user_id) g_free(passanger->user_id);
    passanger->user_id = g_strdup(line);
}

static char *getPassangerUserId(Passanger * passanger){
    if(passanger->user_id){
        char * user_id = g_strdup(passanger->user_id);
        return user_id;
    }
}













ReservationSearchResults lookupReservUserId(gpointer key, gpointer value, gpointer user_data) {
    const char *user_id_to_find = (const char *)user_data;
    Reservation *reservation = (Reservation *)value;

    if (g_strcmp0(reservation->user_id, user_id_to_find) == 0) {
        // Create a new list node with the found reservation
        return g_slist_prepend(NULL, reservation);
    }

    return NULL;
}






// *** Block to get Types through other meanings than the hash table keys *** 

// struct to store the list of reservations of an hotel and the hotel id
typedef struct hotelReservs{
    struct reservation ** hotelReservs;
    char * hotel_id;
} ;

// Returns the reservations by the hotel id
static Reservation ** getAllReservsInHotel(void * dataStruct,const char * hotelId){
    HotelReservs * reservs = malloc(sizeof(struct hotelReservs) * g_hash_table_size((GHashTable *) dataStruct));
    g_hash_table_foreach((GHashTable *)dataStruct,allHotelReservs,reservs);
    return reservs->hotelReservs;
}

// Function to iterate and get the reservations on the list
static void allHotelReservs(gpointer key, gpointer value, gpointer hotelData) {
    HotelReservs * array = (HotelReservs *) hotelData;
    Reservation * reservation = (Reservation *)value;
    static int i = 0;

    if (!g_strcmp0(reservation->hotel_id,array->hotel_id)) {
          array->hotelReservs = reservation;
          i++;
    }  
}

//                                  *** End block ***


//                          *** Get total spend by an user ***




//                                  *** End block ***






static Passanger * lookupPassangerUserId(gpointer key, gpointer value, gpointer userData){
    const char * userId = (const char *) userData;
    Passanger *passanger = (Passanger *) value;

    if (g_strcmp0(passanger->user_id,userId) == 0) {
        return passanger;
    }
    return NULL;  
}







static gint compareTimes(Time *t1,char *passangers1,Time*t2,char *passangers2){
    if(t1->year != t2->year){
        if(t1->year > t2->year) return 1;
        return 0;
    }
    if(t1->mon != t2->mon){
        if(t1->mon > t2->mon) return 1;
        return 0;
    }
    if(t1->mday != t2->mday){
        if(t1->mday > t2->mday) return 1;
        return 0;
    }
    if(t1->hour != t2->hour){
        if(t1->hour> t2->hour) return 1;
        return 0;
    }if(t1->min != t2->min){
        if(t1->min > t2->min) return 1;
        return 0;
    }
    if(t1->sec != t2->sec){
        if(t1->sec > t2->sec) return 1;
        return 0;
    }
    return strcmp(passangers1,passangers2);
}

static gint comparePassangers(gint,gint);
static gint compareMedian(gdouble,gdouble);
static gint compareNames(char *,char*);