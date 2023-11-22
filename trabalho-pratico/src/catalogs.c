#include "../include/catalogs.h"
#include "../include/dataTypes.h"
#include "../include/dataStructs.h"
#include "../include/time.h"
#include <stdio.h>
#include <glib.h>


#define BUFFERSIZE 1000


// Init usersDatabase
UsersDatabase initUsers(){
    UsersDatabase users = g_hash_table_new(g_str_hash, g_str_equal);
    if (users == NULL) {
        g_error("Failed to allocate memory for UsersDatabase");
        return NULL;
    }
    return users;
}

// Insert User
void insertUser(void *table, User *user){
    if (table == NULL || user == NULL) {
        // Handle invalid input
        g_error("Invalid input in insertUser function");
        return;
    }
    if(getUserId(user) == NULL) return;
    if (!g_hash_table_insert((UsersDatabase) table,(gpointer) getUserId(user),(gpointer) user)) {
        // Handle insertion failure
        g_error("Failed to insert user into UsersDatabase");
    }
}

// Returns the user that is supposed to be identified by the ID, that is on the TABLE
User *lookupUser(void *table, const char *id){
    if (table == NULL || id == NULL) {
        // Handle invalid input
        g_error("Invalid input in lookupUser function");
        return NULL;
    }

    User *user = g_hash_table_lookup((UsersDatabase) table, (gconstpointer) id);
    return user;
}

// Destroys usersDatabase
void destroyUsers(UsersDatabase database){
    if (database != NULL) {
        g_hash_table_remove_all(database);
        g_hash_table_destroy(database);
    } else {
        // Handle trying to destroy a NULL hash table
        g_error("Attempted to destroy a NULL UsersDatabase");
    }
}










// Inits the flights database
FlightsDatabase initFlights(){
    FlightsDatabase flights = g_hash_table_new(g_str_hash,g_str_equal);
    return flights;
}

// Inserts the flight on the database by the flight id
void insertFlight(void * structs,Flight * flight){
    g_hash_table_insert((FlightsDatabase)structs,(gpointer)getFlightId(flight),(gpointer) flight);
}

// Returns the flight based on the id
Flight * lookupFlight(void * table ,const char * id){
    Flight * flight = g_hash_table_lookup((FlightsDatabase) table,(gconstpointer) id);
    return flight;
}


void destroyFlights(FlightsDatabase database){
    g_hash_table_destroy(database);
}





























// Inits the reservations database
ReservationsDatabase initReservations(){
    ReservationsDatabase reservs = g_hash_table_new(g_str_hash,g_str_equal);
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
    g_hash_table_destroy(database);
}

























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
HotelDatabase * getHotelDataBase(void * dataStruct,const char * hotelId,Time * begin,Time * end){
    HotelDatabase * reservs = malloc(sizeof(struct hotelDatabase));
    reservs->hotel_id = strdup(hotelId);
    reservs->begin = begin;
    reservs->end = end;
    reservs->numReservas = 0;
    reservs->sumRatings = 0;
    reservs->_hotelReservs = malloc(sizeof(Reservation *) * g_hash_table_size((GHashTable *) dataStruct));
    g_hash_table_foreach((GHashTable *)dataStruct,allHotelReservs,reservs);
    return reservs;
}

// Function to iterate and get the reservations on the list
void allHotelReservs(gpointer key, gpointer value, gpointer hotelData) {
    HotelDatabase * array = (HotelDatabase *) hotelData;
    Reservation * reservation = (Reservation *)value;
    static int i = 0;

    if(array->begin != NULL && array->end != NULL){
        if (!strcoll(getReservHotelId(reservation),array->hotel_id) && compareTimes(getReservBeginDate(reservation),array->end) && compareTimes(array->begin,getReservEndDate(reservation))) {
          array->_hotelReservs[i] = reservation;
          array->sumRatings += getReservRating(reservation);
          array->numReservas++;
          i++;
        }
    }else{
        if (!strcoll(getReservHotelId(reservation),array->hotel_id)) {
          array->_hotelReservs[i] = reservation;
          array->sumRatings += getReservRating(reservation);
          array->numReservas++;
          i++;
        }
    }
}

