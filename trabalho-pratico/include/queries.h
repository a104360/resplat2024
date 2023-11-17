#ifndef QUERIES_H
#define QUERIES_H
#include "../include/dataTypes.h"
#include "../include/dataStructs.h"
#include "../include/catalogs.h"

// Listar o resumo de um user/reserva/voo, através do identificador
void query1(UsersDatabase *, ReservationsDatabase *,FlightsDatabase *,PassangersDatabase *,const char * ,bool);

//listar voos ou reservas de um user !!atencao ao enunciado!!
char * query2(UsersDatabase , ReservationsDatabase ,FlightsDatabase,PassangersDatabase *,const char *,char *,bool);

//apresentar classificacao media de um hotel, atraves do identificador
char * query3();

//listar reservas de um hotel ordenadas pela data de inicio (recente -> antiga) (Se houver 2 mesma data, usar id)
char * query4();

//listar voos com origem num dado aeroporto, entre 2 datas, ordenados por data partida estimada (antiga -> recente) (se houver 2, usar id)
char * query5();

//listar top N aeroportos com mais passageiros, para um dado ano. Contabilizar voos com data estimada de partida nesse ano. (se 2, usar nome)
char * query6();

//listar top N aeroportos com maior mediana de atrasos. Valor atraso em segundos. (se 2, usar nome)
char * query7();

//Apresentar receita total,de um hotel entre 2 datas, apartir do identificador. (usar preco/1noite * num_noites)
char * query8();

//listar todos os users cujo nome começa com o prefixo do argumento, ordenados por nome (crescente) (se 2, usar id)
char * query9();

//Apresentar metricas gerais:
/*  num_novos_users; 
    num_voos (de acordo com o campo schedule_departure_date)
    num_passageiros;
    num_passageiros_unicos;
    num_reservas (de acordo com o begin_date)*/
char * query10();

#endif