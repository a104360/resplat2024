#include "../include/statistics.h"
#include "../include/catalogs.h"
#include "../include/dataTypes.h"
#include <glib.h>


double getTotalSpentByUser(void ** userReservs){
    if(userReservs == NULL) return -1;
    Reservation ** list = (Reservation **) userReservs; 
    double total = 0;
    for(int i = 0;list[i];i++){
        /*
        total += (getReservPricePerNight(list[i]) * dayDiff) + ((dayDiff / 100) * getReservCityTax(list[i]));
        free(reservBeginDate);
        reservBeginDate = NULL;
        free(reservEndDate);
        reservEndDate = NULL;
        */
        Time * reservBeginDate = getReservBeginDate(list[i]);
        Time * reservEndDate = getReservEndDate(list[i]);
        int dayDiff = numberOfDays(reservBeginDate,reservEndDate);
        if(dayDiff == 0) continue;
        total += getTotalSpentOnReserv(list[i],dayDiff);
    }
    return total;
}

double getTotalSpentOnReserv(void * userReservs,int n){
    Reservation * list = (Reservation *) userReservs; 
    double total = 0;
    double p = getReservPricePerNight(list);
    double iva = getReservCityTax(list);
    total = (p * n) + (((p * n)/ 100) * iva);
    /*else{
        Time * reservBeginDate = getReservBeginDate(list);
        Time * reservEndDate = getReservEndDate(list);
        int dayDiff = numberOfDays(reservBeginDate,reservEndDate);
        total = (p * dayDiff) + (((p * dayDiff)/100) * iva);
        free(reservBeginDate);
        reservBeginDate = NULL;
        free(reservEndDate);
        reservEndDate = NULL;
    }*/
    return total;
}

double averageRating(void * reservations, const char * id,int hashSize){
    HotelDatabase * hotelDB = getHotelDataBase(reservations,id,NULL,NULL);
    int sumRatings = getSumRatings(hotelDB);
    int n = getNumReservas(hotelDB);
    destroyHotelDatabase(hotelDB,hashSize);
    hotelDB = NULL;
    return sumRatings / n;
}

double dalayMedianAirport(void*, void*);