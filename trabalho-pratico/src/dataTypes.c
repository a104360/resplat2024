#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <stddef.h>
#include <stdio.h>
#include "../include/dataTypes.h"
#include "../include/catalogs.h"
#include "../include/time.h"
#include "../include/parser.h"



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
    int city_tax;
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
    user->birth_date = createTime();
    user->sex = '\0';
    user->passport = NULL;
    user->country_code = NULL;
    user->address = NULL;
    user->account_creation = createTime();
    user->pay_method = NULL;
    user->account_status = false;
}

User * createUser(){
    User * u = NULL;
    //u = malloc(sizeof(struct user));
    u = g_new(User,1);
    initUser(u);    
    return u;

}
void destroyUser(User *user) {
    if(user) {
        if(user->id != NULL){ //user->id = NULL;
            free(user->id);
            user->id = NULL;
        }
        if(user->name != NULL){ //user->name = NULL;
            free(user->name);
            user->name = NULL;
        }
        if(user->email != NULL){ //user->email = NULL;
            free(user->email);
            user->email = NULL;
        }
        if(user->phone_number != NULL){ //user->phone_number = NULL;
            free(user->phone_number);
            user->phone_number = NULL;
        }
        if(user->sex) user->sex = '\0';
        if(user->passport != NULL){ //user->passport = NULL;
            free(user->passport);
            user->passport = NULL;
        }
        if(user->country_code != NULL){ //user->country_code = NULL;
            free(user->country_code);
            user->country_code = NULL;
        }
        if(user->address != NULL){ //user->address = NULL;
            free(user->address);
            user->address = NULL;
        }
        if(user->pay_method != NULL){ //user->pay_method = NULL;
            free(user->pay_method);
            user->pay_method = NULL;
        }
        if(user->account_creation != NULL) destroyTime(user->account_creation);
        if(user->birth_date != NULL) destroyTime(user->birth_date);
        
        free(user);
        user = NULL;
    }
}



