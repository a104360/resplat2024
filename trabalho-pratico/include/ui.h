#ifndef UI_H
#define UI_H
#include <ncurses.h>
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/singularRecord.h"

/**
 * @brief Draws the box for the main menu
 * @param width Width of the background screen
 * @param height Height of the background screen
*/
WINDOW * drawMainMenu(int,int);

/**
 * @brief Draws the box for the user input
 * @param width Width of the background screen
 * @param height Height of the background screen
*/
WINDOW * drawSearchBox(int, int);

/**
 * @brief Writes on the middle of the window 
 * a message to request something
 * @param window Pointer to the WINDOW structure where 
 * it will be displayed;
 * @param width Width of the window which will display 
 * the message
 * @param message Pointer of the string to be displayed
 * @note The message must be short 
*/
void requestSomething(WINDOW *,int,int,const char *);


void warning(int,int,int,int,const char *);

void printQ1User(int,int,char *,char,int,char *,char *,char *,char *,char *);

void printQ1Flight(int,int, char *, char *, char *,char *,char *,char *,int,int);

void printQ1Reservation(int,int,char *,char *,int, char *, char *,bool,int,double);

void printQ2(bool,int *,int,int,Reservation **,int,int *,Flight **,int,int *);

void printQ3(bool,int,double);

void printQ4(bool,int,int,int *,Reservation **,int);

void printQ5(bool,int,int,int*,Flight**,int);

void printQ6(bool,int,int,int*,int,char **,int *);

void printQ7(bool,int,int,int *,SingularRecord *,int);

void printQ8(bool,int,int);

void printQ9(bool,int,int,int *,char **,char **,int);

void resquestMode();

void requestQuery();

void queryWarning();

void pathWarining();

void drawQueryWindow();

void drawQuery1(); 

void drawQuery2(); 

void drawQuery3(); 

void drawQuery4(); 

void drawQuery5(); 

void drawQuery6(); 

void drawQuery7(); 

void drawQuery8(); 

void drawQuery9(); 

#endif