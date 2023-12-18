#include "../include/flight.h"
#include <stdlib.h>
#include <string.h>

typedef struct flight{
    char * id;
    char * airline;
    char * plane_model;
    unsigned int total_seats;
    char * origin;
    char * destination;
    struct time * schedule_departure_date;
    struct time * schedule_arrival_date;
    struct time * real_departure_date;
    struct time * real_arrival_date;
    char * pilot;
    char * copilot;
    char * notes;
} Flight;






 Flight * createFlight(){
    Flight * f = malloc(sizeof(struct flight));
    initFlight(f);
    return f;
}

  void initFlight(Flight * flight){
    flight->id = NULL;
    flight->airline = NULL;
    flight->plane_model = NULL;
    flight->total_seats = 0;
    flight->origin = NULL;
    flight->destination = NULL;
    flight->schedule_departure_date = createTime();
    flight->schedule_arrival_date = createTime();
    flight->real_departure_date = createTime();
    flight->real_arrival_date = createTime();
    flight->pilot = NULL;
    flight->copilot = NULL;
    flight->notes = NULL;
}

  void destroyFlight(Flight * f) {
    if (f != NULL) {
        if(f->id != NULL){
            free(f->id);
            f->id = NULL;
        } 
        
        if(f->airline != NULL){
            free(f->airline);
            f->airline = NULL;
        } 
        
        if(f->plane_model != NULL){
            free(f->plane_model);
            f->plane_model = NULL;
        } 
        
        if(f->origin != NULL){
            free(f->origin);
            f->origin = NULL;
        } 
        
        if(f->destination != NULL){
            free(f->destination);
            f->destination = NULL;
        } 
        
        if(f->schedule_departure_date != NULL) destroyTime(f->schedule_departure_date); 
        if(f->schedule_arrival_date != NULL) destroyTime(f->schedule_arrival_date); 
        if(f->real_departure_date != NULL) destroyTime(f->real_departure_date); 
        if(f->real_arrival_date != NULL) destroyTime(f->real_arrival_date); 
        if(f->pilot != NULL){
            free(f->pilot);
            f->pilot = NULL;
        } 
        
        if(f->copilot != NULL){
            free(f->copilot);
            f->copilot = NULL;
        } 
        
        if(f->notes != NULL){
            free(f->notes);
            f->notes = NULL;
        } 
        
        free(f); 
        f = NULL;
    }
}


void setFlightId(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->id) {
        free(flight->id);
        flight->id = NULL;
    }
    flight->id = strdup(line);
}

char *getFlightId(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->id){
        char * id =strdup(flight->id);
        return id;
    }
    return NULL;
}

  
void setFlightAirline(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->airline) {
        free(flight->airline);
        flight->airline = NULL;
    }
    flight->airline = strdup(line);
}

char *getFlightAirline(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->airline){
        char * airline =strdup(flight->airline);
        return airline;
    }
    return NULL;
}


void setFlightPlaneModel(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->plane_model) {
        if(strlen(line) > strlen(flight->plane_model)){
            char * temp = realloc(flight->plane_model,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            flight->plane_model = temp;
            return;
        }else{
            strncpy(flight->plane_model,line,strlen(flight->plane_model));
            flight->plane_model[strlen(flight->plane_model)] = '\0';
            return;
        }
    }
    flight->plane_model =strdup(line);
}

char *getFlightPlaneModel(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->plane_model){
        char * plane_model =strdup(flight->plane_model);
        return plane_model;
    }
    return NULL;
}


void setFlightTotalSeats(Flight * flight,const unsigned int n){
    if(flight == NULL) return;
    flight->total_seats = n;
}

unsigned int getFlightTotalSeats(Flight * flight){
    if(flight != NULL) return flight->total_seats;
    else return 0;
}


void setFlightOrigin(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->origin) {
        free(flight->origin);
        flight->origin = NULL;
    }
    flight->origin = strdup(line);
}

char *getFlightOrigin(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->origin){
        char * origin = strdup(flight->origin);
        return origin;
    }
    return NULL;
}


  void setFlightDestination(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->destination) {
        free(flight->destination);
        flight->destination = NULL;
    }
    flight->destination = strdup(line);
}

char *getFlightDestination(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->destination){
        char * destination = strdup(flight->destination);
        return destination;
    }
    return NULL;
}


void setFlightSDepartureDate(Flight * flight,Time * tempo){
    if(flight == NULL || tempo == NULL) return;
    if(flight->schedule_departure_date == NULL) flight->schedule_departure_date = createTime();
    copyTime(flight->schedule_departure_date,tempo);
}

Time *getFlightSDepartureDate(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->schedule_departure_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->schedule_departure_date);
        return tempo;
    }
    return NULL;
}


void setFlightSArrivalDate(Flight * flight,Time * tempo){
    if(flight == NULL || tempo == NULL) return;
    if(flight->schedule_arrival_date == NULL) flight->schedule_arrival_date = createTime();
    copyTime(flight->schedule_arrival_date,tempo);
}

Time *getFlightSArrivalDate(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->schedule_arrival_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->schedule_arrival_date);
        return tempo;
    }
    return NULL;
}


void setFlightRDepartureDate(Flight * flight, Time * tempo){
    if(flight == NULL || tempo == NULL) return;
    if(flight->real_departure_date == NULL) flight->real_departure_date = createTime();
    copyTime(flight->real_departure_date,tempo);
}

