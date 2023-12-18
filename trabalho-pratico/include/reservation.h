#ifndef RESERVATION_H
#define RESERVATION_H
#include "../include/time.h"

typedef struct reservation Reservation;

Reservation * createReservation();

void initReservation(Reservation *);

void destroyReservation(Reservation *);


void setReservId(Reservation *, const char *);
char * getReservId(Reservation *);

void setReservUserId(Reservation *,const char *);
char * getReservUserId(Reservation *);

void setReservHotelId(Reservation *,const char *);
char * getReservHotelId(Reservation *);

void setReservHotelName(Reservation *, const char *);
char * getReservHotelName(Reservation *);

void setReservHotelStars(Reservation *,const unsigned int);
unsigned int getReservHotelStars(Reservation *);

void setReservCityTax(Reservation *,const int);
int getReservCityTax(Reservation * );

void setReservHotelAddress(Reservation *,const char *);
char *getReservHotelAddress(Reservation *);

void setReservBeginDate(Reservation*,Time *);
Time *getReservBeginDate(Reservation *);

void setReservEndDate(Reservation *,Time *);
Time *getReservEndDate(Reservation *);

void setReservPricePerNight(Reservation *,const double);
double getReservPricePerNight(Reservation *);

void setReservBreakfast(Reservation *, const bool);
bool getReservBreakfast(Reservation *);

void setReservRoomDetails(Reservation *, const char *);
char *getReservRoomDetails(Reservation *);

void setReservRating(Reservation *,const unsigned int);
const unsigned int getReservRating(const Reservation *);

void setReservComment(Reservation *, const char *);
char *getReservComment(Reservation *);

void copyReservation(Reservation *,Reservation *);

#endif