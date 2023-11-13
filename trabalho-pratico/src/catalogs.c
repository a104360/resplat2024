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

void initFlightBook(void * pointer ){
    FlightBook * book = (FlightBook *) pointer;
    book->flight = NULL;
    book->flightSize = getFlightSize();
    book->passangerSize = getPassangerSize();
    book->size = 0;
    book->passangers = NULL;
    return book;
}

FlightBook * createFlightBook(){
    FlightBook * book = malloc(sizeof(struct flightBook));
    initFlightBook(book);
    return book;
}

void insertPassanger(void * voo,void * passanger){
    FlightBook * flight = (FlightBook *) voo;
    Passanger * new = (Passanger *) passanger;
    if(flight->passangers){ 
        flight->passangers = realloc(flight->passangers,flight->passangerSize * flight->size + 1);
        if(!flight->passangers[flight->size + 1]) return;
        flight->passangers[flight->size + 1] = new;
        flight->size++;
    }
    else {
        flight->passangers = malloc(flight->passangerSize);
        flight->passangers[0] = new;
        flight->size++;
    }
}

char * isUserOnFlight(void * voo,void * userData){
    FlightBook * flight = (FlightBook * ) voo;
    char * userId = (char *) userData;
    
    for(int i = 0;i < flight->size;i++){
        if(strcmp(getPassangerUserId(flight->passangers[i]),userId)) return getFlightId(flight->flight);
    }
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

// Returns all reservations of an hotel
Reservation ** findHotelReservations(void * table,const char *hotelId){
    Reservation ** hReservs = getAllReservsInHotel(table,hotelId);
    return hReservs;
}

// Only use after call findHotelReservations (free the array)
void destroyHotelReservations(void * list,void * table){
    Reservation ** reservs = (Reservation **) list;
    GHashTable * tabela = (GHashTable * ) table;
    for(int i = 0;i < g_hash_table_size(tabela);i++){
        if(reservs[i]) free(reservs[i]);
    }
    free(reservs);
}







// Returns the reservations by the user id
Reservation * findReservUser(void * table,const char * userId){
    //ReservationSearchResults reservs = g_hash_table_find    ((ReservationsDatabase) table,(GHRFunc) lookupReservUser,(gpointer) userId);
    //return reservs;
    return NULL;
}














// ** Destroys any database passed as argument
void destroyDataBase(void * structs){
    g_hash_table_destroy((GHashTable *) structs);
}











// *** Block to get Types through other meanings than the hash table keys *** 

// struct to store the list of reservations of an hotel and the hotel id
typedef struct hotelReservs{
    struct reservation ** _hotelReservs;
    char * hotel_id;
} HotelReservs;

// Returns the reservations by the hotel id
 Reservation ** getAllReservsInHotel(void * dataStruct,const char * hotelId){
    HotelReservs * reservs = malloc(sizeof(struct hotelReservs) * g_hash_table_size((GHashTable *) dataStruct));
    reservs->hotel_id = strdup(hotelId);
    g_hash_table_foreach((GHashTable *)dataStruct,allHotelReservs,reservs);
    free(reservs->_hotelReservs);
    Reservation ** list = reservs->_hotelReservs;
    free(reservs->_hotelReservs);
    free(reservs);
    return list;
}

// Function to iterate and get the reservations on the list
void allHotelReservs(gpointer key, gpointer value, gpointer hotelData) {
    HotelReservs * array = (HotelReservs *) hotelData;
    Reservation * reservation = (Reservation *)value;
    static int i = 0;

    if (!g_strcmp0(getReservHotelId(reservation),array->hotel_id)) {
          array->_hotelReservs[i] = reservation;
          i++;
    }  
}

//                                  *** End block ***


//                      *** Get all the reservations of a user ***

typedef struct userReservs{
    struct reservation ** _userReservs;
    char * userId;
} UserReservs;

 Reservation ** getAllUserReservs(void * table,const char * userId){
    UserReservs * reservs = malloc(sizeof(struct userReservs) * g_hash_table_size((ReservationsDatabase) table));
    reservs->userId = strdup(userId);
    g_hash_table_foreach((UsersDatabase) table,allUserReservs,reservs);
    free(reservs->userId);
    Reservation ** list = reservs->_userReservs;
    free(reservs->_userReservs);
    free(reservs);
    return list;
}

  void allUserReservs(gpointer key ,gpointer value,gpointer userData){
    UserReservs * array = (UserReservs *) userData;
    Reservation * reserv = (Reservation *) value;
    static int i = 0;

    if(!g_strcmp0(getReservUserId(reserv),array->userId)){
        array->_userReservs[i] = reserv;
        i++;
    }
}

//                                  *** End block ***