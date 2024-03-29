#include "../include/finder.h"
#include "../include/utils.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/sort.h"
#include "../include/statistics.h"
#include "../include/singularRecord.h"
#include "../include/multipleRecord.h"
#include "../include/temporary.h"
#include "../include/time.h"
#include "../include/user.h"
#include <ctype.h>
#include <string.h>
#include <glib.h>


static int i = 0;

Temporary * getAListOfSomething(void * database,const char * hotelId,Time * begin,Time * end,void (*func)()){
    Temporary * temp = createTemporary();
    void ** list = NULL; //= malloc(sizeof(void *) * 500);
    initArrays(&list,500);
    setTempList(temp,list);
    setTempMax(temp,500);
    if(hotelId) setTempId(temp,(char *) hotelId);
    setTempBegin(temp,begin);
    setTempEnd(temp,end);
    i = 0;
    setTempNum(temp,0);
    applyForEach(database,func,(void *)temp);
    return temp;
}

int countUserFlights(void * travels,const char * userId){
    Passengers * pDatabase = (Passengers *) travels;

    int uFlights = 0;

    int max = getNumAllPassengers(pDatabase);
    Passenger ** list = getAllPassengers((pDatabase));

    for(int pList = 0;pList < max;pList++){
        char * pUId = getPassengerUserId((Passenger *)list[pList]);
        if(!strcoll(pUId,userId)) uFlights++;
        ffree((void **) &pUId);
    }

    ffree((void **) &list);

    return uFlights;
}

Temporary * getUserFlights(void * fDatabase,void * travels,const char * userId){
    Flights * allFlights = (Flights *) fDatabase;
    Passengers * pDatabase = (Passengers *) travels;

    Temporary * book = createTemporary();

    int max = getNumAllPassengers(pDatabase);
    setTempMax(book,max);


    void ** tList = NULL;
    initArrays(&tList,max); 

    setTempList(book,tList);

    Passenger ** list = getAllPassengers(pDatabase);
     
    unsigned int w = 0;
    for(int passengersList = 0;passengersList < max;passengersList++){
        char * pUId = getPassengerUserId((Passenger *) list[passengersList]);
        if(!strcoll(pUId,userId)){
            char * pFId = getPassengerFlightId((Passenger *) list[passengersList]);
            Flight * flight = (Flight *) lookupElement(allFlights,pFId);
            if(flight && w < max){
                setTempListElement(book,(void *) flight,w);
                incTempNum(book);
            }
            passengersList++;
            char * pFId2 = getPassengerFlightId((Passenger *) list[passengersList]);
            while(!strcoll(pFId,pFId2) && passengersList < max){
                passengersList += 5;
                ffree((void **) &pFId2);
                pFId2 = getPassengerFlightId((Passenger *) list[passengersList]);
            }
            while(strcoll(pFId,pFId2) != 0 && passengersList > 0){
                passengersList--;
                ffree((void **) &pFId2);
                pFId2 = getPassengerFlightId((Passenger *) list[passengersList]);
                
            }
            ffree((void **) &pFId2);
            ffree((void **) &pFId);
            w++;
        }
        ffree((void **) &pUId);
    }
    ffree((void **) &list);
    return book;
}