void setUserId(User * user, const char * line){
    if(line == NULL) return;
    if (user == NULL) return;

    if (user->id != NULL) {
        if(strlen(line) > strlen(user->id)){
            char * temp = realloc(user->id,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->id = temp;
            return;
        }else{
            strncpy(user->id,line,strlen(user->id));
            user->id[strlen(user->id)] = '\0';
            return;
        }
    }
    if (line) user->id = strdup(line); 
}


 char * getUserId(User * user){
    if(user->id){
        char * aux = strdup(user->id);
        return aux;
    }
    return NULL;
}


  void setUserName(User * user,const char * line){
    if(line == NULL) return;
    if(user->name) {
        if(strlen(line) > strlen(user->name)){
            char * temp = realloc(user->name,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->name = temp;
            return;
        }else{
            strncpy(user->name,line,strlen(user->name));
            user->name[strlen(user->name)] = '\0';
            return;
        }
    }
    if(line) user->name =strdup(line);
}

 char * getUserName(User * user){
     if(user->name){
        char * aux =strdup(user->name);
        return aux;
    }
    return NULL;
}


 void setUserEmail(User * user,const char * line){
    if(line == NULL) return;
    if(user->email != NULL) {
        if(strlen(line) > strlen(user->email)){
            char * temp = realloc(user->email,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->email = temp;
            return;
        }else{
            strncpy(user->email,line,strlen(user->email));
            user->email[strlen(user->email)] = '\0';
            return;
        }
    }
    user->email = strdup(line);
}

 char * getUserEmail(User * user){
    if(user->email != NULL){
        char * aux = strdup(user->email);
        return aux;
    }
    return NULL;
}

 void setUserPhone(User * user,const char * line){
    if(line == NULL) return;
    if(user == NULL) return;
    if(user->phone_number != NULL){
        if(strlen(line) > strlen(user->phone_number)){
            char * temp = realloc(user->phone_number,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->phone_number = temp;
            return;
        }else{
            strncpy(user->phone_number,line,strlen(user->phone_number));
            user->phone_number[strlen(user->phone_number)] = '\0';
            return;
        }
    }
    user->phone_number = strdup(line);
}

/*
void setUserPhone2(User * user, const char * line){
    if(user->phone_number != NULL) 
        free(user->phone_number);
        user->phone_number = NULL;

    // Pass 'phone' instead of 'token'
    char * phone = phoneNumberCheck(line);
    if(!phone) {
        fprintf(stderr, "Error checking phone number\n");
        return;  // or handle the error appropriately
    }

    user->phone_number = strdup(phone);
    free(phone);
}
*/

 char * getUserPhone(User * user){
    if(user->phone_number){
        char * aux = strdup(user->phone_number);
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
    if(user == NULL) return;
    if(line == NULL) return;
    if(user->passport){
        if(strlen(line) > strlen(user->passport)){
            char * temp = realloc(user->passport,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->passport = temp;
            return;
        }else{
            strncpy(user->passport,line,strlen(user->passport));
            user->passport[strlen(user->passport)] = '\0';
            return;
        }
    }
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
    if(user == NULL) return;
    if(line == NULL) return;
    if(user->country_code) {
        if(strlen(line) > strlen(user->country_code)){
            char * temp = realloc(user->country_code,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->country_code = temp;
            return;
        }else{
            strncpy(user->country_code,line,strlen(user->country_code));
            user->country_code[strlen(user->country_code)] = '\0';
            return;
        }
    }
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
    if(user == NULL) return;
    if(line == NULL) return;
    if(user->address) {
        if(strlen(line) > strlen(user->address)){
            char * temp = realloc(user->address,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->address = temp;
            return;
        }else{
            strncpy(user->address,line,strlen(user->address));
            user->address[strlen(user->address)] = '\0';
            return;
        }
    }
    user->address = strdup(line);
}

 char * getUserAddress(User * user){
    if(user->address){
        char * aux = strdup(user->address);
        return aux;
    }
    return NULL;
}


void setUserAccountCreation(User * user ,Time *tempo){
    if(user == NULL) return;
    if(tempo == NULL) return;
    if(user->account_creation == NULL) user->account_creation = createTime();
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
    if(user == NULL) return;
    if(line == NULL) return;
    if(user->pay_method) {
        if(strlen(line) > strlen(user->pay_method)){
            char * temp = realloc(user->pay_method,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->pay_method = temp;
            return;
        }else{
            strncpy(user->pay_method,line,strlen(user->pay_method));
            user->pay_method[strlen(user->pay_method)] = '\0';
            return;
        }
    }
    user->pay_method = strdup(line);
}

 char * getUserPayMethod(User * user){
    if(user->pay_method){
        char * aux =strdup(user->pay_method);
        return aux;
    }
    return NULL;
}


  void setUserAccountStatus(User * user ,const bool status){
    if(user == NULL) return;
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
    char * uId = getUserId(src);
    char * uName = getUserName(src);
    char * uEmail = getUserEmail(src);
    char * uPhone = getUserPhone(src);
    char * uPassport = getUserPassport(src);
    char * uCountry = getUserCountryCode(src);
    char * uAddress = getUserAddress(src);
    char * uPay = getUserPayMethod(src);
    Time * bDay = getUserBday(src);
    Time * accCreation = getUserAccountCreation(src);
    setUserId(dest,uId);
    setUserName(dest,uName);
    setUserEmail(dest,uEmail);
    setUserPhone(dest,uPhone);
    setUserBday(dest,bDay);
    setUserSex(dest,getUserSex(src));
    setUserPassport(dest,uPassport);
    setUserCountryCode(dest,uCountry);
    setUserAddress(dest,uAddress);
    setUserAccountCreation(dest,accCreation);
    setUserPayMethod(dest,uPay);
    setUserAccountStatus(dest,getUserAccountStatus(src));
    free(uId);
    free(uName);
    free(uEmail);
    free(uPhone);
    free(uPassport);
    free(uCountry);
    free(uAddress);
    free(uPay);
    free(bDay);
    free(accCreation);
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
    flight->schedule_departure_date = createTime();
    flight->schedule_arrival_date = createTime();
    flight->real_departure_date = createTime();
    flight->real_arrival_date = createTime();
    flight->pilot = NULL;
    flight->copilot = NULL;
    flight->notes = NULL;
}

  void destroyFlight(Flight * f) {
    if (f != NULL) {
        if(f->id != NULL){
            free(f->id);
            f->id = NULL;
        } 
        
        if(f->airline != NULL){
            free(f->airline);
            f->airline = NULL;
        } 
        
        if(f->plane_model != NULL){
            free(f->plane_model);
            f->plane_model = NULL;
        } 
        
        if(f->origin != NULL){
            free(f->origin);
            f->origin = NULL;
        } 
        
        if(f->destination != NULL){
            free(f->destination);
            f->destination = NULL;
        } 
        
        if(f->schedule_departure_date != NULL) destroyTime(f->schedule_departure_date); 
        if(f->schedule_arrival_date != NULL) destroyTime(f->schedule_arrival_date); 
        if(f->real_departure_date != NULL) destroyTime(f->real_departure_date); 
        if(f->real_arrival_date != NULL) destroyTime(f->real_arrival_date); 
        if(f->pilot != NULL){
            free(f->pilot);
            f->pilot = NULL;
        } 
        
        if(f->copilot != NULL){
            free(f->copilot);
            f->copilot = NULL;
        } 
        
        if(f->notes != NULL){
            free(f->notes);
            f->notes = NULL;
        } 
        
        free(f); 
        f = NULL;
    }
}

size_t getFlightSize(){
    return sizeof(struct flight);
}


  void setFlightId(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->id) {
        free(flight->id);
        flight->id = NULL;
    }
    flight->id = strdup(line);
}

 char *getFlightId(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->id){
        char * id =strdup(flight->id);
        return id;
    }
    return NULL;
}

  
  void setFlightAirline(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->airline) {
        free(flight->airline);
        flight->airline = NULL;
    }
    flight->airline = strdup(line);
}

 char *getFlightAirline(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->airline){
        char * airline =strdup(flight->airline);
        return airline;
    }
    return NULL;
}


  void setFlightPlaneModel(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->plane_model) {
        if(strlen(line) > strlen(flight->plane_model)){
            char * temp = realloc(flight->plane_model,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            flight->plane_model = temp;
            return;
        }else{
            strncpy(flight->plane_model,line,strlen(flight->plane_model));
            flight->plane_model[strlen(flight->plane_model)] = '\0';
            return;
        }
    }
    flight->plane_model =strdup(line);
}

 char *getFlightPlaneModel(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->plane_model){
        char * plane_model =strdup(flight->plane_model);
        return plane_model;
    }
    return NULL;
}


  void setFlightTotalSeats(Flight * flight,const unsigned int n){
    if(flight == NULL) return;
    flight->total_seats = n;
}

 unsigned int getFlightTotalSeats(Flight * flight){
    if(flight != NULL) return flight->total_seats;
    else return 0;
}


  void setFlightOrigin(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->origin) {
        free(flight->origin);
        flight->origin = NULL;
    }
    flight->origin = strdup(line);
}

 char *getFlightOrigin(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->origin){
        char * origin = strdup(flight->origin);
        return origin;
    }
    return NULL;
}


  void setFlightDestination(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->destination) {
        free(flight->destination);
        flight->destination = NULL;
    }
    flight->destination = strdup(line);
}

 char *getFlightDestination(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->destination){
        char * destination = strdup(flight->destination);
        return destination;
    }
    return NULL;
}


  void setFlightSDepartureDate(Flight * flight,Time * tempo){
    if(flight == NULL || tempo == NULL) return;
    if(flight->schedule_departure_date == NULL) flight->schedule_departure_date = createTime();
    copyTime(flight->schedule_departure_date,tempo);
}

 Time *getFlightSDepartureDate(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->schedule_departure_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->schedule_departure_date);
        return tempo;
    }
    return NULL;
}


  void setFlightSArrivalDate(Flight * flight,Time * tempo){
    if(flight == NULL || tempo == NULL) return;
    if(flight->schedule_arrival_date == NULL) flight->schedule_arrival_date = createTime();
    copyTime(flight->schedule_arrival_date,tempo);
}

 Time *getFlightSArrivalDate(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->schedule_arrival_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->schedule_arrival_date);
        return tempo;
    }
    return NULL;
}


  void setFlightRDepartureDate(Flight * flight, Time * tempo){
    if(flight == NULL || tempo == NULL) return;
    if(flight->real_departure_date == NULL) flight->real_departure_date = createTime();
    copyTime(flight->real_departure_date,tempo);
}

 Time *getFlightRDepartureDate(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->real_departure_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->real_departure_date);
        return tempo;
    }
    return NULL;
}


  void setFlightRArrivalDate(Flight * flight,Time * tempo){
    if(flight == NULL || tempo == NULL) return;
    if(flight->real_arrival_date == NULL) flight->real_arrival_date = createTime();
    copyTime(flight->real_arrival_date,tempo);
}

 Time *getFlightRArrivalDate(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->real_arrival_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->real_arrival_date);
        return tempo;
    }
    return NULL;
}


  void setFlightPilot(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->pilot) {
        if(strlen(line) > strlen(flight->pilot)){
            char * temp = realloc(flight->pilot,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            flight->pilot = temp;
            return;
        }else{
            strncpy(flight->pilot,line,strlen(flight->pilot));
            flight->pilot[strlen(flight->pilot)] = '\0';
            return;
        }
    }
    flight->pilot =strdup(line);
}

 char *getFlightPilot(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->pilot){
        char * pilot =strdup(flight->pilot);
        return pilot;
    }
    return NULL;
}


  void setFlightCopilot(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->copilot) {
        if(strlen(line) > strlen(flight->copilot)){
            char * temp = realloc(flight->copilot,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            flight->copilot = temp;
            return;
        }else{
            strncpy(flight->copilot,line,strlen(flight->copilot));
            flight->copilot[strlen(flight->copilot)] = '\0';
            return;
        }
    }
    flight->copilot =strdup(line);
}

 char *getFlightCopilot(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->copilot){
        char * copilot =strdup(flight->copilot);
        return copilot;
    }
    return NULL;
}


  void setFlightNotes(Flight * flight,const char * line){
    if(line == NULL || flight == NULL) return;
    if(flight->notes) {
        if(strlen(line) > strlen(flight->notes)){
            char * temp = realloc(flight->notes,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            flight->notes = temp;
            return;
        }else{
            strncpy(flight->notes,line,strlen(flight->notes));
            flight->notes[strlen(flight->notes)] = '\0';
            return;
        }
    }
    flight->notes =strdup(line);
}

 char *getFlightNotes(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->notes){
        char * notes =strdup(flight->notes);
        return notes;
    }
    return NULL;
}

