#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <stddef.h>
#include "../include/dataTypes.h"
#include "../include/catalogs.h"
#include "../include/time.h"



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
}Reservation;


typedef struct passanger{
    char * flight_id;
    char * user_id;
} Passanger;









// *** User Related Functions ***



  void initUser(User * user){
    if(!user) return;
    user->id = NULL;
    user->name = NULL;
    user->email = NULL;
    user->phone_number = NULL;
    setTime(user->birth_date,0,0,0,0,0,0);
    user->sex = '\0';
    user->passport = NULL;
    user->country_code = NULL;
    user->address = NULL;
    setTime(user->account_creation,0,0,0,0,0,0);
    user->pay_method = NULL;
    user->account_status = false;
}

 User * createUser(){
    User * u = malloc(sizeof(struct user));
    initUser(u);    
    return u;

}
  void destroyUser(User *user) {
    if(user) {
        if(user->id) free(user->id);
        if(user->name) free(user->name);
        if(user->email) free(user->email);
        if(user->phone_number) free(user->phone_number);
        if(user->sex) user->sex = '\0';
        if(user->passport) free(user->passport);
        if(user->country_code) free(user->country_code);
        if(user->address) free(user->address);
        if(user->pay_method) free(user->pay_method);
        if(user->account_creation) destroyTime(user->account_creation);
        if(user->birth_date) destroyTime(user->birth_date);
        free(user);
    }
}



void setUserId(User * user, const char * id){
    if (user == NULL) {
        // Handle the error or return early based on your program's logic.
        return;
    }

    // Free existing memory
    if (user->id) {
        free(user->id);
        user->id = NULL;  // Set to NULL after freeing to avoid potential issues
    }
    if(id == NULL) return;
    // Allocate new memory if id is not NULL
    if (id) {
        user->id = strdup(id);
        // Check if strdup was successful, handle error if needed
    }
}


 char * getUserId(User * user){
    if(user->id){
        char * aux =strdup(user->id);
        return aux;
    }
    return NULL;
}


  void setUserName(User * user,const char * name){
    if(user->name) free(user->name);
    if(name) user->name =strdup(name);
}

 char * getUserName(User * user){
     if(user->name){
        char * aux =strdup(user->name);
        return aux;
    }
    return NULL;
}


 void setUserEmail(User * user,const char * email){
    if(user->email) free(user->email);
    if(email) user->email =strdup(email);
}

 char * getUserEmail(User * user){
    if(user->email){
        char * aux =strdup(user->email);
        return aux;
    }
    return NULL;
}

 void setUserPhone(User * user,const char * line){
    if(user->phone_number) free(user->phone_number);
    if(line) user->phone_number =strdup(line);
}
 char * getUserPhone(User * user){
    if(user->phone_number){
        char * aux =strdup(user->phone_number);
        return aux;
    }
    return NULL;
}



  void setUserBday(User * user ,Time * tempo){
    if(!user->birth_date) user->birth_date = createTime();
    copyTime(user->birth_date,tempo);
}

 Time * getUserBday(User * user){
    if(user->birth_date){
        Time * aux = createTime();
        copyTime(aux,user->birth_date);
        return aux;
    }
    return NULL;
}


void setUserSex(User * user ,const char line){
    user->sex = (char) line;
}

 char getUserSex(User * user){
    return user->sex;
}


  void setUserPassport(User * user ,const char * line){
    if(user->passport) free(user->passport);
    user->passport =strdup(line);
}

 char * getUserPassport(User * user){
    if(user->passport){
        char * aux =strdup(user->passport);
        return aux;
    }
    return NULL;
}


 void setUserCountryCode(User * user ,const char * line){
    if(user->country_code) free(user->country_code);
    user->country_code =strdup(line);
}

 char * getUserCountryCode(User * user){
    if(user->country_code){
        char * aux =strdup(user->country_code);
        return aux;
    }
    return NULL;
}


 void setUserAddress(User * user ,const char * line){
    if(user->address) free(user->address);
    user->address =strdup(line);
}

 char * getUserAddress(User * user){
    if(user->address){
        char * aux =strdup(user->address);
        return aux;
    }
    return NULL;
}


  void setUserAccountCreation(User * user ,Time *tempo){
    if(!user->account_creation) user->account_creation = createTime();
    copyTime(user->account_creation,tempo);
}

 Time * getUserAccountCreation(User * user){
    if(user->account_creation){
        Time * t = createTime();
        copyTime(t,user->account_creation);
        return t;
    }
    return NULL;
}


  void setUserPayMethod(User * user ,const char * line){
    if(user->pay_method) free(user->pay_method);
    user->pay_method =strdup(line);
}

 char * getUserPayMethod(User * user){
    if(user->pay_method){
        char * aux =strdup(user->pay_method);
        return aux;
    }
    return NULL;
}


  void setUserAccountStatus(User * user ,const bool status){
    user->account_status = status;

}

 bool getUserAccountStatus(User * user){
    if(user){
        return user->account_status;
    }
    return false;
} 


