#ifndef DATATYPES_H
#define DATATYPES_H
#include <stdbool.h>
#include <stddef.h>
#include "../include/time.h"


typedef struct user User;

typedef struct flight Flight;

typedef struct reservation Reservation;

typedef struct passanger Passanger;


User * createUser();

void initUser(User *);

void destroyUser(User *);



Flight * createFlight();

void initFlight(Flight *);

void destroyFlight(Flight *);

size_t getFlightSize();



Reservation * createReservation();

void initReservation(Reservation *);

void destroyReservation(Reservation *);




Passanger * createPassanger();

void initPassanger(Passanger *);

void destroyPassanger(Passanger *);

size_t getPassangerSize();





void setUserId(User *, const char *);
char * getUserId(User *);

void setUserName(User *, const char *);
char * getUserName(User *);

void setUserEmail(User *, const char *);
char * getUserEmail(User *);

void setUserPhone(User *,const char *);
char * getUserPhone(User *);

void setUserBday(User *,Time *);
Time * getUserBday(User *);

void setUserSex(User *, const char);
char getUserSex(User *);

void setUserPassport(User *, const char *);
char * getUserPassport(User *);

void setUserCountryCode(User *, const char *);
char * getUserCountryCode(User *);

void setUserAddress(User *, const char *);
char * getUserAddress(User *);

void setUserAccountCreation(User *,Time *);
Time * getUserAccountCreation(User *);

void setUserPayMethod(User *, const char *);
char * getUserPayMethod(User *);

void setUserAccountStatus(User *, const bool);
bool getUserAccountStatus(User *);

int getUserAge(User *);

void copyUser(User *,User *);












void setFlightId(Flight *, const char *);
char * getFlightId(Flight *);
    
void setFlightAirline(Flight *,const char *);
char * getFlightAirline(Flight *);

void setFlightPlaneModel(Flight *, const char *);
char * getFlightPlaneModel(Flight *);

void setFlightTotalSeats(Flight *,const unsigned int);
unsigned int getFlightTotalSeats(Flight *);

void setFlightOrigin(Flight *, const char *);
char * getFlightOrigin(Flight *);

void setFlightDestination(Flight *, const char *);
char * getFlightDestination(Flight *);

void setFlightSDepartureDate(Flight *,Time *);
Time * getFlightSDepartureDate(Flight *);

void setFlightSArrivalDate(Flight *,Time *);
Time * getFlightSArrivalDate(Flight *);

void setFlightRDepartureDate(Flight *, Time *);
Time * getFlightRDepartureDate(Flight *);

void setFlightRArrivalDate(Flight *,Time *);
Time * getFlightRArrivalDate(Flight *);

void setFlightPilot(Flight *, const char *);
char * getFlightPilot(Flight *);

void setFlightCopilot(Flight *, const char *);
char * getFlightCopilot(Flight *);

void setFlightNotes(Flight *, const char *);
char * getFlightNotes(Flight *);

int getFlightDelay(Flight *);

void copyFlight(Flight *, Flight *);







size_t getReservSize();

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

void setReservCityTax(Reservation *,const double);
double getReservCityTax(Reservation *);

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
unsigned int getReservRating(Reservation *);

void setReservComment(Reservation *, const char *);
char *getReservComment(Reservation *);

void copyReservation(Reservation *,Reservation *);




void setPassangerFlightId(Passanger *, const char *);
char *getPassangerFlightId(Passanger *);

void setPassangerUserId(Passanger *, const char *);
char *getPassangerUserId(Passanger *);

void copyPassanger(Passanger *,Passanger *);

#endif