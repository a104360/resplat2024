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

#endif