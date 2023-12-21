#include "../include/catalogs.h"
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/passenger.h"
#include "../include/reservation.h"
#include "../include/dataStructs.h"
#include "../include/time.h"
#include <stdio.h>
#include <ctype.h>
#include <glib.h>


#define BUFFERSIZE 1000



// Inits the flights database
UsersDatabase initUsers(){
    UsersDatabase flights = g_hash_table_new_full(g_str_hash,g_str_equal,free,(GDestroyNotify) destroyUser);
    return flights;
}

// Inserts the flight on the database by the flight id
void insertUser(void * structs,User * user){
    g_hash_table_insert((UsersDatabase)structs,(gpointer)getUserId(user),(gpointer) user);
}

// Returns the flight based on the id
User * lookupUser(void * table ,const char * id){
    User * user = g_hash_table_lookup((UsersDatabase) table,(gconstpointer) id);
    return user;
}

void destroyUsers(UsersDatabase database){
    //g_hash_table_foreach(database,destroyUDB,NULL);
    g_hash_table_destroy(database);
}












// Inits the flights database
FlightsDatabase initFlights(){
    FlightsDatabase flights = g_hash_table_new_full(g_str_hash,g_str_equal,free,(GDestroyNotify)destroyFlight);
    return flights;
}

// Inserts the flight on the database by the flight id
void insertFlight(void * structs,Flight * flight){
    char * key = getFlightId(flight);
    g_hash_table_insert((FlightsDatabase)structs,(gpointer)key,(gpointer) flight);
}

// Returns the flight based on the id
Flight * lookupFlight(void * table ,const char * id){
    Flight * flight = g_hash_table_lookup((FlightsDatabase) table,(gconstpointer) id);
    return flight;
}


void destroyFlights(FlightsDatabase database){
    //g_hash_table_foreach(database,destroyFDB,NULL); 
    g_hash_table_destroy(database);
}





























// Inits the reservations database
ReservationsDatabase initReservations(){
    ReservationsDatabase reservs = g_hash_table_new_full(g_str_hash,g_str_equal,free,(GDestroyNotify) destroyReservation);
    return reservs;
}

// Inserts the reservations based on the reservations id
void insertReserv(void * structs,Reservation * reserv){
    g_hash_table_insert((ReservationsDatabase) structs,(gpointer) getReservId(reserv),(gpointer) reserv);
}

// Returns the reservations by the reservations id
Reservation * lookupReserv(void * table,const char * reservId){
    Reservation * reserv = g_hash_table_lookup((ReservationsDatabase ) table,(gconstpointer) reservId);
    return reserv;
}

void destroyReservs(ReservationsDatabase database){
    //g_hash_table_foreach(database,destroyRDB,NULL);
    g_hash_table_destroy(database);
}






















static int i = 0;



//                             *** Get Hotel Reservations ***

typedef struct hotelDatabase{
    struct reservation ** _hotelReservs;
    char * hotel_id;
    Time * begin;
    Time * end;
    int sumRatings;
    int numReservas;
} HotelDatabase;



int getSumRatings(void * hReservs){
    HotelDatabase * reservs = (HotelDatabase *) hReservs;
    return reservs->sumRatings;
}

int getNumReservas(void * hReservs){
    HotelDatabase * reservs = (HotelDatabase *) hReservs;
    return reservs->numReservas;
}

Reservation ** getAllHotelReservs(const HotelDatabase * hotelData){
    return hotelData->_hotelReservs;
}

// Returns the reservations by the hotel id
HotelDatabase * getHotelDataBase(void * reservations,const char * hotelId,Time * begin,Time * end){
    HotelDatabase * reservs = malloc(sizeof(struct hotelDatabase));
    reservs->hotel_id = strdup(hotelId);
    reservs->begin = begin;
    reservs->end = end;
    reservs->numReservas = 0;
    reservs->sumRatings = 0;
    i = 0;
    int n = g_hash_table_size((ReservationsDatabase)  reservations);
    reservs->_hotelReservs = malloc(sizeof(Reservation *) * n);
    for(int j = 0;j < n;reservs->_hotelReservs[j] = NULL,j++);
    g_hash_table_foreach((ReservationsDatabase) reservations,allHotelReservs,reservs);
    return reservs;
}

