#include "../include/parser.h"
#include "../include/dataTypes.h"
#include "../include/catalogs.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <glib.h>




#define CHECKLEN(line) \
    if(strlen(line) < 1 || line == NULL) return NULL;\
    char * aux = strdup(line);\
    if(aux == NULL){\
        perror("strdup memory allocation failed");\
        return NULL;\
    };\
    return aux; \

#define ALLVAR(aux) for(int i = 0;aux[i] != '\0';aux[i] = tolower(aux[i]),i++);

#define TOKENIZE(token,saveptr) token = strtok_r(NULL,";\n\0",&saveptr); 


/*
*
* In each function, the string passed is in the format to be parsed,
* not the whole line
*
*/



 char * idCheck(const char * line){
    if(line == NULL) return NULL; 
    CHECKLEN(line);
}

// Free necessary
 char * nameCheck(const char * line){
    if(line == NULL) return NULL; 
    CHECKLEN(line);
}

 char * phoneNumberCheck(const char * line){
    if(line == NULL) return NULL; 
    CHECKLEN(line);
}

 char sexCheck(const char * line){
    if(line[0] == 'M') return 'M';
    if(line[0] == 'F') return 'F';
    return '\0';
}

// Free necessary
 char * passaportCheck(const char * line){
    CHECKLEN(line);
}

// Free necessary
 char * addressCheck(const char * line){
    CHECKLEN(line);
}

 char * pay_methodCheck(const char * line){
    if(line[0] == '\0') return NULL;
    char * aux = strdup(line);
    for(int i = 0;aux[i] != '\0';aux[i] = tolower(aux[i]),i++);
    return aux;
}


// Verifies the correctness of the year in the date string, following the determined format
 int yearCheck(const char * line){
    if(!line) return 0;
    for(int i = 0; i < 5;i++){
        if(line[i] > '9' && line[i] < '0') return false;
    }
    if(line[4] != '/') return false;
    char aux[5];
    memset(aux,'\0',5);
    strncpy(aux,line,4);
    aux[4] = '\0';
    int n = 0; 
    n = atoi(aux);
    return n;
}

// Verifies the correctness of the month in the date string, following the determined format
// 01 <= time.mon <= 12
 int monthCheck(const char * line){
    if(!line) return 0;
    if(line[5] != '1' && line[5] != '0') return false;
    if(line[5] == '0')
        if(line[6] > '9' && line[6] < '0') return false;
    if(line[5] == '1')
        if(line[6] > '2' && line[6] < '0') return false;
    if(line[7] != '/') return false;
    char aux[3];
    memset(aux,'\0',3);
    aux[0] = line[5];
    aux[1] = line[6];
    aux[2] = '\0';
    int n = 0; 
    n = atoi(aux);
    return n;
}

// Verifies the correctness of the day in the date string, following the determined format
// 0 -> false
// otherwise -> 1 <= tm.tm_mday <= 31 (true)
 int dayCheck(const char * line){
    if(!line) return 0;
    if(line[8] < '0' || line[8] > '3') return false;
    if(line[9] < '0' && line[9] > '9') return false;
    if(line[8] == '3' && line[9] > '1') return false;
    char aux[3];
    memset(aux,'\0',3);
    aux[0] = line[8];
    aux[1] = line[9]; 
    aux[2] = '\0';
    int n = 0; 
    n = atoi(aux);
    return n;
}

// format : nnnn/nn/nn (0 <= n <= 9)
 Time * dateCheck(const char * line){
    if(line == NULL || (line[4] != '/' && line[7] != '/')) return NULL;
    Time * date = createTime();
    if(date == NULL) return NULL;
    switch (line[10])
    {
    case '\0':
        setTime(date,yearCheck(line),monthCheck(line),dayCheck(line),0,0,0);
        return date;
        break;
        
    case ' ':
        if(line[13] != ':' || line[16] != ':') {
            destroyTime(date);
            return NULL;
        }
        setTime(date,yearCheck(line),monthCheck(line),dayCheck(line),hourCheck(line),minuteCheck(line),secondsCheck(line));
        return date;
        break;
    default:
        free(date);
        date = NULL;
        return NULL;
        break;
    }
    free(date);
    date = NULL;
    return NULL;
}