Temporary * getFlightPassengers(void * fDatabase,void * travels,const char * flightId){
    Flights * allFlights = (Flights *) fDatabase;
    Passengers * pDatabase = (Passengers *) travels;

    Temporary * book = createTemporary();

    void ** list = NULL;
    initArrays(&list,getDatabaseSize(allFlights));
    setTempList(book,list);
    

    int max = getNumAllPassengers(pDatabase);
    Passenger ** pList = getAllPassengers(pDatabase); 

    
    if(pList == NULL){
        fprintf(stderr, "Error: Memory allocation failed for book->list.\n");
        return book;
    }
   

    
    int j = 0;
    char * flight_id = getPassengerFlightId(pList[j]);

    int compare = 0;
    compare = strcoll(flight_id,flightId);

    for(;compare != 0 && j < max;){
        ffree((void **)&flight_id);
        j += 10;
        flight_id = getPassengerFlightId(pList[j]);
        compare = strcoll(flight_id,flightId);
    }


    for(;compare == 0 && j > 0;){
        j--;
        ffree((void **)&flight_id);
        flight_id = getPassengerFlightId(pList[j]);
        compare = strcoll(flight_id,flightId);
    }


    j++;
    ffree((void **) &flight_id);

    flight_id = getPassengerFlightId(pList[j]);
    while(!strcoll(flight_id,flightId)){
        incTempNum(book);
        ffree((void **) &flight_id);
        j++;
        flight_id = getPassengerFlightId(pList[j]);
        continue;
    }
    ffree((void **) &flight_id);


    
    ffree((void **) &pList);

    return book;
}

void countHotelReservs(gpointer key,gpointer value,gpointer hotelData){
    Temporary * array = (Temporary *) hotelData;
    Reservation * reservation = (Reservation *) value;
    char * hotelId = getReservHotelId(reservation);
    Time * beginDate = getReservBeginDate(reservation);
    Time * endDate = getReservEndDate(reservation);
    Time * beginLimit = getTempBegin(array);
    Time * endLimit = getTempEnd(array);
    char * wantedHotel = getTempId(array);

    if(beginLimit != NULL && endLimit != NULL){
        if (!strcoll(hotelId,wantedHotel) && 
        (compareTimes(beginDate,endLimit) || compareTimes(beginDate,endLimit) == 10) && 
        (compareTimes(beginLimit,endDate) || compareTimes(beginLimit,endDate) == 10)) {
          int rating = getReservRating(reservation);
          increaseTempSum(array,rating);
          incTempNum(array);
          i++;
        }
    }else{
        if(!strcoll(hotelId,wantedHotel)) {
          int rating = getReservRating(reservation);
          increaseTempSum(array,rating);
          incTempNum(array);
          i++;
        }
    }
    destroyTime(beginLimit);
    destroyTime(endLimit);
    destroyTime(beginDate);
    destroyTime(endDate);
    ffree((void **) &wantedHotel);
    ffree((void **) &hotelId);
}

void allHotelReservs(gpointer key, gpointer value, gpointer hotelData) {
    Temporary * array = (Temporary *) hotelData;
    Reservation * reservation = (Reservation *) value;
    char * hotelId = getReservHotelId(reservation);
    Time * beginDate = getReservBeginDate(reservation);
    Time * endDate = getReservEndDate(reservation);
    Time * beginLimit = getTempBegin(array);
    Time * endLimit = getTempEnd(array);
    char * wantedHotel = getTempId(array);

    if(beginLimit != NULL && endLimit != NULL){
        if (!strcoll(hotelId,wantedHotel) && 
        (compareTimes(beginDate,endLimit) || compareTimes(beginDate,endLimit) == 10) && 
        (compareTimes(beginLimit,endDate) || compareTimes(beginLimit,endDate) == 10)) {
            setTempListElementReservation(array,reservation,i);
            int rating = getReservRating(reservation);
            increaseTempSum(array,rating);
            incTempNum(array);
            i++;  
        }
        destroyTime(beginLimit);
        destroyTime(endLimit);
        destroyTime(beginDate);
        destroyTime(endDate);
        ffree((void **) &wantedHotel);
        ffree((void **) &hotelId);
        return;
    }
    if(!strcoll(hotelId,wantedHotel)) {
        setTempListElementReservation(array,reservation,i);
        int rating = getReservRating(reservation);
        increaseTempSum(array,rating);
        incTempNum(array);
        i++;
    }
    destroyTime(beginLimit);
    destroyTime(endLimit);
    destroyTime(beginDate);
    destroyTime(endDate);
    ffree((void **) &wantedHotel);
    ffree((void **) &hotelId);
}




