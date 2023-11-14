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

double averageRating(void * reservations, const char * id){
    HotelDatabase * hotelDB = getHotelDataBase(reservations,id);
    int sumRatings = getSumRatings(hotelDB);
    int n = getNumReservas(hotelDB);
    destroyHotelDatabase(hotelDB);
    return sumRatings / n;
}