void destroyHotelDatabase(HotelDatabase * hotel, int hashSize){
    free(hotel->hotel_id);
    hotel->hotel_id = NULL;
    for(int i = 0;i < hashSize;i++){
        hotel->_hotelReservs[i] = NULL;
    }
    free(hotel->_hotelReservs);
    hotel->_hotelReservs = NULL;
    destroyTime(hotel->begin);
    destroyTime(hotel->end);
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


UserReservsDB * getUserReservsDB(void * table,const char * userId){
    UserReservsDB * reservs = malloc(sizeof(struct userReservsDB));
    reservs->userId = strdup(userId);
    reservs->size = 0;
    reservs->_userReservs = malloc(sizeof(Reservation *) * g_hash_table_size((UsersDatabase) table));
    g_hash_table_foreach((UsersDatabase) table,allUserReservs,reservs);
    return reservs;
}

Reservation ** getUserReservs(const UserReservsDB * userData){
    return userData->_userReservs;
}

int getNumReservs(const UserReservsDB * userData){
    return userData->size;
}


void allUserReservs(gpointer key ,gpointer value,gpointer userData){
  UserReservsDB * array = (UserReservsDB *) userData;
  Reservation * reserv = (Reservation *) value;
  static int i = 0;
 
  if(!strcoll(getReservUserId(reserv),array->userId)){
      array->_userReservs[i] = reserv;
      array->size++;
      i++;
  }
}


void destroyUserReservsDB(UserReservsDB * database, int hashSize){
    for(int i = 0;i < hashSize;i++){

        database->_userReservs[i] = NULL;
    }
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



UserFlightsDB * getUserFlightsDB(void * fDatabase,void * travels,const char * userId){
    FlightsDatabase allFlights = (FlightsDatabase) fDatabase;
    UserFlightsDB * book = malloc(sizeof(struct userFlightsDB));
    book->passangers = (PassangersDatabase *) travels;
    book->flights = malloc(sizeof(Flight *) * g_hash_table_size((GHashTable *) allFlights));
    book->numTravels = 0; 
    int max = getNumAllPassangers(book->passangers);
    Passanger ** list = getAllPassangers(book->passangers); 
    for(int passangersList = 0;passangersList < max;passangersList++){
        if(strcoll(getPassangerUserId(list[passangersList]),userId)){
            book->flights[book->numTravels] = lookupFlight(allFlights,getPassangerFlightId(list[passangersList]));
            book->numTravels++;
        }
    }
    return book;
}
int getNumFlights(const UserFlightsDB * book){
    return book->numTravels;
}

Flight ** getUserFlights(const UserFlightsDB * database){
    return database->flights;
}

void destroyUserFlightsDB(UserFlightsDB * database,int hashSize){
    free(database->passangers);
    database->passangers = NULL;
    for(int i = 0;i < hashSize;i++){
        database->flights[i] = NULL;
    }
    free(database->flights);
    database->flights = NULL;
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
        if(strcoll(getPassangerFlightId(pList[passangersList]),flightId) == 0){
            book->list[book->numPassangers] = lookupPassangerFID(book->allPassangers,getPassangerFlightId(pList[passangersList]));
            book->numPassangers++;
        }
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
    if(database->allPassangers) free(database->allPassangers);
    database->allPassangers = NULL;
    for(int i = 0;i < hashSize;i++){
        database->list[i] = NULL;
    }
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


AirportDB * getAirportDB(FlightsDatabase fDatabase,const char * airport,Time * begin,Time * end){
    int max = g_hash_table_size(fDatabase);
    AirportDB * aList = malloc(sizeof(struct airportDB));
    aList->numFlights = 0;
    aList->f = begin;
    aList->l = end;
    aList->fList = malloc(sizeof(Flight *) * max);
    g_hash_table_foreach(fDatabase,checkAirports,aList);
    return aList;
}




void checkAirports(gpointer key,gpointer value,gpointer flightData){
    Flight * flight = (Flight *) value;
    AirportDB * database = (AirportDB *) flightData;
    static int i = 0;
    if(database->f && database->l)
        if(strcoll(database->airport,getFlightOrigin(flight)) && 
        compareTimes(getFlightSDepartureDate(flight),database->l)==true && 
        compareTimes(database->f,getFlightSArrivalDate(flight))==true){
            database->fList[i] = flight;
            i++;
            database->numFlights++;
        }
    if(database->f == NULL || database->f == NULL)
        if(strcoll(database->airport,getFlightOrigin(flight))){
            database->fList[i] = flight;
            i++;
            database->numFlights++;
        }
}

int getNumAirportFlights(AirportDB * db){
    return db->numFlights;
}

Flight ** getAirportFlights(AirportDB * db){
    return db->fList;
}

void destroyAirport(AirportDB * db,int hashSize){
    if(db->airport) free(db->airport);
    db->airport = NULL;
    if(db->f) destroyTime(db->f);
    db->f = NULL;
    if(db->l) destroyTime(db->l);
    db->l = NULL;
    for(int i = 0;i < hashSize;i++){
        db->fList[i] = NULL;
    }
    if(db->fList) free(db->fList);
    db->fList = NULL;
    if(db) free(db);
    db = NULL;
}