int getUserAge(User * user){
    Time * userBday = getUserBday(user);
    int n = PYEAR - (getYear(userBday));
    if(PDAY >= getMday(userBday))
        if(PMON >= getMon(userBday))
            return n;
    return n - 1;
}

void copyUser(User * dest,User * src){
    setUserId(dest,getUserId(src));
    setUserName(dest,getUserName(src));
    setUserEmail(dest,getUserEmail(src));
    setUserPhone(dest,getUserPhone(src));
    setUserBday(dest,getUserBday(src));
    setUserSex(dest,getUserSex(src));
    setUserPassport(dest,getUserPassport(src));
    setUserCountryCode(dest,getUserCountryCode(src));
    setUserAddress(dest,getUserAddress(src));
    setUserAccountCreation(dest,getUserAccountCreation(src));
    setUserPayMethod(dest,getUserPayMethod(src));
    setUserAccountStatus(dest,getUserAccountStatus(src));
}

// *** End of user functions ***












// *** Flight related functions ***

 Flight * createFlight(){
    Flight * f =malloc(sizeof(struct flight));
    initFlight(f);
    return f;
}

  void initFlight(Flight * flight){
    flight->id = NULL;
    flight->airline = NULL;
    flight->plane_model = NULL;
    flight->total_seats = 0;
    flight->origin = NULL;
    flight->destination = NULL;
    setTime(flight->schedule_departure_date,0,0,0,0,0,0);
    setTime(flight->schedule_arrival_date,0,0,0,0,0,0);
    setTime(flight->real_departure_date,0,0,0,0,0,0);
    setTime(flight->real_arrival_date,0,0,0,0,0,0);
    flight->pilot = NULL;
    flight->copilot = NULL;
    flight->notes = NULL;
}

  void destroyFlight(Flight * f) {
    if (f != NULL) {
        if(f->id) free(f->id); 
        if(f->airline) free(f->airline); 
        if(f->plane_model) free(f->plane_model); 
        if(f->origin) free(f->origin); 
        if(f->destination) free(f->destination); 
        if(f->schedule_departure_date) destroyTime(f->schedule_departure_date); 
        if(f->schedule_arrival_date) destroyTime(f->schedule_arrival_date); 
        if(f->real_departure_date) destroyTime(f->real_departure_date); 
        if(f->real_arrival_date) destroyTime(f->real_arrival_date); 
        if(f->pilot) free(f->pilot); 
        if(f->copilot) free(f->copilot); 
        if(f->notes) free(f->notes); 
        free(f); 
    }
}

