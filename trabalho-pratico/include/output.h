#ifndef OUTPUT_H
#define OUTPUT_H
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/passenger.h"
#include <stdbool.h>

void outputQ1User(int , char * , char , int , char * , char * , char * , char * , char * );

void outputQ1Flight(int , char * , char * , char * , char * , char * , char * , int , int);

void outputQ1Reservation(int , char * , char * , int , char * , char * , bool, int , double);

void outputQ2(bool,Reservation **,int, Flight **,int);

void outputQ3(bool,double);

void outputQ4(bool,Reservation **,int);

void outputQ5(bool,Flight **,int);

void outputQ6(const int , char **, int *);

void outputQ8(int ,bool);

#endif