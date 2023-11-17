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








ReservationsDatabase initReservations();

void insertReserv(void *,Reservation *);

Reservation * lookupReserv(void * ,const char * );










typedef struct hotelDatabase HotelDatabase;

int getSumRatings(void *);

int getNumReservas(void *);

Reservation ** getAllHotelReservs(const HotelDatabase *);

HotelDatabase * getHotelDataBase(void *,const char *,Time *,Time *);

void allHotelReservs(gpointer , gpointer , gpointer );

void destroyHotelDatabase(HotelDatabase *);











typedef struct userReservsDB UserReservsDB;

UserReservsDB * getUserReservsDB(void *,const char *);

Reservation ** getUserReservs(const UserReservsDB *);

int getNumReservs(const UserReservsDB *);

void allUserReservs(gpointer,gpointer,gpointer);

void destroyUserReservsDB(UserReservsDB *);




typedef struct userFlightsDB UserFlightsDB;

UserFlightsDB * getUserFlightsDB(void *,void *,const char *);

Flight ** getUserFlights(const UserFlightsDB *);

int getNumFlights(const UserFlightsDB *);

void destroyUserFlightsDB(UserFlightsDB *);




typedef struct flightPassangers FlightPassangers;

FlightPassangers * getFlightPassangers(void *,void *,const char *);

int getNumPassangers(const FlightPassangers *);

Passanger ** getFlightPassangersBook(const FlightPassangers *);

void destroyFlightPassangers(FlightPassangers *);




typedef struct airportDB AirportDB;

AirportDB * getAirportDB(FlightsDatabase,const char *,Time *,Time *);

void checkAirports(gpointer,gpointer,gpointer);

int getNumAirportFlights(AirportDB *);

Flight ** getAirportFlights(AirportDB *);

void destroyAirport(AirportDB * db);


void destroyDataBase(void *);





#endif