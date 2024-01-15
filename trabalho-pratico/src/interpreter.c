#include "../include/interpreter.h"
#include "../include/queries.h"
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/passenger.h"
#include "../include/parser.h"
#include "../include/time.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 1000
#define TOKENIZE(token,saveptr) token = strtok_r(NULL," \n\0",&saveptr);

char * limpaToken(char * token){
    int tamanho = 0;
    if(token[0] == '\"'){
        while(token[tamanho]){
            token[tamanho] = token[tamanho+1];
            tamanho++;
        }
        token[tamanho-2]='\0';
    }
    return token;
}

Time * dateQ5(const char * line){
        
    char * aux = strndup(line,20);
    char * tokenLimpo = limpaToken(aux);
    Time * firstDate = dateCheck(tokenLimpo);

    ffree((void **) &aux);

    return firstDate;
}

Time * dateQ8(const char * line){
        
    char * aux = strndup(line,10);
    Time * firstDate = dateCheck(aux);

    ffree((void **) &aux);

    return firstDate;
}

char * airportName(const char * line){

    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux," \n\0",&saveptr);

    char * temp = strdup(token);

    ffree((void **) &aux);
    return temp;
}


char * getSecondParam(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux," \n\0",&saveptr);
    
    if(token){
        token = strtok_r(NULL," \n\0",&saveptr);
        char * temp = strdup(token);
        ffree((void **) &aux);
        return temp;
    }
    ffree((void **) &aux);
    return NULL;
}



