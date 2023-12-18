#include "../include/statistics.h"
#include "../include/catalogs.h"
#include "../include/reservation.h"
#include <glib.h>


double getTotalSpentByUser(void ** userReservs){
    if(userReservs == NULL) return -1;
    Reservation ** list = (Reservation **) userReservs; 
    double total = 0;
    for(int i = 0;list[i];i++){
        Time * reservBeginDate = getReservBeginDate(list[i]);
        Time * reservEndDate = getReservEndDate(list[i]);
        int dayDiff = numberOfDays(reservBeginDate,reservEndDate);
        if(dayDiff <= 0) continue;
        total += getTotalSpentOnReserv(list[i],dayDiff);
        destroyTime(reservBeginDate);
        destroyTime(reservEndDate);
    }
    return total;
}

double getTotalSpentOnReserv(void * userReservs,int n){
    Reservation * list = (Reservation *) userReservs; 
    double total = 0;
    double p = getReservPricePerNight(list);
    double iva = getReservCityTax(list);
    double baseMoney = (p * n);
    double taxMoney = (((p * n)/ 100) * iva);
    
    total = baseMoney + taxMoney;
    
    return total;
}

int getHotelEarningsOfReserv(void * userReservs,int n){
    Reservation * list = (Reservation *) userReservs; 
    int total = 0;
    int p = (int) getReservPricePerNight(list);
    int baseMoney = (p * n);
    total = baseMoney;
    
    return total;
}


double averageRating(void * reservations, const char * id){
    HotelDatabase * hotelDB = getHotelDataBase(reservations,id,NULL,NULL);
    int sumRatings = getSumRatings(hotelDB);
    int n = getNumReservas(hotelDB);
    double answer = (double) sumRatings / (double) n;  
    destroyHotelDatabase(hotelDB);
    return (double) answer;
}

double dalayMedianAirport(void*, void*);