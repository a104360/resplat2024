#ifndef FLIGHT_H
#define FLIGHT_H
#include "../include/time.h" 
#include "../include/database.h"

/**
 * @brief The type Flights is a database
*/
typedef Database Flights;

/**
 * @brief The type Flight is a struct flight
*/
typedef struct flight Flight;

/**
 * @brief Allocates memory for the fields of a struct flight
*/
Flight * createFlight();

/**
 * @brief Initializes all its fields to a NULL or 0 values
 * @param flight Pointer to the flight
*/
void initFlight(Flight *);

/**
 * @brief Frees the fields of the struct, the struct itself and nullifies all the pointers
 * @param flight Pointer to the flight
*/
void destroyFlight(Flight *);


/**
 * @brief Sets the ID in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param id Pointer to a string ID.
 */
void setFlightId(Flight *, const char *);

/**
 * @brief Gets the ID stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Pointer to the ID string.
 */
char *getFlightId(Flight *);

/**
 * @brief Sets the airline information in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param airline Pointer to a string representing the airline.
 */
void setFlightAirline(Flight *, const char *);

/**
 * @brief Gets the airline information stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Pointer to the airline string.
 */
char *getFlightAirline(Flight *);

/**
 * @brief Sets the plane model in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param model Pointer to a string representing the plane model.
 */
void setFlightPlaneModel(Flight *, const char *);

/**
 * @brief Gets the plane model stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Pointer to the plane model string.
 */
char *getFlightPlaneModel(Flight *);

/**
 * @brief Sets the total seats information in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param totalSeats Total number of seats.
 */
void setFlightTotalSeats(Flight *, const unsigned int);

/**
 * @brief Gets the total seats information stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Total number of seats.
 */
unsigned int getFlightTotalSeats(Flight *);

/**
 * @brief Sets the origin information in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param origin Pointer to a string representing the origin.
 */
void setFlightOrigin(Flight *, const char *);

/**
 * @brief Gets the origin information stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Pointer to the origin string.
 */
char *getFlightOrigin(Flight *);

/**
 * @brief Sets the destination information in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param destination Pointer to a string representing the destination.
 */
void setFlightDestination(Flight *, const char *);

/**
 * @brief Gets the destination information stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Pointer to the destination string.
 */
char *getFlightDestination(Flight *);

/**
 * @brief Sets the scheduled departure date in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param sDepartureDate Pointer to a Time struct representing the scheduled departure date.
 */
void setFlightSDepartureDate(Flight *, Time *);

/**
 * @brief Gets the pointer to the scheduled departure date stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Pointer to the scheduled departure date.
 */
Time *getFlightSDepartureDate(Flight *);

/**
 * @brief Sets the scheduled arrival date in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param sArrivalDate Pointer to a Time struct representing the scheduled arrival date.
 */
void setFlightSArrivalDate(Flight *, Time *);

/**
 * @brief Gets the pointer to the scheduled arrival date stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Pointer to the scheduled arrival date.
 */
Time *getFlightSArrivalDate(Flight *);

/**
 * @brief Sets the return departure date in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param rDepartureDate Pointer to a Time struct representing the return departure date.
 */
void setFlightRDepartureDate(Flight *, Time *);

/**
 * @brief Gets the pointer to the return departure date stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Pointer to the return departure date.
 */
Time *getFlightRDepartureDate(Flight *);

/**
 * @brief Sets the return arrival date in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param rArrivalDate Pointer to a Time struct representing the return arrival date.
 */
void setFlightRArrivalDate(Flight *, Time *);

/**
 * @brief Gets the pointer to the return arrival date stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Pointer to the return arrival date.
 */
Time *getFlightRArrivalDate(Flight *);

/**
 * @brief Sets the pilot information in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param pilot Pointer to a string representing the pilot.
 */
void setFlightPilot(Flight *, const char *);

/**
 * @brief Gets the pilot information stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Pointer to the pilot string.
 */
char *getFlightPilot(Flight *);

/**
 * @brief Sets the copilot information in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param copilot Pointer to a string representing the copilot.
 */
void setFlightCopilot(Flight *, const char *);

/**
 * @brief Gets the copilot information stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Pointer to the copilot string.
 */
char *getFlightCopilot(Flight *);

/**
 * @brief Sets the notes in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @param notes Pointer to a string representing the notes.
 */
void setFlightNotes(Flight *, const char *);

/**
 * @brief Gets the notes stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Pointer to the notes string.
 */
char *getFlightNotes(Flight *);

/**
 * @brief Gets the delay value stored in the Flight structure.
 * @param flight Pointer to the Flight structure.
 * @return Delay value.
 */
int getFlightDelay(Flight *);

/**
 * @brief Copies the contents of one Flight structure to another.
 * @param dest Pointer to the destination Flight structure.
 * @param src Pointer to the source Flight structure.
 */
void copyFlight(Flight *, Flight *);


#endif