// starting dates cannot be after finishing dates
 bool datesCheck(const char * start, const char * end){
    if(!dateCheck(start) || !dateCheck(end)) return false;
    for(int i = 0;i < 10;i++){
        if(start[i] == '/' || start[i] == ' ') continue;
        if(start[i] > end[i]) return false;
    }
    return true;
}

// format : nnnn/nn/nn nn:nn:nn | dateCheck && [0,23]:
 int hourCheck(const char * line){
    if(!line) return 0;
    if(line[11] == '2'){
        if(line[12] < '0' && line[12] > '3') return -1;
        else{
            char * aux = NULL;
            aux = malloc(sizeof(char) * 3);
            memset(aux,'\0',3);
            aux[0] = '2';
            aux[1] = line[12];
            aux[2] = '\0';
            int n = 0; 
            n = atoi(aux);
            free(aux);
            aux = NULL;
            return n;
        }
    }
    if(line[11] < '0' && line[11] > '1' && line[12] < '0' && line[12] > '9') return -1;
    else {
        char * aux = NULL;
        aux = malloc(sizeof(char) * 3);
        memset(aux,'\0',3);
        aux[0] = line[11];
        aux[1] = line[12];
        aux[2] = '\0';
        int n = 0; 
        n = atoi(aux);
        free(aux);
        aux = NULL;
        return n;
    }
    return -2;
}

// 0 <= min <= 59
 int minuteCheck(const char * line){
    if(!line) return 0;
    if(line[14] < '0' && line[14] > '5' && line[15] < '0' && line[15] > '9') return -1;
    else {
        char * aux = NULL;
        aux = malloc(sizeof(char) * 3);
        memset(aux,'\0',3);
        aux[0] = line[14];
        aux[1] = line[15];
        aux[2] = '\0';
        int n = 0; 
        n = atoi(aux);
        free(aux);
        aux = NULL;
        return n;
    }
    return -2;
}

// 0 <= sec <= 59
 int secondsCheck(const char * line){
    if(!line) return 0;
    if(line[17] < '0' && line[17] > '5' && line[18] < '0' && line[18] > '9') return -1;
    else {
        char * aux = NULL;
        aux = malloc(sizeof(char) * 3);
        memset(aux,'\0',3);
        aux[0] = line[17];
        aux[1] = line[18];
        aux[2] = '\0';
        int n = 0; 
        n = atoi(aux);
        free(aux);
        aux = NULL;
        return n;
    }
    return -2;
}

// starting hours cannot be after finishing hours
// RETURN HERE !!
 bool hoursCheck(const char * departure, const char * arrival){
    if(!hourCheck(departure) || !hourCheck(arrival)) return false;
    for(int i = 11;i < 19;i++){
        if(departure[i] == ':' || arrival[i] == ':') continue;
        if(departure[i] > arrival[i]) return false;
    }
    return true;
}

// format : <username>@<domain>.<TLD> | username.length >= 1 , domain.length >= 2 , TDL.length >= 2
 char * emailCheck(const char * line){
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
    char * email = strdup(line);
    return email;
}

// format : LL (L is a letter)
 char * countryCheck(const char * line){
    if(!line) return NULL;
    if(strlen(line) != 2) return NULL;
    else{
        char * country = strdup(line);
        return country;
    }
    return NULL;
}

// active vs inactive (all varitations)
char * accStatusCheck(const char * line){
    if(line == NULL) return NULL;
    char * aux = strdup(line);
    if(aux == NULL) return NULL;
    if(tolower(aux[0]) == 'a' || tolower(aux[0]) == 'i'){
        for(int i = 0; i < strlen(aux); i++){
            aux[i] = tolower(aux[i]);
        }
    }
    if(strcmp(aux,"active") == 0 || strcmp(aux,"inactive") == 0){ return aux;}
    return NULL;
}

