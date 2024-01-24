#include "../include/reservation.h"
#include "../include/database.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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
    if(!reserv) return;
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
    if(!reserv) return;
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
    if(!reserv) return;
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
    if(!reserv) return NULL;
     if(reserv->hotel_id){
        char * hotel_id = NULL;
        
        hotel_id = strdup(reserv->hotel_id);
        return hotel_id;
    }
    return NULL;
}


void setReservHotelName(Reservation * reserv,const char * line){
    if(!reserv) return;
    if(reserv->hotel_name){
        ffree((void **) &reserv->hotel_name);
        reserv->hotel_name = strdup(line);
    }
    reserv->hotel_name = strdup(line);
}

char *getReservHotelName(Reservation * reserv){
    if(!reserv) return NULL;
    if(reserv->hotel_name){
        char * name = strdup((const char *)reserv->hotel_name);
        return name;
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

const unsigned int getReservRating(const Reservation * reserv){
    return (const unsigned int) reserv->rating;
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
    char * reservId = getReservId(src);                     setReservId(dest,reservId);                     ffree((void **) &reservId);
    char * reservUserId = getReservUserId(src);             setReservUserId(dest,reservUserId);             ffree((void **) &reservUserId);
    char * reservHotelId = getReservHotelId(src);           setReservHotelId(dest,reservHotelId);           ffree((void **) &reservHotelId);
    char * reservHotelName = getReservHotelName(src);       setReservHotelName(dest,reservHotelName);       ffree((void **) &reservHotelName);
    char * reservHotelAddress = getReservHotelAddress(src); setReservHotelAddress(dest,reservHotelAddress); ffree((void **) &reservHotelAddress);
    char * reservRoomDetails = getReservRoomDetails(src);   setReservRoomDetails(dest,reservRoomDetails);   ffree((void **) &reservRoomDetails);
    char * reservComment = getReservComment(src);           setReservComment(dest,reservComment);           ffree((void **) &reservComment);
    Time * reservBeginDate = getReservBeginDate(src);       setReservBeginDate(dest,reservBeginDate);       ffree((void **) &reservBeginDate);
    Time * reservEndDate = getReservEndDate(src);           setReservEndDate(dest,reservEndDate);           ffree((void **) &reservEndDate);


    setReservHotelStars(dest,getReservHotelStars(src));
    setReservCityTax(dest,getReservCityTax(src));
    setReservPricePerNight(dest,getReservPricePerNight(src));
    setReservBreakfast(dest,getReservBreakfast(src));
    setReservRating(dest,getReservRating(src));


}


