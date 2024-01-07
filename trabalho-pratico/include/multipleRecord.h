#ifndef MULTIPLERECORD_H
#define MULTIPLERECORD_H

/**
 * @brief Structure that stores multiple entries for one name
*/
typedef struct mRecord MultipleRecord;

/**
 * @brief Allocates memory and initializes a MultipleRecord structure
 * @param num Number of possible slots of array to be stored
 * @return Pointer to the allocated and initialized structure
*/
MultipleRecord * createMRecord(int);

/**
 * @brief Sets the value on the element
 * @param MRecord Pointer to the MultipleRecord structure
 * @param arrayPosition Position of the array wanted
 * @param elementPosition Position of the element wanted
 * @param element Value to be put on the position 
*/
void setMRecordListElement(MultipleRecord *,int,int,int);

/**
 * @brief Gets the value on the element
 * @param MRecord Pointer to the structure MultipleRecord
 * @param arrayPosition Position of the array wanted
 * @param elementPosition Position of the element wanted
 * @return The value stored on the position 
*/
int getMRecordListElement(MultipleRecord *,int,int);

/**
 * @brief Sets an array as the element on an array of arrays
 * @param MRecord Pointer to the MultipleRecord structure 
 * @param position Position of the array wanted
 * @param element Array to be set as the new element of the array 
 * @param size Size of the new array
*/
void setMRecordList(MultipleRecord *,int ,int *,int);

/**
 * @brief Gets a copy of the array stored in the specified position
 * @param MRecord Pointer to the structure MultipleRecord
 * @param arrayPosition Position of the array wanted
*/
int * getMRecordList(MultipleRecord *,int);

/**
 * @brief Sets a pointer on the array
 * @param MRecord Pointer to the MultipleRecord structure
 * @param position Position on the array
 * @param element Pointer the is going to be stored
*/
void setMRecordNamesElement(MultipleRecord *,int,char *);

/**
 * @brief Gets a pointer on the array
 * @param MRecord Pointer to the MultipleRecord structure
 * @param position Position on the array
 * @return Pointer that was stored in the position
*/
char * getMRecordNamesElement(MultipleRecord*,int);

/**
 * @brief Increments the size of the wanted list
 * @param MRecord Pointer to the MultipleRecord structure
 * @param position Position of the array we want to increment
 * the size
*/
void incMRecordListSize(MultipleRecord *,int);

/**
 * @brief Decrements the size of the wanted list
 * @param MRecord Pointer to the MultipleRecord structure
 * @param position Position of the array we want to increment
 * the size
*/
void decMRecordListSize(MultipleRecord *,int);

/**
 * @brief Gets the size of the wanted list
 * @param MRecord Pointer to the MultipleRecord structure
 * @param position Position of the array we want to increment
 * the size
 * @return The size of the selected array
*/
int getMRecordListSize(MultipleRecord *,int);

/**
 * @brief Increments the number of arrays of elements
 * @param MRecord Pointer to the MultipleRecord structure
*/
void incMRecordSize(MultipleRecord *);

/**
 * @brief Decrements the number of arrays of elements
 * @param MRecord Pointer to the MultipleRecord structure
*/
void decMRecordSize(MultipleRecord *);

/**
 * @brief Gets the number of arrays of elements
 * @param MRecord Pointer to the MultipleRecord structure
 * @return The number of arrays stored
*/
int getMRecordSize(MultipleRecord *);

/**
 * @brief Frees the MultipleRecord structure
 * @param MRecord Pointer to the MultipleRecord structure
*/
void destroyMRecord(MultipleRecord **);


#endif