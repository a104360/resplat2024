#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "../include/utils.h"
#include "../include/user.h" 
#include "../include/reservation.h"
#include "../include/flight.h"
#include "../include/passengers.h"

int verTamanhoLinha(const char *);

/**
 * @brief Removes the ' " ' characters from the string
 * @param token String with ' " ' characters on the beggining and the end
 * @return String that is not between ' " ' characters.  
*/
char * limpaToken(char *);

Time * firstDateQ5(const char *);

Time * secondDateQ5(const char *);

Time * firstDateQ8(const char *);

Time * secondDateQ8(const char *);

/**
 * @brief Gets the fist argument of the input (commands) lines
 * @param line String (pointer to the first character)
 * @return The first parameter of the command line, next to the query number
*/
char * airportName(const char *);

/**
 * @brief Reads the inputs text file with the commands and executes them by calling the respective queries
 * @param Users Pointer to user's database 
 * @param Reservations Pointer to Reservations's database 
 * @param Flights Pointer to Flights's database 
 * @param Passengers Pointer to Passengers's database 
 * @param argc Number of arguments 
 * @param argv Array of arguments provinient of the main function
*/
void readEntryFile(const Users *,const Reservations *,const Flights *,const Passengers *,int, char **);

#endif