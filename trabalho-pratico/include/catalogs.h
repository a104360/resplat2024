#ifndef CATALOGS_H
#define CATALOGS_H
#include "../include/dataTypes.h"
#include <glib.h>


typedef GHashTable * UsersDatabase;
typedef GHashTable * FlightsDatabase;
typedef GHashTable * ReservationsDatabase;
typedef GHashTable * PassangersDatabase;



static UsersDatabase initUsers();

static void insertUser(void *,User *);

static User * lookupUser(void *,const char *);





static FlightsDatabase initFlights();

static void insertFlight(void *,Flight *);

static Flight * lookupFlight(void * ,const char *);





static ReservationsDatabase initReservations();

static void insertReserv(void *,Reservation *);

static Reservation * lookupReserv(void * ,const char * );

static Reservation * findReservHotel(void * ,const char * );

static Reservation * findReservUser(void * ,const char * );




static PassangersDatabase initPassangers();

static void insertPassangerFlightId(void * ,Passanger * );

static Passanger * lookupPassangerFlightId(void * ,const char * );
static Passanger * findPassangerUserId(void * ,const char * );



static void destroyDataBase(void *);





static gint compareTimes(Time *,Time*,char *,char *);
static gint comparePassangers(gint,gint);
static gint compareMedian(gdouble,gdouble);
static gint compareNames(char *,char*);


static GArray * UsersAnalysisCatalog();

static void UsersAnalysisCatalogInsert(void *,void *);




static GArray * FlightsAnalysisCatalog();




static GArray * ReservationsAnalysisCatalog();




static GArray * PassangerAnalysisCatalog();



#endif