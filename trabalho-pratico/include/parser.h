#ifndef PARSER_H
#define PARSER_H
#include <time.h>
#include <stdbool.h>
#include "../include/dataTypes.h"



static bool dateCheck(char * );


static bool datesCheck(char * , char * );


static bool hourCheck(char * );


static bool hoursCheck(char * , char * );


static bool emailCheck(char * );


static bool countryCheck(char * );


static bool accStatusCheck(char * );


static bool seatsCheck(char * , char * );


static bool airportCheck(char * ,char * );


static bool hotelStarsCheck(char * );


static bool taxCheck(char * );


static bool pricePNightCheck(char * );


static bool breakfastCheck(char * );


static bool reviewCheck(char * );



static bool lengthCheck(void ** line);

static bool userCheck(char * );

static bool reservationCheck(char * );

static bool flightCheck(char * );

static bool passangerCheck(char * );

#endif