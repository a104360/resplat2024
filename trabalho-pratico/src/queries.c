#include "../include/passengers.h"
#include "../include/statistics.h"
#include "../include/finder.h"
#include "../include/sort.h"
#include "../include/output.h"
#include "../include/utils.h"
#include "../include/temporary.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFFERSIZE 100

void query1(const Users * uDatabase, const Reservations * rDatabase,const Flights * fDatabase,const Passengers * pDatabase,const char * id,bool f){
    //int rDatabaseSize = getDatabaseSize(rDatabase);
    //int fDatabaseSize = getDatabaseSize(fDatabase);
    char * analisa = malloc(sizeof(char) * 5);
    strncpy(analisa,id,4);
    analisa[4] = '\0';
    int flag = 0;
    if(strcoll(analisa,"Book") == 0) flag = 3; //Reservation
    if(isdigit(analisa[0]) && flag == 0) flag = 2;//Flights *
    if(isalpha(analisa[0]) && flag == 0) flag = 1;//User
    switch (flag)
    {
    case 1: // ** User ** 
        User * user = NULL;
        user = lookupElement((const Users *) uDatabase,id);

        if(getUserAccountStatus(user) == false){
            ffree(analisa);
            outputQ1User(f,NULL,'\0',0,NULL,NULL,NULL,NULL,NULL);
            return;
        }

        char * name = getUserName(user);
        char sex = getUserSex(user);
        int age = getUserAge(user);
        char * country_code = getUserCountryCode(user);
        char * passaport = getUserPassport(user);

        Temporary * uFDatabase = getUserFlights((void *) fDatabase,(void *) pDatabase,id);
        char * number_of_fights = malloc(sizeof(char) * 10);
        snprintf(number_of_fights,10,"%d",getTempNum(uFDatabase));

        Temporary * uRDatabase = getAListOfSomething((void *) rDatabase,id,NULL,NULL,&allUserReservs);
        char * number_of_reservations = malloc(sizeof(char) * 10);
        snprintf(number_of_reservations,10,"%d",getTempNum(uRDatabase));

        Reservation ** listReservs = (Reservation **) getTempList(uRDatabase);
        char * total_spent = malloc(sizeof(char) * 10);
        snprintf(total_spent,10,"%.3f",getTotalSpentByUser((void **) listReservs,getTempNum(uRDatabase)));
        free(listReservs);
        destroyTemporary(uFDatabase);
        destroyTemporary(uRDatabase);
        
        outputQ1User((int)f,name,sex,age,country_code,passaport,number_of_fights,number_of_reservations,total_spent);

        ffree(name);
        ffree(country_code);
        ffree(passaport);
        ffree(number_of_fights);
        ffree(number_of_reservations);
        ffree(total_spent);
        
        
        break;
    
    case 2: // ** Flight **
        Flight * flight = NULL;
        flight = lookupElement(fDatabase,id);
        if(flight == NULL){
            ffree(analisa);
            outputQ1Flight(f,NULL,NULL,NULL,NULL,NULL,NULL,0,0);
            return;
        }
        char * airline = getFlightAirline(flight);
        char * plane_model = getFlightPlaneModel(flight);
        char * origin = getFlightOrigin(flight);
        char * destination = getFlightDestination(flight);
        Time * sDD = getFlightSDepartureDate(flight);
        Time * sAD = getFlightSArrivalDate(flight);
        char * schedule_departure_date = timeToString(sDD);
        char * schedule_arrival_date = timeToString(sAD);
        

        Temporary * book = getFlightPassengers((void *) fDatabase,(void *) pDatabase,id);
        int nPassengers = getTempNum(book);
        destroyTemporary(book);

        int delay = getFlightDelay(flight);

        outputQ1Flight((int)f,airline,plane_model,origin,destination,schedule_departure_date,schedule_arrival_date,nPassengers,delay);
        
        destroyTime(sDD);
        destroyTime(sAD);
        ffree(airline);
        ffree(plane_model);
        ffree(origin);
        ffree(destination);
        ffree(schedule_departure_date);
        ffree(schedule_arrival_date);


        break;

    case 3: // ** Reservation **
        Reservation * reserv = NULL;
        reserv = lookupElement(rDatabase,id);
        if(!reserv){
            ffree(analisa);
            outputQ1Reservation(f,NULL,NULL,-1,NULL,NULL,false,0,0);
            return;
        } 
        char * hotel_id = getReservHotelId(reserv);
        char * hotel_name = getReservHotelName(reserv);
        int hotel_stars = getReservHotelStars(reserv);
        Time * begin = getReservBeginDate(reserv);
        Time * end = getReservEndDate(reserv);
        char * begin_date = timeToString(begin);
        char * end_date = timeToString(end);
        int nights = numberOfDays(begin,end);
        bool includes_breakfast = getReservBreakfast(reserv);
        double total_price = getTotalSpentOnReserv(reserv,nights);

        outputQ1Reservation((int)f,hotel_id,hotel_name,hotel_stars,begin_date,end_date,
        includes_breakfast,nights,total_price);

        destroyTime(begin);
        destroyTime(end);
        ffree(hotel_id);
        ffree(hotel_name);
        ffree(begin_date);
        ffree(end_date);
        
        break;
    default:
        return;
        break;
    }
    ffree(analisa);
    return;
}

