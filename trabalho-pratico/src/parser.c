#include "../include/parser.h"
#include "../include/dataTypes.h"
#include "../include/utils.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

/*
*
* In each function, the string passed is in the format to be parsed,
* not the whole line
*
*/



static char * idCheck(const char * line){
    CHECKLEN(line);
}

// Free necessary
static char * nameCheck(const char * line){
    CHECKLEN(line);
}

static unsigned int phoneNumberCheck(const char * line){
    if(line[0] == '\0') return NULL;
    unsigned int n = atoi(line);
    return n;
}

static bool sexCheck(const char * line){
    if(line[0] == '\0') return NULL;
    
}

// Free necessary
static char * passaportCheck(const char * line){
    CHECKLEN(line);
}

// Free necessary
static char * addressCheck(const char * line){
    CHECKLEN(line);
}

static unsigned int pay_methodCheck(const char * line){
    if(line[0] == '\0') return -1;
    char * aux = strdup(line);
    for(int i = 0;aux[i] != '\0';aux[i] = tolower(aux[i]),i++);
}


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
    return n;
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
static Time * dateCheck(const char * line){
    Time * date = (Time *) malloc(sizeof(struct time));
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
// RETURN HERE !!
static bool hoursCheck(const char * departure, const char * arrival){
    if(!hourCheck(departure) || !hourCheck(arrival)) return false;
    for(int i = 11;i < 19;i++){
        if(departure[i] == ':' || arrival[i] == ':') continue;
        if(departure[i] > arrival[i]) return false;
    }
    return true;
}

// format : <username>@<domain>.<TLD> | username.length >= 1 , domain.length >= 2 , TDL.length >= 2
static char * emailCheck(const char * line){
    if(line[0] == '@') return NULL;
    int i = 1, len = strlen(line);
    // Username
    for(;line[i] != '@' && i < len;i++);
    if(i >= len) return NULL;
    // Domain
    if(line[i+1] == '.') return NULL;
    int domain = 0;
    for(i += 1; line[i] != '.' && i < len;domain++,i++);
    if(i >= len && domain < 2) return NULL;
    // TDL
    int tdl = 0;
    for(i += 1;i < len;tdl++,i++);
    if(tdl < 2) return NULL;
    char * email = malloc(sizeof(strlen(line)));
    strcpy(email,line);
    return email;
}

// format : LL (L is a letter)
static char * countryCheck(const char * line){
    if(!line) return false;
    if(line[2] == '\0') return NULL;
    if(line[3] == '\0'){
        char * country = malloc(sizeof(char) * 2);
        strcpy(country,line);
        return country;
    }
}

// active vs inactive (all varitations)
static bool accStatusCheck(const char * line){
    char * aux = strdup(line);
    ALLVAR(aux);
    if(!strcmp(line,"active") || !strcmp(line,"inactive")) return true;
    return false;
}

// total_seats must not be less than the number of passangers
static bool seatsCheck(const char * sold, const char * plain){
    int real = atoi(plain), virtual = atoi(sold);
    if(virtual > real) return false;
    return true;
}

// length == 3 && all variations
static bool airportCheck(const char * departure,const char * arrival){
    if(strlen(departure) != 3 || strlen(arrival) != 3) return false;
    char * d = strdup(departure), * a = strdup(arrival);
    ALLVAR(d);
    ALLVAR(a);
    if(!strcmp(d,a)) return false;
    free(d);
    free(a);
    return true;
}

// int stars : 1 <= starts <= 5
static int hotelStarsCheck(const char * line){
    if(line >= '1' && line <= '5') return line - '0';
    return false;
}

// int tax : 0 <= tax
// if invalid, functions returns -1
static double taxCheck(const char * line){
    double n = atof(line);
    if(n < 0) return -1;
    return n;
}

// int price : 0 < price
// if invalid, functions returns -1
static double pricePNightCheck(const char * line){
    double n = atof(line);
    if(n <= 0) return -1;
    return n;
}

// bool breakfast : if(false){"f","false",0,""} else {"t","true","1"}
static bool breakfastCheck(const char * line){
    char * aux = strdup(line);
    ALLVAR(aux);
    if(!strcmp(aux,"TRUE") || !strcmp(aux,"T") || !strcmp(aux,"1")){ 
        free(aux);
        return true;
    }
    free(aux);
    return false;
}

// int rating : 1 <= rating <= 5
static int reviewCheck(const char * line){
    if(line - '0' < 1 && line - '0' > 5) return false;
    return line - '0';
}



// *** The next 4 functions receive the full line ***  


static User * userCreate(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";",&saveptr);


    char * id = idCheck(token);
    if(!id){ free(aux); return NULL;}
    TOKENIZE(token,saveptr);


    char * name = nameCheck(token);
    if(!name){free(id); free(aux); return NULL;}
    TOKENIZE(token,saveptr);

    char * email = emailCheck(token);
    if(!email) {
        free(name); free(id); free(aux); return NULL;
    }


}

static Reservation * reservationCreate(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";",&saveptr);

    char * id = idCheck(token);
    if(!id){ free(aux); return NULL};
    TOKENIZE(token,saveptr);

    char * userId = idCheck(token);
    if(!userId){ free(id); free(aux); return NULL};
    TOKENIZE(token,saveptr);

    char * hotelId = idCheck(token);
    if(!hotelId){ free(userId); free(id); free(aux); return NULL};
    TOKENIZE(token,saveptr);

    char * hotelName = nameCheck(token);
    if(!hotelName){ free(hotelId); free(userId); free(id); free(aux); return NULL};
    TOKENIZE(token,saveptr);

    unsigned int * hotelStars = hotelStarsCheck(token);
    if(!hotelStars){ free(hotelName); free(hotelId); free(userId); free(id); free(aux); return NULL};
    TOKENIZE(token,saveptr);

    double * tax = taxCheck(token);
    if(!tax){ free(hotelStars); free(hotelName); free(hotelId); free(userId); free(id); free(aux); return NULL};
    TOKENIZE(token;saveptr);

    char * adress = addressCheck(token);
    if(!adress){ free(tax); free(hotelStars); free(hotelName); free(hotelId); free(userId); free(id); free(aux); return NULL};
    TOKENIZE(token;saveptr);

    /*char * beginDate = ;
    if(!beginDate){ free(adress); free(tax); free(hotelStars); free(hotelName); free(hotelId); free(userId); free(id); free(aux); return NULL};
    TOKENIZE(token;saveptr);
    */

    /*char * endDate = ;
    if(!endDate){ free(beginDate); free(adress); free(tax); free(hotelStars); free(hotelName); free(hotelId); free(userId); free(id); free(aux); return NULL};
    TOKENIZE(token;saveptr);
    */

    
}

static Flight * fligthCreate(const char * line);

static Passanger * passangerCreate(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";",&saveptr);

    char * flightId = idCheck(token);
    if(!flightId){ free(aux); return NULL};
    TOKENIZE(token;saveptr);

    char * userId = idCheck(token);
    if(!userId){ free(flightId); free(aux); return NULL};

    
}