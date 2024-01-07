#ifndef TIME_H
#define TIME_H


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



#endif