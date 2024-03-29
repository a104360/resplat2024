#include "../include/parser.h"
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/passenger.h"
#include "../include/utils.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <glib.h>


#define BUFFERSIZE 1000

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


#define ERRORSU(aux,type)\
    if(aux){\
        ffree((void **) &aux);\
        aux = NULL;\
    }\
    if(type){\
        destroyUser(type);\
    }\
    return NULL;


#define ERRORSR(aux,type)\
    if(aux){\
        ffree((void **) &aux);\
        aux = NULL;\
    }\
    if(type){\
        destroyReservation(type);\
    }\
    return NULL;

#define ERRORSF(aux,type)\
    if(aux){\
        ffree((void **) &aux);\
        aux = NULL;\
    }\
    if(type){\
        destroyFlight(type);\
    }\
    return NULL;



#define ERRORSP(aux,type)\
    if(aux){\
        ffree((void **) &aux);\
        aux = NULL;\
    }\
    if(type){\
        destroyPassenger(type);\
    }\
    return NULL;

/*
*
* In each function, the string passed is in the format to be parsed,
* not the whole line
*
*/


//Check if an id is correct
//cannot be NULL
 char * idCheck(const char * line){
    if(line == NULL) return NULL; 
    CHECKLEN(line);
}

//Check if a name is correct
//cannot be NULL
// Free necessary
 char * nameCheck(const char * line){
    if(line == NULL) return NULL; 
    CHECKLEN(line);
}

//Check if a number is correct
//cannot be NULL
 char * phoneNumberCheck(const char * line){
    if(line == NULL) return NULL; 
    CHECKLEN(line);
}

//Check if the sex is valid (M or F)
 char sexCheck(const char * line){
    if(line[0] == 'M') return 'M';
    if(line[0] == 'F') return 'F';
    return '\0';
}

//Check if userpassport is valid 
//cannot be NULL
// Free necessary
 char * passportCheck(const char * line){
    CHECKLEN(line);
}

//Check if an address is valid
// Free necessary
 char * addressCheck(const char * line){
    CHECKLEN(line);
}

//Check if the payment method is valid
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

//Check if dates are valid
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
        ffree((void **)&date);
        date = NULL;
        return NULL;
        break;
    }
    ffree((void **)&date);
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

//datecheck aux
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
            ffree((void **)&aux);
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
        ffree((void **)&aux);
        aux = NULL;
        return n;
    }
    return -2;
}

//datecheck aux
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
        ffree((void **)&aux);
        aux = NULL;
        return n;
    }
    return -2;
}

//datecheck aux
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
        ffree((void **)&aux);
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
char* accStatusCheck(const char* line) {
    if (line == NULL) return NULL;
    
    char* aux = strdup(line);
    if (aux == NULL) return NULL;

    /*int len = strlen(aux);

    if (aux[0] == 'a' || aux[0] == 'A' || aux[0] == 'i' || aux[0] == 'I') {
        for (int i = 0; i < len; i++) {
            aux[i] = tolower(aux[i]);
        }
    }*/

    if (strcasecmp(aux, "active") == 0 || strcasecmp(aux, "inactive") == 0) {
        return aux;
    }
    ffree((void **)&aux);
    aux = NULL;
    return NULL;
}

// total_seats must not be less than the number of passengers
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
    ffree((void **)&d);
    ffree((void **)&a);
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
        ffree((void **)&aux);
        aux = NULL;
        return 1;
    }
    if(!strcoll(aux,"false") || !strcoll(aux,"f") || !strcoll(aux,"0")){ 
        ffree((void **)&aux);
        aux = NULL;
        return 0;
    }
    ffree((void **)&aux);
    aux = NULL;
    return 2;
}

// int rating : 1 <= rating <= 5
 unsigned int reviewCheck(const char * line){
    if(!isdigit(line[0])) return false;
    if(line[1] != '\0' || line[0] - '0' > 5 || line[0] - '0' == 0) return false;
    return line[0] - '0';
}

