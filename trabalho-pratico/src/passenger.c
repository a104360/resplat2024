#include "../include/passenger.h"
#include <stdlib.h>
#include <string.h>


typedef struct passanger{
    char * flight_id;
    char * user_id;
} Passanger;



// *** Passanger related functions *** 

 Passanger * createPassanger(){
    Passanger * p =malloc(sizeof(struct passanger));
    initPassanger(p);
    return p;
}

  void initPassanger(Passanger * passanger){
    passanger->flight_id = NULL;
    passanger->user_id = NULL;
}

  void destroyPassanger(Passanger * p) {
    if (p != NULL) {
        if(p->flight_id != NULL){
            free(p->flight_id); 
            p->flight_id = NULL;
        }
        if(p->user_id != NULL){
            free(p->user_id); 
            p->user_id = NULL;
        }
        free(p); 
        p = NULL;
    }
}

size_t getPassangerSize(){
    return sizeof(struct passanger);
}


 void setPassangerFlightId(Passanger * passanger,const char * line){
    if(passanger == NULL || line == NULL) return;
    if(passanger->flight_id){
        if(strlen(line) > strlen(passanger->flight_id)){
            char * temp = realloc(passanger->flight_id,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            passanger->flight_id = temp;
            return;
        }else{
            strncpy(passanger->flight_id,line,strlen(passanger->flight_id));
            passanger->flight_id[strlen(passanger->flight_id)] = '\0';
            return;
        }
    }
    passanger->flight_id = strdup(line);
}

 char *getPassangerFlightId(Passanger * passanger){
    if(passanger == NULL) return NULL;
    if(passanger->flight_id == NULL) return NULL;
    if(passanger->flight_id != NULL){
        char * flight_id = strdup(passanger->flight_id);
        return flight_id;
    }
    return NULL;
}


  void setPassangerUserId(Passanger * passanger,const char * line){
    if(passanger == NULL || line == NULL) return;
    if(passanger->user_id){
        if(strlen(line) > strlen(passanger->user_id)){
            char * temp = realloc(passanger->user_id,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            passanger->user_id = temp;
            return;
        }else{
            strncpy(passanger->user_id,line,strlen(passanger->user_id));
            passanger->user_id[strlen(passanger->user_id)] = '\0';
            return;
        }
    }
    passanger->user_id = strdup(line);
}

 char *getPassangerUserId(Passanger * passanger){
    if(passanger == NULL) return NULL;
    if(passanger->user_id){
        char * user_id = strdup(passanger->user_id);
        return user_id;
    }
    return NULL;
}


void copyPassanger(Passanger * dest,Passanger * src){
    if(dest == NULL || src == NULL) return;
    char * passangerFlightId = getPassangerFlightId(src);
    char * passangerUserId = getPassangerUserId(src);

    setPassangerFlightId(dest,passangerFlightId);
    setPassangerUserId(dest,passangerUserId);

    free(passangerFlightId);
    passangerFlightId = NULL;
    free(passangerUserId);
    passangerUserId = NULL;
}

