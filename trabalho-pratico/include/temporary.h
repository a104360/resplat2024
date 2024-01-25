#ifndef TEMPORARY_H
#define TEMPORARY_H
#include "../include/utils.h"
#include "../include/time.h"
#include "../include/flight.h"
#include "../include/reservation.h"

/**
 * @brief Struct to be used on Iterations over the databases
*/
typedef struct temporary Temporary;


/**
 * @brief Allocates memory for the temporary struct and initializes it fiels/pointer to NULL/0
 * @return Pointer to the created struct
*/
Temporary * createTemporary();

/**
 * @brief Function that frees all the struct fields or sets them to NULL
*/
void destroyTemporary(Temporary *);

/**
 * @brief Function that frees all the struct fields, when flights are stored in
 * the struct
*/
void destroyTemporaryFlight(Temporary *);

/**
 * @brief Function that frees all the struct fields, when reservations are stored in
 * the struct
*/
void destroyTemporaryReservation(Temporary *);

/**
 * @brief Function that frees all the struct fields, when strings are stored in
 * the struct
*/
void destroyTemporaryChar(Temporary *);

/**
 * @brief Sets a secondary database to be used on some iterating functions
 * @param temp Pointer to the temporary struct
 * @param database Pointer to a database
 */
void setTempDatabase(Temporary *, void *);

/**
 * @brief Gets the pointer to a database stored in the temporary struct
 * @param temp Pointer to the temporary struct
 * @return Pointer to the database
 */
void *getTempDatabase(Temporary *);

/**
 * @brief Sets the ID in the temporary struct
 * @param temp Pointer to the temporary struct
 * @param id Pointer to a string ID
 */
void setTempId(Temporary *, char *);

/**
 * @brief Gets the ID stored in the temporary struct
 * @param temp Pointer to the temporary struct
 * @return Pointer to the ID string
 */
char *getTempId(Temporary *);

/**
 * @brief Sets the list in the temporary struct
 * @param temp Pointer to the temporary struct
 * @param list Pointer to an array of void pointers
 */
void setTempList(Temporary *, void **);

/**
 * @brief Sets an element in the list stored in the temporary struct
 * @param temp Pointer to the temporary struct
 * @param element Pointer to the element to be set in the list
 * @param index Index of the element in the list
 */
void setTempListElement(Temporary *, void *, int );

/**
 * @brief Gets the list stored in the temporary struct
 * @param temp Pointer to the temporary struct
 * @return Pointer to the list
 */
void **getTempList(Temporary *);

/**
 * @brief Sets the Flight on the temporary
 * @param temp Pointer to the temporary struct
 * @param flight Flight to be inserted on trhe 
 * temporary
 * @param position Position on where the flight will be put
*/
void setTempListFlight(Temporary *,Flight *,int);

/**
 * @brief Gets the Flight from the temporary
 * @param temp Pointer to the temporary struct
 * @param position Position from where the flight will be draw
 * @return Flight on the position
*/
Flight * getTempListFlight(Temporary *,int);

/**
 * @brief Gets the all Flights from the temporary
 * @param temp Pointer to the temporary struct
 * @return Flights on the temporary
*/
Flight ** getTempListFlights(Temporary *);

/**
 * @brief Gets the name stored in the temporary 
 * on the position
 * @param temp Pointer to the struct temporary
 * @param position Position the name is on 
 * @return Name on the position
*/
char * getTempListCharElement(Temporary *,int);


/**
 * @brief Gets the names stored on an primary pointer
 * @param temp Pointer to the temporary struct
 * @return Names of the temporary
*/
char ** getTempListChars(Temporary *);

/**
 * @brief Sets a name to a specific position
 * @param temp Pointer to the temporary struct
 * @param name Name to be stored in the primary group of names
 * @param position Position in which the name will be stored
*/
void setTempListElementChar(Temporary *,char *,int);


/**
 * @brief Sets a reservations to a specific position
 * @param temp Pointer to the temporary struct
 * @param reservations reservations to be stored in the primary 
 * group of reservations
 * @param position Position in which the reservations will be stored
*/
void setTempListElementReservation(Temporary *,Reservation *,int);

