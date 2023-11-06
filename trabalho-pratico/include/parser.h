#ifndef PARSER_H
#define PARSER_H
#include <time.h>
#include <stdbool.h>
#include "../include/dataTypes.h"


static int * idCheck(const char *);

static char * nameCheck(const char *);

static char * phoneNumberCheck(const char *);

static bool sexCheck(const char *);

static char * passaportCheck(const char *);

static char * addressCheck(const char *);

static unsigned int pay_methodCheck(const char *);

static int yearCheck(const char * );

static int monthCheck(const char * );

static int dayCheck(const char * );

static Time * dateCheck(const char * );

static bool datesCheck(const char *);

static int hourCheck(const char *);

static int minuteCheck(const char *);

static int secondsCheck(const char *);

static bool hoursCheck(const char * , const char *);

static char * emailCheck(const char * );

static char * countryCheck(const char * );

static bool accStatusCheck(const char * );

static bool seatsCheck(const char * , const char * );

static bool airportCheck(const char * ,const char * );

static int hotelStarsCheck(const char * );

static double taxCheck(const char * );

static double pricePNightCheck(const char * );

static bool breakfastCheck(const char * );

static int reviewCheck(const char * );


static User * userCreate(const char *);

static Reservation * reservationCreate(const char *);

static Flight * fligthCreate(const char *);

static Passanger * passangerCreate(const char *);


#endif