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
#include <glib.h>


static int i = 0;

Temporary * getAListOfSomething(void * database,const char * hotelId,Time * begin,Time * end,void (*func)()){
    Temporary * temp = createTemporary();
    void ** list = NULL; //= malloc(sizeof(void *) * 500);
    initArrays(&list,500);
    setTempList(temp,list);
    if(hotelId) setTempId(temp,(char *) hotelId);
    setTempBegin(temp,begin);
    setTempEnd(temp,end);
    setTempMax(temp,500);
    i = 0;
    applyForEach(database,func,(void *)temp);
    return temp;
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
     
    i = 0;
    for(int passengersList = 0;passengersList < max;passengersList++){
        char * pUId = getPassengerUserId((Passenger *) list[passengersList]);
        if(!strcoll(pUId,userId)){
            char * pFId = getPassengerFlightId((Passenger *) list[passengersList]);
            Flight * flight = (Flight *) lookupElement(allFlights,pFId);
            if(flight){
                setTempListElement(book,(void *) flight,i);
                incTempNum(book);
            }
            char * pFId2 = getPassengerFlightId((Passenger *) list[passengersList + 1]);
            while(!strcmp(pFId,pFId2)){
                passengersList++;
                ffree(pFId2);
                pFId2 = getPassengerFlightId((Passenger *) list[passengersList]);
            }
            ffree(pFId2);
            ffree(pFId);
            i++;
        }
        ffree(pUId);
    }
    ffree(list);
    return book;
}


Temporary * getFlightPassengers(void * fDatabase,void * travels,const char * flightId){
    Database * allFlights = (Database *) fDatabase;
    Passengers * pDatabase = (Passengers *) travels;

    Temporary * book = createTemporary();

    void ** list = NULL;// = malloc(sizeof(void *) * g_hash_table_size((GHashTable *) allFlights)); 
    initArrays(&list,getDatabaseSize(allFlights));
    setTempList(book,list);
    

    int max = getNumAllPassengers(pDatabase);
    Passenger ** pList = getAllPassengers(pDatabase); 

    
    if(pList == NULL){
        fprintf(stderr, "Error: Memory allocation failed for book->list.\n");
        return book;
    }
    
    for(int passengersList = 0;passengersList < max;passengersList++){
        char * flight_id = getPassengerFlightId(pList[passengersList]);
        if(!strcoll(flight_id,flightId)){
            //setTempListElement(book,(void *) lookupPassengerFID(pDatabase,flight_id),getTempNum(book));
            incTempNum(book);
            
        }
        free(flight_id);
    }
    
    ffree(pList);

    return book;
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
          if(i == getTempMax(array)){
            void ** list = getTempList(array);
            void ** aux = realloc(list,(getTempMax(array) * 2) * sizeof(void *));
            if(!aux){
                fprintf(stderr,"Error allocating memory for the list");
                ffree(hotelId);
                destroyTime(beginDate);
                destroyTime(endDate);
                destroyTime(beginLimit);
                destroyTime(endLimit);
                ffree(wantedHotel);
                ffree(list);
                return;
            }
            list = aux;
            setTempList(array,list);         
            setTempMax(array,getTempMax(array) * 2);
            ffree(aux);
          }
          setTempListElement(array,reservation,i);
          int rating = getReservRating(reservation);
          //setTempSum(array,getTempSum(array) + rating);
          increaseTempSum(array,rating);
          incTempNum(array);
          i++;
        }
    }else{
        if(!strcoll(hotelId,wantedHotel)) {
          if(i == getTempMax(array)){
           void ** list = getTempList(array);
            void ** aux = realloc(list,(getTempMax(array) * 2) * sizeof(void *));
            if(!aux){
                fprintf(stderr,"Error allocating memory for the list");
                ffree(hotelId);
                destroyTime(beginDate);
                destroyTime(endDate);
                destroyTime(beginLimit);
                destroyTime(endLimit);
                ffree(wantedHotel);
                ffree(list);
                return;
            }
            list = aux;
            setTempList(array,list);         
            setTempMax(array,getTempMax(array) * 2);
            ffree(aux);     
          }
          setTempListElement(array,reservation,i);
          int rating = getReservRating(reservation);
          //setTempSum(array,getTempSum(array) + rating);
          increaseTempSum(array,rating);
          incTempNum(array);
          i++;
        }
    }
    destroyTime(beginLimit);
    destroyTime(endLimit);
    destroyTime(beginDate);
    destroyTime(endDate);
    ffree(wantedHotel);
    ffree(hotelId);
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
            setTempListElement(database,(void *) value,i);
            i++;
            incTempNum(database);
        }
    }
    else{
        if(!strcoll(airport,origin)){
            setTempListElement(database,(void *) value,i);
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
    SingularRecord * airports = createSRecord(50);

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
            ffree(origin);
            ffree(dest);
            ffree(name);
            return;
        }
        ffree(name);
    }
    if(originPosition == -1 && destPosition != -1){
        setSRecordName(record,j,origin);
        setSRecordListElement(record,j,0);
        incSRecordSize(record);
        ffree(origin);
        ffree(dest);
        return;
    }
    if(originPosition != -1 && destPosition == -1){
        setSRecordName(record,j,dest);
        setSRecordListElement(record,j,0);
        incSRecordSize(record);
        ffree(origin);
        ffree(dest);
        return;
    }
    if(originPosition == -1 && destPosition == -1){
        setSRecordName(record,j,origin);
        setSRecordListElement(record,j,0);
        incSRecordSize(record);

        setSRecordName(record,j + 1,dest);
        setSRecordListElement(record,j + 1,0);
        incSRecordSize(record);

        ffree(origin);
        ffree(dest);
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
                        ffree(aux);
                        continue;
                    }
                    ffree(aux);
                    break;
                }
            }else{
                goto nonexistent;
            }

            k = j; // Set k to the value of the next flight id, so it does not go through nonsense checks

            ffree(departAirport);
            ffree(arriveAirport);


            ffree(id);
            year1 = 0;
            destroyTime(time1);

            continue;
        }
            
        
        nonexistent:
        int j = k;
        while(j < max){
            char * aux = getPassengerFlightId(p[j]);
            if(!strcoll(aux,id)){
                ffree(aux);
                j++;
                continue;
            }
            ffree(aux);
            break;
        }
        
        year1 = 0;
        destroyTime(time1);

        ffree(id);
        k = j;
    }
    ffree(p);
}

