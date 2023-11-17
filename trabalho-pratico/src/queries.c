#include "../include/queries.h"
#include "../include/dataTypes.h"
#include "../include/catalogs.h"
#include "../include/statistics.h"
#include "../include/dataStructs.h"
#include "../include/catalogs.h"
#include "../include/sort.h"
#include "../include/output.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>


#define BUFFERSIZE 100

void query1(UsersDatabase * uDatabase, ReservationsDatabase * rDatabase,FlightsDatabase * fDatabase,PassangersDatabase * pDatabase,const char * id,bool f){
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

        if(getUserAccountStatus(user) == false){
            free(user);
            return;
        }

        char * name = getUserName(user);
        char sex = getUserSex(user);
        int age = getUserAge(user);
        char * country_code = getUserCountryCode(user);
        char * passaport = getUserPassaport(user);

        UserFlightsDB * uFDatabase = getUserFlightsDB(*fDatabase,pDatabase,id);
        char * number_of_fights = malloc(sizeof(char) * 10);
        snprintf(number_of_fights,10,"%d",getNumFlights(uFDatabase));
        destroyUserFlightsDB(uFDatabase);

        UserReservsDB * uRDatabase = getUserReservsDB(*uDatabase,id);
        char * number_of_reservations = malloc(sizeof(char) * 10);
        snprintf(number_of_reservations,10,"%d",getNumReservs(uRDatabase));
        destroyUserReservsDB(uRDatabase);

        char * total_spent = malloc(sizeof(char) * 10);
        snprintf(total_spent,10,"%.3f",getTotalSpentByUser((void **) getUserReservs(uRDatabase)));
        
        outputQ1User((int)f,name,sex,age,country_code,passaport,number_of_fights,number_of_reservations,total_spent);

        free(name);
        free(country_code);
        free(passaport);
        free(number_of_fights);
        free(number_of_reservations);
        free(total_spent);
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
        int nPassangers = getNumPassangers(book);
        destroyFlightPassangers(book);

        int delay = getFlightDelay(flight);

        outputQ1Flight((int)f,airline,plane_model,origin,destination,schedule_departure_date,schedule_arrival_date,nPassangers,delay);

        free(airline);
        free(plane_model);
        free(origin);
        free(destination);
        free(schedule_departure_date);
        free(schedule_arrival_date);
        free(nPassangers);
        free(delay);


        break;

    case 3: // ** Reservation **
        Reservation * reserv = lookupReserv(rDatabase,id);
        char * hotel_id = getReservHotelId(reserv);
        char * hotel_name = getReservHotelName(reserv);
        int hotel_stars = getReservHotelStars(reserv);
        char * begin_date = timeToString(getReservBeginDate(reserv));
        char * end_date = timeToString(getReservEndDate(reserv));
        int nights = numberOfDays(getReservBeginDate(reserv),getReservEndDate(reserv));
        bool includes_breakfast = getReservBreakfast(reserv);
        double total_price = getTotalSpentOnReserv(reserv);

        outputQ1Reservation((int)f,hotel_id,hotel_name,hotel_stars,begin_date,end_date,
        includes_breakfast,nights,total_price);

        free(hotel_id);
        free(hotel_name);
        free(begin_date);
        free(end_date);
        break;
    default:
        return;
        break;
    }
    free(analisa);
    return;
}

void query2(UsersDatabase uDatabase, ReservationsDatabase rDatabase,FlightsDatabase fDatabase,PassangersDatabase * passangers,
const char * id,char * tipo,bool f){
    User * user = lookupUser(uDatabase,id);

    if(getUserAccountStatus(user) == false){
        free(user);
        return;
    }
    int flag = 0;
    if(!tipo) flag = 1;
    else{
    if(strcool(tipo,"flight") == 0) flag = 2;
        else if(strcool(tipo,"reservation") == 0) flag = 3;
    }
    switch (flag)
    {
    case 1: // SEM ARGUMENTOS
        UserFlightsDB * uFDatabase = getUserFlightsDB(fDatabase,passangers,id);
        UserReservsDB * uRDatabase = getUserReservsDB(rDatabase,id);
        
        Reservation ** rList = getUserReservs(uRDatabase);
        Flight ** fList = getUserFlights(uFDatabase);

        mergeSortF(fList,0,getNumFlights(uFDatabase));
        mergeSortR(rList,0,getNumReservs(uRDatabase));

        outputQ2(f,rList,getNumReservs(uRDatabase),fList,getNumFlights(uFDatabase));

        free(fList);
        free(rList);
        destroyUserFlightsDB(uFDatabase);
        destroyUserReservsDB(uRDatabase);

        break;

    case 2: // FLIGHT
        UserFlightsDB * uFDatabase = getUserFlightsDB(fDatabase,passangers,id);
        
        Flight ** fList = getUserFlights(uFDatabase);

        mergeSortF(fList,0,getNumFlights(uFDatabase));

        outputQ2(f,NULL,0,fList,getNumFlights(uFDatabase));

        free(fList);
        destroyUserFlightsDB(uFDatabase);

        break;

    case 3: // RESERVATION
        UserReservsDB * uRDatabase = getUserReservsDB(rDatabase,id);
        
        Reservation ** rList = getUserReservs(uRDatabase);

        mergeSortR(rList,0,getNumReservs(uRDatabase));

        outputQ2(f,rList,getNumReservs(uRDatabase),NULL,0);

        free(rList);
        destroyUserReservsDB(uRDatabase);        
        
        break;
    
    
    default:
        break;
    }
    
    free(user);
    return;
}

// Average rating of an hotel
void query3(ReservationsDatabase * rDatabase,const char * id,bool f){
    double n = averageRating(rDatabase,id);

    outputQ3(f,n);

    return;
}

void query4(ReservationsDatabase * rDatabase,const char * id,bool f){
    HotelDatabase * hDatabase = getHotelDataBase(rDatabase,id);
    Reservation ** rList = getAllHotelReservs(hDatabase);
    mergeSortR(rList,0,getNumReservas(hDatabase));

    outputQ4(f,rList,getNumReservas(hDatabase));

    for(int i = 0; i < getNumReservas(hDatabase);i++){
        free(rList[i]);
    }
    free(rList);

    destroyHotelDatabase(hDatabase);

    return;
}

void query5(){
    return;
}

void query6(){
    return;
}

void query7(){
    return;
}

void query8(){
    return;
}

void query9(){
    return;
}

void query10(){
    return;
}