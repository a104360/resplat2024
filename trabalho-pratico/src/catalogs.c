#include "../include/catalogs.h"
#include "../include/dataTypes.h"
#include "../include/dataStructs.h"
#include "../include/time.h"
#include <stdio.h>
#include <glib.h>
#include <gmodule.h>


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
        if (!strcoll(hotelId,array->hotel_id) && compareTimes(beginDate,array->end) && compareTimes(array->begin,endDate)) {
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
    struct passangersDB * passangers;
    struct flight ** flights;
    int numTravels;
} UserFlightsDB;


// Args: Flights,Passangers,Id
UserFlightsDB * getUserFlightsDB(void * fDatabase,void * travels,const char * userId){
    FlightsDatabase allFlights = (FlightsDatabase) fDatabase;
    UserFlightsDB * book = malloc(sizeof(struct userFlightsDB));
    book->passangers = (PassangersDatabase *) travels;
    int max = getNumAllPassangers(book->passangers);
    book->flights = malloc(sizeof(Flight *) * max);
    for(int i = 0;i < max;book->flights[i] = NULL, i++);
    book->numTravels = 0; 
    Passanger ** list = getAllPassangers(book->passangers); 
    for(int passangersList = 0;passangersList < max;passangersList++){
        char * pUId = getPassangerUserId(list[passangersList]);
        if(!strcoll(pUId,userId)){
            char * pFId = getPassangerFlightId(list[passangersList]);
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






//                                 *** All Passangers of a flight ***  


typedef struct flightPassangers {
    struct passangersDB * allPassangers;
    Passanger ** list;
    int numPassangers;
} FlightPassangers;




FlightPassangers * getFlightPassangers(void * fDatabase,void * travels,const char * flightId){
    FlightsDatabase allFlights = (FlightsDatabase) fDatabase;
    FlightPassangers * book = malloc(sizeof(struct flightPassangers));
    book->allPassangers = (PassangersDatabase *) travels;
    book->list = malloc(sizeof(Passanger *) * g_hash_table_size((GHashTable *) allFlights));
    book->numPassangers = 0; 
    int max = getNumAllPassangers(book->allPassangers);
    Passanger ** pList = getAllPassangers(book->allPassangers); 
    if(pList == NULL){
        fprintf(stderr, "Error: Memory allocation failed for book->list.\n");
        book->list = NULL;
        return book;
    }
    for(int passangersList = 0;passangersList < max;passangersList++){
        char * flight_id = getPassangerFlightId(pList[passangersList]);
        if(!strcoll(flight_id,flightId)){
            book->list[book->numPassangers] = lookupPassangerFID(book->allPassangers,flight_id);
            book->numPassangers++;
        }
        free(flight_id);
    }
    return book;
}

int getNumPassangers(const FlightPassangers * book){
    return book->numPassangers;
}

Passanger ** getFlightPassangersBook(const FlightPassangers * database){
    return database->list;
}

void destroyFlightPassangers(FlightPassangers * database,int hashSize){
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
    for(int i = 0;i < max;i++) aList->fList[i] = NULL;
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
    if(database->f == NULL){
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














