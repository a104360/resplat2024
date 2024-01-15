#include "../include/database.h"
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/utils.h"
#include <ctype.h>
#include <stdio.h>

typedef struct database {
    GHashTable * table;
} Database;

Database * createDatabase(void (*func)()){
    Database * database = malloc(sizeof(struct database));
    GDestroyNotify function = (GDestroyNotify) func;
    database->table = g_hash_table_new_full(g_str_hash,g_str_equal,free,(GDestroyNotify) function);
    return database;
}

void insertOnDatabase(void * dBase,const char * id,void * element){
    Database * database = (Database *) dBase;
    g_hash_table_insert((GHashTable *)database->table,(gpointer)id,(gpointer) element);
}

void * lookupElement(const void * dBase ,const char * id){
    Database * database = (Database *) dBase;
    void * element = g_hash_table_lookup((GHashTable *)database->table,(gconstpointer)id);
    return element;
}

int getDatabaseSize(const void * database){
    Database * dBase = (Database *) database;
    return g_hash_table_size(dBase->table);
}

void applyForEach(void * database,void (*func)(gpointer,gpointer,gpointer),void * data){
    Database * dBase = (Database *) database;
    g_hash_table_foreach((GHashTable *) dBase->table,(GHFunc) (*func),(gpointer)data);
}

void destroyDatabase(void * database){
    Database * dBase = (Database *) database;
    g_hash_table_destroy(dBase->table);
    ffree(database);
}

