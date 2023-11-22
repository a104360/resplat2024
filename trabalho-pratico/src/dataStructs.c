#include "../include/dataStructs.h"
#include "../include/dataTypes.h"
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

#define BUFFERSIZE 1000



typedef struct passangersDB {
    Passanger ** passangers;
    unsigned int max;
    unsigned int numPassangers;
} PassangersDatabase;


PassangersDatabase * createPassangerDatabase(){
    PassangersDatabase * db = malloc(sizeof(struct passangersDB));
    if (!db) {
        // Handle error, for example, print an error message and exit.
        fprintf(stderr, "Error: Memory allocation failed for PassangersDatabase.\n");
        exit(EXIT_FAILURE);
    }
    db->passangers = NULL;
    db->max = BUFFERSIZE;
    db->numPassangers = 0;
    return db;
}

void insertPassanger(void * dataStruct, void * passangerData){
    PassangersDatabase * table = (PassangersDatabase *) dataStruct;
    Passanger * passanger = (Passanger *) passangerData;
    if(table->numPassangers == 0){
        table->passangers = malloc(sizeof(Passanger *) * (table->max));
        if(!table->passangers){
            if(table) free(table);
            table = NULL;
            return;
        }
        table->passangers[table->numPassangers] = passanger;
        table->numPassangers++;
        return;
    } else {
        if(table->numPassangers >= table->max){
            Passanger **temp = realloc(table->passangers, (table->max * 2) * sizeof(Passanger *));
                if (!temp) {
                    fprintf(stderr, "Error: Memory reallocation failed in insertPassanger.\n");
                    for(int i = 0;i < table->max;i++){
                        free(table->passangers[i]);
                        table->passangers[i] = NULL;
                    }
                    free(table->passangers);
                    table->passangers = NULL;
                    free(table);
                    table = NULL;
                    return;
                }
                table->passangers = temp;
                table->max *= 2;
            }
        table->passangers[table->numPassangers] = passanger;
        table->numPassangers++;
        }
}


Passanger * lookupPassangerUID(const PassangersDatabase * database,const char * id){
    for(int i = 0;i < database->numPassangers;i++){
        if (database->passangers[i] && strcoll(getPassangerUserId(database->passangers[i]), id) == 0){
            return database->passangers[i];
        }
    }
    return NULL;
}

Passanger * lookupPassangerFID(const PassangersDatabase * database,const char * id){
    if(database == NULL || id == NULL) return NULL;
    for(int i = 0;i < database->numPassangers;i++){
        if (database->passangers[i] && strcoll(getPassangerFlightId(database->passangers[i]), id) == 0) {
            return database->passangers[i];
        }
    }
    return NULL;
}

int getNumAllPassangers(const PassangersDatabase * database){
    return database->numPassangers;
}

Passanger ** getAllPassangers(const PassangersDatabase * database){
    return database->passangers;
}

void destroyPassangersDB(PassangersDatabase * database){
    for(int i = 0;i < database->numPassangers;i++){
        database->passangers[i] = NULL;
    }
    free(database->passangers);
    database->passangers = NULL;
    free(database);
    database = NULL;
}   