/**
 * @brief Gets all reservations on the temporary
 * @param temp Pointer to the temporary struct
 * @return Reservations in the temporary struct
*/
Reservation ** getTempListReservations(Temporary *);

/**
 * @brief Gets the pointer stored in a specific position
 * @param temp Pointer to ht temporary struct
 * @param position Position from which the pointer shall be retrieved
*/
const void * getTempListElement(Temporary *,int);


/**
 * @brief Gets all the pointers stored in the struct
 * @param temp Pointer to the temporary struct
*/
void ** getTempList(Temporary *);


/**
 * @brief Sets a numerical value in the temporary struct
 * @param temp Pointer to the temporary struct
 * @param num Numerical value to be set
 */
void setTempNum(Temporary *, int );

/**
 * @brief Increments the numerical value stored in the temporary struct
 * @param temp Pointer to the temporary struct
 */
void incTempNum(Temporary *);

/**
 * @brief Gets the numerical value stored in the temporary struct
 * @param temp Pointer to the temporary struct
 * @return Numerical value
 */
int getTempNum(Temporary *);

/**
 * @brief Sets a sum value in the temporary struct
 * @param temp Pointer to the temporary struct
 * @param sum Sum value to be set
 */
void setTempSum(Temporary *, int );

/**
 * @brief Increases the sum value stored in the temporary struct
 * @param temp Pointer to the temporary struct
 * @param value Value to be added to the current sum
 */
void increaseTempSum(Temporary *, int );

/**
 * @brief Gets the sum value stored in the temporary struct
 * @param temp Pointer to the temporary struct
 * @return Sum value
 */
int getTempSum(Temporary *);

/**
 * @brief Sets the beginning time in the temporary struct
 * @param temp Pointer to the temporary struct
 * @param begin Pointer to a Time struct representing the beginning time
 */
void setTempBegin(Temporary *, Time *);

/**
 * @brief Gets the pointer to the beginning time stored in the temporary struct
 * @param temp Pointer to the temporary struct
 * @return Pointer to the beginning time
 */
Time *getTempBegin(Temporary *);

/**
 * @brief Sets the end time in the temporary struct
 * @param temp Pointer to the temporary struct
 * @param end Pointer to a Time struct representing the end time
 */
void setTempEnd(Temporary *, Time *);

/**
 * @brief Gets the pointer to the end time stored in the temporary struct
 * @param temp Pointer to the temporary struct
 * @return Pointer to the end time
 */
Time *getTempEnd(Temporary *);

/**
 * @brief Sets a maximum value in the temporary struct
 * @param temp Pointer to the temporary struct
 * @param max Maximum value to be set
 */
void setTempMax(Temporary *, int);

/**
 * @brief Gets the maximum value stored in the temporary struct
 * @param temp Pointer to the temporary struct
 * @return Maximum value
 */
int getTempMax(Temporary *);


/**
 * @brief Sets a pointer to the struct
 * @param temp Pointer to the temporary struct
 * @param element Pointer to what will be stored in the struct
 * @note Only use this function when no dates are needed
*/
void setTempAux(Temporary *,char **);

/**
 * @brief Sets an element on an position
 * @param temp Pointer to the temporary struct
 * @param element Pointer to the element to be inserted on the element
 * @param position Position for the element to be inserted in 
*/
void setTempAuxElement(Temporary *, void *, int);


/**
 * @brief Sets a name to the position requested
 * @param temp Pointer to the temporary struct
 * @param name Pointer to the name to be inserted on the element
 * @param position Position for the element to be inserted in 
*/
void setTempAuxElementChar(Temporary *,char *,int);

/**
 * @brief Gets the pointer stored on the struct
 * @param temp Pointer to the temporary struct
 * @return Pointer stored on the struct
*/
void * getTempAux(Temporary *);


/**
 * @brief Gets the names stored on an secondary pointer
 * @param temp Pointer to the temporary struct
 * @note This function must not be used when a begin date is being used
*/
char ** getTempAuxChar(Temporary *);

#endif