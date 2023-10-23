#include "../include/parser.h"
#include <string.h>




// format : nnnn/nn/nn (0 <= n <= 9)
static bool dateCheck(char * line);

// starting dates cannot be after finishing dates
static bool datesCheck(char * start, char * end);

// format : nnnn/nn/nn nn:nn:nn | dateCheck && [0,23]:
static bool hourCheck(char * line);

// starting hours cannot be after finishing hours
static bool hoursCheck(char * departure, char * arrival);

// format : <username>@<domain>.<TLD> | username.length >= 1 , domain.length >= 2 , TDL.length >= 2
static bool emailCheck(char * line);

// format : LL (L is a letter)
static bool countryCheck(char * line);

// active vs inactive (all varitations)
static bool accStatusCheck(char * line);

// total_seats must not be less than the number of passangers
static bool seatsCheck(char * sold, char * plain);

// length == 3 && all variations
static bool airportCheck(char * departure,char * arrival);

// int stars : 1 <= starts <= 5
static bool hotelStarsCheck(char * line);

// int tax : 0 <= tax
static bool taxCheck(char * line);

// int price : 0 <= price
static bool pricePNightCheck(char * line);

// bool breakfast : if(false){"f","false",0,""} else {"t","true","1"}
static bool breakfastCheck(char * line);

// int rating : 1 <= rating <= 5
static bool reviewCheck(char * line);

// Check the length of some camps of the users, reservations and flights
static bool lengthCheck(void ** line);

static bool userCheck(char * line);

static bool reservationCheck(char * line);

static bool flightCheck(char * line);

static bool passangerCheck(char * line);