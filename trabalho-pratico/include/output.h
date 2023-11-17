#ifndef OUTPUT_H
#define OUTPUT_H
#include "../include/dataTypes.h"

void outputQ1User(int , char * , char , int , char * , char * , char * , char * , char * );

void outputQ1Flight(int , char * , char * , char * , char * , char * , char * , int , int);

void outputQ1Reservation(int , char * , char * , int , char * , char * , bool, int , double);

void outputQ2(bool,Reservation **,int, Flight **,int);

void outputQ3(bool,double);

void outputQ4(bool,Reservation **,int);

#endif