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

/**
 * @brief Presents the average rating of an hotel, by its id
 * @param reservations Pointer to the reservations database
 * @param hotelId Id of the hotel
 * @param f Mode of the outputs
*/
void query3(Reservations *,const char *,bool);

/**
 * @brief List reservations of an hotel, sorted by begin date
 * @param reservations Pointer to the reservations database
 * @param hotelId Id of the hotel
 * @param f Mode of the outputs
 * @note If the dates are the same, the reservations must be sorted by their id
*/
void query4(Reservations *,const char *,bool);

/**
 * @brief List flight that depart from an airport, between 2 dates, sorted by the schedule departure date
 * @param flights Pointer to the flights database
 * @param beginLimit Pointer to the date that limits the begin of the time interval
 * @param endLimit Pointer to the date that limits the end of the time interval
 * @param airport Name of the airport
 * @param f Mode of the outputs
*/
void query5(const Flights *,Time *,Time *,const char *,bool);

/**
 * @brief Presents the top N airports with the most amount of passengers, in a year
 * @param flights Pointer to the flights database
 * @param passengers Pointer to the passengers database
 * @param year Year to which the flights take place
 * @param n Max number of airports to display
 * @param f Mode of the outputs
 * @note Both schedule dates are considered 
*/
void query6(const Flights *,const Passengers *,const char *, const char *,bool);

/**
 * @brief Presents the top N airports with the most median of flight delays
 * @param flights Pointer to the flights database
 * @param n Max number of airports to display
 * @param f Mode of the outputs
 * @note It outputs the values in seconds
*/
void query7(Flights *,char *,bool);

/**
 * @brief Present the total revenue from an hotel between 2 dates, from the hotel id
 * @param reservations Pointer to the reservations database
 * @param hotelId Id of the hotel
 * @param beginLimit Pointer to the date that limits the begin of the time interval
 * @param endLimit Pointer to the date that limits the end of the time interval
 * @param f Mode of the outputs
*/
void query8(Reservations *,const char *,Time *,Time *,bool);

/**
 * @brief Presents all the users whose names begin with the string provided,
 * sorted by name, or id, if the names are the same, on ascending order
 * @param users Pointer to the users database
 * @param prefix String with the prefix to search the users
 * @param f Mode of the outputs
*/
void query9(Users *, char *, bool);

//Apresentar metricas gerais:
/*  num_novos_users; 
    num_voos (de acordo com o campo schedule_departure_date)
    num_passageiros;
    num_passageiros_unicos;
    num_reservas (de acordo com o begin_date)*/
void query10();

#endif