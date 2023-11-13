#include "../include/interpreter.h"
#include <stdio.h>
#include <utils.h>
#include <queries.h>

int readEntryFile(int agrc, char **argv){
    FILE * comandos = fopen(argv[2],"r");

    if (comandos == NULL){ perror("Erro a abrir o ficheiro dos comandos"); return 1;} 

    char * linha = malloc(sizeof(char) * BUFFERSIZE);

    if(!linha) { perror("Erro a alocar memoria no readFile"); return 1;}

    while(fgets(linha,sizeof(linha),comandos)){
        // colocar funcoes para identificar quais as queries para enviar para as queries certas
        switch (linha[0])
        {

        //QUERIE 1 ou 10
        case '1':

            //QUERIE 10
            if(linha[1] == '0'){
                if(linha[2] == 'F'){
                    char * resultadoQuerie10 = query10(&linha[4]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie10 = query10(&linha[3]);
                    //mandar para o output sem F
                }

            //QUERIE 1
            }else {
                if(linha[1] == 'F'){
                    char * resultadoQuerie1 = query1(&linha[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie1 = query1(&linha[2]);
                    //mandar para o output sem F
                }
            }

            break;
        
        //QUERIE 2
        case '2':

            if(linha[1] == 'F'){
                    char * resultadoQuerie2 = query2(&linha[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie2 = query2(&linha[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 3
        case '3':

            if(linha[1] == 'F'){
                    char * resultadoQuerie3 = query3(&linha[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie3 = query3(&linha[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 4
        case '4':

            if(linha[1] == 'F'){
                    char * resultadoQuerie4 = query4(&linha[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie4 = query4(&linha[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 5
        case '5':

            if(linha[1] == 'F'){
                    char * resultadoQuerie5 = query5(&linha[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie5 = query5(&linha[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 6
        case '6':

            if(linha[1] == 'F'){
                    char * resultadoQuerie6 = query6(&linha[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie6 = query6(&linha[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 7
        case '7':

            if(linha[1] == 'F'){
                    char * resultadoQuerie7 = query7(&linha[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie7 = query7(&linha[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 8
        case '8':

            if(linha[1] == 'F'){
                    char * resultadoQuerie8 = query8(&linha[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie8 = query8(&linha[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 9
        case '9':

            if(linha[1] == 'F'){
                    char * resultadoQuerie9 = query9(&linha[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie9 = query9(&linha[2]);
                    //mandar para o output sem F
                }

            break;


        default:
                perror("Erro ao detetar querie");
            break;
        }
    }

    free(linha);
    fclose(comandos);

    return 0;
}

