#include "../include/catalogs.h"
#include "../include/utils.h"
#include "../include/dataTypes.h"
#include <glib.h>






// Init usersDatabase
static UsersDatabase initUsers(){
    UsersDatabase users = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
    return users;
}
// Insert User
static void insertUser(void * table,User * user){
    g_hash_table_insert((UsersDatabase) table,(gpointer) getUserId(user),(gpointer) user);
}

// Returns the user that is supposed to be identified by the ID, that is on the TABLE
static User * lookupUser(void * table ,const char * id){
    User * user = g_hash_table_lookup((UsersDatabase) table,(gconstpointer) id);
    return user;
}








// Inits the flights database
static FlightsDatabase initFlights(){
    FlightsDatabase flights = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
    return flights;
}

// Inserts the flight on the database by the flight id
static void insertFlight(void * structs,Flight * flight){
    g_hash_table_insert((FlightsDatabase)structs,(gpointer)getFlightId(flight),(gpointer) flight);
}

// Returns the flight based on the id
static Flight * lookupFlight(void * table ,const char * id){
    Flight * flight = g_hash_table_lookup((FlightsDatabase) table,(gconstpointer) id);
    return flight;
}












// Inits the reservations database
static ReservationsDatabase initReservations(){
    ReservationsDatabase reservs = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
    return reservs;
}

// Inserts the reservations based on the reservations id
static void insertReserv(void * structs,Reservation * reserv){
    g_hash_table_insert((ReservationsDatabase) structs,(gpointer) getReservId(reserv),(gpointer) reserv);
}

// Returns the reservations by the reservations id
static Reservation * lookupReserv(void * table,const char * reservId){
    Reservation * reserv = g_hash_table_lookup((ReservationsDatabase ) table,(gconstpointer) reservId);
    return reserv;
}





// Returns the reservations by the hotel id
static Reservation ** allReservsInHotel(void * table,const char * hotelId){
    Reservation ** reservs = malloc(sizeof(struct reservation));

    g_hash_table_find((ReservationsDatabase) table,(GHRFunc) lookupReservHotel,(gpointer) hotelId);
    return reserv;
}


// Returns the reservations by the user id
static Reservation * findReservUser(void * table,const char * userId){
    ReservationSearchResults reservs = g_hash_table_find    ((ReservationsDatabase) table,(GHRFunc) lookupReservUser,(gpointer) userId);
    return reservs;
}













// Inits the passangers database
static PassangersDatabase initPassangers(){
    PassangersDatabase passangers = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
    return passangers;
}


// Inserts passangers on database by their flight id
static void insertPassangerFlightId(void * structs,Passanger * passanger){
    g_hash_table_insert((PassangersDatabase) structs,(gpointer) getPassangerFlightId(passanger),(gpointer) passanger);
}

// Returns the Passanger found by the flight id
static Passanger * lookupPassangerFlightId(void * structs,const char * flightId){
    Passanger * passanger = g_hash_table_lookup((PassangersDatabase) structs,(gconstpointer) flightId);
    return passanger;
}



// ** Destroys any database passed as argument
static void destroyDataBase(void * structs){
    g_hash_table_destroy((GHashTable *) structs);
}

















static GArray * UsersAnalysisCatalog();

static void UsersAnalysisCatalogInsert(void *,void *);


static GArray * FlightsAnalysisCatalog();




static GArray * ReservationsAnalysisCatalog();




static GArray * PassangerAnalysisCatalog();


