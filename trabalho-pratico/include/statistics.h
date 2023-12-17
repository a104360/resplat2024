#ifndef STATISTICS_H
#define STATISTICS_H
#include "../include/dataTypes.h"

double getTotalSpentByUser(void **);

double getTotalSpentOnReserv(void *,int);

int getHotelEarningsOfReserv(void *,int);

double averageRating(void *,const char *);


double dalayMedianAirport(void*, void*);

#endif