int getFlightDelay(Flight * flight){
    if(flight == NULL) return -1;
    return ((getYear(flight->real_departure_date) - getYear(flight->schedule_departure_date)) * 31536000) + 
    ((getMon(flight->real_departure_date) - getMon(flight->schedule_departure_date)) * 2592000) + 
    ((getMday(flight->real_departure_date) - getMday(flight->schedule_departure_date)) * 86400) + 
    ((getHour(flight->real_departure_date) - getHour(flight->schedule_departure_date)) * 3600) + 
    ((getMin(flight->real_departure_date) - getMin(flight->schedule_departure_date)) * 60) +
    ((getSec(flight->real_departure_date) - getSec(flight->schedule_departure_date)));
}


void copyFlight(Flight * dest,Flight * src){
    if(dest == NULL || src == NULL) return;
    char * flightId = getFlightId(src);
    char * flightAirline = getFlightAirline(src);
    char * flightPlaneModel = getFlightPlaneModel(src);
    char * flightOrigin = getFlightOrigin(src);
    char * flightDestination = getFlightDestination(src);
    char * flightPilot = getFlightPilot(src);
    char * flightCopilot = getFlightCopilot(src);
    char * flightNotes = getFlightNotes(src);
    Time * flightSDepartureDate = getFlightSDepartureDate(src);
    Time * flightSArrivalDate = getFlightSArrivalDate(src);
    Time * flightRDepartureDate = getFlightRDepartureDate(src);
    Time * flightRArrivalDate = getFlightRArrivalDate(src);


    setFlightId(dest,flightId);
    setFlightAirline(dest,flightAirline);
    setFlightPlaneModel(dest,flightPlaneModel);
    setFlightTotalSeats(dest,getFlightTotalSeats(src));
    setFlightOrigin(dest,flightOrigin);
    setFlightDestination(dest,flightDestination);
    setFlightSDepartureDate(dest,flightSDepartureDate);
    setFlightSArrivalDate(dest,flightSArrivalDate);
    setFlightRDepartureDate(dest,flightRDepartureDate);
    setFlightRArrivalDate(dest,flightRArrivalDate);
    setFlightPilot(dest,flightPilot);
    setFlightCopilot(dest,flightCopilot);
    setFlightNotes(dest,flightNotes);


    free(flightId);
    flightId = NULL;
    free(flightAirline);
    flightAirline = NULL;
    free(flightPlaneModel);
    flightPlaneModel = NULL;
    free(flightOrigin);
    flightOrigin = NULL;
    free(flightDestination);
    flightDestination = NULL;
    free(flightPilot);
    flightPilot = NULL;
    free(flightCopilot);
    flightCopilot = NULL;
    free(flightNotes);
    flightNotes = NULL;
    free(flightSDepartureDate);
    flightSDepartureDate = NULL;
    free(flightSArrivalDate);
    flightSArrivalDate = NULL;
    free(flightRDepartureDate);
    flightRDepartureDate = NULL;
    free(flightRArrivalDate);
    flightRArrivalDate = NULL;
}


