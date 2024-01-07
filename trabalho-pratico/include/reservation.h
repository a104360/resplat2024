#ifndef RESERVATION_H
#define RESERVATION_H
#include "../include/time.h"
#include "../include/database.h"
#include <stdbool.h>
/**
 * @brief Represents a type alias for the Database named Reservations.
 */
typedef Database Reservations;

/**
 * @brief Represents a structure for storing reservation information.
 */
typedef struct reservation Reservation;

/**
 * @brief Allocates memory for a Reservation structure and returns a pointer to it.
 * @return Pointer to the created Reservation.
 */
Reservation *createReservation();

/**
 * @brief Initializes a Reservation structure.
 * @param reservation Pointer to the Reservation structure to be initialized.
 */
void initReservation(Reservation *);

/**
 * @brief Correctly frees the memory allocated for a Reservation structure.
 * @param reservation Pointer to the Reservation structure to be destroyed.
 */
void destroyReservation(Reservation *);

/**
 * @brief Sets the ID in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param id Pointer to a string ID.
 */
void setReservId(Reservation *, const char *);

/**
 * @brief Gets the ID stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Pointer to the ID string.
 */
char *getReservId(Reservation *);

/**
 * @brief Sets the user ID in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param userId Pointer to a string representing the user ID.
 */
void setReservUserId(Reservation *, const char *);

/**
 * @brief Gets the user ID stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Pointer to the user ID string.
 */
char *getReservUserId(Reservation *);

/**
 * @brief Sets the hotel ID in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param hotelId Pointer to a string representing the hotel ID.
 */
void setReservHotelId(Reservation *, const char *);

/**
 * @brief Gets the hotel ID stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Pointer to the hotel ID string.
 */
char *getReservHotelId(Reservation *);

/**
 * @brief Sets the hotel name in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param hotelName Pointer to a string representing the hotel name.
 */
void setReservHotelName(Reservation *, const char *);

/**
 * @brief Gets the hotel name stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Pointer to the hotel name string.
 */
char *getReservHotelName(Reservation *);

/**
 * @brief Sets the hotel stars information in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param hotelStars Total number of hotel stars.
 */
void setReservHotelStars(Reservation *, const unsigned int);

/**
 * @brief Gets the hotel stars information stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Total number of hotel stars.
 */
unsigned int getReservHotelStars(Reservation *);

/**
 * @brief Sets the city tax information in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param cityTax City tax value.
 */
void setReservCityTax(Reservation *, const int);

/**
 * @brief Gets the city tax information stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return City tax value.
 */
int getReservCityTax(Reservation *);

/**
 * @brief Sets the hotel address information in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param hotelAddress Pointer to a string representing the hotel address.
 */
void setReservHotelAddress(Reservation *, const char *);

/**
 * @brief Gets the hotel address information stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Pointer to the hotel address string.
 */
char *getReservHotelAddress(Reservation *);

/**
 * @brief Sets the beginning date in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param beginDate Pointer to a Time struct representing the beginning date.
 */
void setReservBeginDate(Reservation *, Time *);

/**
 * @brief Gets the pointer to the beginning date stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Pointer to the beginning date.
 */
Time *getReservBeginDate(Reservation *);

/**
 * @brief Sets the end date in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param endDate Pointer to a Time struct representing the end date.
 */
void setReservEndDate(Reservation *, Time *);

/**
 * @brief Gets the pointer to the end date stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Pointer to the end date.
 */
Time *getReservEndDate(Reservation *);

/**
 * @brief Sets the price per night information in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param pricePerNight Price per night value.
 */
void setReservPricePerNight(Reservation *, const double);

/**
 * @brief Gets the price per night information stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Price per night value.
 */
double getReservPricePerNight(Reservation *);

/**
 * @brief Sets the breakfast information in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param hasBreakfast Boolean value indicating the presence of breakfast.
 */
void setReservBreakfast(Reservation *, const bool);

/**
 * @brief Gets the breakfast information stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Boolean value indicating the presence of breakfast.
 */
bool getReservBreakfast(Reservation *);

/**
 * @brief Sets the room details in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param roomDetails Pointer to a string representing the room details.
 */
void setReservRoomDetails(Reservation *, const char *);

/**
 * @brief Gets the room details stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Pointer to the room details string.
 */
char *getReservRoomDetails(Reservation *);

/**
 * @brief Sets the rating information in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param rating Rating value.
 */
void setReservRating(Reservation *, const unsigned int);

/**
 * @brief Gets the rating information stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Rating value.
 */
const unsigned int getReservRating(const Reservation *);

/**
 * @brief Sets the comment in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @param comment Pointer to a string representing the comment.
 */
void setReservComment(Reservation *, const char *);

/**
 * @brief Gets the comment stored in the Reservation structure.
 * @param reservation Pointer to the Reservation structure.
 * @return Pointer to the comment string.
 */
char *getReservComment(Reservation *);

/**
 * @brief Copies the contents of one Reservation structure to another.
 * @param dest Pointer to the destination Reservation structure.
 * @param src Pointer to the source Reservation structure.
 */
void copyReservation(Reservation *, Reservation *);


#endif