// Function to iterate and get the reservations on the list
void allHotelReservs(gpointer key, gpointer value, gpointer hotelData) {
    HotelDatabase * array = (HotelDatabase *) hotelData;
    Reservation * reservation = (Reservation *) value;
    char * hotelId = getReservHotelId(reservation);
    Time * beginDate = getReservBeginDate(reservation);
    Time * endDate = getReservEndDate(reservation);

    if(array->begin != NULL && array->end != NULL){
        if (!strcoll(hotelId,array->hotel_id) && 
        (compareTimes(beginDate,array->end) || compareTimes(beginDate,array->end) == 10) && 
        (compareTimes(array->begin,endDate) || compareTimes(array->begin,endDate) == 10)) {
          array->_hotelReservs[i] = reservation;
          int rating = getReservRating(reservation);
          array->sumRatings += rating;
          array->numReservas++;
          i++;
        }
    }else{
        if(!strcoll(hotelId,array->hotel_id)) {
          array->_hotelReservs[i] = reservation;
          int rating = getReservRating(reservation);
          array->sumRatings += rating;
          array->numReservas++;
          i++;
        }
    }
    destroyTime(beginDate);
    destroyTime(endDate);
    free(hotelId);
}

void destroyHotelDatabase(HotelDatabase * hotel){
    free(hotel->hotel_id);
    hotel->hotel_id = NULL;
    
    free(hotel->_hotelReservs);
    hotel->_hotelReservs = NULL;

    free(hotel);
    hotel = NULL;
}

//                                  *** End block ***



//                      *** Get all the reservations of a user ***

typedef struct userReservsDB{
    struct reservation ** _userReservs;
    char * userId;
    int size;
} UserReservsDB;



UserReservsDB * getUserReservsDB(const void * table,const char * userId){
    UserReservsDB * reservs = malloc(sizeof(struct userReservsDB));
    reservs->userId = strdup(userId);
    reservs->size = 0;
    reservs->_userReservs = malloc(sizeof(Reservation *) * 1000);
    if(reservs->_userReservs == NULL){
        perror("Memory was not allocated for the users reservs list!\n");
        return NULL;
    }
    for(int i = 0;i < 1000;i++){
        reservs->_userReservs[i] = NULL;
    }
    i = 0;
    g_hash_table_foreach((const ReservationsDatabase) table,allUserReservs,(gpointer) reservs);

    return reservs;
}

Reservation ** getUserReservs(const UserReservsDB * userData){
    return (Reservation **) userData->_userReservs;
}

int getNumReservs(const UserReservsDB * userData){
    return userData->size;
}


void allUserReservs(gpointer key ,gpointer value,gpointer userData){
    UserReservsDB * array = (UserReservsDB *) userData;
    Reservation * reserv = (Reservation *) value;
    char * rId = getReservUserId(reserv);

    if(!strcoll(rId,array->userId)){
        array->_userReservs[i] = (Reservation *) value;
        array->size++;
        i++;
    }
    free(rId);
}


void destroyUserReservsDB(UserReservsDB * database, int hashSize){
    free(database->_userReservs);
    database->_userReservs = NULL;
    free(database->userId);
    database->userId = NULL;
    free(database);
    database = NULL;
}

//                                  *** End block ***





//                             *** All flights of a user ***

typedef struct userFlightsDB {
    struct passengersDB * passengers;
    struct flight ** flights;
    int numTravels;
} UserFlightsDB;