size_t getFlightSize(){
    return sizeof(struct flight);
}


  void setFlightId(Flight * flight,const char * line){
    if(flight->id) free(flight->id);
    flight->id =strdup(line);
}

 char *getFlightId(Flight * flight){
    if(flight->id){
        char * id =strdup(flight->id);
        return id;
    }
    return NULL;
}

  
  void setFlightAirline(Flight * flight,const char * line){
    if(flight->airline) free(flight->airline);
    flight->airline =strdup(line);
}

 char *getFlightAirline(Flight * flight){
    if(flight->airline){
        char * airline =strdup(flight->airline);
        return airline;
    }
    return NULL;
}


  void setFlightPlaneModel(Flight * flight,const char * line){
    if(flight->plane_model) free(flight->plane_model);
    flight->plane_model =strdup(line);
}

 char *getFlightPlaneModel(Flight * flight){
    if(flight->plane_model){
        char * plane_model =strdup(flight->plane_model);
        return plane_model;
    }
    return NULL;
}


  void setFlightTotalSeats(Flight * flight,const unsigned int n){
    flight->total_seats = n;
}

 unsigned int getFlightTotalSeats(Flight * flight){
    return flight->total_seats;
}


  void setFlightOrigin(Flight * flight,const char * line){
    if(flight->origin) free(flight->origin);
    flight->origin =strdup(line);
}

 char *getFlightOrigin(Flight * flight){
    if(flight->origin){
        char * origin =strdup(flight->origin);
        return origin;
    }
    return NULL;
}


  void setFlightDestination(Flight * flight,const char * line){
    if(flight->destination) free(flight->destination);
    flight->destination =strdup(line);
}

 char *getFlightDestination(Flight * flight){
    if(flight->destination){
        char * destination =strdup(flight->destination);
        return destination;
    }
    return NULL;
}


  void setFlightSDepartureDate(Flight * flight,Time * tempo){
    if(!flight->schedule_departure_date) flight->schedule_departure_date = createTime();
    copyTime(flight->schedule_departure_date,tempo);
}

 Time *getFlightSDepartureDate(Flight * flight){
    if(flight->schedule_departure_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->schedule_departure_date);
        return tempo;
    }
    return NULL;
}


  void setFlightSArrivalDate(Flight * flight,Time * tempo){
    if(!flight->schedule_arrival_date) flight->schedule_arrival_date = createTime();
    copyTime(flight->schedule_arrival_date,tempo);
}

 Time *getFlightSArrivalDate(Flight * flight){
    if(flight->schedule_arrival_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->schedule_arrival_date);
        return tempo;
    }
    return NULL;
}


  void setFlightRDepartureDate(Flight * flight, Time * tempo){
    if(!flight->real_departure_date) flight->real_departure_date = createTime();
    copyTime(flight->real_departure_date,tempo);
}

 Time *getFlightRDepartureDate(Flight * flight){
    if(flight->real_departure_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->real_departure_date);
        return tempo;
    }
    return NULL;
}


  void setFlightRArrivalDate(Flight * flight,Time * tempo){
    if(!flight->real_arrival_date) flight->real_arrival_date = createTime();
    copyTime(flight->real_arrival_date,tempo);
}

 Time *getFlightRArrivalDate(Flight * flight){
    if(flight->real_arrival_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->real_arrival_date);
        return tempo;
    }
    return NULL;
}


  void setFlightPilot(Flight * flight,const char * line){
    if(flight->pilot) free(flight->pilot);
    flight->pilot =strdup(line);
}

 char *getFlightPilot(Flight * flight){
    if(flight->pilot){
        char * pilot =strdup(flight->pilot);
        return pilot;
    }
    return NULL;
}


  void setFlightCopilot(Flight * flight,const char * line){
    if(flight->copilot) free(flight->copilot);
    flight->copilot =strdup(line);
}

 char *getFlightCopilot(Flight * flight){
    if(flight->copilot){
        char * copilot =strdup(flight->copilot);
        return copilot;
    }
    return NULL;
}


  void setFlightNotes(Flight * flight,const char * line){
    if(flight->notes) free(flight->notes);
    flight->notes =strdup(line);
}

 char *getFlightNotes(Flight * flight){
    if(flight->notes){
        char * notes =strdup(flight->notes);
        return notes;
    }
    return NULL;
}

int getFlightDelay(Flight * flight){
    return ((getYear(flight->real_departure_date) - getYear(flight->schedule_departure_date)) * 31536000) + 
    ((getMon(flight->real_departure_date) - getMon(flight->schedule_departure_date)) * 2592000) + 
    ((getMday(flight->real_departure_date) - getMday(flight->schedule_departure_date)) * 86400) + 
    ((getHour(flight->real_departure_date) - getHour(flight->schedule_departure_date)) * 3600) + 
    ((getMin(flight->real_departure_date) - getMin(flight->schedule_departure_date)) * 60) +
    ((getSec(flight->real_departure_date) - getSec(flight->schedule_departure_date)));
}


