#ifndef PARSER_H
#define PARSER_H
#include <stdbool.h>
#include "../include/catalogs.h"
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/passenger.h"

char * idCheck(const char *);

char * nameCheck(const char *);

char * phoneNumberCheck(const char *);

char sexCheck(const char *);

char * passaportCheck(const char *);

char * addressCheck(const char *);

char * pay_methodCheck(const char *);

int yearCheck(const char * );

int monthCheck(const char * );

int dayCheck(const char * );

Time * dateCheck(const char * );

bool datesCheck(const char * , const char *);

int hourCheck(const char *);

int minuteCheck(const char *);

int secondsCheck(const char *);

bool hoursCheck(const char * , const char *);

char * emailCheck(const char * );

char * countryCheck(const char * );

char * accStatusCheck(const char * );

unsigned int seatsCheck(const char *);

bool airportCheck(const char * ,const char * );

unsigned int hotelStarsCheck(const char *);

int taxCheck(const char * );

double pricePNightCheck(const char * );

int breakfastCheck(const char * );

unsigned int reviewCheck(const char *);


User * userCheck(const char *);

Reservation * reservationCheck(const char *,UsersDatabase);

Flight * fligthCheck(const char *);

Passenger * passengerCheck(const char *,UsersDatabase,FlightsDatabase);


#endif