// Args: Flights,Passengers,Id
UserFlightsDB * getUserFlightsDB(void * fDatabase,void * travels,const char * userId){
    FlightsDatabase allFlights = (FlightsDatabase) fDatabase;
    UserFlightsDB * book = malloc(sizeof(struct userFlightsDB));
    book->passengers = (PassengersDatabase *) travels;
    int max = getNumAllPassengers(book->passengers);
    book->flights = malloc(sizeof(Flight *) * max);
    for(int i = 0;i < max;book->flights[i] = NULL, i++);
    book->numTravels = 0; 
    Passenger ** list = getAllPassengers(book->passengers); 
    for(int passengersList = 0;passengersList < max;passengersList++){
        char * pUId = getPassengerUserId(list[passengersList]);
        if(!strcoll(pUId,userId)){
            char * pFId = getPassengerFlightId(list[passengersList]);
            Flight * flight = lookupFlight(allFlights,pFId);
            if(flight){
                book->flights[book->numTravels] = flight;
                book->numTravels++;
            }
            if(pFId) free(pFId);
        }
        free(pUId);
        pUId = NULL;
    }
    return book;
}
int getNumFlights(const UserFlightsDB * book){
    return book->numTravels;
}

Flight ** getUserFlights(const UserFlightsDB * database){
    return (Flight **) database->flights;
}

void destroyUserFlightsDB(UserFlightsDB * database,int hashSize){
    if(!database) return;
    if(database->flights){
        free(database->flights);
        database->flights = NULL;
    }
    free(database);
    database = NULL;
}






//                                 *** All Passengers of a flight ***  


typedef struct flightPassengers {
    struct passengersDB * allPassengers;
    Passenger ** list;
    int numPassengers;
} FlightPassengers;




FlightPassengers * getFlightPassengers(void * fDatabase,void * travels,const char * flightId){
    FlightsDatabase allFlights = (FlightsDatabase) fDatabase;
    FlightPassengers * book = malloc(sizeof(struct flightPassengers));
    book->allPassengers = (PassengersDatabase *) travels;
    book->list = malloc(sizeof(Passenger *) * g_hash_table_size((GHashTable *) allFlights));
    book->numPassengers = 0; 
    int max = getNumAllPassengers(book->allPassengers);
    Passenger ** pList = getAllPassengers(book->allPassengers); 
    if(pList == NULL){
        fprintf(stderr, "Error: Memory allocation failed for book->list.\n");
        book->list = NULL;
        return book;
    }
    for(int passengersList = 0;passengersList < max;passengersList++){
        char * flight_id = getPassengerFlightId(pList[passengersList]);
        if(!strcoll(flight_id,flightId)){
            book->list[book->numPassengers] = lookupPassengerFID(book->allPassengers,flight_id);
            book->numPassengers++;
        }
        free(flight_id);
    }
    return book;
}

int getNumPassengers(const FlightPassengers * book){
    return book->numPassengers;
}

Passenger ** getFlightPassengersBook(const FlightPassengers * database){
    return database->list;
}

void destroyFlightPassengers(FlightPassengers * database,int hashSize){
    if(database->list) free(database->list);
    database->list = NULL;
    if(database) free(database);
    database = NULL;
}



typedef struct airportDB{
    Flight ** fList;
    char * airport;
    Time * f;
    Time * l;
    int numFlights;
} AirportDB;


AirportDB * getAirportDB(const FlightsDatabase fDatabase,const char * airport,Time * begin,Time * end){
    int max = g_hash_table_size(fDatabase);
    AirportDB * aList = malloc(sizeof(struct airportDB));
    aList->numFlights = 0;
    aList->f = begin;
    aList->l = end;
    aList->airport = strdup(airport);
    aList->fList = malloc(sizeof(Flight *) * max);
    for(int a = 0;a < max;a++) aList->fList[a] = NULL;
    i = 0;
    g_hash_table_foreach((const FlightsDatabase) fDatabase,checkAirports,aList);
    return aList;
}




