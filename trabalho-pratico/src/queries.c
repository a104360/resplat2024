#include "../include/queries.h"
#include "../include/dataTypes.h"
#include "../include/statistics.h"
#include "../include/dataStructs.h"
#include "../include/catalogs.h"
#include "../include/sort.h"
#include "../include/output.h"
#include "../include/catalogs.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>


#define BUFFERSIZE 100

#define FREE(ptr) if(ptr){\
    free(ptr);\
    ptr = NULL;\
}

void query1(const UsersDatabase uDatabase, const ReservationsDatabase rDatabase,const FlightsDatabase fDatabase,const PassangersDatabase * pDatabase,const char * id,bool f){
    int rDatabaseSize = g_hash_table_size(rDatabase);
    int fDatabaseSize = g_hash_table_size(fDatabase);
    char * analisa = malloc(sizeof(char) * 5);
    strncpy(analisa,id,4);
    analisa[4] = '\0';
    int flag = 0;
    if(strcoll(analisa,"Book") == 0) flag = 3; //Reservation
    if(isdigit(analisa[0]) && flag == 0) flag = 2;//Flights
    if(isalpha(analisa[0]) && flag == 0) flag = 1;//User
    switch (flag)
    {
    case 1: // ** User ** 
        User * user = lookupUser((const UsersDatabase) uDatabase,id);

        if(getUserAccountStatus(user) == false){
            outputQ1User(f,NULL,'\0',0,NULL,NULL,NULL,NULL,NULL);
            return;
        }

        char * name = getUserName(user);
        char sex = getUserSex(user);
        int age = getUserAge(user);
        char * country_code = getUserCountryCode(user);
        char * passaport = getUserPassport(user);

        UserFlightsDB * uFDatabase = getUserFlightsDB((void *) fDatabase,(void *) pDatabase,id);
        char * number_of_fights = malloc(sizeof(char) * 10);
        snprintf(number_of_fights,10,"%d",getNumFlights(uFDatabase));

        UserReservsDB * uRDatabase = getUserReservsDB((const void *) rDatabase,id);
        char * number_of_reservations = malloc(sizeof(char) * 10);
        snprintf(number_of_reservations,10,"%d",getNumReservs(uRDatabase));

        Reservation ** listReservs = getUserReservs(uRDatabase);
        char * total_spent = malloc(sizeof(char) * 10);
        snprintf(total_spent,10,"%.3f",getTotalSpentByUser((void **) listReservs));
        destroyUserFlightsDB(uFDatabase,fDatabaseSize);
        destroyUserReservsDB(uRDatabase,rDatabaseSize);
        
        outputQ1User((int)f,name,sex,age,country_code,passaport,number_of_fights,number_of_reservations,total_spent);

        FREE(name);
        FREE(country_code);
        FREE(passaport);
        FREE(number_of_fights);
        FREE(number_of_reservations);
        FREE(total_spent);
        
        
        break;
    
    case 2: // ** Flight **
        Flight * flight = lookupFlight(fDatabase,id);
        if(flight == NULL){
            outputQ1Flight(f,NULL,NULL,NULL,NULL,NULL,NULL,0,0);
            return;
        }
        char * airline = getFlightAirline(flight);
        char * plane_model = getFlightPlaneModel(flight);
        char * origin = getFlightOrigin(flight);
        char * destination = getFlightDestination(flight);
        char * schedule_departure_date = timeToString(getFlightSDepartureDate(flight));
        char * schedule_arrival_date = timeToString(getFlightSArrivalDate(flight));
        

        FlightPassangers * book = getFlightPassangers((void *) fDatabase,(void *) pDatabase,id);
        int nPassangers = getNumPassangers(book);
        destroyFlightPassangers(book,fDatabaseSize);

        int delay = getFlightDelay(flight);

        outputQ1Flight((int)f,airline,plane_model,origin,destination,schedule_departure_date,schedule_arrival_date,nPassangers,delay);

        FREE(airline);
        FREE(plane_model);
        FREE(origin);
        FREE(destination);
        FREE(schedule_departure_date);
        FREE(schedule_arrival_date);


        break;

    case 3: // ** Reservation **
        Reservation * reserv = lookupReserv(rDatabase,id);
        if(!reserv){
            outputQ1Reservation(f,NULL,NULL,-1,NULL,NULL,false,0,0);
            return;
        } 
        char * hotel_id = getReservHotelId(reserv);
        char * hotel_name = getReservHotelName(reserv);
        int hotel_stars = getReservHotelStars(reserv);
        char * begin_date = timeToString(getReservBeginDate(reserv));
        char * end_date = timeToString(getReservEndDate(reserv));
        int nights = numberOfDays(getReservBeginDate(reserv),getReservEndDate(reserv));
        bool includes_breakfast = getReservBreakfast(reserv);
        double total_price = getTotalSpentOnReserv(reserv,nights);

        outputQ1Reservation((int)f,hotel_id,hotel_name,hotel_stars,begin_date,end_date,
        includes_breakfast,nights,total_price);

        FREE(hotel_id);
        FREE(hotel_name);
        FREE(begin_date);
        FREE(end_date);
        
        break;
    default:
        return;
        break;
    }
    FREE(analisa);
    return;
}

