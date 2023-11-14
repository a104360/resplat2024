#include "../include/catalogs.h"
#include "../include/utils.h"
#include "../include/dataTypes.h"
#include <glib.h>




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










typedef struct flightBook {
    Passanger ** passangers;
    Flight * flight;
    int size;
    int passangerSize;
    int flightSize;
} FlightBook;


int getNumPassangers(const FlightBook * book){
    return book->size;
}

Passanger ** getFlightPassangers(const FlightBook * book){
    return book->passangers;
}


FlightBook * getFlightBook(void * dataStruct, const char * id){
    GHashTable * table = (GHashTable *) dataStruct;
    int aux = g_hash_table_size(table);
    FlightBook * book = malloc(sizeof(struct flightBook));
    book->flight = lookupFlight(table,id);
    book->size = 0;
    book->passangerSize = getPassangerSize();
    book->flightSize = getFlightSize();
    book->passangers = malloc(book->passangerSize * aux);
    g_hash_table_foreach(table,getPassangers,book);
    return book;
}

// Iterative function to fetch every passanger on the flight
void getPassangers(gpointer key,gpointer value,gpointer flightbook){
    FlightBook * book = (FlightBook * ) flightbook;
    Passanger * passanger = (Passanger * ) value;
    static int i = 0;

    if(g_strcmp0(getFlightId(book->flight),getPassangerFlightId(passanger)) == 0){
        book->passangers[i] = passanger;
        i++;
        book->size++;
    }
}

// Destroys Flight Book
void destroyFlightBook(FlightBook * book){
    destroyFlight(book->flight);
    for(int i = 0; i < book->size;i++){
        destroyPassanger(book->passangers[i]);
    }
    free(book);
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
    HotelDatabase * reservs = malloc(sizeof(struct hotelDatabase) * g_hash_table_size((GHashTable *) dataStruct));
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

    if (!g_strcmp0(getReservHotelId(reservation),array->hotel_id)) {
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
    reservs->_userReservs = malloc(getReservSize() * g_hash_table_size((UsersDatabase *) table));
    g_hash_table_foreach((UsersDatabase *) table,allUserReservs,reservs);
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
 
  if(!g_strcmp0(getReservUserId(reserv),array->userId)){
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










// Destroys User, Reservation or Flight database
void destroyDataBase(void * structs){
    g_hash_table_destroy((GHashTable *) structs);
}