void allUserReservs(gpointer key ,gpointer value,gpointer userData){
    Temporary * array = (Temporary *) userData;
    Reservation * reserv = (Reservation *) value;
    char * rId = getReservUserId(reserv);
    char * wantedId = getTempId(array);

    if(!strcoll(rId,wantedId)){
        setTempListElement(array,(void *) reserv,i);
        incTempNum(array);
        i++;
    }
    free(rId);
    free(wantedId);
}



void checkAirports(gpointer key,gpointer value,gpointer flightData){
    Flight * flight = (Flight *) value;
    Temporary * database = (Temporary *) flightData;
    char * origin = getFlightOrigin(flight);
    Time * sDepartureDate = getFlightSDepartureDate(flight);
    Time * SArrivalDate = getFlightSArrivalDate(flight);
    Time * beginLimit = getTempBegin(database);
    Time * endLimit = getTempEnd(database);
    char * airport = getTempId(database);

    if(beginLimit && endLimit){
        if(!strcoll(airport,origin) && 
        compareTimes(sDepartureDate,endLimit)==true && 
        compareTimes(beginLimit,SArrivalDate)==true){
            setTempListFlight(database,flight,i);
            i++;
            incTempNum(database);
        }
    }
    else{
        if(!strcoll(airport,origin)){
            setTempListFlight(database,flight,i);
            i++;
            incTempNum(database);
        }
    }
    free(airport);
    destroyTime(beginLimit);
    destroyTime(endLimit);

    free(origin);
    destroyTime(sDepartureDate);
    destroyTime(SArrivalDate);
}

SingularRecord * getYearFlights(const void * database,const void * databasep, const int fYear){
    Flights * fDatabase = (Flights *) database;
    SingularRecord * airports = createSRecord(30);

    i = 0;
    applyForEach(fDatabase,&yearFlight,airports);

    countFPassengers(databasep,database,(void *) airports,fYear);

    return airports;
}

void yearFlight(gpointer key, gpointer value, gpointer data){
    Flight * flight = (Flight *) value;
    SingularRecord * record = (SingularRecord *) data;
    char * origin = getFlightOrigin(flight);
    char * dest = getFlightDestination(flight);
    int max = getSRecordSize(record);
    int j = 0;
    int destPosition = -1,originPosition = -1;
    for(;j < max;j++){
        char * name = getSRecordName(record,j);
        if(!strcoll(name,origin)){
            originPosition = j;
        }
        if(!strcoll(name,dest)){
            destPosition = j;
        }
        if(originPosition != -1 && destPosition != -1){
            ffree((void **) &origin);
            ffree((void **) &dest);
            ffree((void **) &name);
            return;
        }
        ffree((void **) &name);
    }
    if(originPosition == -1 && destPosition != -1){
        setSRecordName(record,j,origin);
        setSRecordListElement(record,j,0);
        incSRecordSize(record);
        ffree((void **) &origin);
        ffree((void **) &dest);
        return;
    }
    if(originPosition != -1 && destPosition == -1){
        setSRecordName(record,j,dest);
        setSRecordListElement(record,j,0);
        incSRecordSize(record);
        ffree((void **) &origin);
        ffree((void **) &dest);
        return;
    }
    if(originPosition == -1 && destPosition == -1){
        setSRecordName(record,j,origin);
        setSRecordListElement(record,j,0);
        incSRecordSize(record);

        setSRecordName(record,j + 1,dest);
        setSRecordListElement(record,j + 1,0);
        incSRecordSize(record);

        ffree((void **) &origin);
        ffree((void **) &dest);
        return;
    }
    
}

