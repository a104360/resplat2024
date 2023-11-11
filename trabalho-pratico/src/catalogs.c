#include "../include/catalogs.h"
#include "../include/utils.h"
#include "../include/dataTypes.h"
#include <glib.h>


static GHashTable * UsersDataBase(){
    GHashTable * users = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
    return users;
}
static void insertUser(void * table,User * user){


    g_hash_table_insert((GHashTable *) table,(gpointer) getUserId(user),(gpointer) user);
}
static User * lookupUser(void * table ,const char * id){


    User * user = g_hash_table_lookup((GHashTable *) table,(gconstpointer) id);
    return user;
}






static GHashTable * FlightsDataBase(){
    GHashTable * flights = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
    return flights;
}
static void insertFlight(void * structs,Flight * flight){

    g_hash_table_insert((GHashTable *)structs,(gpointer)getFlightId(flight),(gpointer) flight);
}
static Flight * lookupFlight(void * table ,const char * id){

    Flight * flight = g_hash_table_lookup((GHashTable *) table,(gconstpointer) id);
    return flight;
}



static GHashTable * ReservationsDataBase(){


    GHashTable * reservs = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
    return reservs;
}
static void insertReserv(void * structs,Reservation * reserv){


    g_hash_table_insert((GHashTable *) structs,(gpointer) getReservId(reserv),(gpointer) reserv);
}

static Reservation * lookupReserv(void * table,const char * reservId){

    Reservation * reserv = g_hash_table_lookup((GHashTable * ) table,(gconstpointer) reservId);
    return reserv;
}
static Reservation * lookupReservHotel(void * table,const char * hotelId){

    Reservation * reserv = g_hash_table_lookup((GHashTable * ) table,(gconstpointer) hotelId);
    return reserv;
}
static Reservation * lookupReservUser(void * table,const char * userId){

    Reservation * reserv = g_hash_table_lookup((GHashTable * ) table,(gconstpointer) userId);
    return reserv;
}





static GHashTable * PassangersDataBase(){

    GHashTable * passangers = g_hash_table_new_full(g_str_hash,g_str_equal,(GDestroyNotify)g_free,(GDestroyNotify)g_hash_table_destroy);
    return passangers;
}

static void insertPassangerFlightId(void * structs,Passanger * passanger){

    g_hash_table_insert((GHashTable *) structs,(gpointer) getPassangerFlightId(passanger),(gpointer) passanger);
}
static void insertPassangerUserId(void * structs,Passanger * passanger){

    g_hash_table_insert((GHashTable *) structs,(gpointer) getPassangerUserId(passanger),(gpointer) passanger);
}

static Passanger * lookupPassangerFlightId(void * structs,const char * flightId){

    Passanger * passanger = g_hash_table_lookup((GHashTable *) structs,(gconstpointer) flightId);
    return passanger;
}
static Passanger * lookupPassangerUserId(void * structs,const char * userId){

    Passanger * passanger = g_hash_table_lookup((GHashTable *) structs,(gconstpointer) userId);
    return passanger;
}











static void destroyDataBase(void * structs){
    g_hash_table_destroy((GHashTable *) structs);
}