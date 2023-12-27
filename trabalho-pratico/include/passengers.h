#ifndef PASSENGERS_H
#define PASSENGERS_H

#include <stdbool.h>
#include "../include/passenger.h"

/**
 * @brief Passengers Database
*/
typedef struct passengers Passengers;

/**
 * @brief Allocates memory for the database and all it's fields
*/
Passengers * createPassengerDatabase();

/**
 * @brief Inserts a passenger into the database
 * @param dataStruct Pointer to the database
 * @param passengerData Pointer to the passenger to be put into the database
*/
void insertPassenger(void *,void *);

/**
 * @brief Get the total amount of passengers in the database
 * @param database Pointer to the database
 * @return How many passengers on the database
*/
int getNumAllPassengers(const Passengers *);

/**
 * @brief Search an passenger by the user Id
 * @param database Pointer to the database
 * @param id Id of the user needed
 * @return Pointer to the passenger
*/
Passenger * lookupPassengerUID(const Passengers *,const char *);

/**
 * @brief Search an passenger by the flight Id
 * @param database Pointer to the database
 * @param id Id of the flight needed
 * @return Pointer to the passenger
*/
Passenger * lookupPassengerFID(const Passengers *,const char *);

/**
 * @brief Gets the array of all passengers in the database
 * @param database Pointer to the passengers database
*/
Passenger ** getAllPassengers(const Passengers * );


/**
 * @brief Frees the database
 * @param database Pointer to the database
*/
void destroyPassengers(Passengers *);

#endif