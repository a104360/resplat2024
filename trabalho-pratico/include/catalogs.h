#ifndef CATALOGS_H
#define CATALOGS_H
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/passenger.h"
#include <glib.h>


typedef GHashTable * UsersDatabase;
typedef GHashTable * FlightsDatabase;
typedef GHashTable * ReservationsDatabase;



UsersDatabase initUsers();

void insertUser(void *,User *);

User * lookupUser(void *,const char *);

void destroyUsers(UsersDatabase);





FlightsDatabase initFlights();

void insertFlight(void *,Flight *);

Flight * lookupFlight(void * ,const char *);

void destroyFlights(FlightsDatabase);







ReservationsDatabase initReservations();

void insertReserv(void *,Reservation *);

Reservation * lookupReserv(void * ,const char * );

void destroyReservs(ReservationsDatabase);








typedef struct hotelDatabase HotelDatabase;

int getSumRatings(void *);

int getNumReservas(void *);

Reservation ** getAllHotelReservs(const HotelDatabase *);

HotelDatabase * getHotelDataBase(void *,const char *,Time *,Time *);

void allHotelReservs(gpointer , gpointer , gpointer );

void destroyHotelDatabase(HotelDatabase *);











typedef struct userReservsDB UserReservsDB;

UserReservsDB * getUserReservsDB(const void *,const char *);

Reservation ** getUserReservs(const UserReservsDB *);

int getNumReservs(const UserReservsDB *);

void allUserReservs(gpointer,gpointer,gpointer);

void destroyUserReservsDB(UserReservsDB *,int);




typedef struct userFlightsDB UserFlightsDB;

UserFlightsDB * getUserFlightsDB(void *,void *,const char *);

Flight ** getUserFlights(const UserFlightsDB *);

int getNumFlights(const UserFlightsDB *);

void destroyUserFlightsDB(UserFlightsDB *,int);




typedef struct flightPassengers FlightPassengers;

FlightPassengers * getFlightPassengers(void *,void *,const char *);

int getNumPassengers(const FlightPassengers *);

Passenger ** getFlightPassengersBook(const FlightPassengers *);

void destroyFlightPassengers(FlightPassengers *,int);




typedef struct airportDB AirportDB;

AirportDB * getAirportDB(const FlightsDatabase,const char *,Time *,Time *);

void checkAirports(gpointer,gpointer,gpointer);

int getNumAirportFlights(AirportDB *);

Flight ** getAirportFlights(AirportDB *);

void destroyAirport(AirportDB * db,int hashSize);



typedef struct airportPassengers AirportPassengers;

char ** getAirportPassengersAirportName(AirportPassengers *);

int * getAirportPassengersPassengers(AirportPassengers *);

typedef struct yearFlights YearFlights;

AirportPassengers * getYearFlights(const void *,const void *, const int);

void yearFlight(gpointer, gpointer, gpointer);

int countFPassengers(const char *,const void *);

typedef struct usersIdQ9 UsersIdQ9;

UsersIdQ9 * prefixQ9(const void *, char *);

void checkPrefix(gpointer, gpointer, gpointer);

int getUsersIdQ9NumIds (UsersIdQ9 * data);

char ** getUsersIdQ9Ids (UsersIdQ9 * data, int num);

#endif