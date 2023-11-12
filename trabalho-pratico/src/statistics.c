#include "../include/statistics.h"
#include "../include/dataTypes.h"
#include <glib.h>




// Returns the reservations by the hotel id
static Reservation * findReservHotel(void * table,const char * hotelId){
    Reservation ** reserv = NULL;
    g_hash_table_foreach((GHashTable *) table,(GHRFunc) lookupReservHotel,(gpointer) hotelId);
    return reserv;
}


// Returns the reservations by the user id
static Reservation * findReservUser(void * table,const char * userId){
    Reservation * reserv = g_hash_table_find((GHashTable *) table,(GHRFunc) lookupReservUser,(gpointer) userId);
    return reserv;
}




// Returns the passanger found by the user id
static Passanger * findPassangerUserId(void * structs,const char * userId){
    Passanger * passanger = g_hash_table_find((GHashTable *) structs,(GHRFunc) lookupPassangerUserId,(gpointer) userId);
    return passanger;
}
