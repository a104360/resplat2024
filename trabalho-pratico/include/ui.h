#ifndef UI_H
#define UI_H
#include <ncurses.h>
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/passengers.h"
#include "../include/singularRecord.h"

/**
 * @brief Prints user details for Query 1
 * @param f Mode
 * @param name Username
 * @param sex User sex
 * @param age User age
 * @param countryCode Country code
 * @param passport Passport
 * @param flights Number of flights
 * @param seatNumber Number of reservations
 * @param cost Total speant
 */
void printQ1User(bool,char *,char,int,char *,char *,int,int,double);

void printQ1Flight(bool, char *, char *, char *,char *,char *,char *,int,int);

void printQ1Reservation(bool,char *,char *,int, char *, char *,bool,int,double);

/**
 * @brief Prints chuncks of the query 2
 * @param f Mode
 * @param command Number of the command to be displayed
 * @param npp Number of chunks per page
 * @param reservations Reservations to be displayed
 * @param n1 Number of reservations
 * @param rCount Index of reservations
 * @param flights Flights to be displayed
 * @param n2 Number of flights
 * @param fCount Index of flights
*/
void printQ2(bool,int *,int,Reservation **,int,int *,Flight **,int,int *);

/**
 * @brief Prints chuncks of the query 3
 * @param f Mode
 * @param rating Hotel average rating
*/
void printQ3(bool,double);

/**
 * @brief Prints chuncks of the query 4
 * @param f Mode
 * @param npp Number of chunks per page
 * @param reservation Reservations to be displayed 
 * @param max Number of Reservations 
*/

void printQ4(bool,int,int *,Reservation **,int);

/**
 * @brief Prints chuncks of the query 5
 * @param f Mode
 * @param npp Number of chunks per page
 * @param flight Flights to be displayed
 * @param max Number of Flights
*/

void printQ5(bool,int,int*,Flight**,int);

/**
 * @brief Prints chuncks of the query 6
 * @param f Mode
 * @param npp Number of chunks per page
 * @param max Number of airports / passengers
 * @param names Airports to be displayed
 * @param passengers Number of passengers per airport to be displayed
*/

void printQ6(bool,int,int*,int,char **,int *);

/**
 * @brief Prints chuncks of the query 7
 * @param f Mode
 * @param npp Number of chunks per page
 * @param table Airports informations to be displayed
 * @param max Number of airports 
*/


void printQ7(bool,int,int *,SingularRecord *,int);

/**
 * @brief Prints chuncks of the query 8
 * @param f Mode
 * @param revenue Hotel revenue between two dates
*/

void printQ8(bool,int);

/**
 * @brief Prints chuncks of the query 2
 * @param f Mode
 * @param npp Number of chunks per page
 * @param ids Users ids to be displayed
 * @param names Users names to be displayed
 * @param max Number of users names/ids
*/

void printQ9(bool,int,int *,char **,char **,int);

/**
 * @brief commands used in the menu
*/

int getInput();

/**
 * @brief Control function of the interactive mode
*/
void menus();

/**
 * @brief Turns off the printing of inputs of the user
*/
void dontWriteOnScreen();

/**
 * @brief Turns on the printing of inputs of the user
*/
void writeOnScreen();

/**
 * @brief Turns the cursor visible
*/
void cursorOn();


/**
 * @brief Removes the cursor from the screen
*/
void cursorOff();

#endif