// total_seats must not be less than the number of passangers
 unsigned int seatsCheck(const char * sold){
    unsigned int virtual = atoi(sold);
    return virtual;
}

// length == 3 && all variations
 bool airportCheck(const char * departure,const char * arrival){
    if(strlen(departure) != 3 || strlen(arrival) != 3) return false;
    char * d = strdup(departure), * a = strdup(arrival);
    ALLVAR(d);
    ALLVAR(a);
    if(!strcoll(d,a)) return false;
    free(d);
    free(a);
    return true;
}

// int stars : 1 <= starts <= 5
 unsigned int hotelStarsCheck(const char * line){
    if(line[1] != '\0') return 0;
    if((int) line[0] >= '1' && (int) line[0] <= '5') return (int) line[0] - '0';
    return 0;
}

// int tax : 0 <= tax
// if invalid, functions returns -1
int taxCheck(const char * line){
    if(line[0] == '-') return -1;
    for(int i = 0;line[i] != '\0';i++) if(line[i] == '.' || line[i] == ',') return -1;
    double n = atof(line);
    if(n < 0) return -1;
    return n;
}

// int price : 0 < price
// if invalid, functions returns -1
 double pricePNightCheck(const char * line){
    if(line[0] == '-') return -1;
    double n = atof(line);
    if(n <= 0) return -1;
    return n;
}

// bool breakfast : if(false){"f","false",0,""} else {"t","true","1"}
int breakfastCheck(const char * line){
    char * aux = strdup(line);
    ALLVAR(aux);
    if(!strcoll(aux,"true") || !strcoll(aux,"t") || !strcoll(aux,"1")){ 
        free(aux);
        aux = NULL;
        return 1;
    }
    if(!strcoll(aux,"false") || !strcoll(aux,"f") || !strcoll(aux,"0")){ 
        free(aux);
        aux = NULL;
        return 0;
    }
    free(aux);
    aux = NULL;
    return 2;
}

// int rating : 1 <= rating <= 5
 unsigned int reviewCheck(const char * line){
    if((int) line[0] > '0' && (int) line[0] - '0' < 0 && (int) line[0] - '0' > 4 ) return false;
    return (int) line[0] - '0';
}

