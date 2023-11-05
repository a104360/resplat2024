#include "../include/parser.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/*
*
* In each function, the string passed is in the format to be parsed,
* not the whole line
*
*/

// Verifies the correctness of the year in the date string, following the determined format
// tm.year = years after 1900
// Example : the year 2023 would appear on tm.year as 123
static int yearCheck(const char * line){
    for(int i = 0; i < 5;i++){
        if(i < 4){
            if(line[i] > '9' && line[i] < '0') return false;
        }
        else if(line[i] != '/') return false;
    }
    char * aux = malloc(sizeof(char) * 4);
    strncpy(aux,line,4);
    int n = atoi(aux);
    free(aux);
    return n - 1900;
}

// Verifies the correctness of the month in the date string, following the determined format
// 0 <= tm.tm_mon <= 11
static int monthCheck(const char * line){
    if(line[5] != '1' && line[5] != '0') return false;
    if(line[5] == '0')
        if(line[6] > '9' && line[6] < '0') return false;
    if(line[5] == '1')
        if(line[6] < '0' && line[6] > '2') return false;
    if(line[7] != '/') return false;
    char * aux = malloc(sizeof(char)*2);
    aux[0] = line[5];
    aux[1] = line[6];
    int n = atoi(aux);
    free(aux);
    return n;
}

// Verifies the correctness of the day in the date string, following the determined format
// 0 -> false
// otherwise -> 1 <= tm.tm_mday <= 31 (true)
static int dayCheck(const char * line){
    if(line[8] < '0' || line[8] > '3') return false;
    if(line[9] < '0' && line[9] > '9') return false;
    char * aux = malloc(sizeof(char) * 2);
    aux[0] = line[8];
    aux[1] = line[9]; 
    int n = atoi(aux);
    return n;
}

// format : nnnn/nn/nn (0 <= n <= 9)
static struct tm * dateCheck(const char * line){
    struct tm * date = malloc(sizeof(struct tm));
    if(!date) return NULL;
    date->tm_year = yearCheck(line);
    date->tm_mon = monthCheck(line) - 1;
    date->tm_mday = dayCheck(line);
    if(date->tm_year == 0 || date->tm_mon == -1 || date->tm_mday == 0){
        free(date);
        return NULL;
    }
    switch (line[10])
    {
    case '\0':
        return date;
        break;
    
    default:
        date->tm_hour = hourCheck(line);
        date->tm_min = minuteCheck(line);
        date->tm_sec = secondsCheck(line);
        return date;
        break;
    }

    return NULL;
}

// starting dates cannot be after finishing dates
static bool datesCheck(const char * start, const char * end){
    if(!dateCheck(start) || !dateCheck(end)) return false;
    for(int i = 0;i < 10;i++){
        if(start[i] == '/' || start[i] == ' ') continue;
        if(start[i] > end[i]) return false;
    }
    return true;
}

// format : nnnn/nn/nn nn:nn:nn | dateCheck && [0,23]:
static int hourCheck(const char * line){
    if(line[11] == '2'){
        if(line[12] < '0' && line[12] > '3') return -1;
        else{
            char * aux = malloc(sizeof(char) * 2);
            aux[0] = '2';
            aux[1] = line[12];
            int n = atoi(aux);
            free(aux);
            return n;
        }
    }
    if(line[11] < '0' && line[11] > '1' && line[12] < '0' && line[12] > '9') return -1;
    else {
        char * aux = malloc(sizeof(char) * 2);
        aux[0] = line[11];
        aux[2] = line[12];
        int n = atoi(aux);
        free(aux);
        return n;
    }
    return -2;
}

// 0 <= min <= 59
static int minuteCheck(const char * line){
    if(line[14] < '0' && line[14] > '5' && line[15] < '0' && line[15] > '9') return -1;
    else {
        char * aux = malloc(sizeof(char) * 2);
        aux[0] = line[14];
        aux[1] = line[15];
        int n = atoi(aux);
        free(aux);
        return n;
    }
    return -2;
}

// 0 <= sec <= 59
static int secondsCheck(const char * line){
    if(line[17] < '0' && line[17] > '5' && line[18] < '0' && line[18] > '9') return -1;
    else {
        char * aux = malloc(sizeof(char) * 2);
        aux[0] = line[17];
        aux[1] = line[18];
        int n = atoi(aux);
        free(aux);
        return n;
    }
    return -2;
}

// starting hours cannot be after finishing hours
static bool hoursCheck(const char * departure, const char * arrival){
    if(!hourCheck(departure) || !hourCheck(arrival)) return false;
    for(int i = 11;i < 19;i++){
        if(departure[i] == ':' || arrival[i] == ':') continue;
        if(departure[i] > arrival[i]) return false;
    }
    return true;
}

// format : <username>@<domain>.<TLD> | username.length >= 1 , domain.length >= 2 , TDL.length >= 2
static bool emailCheck(const char * line){
    if(line[0] == '@') return false;
    int i = 1, len = strlen(line);
    // Username
    for(;line[i] != '@' && i < len;i++);
    if(i >= len) return false;
    // Domain
    if(line[i+1] == '.') return false;
    int domain = 0;
    for(i += 1; line[i] != '.' && i < len;domain++,i++);
    if(i >= len && domain < 2) return false;
    // TDL
    int tdl = 0;
    for(i += 1;i < len;tdl++,i++);
    if(tdl < 2) return false;
    return true;
}

// format : LL (L is a letter)
static bool countryCheck(const char * line){
    if(!line) return false;
    if(line[2] == '\0') return false;
    if(line[3] == '\0') return true;

}

// active vs inactive (all varitations)
static bool accStatusCheck(const char * line){
    toUpper(line);
    if(!strcmp(line,"ACTIVE") || !strcmp(line,"INACTIVE")) return true;
    return false;
}

// total_seats must not be less than the number of passangers
static bool seatsCheck(const char * sold, const char * plain){
    int real = atoi(plain), virtual = atoi(sold);
    if(virtual > sold) return false;
    return true;
}

// length == 3 && all variations
static bool airportCheck(const char * departure,const char * arrival);

// int stars : 1 <= starts <= 5
static bool hotelStarsCheck(const char * line);

// int tax : 0 <= tax
static bool taxCheck(const char * line);

// int price : 0 <= price
static bool pricePNightCheck(const char * line);

// bool breakfast : if(false){"f","false",0,""} else {"t","true","1"}
static bool breakfastCheck(const char * line);

// int rating : 1 <= rating <= 5
static bool reviewCheck(const char * line);

// Check the length of some camps of the users, reservations and flights
static bool lengthCheck(void ** line);

static bool userCheck(const char * line);

static bool reservationCheck(const char * line);

static bool flightCheck(const char * line);

static bool passangerCheck(const char * line);


static User * userAdd(const char * line);

static Reservation * reservationAdd(const char * line);

static Flight * fligthAdd(const char * line);

static Passanger * passangerAdd(const char * line);