Time *getFlightRDepartureDate(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->real_departure_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->real_departure_date);
        return tempo;
    }
    return NULL;
}


void setFlightRArrivalDate(Flight * flight,Time * tempo){
    if(flight == NULL || tempo == NULL) return;
    if(flight->real_arrival_date == NULL) flight->real_arrival_date = createTime();
    copyTime(flight->real_arrival_date,tempo);
}

Time *getFlightRArrivalDate(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->real_arrival_date){
        Time * tempo = createTime();
        copyTime(tempo,flight->real_arrival_date);
        return tempo;
    }
    return NULL;
}


void setFlightPilot(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->pilot) {
        if(strlen(line) > strlen(flight->pilot)){
            char * temp = realloc(flight->pilot,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            flight->pilot = temp;
            return;
        }else{
            strncpy(flight->pilot,line,strlen(flight->pilot));
            flight->pilot[strlen(flight->pilot)] = '\0';
            return;
        }
    }
    flight->pilot =strdup(line);
}

char *getFlightPilot(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->pilot){
        char * pilot =strdup(flight->pilot);
        return pilot;
    }
    return NULL;
}


void setFlightCopilot(Flight * flight,const char * line){
    if(flight == NULL) return;
    if(flight->copilot) {
        if(strlen(line) > strlen(flight->copilot)){
            char * temp = realloc(flight->copilot,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            flight->copilot = temp;
            return;
        }else{
            strncpy(flight->copilot,line,strlen(flight->copilot));
            flight->copilot[strlen(flight->copilot)] = '\0';
            return;
        }
    }
    flight->copilot =strdup(line);
}

char *getFlightCopilot(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->copilot){
        char * copilot =strdup(flight->copilot);
        return copilot;
    }
    return NULL;
}


void setFlightNotes(Flight * flight,const char * line){
    if(line == NULL || flight == NULL) return;
    if(flight->notes) {
        if(strlen(line) > strlen(flight->notes)){
            char * temp = realloc(flight->notes,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            flight->notes = temp;
            return;
        }else{
            strncpy(flight->notes,line,strlen(flight->notes));
            flight->notes[strlen(flight->notes)] = '\0';
            return;
        }
    }
    flight->notes =strdup(line);
}

char *getFlightNotes(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->notes){
        char * notes =strdup(flight->notes);
        return notes;
    }
    return NULL;
}

int getFlightDelay(Flight * flight){
    if(flight == NULL) return -1;
    return ((getYear(flight->real_departure_date) - getYear(flight->schedule_departure_date)) * 31536000) + 
    ((getMon(flight->real_departure_date) - getMon(flight->schedule_departure_date)) * 2592000) + 
    ((getMday(flight->real_departure_date) - getMday(flight->schedule_departure_date)) * 86400) + 
    ((getHour(flight->real_departure_date) - getHour(flight->schedule_departure_date)) * 3600) + 
    ((getMin(flight->real_departure_date) - getMin(flight->schedule_departure_date)) * 60) +
    ((getSec(flight->real_departure_date) - getSec(flight->schedule_departure_date)));
}


void copyFlight(Flight * dest,Flight * src){
    if(dest == NULL || src == NULL) return;
    char * flightId = getFlightId(src);
    char * flightAirline = getFlightAirline(src);
    char * flightPlaneModel = getFlightPlaneModel(src);
    char * flightOrigin = getFlightOrigin(src);
    char * flightDestination = getFlightDestination(src);
    char * flightPilot = getFlightPilot(src);
    char * flightCopilot = getFlightCopilot(src);
    char * flightNotes = getFlightNotes(src);
    Time * flightSDepartureDate = getFlightSDepartureDate(src);
    Time * flightSArrivalDate = getFlightSArrivalDate(src);
    Time * flightRDepartureDate = getFlightRDepartureDate(src);
    Time * flightRArrivalDate = getFlightRArrivalDate(src);


    setFlightId(dest,flightId);
    setFlightAirline(dest,flightAirline);
    setFlightPlaneModel(dest,flightPlaneModel);
    setFlightTotalSeats(dest,getFlightTotalSeats(src));
    setFlightOrigin(dest,flightOrigin);
    setFlightDestination(dest,flightDestination);
    setFlightSDepartureDate(dest,flightSDepartureDate);
    setFlightSArrivalDate(dest,flightSArrivalDate);
    setFlightRDepartureDate(dest,flightRDepartureDate);
    setFlightRArrivalDate(dest,flightRArrivalDate);
    setFlightPilot(dest,flightPilot);
    setFlightCopilot(dest,flightCopilot);
    setFlightNotes(dest,flightNotes);


    free(flightId);
    flightId = NULL;
    free(flightAirline);
    flightAirline = NULL;
    free(flightPlaneModel);
    flightPlaneModel = NULL;
    free(flightOrigin);
    flightOrigin = NULL;
    free(flightDestination);
    flightDestination = NULL;
    free(flightPilot);
    flightPilot = NULL;
    free(flightCopilot);
    flightCopilot = NULL;
    free(flightNotes);
    flightNotes = NULL;
    free(flightSDepartureDate);
    flightSDepartureDate = NULL;
    free(flightSArrivalDate);
    flightSArrivalDate = NULL;
    free(flightRDepartureDate);
    flightRDepartureDate = NULL;
    free(flightRArrivalDate);
    flightRArrivalDate = NULL;
}
