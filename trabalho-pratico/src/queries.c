#include "../include/queries.h"
#include "../include/dataTypes.h"
#include "../include/catalogs.h"
#include "../include/statistics.h"
#include "../include/dataStructs.h"
#include "../include/catalogs.h"
#include <stdio.h>
#include <ctype.h>


#define BUFFERSIZE 100

char * query1(UsersDatabase * uDatabase, ReservationsDatabase * rDatabase,FlightsDatabase * fDatabase,PassangersDatabase * pDatabase,const char * id,bool f){
    char * analisa = malloc(sizeof(char) * 4);
    strncpy(analisa,id,4);
    int flag = 0;
    if(strcoll(analisa,"Book") == 0) flag = 3; //Reservation
    if(isdigit(analisa[0])) flag = 2;//Flights
    if(isalpha(analisa[0])) flag = 1;//User
    switch (flag)
    {
    case 1: // ** User ** 
        User * user = lookupUser(uDatabase,id);

        char * name = getUserName(user);
        char sex = getUserSex(user);
        int age = getUserAge(user);
        char * country_code = getUserCountryCode(user);

        UserFlightsDB * uFDatabase = getUserFlightsDB(*fDatabase,pDatabase,id);
        char * number_of_fights = malloc(sizeof(char) * 10);
        sprintf(number_of_fights,"%d",getNumFlights(uFDatabase));
        destroyUserFlightsDB(uFDatabase);

        UserReservsDB * uRDatabase = getUserReservsDB(*uDatabase,id);
        char * number_of_reservations = malloc(sizeof(char) * 10);
        sprintf(number_of_reservations,"%d",getNumReservs(uRDatabase));
        destroyUserReservsDB(uRDatabase);

        char * total_spent = malloc(sizeof(char) * 10);
        sprintf(total_spent,"%.3f",getTotalSpentByUser((void **) getUserReservs(uRDatabase)));
        
        char * final1 = malloc(sizeof(char) * BUFFERSIZE);
        sprintf(final1,"%s;%c;%d;%s;%s;%s;",name,sex,age,number_of_fights,number_of_reservations,total_spent);

        free(name);
        free(country_code);
        free(number_of_fights);
        free(number_of_reservations);
        free(total_spent);

        return final1;
        break;
    
    case 2: // ** Flight **
        Flight * flight = lookupFlight(fDatabase,id);
        char * airline = getFlightAirline(flight);
        char * plane_model = getFlightPlaneModel(flight);
        char * origin = getFlightOrigin(flight);
        char * destination = getFlightDestination(flight);
        char * schedule_departure_date = timeToString(getFlightSDepartureDate(flight));
        char * schedule_arrival_date = timeToString(getFlightSArrivalDate(flight));
        

        FlightPassangers * book = getFlightPassangers(fDatabase,pDatabase,id);
        char * nPassangers = malloc(sizeof(char) * 10);
        sprintf(nPassangers,"%d",getNumPassangers(book));
        destroyFlightPassangers(book);

        char * delay = malloc(sizeof(char) * 10);
        sprintf(delay,"%d",getFlightDelay(flight));


        char * final2 = malloc(sizeof(char) * BUFFERSIZE);
        sprintf(final2,"%s;%s;%s;%s;%s;%s;%s;%s;",airline,plane_model,origin,destination,schedule_departure_date,
        schedule_arrival_date,nPassangers,delay);

        free(airline);
        free(plane_model);
        free(origin);
        free(destination);
        free(schedule_departure_date);
        free(schedule_arrival_date);
        free(nPassangers);
        free(delay);

        return final2;
        break;

    case 3: // ** Reservation **
        Reservation * reserv = lookupReserv(rDatabase,id);
        char * hotel_id = getReservHotelId(reserv);
        char * hotel_name = getReservHotelName(reserv);
        char hotel_stars = getReservHotelStars(reserv) + '0';
        char * begin_date = timeToString(getReservBeginDate(reserv));
        char * end_date = timeToString(getReservEndDate(reserv));
        int nights = numberOfDays(getReservBeginDate(reserv),getReservEndDate(reserv));
        char includes_breakfast = getReservBreakfast(reserv) + '0';
        char * total_price = malloc(sizeof(char) * 10);
        sprintf(total_price,"%.3f",getTotalSpentOnReserv(reserv));
        char * final3 = malloc(sizeof(char) * BUFFERSIZE);
        sprintf(final3,"%s;%s;%c;%s;%s;%d;%c;%s;",hotel_id,hotel_name,hotel_stars,begin_date,end_date,
        nights,includes_breakfast,total_price);

        free(hotel_id);
        free(hotel_name);
        free(begin_date);
        free(end_date);
        free(total_price);

        return final3;
        break;
    default:
        return NULL;
        break;
    }
    free(analisa);
    return NULL;
}

char * query2(ReservationsDatabase reservs,PassangersDatabase * passangers,const char * id,bool f){
    
    return NULL;
}

char * query3(){
    return NULL;
}

char * query4(){
    return NULL;
}

char * query5(){
    return NULL;
}

char * query6(){
    return NULL;
}

char * query7(){
    return NULL;
}

char * query8(){
    return NULL;
}

char * query9(){
    return NULL;
}

char * query10(){
    return NULL;
}