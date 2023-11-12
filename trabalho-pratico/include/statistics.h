#ifndef STATISTICS_H
#define STATISTICS_H
#include "../include/dataTypes.h"


static Reservation * findReservHotel(void * table,const char * hotelId);

static Reservation * findReservUser(void * table,const char * userId);

static Passanger * findPassangerUserId(void * structs,const char * userId);

#endif