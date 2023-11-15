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




typedef struct passangersDB PassangersDatabase;

PassangersDatabase * createPassangerDatabase();

void insertPassanger(void * , void * );

int getNumAllPassangers(const PassangersDatabase * );

Passanger ** getAllUserPassages(const PassangersDatabase * ,char *);

void destroyPassangersDB(PassangersDatabase * );





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

HotelDatabase * getHotelDataBase(void * ,const char * );

void allHotelReservs(gpointer , gpointer , gpointer );

void destroyHotelDatabase(HotelDatabase *);











typedef struct userReservsDB UserReservsDB;

UserReservsDB * getUserReservsDB(void *,const char *);

Reservation ** getUserReservs(const UserReservsDB *);

int getNumReservs(const UserReservsDB *);

void allUserReservs(gpointer,gpointer,gpointer);

void destroyUserReservsDB(UserReservsDB *);




typedef struct userFlightsDB UserFlightsDB;

UserFlightsDB * getUserFlightsDB(void *,const char *);

Flight ** getUserFlights(const UserFlightsDB *);

int getNumFlights(const UserFlightsDB *);

void allUserFlights(gpointer,gpointer,gpointer);

void destroyUserFlightsDB(UserFlightsDB *);



void destroyDataBase(void *);





#endif