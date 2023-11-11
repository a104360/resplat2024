#ifndef CATALOGS_H
#define CATALOGS_H
#include "../include/dataTypes.h"
#include <glib.h>





static GHashTable * UsersDataBase();

static void insertUser(void *,User *);

static User * lookupUser(void *,const char *);





static GHashTable * FlightsDataBase();

static void insertFlight(void *,Flight *);

static Flight * lookupFlight(void * ,const char *);

static double dalayMedianAirport(void*, void*);





static GHashTable * ReservationsDataBase();

static void insertReserv(void *,Reservation *);

static Reservation * lookupReserv(void * ,const char * );

static Reservation * lookupReservHotel(void * ,const char * );

static Reservation * lookupReservUser(void * ,const char * );




static GHashTable * PassangersDataBase();

static void insertPassangerFlightId(void * ,Passanger * );
static void insertPassangerUserId(void * ,Passanger * );


static Passanger * lookupPassangerFlightId(void * ,const char * );
static Passanger * lookupPassangerUserId(void * ,const char * );



static void destroyDataBase(void *);




static gint compareTimes(Time *,Time*,char *,char *);
static gint comparePassangers(gint,gint);
static gint compareMedian(gdouble,gdouble);
static gint compareNames(char *,char*);


static GTree * UsersAnalysisCatalog();

static void UsersAnalysisCatalogInsert(void *,void *);




static GTree * FlightsAnalysisCatalog();




static GTree * ReservationsAnalysisCatalog();




static GTree * PassangerAnalysisCatalog();



#endif