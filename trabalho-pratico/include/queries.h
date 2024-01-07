#ifndef QUERIES_H
#define QUERIES_H
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/passengers.h"
#include "../include/utils.h"

/**
 * @brief Lists the informations related to a user/reservation/flight, throght the id
 * @param users Pointer to the users database
 * @param reseravtions Pointer to the reseravtions database
 * @param flights Pointer to the flights database
 * @param passenger Pointer to the passenger database
 * @param id Id of what is going to be searched
 * @param f Mode of the outputs
*/
void query1(const Users *, const Reservations *,const Flights *,const Passengers *,const char *,bool);

/**
 * @brief Lists the flights or reservations of an user
 * @param users Pointer to the users database
 * @param reseravtions Pointer to the reseravtions database
 * @param flights Pointer to the flights database
 * @param passenger Pointer to the passenger database
 * @param id Id of the user
 * @param f Mode of the outputs
*/
void query2(const Users * ,const Reservations *,const Flights *,const Passengers *,const char *,bool);

//apresentar classificacao media de um hotel, atraves do identificador
/**
 * @brief Presents the average rating of an hotel, by its id
 * @param reservations Pointer to the reservations database
 * @param hotelId Id of the hotel
 * @param f Mode of the outputs
*/
void query3(Reservations *,const char *,bool);

//listar reservas de um hotel ordenadas pela data de inicio (recente -> antiga) (Se houver 2 mesma data, usar id)
/**
 * @brief List reservations of an hotel, sorted by begin date
 * @param reservations Pointer to the reservations database
 * @param hotelId Id of the hotel
 * @param f Mode of the outputs
 * @note If the dates are the same, the reservations must be sorted by their id
*/
void query4(Reservations *,const char *,bool);

//listar voos com origem num dado aeroporto, entre 2 datas, ordenados por data partida estimada (antiga -> recente) (se houver 2, usar id)
/**
 * @brief List flight that depart from an airport, between 2 dates, sorted by the schedule departure date
 * @param flights Pointer to the flights database
 * @param beginLimit Pointer to the date that limits the begin of the time interval
 * @param endLimit Pointer to the date that limits the end of the time interval
 * @param airport Name of the airport
 * @param f Mode of the outputs
*/
void query5(const Flights *,Time *,Time *,const char *,bool);

//listar top N aeroportos com mais passageiros, para um dado ano. Contabilizar voos com data estimada de partida nesse ano. (se 2, usar nome)
void query6();

//listar top N aeroportos com maior mediana de atrasos. Valor atraso em segundos. (se 2, usar nome)
void query7(Flights *,char *,bool);

//Apresentar receita total,de um hotel entre 2 datas, apartir do identificador. (usar preco/1noite * num_noites)
/**
 * @brief Present the total revenue from an hotel between 2 dates, from the hotel id
 * @param reservations Pointer to the reservations database
 * @param hotelId Id of the hotel
 * @param beginLimit Pointer to the date that limits the begin of the time interval
 * @param endLimit Pointer to the date that limits the end of the time interval
 * @param f Mode of the outputs
*/
void query8(Reservations *,const char *,Time *,Time *,bool);

//listar todos os users cujo nome começa com o prefixo do argumento, ordenados por nome (crescente) (se 2, usar id)
void query9();

//Apresentar metricas gerais:
/*  num_novos_users; 
    num_voos (de acordo com o campo schedule_departure_date)
    num_passageiros;
    num_passageiros_unicos;
    num_reservas (de acordo com o begin_date)*/
void query10();

#endif