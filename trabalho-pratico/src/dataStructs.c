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
        fprintf(stderr, "Error: Memory allocation failed for PassangersDatabase.\n");
        exit(EXIT_FAILURE);
    }
    db->max = BUFFERSIZE;
    db->numPassangers = 0;
    db->passangers = malloc(sizeof(Passanger *) * db->max);
    for(int i = 0;i < db->max;i++) db->passangers[i] = NULL;
    return db;
}

void insertPassanger(void * dataStruct, void * passangerData){
    //Casting the arguments
    PassangersDatabase * table = (PassangersDatabase *) dataStruct;
    Passanger * passanger = (Passanger *) passangerData;
/*
    if(table->numPassangers == 0){ // First insertion of the table
        table->passangers = malloc(sizeof(Passanger *) * (table->max));
        if(!table->passangers){
            if(table) free(table);
            table = NULL;
            return;
        }
        table->passangers[table->numPassangers] = passanger;
        table->numPassangers++;
        return;

    } else {*/
        if(table->numPassangers >= table->max){
            Passanger ** temp = realloc(table->passangers, (table->max * 2) * sizeof(Passanger *));
                if (!temp) {
                    fprintf(stderr, "Error: Memory reallocation failed in insertPassanger.\n");
                    for(int i = 0;i < table->max;i++){
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
        //}
}


Passanger * lookupPassangerUID(const PassangersDatabase * database,const char * id){
    for(int i = 0;i < database->numPassangers;i++){
        char * uId = getPassangerUserId(database->passangers[i]);
        if (database->passangers[i] && strcoll(uId, id) == 0){
            free(uId);
            uId = NULL;
            return database->passangers[i];
        }
        free(uId);
        uId = NULL;
    }
    return NULL;
}

Passanger * lookupPassangerFID(const PassangersDatabase * database,const char * id){
    if(database == NULL || id == NULL) return NULL;
    for(int i = 0;i < database->numPassangers;i++){
        char * fId = getPassangerFlightId(database->passangers[i]);
        if (database->passangers[i] && strcoll(fId, id) == 0) {
            free(fId);
            return database->passangers[i];
        }
        free(fId);
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
        destroyPassanger(database->passangers[i]);
    }
    free(database->passangers);
    database->passangers = NULL;
    free(database);
    database = NULL;
}   