#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include "../include/parser.h"
#include "../include/interpreter.h"
#include "../include/user.h"
#include "../include/reservation.h"
#include "../include/flight.h"
#include "../include/passengers.h"
#include "../include/statistics.h"
#include "../include/testes.h"
#include "../include/ui.h"

#define BUFFERSIZE 1000

bool interactive = false;   

int main(int argc,char **argv){

    struct timespec start, end;
    double elapsed;
    double queriesTimes[10] = {0,0,0,0,0,0,0,0,0,0};
    
    //start time
    
    clock_gettime(CLOCK_REALTIME, &start);

    setlocale(LC_COLLATE, "en_US.UTF-8");
    if(argc == 1){
        interactive = true;
        //printf("Modo interativo em desenvolvimento\n");
        menus();
        return 0;
    }
    if(argc == 3){

        Users * uDatabase = validateUsers(argv[1]);

        Reservations * rDatabase = validateReservations(uDatabase,argv[1]);

        Flights * fDatabase = validateFlights(argv[1]);


        Passengers * pDatabase = validatePassengers(uDatabase,fDatabase,argv[1]);


        readEntryFile((const Users *) uDatabase,(const Reservations *) rDatabase,(const Flights *) fDatabase,(const Passengers *) pDatabase,argc,argv,queriesTimes);

        // Free everything used
        destroyPassengers(pDatabase);
        destroyDatabase(uDatabase);
        destroyDatabase(fDatabase);
        destroyDatabase(rDatabase);
    }
    if(argc == 4){
        confirmar();
    }

    //end time
    clock_gettime(CLOCK_REALTIME, &end);

    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    //queries time
    for(int t = 0; t<10; t++){
        printf("\nA querie %d demorou %.6f segundos a ser executada.", t+1, queriesTimes[t]);
    }
    
    //total time
    printf("\nO programa demorou %.6f segundos a ser executado.\n", elapsed);


    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);

    printf("\n\nO programa usou %ld KB de memória\n", r_usage.ru_maxrss);

    return 0;
}