// *** The next 4 functions receive the full line ***  

//Recieves a user and checks if the user is valid using the previus functions
User * userCheck(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";\n\0",&saveptr);
    User * user = NULL;
    user = createUser();
    if(!user){
        fprintf(stderr,"Memory allocation for User failed");
        ffree((void **)&token);
        ffree((void **)&aux);
        return NULL;
    }

    //check userId
    char * id = idCheck(token);
    if(!id || saveptr[0] == ';'){ 
        ffree((void **)&id);
        ERRORSU(aux,user);
    }
    setUserId(user,token);
    ffree((void **)&id);
    TOKENIZE(token,saveptr);

    //check userName
    char * name = nameCheck(token);
    if(!name || saveptr[0] == ';'){
        ffree((void **)&name);
        ERRORSU(aux,user);
    }
    setUserName(user,token);
    ffree((void **)&name);
    TOKENIZE(token,saveptr);

    //check userEmail
    char * email = emailCheck(token);
    if(!email || saveptr[0] == ';') { 
        ffree((void **)&email);
        ERRORSU(aux,user);
    }
    //setUserEmail(user,token);
    ffree((void **)&email);
    TOKENIZE(token,saveptr);

    //check userPhone
    char * phone = phoneNumberCheck(token);
    if(!phone || saveptr[0] == ';') { 
        ffree((void **)&phone);
        ERRORSU(aux,user);
    }
    //setUserPhone(user,token);
    ffree((void **)&phone);
    TOKENIZE(token,saveptr);
    
    //check userBday
    Time * userBday = dateCheck(token);
    if(!userBday || saveptr[0] == ';') { 
        destroyTime(userBday);
        ERRORSU(aux,user);
    }
    setUserBday(user,userBday);
    TOKENIZE(token,saveptr);



    //check userSex
    char sex = sexCheck(token);
    if(sex == '\0') { 
        destroyTime(userBday);
        ERRORSU(aux,user);
    }
    setUserSex(user,(char) sex);
    TOKENIZE(token,saveptr);

    //check userPassport
    char * passport = passportCheck(token);
    if(!passport || saveptr[0] == ';') { 
        destroyTime(userBday);
        ffree((void **)&passport);
        ERRORSU(aux,user);
    }
    setUserPassport(user,passport);
    ffree((void **)&passport);
    TOKENIZE(token,saveptr);

    //check userCountryCode
    char * countryCode = countryCheck(token);
    if(!countryCode || saveptr[0] == ';') {
        destroyTime(userBday);
        ffree((void **)&countryCode);
        ERRORSU(aux,user);
    }
    setUserCountryCode(user,countryCode);
    ffree((void **)&countryCode);
    TOKENIZE(token,saveptr);

    //check userAdress
    char * address = addressCheck(token);
    if(!address || saveptr[0] == ';') { 
        destroyTime(userBday);
        ffree((void **)&address);
        ERRORSU(aux,user);
    }
    //setUserAddress(user,address);
    ffree((void **)&address);
    TOKENIZE(token,saveptr);

    //check userAccountCreation time
    Time * userAccountCreation = dateCheck(token);
    if(!userAccountCreation || compareTimes(userBday,userAccountCreation) == false || saveptr[0] == ';') {
        destroyTime(userBday);
        destroyTime(userAccountCreation);
        ERRORSU(aux,user);
    }
    setUserAccountCreation(user,userAccountCreation);
    destroyTime(userAccountCreation);
    destroyTime(userBday);
    TOKENIZE(token,saveptr);
    
    //check userPayMethod
    char * payMethod = pay_methodCheck(token);
    if(!payMethod || saveptr[0] == ';' || saveptr[0] == '\0' || saveptr[0] == '\n') { 
        ffree((void **)&payMethod);
        ERRORSU(aux,user);
    }
    //setUserPayMethod(user,payMethod);
    ffree((void **)&payMethod);
    TOKENIZE(token,saveptr);
    
    char * string = accStatusCheck(token);
    if(string == NULL) {
        ffree((void **)&string);
        ERRORSU(aux,user);
    }
    if(strcasecmp(string,"active") == 0){setUserAccountStatus(user,true);}else {setUserAccountStatus(user,false);} 
    ffree((void **)&string);
    

    ffree((void **)&aux);
    aux = NULL;
    return user;
}