void query2(const Users * uDatabase, const Reservations * rDatabase,const Flights * fDatabase,const Passengers * pDatabase,const char * line,bool F){
    //int rDatabaseSize = getDatabaseSize(rDatabase);
    //int fDatabaseSize = getDatabaseSize(fDatabase);
    char * SRecord = strdup(line);
    char * token = NULL;
    char * saveprt = NULL;
    token = strtok_r(SRecord," \n\0",&saveprt);
    User * user = lookupElement((const Users *) uDatabase,token);
    if(user == NULL){
        outputQ2(F,NULL,-1,NULL,-1);
        ffree(SRecord);
        return;
    }
    token = strtok_r(NULL,"\n\0",&saveprt);


    if(getUserAccountStatus(user) == false){
        outputQ2(F,NULL,-1,NULL,-1);
        ffree(SRecord);
        return;
    }
    int flag = 0;
    if(!token) flag = 1;
    else{
    if(strcoll(token,"flights") == 0) flag = 2;
        else if(strcoll(token,"reservations") == 0) flag = 3;
    }
    ffree(SRecord);
    char * id = getUserId(user);
    switch (flag)
    {
    case 1: // SEM ARGUMENTOS
        Temporary * uFDatabase1 = getUserFlights((void *) fDatabase,(void *) pDatabase,id);
        Temporary * uRDatabase1 = getAListOfSomething((void *) rDatabase,id,NULL,NULL,&allUserReservs);
        
        Reservation ** rList1 = (Reservation **) getTempList(uRDatabase1);
        Flight ** fList1 = (Flight **) getTempList(uFDatabase1);

        int r = getTempNum(uRDatabase1);
        int f = getTempNum(uFDatabase1);

        mergeSort((void **) fList1,f,"Flight");
        mergeSort((void **) rList1,r,"Reservation");

        outputQ2(F,rList1,r,fList1,f);

        free(fList1);
        free(rList1);
        destroyTemporary(uRDatabase1);
        destroyTemporary(uFDatabase1);

        
        
        break;

    case 2: // FLIGHT
        Temporary * uFDatabase2 = getUserFlights((void *) fDatabase,(void *) pDatabase,id);
        
        Flight ** fList2 = (Flight **) getTempList(uFDatabase2);

        int max2 = getTempNum(uFDatabase2);

        mergeSort((void **) fList2,max2,"Flight");

        outputQ2(F,NULL,0,fList2,max2);

        free(fList2);

        destroyTemporary(uFDatabase2);

        break;

    case 3: // RESERVATION
        Temporary * uRDatabase3 = getAListOfSomething((void *) rDatabase,id,NULL,NULL,&allUserReservs);
        
        Reservation ** rList3 = (Reservation **) getTempList(uRDatabase3);

        int max3 = getTempNum(uRDatabase3);

        mergeSort((void **) rList3,max3,"Reservation");

        outputQ2(F,rList3,max3,NULL,0);
        
        free(rList3);
        
        destroyTemporary(uRDatabase3);
        
        break;
    
    
    default:
        break;
    }

    ffree(id);
    return;
}

