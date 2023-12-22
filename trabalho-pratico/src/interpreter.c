#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/interpreter.h"
#include "../include/queries.h"
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/passenger.h"
#include "../include/parser.h"

#define BUFFERSIZE 1000
#define TOKENIZE(token,saveptr) token = strtok_r(NULL," \n\0",&saveptr);

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

    ffree(aux);

    return firstDate;
}

Time * secondDateQ5(const char * line){

    char * aux = strndup(line,20);
    char * tokenLimpo = limpaToken(aux);
    Time * secondDate = dateCheck(tokenLimpo);

    ffree(aux);

    return secondDate;
}

Time * firstDateQ8(const char * line){
        
    char * aux = strndup(line,10);
    Time * firstDate = dateCheck(aux);

    ffree(aux);

    return firstDate;
}

Time * secondDateQ8(const char * line){

    char * aux = strndup(line,10);
    Time * secondDate = dateCheck(aux);

    ffree(aux);

    return secondDate;
}

char * airportName(const char * line){

    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux," \n\0",&saveptr);

    char * temp = strdup(token);

    ffree(aux);
    return temp;
}

void readEntryFile(const Users * uDatabase,const Reservations * rDatabase,const Flights * fDatabase,const Passengers * pDatabase,int agrc, char **argv){
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
            Time * firstDate = firstDateQ5(&linhaLimpa[7]);
            Time * secondDate = secondDateQ5(&linhaLimpa[29]);
            if(linhaLimpa[1] == 'F'){
                    char * airport = airportName(&linhaLimpa[3]);
                    query5((const Flights * ) fDatabase,firstDate,secondDate,airport,true);
                    destroyTime(firstDate);
                    destroyTime(secondDate);
                    ffree(airport);
                }else {
                    char * airport = airportName(&linhaLimpa[2]);
                    query5((const Flights * ) fDatabase,firstDate,secondDate,airport,false);
                    destroyTime(firstDate);
                    destroyTime(secondDate);
                    ffree(airport);
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

                    query8((Reservations *) rDatabase,token,firstDate,secondDate,true);

                    ffree(aux);
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

                    query8((Reservations *) rDatabase,token,firstDate,secondDate,false);

                    ffree(aux);
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
    ffree(linha);
    fclose(comandos);
}