void checkAirports(gpointer key,gpointer value,gpointer flightData){
    Flight * flight = (Flight *) value;
    AirportDB * database = (AirportDB *) flightData;
    char * origin = getFlightOrigin(flight);
    Time * sDepartureDate = getFlightSDepartureDate(flight);
    Time * SArrivalDate = getFlightSArrivalDate(flight);
    if(database->f && database->l){
        if(!strcoll(database->airport,origin) && 
        compareTimes(sDepartureDate,database->l)==true && 
        compareTimes(database->f,SArrivalDate)==true){
            database->fList[i] = flight;
            i++;
            database->numFlights++;
        }
    }
    else{
        if(!strcoll(database->airport,origin)){
            database->fList[i] = flight;
            i++;
            database->numFlights++;
        }
    }
    free(origin);
    destroyTime(sDepartureDate);
    destroyTime(SArrivalDate);
}

int getNumAirportFlights(AirportDB * db){
    return db->numFlights;
}

Flight ** getAirportFlights(AirportDB * db){
    return db->fList;
}

void destroyAirport(AirportDB * db,int hashSize){
    if(db->airport){ 
        free(db->airport);
        db->airport = NULL;
    }
    if(db->fList){
        free(db->fList);
        db->fList = NULL;
    }
    if(db){
        free(db);
        db = NULL;
    }
}






//                                  *** End block ***
typedef struct airportPassengers{
    char ** airportName;
    int  * passengers;
} AirportPassengers;


char ** getAirportPassengersAirportName(AirportPassengers * db){
    char ** name = malloc(sizeof(char *)*100);
    for(int i = 0;i<27; i++){
        name[i] = db->airportName[i];
    }
    return name;
}

int * getAirportPassengersPassengers(AirportPassengers * db){
    int * number = malloc(sizeof(int)*100);
    for(int i = 0;i < 27; i++){
        number[i] = db->passengers[i];
    }
    return number;
}

typedef struct yearFlights {
    Flight ** flights;
    int * dateYear;
    AirportPassengers * airports;
    PassengersDatabase * passengers;
} YearFlights;

AirportPassengers * getYearFlights(const void * database,const void * databasep, const int fYear){
    GHashTable * fDatabase = (GHashTable *) database;
    PassengersDatabase * pDatabase = (PassengersDatabase *) databasep;

    Flight ** temp = malloc(sizeof (Flight *)*1000);
    AirportPassengers * airports = malloc(sizeof(AirportPassengers));

    airports->airportName = malloc(sizeof(char *)*100);
    airports->passengers = malloc(sizeof(int )*100);

    YearFlights * list = malloc(sizeof(struct yearFlights));
    list->airports = airports;
    list->passengers = pDatabase;

    for(int j = 0; j < 100; j++){
        list->airports->airportName[j] = NULL;
        list->airports->passengers[j] = 0;
    }

    list->flights = temp;
    list->dateYear = fYear;

    g_hash_table_foreach(fDatabase,yearFlight,list);

    list->flights = NULL;
    free(list);

    return airports;
}

void yearFlight(gpointer key, gpointer value, gpointer siuuu){
    Flight * f = (Flight *) value;
    YearFlights * yF = (YearFlights *) siuuu;
    char * airport = getFlightOrigin(f);
    Time * dDate = getFlightSDepartureDate(f);
    int year = getYear(dDate);

    if(year == yF->dateYear){
        int k = 0;
        int temp = 0;
        char * id = getFlightId(f);
        
        for(; yF->airports->airportName[k]; k++){
            if(strcoll(airport,yF->airports->airportName[k]) != 0) continue;
            yF->airports->passengers[k]+= countFPassengers(id, yF->passengers);
            temp++;
            break;
        }
        if(temp == 0){
            yF->airports->airportName[k] = strdup(airport);
            yF->airports->passengers[k]+= countFPassengers(id, yF->passengers);
        } 
    }
    year = 0;
    destroyTime(dDate);
}

int countFPassengers(const char * flightId,const void * database){
    PassengersDatabase * pDatabase = (PassengersDatabase *) database;
    int count = 0;
    int k = 0;
    Passenger ** p = getAllPassengers(pDatabase);
    while(p[k]){
        char * id = getPassengerFlightId(p[k]);
        if(!strcoll(flightId,id)){
            count++;
        }
        k++;
    }
    p = NULL;
    return count;
}
