#ifndef DATATYPES_H
#define DATATYPES_H
#include <stdbool.h>
#include <glib.h>

typedef struct time Time;

typedef struct user User;

typedef struct flight Flight;

typedef struct reservation Reservation;

typedef struct passanger Passanger;




static Time * createTime();

static void initTime(Time *);

static void setTime(Time *,int,int,int,int,int,int);

static void copyTime(Time *,Time *);

static void destroyTime(Time *); 



static User * createUser();

static void initUser(User *);

static void destroyUser(User *);



static Flight * createFlight();

static void initFlight(Flight *);

static void destroyFlight(Flight *);



static Reservation * createReservation();

static void initReservation(Reservation *);

static void destroyReservation(Reservation *);




static Passanger * createPassanger();

static void initPassanger(Passanger *);

static void destroyPassanger(Passanger *);





static void setUserId(User *, const char *);
static char * getUserId(User *);

static void setUserName(User *, const char *);
static char * getUserName(User *);

static void setUserEmail(User *, const char *);
static char * getUserEmail(User *);

static void setUserPhone(User *,const char *);
static char * getUserPhone(User *);

static void setUserBday(User *,Time *);
static Time * getUserBday(User *);

static void setUserSex(User *, const char);
static char getUserSex(User *);

static void setUserPassport(User *, const char *);
static char * getUserPassaport(User *);

static void setUserCountryCode(User *, const char *);
static char * getUserCountryCode(User *);

static void setUserAddress(User *, const char *);
static char * getUserAddress(User *);

static void setUserAccountCreation(User *,Time *);
static Time * getUserAccountCreation(User *);

static void setUserPayMethod(User *, const char *);
static char * getUserPayMethod(User *);

static void setUserAccountStatus(User *, const bool);
static bool getUserAccountStatus(User *);














static void setFlightId(Flight *, const char *);
static char * getFlightId(Flight *);
    
static void setFlightAirline(Flight *,const char *);
static char * getFlightAirline(Flight *);

static void setFlightPlaneModel(Flight *, const char *);
static char * getFlightPlaneModel(Flight *);

static void setFlightTotalSeats(Flight *,const unsigned int);
static unsigned int getFlightTotalSeats(Flight *);

static void setFlightOrigin(Flight *, const char *);
static char * getFlightOrigin(Flight *);

static void setFlightDestination(Flight *, const char *);
static char * getFlightDestination(Flight *);

static void setFlightSDepartureDate(Flight *,Time *);
static Time * getFlightSDepartureDate(Flight *);

static void setFlightSArrivalDate(Flight *,Time *);
static Time * getFlightSArrivalDate(Flight *);

static void setFlightRDepartureDate(Flight *, Time *);
static Time * getFlightRDepartureDate(Flight *);

static void setFlightRArrivalDate(Flight *,Time *);
static Time * getFlightRArrivalDate(Flight *);

static void setFlightPilot(Flight *, const char *);
static char * getFlightPilot(Flight *);

static void setFlightCopilot(Flight *, const char *);
static char * getFlightCopilot(Flight *);

static void setFlightNotes(Flight *, const char *);
static char * getFlightNotes(Flight *);













static void setReservId(Reservation *, const char *);
static char * getReservId(Reservation *);

static void setReservUserId(Reservation *,const char *);
static char * getReservUserId(Reservation *);

static void setReservHotelId(Reservation *,const char *);
static char * getReservHotelId(Reservation *);

static void setReservHotelName(Reservation *, const char *);
static char * getReservHotelName(Reservation *);

static void setReservHotelStars(Reservation *,const unsigned int);
static unsigned int getReservHotelStars(Reservation *);

static void setReservCityTax(Reservation *,const double);
static double getReservCityTax(Reservation *);

static void setReservHotelAddress(Reservation *,const char *);
static char *getReservHotelAddress(Reservation *);

static void setReservBeginDate(Reservation*,Time *);
static Time *getReservBeginDate(Reservation *);

static void setReservEndDate(Reservation *,Time *);
static Time *getReservEndDate(Reservation *);

static void setReservPricePerNight(Reservation *,const double);
static double getReservPricePerNight(Reservation *);

static void setReservBreakfast(Reservation *, const bool);
static bool getReservBreakfast(Reservation *);

static void setReservRoomDetails(Reservation *, const char *);
static char *getReservRoomDetails(Reservation *);

static void setReservRating(Reservation *,const unsigned int);
static unsigned int getReservRating(Reservation *);

static void setReservComment(Reservation *, const char *);
static char *getReservComment(Reservation *);







static void setPassangerFlightId(Passanger *, const char *);
char *getPassangerFlightId(Passanger *);

static void setPassangerUserId(Passanger *, const char *);
char *getPassangerUserId(Passanger *);





static Reservation * lookupReservUser(gpointer , gpointer , gpointer );

static Reservation * lookupReservHotel(gpointer , gpointer , gpointer );

static Passanger * lookupPassangerUserId(gpointer , gpointer , gpointer );


static double dalayMedianAirport(void*, void*);


#endif