void query2(const UsersDatabase uDatabase, const ReservationsDatabase rDatabase,const FlightsDatabase fDatabase,const PassangersDatabase * pDatabase,const char * line,bool F){
    int rDatabaseSize = g_hash_table_size(rDatabase);
    int fDatabaseSize = g_hash_table_size(fDatabase);
    char * aux = strdup(line);
    char * token = NULL;
    char * saveprt = NULL;
    token = strtok_r(aux," \n\0",&saveprt);
    User * user = lookupUser((const UsersDatabase) uDatabase,token);
    if(user == NULL){
        outputQ2(F,NULL,-1,NULL,-1);
        return;
    }
    token = strtok_r(NULL,"\n\0",&saveprt);

    FREE(aux);

    if(getUserAccountStatus(user) == false){
        outputQ2(F,NULL,-1,NULL,-1);
        return;
    }
    int flag = 0;
    if(!token) flag = 1;
    else{
    if(strcoll(token,"flights") == 0) flag = 2;
        else if(strcoll(token,"reservations") == 0) flag = 3;
    }
    char * id = getUserId(user);
    switch (flag)
    {
    case 1: // SEM ARGUMENTOS
        UserFlightsDB * uFDatabase1 = getUserFlightsDB((void *) fDatabase,(void *) pDatabase,id);
        UserReservsDB * uRDatabase1 = getUserReservsDB((void *) rDatabase,id);
        
        Reservation ** rList1 = getUserReservs(uRDatabase1);
        Flight ** fList1 = getUserFlights(uFDatabase1);

        int r = getNumReservs(uRDatabase1);
        int f = getNumFlights(uFDatabase1);

        mergeSort((void **) fList1,f,"Flight");
        mergeSort((void **) rList1,r,"Reservation");

        outputQ2(F,rList1,r,fList1,f);

        destroyUserReservsDB(uRDatabase1,rDatabaseSize);
        destroyUserFlightsDB(uFDatabase1,fDatabaseSize);

        if(id){
            FREE(id);
        }
        if(token){
            FREE(token);
        }
        break;

    case 2: // FLIGHT
        UserFlightsDB * uFDatabase2 = getUserFlightsDB((void *) fDatabase,(void *) pDatabase,id);
        
        Flight ** fList2 = getUserFlights(uFDatabase2);

        int max2 = getNumFlights(uFDatabase2);

        mergeSort((void **) fList2,max2,"Flight");

        outputQ2(F,NULL,0,fList2,max2);

        destroyUserFlightsDB(uFDatabase2,fDatabaseSize);

        break;

    case 3: // RESERVATION
        UserReservsDB * uRDatabase3 = getUserReservsDB(rDatabase,id);
        
        Reservation ** rList3 = getUserReservs(uRDatabase3);

        int max3 = getNumReservs(uRDatabase3);

        mergeSort((void **) rList3,max3,"Reservation");

        outputQ2(F,rList3,max3,NULL,0);

        destroyUserReservsDB(uRDatabase3,rDatabaseSize);
        
        break;
    
    
    default:
        break;
    }
    FREE(id);
    return;
}

// Average rating of an hotel
void query3(ReservationsDatabase rDatabase,const char * id,bool f){
    double n = averageRating(rDatabase,id);

    outputQ3(f,n);

    return;
}

void query4(ReservationsDatabase rDatabase,const char * id,bool f){
    int rDatabaseSize = g_hash_table_size(rDatabase);
    HotelDatabase * hDatabase = getHotelDataBase(rDatabase,id,NULL,NULL);
    Reservation ** rList = getAllHotelReservs(hDatabase);
    mergeSort((void **) rList,getNumReservas(hDatabase),"Reservations");

    outputQ4(f,rList,getNumReservas(hDatabase));

    destroyHotelDatabase(hDatabase);

    return;
}

void query5(FlightsDatabase fDatabase,Time * ti,Time * tf,const char * name,bool f){
    int fDatabaseSize = g_hash_table_size(fDatabase);
    AirportDB * airportFlights = getAirportDB(fDatabase,name,ti,tf);
    Flight ** fList = getAirportFlights(airportFlights);
    int max = getNumAirportFlights(airportFlights);
    mergeSort((void **) fList,max,"Flight");

    outputQ5(f,fList,max);

    destroyAirport(airportFlights,fDatabaseSize);
}

void query6(){
    outputQ1Reservation(false,NULL,NULL,-1,NULL,NULL,false,0,0);
    return;
}

void query7(){
    outputQ1Reservation(false,NULL,NULL,-1,NULL,NULL,false,0,0);
    return;
}

void query8(ReservationsDatabase rDatabase,const char * id,Time * begin,Time * end,bool f){
    int rDatabaseSize = g_hash_table_size(rDatabase);
    HotelDatabase * hDatabase = getHotelDataBase(rDatabase,id,begin,end);
    
    Reservation ** rList = getAllHotelReservs(hDatabase);

    double total = 0;

    int days = numberOfDays(begin,end);

    for(int i = 0;i < getNumReservas(hDatabase);i++){
        total += getTotalSpentOnReserv(rList[i],days);
    }

    outputQ8(total,f);

    destroyHotelDatabase(hDatabase);

    return;
}

void query9(){
    outputQ1Reservation(false,NULL,NULL,-1,NULL,NULL,false,0,0);
    return;
}

void query10(){
    outputQ1Reservation(false,NULL,NULL,-1,NULL,NULL,false,0,0);
    return;
}