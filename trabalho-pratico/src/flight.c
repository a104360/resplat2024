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
        ffree((void **) &f->id);
        ffree((void **) &f->airline);
        ffree((void **) &f->plane_model);
        ffree((void **) &f->origin);
        ffree((void **) &f->destination);
        destroyTime(f->schedule_departure_date); 
        destroyTime(f->schedule_arrival_date); 
        destroyTime(f->real_departure_date); 
        destroyTime(f->real_arrival_date); 
        ffree((void **) &f->pilot);
        ffree((void **) &f->copilot);
        ffree((void **) &f->notes);
        ffree((void **) &f); 
    }
}


void setFlightId(Flight * flight,const char * line){
    if(flight == NULL) return;

    ffree((void **) &flight->id);

    flight->id = strdup(line);
}

char *getFlightId(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->id){
        char * id = strdup(flight->id);
        return id;
    }
    return NULL;
}

  
void setFlightAirline(Flight * flight,const char * line){
    if(flight == NULL) return;

    ffree((void **) &flight->airline);

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

    ffree((void **) &flight->plane_model);

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

    ffree((void **) &flight->origin);

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
    ffree((void **) &flight->destination);
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

    ffree((void **) &flight->pilot);

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
    
    ffree((void **) &flight->copilot);
    
    flight->copilot = strdup(line);
}

char *getFlightCopilot(Flight * flight){
    if(flight == NULL) return NULL;
    if(flight->copilot){
        char * copilot = strdup(flight->copilot);
        return copilot;
    }
    return NULL;
}


void setFlightNotes(Flight * flight,const char * line){
    if(line == NULL || flight == NULL) return;

    ffree((void **) &flight->notes);
    
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
    return ((getYear(flight->real_departure_date) - getYear(flight->schedule_departure_date)) * 32140800) + 
    ((getMon(flight->real_departure_date) - getMon(flight->schedule_departure_date)) * 2678400) + 
    ((getMday(flight->real_departure_date) - getMday(flight->schedule_departure_date)) * 86400) + 
    ((getHour(flight->real_departure_date) - getHour(flight->schedule_departure_date)) * 3600) + 
    ((getMin(flight->real_departure_date) - getMin(flight->schedule_departure_date)) * 60) +
    ((getSec(flight->real_departure_date) - getSec(flight->schedule_departure_date)));
}


void copyFlight(Flight * dest,Flight * src){
    if(dest == NULL || src == NULL) return;
    char * flightId = getFlightId(src);                         setFlightId(dest,flightId);                         ffree((void **) &flightId);
    char * flightAirline = getFlightAirline(src);               setFlightAirline(dest,flightAirline);               ffree((void **) &flightAirline);
    char * flightPlaneModel = getFlightPlaneModel(src);         setFlightPlaneModel(dest,flightPlaneModel);         ffree((void **) &flightPlaneModel);
    char * flightOrigin = getFlightOrigin(src);                 setFlightOrigin(dest,flightOrigin);                 ffree((void **) &flightOrigin);
    char * flightDestination = getFlightDestination(src);       setFlightDestination(dest,flightDestination);       ffree((void **) &flightDestination);
    char * flightPilot = getFlightPilot(src);                   setFlightPilot(dest,flightPilot);                   ffree((void **) &flightPilot);
    char * flightCopilot = getFlightCopilot(src);               setFlightCopilot(dest,flightCopilot);               ffree((void **) &flightCopilot);
    char * flightNotes = getFlightNotes(src);                   setFlightNotes(dest,flightNotes);                   ffree((void **) &flightNotes);
    Time * flightSDepartureDate = getFlightSDepartureDate(src); setFlightSDepartureDate(dest,flightSDepartureDate); destroyTime(flightSDepartureDate);
    Time * flightSArrivalDate = getFlightSArrivalDate(src);     setFlightSArrivalDate(dest,flightSArrivalDate);     destroyTime(flightSArrivalDate);
    Time * flightRDepartureDate = getFlightRDepartureDate(src); setFlightRDepartureDate(dest,flightRDepartureDate); destroyTime(flightRDepartureDate);
    Time * flightRArrivalDate = getFlightRArrivalDate(src);     setFlightRArrivalDate(dest,flightRArrivalDate);     destroyTime(flightRArrivalDate);
    
    setFlightTotalSeats(dest,getFlightTotalSeats(src));
}
