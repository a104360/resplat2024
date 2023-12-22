#include "../include/statistics.h"
#include "../include/reservation.h"
#include "../include/database.h"
#include "../include/finder.h"
#include <glib.h>


double getTotalSpentByUser(void ** userReservs,int max){
    if(userReservs == NULL) return -1;
    Reservation ** list = (Reservation **) userReservs; 
    double total = 0;
    for(int i = 0;i < max;i++){
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
    Temporary * temp = getAListOfSomething(reservations,id,NULL,NULL,&allHotelReservs);
    int sumRatings = getTempSum(temp);
    int n = getTempNum(temp);
    double answer = (double) sumRatings / (double) n;  
    destroyTemporary(temp);
    return (double) answer;
}

double dalayMedianAirport(void*, void*);