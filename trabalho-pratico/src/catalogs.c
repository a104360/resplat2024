#include "../include/catalogs.h"
#include "../include/dataTypes.h"
#include "../include/dataStructs.h"
#include "../include/time.h"
#include <glib.h>


#define BUFFERSIZE 1000



// Init usersDatabase
UsersDatabase initUsers(){
    UsersDatabase users = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)free,(GDestroyNotify)destroyUser);
    return users;
}

// Insert User
void insertUser(void * table,User * user){
    g_hash_table_insert((UsersDatabase) table,(gpointer) getUserId(user),(gpointer) user);
}

// Returns the user that is supposed to be identified by the ID, that is on the TABLE
User * lookupUser(void * table ,const char * id){
    User * user = g_hash_table_lookup((UsersDatabase) table,(gconstpointer) id);
    return user;
}

// Destroys usersDatabase
void destroyUsers(UsersDatabase database){
    g_hash_table_destroy(database);
}









// Inits the flights database
FlightsDatabase initFlights(){
    FlightsDatabase flights = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)free,(GDestroyNotify)destroyFlight);
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
    ReservationsDatabase reservs = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)free,(GDestroyNotify)destroyReservation);
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
    reservs->_hotelReservs = malloc(getReservSize() * g_hash_table_size((GHashTable *) dataStruct));
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
    for(int i = 0;i < hashSize;i++){
        if(hotel->_hotelReservs[i]) free(hotel->_hotelReservs[i]);
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
    reservs->_userReservs = malloc(getReservSize() * g_hash_table_size((UsersDatabase) table));
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
        free(database->_userReservs[i]);
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
    book->flights = malloc(getFlightSize() * g_hash_table_size((GHashTable *) allFlights));
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
        free(database->flights[i]);
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
    book->list = malloc(getPassangerSize() * g_hash_table_size((GHashTable *) allFlights));
    book->numPassangers = 0; 
    int max = getNumAllPassangers(book->allPassangers);
    Passanger ** pList = getAllPassangers(book->allPassangers); 
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
        if(database->list[i]) free(database->list[i]);
        database->list[i] = NULL;
    }
    if(database->list)free(database->list);
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
    aList->fList = malloc(getFlightSize() * max);
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
        if(db->fList[i]) free(db->fList[i]);
        db->fList[i] = NULL;
    }
    if(db->fList) free(db->fList);
    db->fList = NULL;
    if(db) free(db);
    db = NULL;
}