void copyFlight(Flight * dest,Flight * src){
    setFlightId(dest,getFlightId(src));
    setFlightAirline(dest,getFlightAirline(src));
    setFlightPlaneModel(dest,getFlightPlaneModel(src));
    setFlightTotalSeats(dest,getFlightTotalSeats(src));
    setFlightOrigin(dest,getFlightOrigin(src));
    setFlightDestination(dest,getFlightDestination(src));
    setFlightSDepartureDate(dest,getFlightSDepartureDate(src));
    setFlightSArrivalDate(dest,getFlightSArrivalDate(src));
    setFlightRDepartureDate(dest,getFlightRDepartureDate(src));
    setFlightRArrivalDate(dest,getFlightRArrivalDate(src));
    setFlightPilot(dest,getFlightPilot(src));
    setFlightCopilot(dest,getFlightCopilot(src));
    setFlightNotes(dest,getFlightNotes(src));
}


// 








// *** Reservation related functions ***
 Reservation * createReservation(){
    Reservation * r =malloc(sizeof(struct reservation));
    initReservation(r);
    return r;
}

  void initReservation(Reservation * reservation){
    reservation->id = NULL;
    reservation->user_id = NULL;
    reservation->hotel_id = NULL;
    reservation->hotel_name = NULL;
    reservation->hotel_stars = 0;
    reservation->city_tax = 0.0;
    reservation->address = NULL;
    setTime(reservation->begin_date,0,0,0,0,0,0);
    setTime(reservation->end_date,0,0,0,0,0,0);
    reservation->price_per_night = 0.0;
    reservation->includes_breakfast = false;
    reservation->room_details = NULL;
    reservation->rating = 0;
    reservation->comment = NULL;
}

  void destroyReservation(Reservation * r) {
    if (r != NULL) {
        if(r->id) free(r->id); 
        if(r->user_id) free(r->user_id); 
        if(r->hotel_id) free(r->hotel_id); 
        if(r->hotel_name) free(r->hotel_name); 
        if(r->address) free(r->address); 
        if(r->begin_date) destroyTime(r->begin_date); 
        if(r->end_date) destroyTime(r->end_date); 
        if(r->room_details) free(r->room_details); 
        if(r->comment) free(r->comment); 
        free(r); 
    }
}

size_t getReservSize(){
    return sizeof(struct reservation);
}

  void setReservId(Reservation * reserv,const char * line){
    if(reserv->id) free(reserv->id);
    reserv->id =strdup(line);
}

 char *getReservId(Reservation * reserv){
    if(reserv->id){
        char * id =strdup(reserv->id);
        return id;
    }
    return NULL;
}


  void setReservUserId(Reservation * reserv,const char * line){
    if(reserv->user_id) free(reserv->user_id);
    reserv->user_id =strdup(line);
}

 char *getReservUserId(Reservation * reserv){
     if(reserv->user_id){
        char * user_id =strdup(reserv->user_id);
        return user_id;
    }
    return NULL;
}


  void setReservHotelId(Reservation * reserv,const char * line){
    if(reserv->hotel_id) free(reserv->hotel_id);
    reserv->hotel_id =strdup(line);
}

 char *getReservHotelId(Reservation * reserv){
     if(reserv->hotel_id){
        char * hotel_id =strdup(reserv->hotel_id);
        return hotel_id;
    }
    return NULL;
}


  void setReservHotelName(Reservation * reserv,const char * line){
    if(reserv->hotel_name) free(reserv->hotel_name);
    reserv->hotel_name =strdup(line);
}

 char *getReservHotelName(Reservation * reserv){
     if(reserv->hotel_name){
        char * hotel_name =strdup(reserv->hotel_name);
        return hotel_name;
    }
    return NULL;
}


  void setReservHotelStars(Reservation * reserv,const unsigned int n){
    reserv->hotel_stars = n;
}

 unsigned int getReservHotelStars(Reservation * reserv){
    return reserv->hotel_stars;
}


  void setReservCityTax(Reservation * reserv,const double n){
    reserv->city_tax = n;
}

 double getReservCityTax(Reservation * reserv){
    return reserv->city_tax;
}


  void setReservHotelAddress(Reservation * reserv,const char * line){
    if(reserv->address) free(reserv->address);
    reserv->address =strdup(line);
}

 char *getReservHotelAddress(Reservation * reserv){
    if(reserv->address){
        char * address =strdup(reserv->address);
        return address;
    }
    return NULL;
}


  void setReservBeginDate(Reservation * reserv,Time * tempo){
    if(!reserv->begin_date) reserv->begin_date = createTime();
    copyTime(reserv->begin_date,tempo);
}

 Time * getReservBeginDate(Reservation * reserv){
    if(reserv->begin_date){
        Time * tempo = createTime();
        copyTime(tempo,reserv->begin_date);
        return tempo;
    }
    return NULL;
}


  void setReservEndDate(Reservation * reserv,Time * tempo){
    if(!reserv->end_date) reserv->end_date = createTime();
    copyTime(reserv->end_date,tempo);
}

 Time *getReservEndDate(Reservation * reserv){
    if(reserv->end_date){
        Time * tempo = createTime();
        copyTime(tempo,reserv->end_date);
        return tempo;
    }
    return NULL;
}


  void setReservPricePerNight(Reservation * reserv,const double n){
    reserv->price_per_night = n;
}

 double getReservPricePerNight(Reservation * reserv){
    return reserv->price_per_night;
}


  void setReservBreakfast(Reservation * reserv,const bool x){
    reserv->includes_breakfast = x;
}

 bool getReservBreakfast(Reservation * reserv){
    return reserv->includes_breakfast;
}


  void setReservRoomDetails(Reservation * reserv,const char * line){
    if(reserv->room_details) free(reserv->room_details);
    reserv->room_details =strdup(line);
}

 char *getReservRoomDetails(Reservation * reserv){
    if(reserv->room_details){
        char * room_details =strdup(reserv->room_details);
        return room_details;
    }
    return NULL;
}


  void setReservRating(Reservation * reserv,const unsigned int n){
    reserv->rating = n;
}

 unsigned int getReservRating(Reservation * reserv){
    return reserv->rating;
}


  void setReservComment(Reservation * reserv,const char * line){
    if(reserv->comment) free(reserv->comment);
    reserv->comment =strdup(line);
}

 char *getReservComment(Reservation * reserv){
    if(reserv->comment){
        char * comment =strdup(reserv->comment);
        return comment;
    }
    return NULL;
}