//Recieves a reservation and checks whether the reservation is valid using the previus functions
 Reservation * reservationCheck(const char * line,Users * uDatabase){
    if(line[0] == ';') return NULL;
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";\n\0",&saveptr);
    Reservation * reservation = createReservation();
    if(reservation == NULL){
        fprintf(stderr,"Memory allocation for User failed");
        ffree((void **)&token);
        ffree((void **)&aux);
        return NULL;
    }

    char * reservationId = idCheck(token);
    if(reservationId == NULL || saveptr[0] == ';') {
        ffree((void **)&reservationId);
        ERRORSR(aux,reservation);
    }  
    setReservId(reservation,token);
    ffree((void **)&reservationId);
    TOKENIZE(token,saveptr);
    User * temp = lookupElement(uDatabase,token);
    if(temp == NULL || saveptr[0] == ';'){ERRORSR(aux,reservation);}
    setReservUserId(reservation,token);
    TOKENIZE(token,saveptr);

    char * reservationHotelId = idCheck(token);
    if(!reservationHotelId || saveptr[0] == ';'){
        ffree((void **)&reservationHotelId);    
        ERRORSR(aux,reservation);
    }
    setReservHotelId(reservation,reservationHotelId);
    ffree((void **)&reservationHotelId);
    TOKENIZE(token,saveptr);

    char * reservationHotelName = nameCheck(token);
    if(!reservationHotelName || saveptr[0] == ';'){
        ffree((void **)&reservationHotelName);
        ERRORSR(aux,reservation);
    }
    setReservHotelName(reservation,reservationHotelName);
    ffree((void **)&reservationHotelName);
    TOKENIZE(token,saveptr);

    unsigned int reservationHotelStars = hotelStarsCheck(token);
    if(!reservationHotelStars || saveptr[0] == ';'){ ERRORSR(aux,reservation);}
    setReservHotelStars(reservation,reservationHotelStars);
    TOKENIZE(token,saveptr);

    int reservationTax = taxCheck(token);
    if(reservationTax < 0 || saveptr[0] == ';'){ ERRORSR(aux,reservation);}
    setReservCityTax(reservation,reservationTax);
    TOKENIZE(token,saveptr);

    char * reservationAddress = addressCheck(token);
    if(!reservationAddress || saveptr[0] == ';'){
        ffree((void **)&reservationAddress);
        ERRORSR(aux,reservation);
    }
    //setReservHotelAddress(reservation,reservationAddress);
    ffree((void **)&reservationAddress);
    TOKENIZE(token,saveptr);

    Time * beginDate = dateCheck(token);
    if(!beginDate || saveptr[0] == ';'){ 
        destroyTime(beginDate);
        ERRORSR(aux,reservation);
    }
    setReservBeginDate(reservation, beginDate);
    TOKENIZE(token,saveptr);

    Time * endDate = dateCheck(token);
    if(!endDate || saveptr[0] == ';'){ 
        destroyTime(beginDate);
        destroyTime(endDate);
        ERRORSR(aux,reservation);
    }
    if(!compareTimes(beginDate,endDate)){ 
        destroyTime(beginDate); 
        destroyTime(endDate); 
        ERRORSR(aux,reservation);
    }
    setReservEndDate(reservation, endDate);
    destroyTime(endDate);
    destroyTime(beginDate);
    TOKENIZE(token,saveptr);

    double pricePerNight = pricePNightCheck(token);
    if(pricePerNight < 0){ ERRORSR(aux,reservation);}
    setReservPricePerNight(reservation, pricePerNight);
    bool includesBreakfast = false;
    if(saveptr[0] == ';') {
        setReservBreakfast(reservation, includesBreakfast);
        //RoomDetails
        if(saveptr[1] == ';'){
            //setReservRoomDetails(reservation,NULL);
            TOKENIZE(token,saveptr);
            
            unsigned int rating = reviewCheck(token);
            if(rating == 0){ERRORSR(aux,reservation);}
            setReservRating(reservation,rating);
            if(saveptr[0] == ';') {
                if(aux){
                    ffree((void **)&aux);
                    aux = NULL;
                }
                    return reservation;
            }
            TOKENIZE(token,saveptr);

            //Comment
            //setReservComment(reservation,token);
            
            strcpy(aux,line);
            ffree((void **)&aux);
            aux = NULL;
            return reservation;
        }else{
            TOKENIZE(token,saveptr);
            char * roomDetails = idCheck(token);
            if(!roomDetails || saveptr[0] == ';'){
                ffree((void **)&roomDetails);
                ERRORSR(aux,reservation);
            }
            //setReservRoomDetails(reservation,roomDetails);
            ffree((void **)&roomDetails);
            TOKENIZE(token,saveptr);

            unsigned int rating = reviewCheck(token);
            if(!rating){ ERRORSR(aux,reservation); }
            setReservRating(reservation, rating);
            if(saveptr[0] == ';'){
                strcpy(aux,line);
                ffree((void **)&aux);
                aux = NULL;
                return reservation;
            }

            TOKENIZE(token,saveptr);

            //Comment
            //setReservComment(reservation,token);
            
            strcpy(aux,line);
            ffree((void **)&aux);
            aux = NULL;
            return reservation;
        }
    }
    TOKENIZE(token,saveptr);


    int n = breakfastCheck(token);
    if(n == 2) { ERRORSR(aux,reservation);}
    if(n == 1) includesBreakfast = true;
    setReservBreakfast(reservation, includesBreakfast);
    if(saveptr[0] == ';'){
        TOKENIZE(token,saveptr);
        unsigned int rating = reviewCheck(token);
        if(rating == 0){ ERRORSR(aux,reservation);}
        setReservRating(reservation,rating);
        if(saveptr[0] == ';'){
                strcpy(aux,line);
                ffree((void **)&aux);
                aux = NULL;
                return reservation;
        }

        TOKENIZE(token,saveptr);

        //Comment
        //setReservComment(reservation,token);
        
        strcpy(aux,line);
        ffree((void **)&aux);
        aux = NULL;
        return reservation;
    }
    TOKENIZE(token,saveptr);

    //RoomDetails
    //setReservRoomDetails(reservation,token);
    TOKENIZE(token,saveptr);
    
    unsigned int rating = reviewCheck(token);
    if(!rating){ ERRORSR(aux,reservation);}
    setReservRating(reservation,rating);
    if(saveptr[0] == ';' || saveptr[0] == '\n' || saveptr[0] == '\0'){
        strcpy(aux,line);
        ffree((void **)&aux);
        aux = NULL;
        return reservation;
    }
    TOKENIZE(token,saveptr);

    //Comment
    //setReservComment(reservation,token);
    strcpy(aux,line);
    ffree((void **)&aux);
    aux = NULL;
    return reservation;
}


