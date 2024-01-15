#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "../include/utils.h"
#include "../include/user.h" 
#include "../include/reservation.h"
#include "../include/flight.h"
#include "../include/passengers.h"

/**
 * @brief Removes the ' " ' characters from the string
 * @param token String with ' " ' characters on the beggining and the end
 * @return String that is not between ' " ' characters.  
*/
char * limpaToken(char *);

/**
 * @brief Gets the date for the query 5
 * @param line Formated string with the date
 * @return Pointer to the time struct that holds the date
*/
Time * dateQ5(const char *);

/**
 * @brief Gets the date for the query 5
 * @param line Formated string with the date
 * @return Pointer to the time struct that holds the date
*/
Time * dateQ8(const char *);

/**
 * @brief Gets the fist argument of the input (commands) lines
 * @param line String (pointer to the first character)
 * @return The first parameter of the command line, next to the query number
*/
char * airportName(const char *);

/**
 * @brief Gets the second argument of the input (command) lines
 * @param line String with the input line
 * @return The second parameter of the command line
*/
char * getSecondParam(const char *);

/**
 * @brief Reads the inputs text file with the commands and executes them by calling the respective queries
 * @param Users Pointer to user's database 
 * @param Reservations Pointer to Reservations's database 
 * @param Flights Pointer to Flights's database 
 * @param Passengers Pointer to Passengers's database 
 * @param argc Number of arguments 
 * @param argv Array of arguments provinient of the main function
*/
void readEntryFile(const Users *,const Reservations *,const Flights *,const Passengers *,int, char **,double *,int *);

/**
 * @brief Reads the inputs passed by the user on the interactive mode
 * @param Users Pointer to user's database 
 * @param Reservations Pointer to Reservations's database 
 * @param Flights Pointer to Flights's database 
 * @param Passengers Pointer to Passengers's database 
 * @param query Query to be executed
*/
void readQuery(const Users *,const Reservations *,const Flights *,const Passengers *,char *);

#endif