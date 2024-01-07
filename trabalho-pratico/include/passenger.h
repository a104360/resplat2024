#ifndef PASSENGER_H
#define PASSENGER_H


/**
 * @brief Struct that defines the passenger informations
*/
typedef struct passenger Passenger;


/**
 * @brief Allocates a memory for the all the passenger values and for the passenger itself
 * @return Pointer to the allocated passenger 
*/
Passenger * createPassenger();

/**
 * @brief Initializes all the values of the passenger
 * @param passenger Pointer to a passenger 
*/
void initPassenger(Passenger *);


/**
 * @brief Frees the values and the passenger itself
 * @param passenger Pointer to a passenger
*/
void destroyPassenger(Passenger *);



/**
 * @brief Sets the passenger flight id
 * @param passenger Pointer to a passenger
 * @param flightId Id of the flight
*/
void setPassengerFlightId(Passenger *, const char *);

/**
 * @brief Gets the passenger flight id
 * @param passenger Pointer to a passenger
 * @return Id of the flight the passenger was in
*/
char *getPassengerFlightId(Passenger *);

/**
 * @brief Sets the passenger user id
 * @param passenger Pointer to the passenger
 * @param userId Id of the user id
*/
void setPassengerUserId(Passenger *, const char *);

/**
 * @brief Gets the passenger user id
 * @param passenger Pointer to the passenger
 * @return Id of the user that was the passenger on the flight
*/
char *getPassengerUserId(Passenger *);


/**
 * @brief Transfers every fields from the one to another
 * @param dest Pointer to the passenger that will receive the values
 * @param src Pointer to the passenger that gives the values to the dest
 * @note Both must be already allocated
*/
void copyPassenger(Passenger *,Passenger *);

#endif