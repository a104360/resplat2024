#ifndef SORT_H
#define SORT_H


/**
 * @brief Sorts an array of pointers to or flights or reservations
 * @param a Array of pointers to be sorted
 * @param length Size of the array
 * @param type Specification of the type that is 
 * stored in the array to be sorted (flight/reservation)
*/
void mergeSort(void **,int,const char *);

#endif