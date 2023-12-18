#ifndef STATISTICS_H
#define STATISTICS_H
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/passenger.h"

double getTotalSpentByUser(void **);

double getTotalSpentOnReserv(void *,int);

int getHotelEarningsOfReserv(void *,int);

double averageRating(void *,const char *);


double dalayMedianAirport(void*, void*);

#endif