// Average rating of an hotel
void query3(Reservations * rDatabase,const char * id,bool f){
    double n = averageRating((void *) rDatabase,id);

    outputQ3(f,n);

    return;
}

void query4(Reservations * rDatabase,const char * id,bool f){
    Temporary * hDatabase = getAListOfSomething((void *) rDatabase,id,NULL,NULL,&allHotelReservs);
    Reservation ** rList = (Reservation **) getTempList(hDatabase);
    mergeSort((void **) rList,getTempNum(hDatabase),"Reservation");

    outputQ4(f,rList,getTempNum(hDatabase));

    ffree(rList);
    destroyTemporary(hDatabase);

    return;
}

void query5(const Flights * fDatabase,Time * ti,Time * tf,const char * name,bool f){
    Temporary * airportFlights = getAListOfSomething((void *) fDatabase,name,ti,tf,&checkAirports);
    Flight ** fList = (Flight **) getTempList(airportFlights);
    int max = getTempNum(airportFlights);
    mergeSort((void **) fList,max,"Flight");

    outputQ5(f,fList,max);

    free(fList);
    destroyTemporary(airportFlights);
}

void query6(const Flights * fDatabase,const Passengers * pDatabase,const char * year, const char * n,bool f){
    int n_airports = atoi(n);
    int fYear = atoi(year);

    SingularRecord * airports = getYearFlights(fDatabase, pDatabase, fYear);
    char ** names = getSRecordNames(airports);
    int * number = malloc(sizeof(int) * getSRecordSize(airports));//getAirportPassengersPassengers(airports);
    for(int i = 0;i < getSRecordSize(airports);number[i] = getSRecordListElement(airports,i),i++);

    
    void ** list = malloc(sizeof(void *) * 2);
    list[0] = (void *) number;
    list[1] = (void **) names;
    mergeSort(list,getSRecordSize(airports),"Integers");

    list[0] = NULL;
    list[1] = NULL;
    ffree(list);


    outputQ6(f,n_airports,names,number);

    ffree(names);

    ffree(number);

    destroySRecord(airports);

}

void query7(Flights * fDatabase,char * num, bool f){
    SingularRecord * allDelays = getDelays((void *)fDatabase);
    int n = atoi(num);
    int * delays = malloc(sizeof(int) * getSRecordSize(allDelays));
    for(int i = 0;i < getSRecordSize(allDelays);
    delays[i] = -1,
    delays[i] = getSRecordListElement(allDelays,i),
    i++);

    char ** airports = malloc(sizeof(char *) * getSRecordSize(allDelays));
    for(int i = 0;i < getSRecordSize(allDelays);
    airports[i] = NULL,
    airports[i] = getSRecordName(allDelays,i),
    i++);

    outputQ7(f,allDelays,n);

    ffree(airports);
    ffree(delays);

    destroySRecord(allDelays);

    /*Temporary * temp = getAListOfSomething(fDatabase,NULL,NULL,NULL,&getAirportsDelays);


    char ** airports = (char **) getTempList(temp);


    destroyTemporary(temp);
    outputQ1Reservation(false,NULL,NULL,-1,NULL,NULL,false,0,0);*/
}

void query8(Reservations * rDatabase,const char * id,Time * lLimit,Time * uLimit,bool f){
    Temporary * hDatabase = getAListOfSomething((void *) rDatabase,id,lLimit,uLimit,&allHotelReservs);
    
    Reservation ** rList = (Reservation **) getTempList(hDatabase);

    int total = 0;


    int max = getTempNum(hDatabase);

    for(int i = 0;i < max;i++){
        Time * begin = getReservBeginDate(rList[i]);
        Time * end = getReservEndDate(rList[i]);
        int days = 1;
        switch (compareTimes(begin,lLimit))
        {
        case true:
            if(compareTimes(end,uLimit)) days += numberOfDays(lLimit,end);
            else days += numberOfDays(lLimit,uLimit);
            break;
        default:
            if(compareTimes(end,uLimit)) days = numberOfDays(begin,end);
            else days += numberOfDays(begin,uLimit);
            break;
        }
        total += getHotelEarningsOfReserv(rList[i],days);
        destroyTime(begin);
        destroyTime(end);
    }

    outputQ8(f,total);

    ffree(rList);
    destroyTemporary(hDatabase);

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