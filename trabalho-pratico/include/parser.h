#ifndef PARSER_H
#define PARSER_H
#include <time.h>
#include <stdbool.h>
#include "../include/dataTypes.h"


static int yearCheck(const char * );

static int monthCheck(const char * );

static int dayCheck(const char * );

static struct tm * dateCheck(const char * );

static bool datesCheck(const char * , const char * );

static int hourCheck(const char * );

static int minuteCheck(const char *);

static int secondsCheck(const char *);

static bool hoursCheck(const char * , const char * );

static bool emailCheck(const char * );

static bool countryCheck(const char * );

static bool accStatusCheck(const char * );

static bool seatsCheck(const char * , const char * );

static bool airportCheck(const char * ,const char * );

static bool hotelStarsCheck(const char * );

static bool taxCheck(const char * );

static bool pricePNightCheck(const char * );

static bool breakfastCheck(const char * );

static bool reviewCheck(const char * );



static bool lengthCheck(void ** line);

static bool userCheck(const char * );

static bool reservationCheck(const char * );

static bool flightCheck(const char * );

static bool passangerCheck(const char * );


static User * userAdd(const char *);

static Reservation * reservationAdd(const char *);

static Flight * fligthAdd(const char *);

static Passanger * passangerAdd(const char *);

#endif