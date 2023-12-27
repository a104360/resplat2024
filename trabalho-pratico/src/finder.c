#include "../include/finder.h"
#include "../include/utils.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include <glib.h>


static int i = 0;

Temporary * getAListOfSomething(void * database,const char * hotelId,Time * begin,Time * end,void (*func)(gpointer,gpointer,gpointer)){
    Temporary * temp = createTemporary();
    void ** list = NULL; //= malloc(sizeof(void *) * 500);
    initArrays(&list,500);
    setTempList(temp,list);
    setTempId(temp,(char *) hotelId);
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
            ffree(pFId);
            i++;
        }
        //free(pUId);
        //pUId = NULL;
        ffree(pUId);
    }
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
