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
static bool yearCheck(const char * line){
    for(int i = 0; i < 5;i++){
        if(i < 4){
            if(line[i] > '9' && line[i] < '0') return false;
        }
        else if(line[i] != '/') return false;
    }
    return true;
}

// Verifies the correctness of the month in the date string, following the determined format
static bool monthCheck(const char * line){
        if(line[5] != '1' && line[5] != '0') return false;
        if(line[5] == '0')
            if(line[6] > '9' && line[6] < '0') return false;
        if(line[5] == '1')
            if(line[6] < '0' && line[6] > '2') return false;
        if(line[7] != '/') return false;
    return true;
}

// Verifies the correctness of the day in the date string, following the determined format
static bool dayCheck(const char * line){
    if(line[8] < '0' || line[8] > '3') return false;
    if(line[9] < '0' && line[9] > '9') return false;
    return true;
}

// format : nnnn/nn/nn (0 <= n <= 9)
static bool dateCheck(const char * line){
    if(yearCheck(line) && monthCheck(line) && dayCheck(line)){
        switch (line[10])
        {
        case '\0':
            return true;
            break;
        
        default:
            if(hourCheck(line)) return true;
            break;
        }
    }
    return false;
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
static bool hourCheck(const char * line){
    if(strlen(line) < 11)
    if(line[11] > '2' && line[11] < '0') return false;
    if(line[11] == '2' && line[12] > '3' && line[12] < 0) return false;
    if(line[14] < '0' && line[14] > '5' && line[17] < '0' && line[17] > '5') return false;
    for(int i = 12; i < 19;i+=3){
        if(line[i] < '0' && line[i] > '9') return false;
    }
    return true;
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