#include "../include/dataStructs.h"
#include "../include/dataTypes.h"
#include <stdlib.h>
#include <glib.h>

#define BUFFERSIZE 1000



typedef struct passangersDB {
    Passanger ** passangers;
    unsigned int max;
    unsigned int numPassangers;
} PassangersDatabase;


PassangersDatabase * createPassangerDatabase(){
    PassangersDatabase * db = malloc(sizeof(struct passangersDB));
    db->passangers = NULL;
    db->max = BUFFERSIZE;
    db->numPassangers = 0;
    return db;
}

void insertPassanger(void * dataStruct, void * passangerData){
    PassangersDatabase * table = (PassangersDatabase *) dataStruct;
    Passanger * passanger = (Passanger *) passangerData;
    if(table->numPassangers == 0){
        table->passangers = malloc(getPassangerSize() * BUFFERSIZE);
        if(!table->passangers){
            free(table);
            return;
        }
        table->passangers[table->numPassangers] = passanger;
        table->numPassangers++;
        return;
    } else {
        if(table->numPassangers >= table->max){
            Passanger *temp = realloc(table->passangers, (table->max * 2) * getPassangerSize());
                if (!temp) {
                    for(int i = 0;i < table->max;i++){
                        free(table->passangers[i]);
                    }
                    free(table);
                    return;
                }
                table->passangers = temp;
                table->max *= 2;
                table->passangers[table->numPassangers] = passanger;
                table->numPassangers++;
            }
        }
    table->passangers[table->numPassangers] = passanger;
    table->numPassangers++;

}

int getNumAllPassangers(const PassangersDatabase * database){
    return database->numPassangers;
}

Passanger ** getAllPassangers(const PassangersDatabase * database){
    return database->passangers;
}

void destroyPassangersDB(PassangersDatabase * database){
    for(int i = 0;i < database->numPassangers;i++){
        free(database->passangers[i]);
    }
    free(database);
}