void copyReservation(Reservation * dest,Reservation * src){
    setReservId(dest,getReservId(src));
    setReservUserId(dest,getReservUserId(src));
    setReservHotelId(dest,getReservHotelId(src));
    setReservHotelName(dest,getReservHotelName(src));
    setReservHotelStars(dest,getReservHotelStars(src));
    setReservCityTax(dest,getReservCityTax(src));
    setReservHotelAddress(dest,getReservHotelAddress(src));
    setReservBeginDate(dest,getReservBeginDate(src));
    setReservEndDate(dest,getReservEndDate(src));
    setReservPricePerNight(dest,getReservPricePerNight(src));
    setReservBreakfast(dest,getReservBreakfast(src));
    setReservRoomDetails(dest,getReservRoomDetails(src));
    setReservRating(dest,getReservRating(src));
    setReservComment(dest,getReservComment(src));
}














// *** Passanger related functions *** 

 Passanger * createPassanger(){
    Passanger * p =malloc(sizeof(struct passanger));
    initPassanger(p);
    return p;
}

  void initPassanger(Passanger * passanger){
    passanger->flight_id = NULL;
    passanger->user_id = NULL;
}

  void destroyPassanger(Passanger * p) {
    if (p) {
        if(p->flight_id) free(p->flight_id); 
        if(p->user_id) free(p->user_id); 
        free(p); 
    }
}

size_t getPassangerSize(){
    return sizeof(struct passanger);
}


  void setPassangerFlightId(Passanger * passanger,const char * line){
    if(passanger->flight_id) free(passanger->flight_id);
    passanger->flight_id =strdup(line);
}

 char *getPassangerFlightId(Passanger * passanger){
    if(passanger->flight_id){
        char * flight_id =strdup(passanger->flight_id);
        return flight_id;
    }
    return NULL;
}


  void setPassangerUserId(Passanger * passanger,const char * line){
    if(passanger->user_id) free(passanger->user_id);
    passanger->user_id = strdup(line);
}

 char *getPassangerUserId(Passanger * passanger){
    if(passanger->user_id){
        char * user_id =strdup(passanger->user_id);
        return user_id;
    }
    return NULL;
}


void copyPassanger(Passanger * dest,Passanger * src){
    setPassangerFlightId(dest,getPassangerFlightId(src));
    setPassangerUserId(dest,getPassangerUserId(src));
}



//                      *** Get all the passangers of a flight ***


//                                  *** End block ***
