#include "../include/catalogs.h"
#include "../include/dataTypes.h"
#include "../include/dataStructs.h"
#include <glib.h>


#define BUFFERSIZE 1000



// Init usersDatabase
UsersDatabase initUsers(){
    UsersDatabase users = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
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








// Inits the flights database
FlightsDatabase initFlights(){
    FlightsDatabase flights = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
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
































// Inits the reservations database
ReservationsDatabase initReservations(){
    ReservationsDatabase reservs = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
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



























//                             *** Get Hotel Reservations ***

typedef struct hotelDatabase{
    struct reservation ** _hotelReservs;
    char * hotel_id;
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
HotelDatabase * getHotelDataBase(void * dataStruct,const char * hotelId){
    HotelDatabase * reservs = malloc(sizeof(struct hotelDatabase));
    reservs->hotel_id = strdup(hotelId);
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

    if (!strcoll(getReservHotelId(reservation),array->hotel_id)) {
          array->_hotelReservs[i] = reservation;
          array->sumRatings += getReservRating(reservation);
          array->numReservas++;
          i++;
    }  
}

void destroyHotelDatabase(HotelDatabase * hotel){
    free(hotel->hotel_id);
    for(int i = 0;i < hotel->numReservas;i++){
        destroyReservation(hotel->_hotelReservs[i]);
    }
    free(hotel->_hotelReservs);
    free(hotel);
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


void destroyUserReservsDB(UserReservsDB * database){
    for(int i = 0;i < database->size;i++){
        destroyReservation(database->_userReservs[i]);
    }
    free(database->_userReservs);
    free(database->userId);
    free(database);
}

//                                  *** End block ***



//                             *** All flights of a user ***

typedef struct userFlightsDB {
    struct passangersDB * passangers;
    struct flight ** flights;
    int numTravels;
} UserFlightsDB;



UserFlightsDB * getUserFlightsBook(void * fDatabase,void * travels,const char * userId){
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

Flight ** getFlightIdList(const UserFlightsDB * database){
    return database->flights;
}

void destroyUserFlightsBook(UserFlightsDB * database){
    destroyPassangersDB(database->passangers);
    for(int i = 0;i < database->numTravels;i++){
        destroyFlight(database->flights[i]);
    }
    free(database->flights);
    free(database);
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

void destroyFlightPassangers(FlightPassangers * database){
    database->allPassangers = NULL;
    for(int i = 0;i < database->numPassangers;i++){
        destroyPassanger(database->list[i]);
    }
    free(database->list);
    free(database);
}















// Destroys User, Reservation or Flight database
void destroyDataBase(void * structs){
    g_hash_table_destroy((GHashTable *) structs);
}











