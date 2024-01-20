#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Better version of free function (only frees if it exists and nullifies it)
 * @param ptr Pointer to something that was allocated
*/
void ffree(void *);



/**
 * @brief Cicle to initialize any array of pointer to NULL
 * @note If the pointer provided is NULL, the function allocates memory for it
*/
void initArrays(void ***,int);

int extendArray(void ***,int,int);
#endif