//Recieves a flight and checks if the flight is valid using the previus functions
 Flight * fligthCheck(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";\n\0",&saveptr);
    Flight * flight = createFlight();

    char * flightId = idCheck(token);
    if(flightId == NULL || saveptr[0] == ';'){
        ffree((void **)&flightId);
        ERRORSF(aux,flight);
    }
    setFlightId(flight,flightId);
    ffree((void **)&flightId);
    TOKENIZE(token,saveptr);

    char * airline = nameCheck(token);
    if(!airline || saveptr[0] == ';'){
        ffree((void **)&airline);
        ERRORSF(aux,flight);
    }
    setFlightAirline(flight,airline);
    ffree((void **)&airline);
    TOKENIZE(token,saveptr);

    char * planeModel = nameCheck(token);
    if(!planeModel || saveptr[0] == ';'){ 
        ffree((void **)&planeModel);
        ERRORSF(aux,flight);
    }
    setFlightPlaneModel(flight,planeModel);
    ffree((void **)&planeModel);
    TOKENIZE(token,saveptr);

    unsigned int totalSeats = seatsCheck(token);
    if(!totalSeats || saveptr[0] == ';'){
        ERRORSF(aux,flight);
    }
    setFlightTotalSeats(flight,totalSeats);
    TOKENIZE(token,saveptr);

    //Origin
    if(strlen(token)!=3 || saveptr[0] == ';'){ 
        ERRORSF(aux,flight);
    }
    char * origin = strdup(token);
    for(int a = 0;a < 3;a++) origin[a] = toupper(origin[a]);
    setFlightOrigin(flight,origin);
    TOKENIZE(token,saveptr);

    //Destination
    if((!airportCheck(origin,token) && strlen(token) != 3) || saveptr[0] == ';'){
        ffree((void **)&origin);
        ERRORSF(aux,flight);
    }
    ffree((void **)&origin);
    char * destination = strdup(token);
    for(int i = 0;i < 3;i++) destination[i] = toupper(destination[i]);
    setFlightDestination(flight,destination);
    ffree((void **)&destination);
    TOKENIZE(token,saveptr);
    
    Time * sDepartDate = dateCheck(token);
        if(!sDepartDate || saveptr[0] == ';'){ 
            destroyTime(sDepartDate);
            ERRORSF(aux,flight);
        }
    setFlightSDepartureDate(flight,sDepartDate);
    TOKENIZE(token,saveptr);

    Time * sArrivalDate = dateCheck(token);
    if(!sArrivalDate || saveptr[0] == ';'){
        destroyTime(sDepartDate);
        destroyTime(sArrivalDate);
        ERRORSF(aux,flight);
    }
    setFlightSArrivalDate(flight,sArrivalDate);


    //sDepartDate before sArrivalDate
    if(compareTimes(sDepartDate,sArrivalDate) == false || saveptr[0] == ';'){ 
        destroyTime(sArrivalDate);
        destroyTime(sDepartDate);
        ERRORSF(aux,flight);
    }
    destroyTime(sArrivalDate);
    destroyTime(sDepartDate);
    TOKENIZE(token,saveptr);


    Time * rDepartDate = dateCheck(token);
    if(!rDepartDate || saveptr[0] == ';'){ 
        destroyTime(rDepartDate);
        ERRORSF(aux,flight);
        }
    setFlightRDepartureDate(flight,rDepartDate);
    TOKENIZE(token,saveptr);

    Time * rArrivalDate = dateCheck(token);
    if(!rArrivalDate || saveptr[0] == ';'){
        destroyTime(rDepartDate);
        destroyTime(rArrivalDate);
        ERRORSF(aux,flight);
        }
    setFlightRArrivalDate(flight,rArrivalDate);

    //rDepartDate before rArrivalDate
    if(compareTimes(rDepartDate,rArrivalDate) == false || saveptr[0] == ';'){ 
        destroyTime(rDepartDate);
        destroyTime(rArrivalDate);
        ERRORSF(aux,flight);
    }
    destroyTime(rArrivalDate);
    destroyTime(rDepartDate);
    TOKENIZE(token,saveptr);

    char * pilot = nameCheck(token);
    if(pilot == NULL || saveptr[0] == ';'){
        ffree((void **)&pilot);
        ERRORSF(aux,flight);
    }
    //setFlightPilot(flight,pilot);
    ffree((void **)&pilot);
    TOKENIZE(token,saveptr);

    char * copilot = nameCheck(token);
    if(!copilot){ 
        ffree((void **)&copilot);
        ERRORSF(aux,flight);
    }
    //setFlightCopilot(flight,copilot);
    ffree((void **)&copilot);
    if(saveptr[0] == ';'){
        ffree((void **)&aux);
        return flight;
    }
    TOKENIZE(token,saveptr);


    //if(token) setFlightNotes(flight,token);
    
    ffree((void **)&aux);
    aux = NULL;
    return flight;

}


