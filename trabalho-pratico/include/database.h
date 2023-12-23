#ifndef DATABASE_H
#define DATABASE_H
#include <glib.h>
#include "../include/utils.h"

/**
 * @brief This must be used to make a database where the elements have a designated key/id
*/
typedef struct database Database;

/**
 * @brief Allocates memory for the database and sets the argument function as the element free function;
 * @param func Pointer to the function that will be used as a element free function
 * @return Pointer to the created database
*/
Database * createDatabase(void (*)());

/**
 * @brief Inserts an element on the database
 * @param dBase Pointer to the desired Database to insert the element on
 * @param id Key to store the element
 * @param element Value to be stored with the Key as a reference
*/
void insertOnDatabase(void *,const char *,void *);

/**
 * @brief Gets a pointer, not a copy, of the element stored in the database
 * @param dBase Pointer to the desired database
 * @param id Id of the Value wanted
 * @return Pointer stored in the database (NOT A COPY!)
*/
void * lookupElement(const void *,const char *);

/**
 * @brief Gets the amount of elements present on the database
 * @param database Pointer to the database
 * @return The number of elements of the database
*/
int getDatabaseSize(const void *);


/**
 * @brief Applies a function to every elements of the database 
 * @param database Pointer to the database
 * @param function Function to apply to every function
 * @param data Pointer to the auxiliar struct
*/
void applyForEach(void *,void (*func)(gpointer,gpointer,gpointer),void *);

/**
 * @brief Correctly frees the database
 * @param database Pointer to the database to be erased
*/
void destroyDatabase(void *);





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
 * @brief Sets a secondary database to be used on some iterating functions
 * @param temp Pointer to the temporary struct,
 * @param database Pointer to a database
*/
void setTempDatabase(Temporary *,void *);

/**
 * @brief Gets the pointer, to a the database, stored in the temporary struct
 * @param temp Pointer to the temporary struct 
 * @return Pointer to the database 
*/
void * getTempDatabase(Temporary *);

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



#endif