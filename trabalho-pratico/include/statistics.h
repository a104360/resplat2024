#ifndef STATISTICS_H
#define STATISTICS_H

/**
 * @brief Calculates the total amount spent by on a reservation by an user
 * @param userReservations Array of pointers to reservations
 * @param max Number of reservations made
 * @return The total spent on a set of reservations
*/
double getTotalSpentByUser(void **,int);

/**
 * @brief Calculates the total amount spent on a reservation, with taxes
 * @param reservation Pointer to the reservation 
 * @param n Number for how many days the reservations was set
 * @return The total spent on a reservation, including the hotel revenue and
 * tax money
*/
double getTotalSpentOnReserv(void *,int);

/**
 * @brief Calculates the profit the hotel made with the reservation
 * @param reservation Pointer to the reservation
 * @param n Number for how many days the reservations was set
 * @return The total amount of profit the hotel made from the reservation
*/
int getHotelEarningsOfReserv(void *,int);

/**
 * @brief Calculates the average rating of an hotel, from all their 
 * reservations
 * @param reseravtions Pointer to the reservations database
 * @param id Id of the hotel
 * @return The average rating by dividing the sum of the rating values by 
 * the number of reservations that were made
*/
double averageRating(void *,const char *);

/**
 * @brief Calculates the median of an array of values
 * @param values Pointer the first one of the values
 * @param n Number of values
*/
int delayMedianAirport(int *,int);

#endif