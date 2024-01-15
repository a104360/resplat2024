#ifndef PARSER_H
#define PARSER_H
#include <stdbool.h>
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/passenger.h"
#include "../include/passengers.h"
#include "../include/time.h"

/**
 * @brief Checks if the id is valid
 * @param id Id of something
*/
char * idCheck(const char *);


/**
 * @brief Checks if the name is valid
 * @param name Name of something
*/
char * nameCheck(const char *);

/**
 * @brief Checks if the phone number is valid
 * @param phone Phone number string
*/
char * phoneNumberCheck(const char *);

/**
 * @brief Checks if the sex character is valid
 * @param sex Sex char
*/
char sexCheck(const char *);

/**
 * @brief Checks if the passport is valid
 * @param passport Passport string 
*/
char * passportCheck(const char *);

/**
 * @brief Checks if the address is valid 
 * @param address Adress string
*/
char * addressCheck(const char *);

/**
 * @brief Checks if the payment method is valid
 * @param payMethod Payment method string
*/
char * pay_methodCheck(const char *);

/**
 * @brief Checks if the year is valid
 * @param year date string
*/
int yearCheck(const char * );
/**
 * @brief Checks if the month is valid
 * @param month month string
*/
int monthCheck(const char * );
/**
 * @brief Checks if the day is valid
 * @param day day string
*/
int dayCheck(const char * );
/**
 * @brief Checks if the date is valid
 * @param date Date string
*/
Time * dateCheck(const char * );

/**
 * @brief Checks if the first param date is previous to the second param
 * @param start The more ancient date
 * @param end The more recent date
 * @return If start happened before end
*/
bool datesCheck(const char * , const char *);

/**
 * @brief Checks if the hour is valid
 * @param hour Hours string
*/
int hourCheck(const char *);

/**
 * @brief Checks if the minute is valid
 * @param minute Minutes string
*/
int minuteCheck(const char *);

/**
 * @brief Checks if the seconds is valid
 * @param seconds Seconds string
*/
int secondsCheck(const char *);

/**
 * @brief Checks if the first date happens after the second date
 * @param departure First date
 * @param arrival Second date
 * @return The verification of the correctness of the dates
*/
bool hoursCheck(const char * , const char *);

/**
 * @brief Checks if the email is valid
 * @param email Email string
*/
char * emailCheck(const char * );

/**
 * @brief Checks if the country name is valid
 * @param country Country name string
*/
char * countryCheck(const char * );

/**
 * @brief Checks if the status of the account is valid
 * @param status Account status string
*/
char * accStatusCheck(const char * );

/**
 * @brief Checks if the number of seats is valid
 * @param seats Number of seats string
*/
unsigned int seatsCheck(const char *);

/**
 * @brief Checks if the departure and the arrival airport are not the same
 * @param departureAirport Departure airport name
 * @param arrivalAirport Arrival airport name
*/
bool airportCheck(const char * ,const char * );

/**
 * @brief Checks if the hotel stars is valid
 * @param hotelStars Hotel stars string
*/
unsigned int hotelStarsCheck(const char *);

/**
 * @brief Checks if the tax value is valid
 * @param tax Tax string
*/
int taxCheck(const char * );

/**
 * @brief Checks if the price per night of the hotel is valid
 * @param price Hotel night price string
*/
double pricePNightCheck(const char * );

/**
 * @brief Checks if the breakfast tag is valid
 * @param breakfast Breakfast string
*/
int breakfastCheck(const char * );

/**
 * @brief Checks if the review is valid
 * @param review Review string
*/
unsigned int reviewCheck(const char *);


/**
 * @brief Checks if an user is valid
 * @param line User informations
 * @return Pointer to user or NULL pointer
*/
User * userCheck(const char *);

/**
 * @brief Checks if an reservation is valid
 * @param line reservation informations
 * @return Pointer to reservation or NULL pointer
*/
Reservation * reservationCheck(const char *,Users *);

/**
 * @brief Checks if an flight is valid
 * @param line flight informations
 * @return Pointer to flight or NULL pointer
*/
Flight * fligthCheck(const char *);

/**
 * @brief Checks if an passenger is valid
 * @param line passenger informations
 * @return Pointer to passenger or NULL pointer
*/
Passenger * passengerCheck(const char *,Users *,Flights *);

/**
 * @brief Validates the csv files and creates the users database
 * @param folder Path to the folder
 * @return Pointer to the created database
*/
Users * validateUsers(const char *);

/**
 * @brief Validates the csv files and creates the reservations database
 * @param users Pointer to the users database
 * @param folder Path to the folder
 * @return Pointer to the created database
*/
Reservations * validateReservations(Users *,const char *);

/**
 * @brief Validates the csv files and creates the flights database
 * @param folder Path to the folder
 * @return Pointer to the created database
*/
Flights * validateFlights(const char *);

/**
 * @brief Validates the csv files and creates the passengers database
 * @param users Pointer to the users database
 * @param flights Pointer to the flights database
 * @param folder Path to the folder
 * @return Pointer to the created database
*/
Passengers * validatePassengers(Users *, Flights *,const char *);


#endif