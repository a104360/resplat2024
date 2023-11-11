#ifndef CATALOGS_H
#define CATALOGS_H
#include "../include/dataTypes.h"
#include <glib.h>

static GHashTable * Users();

static void insertUser(void *,User *);

static User * lookupUser(void *,const char *);





static GHashTable * Flights();

static void insertFlight(void *,Flight *);

static Flight * lookupFlight(void * ,const char *);





static GHashTable * Reservations();

static void insertReserv(void *,Reservation *);

static Reservation * lookupReserv(void * ,const char * );

static Reservation * lookupReservHotel(void * ,const char * );

static Reservation * lookupReservUser(void * ,const char * );




static GHashTable * Passangers();

static void insertPassangerFlightId(void * ,Passanger * );
static void insertPassangerUserId(void * ,Passanger * );


static Passanger * lookupPassangerFlightId(void * ,const char * );
static Passanger * lookupPassangerUserId(void * ,const char * );



static void destroyCatalog(void *);

#endif