// 








// *** Reservation related functions ***
Reservation * createReservation(){
    Reservation * r = malloc(sizeof(struct reservation));
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
    reservation->begin_date = createTime();
    reservation->end_date = createTime();
    reservation->price_per_night = 0.0;
    reservation->includes_breakfast = false;
    reservation->room_details = NULL;
    reservation->rating = 0;
    reservation->comment = NULL;
}

void destroyReservation(Reservation * r) {
    if (r != NULL) {
        if(r->id) {
            free(r->id);
            r->id = NULL;
        } 
        if(r->user_id) {
            free(r->user_id);
            r->user_id = NULL;
        } 
        if(r->hotel_id) {
            free(r->hotel_id);
            r->hotel_id = NULL;
        } 
        if(r->hotel_name) {
            free(r->hotel_name);
            r->hotel_name = NULL;
        } 
        if(r->address) {
            free(r->address);
            r->address = NULL;
        } 
        if(r->begin_date) destroyTime(r->begin_date); 
        if(r->end_date) destroyTime(r->end_date); 
        if(r->room_details) {
            free(r->room_details);
            r->room_details = NULL;
        } 
        if(r->comment) {
            free(r->comment);
            r->comment = NULL;
        } 
        free(r); 
        r = NULL;
    }
}

size_t getReservSize(){
    return sizeof(struct reservation);
}

