#ifndef SINGULARRECORD_H
#define SINGULARRECORD_H

/**
 * @brief Structure that stores a singular value for each name stored on 
 * the struct as well
*/
typedef struct sRecord SingularRecord;

/**
 * @brief Allocates memory for a sRecord struct
 * @param num Number of different names to be stored
 * @return Pointer to the struct created
*/
SingularRecord * createSRecord(int);

/**
 * @brief Sets a name for the selected position
 * @param sRecord Pointer to the structure 
 * @param position Position of the array to store
 * @param name Pointer to the name to be stored
*/
void setSRecordName(SingularRecord *,int,char *);

/**
 * @brief Gets the name on the position selected
 * @param sRecord Pointer to the structure 
 * @param position Position of the array to store
 * @return Pointer to a copy of the name on the position selected
*/
char *getSRecordName(SingularRecord *,int);

/**
 * @brief Gets the position on the array in which a name is on
 * @param sRecord Pointer to the struct
 * @param name Name selected
 * @note Returns -1 if the name does not exist
*/
int getSRecordNamePosition(SingularRecord *,const char *);

/**
 * @brief Increments the value that is stored on the name, adding the
 * the name and values to the structure
 * @param sRecord Pointer to the structure
 * @param name Name to be searched/inserted on the structure
*/
void incSRecordNameElement(SingularRecord *,const char *);

/**
 * @brief Get a copy of all the names on the struct
 * @param sRecord Pointer to the structure
 * @return Pointer to an copy of all names on the structure
*/
char ** getSRecordNames(SingularRecord *);

/**
 * @brief Sets a value to the selected position
 * @param sRecord Pointer to the structure
 * @param position Position to where the value shall be inserted
 * @param num Value to be inserted 
 * @note The positions of the values will be referent to the name
 * on the same position
*/
void setSRecordListElement(SingularRecord *,int,int);


/**
 * @brief Increments the value of one element of the list
 * @param sRecord Pointer to the structure
 * @param position Position on the array to be incremented
*/
void incSRecordListElement(SingularRecord *,int);


/**
 * @brief Gets a value on the selected position
 * @param sRecord Pointer to the structure
 * @param position Position to where the value shall be inserted
 * @note The value will describe something of the name on the same
 * position
*/
int getSRecordListElement(SingularRecord *,int);

/**
 * @brief Sets the structure size, or how many different names/values
 * there are
 * @param sRecord Pointer to the structure
 * @param size Number to be setted as the size of the structure
*/
void setSRecordSize(SingularRecord *,int);

/**
 * @brief Increments the size/number of diferent elements
 * @param sRecord Pointer to the structure
*/
void incSRecordSize(SingularRecord *);

/**
 * @brief Gets the structure size, or how many different names/values
 * there are
 * @param sRecord Pointer to the structure
*/
int getSRecordSize(SingularRecord *);


/**
 * @brief Frees the pointer fields of the structure and also the 
 * structure itself and nullifies the pointers
 * @param sRecord Pointer to the structure
*/
void destroySRecord(SingularRecord **);

#endif 