#ifndef CATALOGS_H
#define CATALOGS_H
#include "../include/dataTypes.h"
#include <glib.h>


typedef GHashTable * UsersDatabase;
typedef GHashTable * FlightsDatabase;
typedef GHashTable * ReservationsDatabase;
typedef struct flightBook FlightBook;



UsersDatabase initUsers();

void insertUser(void *,User *);

User * lookupUser(void *,const char *);





FlightsDatabase initFlights();

void insertFlight(void *,Flight *);

Flight * lookupFlight(void * ,const char *);





void initFlightBook(void *);

FlightBook * createFlightBook();

void insertPassanger(void * ,void *);

char * isUserOnFlight(void * voo,void * userData);




ReservationsDatabase initReservations();

void insertReserv(void *,Reservation *);

Reservation * lookupReserv(void * ,const char * );

Reservation ** findHotelReservations(void * ,const char *);

Reservation * findReservUser(void * ,const char * );




void destroyDataBase(void *);








#endif