SingularRecord * getDelays(void * database){
    MultipleRecord * temp = createMRecord(30);
    applyForEach(database,&getAirportsDelays,(void *)temp); // Fill up MRcreateMRecord with information

    int max = getMRecordSize(temp); // Get then number of different airports

    int * allDelays = malloc(sizeof(int) * max);// Get a list of the median of each airport delay
    char ** airports = malloc(sizeof(char *) * max);
    for(int j = 0;j < max;j++){
        int * array = (int *) getMRecordList(temp,j);
        mergeSort((void **)&array,getMRecordListSize(temp,j),"Int");
        setMRecordList(temp,j,array,getMRecordListSize(temp,j));
        allDelays[j] = delayMedianAirport(array,getMRecordListSize(temp,j));
        airports[j] = getMRecordNamesElement(temp,j);
        ffree(array);
    }
    destroyMRecord(temp);
    void ** aux = malloc(sizeof(void *) * 2);
    aux[0] = (void *) allDelays;
    aux[1] = (void *) airports;
    mergeSort((void **) aux,max,"Integers");
    ffree(aux);
    SingularRecord * sorted = createSRecord(max);
    setSRecordSize(sorted,max);
    for(int j = 0;j < max;setSRecordName(sorted,j,airports[j]),j++);
    for(int j = 0;j < max;setSRecordListElement(sorted,j,allDelays[j]),j++);
    for(int j = 0;j < max;ffree(airports[j]),j++);
    ffree(airports);
    ffree(allDelays);
    return sorted;
}

void getAirportsDelays(gpointer key,gpointer value,gpointer data){
    MultipleRecord * temp = (MultipleRecord *) data; // Cast for the temp struct
    Flight * flight = (Flight *) value; // Cast for the flight that is being analysed


    int delay = getFlightDelay(flight); // Get the delay 
    char * origin = getFlightOrigin(flight); // Get the airport of the flight
    int max = getMRecordSize(temp); // Get how many differents airports I have on the list

    bool flag = false; // Flag to check if the airport is already on the list

    if(max == 0){ // Case of the first iteration

        // Set the first airport for the first 
        // element of the airports list
        setMRecordNamesElement(temp,0,origin); 

        // Set the first flight delay for the first 
        // element of the delays list
        setMRecordListElement(temp,0,0,delay);
        incMRecordListSize(temp,0);
        incMRecordSize(temp); // Increments the number of diferents airports
        ffree(origin);
        return;
    }

    for(int j = 0;j < max;j++){ // Checks if the airport is already on the list
        char * listOrigin = getMRecordNamesElement(temp,j);
        if(!strcoll(listOrigin,origin)){
            setMRecordListElement(temp,j,getMRecordListSize(temp,j),delay); // Sets the delay for the respetive position
            incMRecordListSize(temp,j);
            flag = true;
            ffree(listOrigin);
            break;
        }
        ffree(listOrigin);
    }
    if(flag == false){
        setMRecordNamesElement(temp,max,(void *)origin);
        setMRecordListElement(temp,getMRecordSize(temp),0,delay);
        incMRecordListSize(temp,getMRecordSize(temp));
        incMRecordSize(temp);
    }
    ffree(origin);
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


    if(strncmp(userName,prefix,strlen(prefix))==0 && status ==1){
        int max = getTempMax(temp);
        setTempListElementChar(temp,userName,max);
        setTempAuxElementChar(temp,userId,max);
        setTempMax(temp,max+1);
    }    
    ffree(userName);
    ffree(userId);
    ffree(prefix);
}