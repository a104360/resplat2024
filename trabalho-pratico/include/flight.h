#ifndef FLIGHT_H
#define FLIGHT_H
#include "../include/time.h" 
#include "../include/database.h"

typedef Database Flights;

typedef struct flight Flight;

Flight * createFlight();

void initFlight(Flight *);

void destroyFlight(Flight *);



void setFlightId(Flight *, const char *);
char * getFlightId(Flight *);
    
void setFlightAirline(Flight *,const char *);
char * getFlightAirline(Flight *);

void setFlightPlaneModel(Flight *, const char *);
char * getFlightPlaneModel(Flight *);

void setFlightTotalSeats(Flight *,const unsigned int);
unsigned int getFlightTotalSeats(Flight *);

void setFlightOrigin(Flight *, const char *);
char * getFlightOrigin(Flight *);

void setFlightDestination(Flight *, const char *);
char * getFlightDestination(Flight *);

void setFlightSDepartureDate(Flight *,Time *);
Time * getFlightSDepartureDate(Flight *);

void setFlightSArrivalDate(Flight *,Time *);
Time * getFlightSArrivalDate(Flight *);

void setFlightRDepartureDate(Flight *, Time *);
Time * getFlightRDepartureDate(Flight *);

void setFlightRArrivalDate(Flight *,Time *);
Time * getFlightRArrivalDate(Flight *);

void setFlightPilot(Flight *, const char *);
char * getFlightPilot(Flight *);

void setFlightCopilot(Flight *, const char *);
char * getFlightCopilot(Flight *);

void setFlightNotes(Flight *, const char *);
char * getFlightNotes(Flight *);

int getFlightDelay(Flight *);

void copyFlight(Flight *, Flight *);

#endif