//Recieves a passenger and checks if the passenger is valid using the previus functions
Passenger * passengerCheck(const char * line,Users * uDatabase,Flights * fDatabase){
    if(line[0] == ';' || line == NULL || line[0] == '\0' || line[0] == '\n') return NULL;
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";\n\0",&saveptr);
    Passenger * passenger = createPassenger();
    if(!passenger){
        ffree((void **)&token);
        ffree((void **)&aux);
        return NULL;
    }


    Flight * fTemp = lookupElement(fDatabase,token);
    if(fTemp == NULL || saveptr[0] == ';'){ 
        ERRORSP(aux,passenger);
    }
    setPassengerFlightId(passenger,token);

    TOKENIZE(token,saveptr);

    User * uTemp = lookupElement(uDatabase,token);
    if(uTemp == NULL){ ERRORSP(aux,passenger);}

    setPassengerUserId(passenger,token);

    ffree((void **)&aux);
    return passenger;
}




Users * validateUsers(const char * folderPath){
    size_t argSize = 0;
    argSize = strlen(folderPath);
    char * storeFgets = NULL;
    char * filePath = NULL;
    filePath = malloc(argSize + 20); // malloc
    memset(filePath,'\0',argSize + 20);
    strcpy(filePath,folderPath);


    // Create Users Database
    strncat(filePath,"/users.csv",12); // ?
    filePath[argSize + 1 + 10 + 1] = '\0';

    FILE * userFile = NULL;
    userFile = fopen(filePath,"r"); // open

    FILE * userErrors = NULL;
    char * filePathUErrors = NULL;
    filePathUErrors = malloc(strlen(folderPath) + 20); // malloc
    strncpy(filePathUErrors,"Resultados",14);
    strncat(filePathUErrors,"/users_errors.csv",18); // ?
    userErrors = fopen(filePathUErrors,"a"); // open
    if(userErrors == NULL) {perror("Users errors file did not open\n"); return NULL;}

    char * userData = malloc(sizeof(char) * BUFFERSIZE); // malloc

    if(userData == NULL) { perror("Erro a alocar memoria na main"); return NULL;}

    memset(userData, '\0', BUFFERSIZE);


    Users * uDatabase = createDatabase(&destroyUser); // initDatabase

    storeFgets = fgets(userData,BUFFERSIZE,userFile);

    fprintf(userErrors,"%s",userData);

    while((storeFgets = fgets(userData,BUFFERSIZE,userFile)) != NULL){

        User * uBuffer = NULL;

        int tamanhoUserData = strlen(userData);

        char * userDataClean = malloc(sizeof(char) * (tamanhoUserData +1)); // malloc

        strncpy(userDataClean,userData,tamanhoUserData);

        userDataClean[tamanhoUserData] = '\0';


        uBuffer = userCheck(userDataClean); // malloc


        if(uBuffer != NULL){
            insertOnDatabase(uDatabase,getUserId(uBuffer),uBuffer);

        }else{ 
            fprintf(userErrors,"%s",userDataClean);
        }
        
        free(userDataClean);// free
        userDataClean = NULL;
    }
    
    fclose(userFile); // close
    userFile = NULL;
    
    free(filePathUErrors);  // free
    filePathUErrors = NULL;
    
    free(userData); // free
    userData = NULL;

    fclose(userErrors); // close
    userErrors = NULL;

    ffree((void **)&filePath);



    return uDatabase;
}



























