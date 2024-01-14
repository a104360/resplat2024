#ifndef UI_H
#define UI_H
#include <ncurses.h>
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/singularRecord.h"

void printQ1User(bool,char *,char,int,char *,char *,char *,char *,char *);

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

void printQ3(bool,double);

void printQ4(bool,int,int *,Reservation **,int);

void printQ5(bool,int,int*,Flight**,int);

void printQ6(bool,int,int*,int,char **,int *);

void printQ7(bool,int,int *,SingularRecord *,int);

void printQ8(bool,int);

void printQ9(bool,int,int *,char **,char **,int);

int getInput();

void menus();

#endif