void setReservId(Reservation * reserv,const char * line){
    if(reserv->id){
        free(reserv->id);
        reserv->id = NULL;
    }
    reserv->id = strdup(line);
}

char *getReservId(Reservation * reserv){
    if(reserv == NULL) return NULL;
    if(reserv->id == NULL) return NULL;
    if(reserv->id != NULL){
        char * id = strdup(reserv->id);
        return id;
    }
    return NULL;
}


void setReservUserId(Reservation * reserv,const char * line){
    if(reserv->user_id){
        free(reserv->user_id);
        reserv->user_id = NULL;
    }
    reserv->user_id = strdup(line);
}

char *getReservUserId(Reservation * reserv){
     if(reserv->user_id){
        char * user_id = strdup(reserv->user_id);
        return user_id;
    }
    return NULL;
}


  void setReservHotelId(Reservation * reserv,const char * line){
    if(reserv->hotel_id){
        if(strlen(line) > strlen(reserv->hotel_id)){
            char * temp = realloc(reserv->hotel_id,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            reserv->hotel_id = temp;
            return;
        }else{
            strncpy(reserv->hotel_id,line,strlen(reserv->hotel_id));
            reserv->hotel_id[strlen(reserv->hotel_id)] = '\0';
            return;
        }
    }
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
    if(reserv->hotel_name){
        if(strlen(line) > strlen(reserv->hotel_name)){
            char * temp = realloc(reserv->hotel_name,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            reserv->hotel_name = temp;
            return;
        }else{
            strncpy(reserv->hotel_name,line,strlen(reserv->hotel_name));
            reserv->hotel_name[strlen(reserv->hotel_name)] = '\0';
            return;
        }
    }
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


  void setReservCityTax(Reservation * reserv,const int n){
    reserv->city_tax = n;
}

 int getReservCityTax(Reservation * reserv){
    return reserv->city_tax;
}


  void setReservHotelAddress(Reservation * reserv,const char * line){
    if(reserv->address){
        if(strlen(line) > strlen(reserv->address)){
            char * temp = realloc(reserv->address,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            reserv->address = temp;
            return;
        }else{
            strncpy(reserv->address,line,strlen(reserv->address));
            reserv->address[strlen(reserv->address)] = '\0';
            return;
        }
    }
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
    if(reserv->begin_date == NULL) reserv->begin_date = createTime();
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
    if(reserv->end_date == NULL) reserv->end_date = createTime();
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
    if(line == NULL) return;
    if(reserv->room_details){
        if(strlen(line) > strlen(reserv->room_details)){
            char * temp = realloc(reserv->room_details,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            reserv->room_details = temp;
            return;
        }else{
            strncpy(reserv->room_details,line,strlen(reserv->room_details));
            reserv->room_details[strlen(reserv->room_details)] = '\0';
            return;
        }
    }
    reserv->room_details =strdup(line);
}

 char *getReservRoomDetails(Reservation * reserv){
    if(reserv->room_details){
        char * room_details = strdup(reserv->room_details);
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
    if(line == NULL) return;
    if(reserv->comment) {
        if(strlen(line) > strlen(reserv->comment)){
            char * temp = realloc(reserv->comment,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            reserv->comment = temp;
            return;
        }else{
            strncpy(reserv->comment,line,strlen(reserv->comment));
            reserv->comment[strlen(reserv->comment)] = '\0';
            return;
        }
    }
    reserv->comment = strdup(line);
}

 char *getReservComment(Reservation * reserv){
    if(reserv->comment){
        char * comment =strdup(reserv->comment);
        return comment;
    }
    return NULL;
}


void copyReservation(Reservation * dest,Reservation * src){
    char * reservId = getReservId(src);
    char * reservUserId = getReservUserId(src);
    char * reservHotelId = getReservHotelId(src);
    char * reservHotelName = getReservHotelName(src);
    char * reservHotelAddress = getReservHotelAddress(src);
    char * reservRoomDetails = getReservRoomDetails(src);
    char * reservComment = getReservComment(src);
    Time * reservBeginDate = getReservBeginDate(src);
    Time * reservEndDate = getReservEndDate(src);


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


    free(reservId);
    reservId = NULL;
    free(reservUserId);
    reservUserId = NULL;
    free(reservHotelId);
    reservHotelId = NULL;
    free(reservHotelName);
    reservHotelName = NULL;
    free(reservHotelAddress);
    reservHotelAddress = NULL;
    free(reservRoomDetails);
    reservRoomDetails = NULL;
    free(reservComment);
    reservComment = NULL;
    free(reservBeginDate);
    reservBeginDate = NULL;
    free(reservEndDate);
    reservEndDate = NULL;
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
    if (p != NULL) {
        if(p->flight_id != NULL){
            free(p->flight_id); 
            p->flight_id = NULL;
        }
        if(p->user_id != NULL){
            free(p->user_id); 
            p->user_id = NULL;
        }
        free(p); 
        p = NULL;
    }
}

size_t getPassangerSize(){
    return sizeof(struct passanger);
}


 void setPassangerFlightId(Passanger * passanger,const char * line){
    if(passanger == NULL || line == NULL) return;
    if(passanger->flight_id){
        if(strlen(line) > strlen(passanger->flight_id)){
            char * temp = realloc(passanger->flight_id,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            passanger->flight_id = temp;
            return;
        }else{
            strncpy(passanger->flight_id,line,strlen(passanger->flight_id));
            passanger->flight_id[strlen(passanger->flight_id)] = '\0';
            return;
        }
    }
    passanger->flight_id = strdup(line);
}

 char *getPassangerFlightId(Passanger * passanger){
    if(passanger == NULL) return NULL;
    if(passanger->flight_id == NULL) return NULL;
    if(passanger->flight_id != NULL){
        char * flight_id = strdup(passanger->flight_id);
        return flight_id;
    }
    return NULL;
}


  void setPassangerUserId(Passanger * passanger,const char * line){
    if(passanger == NULL || line == NULL) return;
    if(passanger->user_id){
        if(strlen(line) > strlen(passanger->user_id)){
            char * temp = realloc(passanger->user_id,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            passanger->user_id = temp;
            return;
        }else{
            strncpy(passanger->user_id,line,strlen(passanger->user_id));
            passanger->user_id[strlen(passanger->user_id)] = '\0';
            return;
        }
    }
    passanger->user_id = strdup(line);
}

 char *getPassangerUserId(Passanger * passanger){
    if(passanger == NULL) return NULL;
    if(passanger->user_id){
        char * user_id = strdup(passanger->user_id);
        return user_id;
    }
    return NULL;
}


void copyPassanger(Passanger * dest,Passanger * src){
    if(dest == NULL || src == NULL) return;
    char * passangerFlightId = getPassangerFlightId(src);
    char * passangerUserId = getPassangerUserId(src);

    setPassangerFlightId(dest,passangerFlightId);
    setPassangerUserId(dest,passangerUserId);

    free(passangerFlightId);
    passangerFlightId = NULL;
    free(passangerUserId);
    passangerUserId = NULL;
}



//                      *** Get all the passangers of a flight ***


//                                  *** End block ***