Reservations * validateReservations(Users * uDatabase, const char * folderPath){
    size_t argSize = 0;
    argSize = strlen(folderPath);
    char * storeFgets = NULL;
    char * filePath = NULL;
    filePath = malloc(argSize + 20);
    memset(filePath,'\0',argSize + 20);
    strcpy(filePath,folderPath);

    memset(filePath,'\0',argSize + 20);
    
        // Create Reservations Database
        strcpy(filePath,folderPath);
        strncat(filePath,"/reservations.csv",19);

        filePath[argSize + 1 + 17 + 1] = '\0';

        FILE * reservationsFile = NULL;
        reservationsFile = fopen(filePath,"r");

        FILE * reservationsErrors = NULL;
        char * filePathRErrors = NULL;
        filePathRErrors = malloc(argSize + 27);
        strncpy(filePathRErrors,"Resultados",14);
        strncat(filePathRErrors,"/reservations_errors.csv",25);
        reservationsErrors = fopen(filePathRErrors,"a+");
        if(!reservationsErrors) {perror("Reservations errors file did not open\n"); return NULL;}

        char * reservationData = malloc(sizeof(char) * BUFFERSIZE);

        if(!reservationData) { perror("Erro a alocar memoria na main"); return NULL;}

        memset(reservationData, '\0', BUFFERSIZE);

        Reservations * rDatabase = createDatabase(&destroyReservation);

        storeFgets = fgets(reservationData,BUFFERSIZE,reservationsFile);

        fprintf(reservationsErrors,"%s",reservationData);

        while((storeFgets = fgets(reservationData,BUFFERSIZE,reservationsFile)) != NULL){

            Reservation * rBuffer = NULL;

            int tamanhoReservationData = strlen(reservationData);

            char * reservationDataClean = malloc(sizeof(char) * (tamanhoReservationData +1));

            strncpy(reservationDataClean,reservationData,tamanhoReservationData);

            reservationDataClean[tamanhoReservationData] = '\0';

            rBuffer = reservationCheck(reservationDataClean,uDatabase);

        if(rBuffer != NULL){
                insertOnDatabase(rDatabase,getReservId(rBuffer),rBuffer);
            }else{ 
                fprintf(reservationsErrors,"%s",reservationDataClean);
            }
                
                free(reservationDataClean);
                reservationDataClean = NULL;
        }
        
        fclose(reservationsFile); // close
        reservationsFile = NULL;
        free(filePathRErrors);  // free
        filePathRErrors = NULL;
        free(reservationData); // free
        reservationData = NULL;
        fclose(reservationsErrors); // close
        reservationsErrors = NULL;

    ffree((void **)&filePath);
    return rDatabase;
}


























