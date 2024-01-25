#include "../include/statistics.h"
#include "../include/reservation.h"
#include "../include/finder.h"
#include "../include/temporary.h"


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
    Temporary * temp = getAListOfSomething(reservations,id,NULL,NULL,&countHotelReservs);
    int sumRatings = getTempSum(temp);
    int n = getTempNum(temp);
    destroyTemporary(temp);
    double answer = (double) sumRatings / (double) n;  
    return (double) answer;
}

int delayMedianAirport(int * list,int n){
    int mid = (n / 2) - 1;
    if(n % 2 == 0){
        int a =  (list[mid]);
        int b =  (list[mid + 1]);
        return (int) (a + b) / 2;
    }
    return list[mid]; 
}