void countFPassengers(const void * pDatabase,const void * fDatabase,void * record,int year){
    Passengers * passengers = (Passengers *) pDatabase;
    SingularRecord * table = (SingularRecord *) record;
    
    int k = 0; // Marks the first element of the block of flights
    int max = getNumAllPassengers(pDatabase);
    Passenger ** p = getAllPassengers(passengers);

    while(k < max){ // Run through every passenger on the database

        // Get the flight and its year
        char * id = getPassengerFlightId(p[k]);
        Flight * flight = (Flight *) lookupElement(fDatabase,id);
        Time * time1 = getFlightSDepartureDate(flight);

        int year1 = getYear(time1);

        if(year == year1){ // Procedure to execute in case the flight took place on the year
            // Get the airports and their positions on the structure
            char * departAirport = getFlightOrigin(flight);
            char * arriveAirport = getFlightDestination(flight);

            int departPosition = getSRecordNamePosition(table,departAirport);
            int arrivePosition = getSRecordNamePosition(table,arriveAirport);
            
            // Check if they are on the array
            bool dep = false,arr = false;
            if(departPosition > -1) dep = true;
            if(arrivePosition > -1) arr = true;

            int j = k; // Block iteration count 

            // This cycle should only be executed if any of the airports is in the array
            if(dep == true || arr == true){ 
                while(j < max){ // The cycle must count the amount of users on the flight and add them to the airports in which the flights arrive/depart
                    char * aux = getPassengerFlightId(p[j]);
                    if(!strcoll(aux,id)){
                        if(dep == true) incSRecordListElement(table,departPosition);
                        if(arr == true) incSRecordListElement(table,arrivePosition);
                        j++;
                        ffree((void **) &aux);
                        continue;
                    }
                    ffree((void **) &aux);
                    break;
                }
            }else{
                goto nonexistent;
            }

            k = j; // Set k to the value of the next flight id, so it does not go through nonsense checks

            ffree((void **) &departAirport);
            ffree((void **) &arriveAirport);


            ffree((void **) &id);
            year1 = 0;
            destroyTime(time1);

            continue;
        }
            
        
        nonexistent:
        int j = k;
        while(j < max){
            char * aux = getPassengerFlightId(p[j]);
            if(!strcoll(aux,id)){
                ffree((void **) &aux);
                j += 10;
                continue;
            }
            ffree((void **) &aux);
            for(int z = 1;z < 11;z++){
                aux = getPassengerFlightId(p[j - z]);
                if(!strcoll(aux,id)){
                    j -= z;
                    j++;
                    ffree((void **) &aux);
                    break;
                }
                ffree((void **) &aux);
            }
            
            break;
        }
        
        year1 = 0;
        destroyTime(time1);

        k = j;
        ffree((void **) &id);
    }
    ffree((void **) &p);
}

SingularRecord * getDelays(void * database){
    MultipleRecord * temp = createMRecord(30);
    i = 0;
    applyForEach(database,&getAirportsDelays,(void *)temp); // Fill up MRcreateMRecord with information

    int max = getMRecordSize(temp); // Get then number of different airports

    int * allDelays = malloc(sizeof(int) * max);// Get a list of the median of each airport delay
    char ** airports = malloc(sizeof(char *) * max);
    for(int j = 0;j < max;j++){
        int * array = (int *) getMRecordList(temp,j);
        mergeSort((void **)&array,getMRecordListSize(temp,j),"Int");
        //setMRecordList(temp,j,array,getMRecordListSize(temp,j));
        allDelays[j] = delayMedianAirport(array,getMRecordListSize(temp,j));
        airports[j] = getMRecordNamesElement(temp,j);
        ffree((void **) &array);
    }
    destroyMRecord(&temp);
    void ** aux = malloc(sizeof(void *) * 2);
    aux[0] = (void *) allDelays;
    aux[1] = (void *) airports;
    mergeSort((void **) aux,max,"Integers");
    ffree((void **) &aux);
    SingularRecord * sorted = createSRecord(max);
    setSRecordSize(sorted,max);
    for(int j = 0;j < max;setSRecordName(sorted,j,airports[j]),j++);
    for(int j = 0;j < max;setSRecordListElement(sorted,j,allDelays[j]),j++);
    for(int j = 0;j < max;ffree((void **) &airports[j]),j++);
    ffree((void **) &airports);
    ffree((void **) &allDelays);
    return sorted;
}