Flights * validateFlights(const char * folderPath){
    size_t argSize = 0;
    argSize = strlen(folderPath);
    char * filePath = NULL;
    filePath = malloc(argSize + 20);
    memset(filePath,'\0',argSize + 20);
    strcpy(filePath,folderPath);

    memset(filePath,'\0',argSize + 20); // CORRIGIR
    

        //Create Flights Database
        strcpy(filePath,folderPath);
        strncat(filePath,"/flights.csv",14);

        FILE * flightFile = NULL;
        flightFile = fopen(filePath,"r");

        FILE * flightsErrors = NULL;
        char * filePathFErrors = NULL;
        filePathFErrors = malloc(argSize + 27);
        strncpy(filePathFErrors,"Resultados",14);
        strncat(filePathFErrors,"/flights_errors.csv",25);
        flightsErrors = fopen(filePathFErrors,"a+");
        if(!flightsErrors) {
            perror("Flights errors file did not open\n");
            if(filePath){
                free(filePath);
                filePath = NULL;
            } 
            if(filePathFErrors){
                free(filePathFErrors);
                filePathFErrors = NULL;
            }
            if(flightFile){
                fclose(flightFile);
                flightFile = NULL;
            }
            return NULL;
        }

        char * flightData = malloc(sizeof(char) * BUFFERSIZE);

        if(!flightData) { 
            perror("Erro a alocar memoria na main"); 
            if(filePath){
                free(filePath);
                filePath = NULL;
            } 
            if(filePathFErrors){
                free(filePathFErrors);
                filePathFErrors = NULL;
            }
            if(flightFile){
                fclose(flightFile);
                flightFile = NULL;
            }
            fclose(flightsErrors);
            flightsErrors = NULL;
            return NULL;
        }

        memset(flightData, '\0', BUFFERSIZE);

        Flights * fDatabase = createDatabase(&destroyFlight);

        while(fgets(flightData,BUFFERSIZE,flightFile)){

            Flight * fBuffer = NULL;

            int tamanhoFlightData = strlen(flightData);

            char flightDataClean[tamanhoFlightData +1];

            strncpy(flightDataClean,flightData,tamanhoFlightData);

            flightDataClean[tamanhoFlightData] = '\0';

            fBuffer = fligthCheck(flightDataClean);

            //fligthCheck(flightDataClean);

            if(fBuffer != NULL){

                insertOnDatabase(fDatabase,getFlightId(fBuffer),fBuffer);

            }else{ 
                fprintf(flightsErrors,"%s",flightDataClean);
            }

        }

        fclose(flightFile); // close
        flightFile = NULL;
        free(filePathFErrors);  // free
        filePathFErrors = NULL;
        free(flightData); // free
        flightData = NULL;
        fclose(flightsErrors); // close
        flightsErrors = NULL;

    ffree((void **)&filePath);
    return fDatabase;
}


