// *** The next 4 functions receive the full line ***  


 User * userCheck(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";\n\0",&saveptr);
    User * user = NULL;
    user = createUser();
    if(!user){
        fprintf(stderr,"Memory allocation for User failed");
        if(token) free(token);
        if(aux) free(aux);
        aux = NULL;
        return NULL;
    }

    //check userId
    char * id = idCheck(token);
    if(!id){ free(aux);
    aux = NULL; destroyUser(user); return NULL;}
    setUserId(user,token);
    free(id);
    id = NULL;
    TOKENIZE(token,saveptr);

    //check userName
    char * name = nameCheck(token);
    if(!name){ free(aux);
    aux = NULL; destroyUser(user); return NULL;}
    setUserName(user,name);
    free(name);
    name = NULL;
    TOKENIZE(token,saveptr);

    //check userEmail
    char * email = emailCheck(token);
    if(!email) { free(aux);
    aux = NULL; destroyUser(user); return NULL;}
    setUserEmail(user,email);
    free(email);
    email = NULL;
    TOKENIZE(token,saveptr);

    //check userPhone
    char * phone = phoneNumberCheck(token);
    if(!phone) { free(aux);
    aux = NULL; destroyUser(user); return NULL;}
    setUserPhone(user,token);
    free(phone);
    phone = NULL;
    TOKENIZE(token,saveptr);
    
    //check userBday
    Time * userBday = dateCheck(token);
    if(userBday == NULL) { free(aux);
    aux = NULL; destroyUser(user); return NULL;}
    setUserBday(user,userBday);
    //destroyTime(userBday);
    TOKENIZE(token,saveptr);

    //check userSex
    char sex = sexCheck(token);
    if(sex == '\0') { free(aux);
    aux = NULL; destroyUser(user); return NULL;}
    setUserSex(user,(char) sex);
    sex = '\0';
    TOKENIZE(token,saveptr);

    //check userPassaport
    char * passaport = passaportCheck(token);
    if(!passaport) { free(aux);
    aux = NULL; destroyUser(user); return NULL;}
    setUserPassport(user,passaport);
    free(passaport);
    passaport = NULL;
    TOKENIZE(token,saveptr);

    //check userCountryCode
    char * countryCode = countryCheck(token);
    if(!countryCode) { free(aux);
    aux = NULL; destroyUser(user); return NULL;}
    setUserCountryCode(user,countryCode);
    free(countryCode);
    countryCode = NULL;
    TOKENIZE(token,saveptr);

    //check userAdress
    char * address = addressCheck(token);
    if(!address) { free(aux);
    aux = NULL; destroyUser(user); return NULL;}
    setUserAddress(user,address);
    free(address);
    address = NULL;
    TOKENIZE(token,saveptr);

    //check userAccountCreation time
    Time * userAccountCreation = dateCheck(token);
    if(!userAccountCreation && compareTimes(userBday,userAccountCreation) == false) { free(aux);
    aux = NULL; destroyUser(user); return NULL;}
    setUserAccountCreation(user,userAccountCreation);
    destroyTime(userAccountCreation);
    destroyTime(userBday);
    userAccountCreation = NULL;
    userBday = NULL;
    TOKENIZE(token,saveptr);

    //check userPayMethod
    char * payMethod = pay_methodCheck(token);
    if(!payMethod) { free(aux);
    aux = NULL; destroyUser(user); return NULL;}
    setUserPayMethod(user,payMethod);
    free(payMethod);
    payMethod = NULL;
    TOKENIZE(token,saveptr);

    //check user accountStatus
    char * accStatus = accStatusCheck(token);
    if(accStatus == NULL) { free(aux);
    aux = NULL; destroyUser(user); return NULL;}
    bool accStat = false;
    if(strcmp(accStatus,"active") == 0) accStat = true;
    setUserAccountStatus(user,accStat);
    free(accStatus);
    accStatus = NULL;
    free(aux);
    aux = NULL;
    return user;
}

 Reservation * reservationCheck(const char * line,UsersDatabase uDatabase){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";\n\0",&saveptr);
    Reservation * reservation = createReservation();
    if(reservation == NULL){
        fprintf(stderr,"Memory allocation for User failed");
        if(token) free(token);
        if(aux) free(aux);
        aux = NULL;
        return NULL;
    }

    char * reservationId = idCheck(token);
    if(reservationId == NULL){ free(aux);
    aux = NULL; destroyReservation(reservation); return NULL;}
    setReservId(reservation,token);
    free(reservationId);
    reservationId = NULL;
    TOKENIZE(token,saveptr);
    User * temp = lookupUser(uDatabase,token);
    
    if(temp == NULL){ free(aux);
    aux = NULL; destroyReservation(reservation); return NULL;}
    setReservUserId(reservation,token);
    TOKENIZE(token,saveptr);

    char * reservationHotelId = idCheck(token);
    if(!reservationHotelId){ free(aux);
    aux = NULL; destroyReservation(reservation); return NULL;}
    setReservHotelId(reservation,reservationHotelId);
    free(reservationHotelId);
    reservationHotelId = NULL;
    TOKENIZE(token,saveptr);

    char * reservationHotelName = nameCheck(token);
    if(!reservationHotelName){ free(aux);
    aux = NULL; destroyReservation(reservation); return NULL;}
    setReservHotelName(reservation,reservationHotelName);
    free(reservationHotelName);
    reservationHotelName = NULL;
    TOKENIZE(token,saveptr);

    unsigned int reservationHotelStars = hotelStarsCheck(token);
    if(!reservationHotelStars){ free(aux);
    aux = NULL; destroyReservation(reservation); return NULL;}
    setReservHotelStars(reservation,reservationHotelStars);
    TOKENIZE(token,saveptr);

    int reservationTax = taxCheck(token);
    if(reservationTax < 0){ free(aux);
    aux = NULL; destroyReservation(reservation) ;return NULL;}
    setReservCityTax(reservation,reservationTax);
    TOKENIZE(token,saveptr);

    char * reservationAdress = addressCheck(token);
    if(!reservationAdress){ free(aux);
    aux = NULL; destroyReservation(reservation) ;return NULL;}
    setReservHotelAddress(reservation,reservationAdress);
    free(reservationAdress);
    reservationAdress = NULL;
    TOKENIZE(token,saveptr);

    Time * beginDate = dateCheck(token);
    if(!beginDate){ free(aux);
    aux = NULL; destroyReservation(reservation); return NULL;}
    setReservBeginDate(reservation, beginDate);
    TOKENIZE(token,saveptr);

    Time * endDate = dateCheck(token);
    if(!endDate){ free(aux);
    aux = NULL; destroyReservation(reservation); return NULL;}
    setReservEndDate(reservation, endDate);
    if(!compareTimes(beginDate,endDate)){ destroyTime(beginDate); destroyTime(endDate); free(aux);
    aux = NULL; destroyReservation(reservation); return NULL;}
    destroyTime(endDate);
    endDate = NULL;
    destroyTime(beginDate);
    beginDate = NULL; 
    TOKENIZE(token,saveptr);

    double pricePerNight = pricePNightCheck(token);
    if(pricePerNight < 0){ free(aux);
    aux = NULL; destroyReservation(reservation); return NULL;}
    setReservPricePerNight(reservation, pricePerNight);
    bool includesBreakfast = false;
    if(saveptr[0] == ';') {
        setReservBreakfast(reservation, includesBreakfast);
        //RoomDetails
        setReservRoomDetails(reservation,token);
        TOKENIZE(token,saveptr);
        
        unsigned int rating = reviewCheck(token);
        if(rating == 0){ free(aux);
        aux = NULL; destroyReservation(reservation); return NULL;}
        setReservRating(reservation,rating);
        TOKENIZE(token,saveptr);

        //Comment
        setReservComment(reservation,token);
        
        free(aux);
        aux = NULL;
        return reservation;
    }
    TOKENIZE(token,saveptr);


    int n = breakfastCheck(token);
    if(n == 2) { free(aux);
    aux = NULL; destroyReservation(reservation); return NULL;}
    if(n == 1) includesBreakfast = true;
    setReservBreakfast(reservation, includesBreakfast);
    //free(includesBreakfast);
    TOKENIZE(token,saveptr);

    //RoomDetails
    setReservRoomDetails(reservation,token);
    TOKENIZE(token,saveptr);
    
    unsigned int rating = reviewCheck(token);
    if(!rating){ free(aux);
    aux = NULL; destroyReservation(reservation); return NULL;}
    setReservRating(reservation,rating);
    TOKENIZE(token,saveptr);

    //Comment
    setReservComment(reservation,token);
    
    free(aux);
    aux = NULL;
    return reservation;
}

 Flight * fligthCheck(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";\n\0",&saveptr);
    Flight * flight = createFlight();

    char * flightId = idCheck(token);
    if(!flightId || saveptr[0] == ';'){ free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    setFlightId(flight,flightId);
    free(flightId);
    flightId = NULL;
    TOKENIZE(token,saveptr);

    char * airline = nameCheck(token);
    if(!airline || saveptr[0] == ';'){ free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    setFlightAirline(flight,airline);
    free(airline);
    airline = NULL;
    TOKENIZE(token,saveptr);

    char * planeModel = nameCheck(token);
    if(!planeModel || saveptr[0] == ';'){ free(planeModel); free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    setFlightPlaneModel(flight,planeModel);
    free(planeModel);
    planeModel = NULL;
    TOKENIZE(token,saveptr);

    unsigned int totalSeats = seatsCheck(token);
    if(!totalSeats || saveptr[0] == ';'){ free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    setFlightTotalSeats(flight,totalSeats);
    TOKENIZE(token,saveptr);

    //Origin
    if(strlen(token)!=3 || saveptr[0] == ';'){ free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    char * origin = strdup(token);
    setFlightOrigin(flight,origin);
    TOKENIZE(token,saveptr);

    //Destination
    if((!airportCheck(origin,token) && strlen(token)) || saveptr[0] == ';'){ free(origin); free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    free(origin);
    origin = NULL;
    setFlightDestination(flight,token);
    TOKENIZE(token,saveptr);
    
    Time * sDepartDate = dateCheck(token);
    if(!sDepartDate || saveptr[0] == ';'){ free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    setFlightSDepartureDate(flight,sDepartDate);
    TOKENIZE(token,saveptr);

    Time * sArrivalDate = dateCheck(token);
    if(!sArrivalDate || saveptr[0] == ';'){ free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    setFlightSArrivalDate(flight,sArrivalDate);

    //sDepartDate before sArrivalDate
    if(compareTimes(sDepartDate,sArrivalDate) == false || saveptr[0] == ';'){ destroyTime(sArrivalDate); destroyTime(sDepartDate); free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    destroyTime(sArrivalDate);
    sArrivalDate = NULL;
    destroyTime(sDepartDate);
    sDepartDate = NULL;
    TOKENIZE(token,saveptr);

    Time * rDepartDate = dateCheck(token);
    if(!rDepartDate || saveptr[0] == ';'){ free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    setFlightRDepartureDate(flight,rDepartDate);
    TOKENIZE(token,saveptr);

    Time * rArrivalDate = dateCheck(token);
    if(!rArrivalDate || saveptr[0] == ';'){ free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    setFlightRArrivalDate(flight,rArrivalDate);

    //rDepartDate before rArrivalDate
    if(compareTimes(rDepartDate,rArrivalDate) == false || saveptr[0] == ';'){ free(rArrivalDate); free(rDepartDate); free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    destroyTime(rArrivalDate);
    rArrivalDate = NULL;
    destroyTime(rDepartDate);
    rDepartDate = NULL;
    TOKENIZE(token,saveptr);

    char * pilot = nameCheck(token);
    if(pilot == NULL || saveptr[0] == ';'){ free(pilot); free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    setFlightPilot(flight,pilot);
    free(pilot);
    pilot = NULL;
    TOKENIZE(token,saveptr);

    char * copilot = nameCheck(token);
    if(!copilot){ free(copilot); free(aux);
    aux = NULL; destroyFlight(flight); return NULL;}
    setFlightCopilot(flight,copilot);
    free(copilot);
    copilot = NULL;
    TOKENIZE(token,saveptr);


    if(token) setFlightNotes(flight,token);
    
    free(aux);
    aux = NULL;
    return flight;

}

 Passanger * passangerCheck(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";\n\0",&saveptr);
    Passanger * passanger = createPassanger();

    char * passangerFlightId = idCheck(token);
    if(!passangerFlightId){ free(aux);
    aux = NULL; destroyPassanger(passanger); return NULL;}
    setPassangerFlightId(passanger,passangerFlightId);
    free(passangerFlightId);
    passangerFlightId = NULL;
    TOKENIZE(token,saveptr);

    char * passangerUserId = idCheck(token);
    if(!passangerUserId){ free(aux);
    aux = NULL; destroyPassanger(passanger); return NULL;}
    setPassangerUserId(passanger,passangerUserId);
    free(passangerUserId);
    passangerUserId = NULL;

    free(aux);
    aux = NULL;
    return passanger;
}