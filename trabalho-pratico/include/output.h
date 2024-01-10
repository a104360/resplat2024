#ifndef OUTPUT_H
#define OUTPUT_H
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/passenger.h"
#include "../include/singularRecord.h"
#include <stdbool.h>

/**
 * @brief Writes on a file the outputs of the query 1, refering to a user
 * @param F Integer that tells the mode of the command/output
 * @param name Name of the user
 * @param sex Sex of the user
 * @param Age Age of the user
 * @param countryCode Country code of the user
 * @param passport passport of the user
 * @param numberOfFlights number of flights of the user
 * @param numberOfReservations Number of reservations of the user
 * @param totalSpent Total spent by the user
*/
void outputQ1User(int , char * , char , int , char * , char * , char * , char * , char * );

/**
 * @brief Writes on a file the outputs of the query 1, refering to a flight
 * @param F Integer that tells the mode of the command/output
 * @param airline Name of the flight airline
 * @param planeModel Name of the flight plane model
 * @param origin Origin of the flight
 * @param destination Destination of the flight
 * @param scheduleDepartureDate Schedule departure date of the flight
 * @param ScheduleArrivalDate Schedule arrival date of the flight
 * @param passengers Number of passengers of the flight
 * @param delay Delay the flight
*/
void outputQ1Flight(int , char * , char * , char * , char * , char * , char * , int , int);

/**
 * @brief Writes on a file the outputs of the query 1, refering to a reservation
 * @param F Integer that tells the mode of the command/output
 * @param hotelId Hotel id of the reservation
 * @param hotelName Hotel name of the reservation
 * @param hotelStars Hotel stars of the reservation
 * @param beginDate Begin date of the reservation
 * @param endDate End date of the reservation
 * @param Breakfast Breakfast of the reservation
 * @param nights Number of nights of the reservation
 * @param totalPrice Total price the reservation
*/
void outputQ1Reservation(int , char * , char * , int , char * , char * , bool, int , double);

/**
 * @brief Writes on a text file the outputs of the query 2
 * @param f Mode of the command/output
 * @param reservations Array of reservations 
 * @param n1 Number of reservations of the array
 * @param flights Array of Flights
 * @param n2 Number of flights on the array
*/
void outputQ2(bool,Reservation **,int, Flight **,int);

/**
 * @brief Writes on a text file the outputs of the query 3
 * @param f Mode of the command/output
 * @param rating Average rating of a hotel
*/
void outputQ3(bool,double);

/**
 * @brief Writes on a text file the outputs of the query 4
 * @param f Mode of the command/output
 * @param rList Array of reservations
 * @param max The number of reservations on the array
*/
void outputQ4(bool,Reservation **,int);

/**
 * @brief Writes on a text file the outputs of the query 5
 * @param f Mode of the command/output
 * @param fList Array of flights
 * @param max Number of flights on the array
*/
void outputQ5(bool,Flight **,int);

/**
 * @brief Writes on a text file the outputs of the query 5
 * @param f Mode of the command/output
 * @param n Number of sets to be displayed
 * @param names Array with the names of the airports
 * @param passengers Array with the passengers of each airport
*/
void outputQ6(bool,int,char **,int *);

/**
 * @brief Writes on a text file the outputs of the query 7
 * @param f Mode of the command/output
 * @param aux Auxiliar structure 
 * @param max Number of sets to be displayed
*/
void outputQ7(bool,SingularRecord * ,int);

/**
 * @brief Writes on a text file the outputs of the query 8
 * @param f Mode of the command/output
 * @param revenue Total profit of the hotel
*/
void outputQ8(bool,int);

void outputQ9(char **,char**,int,bool);

#endif