Passengers * validatePassengers(Users * uDatabase,Flights * fDatabase,const char * folderPath){
    size_t argSize = 0;
    argSize = strlen(folderPath);
    char * storeFgets = NULL;
    char * filePath = NULL;
    filePath = malloc(argSize + 20);
    memset(filePath,'\0',argSize + 20);
    strcpy(filePath,folderPath);

    memset(filePath,'\0',argSize + 20);

        strcpy(filePath,folderPath);
        strncat(filePath,"/passengers.csv",17);

        FILE * passengersFile = NULL;
        passengersFile = fopen(filePath,"r");
        if(passengersFile == NULL){
            perror("Did not opened the file correctly");
            return NULL;
        }

        FILE * passengersErrors = NULL;
        char * filePathPErrors = NULL;
        filePathPErrors = malloc(argSize + 27);
        strncpy(filePathPErrors,"Resultados",14);
        strncat(filePathPErrors,"/passengers_errors.csv",25);
        passengersErrors = fopen(filePathPErrors,"a+");
        if(!passengersErrors) {perror("Passengers errors file did not open\n"); return NULL;}

        char * passengersData = malloc(sizeof(char) * BUFFERSIZE);

        if(!passengersData) { perror("Erro a alocar memoria na main"); return NULL;}

        memset(passengersData, '\0', BUFFERSIZE);

        Passengers * pDatabase = createPassengerDatabase();
        
        storeFgets = fgets(passengersData,BUFFERSIZE,passengersFile);

        fprintf(passengersErrors,"%s",passengersData);

        while((storeFgets = fgets(passengersData,BUFFERSIZE,passengersFile)) != NULL){

            Passenger * pBuffer = NULL;

            int tamanhoPassengersData = strlen(passengersData);

            char passengersDataClean[tamanhoPassengersData +1];

            strncpy(passengersDataClean,passengersData,tamanhoPassengersData);

            passengersDataClean[tamanhoPassengersData] = '\0';

            pBuffer = passengerCheck(passengersDataClean,uDatabase,fDatabase);

            if(pBuffer != NULL){
                insertPassenger(pDatabase,pBuffer);

            }else{ 
                fprintf(passengersErrors,"%s",passengersDataClean);
            }
        }

        fclose(passengersFile); // close
        passengersFile = NULL;
        free(filePathPErrors);  // free
        filePathPErrors = NULL;
        free(passengersData); // free
        passengersData = NULL;
        fclose(passengersErrors); // close
        passengersErrors = NULL;

    ffree((void **)&filePath);
    return pDatabase;
}


