#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/interpreter.h"
#include "../include/queries.h"
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/passenger.h"
#include "../include/dataStructs.h"
#include "../include/catalogs.h"
#include "../include/parser.h"

#define BUFFERSIZE 1000
#define TOKENIZE(token,saveptr) token = strtok_r(NULL," \n\0",&saveptr);
#define FREE(ptr) if(ptr){free(ptr); ptr = NULL;} 


int verTamanhoLinha(const char * linha){
    int i = 0;
    int count = 0;
    while(linha[i] != '\0'){
        count++;
        i++;
    }
    return count;
}

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

Time * firstDateQ5(const char * line){
        
    char * aux = strndup(line,20);
    char * tokenLimpo = limpaToken(aux);
    Time * firstDate = dateCheck(tokenLimpo);

    free(aux);
    aux = NULL;

    return firstDate;
}

Time * secondDateQ5(const char * line){

    char * aux = strndup(line,20);
    char * tokenLimpo = limpaToken(aux);
    Time * secondDate = dateCheck(tokenLimpo);

    free(aux);
    aux = NULL;

    return secondDate;
}

Time * firstDateQ8(const char * line){
        
    char * aux = strndup(line,10);
    Time * firstDate = dateCheck(aux);

    free(aux);
    aux = NULL;

    return firstDate;
}

Time * secondDateQ8(const char * line){

    char * aux = strndup(line,10);
    Time * secondDate = dateCheck(aux);

    free(aux);
    aux = NULL;

    return secondDate;
}

char * airportName(const char * line){

    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux," \n\0",&saveptr);

    char * temp = strdup(token);

    free(aux);
    aux = NULL;
    return temp;
}

void readEntryFile(const UsersDatabase uDatabase,const ReservationsDatabase rDatabase,const FlightsDatabase fDatabase,const PassengersDatabase * pDatabase,int agrc, char **argv){
    if(uDatabase == NULL || rDatabase == NULL || fDatabase == NULL || pDatabase == NULL) return;
    FILE * comandos = fopen(argv[2],"r");

    if (comandos == NULL){ perror("Erro a abrir o ficheiro dos comandos"); return;} 

    char * linha = malloc(sizeof(char) * BUFFERSIZE);

    if(!linha) { perror("Erro a alocar memoria no readFile"); return;}

    memset(linha, '\0', BUFFERSIZE);

    while(fgets(linha,BUFFERSIZE,comandos)){

        int tamanhoLinha = verTamanhoLinha(linha);

        char linhaLimpa[tamanhoLinha +1];

        strncpy(linhaLimpa,linha,tamanhoLinha);

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
                    query1((const UsersDatabase) uDatabase,(const ReservationsDatabase) rDatabase,(const FlightsDatabase) fDatabase,(const PassengersDatabase *) pDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query1((const UsersDatabase) uDatabase,(const ReservationsDatabase) rDatabase,(const FlightsDatabase) fDatabase,(const PassengersDatabase *) pDatabase,&linhaLimpa[2],false);
                    
                }
            }

            break;
        
        //QUERIE 2
        case '2':

            if(linhaLimpa[1] == 'F'){
                    query2((const UsersDatabase) uDatabase,(const ReservationsDatabase) rDatabase,(const FlightsDatabase) fDatabase,(const PassengersDatabase *) pDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query2((const UsersDatabase) uDatabase,(const ReservationsDatabase) rDatabase,(const FlightsDatabase) fDatabase,(const PassengersDatabase *) pDatabase,&linhaLimpa[2],false);
                    
                }

            break;


        //QUERIE 3
        case '3':

            if(linhaLimpa[1] == 'F'){
                    query3((const ReservationsDatabase) rDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query3((const ReservationsDatabase) rDatabase,&linhaLimpa[2],false);
                    
                }

            break;


        //QUERIE 4
        case '4':

            if(linhaLimpa[1] == 'F'){
                    query4(rDatabase,&linhaLimpa[3],true);
                    
                }else {
                    query4(rDatabase,&linhaLimpa[2],false);
                    
                }

            break;


        //QUERIE 5
        case '5':
            Time * firstDate = firstDateQ5(&linhaLimpa[7]);
            Time * secondDate = secondDateQ5(&linhaLimpa[29]);
            if(linhaLimpa[1] == 'F'){
                    char * airport = airportName(&linhaLimpa[3]);
                    query5((const FlightsDatabase) fDatabase,firstDate,secondDate,airport,true);
                    destroyTime(firstDate);
                    destroyTime(secondDate);
                    free(airport);
                    airport = NULL;
                }else {
                    char * airport = airportName(&linhaLimpa[2]);
                    query5((const FlightsDatabase) fDatabase,firstDate,secondDate,airport,false);
                    destroyTime(firstDate);
                    destroyTime(secondDate);
                    free(airport);
                    airport = NULL;
                }

            break;


        //QUERIE 6
        case '6':

            if(linhaLimpa[1] == 'F'){
                    query6(&linhaLimpa[3]);
                    
                }else {
                    query6(&linhaLimpa[2]);
                    
                }

            break;


        //QUERIE 7
        case '7':

            if(linhaLimpa[1] == 'F'){
                    query7(&linhaLimpa[3]);
                    
                }else {
                    query7(&linhaLimpa[2]);
                    
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

                    int tokenSize = verTamanhoLinha(token);


                    Time * firstDate = firstDateQ8(&linhaLimpa[4+tokenSize]);
                    Time * secondDate = secondDateQ8(&linhaLimpa[15+tokenSize]);

                    query8(rDatabase,token,firstDate,secondDate,true);

                    FREE(aux);
                    destroyTime(firstDate);
                    destroyTime(secondDate);
                    
                }else{
                    char * aux = strdup(linhaLimpa);
                    char * token = NULL;
                    char * saveptr = aux;
                    token = strtok_r(aux," \n\0",&saveptr);
                    TOKENIZE(token,saveptr);

                    int tokenSize = verTamanhoLinha(token);

                    Time * firstDate = firstDateQ8(&linhaLimpa[3+tokenSize]);
                    Time * secondDate = secondDateQ8(&linhaLimpa[14+tokenSize]);

                    query8(rDatabase,token,firstDate,secondDate,false);

                    FREE(aux);
                    destroyTime(firstDate);
                    destroyTime(secondDate);
                    
                }

            break;


        //QUERIE 9
        case '9':

            if(linhaLimpa[1] == 'F'){
                    query9(&linhaLimpa[3]);
                    
                }else {
                    query9(&linhaLimpa[2]);
                    
                }

            break;


        default:
                perror("Erro ao detetar querie");
            break;
        }
    }
    free(linha);
    fclose(comandos);
}