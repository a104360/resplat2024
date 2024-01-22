#include "../include/passengers.h"
#include "../include/statistics.h"
#include "../include/finder.h"
#include "../include/sort.h"
#include "../include/output.h"
#include "../include/utils.h"
#include "../include/time.h"
#include "../include/temporary.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFFERSIZE 100

void query1(const Users * uDatabase, const Reservations * rDatabase,const Flights * fDatabase,const Passengers * pDatabase,const char * id,bool f){
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
            outputQ1User(f,NULL,'\0',0,NULL,NULL,0,0,0);
            return;
        }

        char * name = getUserName(user);
        char sex = getUserSex(user);
        int age = getUserAge(user);
        char * country_code = getUserCountryCode(user);
        char * passaport = getUserPassport(user);

        int number_of_fights = countUserFlights((void *) pDatabase,id);

        Temporary * uRDatabase = getAListOfSomething((void *) rDatabase,id,NULL,NULL,&allUserReservs);
        int number_of_reservations = getTempNum(uRDatabase);

        Reservation ** listReservs = (Reservation **) getTempList(uRDatabase);
        double total_spent = getTotalSpentByUser((void **) listReservs,number_of_reservations);
        free(listReservs);
        destroyTemporary(uRDatabase);
        
        outputQ1User((int)f,name,sex,age,country_code,passaport,number_of_fights,number_of_reservations,total_spent);

        ffree(name);
        ffree(country_code);
        ffree(passaport);
        
        
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
    Reservation ** rList = (Reservation **) getTempListReservations(hDatabase);
    int n = getTempNum(hDatabase);
    mergeSort((void **) rList,n,"Reservation");

    outputQ4(f,rList,n);

    for(int i = 0;i < n;destroyReservation(rList[i]),i++);
    ffree(rList);
    destroyTemporaryReservation(hDatabase);

    return;
}

void query5(const Flights * fDatabase,Time * ti,Time * tf,const char * name,bool f){
    Temporary * airportFlights = getAListOfSomething((void *) fDatabase,name,ti,tf,&checkAirports);
    if(!strcoll(name,"VIE")){
        int n = 0;
    }
    Flight ** fList = (Flight **) getTempListFlights(airportFlights);
    int max = getTempNum(airportFlights);
    mergeSort((void **) fList,max,"Flight");

    outputQ5(f,fList,max);

    for(int j = 0;j < max;destroyFlight(fList[j]),j++);
    ffree(fList);
    destroyTemporaryFlight(airportFlights);
}

void query6(const Flights * fDatabase,const Passengers * pDatabase,const char * year, const char * n,bool f){
    
    int n_airports = atoi(n);
    int fYear = atoi(year);

    SingularRecord * airports = getYearFlights(fDatabase, pDatabase, fYear);
    int max = getSRecordSize(airports);
    char ** names = getSRecordNames(airports);
    int * number = malloc(sizeof(int) * max);
    for(int i = 0;i < max;number[i] = getSRecordListElement(airports,i),i++);
    destroySRecord(&airports);

    
    void ** list = malloc(sizeof(void *) * 2);
    list[0] = (void *) number;
    list[1] = (void **) names;
    mergeSort(list,max,"Integers");

    list[0] = NULL;
    list[1] = NULL;
    ffree(list);


    outputQ6(f,n_airports,names,number);

    for(int i = 0;i < max;i++) ffree(names[i]);
    ffree(names);

    ffree(number);


}

void query7(Flights * fDatabase,char * num, bool f){
    SingularRecord * allDelays = getDelays((void *)fDatabase);
    int n = atoi(num);
    int max = getSRecordSize(allDelays);
    if(max < n) n = max;
    /*int * delays = malloc(sizeof(int) * max);
    for(int i = 0;i < max;
    delays[i] = -1,
    delays[i] = getSRecordListElement(allDelays,i),
    i++);

    char ** airports = malloc(sizeof(char *) * max);
    for(int i = 0;i < max;
    airports[i] = NULL,
    airports[i] = getSRecordName(allDelays,i),
    i++);*/

    outputQ7(f,allDelays,n);
    //for(int i = 0;i < max;ffree((airports[i])),i++);
    //ffree(airports);
    //ffree(delays);

    destroySRecord(&allDelays);

    
}

void query8(Reservations * rDatabase,const char * id,Time * lLimit,Time * uLimit,bool f){
    Temporary * hDatabase = getAListOfSomething((void *) rDatabase,id,lLimit,uLimit,&allHotelReservs);
    
    Reservation ** rList = (Reservation **) getTempListReservations(hDatabase);

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

    for(int i = 0;i < max;destroyReservation(rList[i]),i++);
    ffree(rList);
    destroyTemporaryReservation(hDatabase);

    return;
}
/*
void query9(){
    outputQ1Reservation(false,NULL,NULL,-1,NULL,NULL,false,0,0);
    return;
}*/

void query9(Users * uDatabase, char * pre, bool f){
    //SingularRecord * preUsers = getUsersPre(uDatabase,pre);
    //char ** users = getSRecordNames(preUsers);
    //int max = getSRecordSize(preUsers);
    Temporary * temp = getUsersPre(uDatabase,pre);
    char ** preUsersIds = getTempAuxChar(temp);
    char ** preUsersNames = getTempListChars(temp);
    int max = getTempNum(temp);

    void ** sort = malloc(sizeof(void *) * 2);
    sort[0] = preUsersNames;
    sort[1] = preUsersIds;

    mergeSort(sort,max,"String");

    //outputQ9(users,max,f);
    outputQ9(preUsersIds,preUsersNames,max,f);
    sort[0] = NULL;
    sort[1] = NULL;
    ffree(sort);
    for(int i = 0; i < max;i++){
        ffree(preUsersIds[i]);
    }
    free(preUsersIds);
    for(int i = 0; i < max;i++){
        ffree(preUsersNames[i]);
    }
    free(preUsersNames);
    destroyTemporaryChar(temp);
    return;
}

void query10(){
    outputQ1Reservation(false,NULL,NULL,-1,NULL,NULL,false,0,0);
    return;
}