void readEntryFile(const Users * uDatabase,const Reservations * rDatabase,const Flights * fDatabase,const Passengers * pDatabase,int agrc, char **argv, double * queriesTimes,int * queriesNumExec){

    //Time
    struct timespec start, end;
    double elapsed;

    if(uDatabase == NULL || rDatabase == NULL || fDatabase == NULL || pDatabase == NULL) return;
    FILE * comandos = fopen(argv[2],"r");

    if (comandos == NULL){ perror("Erro a abrir o ficheiro dos comandos"); return;} 

    char * line = malloc(sizeof(char) * BUFFERSIZE);

    if(!line) { perror("Erro a alocar memoria no readFile"); return;}

    memset(line, '\0', BUFFERSIZE);

    while(fgets(line,BUFFERSIZE,comandos)){

        int tamanhoLinha = strlen(line);

        char linhaLimpa[tamanhoLinha +1];

        strncpy(linhaLimpa,line,tamanhoLinha);

        linhaLimpa[tamanhoLinha - 1] = '\0';

        switch (linhaLimpa[0])
        {

        //QUERIE 1 ou 10
        case '1':


            //QUERIE 10
            if(linhaLimpa[1] == '0'){

            queriesNumExec[9] ++;
            
            //start time
            clock_gettime(CLOCK_REALTIME, &start);

                if(linhaLimpa[2] == 'F'){
                        query10(&linhaLimpa[4]);

                    

                }else {
                    query10(&linhaLimpa[3]);
                    
                }
                //end time
                clock_gettime(CLOCK_REALTIME, &end);
                elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

                queriesTimes[9] += elapsed;

            //QUERIE 1
            }else {

                queriesNumExec[0] ++;

                //start time
                clock_gettime(CLOCK_REALTIME, &start);

                if(linhaLimpa[1] == 'F'){
                    query1((const Users *) uDatabase,(const Reservations *) rDatabase,(const Flights *) fDatabase,(const Passengers *) pDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query1((const Users *) uDatabase,(const Reservations *) rDatabase,(const Flights *) fDatabase,(const Passengers *) pDatabase,&linhaLimpa[2],false);
                    
                }

                //end time
                clock_gettime(CLOCK_REALTIME, &end);
                elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

                queriesTimes[0] += elapsed;
            }

            break;
        
        //QUERIE 2
        case '2':

            queriesNumExec[1] ++;

            //start time
            clock_gettime(CLOCK_REALTIME, &start);

            if(linhaLimpa[1] == 'F'){
                    query2((const Users * ) uDatabase,(const Reservations * ) rDatabase,(const Flights * ) fDatabase,(const Passengers *) pDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query2((const Users * ) uDatabase,(const Reservations * ) rDatabase,(const Flights * ) fDatabase,(const Passengers *) pDatabase,&linhaLimpa[2],false);
                    
                }

            //end time
            clock_gettime(CLOCK_REALTIME, &end);
            elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

            queriesTimes[1] += elapsed;

            break;


        //QUERIE 3
        case '3':

            queriesNumExec[2] ++;

            //start time
            clock_gettime(CLOCK_REALTIME, &start);

            if(linhaLimpa[1] == 'F'){
                    query3((Reservations * ) rDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query3((Reservations * ) rDatabase,&linhaLimpa[2],false);
                    
                }

            //end time
            clock_gettime(CLOCK_REALTIME, &end);
            elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            
            queriesTimes[2] += elapsed;

            break;


        //QUERIE 4
        case '4':

            queriesNumExec[3] ++;

            //start time
            clock_gettime(CLOCK_REALTIME, &start);

            if(linhaLimpa[1] == 'F'){
                    query4((Reservations *) rDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query4((Reservations *) rDatabase,&linhaLimpa[2],false);
                    
                }

            //end time
            clock_gettime(CLOCK_REALTIME, &end);
            elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
            
            queriesTimes[3] += elapsed;

            break;


        //QUERIE 5
        case '5':

            queriesNumExec[4] ++;

            //start time
            clock_gettime(CLOCK_REALTIME, &start);

            Time * firstDate = dateQ5(&linhaLimpa[7]);
            Time * secondDate = dateQ5(&linhaLimpa[29]);
            if(linhaLimpa[1] == 'F'){
                    char * airport = airportName(&linhaLimpa[3]);
                    query5((const Flights * ) fDatabase,firstDate,secondDate,airport,true);
                    destroyTime(firstDate);
                    destroyTime(secondDate);
                    ffree((void **) &airport);
                }else {
                    char * airport = airportName(&linhaLimpa[2]);
                    query5((const Flights * ) fDatabase,firstDate,secondDate,airport,false);
                    destroyTime(firstDate);
                    destroyTime(secondDate);
                    ffree((void **) &airport);
                }

            //end time
            clock_gettime(CLOCK_REALTIME, &end);
            elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

            queriesTimes[4] += elapsed;

            break;


        //QUERIE 6
        case '6':

            queriesNumExec[5] ++;

            //start time
            clock_gettime(CLOCK_REALTIME, &start);

            if(linhaLimpa[1] == 'F'){
                char * year = airportName(&linhaLimpa[3]);
                char * nAirports = getSecondParam(&linhaLimpa[3]);
                query6((const Flights *) fDatabase,(const Passengers *) pDatabase,year,nAirports,true);
                ffree((void **) &year);
                ffree((void **) &nAirports);

                
            }else {
                char * year = airportName(&linhaLimpa[2]);
                char * nAirports = getSecondParam(&linhaLimpa[2]);
                query6((const Flights *) fDatabase,(const Passengers *) pDatabase,year,nAirports,false);
                ffree((void **) &year);
                ffree((void **) &nAirports);

            }

            //end time
            clock_gettime(CLOCK_REALTIME, &end);
            elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

            queriesTimes[5] += elapsed;

            break;


        //QUERIE 7
        case '7':

            queriesNumExec[6] ++;

            //start time
            clock_gettime(CLOCK_REALTIME, &start);

            if(linhaLimpa[1] == 'F'){
                    
                    query7((Flights *) fDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query7((Flights *) fDatabase,&linhaLimpa[2],false);
                    
                }

            //end time
            clock_gettime(CLOCK_REALTIME, &end);
            elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

            queriesTimes[6] += elapsed;

            break;


        //QUERIE 8
        case '8':

            queriesNumExec[7] ++;

            //start time
            clock_gettime(CLOCK_REALTIME, &start);

            if(linhaLimpa[1] == 'F'){
                    char * aux = strdup(linhaLimpa);
                    char * token = NULL;
                    char * saveptr = aux;
                    token = strtok_r(aux," \n\0",&saveptr);
                    TOKENIZE(token,saveptr);

                    int tokenSize = strlen(token);


                    Time * firstDate = dateQ8(&linhaLimpa[4+tokenSize]);
                    Time * secondDate = dateQ8(&linhaLimpa[15+tokenSize]);

                    query8((Reservations *) rDatabase,token,firstDate,secondDate,true);

                    ffree((void **) &aux);
                    destroyTime(firstDate);
                    destroyTime(secondDate);
                    
                }else{
                    char * aux = strdup(linhaLimpa);
                    char * token = NULL;
                    char * saveptr = aux;
                    token = strtok_r(aux," \n\0",&saveptr);
                    TOKENIZE(token,saveptr);

                    int tokenSize = strlen(token);

                    Time * firstDate = dateQ8(&linhaLimpa[3+tokenSize]);
                    Time * secondDate = dateQ8(&linhaLimpa[14+tokenSize]);

                    query8((Reservations *) rDatabase,token,firstDate,secondDate,false);

                    ffree((void **) &aux);
                    destroyTime(firstDate);
                    destroyTime(secondDate);
                    
                }

            //end time
            clock_gettime(CLOCK_REALTIME, &end);
            elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

            queriesTimes[7] += elapsed;

            break;


        //QUERIE 9
        case '9':

            queriesNumExec[8] ++;

            //start time
            clock_gettime(CLOCK_REALTIME, &start);

            if(linhaLimpa[1] == 'F'){
                    query9((Users *) uDatabase,limpaToken(&linhaLimpa[3]),true);
                    
                }else {
                    query9((Users *) uDatabase,limpaToken(&linhaLimpa[2]),false);
                    
                }

            //end time
            clock_gettime(CLOCK_REALTIME, &end);
            elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

            queriesTimes[8] += elapsed;

            break;


        default:
                perror("Erro ao detetar querie");
            break;
        }
    }
    ffree((void **) &line);
    fclose(comandos);
}