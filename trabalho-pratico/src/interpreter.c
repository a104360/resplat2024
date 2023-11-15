#include "../include/interpreter.h"
#include <stdio.h>
#include <string.h>
#include "../include/queries.h"

#define BUFFERSIZE 1000


int verTamanhoLinha(char * linha){
    int i = 0;
    int count = 0;
    while(linha[i] != '\0'){
        count++;
        i++;
    }
    return count;
}

int readEntryFile(int agrc, char **argv){
    FILE * comandos = fopen(argv[2],"r");

    if (comandos == NULL){ perror("Erro a abrir o ficheiro dos comandos"); return 1;} 

    char * linha = malloc(sizeof(char) * BUFFERSIZE);

    if(!linha) { perror("Erro a alocar memoria no readFile"); return 1;}

    memset(linha, '\0', sizeof(linha));

    while(fgets(linha,sizeof(linha),comandos)){

        int tamanhoLinha = verTamanhoLinha(linha);

        char linhaLimpa[tamanhoLinha +1];

        strncpy(linhaLimpa,linha,tamanhoLinha);

        linhaLimpa[tamanhoLinha] = '\0';

        switch (linhaLimpa[0])
        {

        //QUERIE 1 ou 10
        case '1':

            //QUERIE 10
            if(linhaLimpa[1] == '0'){
                if(linhaLimpa[2] == 'F'){
                    char * resultadoQuerie10 = query10(&linhaLimpa[4]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie10 = query10(&linhaLimpa[3]);
                    //mandar para o output sem F
                }

            //QUERIE 1
            }else {
                if(linhaLimpa[1] == 'F'){
                    char * resultadoQuerie1 = query1(&linhaLimpa[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie1 = query1(&linhaLimpa[2]);
                    //mandar para o output sem F
                }
            }

            break;
        
        //QUERIE 2
        case '2':

            if(linhaLimpa[1] == 'F'){
                    char * resultadoQuerie2 = query2(&linhaLimpa[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie2 = query2(&linhaLimpa[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 3
        case '3':

            if(linhaLimpa[1] == 'F'){
                    char * resultadoQuerie3 = query3(&linhaLimpa[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie3 = query3(&linhaLimpa[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 4
        case '4':

            if(linhaLimpa[1] == 'F'){
                    char * resultadoQuerie4 = query4(&linhaLimpa[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie4 = query4(&linhaLimpa[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 5
        case '5':

            if(linhaLimpa[1] == 'F'){
                    char * resultadoQuerie5 = query5(&linhaLimpa[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie5 = query5(&linhaLimpa[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 6
        case '6':

            if(linhaLimpa[1] == 'F'){
                    char * resultadoQuerie6 = query6(&linhaLimpa[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie6 = query6(&linhaLimpa[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 7
        case '7':

            if(linhaLimpa[1] == 'F'){
                    char * resultadoQuerie7 = query7(&linhaLimpa[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie7 = query7(&linhaLimpa[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 8
        case '8':

            if(linhaLimpa[1] == 'F'){
                    char * resultadoQuerie8 = query8(&linhaLimpa[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie8 = query8(&linhaLimpa[2]);
                    //mandar para o output sem F
                }

            break;


        //QUERIE 9
        case '9':

            if(linhaLimpa[1] == 'F'){
                    char * resultadoQuerie9 = query9(&linhaLimpa[3]);
                    //mandar para o output das F
                }else {
                    char * resultadoQuerie9 = query9(&linhaLimpa[2]);
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