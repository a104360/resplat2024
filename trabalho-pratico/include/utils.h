#ifndef UTILS_H
#define UTILS_H


typedef struct integers Integers;

/**
 * @brief Allocates memory and initializes a Integers structure
 * @param num Number of possible slots of array to be stored
 * @return Pointer to the allocated and initialized structure
*/
Integers * createIntegers(int);

/**
 * @brief Sets the value on the element
 * @param integers Pointer to the Integers structure
 * @param arrayPosition Position of the array wanted
 * @param elementPosition Position of the element wanted
 * @param element Value to be put on the position 
*/
void setIntListElement(Integers *,int,int,int);

/**
 * @brief Gets the value on the element
 * @param integers Pointer to the structure Integers
 * @param arrayPosition Position of the array wanted
 * @param elementPosition Position of the element wanted
 * @return The value stored on the position 
*/
int getIntListElement(Integers *,int,int);

/**
 * @brief Sets an array as the element on an array of arrays
 * @param integers Pointer to the Integers structure 
 * @param position Position of the array wanted
 * @param element Array to be set as the new element of the array 
*/
void setIntList(Integers *,int ,int *);

/**
 * @brief Gets a copy of the array stored in the specified position
 * @param integers Pointer to the structure Integers
 * @param arrayPosition Position of the array wanted
*/
int * getIntList(Integers *,int);

/**
 * @brief Sets a pointer on the array
 * @param integers Pointer to the Integers structure
 * @param position Position on the array
 * @param element Pointer the is going to be stored
*/
void setIntNamesElement(Integers *,int,void *);

/**
 * @brief Gets a pointer on the array
 * @param integers Pointer to the Integers structure
 * @param position Position on the array
 * @return Pointer that was stored in the position
*/
void * getIntNamesElement(Integers*,int);

/**
 * @brief Increments the size of the wanted list
 * @param integers Pointer to the Integers structure
 * @param position Position of the array we want to increment
 * the size
*/
void incIntListSize(Integers *,int);

/**
 * @brief Decrements the size of the wanted list
 * @param integers Pointer to the Integers structure
 * @param position Position of the array we want to increment
 * the size
*/
void decIntListSize(Integers *,int);

/**
 * @brief Gets the size of the wanted list
 * @param integers Pointer to the Integers structure
 * @param position Position of the array we want to increment
 * the size
 * @return The size of the selected array
*/
int getIntListSize(Integers *,int);

/**
 * @brief Increments the number of arrays of elements
 * @param integers Pointer to the Integers structure
*/
void incIntSize(Integers *);

/**
 * @brief Decrements the number of arrays of elements
 * @param integers Pointer to the Integers structure
*/
void decIntSize(Integers *);

/**
 * @brief Gets the number of arrays of elements
 * @param integers Pointer to the Integers structure
 * @return The number of arrays stored
*/
int getIntSize(Integers *);

/**
 * @brief Frees the Integers structure
 * @param integers Pointer to the Integers structure
*/
void destroyIntegers(Integers *);




/**
 * @brief Year of the date considered as the present day
*/
#define PYEAR 2023
/**
 * @brief Month of the date considered as the present day
*/
#define PMON 10
/**
 * @brief Day of the date considered as the present day
*/
#define PDAY 1


/**
 * @brief Struct to store dates
 * @note Years do not have an offset - What you see, what you get
 * @note Months from 1 to 12
 * @note Month days all from 1 to 31
*/
typedef struct time Time;


/**
 * @brief Gets the year of the date
 * @param date
*/
int getYear(Time *);

/**
 * @brief Gets the month of the date
 * @param date
*/
int getMon(Time *);

/**
 * @brief Gets the month day of the date
 * @param date
*/
int getMday(Time *);

/**
 * @brief Gets the hours of the date
 * @param date
*/
int getHour(Time *);

/**
 * @brief Gets the minutes of the date
 * @param date
*/
int getMin(Time *);

/**
 * @brief Gets the seconds of the date
 * @param date
*/
int getSec(Time *);

/**
 * @brief Initializes all fields to 0
 * @param date Pointer to the date
*/
void initTime(Time *);

/**
 * @brief Frees the Time pointer
 * @param date
*/
void destroyTime(Time *);

/**
 * @brief Allocates and initializes the values to 0
 * @return Pointer to the date
*/
Time * createTime();


/**
 * @brief Setter function the the time struct
 * @param year
 * @param month
 * @param day 
 * @param hour
 * @param minute
 * @param second
*/
void setTime(Time *,int,int,int,int,int,int);


/**
 * @brief Copies Time from the second argument to the first
 * @note Both must be allocated
*/
void copyTime(Time *,Time *);


/**
 * @brief Compares dates to determine if the first parameter comes before the second one
 * @param date1 More ancient date
 * @param date2 Mode recent date
 * @return 1 / 0 / 10
 * @note 1 - True
 * @note 0 - False
 * @note 10 - Dates are equal
*/
int compareTimes(Time *,Time*);

/**
 * @brief Calculates the difference of days, only within same months
 * @param beginDate Date that comes first
 * @param endDate Date that comes later
 * @return How many from one date to another
*/
int numberOfDays(Time *,Time *);

/**
 * @brief Converts the time to formated string
 * @param time Pointer to a date
 * @return Formated string pf the date
 * @note "yy/mm/dd 00:00:00"
*/
char * timeToString(Time *);





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


#endif