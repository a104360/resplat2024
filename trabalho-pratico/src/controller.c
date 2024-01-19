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

void run(char ** argv){
    setlocale(LC_COLLATE, "en_US.UTF-8");

    Users * uDatabase = validateUsers(argv[1]);

    Reservations * rDatabase = validateReservations(uDatabase,argv[1]);

    Flights * fDatabase = validateFlights(argv[1]);

    Passengers * pDatabase = validatePassengers(uDatabase,fDatabase,argv[1]);


    readEntryFile((const Users *) uDatabase,(const Reservations *) rDatabase,(const Flights *) fDatabase,(const Passengers *) pDatabase,3,argv,NULL,NULL);

    // Free everything used
    destroyPassengers(pDatabase);
    destroyDatabase(uDatabase);
    destroyDatabase(fDatabase);
    destroyDatabase(rDatabase);
}

void test(char ** argv){
    struct timespec start, end;
        double elapsed;
        double queriesTimes[10] = {0,0,0,0,0,0,0,0,0,0};
        int queriesNumExec[10] = {0,0,0,0,0,0,0,0,0,0};
        
        //start time
        
        clock_gettime(CLOCK_REALTIME, &start);

        setlocale(LC_COLLATE, "en_US.UTF-8");

        Users * uDatabase = validateUsers(argv[1]);

        Reservations * rDatabase = validateReservations(uDatabase,argv[1]);

        Flights * fDatabase = validateFlights(argv[1]);


        Passengers * pDatabase = validatePassengers(uDatabase,fDatabase,argv[1]);


        readEntryFile((const Users *) uDatabase,(const Reservations *) rDatabase,(const Flights *) fDatabase,(const Passengers *) pDatabase,4,argv,queriesTimes,queriesNumExec);

        // Free everything used
        destroyPassengers(pDatabase);
        destroyDatabase(uDatabase);
        destroyDatabase(fDatabase);
        destroyDatabase(rDatabase);

        confirmar(argv);

        //end time
        clock_gettime(CLOCK_REALTIME, &end);

        elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

        //queries time
        for(int t = 0; t<10; t++){
            printf("\nA querie %d demorou %.6f segundos a ser executada e foi executada %d vezes", t+1, queriesTimes[t]/queriesNumExec[t], queriesNumExec[t]);
        }
        
        //total time
        printf("\nO programa demorou %.6f segundos a ser executado.\n", elapsed);


        struct rusage r_usage;
        getrusage(RUSAGE_SELF, &r_usage);

        printf("\n\nO programa usou %ld KB de memória.\n", r_usage.ru_maxrss);
}