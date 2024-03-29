#ifndef FINDER_H
#define FINDER_H
#include "../include/database.h"
#include "../include/passengers.h"
#include "../include/utils.h"
#include "../include/singularRecord.h"
#include "../include/temporary.h"
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

/**
 * @brief Function that aplies a secondary function to every element of a database
 * @param database Pointer to the desired database
 * @param wantedString A string that will be used in the search of the elements
 * @param begin A pointer to limit the dates to after or commencing on the date
 * @param end A pointer to limit the dates to prior this date
 * @param function The function to be applied to the elements of the database
 * @return A struct with everything needed
*/
Temporary * getAListOfSomething(void * ,const char * ,Time * ,Time * ,void (*func)());


int countUserFlights(void *,const char *);

/**
 * @brief Function to search all the flights user went on
 * @param flights Database of all flights
 * @param passengers Database of all passengers
 * @param id Id of the user that is the reference
 * @return A struct containing the list and some more information
*/
Temporary * getUserFlights(void * ,void * ,const char * );

/**
 * @brief Function to get all passengers that went on the flight
 * @param flights Database of all flights
 * @param travels Database of all passengers
 * @param id Id of the flight that is the reference
 * @return A struct containing the list and some more information
*/
Temporary * getFlightPassengers(void * ,void * ,const char * );


void countHotelReservs(gpointer,gpointer,gpointer);


/**
 * @brief Sees if the reservation belongs to the desired hotel
*/
void allHotelReservs(gpointer, gpointer, gpointer);

/**
 * @brief Checks if the reservations belongs to an user
*/
void allUserReservs(gpointer ,gpointer,gpointer);
/**
 * @brief Checks if the flight departures from a certain airport
*/
void checkAirports(gpointer,gpointer,gpointer);

/**
 * @brief Grabs a list of names of airports and the amount of 
 * passengers the airport has had in a year
 * @param flights Pointer to the flights database
 * @param passengers Pointer to the passengers database
 * @param year Year which the flights must be from
 * @return Pointer to an SingularRecord structure with the list of
 * airport names and the respective number of passengers
*/
SingularRecord * getYearFlights(const void *,const void *, int);

/**
 * @brief If the flight is from the selected year, it is added to the list
 * and the number of passengers in the selected year
*/
void yearFlight(gpointer, gpointer, gpointer);

/**
 * @brief Counts the amount of passengers on the airports on the selected year
 * @param passengers Pointer to the passengers database
 * @param flights Pointer to the flights database
 * @param record Pointer to the table to be filled
 * @param year Year selected
 * @return Number of passengers on the flight 
*/
void countFPassengers(const void * ,const void *,void * ,int );

/**
 * @brief Gets a structure with a list of names 
 * @param flights Pointer to the flights database
 * @return Pointer to the structure with the names of the airports
 * and the respective median of the flight delays
*/
SingularRecord * getDelays(void *);

/**
 * @brief Adds the delay of the flight to the respective airport 
*/
void getAirportsDelays(gpointer,gpointer,gpointer);

/**
 * @brief Gets a temporary struct with all the ids and names of the users, whose names 
 * match the prefix selected
 * @param users Pointer to the users Database
 * @param prefix Prefix to compared with the names
*/
Temporary * getUsersPre(void *, char *);

/**
 * @brief Compares the user name to the pretended prefix storing if they match
*/
void checkPre(gpointer, gpointer, gpointer);

#endif