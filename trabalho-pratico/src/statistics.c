#include "../include/statistics.h"
#include "../include/catalogs.h"
#include "../include/dataTypes.h"
#include <glib.h>


double getTotalSpentByUser(void ** userReservs){
    Reservation ** list = (Reservation **) userReservs; 
    int total = 0;
    for(int i = 0;list[i];i++){
        int dayDiff = numberOfDays(getReservBeginDate(list[i]),getReservEndDate(list[i]));
        total += (getReservPricePerNight(list[i]) * dayDiff) + ((dayDiff / 100) * getReservCityTax(list[i]));
    }
    return total;
}

double getTotalSpentOnReserv(void * userReservs,int n){
    Reservation * list = (Reservation *) userReservs; 
    int total = 0;
    double p = getReservPricePerNight(list);
    double iva = getReservCityTax(list);
    if(n > -1) total = (p * n) + (((p * n)/ 100) * iva);
    else{
        int dayDiff = numberOfDays(getReservBeginDate(list),getReservEndDate(list));
        total = (p * dayDiff) + (((p * dayDiff)/100) * iva);
    }
    return total;
}

double averageRating(void * reservations, const char * id){
    HotelDatabase * hotelDB = getHotelDataBase(reservations,id,NULL,NULL);
    int sumRatings = getSumRatings(hotelDB);
    int n = getNumReservas(hotelDB);
    destroyHotelDatabase(hotelDB);
    return sumRatings / n;
}

double dalayMedianAirport(void*, void*);