void getAirportsDelays(gpointer key,gpointer value,gpointer data){
    Flight * flight = (Flight *) value; // Cast for the flight that is being analysed


    int delay = getFlightDelay(flight); // Get the delay 
    char * origin = getFlightOrigin((Flight *)value); // Get the airport of the flight
    int max = getMRecordSize((MultipleRecord *)data); // Get how many differents airports I have on the list

    
    bool flag = false; // Flag to check if the airport is already on the list

    if(max == 0){ // Case of the first iteration

        // Set the first airport for the first 
        // element of the airports list
        setMRecordNamesElement((MultipleRecord *) data,0,origin); 

        // Set the first flight delay for the first 
        // element of the delays list
        setMRecordListElement((MultipleRecord *) data,0,0,delay);
        incMRecordListSize((MultipleRecord *) data,0);
        incMRecordSize((MultipleRecord *) data); // Increments the number of diferents airports
        
        ffree((void **) &origin);
        i++;
        return;
    }

    for(int j = 0;j < max;j++){ // Checks if the airport is already on the list
        char * listOrigin = getMRecordNamesElement((MultipleRecord *) data,j);
        if(!strcoll(listOrigin,origin)){
            ffree((void **) &listOrigin);
            ffree((void **) &origin);
            int position = getMRecordListSize((MultipleRecord *) data,j);
            setMRecordListElement((MultipleRecord *) data,j,position,delay); // Sets the delay for the respetive position
            incMRecordListSize((MultipleRecord *) data,j);
            flag = true;
            i++;
            return;
        }
        ffree((void **) &listOrigin);
    }

    if(flag == false){
        setMRecordNamesElement((MultipleRecord *) data,max,origin);
        setMRecordListElement((MultipleRecord *) data,getMRecordSize((MultipleRecord *) data),0,delay);
        incMRecordListSize((MultipleRecord *) data,getMRecordSize((MultipleRecord *) data));
        incMRecordSize((MultipleRecord *) data);
    }
    ffree((void **) &origin);
    i++;
}

Temporary * getUsersPre(void * database, char * prefix){
    Users * uDatabase = (Users *) database;

    char ** preUsersIds = malloc(sizeof(char*) *10000);
    for(int j = 0;j < 10000;j++){
        preUsersIds[j] = NULL;
    }
    char ** preUsersNames = malloc(sizeof(char*)*10000);
    for(int j = 0;j < 10000;j++){
        preUsersNames[j] = NULL;
    }

    Temporary * list = createTemporary();
    setTempAux(list,(void *) preUsersIds);
    setTempList(list,(void **)preUsersNames);
    setTempMax(list,10000);
    setTempId(list,prefix);

    applyForEach(uDatabase,&checkPre,(void *)list);

    return list;
}

void checkPre(gpointer key, gpointer value, gpointer data){
    User * user = (User *) value;
    Temporary * temp = (Temporary *) data;
    char * userId = getUserId(user);
    char * userName = getUserName(user);
    char * prefix = getTempId(temp);
    bool status = getUserAccountStatus(user);


    int preSize = strlen(prefix);
    int nameSize = strlen(userName);

    if(nameSize < preSize) return;


    if(strncmp(userName,prefix,preSize)==0 && status ==1){
        int num = getTempNum(temp);
        setTempListElementChar(temp,userName,num);
        setTempAuxElementChar(temp,userId,num);
        setTempNum(temp,num+1);
    }    
    ffree((void **) &userName);
    ffree((void **) &userId);
    ffree((void **) &prefix);
}