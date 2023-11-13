#ifndef CATALOGS_H
#define CATALOGS_H
#include "../include/dataTypes.h"
#include <glib.h>


typedef GHashTable * UsersDatabase;
typedef GHashTable * FlightsDatabase;
typedef GHashTable * ReservationsDatabase;
typedef GHashTable * PassangersDatabase;


typedef GList * UserSearchResults;
typedef GList * FlightSearchResults;
typedef GList * ReservationSearchResults;
typedef GList * PassangerSearchResults;



static UsersDatabase initUsers();

static void insertUser(void *,User *);

static User * lookupUser(void *,const char *);





static FlightsDatabase initFlights();

static void insertFlight(void *,Flight *);

static Flight * lookupFlight(void * ,const char *);





static ReservationsDatabase initReservations();

static void insertReserv(void *,Reservation *);

static Reservation * lookupReserv(void * ,const char * );

static Reservation ** findHotelReservations(void * ,const char *);

static Reservation * findReservUser(void * ,const char * );




static PassangersDatabase initPassangers();

static void insertPassangerFlightId(void * ,Passanger * );

static Passanger * lookupPassangerFlightId(void * ,const char * );
static Passanger * findPassangerUserId(void * ,const char * );



static void destroyDataBase(void *);








#endif