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
    Database * allFlights = (Database *) fDatabase;
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
                //tList[getTempNum(book)] = (void *) flight;
                setTempListElement(book,(void *) flight,i);
                incTempNum(book);
            }
            ffree((void **) &pFId);
            i++;
        }
        //free(pUId);
        //pUId = NULL;
        ffree((void **) &pUId);
    }
    ffree((void **) &list);
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
            setTempListElement(book,(void *) lookupPassengerFID(pDatabase,flight_id),getTempNum(book));
            incTempNum(book);
        }
        free(flight_id);
    }
    
    ffree((void **) &pList);

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
                ffree((void **) &hotelId);
                destroyTime(beginDate);
                destroyTime(endDate);
                destroyTime(beginLimit);
                destroyTime(endLimit);
                ffree((void **) &wantedHotel);
                ffree((void **) &list);
                return;
            }
            list = aux;
            setTempList(array,list);         
            setTempMax(array,getTempMax(array) * 2);
            ffree((void **) &aux);
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
                ffree((void **) &hotelId);
                destroyTime(beginDate);
                destroyTime(endDate);
                destroyTime(beginLimit);
                destroyTime(endLimit);
                ffree((void **) &wantedHotel);
                ffree((void **) &list);
                return;
            }
            list = aux;
            setTempList(array,list);         
            setTempMax(array,getTempMax(array) * 2);
            ffree((void **) &aux);     
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

    Flight ** temp = malloc(sizeof(Flight *) * 2000);
    SingularRecord * airports = createSRecord(50);


    Temporary * list = createTemporary();
    setTempAux(list,(void *) airports);
    setTempDatabase(list,(void *) databasep);

    setTempList(list,(void **)temp);
    setTempSum(list,fYear);

    applyForEach(fDatabase,&yearFlight,list);

    setTempAux(list,NULL);

    destroyTemporary(list);

    return airports;
}


void yearFlight(gpointer key, gpointer value, gpointer data){
    Flight * flight = (Flight *) value;
    Temporary * temp = (Temporary *) data;
    char * flightId = getFlightId(flight);
    int selectedYear = getTempSum(temp);
    Time * date = getFlightSDepartureDate(flight);
    Time * date2 = getFlightRDepartureDate(flight);
    Time * date3 = getFlightSArrivalDate(flight);
    Time * date4 = getFlightRArrivalDate(flight);
    int year = getYear(date);
    int year2 = getYear(date2);
    int year3 = getYear(date3);
    int year4 = getYear(date4);
    SingularRecord * aux = (SingularRecord *) getTempAux(temp);

    bool flag = false;

    if(selectedYear == year || selectedYear == year2){

        char * origin = getFlightOrigin(flight);
        int max = getSRecordSize(aux);
        Passengers * pDatabase = getTempDatabase(temp);

        for(int j = 0;j < max;j++){

            char * airport = getSRecordName(aux,j);
            if(!strcoll(airport,origin)){

                int n = getSRecordListElement(aux,j);
                setSRecordListElement(aux,j,n + countFPassengers(flightId,(void *)pDatabase));
                flag = true;
                ffree((void **) &airport);
                break;

            }
            ffree((void **) &airport);
        }
        if(flag == false){
            
            setSRecordName(aux,max,origin);
            setSRecordListElement(aux,max,countFPassengers(flightId,(void *) pDatabase));
            setSRecordSize(aux,getSRecordSize(aux) + 1);

        }
        ffree((void **) &origin);
        

    }

    flag = false;

        if(selectedYear == year3 || selectedYear == year4){

        char * destination = getFlightDestination(flight);
        int max = getSRecordSize(aux);
        Passengers * pDatabase = getTempDatabase(temp);

        for(int j2 = 0;j2 < max;j2++){

            char * airport = getSRecordName(aux,j2);
            if(!strcoll(airport,destination)){

                int n = getSRecordListElement(aux,j2);
                setSRecordListElement(aux,j2,n + countFPassengers(flightId,(void *)pDatabase));
                flag = true;
                ffree((void **) &airport);
                break;

            }
            ffree((void **) &airport);
        }
        if(flag == false){
            
            setSRecordName(aux,max,destination);
            setSRecordListElement(aux,max,countFPassengers(flightId,(void *) pDatabase));
            setSRecordSize(aux,getSRecordSize(aux) + 1);

        }
        ffree((void **) &destination);
        

    }

    ffree((void **) &flightId);
    destroyTime(date);
    destroyTime(date2);
    destroyTime(date3);
    destroyTime(date4);
    

}

int countFPassengers(const char * flightId,const void * database){
    Passengers * pDatabase = (Passengers *) database;
    int count = 0;
    int k = 0;
    int max = getNumAllPassengers(pDatabase);
    Passenger ** p = getAllPassengers(pDatabase);

    while(k < max){
        char * id = getPassengerFlightId(p[k]);
        if(!strcoll(flightId,id)){
            count++;
        }
        k++;
        ffree((void **) &id);
    }
    ffree((void **) &p);
    return count;
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
        ffree((void **) &origin);
        return;
    }

    for(int j = 0;j < max;j++){ // Checks if the airport is already on the list
        char * listOrigin = getMRecordNamesElement(temp,j);
        if(!strcoll(listOrigin,origin)){
            setMRecordListElement(temp,j,getMRecordListSize(temp,j),delay); // Sets the delay for the respetive position
            incMRecordListSize(temp,j);
            flag = true;
            ffree((void **) &listOrigin);
            break;
        }
        ffree((void **) &listOrigin);
    }
    if(flag == false){
        setMRecordNamesElement(temp,max,(void *)origin);
        setMRecordListElement(temp,getMRecordSize(temp),0,delay);
        incMRecordListSize(temp,getMRecordSize(temp));
        incMRecordSize(temp);
    }
    ffree((void **) &origin);
}