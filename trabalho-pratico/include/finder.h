#ifndef FINDER_H
#define FINDER_H
#include "../include/database.h"
#include "../include/passengers.h"
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
Temporary * getAListOfSomething(void * database,const char * hotelId,Time * begin,Time * end,void (*func)());


/**
 * @brief Function to search all the flights user went on
 * @param flights Database of all flights
 * @param passengers Database of all passengers
 * @param id Id of the user that is the reference
 * @return A struct containing the list and some more information
*/
Temporary * getUserFlights(void * fDatabase,void * travels,const char * userId);

/**
 * @brief Function to get all passengers that went on the flight
 * @param flights Database of all flights
 * @param travels Database of all passengers
 * @param id Id of the flight that is the reference
 * @return A struct containing the list and some more information
*/
Temporary * getFlightPassengers(void * fDatabase,void * travels,const char * flightId);

/**
 * @brief Sees if the reservation belongs to the desired hotel
*/
void allHotelReservs(gpointer key, gpointer value, gpointer hotelData);

/**
 * @brief Checks if the reservations belongs to an user
*/
void allUserReservs(gpointer key ,gpointer value,gpointer userData);
/**
 * @brief Checks if the flight departures from a certain airport
*/
void checkAirports(gpointer key,gpointer value,gpointer flightData);

#endif