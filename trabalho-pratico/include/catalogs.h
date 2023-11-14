#ifndef CATALOGS_H
#define CATALOGS_H
#include "../include/dataTypes.h"
#include <glib.h>


typedef GHashTable * UsersDatabase;
typedef GHashTable * FlightsDatabase;
typedef GHashTable * ReservationsDatabase;



UsersDatabase initUsers();

void insertUser(void *,User *);

User * lookupUser(void *,const char *);





FlightsDatabase initFlights();

void insertFlight(void *,Flight *);

Flight * lookupFlight(void * ,const char *);



typedef struct flightBook FlightBook;

int getNumPassangers(const FlightBook *);

Passanger ** getFlightPassangers(const FlightBook *);

FlightBook * getFlightBook(void *, const char *);

void getPassangers(gpointer,gpointer,gpointer);

void destroyFlightBook(FlightBook *);



ReservationsDatabase initReservations();

void insertReserv(void *,Reservation *);

Reservation * lookupReserv(void * ,const char * );




typedef struct hotelDatabase HotelDatabase;

int getSumRatings(void *);

int getNumReservas(void *);

Reservation ** getAllHotelReservs(const HotelDatabase *);

HotelDatabase * getHotelDataBase(void * ,const char * );

void allHotelReservs(gpointer , gpointer , gpointer );

void destroyHotelDatabase(HotelDatabase *);




typedef struct userReservsDB UserReservsDB;

UserReservsDB * getUserReservsDB(void *,const char *);

Reservation ** getUserReservs(const UserReservsDB *);

int getNumReservs(const UserReservsDB *);

void allUserReservs(gpointer,gpointer,gpointer);

void destroyUserReservsDB(UserReservsDB *);


void destroyDataBase(void *);





#endif