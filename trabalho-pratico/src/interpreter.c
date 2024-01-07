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

<<<<<<< HEAD
char * yearQ6(const char * line){

=======

char * getSecondParam(const char * line){
>>>>>>> main
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux," \n\0",&saveptr);
<<<<<<< HEAD

    char * temp = strdup(token);

    free(aux);
    aux = NULL;
    return temp;
}

char * airportsQ6(const char * line){

    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux," \n\0",&saveptr);
    TOKENIZE(token,saveptr);

    char * temp = strdup(token);

    free(aux);
    aux = NULL;
    return temp;
}
=======
    
    if(token){
        token = strtok_r(NULL," \n\0",&saveptr);
        char * temp = strdup(token);
        ffree((void **) &aux);
        return temp;
    }
    ffree((void **) &aux);
    return NULL;
}


>>>>>>> main

void readEntryFile(const Users * uDatabase,const Reservations * rDatabase,const Flights * fDatabase,const Passengers * pDatabase,int agrc, char **argv){
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
                if(linhaLimpa[2] == 'F'){
                    query10(&linhaLimpa[4]);
                    
                }else {
                    query10(&linhaLimpa[3]);
                    
                }

            //QUERIE 1
            }else {
                if(linhaLimpa[1] == 'F'){
                    query1((const Users *) uDatabase,(const Reservations *) rDatabase,(const Flights *) fDatabase,(const Passengers *) pDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query1((const Users *) uDatabase,(const Reservations *) rDatabase,(const Flights *) fDatabase,(const Passengers *) pDatabase,&linhaLimpa[2],false);
                    
                }
            }

            break;
        
        //QUERIE 2
        case '2':

            if(linhaLimpa[1] == 'F'){
                    query2((const Users * ) uDatabase,(const Reservations * ) rDatabase,(const Flights * ) fDatabase,(const Passengers *) pDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query2((const Users * ) uDatabase,(const Reservations * ) rDatabase,(const Flights * ) fDatabase,(const Passengers *) pDatabase,&linhaLimpa[2],false);
                    
                }

            break;


        //QUERIE 3
        case '3':

            if(linhaLimpa[1] == 'F'){
                    query3((Reservations * ) rDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query3((Reservations * ) rDatabase,&linhaLimpa[2],false);
                    
                }

            break;


        //QUERIE 4
        case '4':

            if(linhaLimpa[1] == 'F'){
                    query4((Reservations *) rDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query4((Reservations *) rDatabase,&linhaLimpa[2],false);
                    
                }

            break;


        //QUERIE 5
        case '5':
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

            break;


        //QUERIE 6
        case '6':
            if(linhaLimpa[1] == 'F'){
<<<<<<< HEAD
                    char * year = yearQ6(&linhaLimpa[3]);
                    char * nAirports = airportsQ6(&linhaLimpa[3]);
                    query6((Flights *) fDatabase,(Passengers *) pDatabase,year,nAirports,true);
                    
                }else {
                    char * year = yearQ6(&linhaLimpa[2]);
                    char * nAirports = airportsQ6(&linhaLimpa[2]);
                    query6((Flights *) fDatabase,(Passengers *) pDatabase,year,nAirports,true);
                    
                }
=======
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
>>>>>>> main
            break;


        //QUERIE 7
        case '7':

            if(linhaLimpa[1] == 'F'){
                    
                    query7((Flights *) fDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query7((Flights *) fDatabase,&linhaLimpa[2],false);
                    
                }

            break;


        //QUERIE 8
        case '8':

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

            break;


        //QUERIE 9
        case '9':

            if(linhaLimpa[1] == 'F'){
                    query9((Users *) uDatabase,limpaToken(&linhaLimpa[3]),true);
                    
                }else {
                    query9((Users *) uDatabase,limpaToken(&linhaLimpa[2]),false);
                    
                }

            break;


        default:
                perror("Erro ao detetar querie");
            break;
        }
    }
    ffree((void **) &line);
    fclose(comandos);
}