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

static char * phoneNumberCheck(const char * line){
    if(line[0] == '\0') return NULL;
    char * n = atoi(line);
    return n;
}

static char sexCheck(const char * line){
    if(line[0] == '\0') return NULL;
    return line[0];
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
    Time * date = createTime();
    if(!date) return NULL;
    switch (line[10])
    {
    case '\0':
        setTime(date,yearCheck(line),monthCheck(line),dayCheck(line),0,0,0);
        return date;
        break;
        
    default:
        setTime(date,yearCheck(line),monthCheck(line),dayCheck(line),hourCheck(line),minuteCheck(line),secondsCheck(line));
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
static unsigned int hotelStarsCheck(const char * line){
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
static unsigned int reviewCheck(const char * line){
    if(line > '0' && line - '0' < 0 && line - '0' > 4 ) return false;
    return line - '0';
}

// *** The next 4 functions receive the full line ***  


static User * userCheck(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";",&saveptr);
    User * user = createUser();

    //check userId
    char * id = idCheck(token);
    if(!id){ free(aux); destroyUser(user); return NULL;}
    setUserId(user,id);
    free(id);
    TOKENIZE(token,saveptr);

    //check userName
    char * name = nameCheck(token);
    if(!name){ free(aux); destroyUser(user); return NULL;}
    setUserName(user,name);
    free(name);
    TOKENIZE(token,saveptr);

    //check userEmail
    char * email = emailCheck(token);
    if(!email) { free(aux); destroyUser(user); return NULL;}
    setUserEmail(user,email);
    free(email);
    TOKENIZE(token,saveptr);

    //check userPhone
    char * phone = phoneNumberCheck(token);
    if(!phone) { free(aux); destroyUser(user); return NULL;}
    setUserPhone(user,phone);
    free(phone);
    TOKENIZE(token,saveptr);
    
    //check userBday
    Time * userBday = dateCheck(token);
    if(!time) { free(aux); destroyUser(user); return NULL;}
    setUserBday(user,userBday);
    free(userBday);
    TOKENIZE(token,saveptr);

    //check userSex
    char * sex = sexCheck(token);
    if(!sex) { free(aux); destroyUser(user); return NULL;}
    setUserSex(user,sex);
    free(sex);
    TOKENIZE(token,saveptr);

    //check userPassaport
    char * passaport = passaportCheck(token);
    if(!passaport) { free(aux); destroyUser(user); return NULL;}
    setUserPassport(user,passaport);
    free(passaport);
    TOKENIZE(token,saveptr);

    //check userCountryCode
    char * countryCode = countryCheck(token);
    if(!countryCode) { free(aux); destroyUser(user); return NULL;}
    setUserCountryCode(user,countryCode);
    free(countryCode);
    TOKENIZE(token,saveptr);

    //check userAdress
    char * adress = addressCheck(token);
    if(!adress) { free(aux); destroyUser(user); return NULL;}
    setUserAddress(user,adress);
    free(adress);
    TOKENIZE(token,saveptr);

    //check userAccountCreation time
    Time * userAccountCreation = dateCheck(token);
    if(!userAccountCreation) { free(aux); destroyUser(user); return NULL;}
    setUserAccountCreation(user,userAccountCreation);
    free(userAccountCreation);
    TOKENIZE(token,saveptr);

    //check userPayMethod
    char * payMethod = pay_methodCheck(token);
    if(!payMethod) { free(aux); destroyUser(user); return NULL;}
    setUserPayMethod(user,payMethod);
    free(payMethod);
    TOKENIZE(token,saveptr);

    //check user accountStatus
    bool accStatus = accStatusCheck(token);
    if(!accStatus) { free(aux); destroyUser(user); return NULL;}
    setUserAccountStatus(user,accStatus);
    free(accStatus);
    
    free(aux);
    return user;
}

static Reservation * reservationCheck(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";",&saveptr);
    Reservation * reservation = createReservation();

    char * reservationId = idCheck(token);
    if(!reservationId){ free(aux); destroyReservation(reservation); return NULL;}
    setReservId(reservation,reservationId);
    free(reservationId);
    TOKENIZE(token,saveptr);

    char * reservationUserId = idCheck(token);
    if(!reservationUserId){ free(aux); destroyReservation(reservation); return NULL;}
    setReservUserId(reservation,reservationUserId);
    free(reservationUserId);
    TOKENIZE(token,saveptr);

    char * reservationHotelId = idCheck(token);
    if(!reservationHotelId){ free(aux); destroyReservation(reservation); NULL;}
    setReservHotelId(reservation,reservationHotelId);
    free(reservationHotelId);
    TOKENIZE(token,saveptr);

    char * reservationHotelName = nameCheck(token);
    if(!reservationHotelName){ free(aux); destroyReservation(reservation); NULL;}
    setReservHotelName(reservation,reservationHotelName);
    free(reservationHotelName);
    TOKENIZE(token,saveptr);

    unsigned int reservationHotelStars = hotelStarsCheck(token);
    if(!reservationHotelStars){ free(aux); destroyReservation(reservation); NULL;}
    setReservHotelStars(reservation,reservationHotelStars);
    TOKENIZE(token,saveptr);

    double reservationTax = taxCheck(token);
    if(!reservationTax){ free(aux); destroyReservation(reservation) ;return NULL;}
    setReservCityTax(reservation,reservationTax);
    TOKENIZE(token,saveptr);

    char * reservationAdress = addressCheck(token);
    if(!reservationAdress){ free(aux); destroyReservation(reservation) ;return NULL;}
    setReservHotelAddress(reservation,reservationAdress);
    free(reservationAdress);
    TOKENIZE(token,saveptr);

    Time * beginDate = dateCheck(token);
    if(!beginDate){ free(aux); destroyReservation(reservation); return NULL;}
    setReservBeginDate(reservation, beginDate);
    TOKENIZE(token,saveptr);

    Time * endDate = dateCheck(token);
    if(!endDate){ free(aux); destroyReservation(reservation); return NULL;}
    setReservEndDate(reservation, endDate);
    if(!datesCheck(beginDate,endDate)){ free(endDate); free(beginDate); free(aux); destroyReservation(reservation); return NULL;}
    free(endDate);
    free(beginDate);
    TOKENIZE(token,saveptr);

    double pricePerNight = pricePNightCheck(token);
    if(!pricePerNight){ free(aux); destroyReservation(reservation); return NULL;}
    setReservPricePerNight(reservation, pricePerNight);
    TOKENIZE(token,saveptr);

    bool includesBreakfast = breakfastCheck(token);
    if(!breakfastCheck){ free(aux); destroyReservation(reservation); return NULL;}
    setReservBreakfast(reservation, includesBreakfast);
    //free(includesBreakfast);
    TOKENIZE(token,saveptr);

    //RoomDetails
    setReservRoomDetails(reservation,token);
    TOKENIZE(token,saveptr);
    
    unsigned int rating = reviewCheck(token);
    if(!rating){ free(aux); destroyReservation(reservation); return NULL;}
    setReservRating(reservation,rating);
    TOKENIZE(token,saveptr);

    //Comment
    setReservComment(reservation,token);
    
    free(aux);
    return reservation;
}

static Flight * fligthCheck(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";",&saveptr);
    Flight * flight = createFlight();

    char * flightId = idCheck(token);
    if(!flightId){ free(aux); destroyFlight(flight); return NULL;}
    setFlightId(flight,flightId);
    free(flightId);
    TOKENIZE(token,saveptr);

    char * airline = nameCheck(token);
    if(!airline){ free(aux); destroyFlight(flight); return NULL;}
    setFlightAirline(flight,airline);
    free(airline);
    TOKENIZE(token,saveptr);

    char * planeModel = nameCheck(token);
    if(!planeModel){ free(aux); destroyFlight(planeModel); return NULL;}
    setFlightPlaneModel(flight,planeModel);
    free(planeModel);
    TOKENIZE(token,saveptr);

    /*unsigned int totalSeats = seatsCheck(token);
    if(!totalSeats){ free(aux); destroyFlight(totalSeats); return NULL;}
    setFlightTotalSeats(flight,totalSeats);
    free(totalSeats);
    TOKENIZE(token,saveptr);*/

    //Origin
    if(strlen(token)!=3){ free(aux); destroyFlight(flight); return NULL;}
    char * origin = strdup(token);
    setFlightOrigin(flight,origin);
    TOKENIZE(token,saveptr);

    //Destination
    if(!airportCheck(origin,token)){ free(origin); free(aux); destroyFlight(flight); return NULL;}
    free(origin);
    setFlightDestination(flight,token);
    TOKENIZE(token,saveptr);
    
    Time * sDepartDate = dateCheck(token);
    if(!sDepartDate){ free(aux); destroyFlight(flight); return NULL;}
    setFlightSDepartureDate(flight,sDepartDate);
    TOKENIZE(token,saveptr);

    Time * sArrivalDate = dateCheck(token);
    if(!sArrivalDate){ free(aux); destroyFlight(flight); return NULL;}
    setFlightSArrivalDate(flight,sArrivalDate);

    //sDepartDate before sArrivalDate
    if(datesCheck(sDepartDate,sArrivalDate)){ free(sArrivalDate); free(sDepartDate); free(aux); destroyFlight(flight); return NULL;}
    free(sArrivalDate);
    free(sDepartDate);
    TOKENIZE(token,saveptr);

    Time * rDepartDate = dateCheck(token);
    if(!rDepartDate){ free(aux); destroyFlight(flight); return NULL;}
    setFlightRDepartureDate(flight,rDepartDate);
    TOKENIZE(token,saveptr);

    Time * rArrivalDate = dateCheck(token);
    if(!rArrivalDate){ free(aux); destroyFlight(flight); return NULL;}
    setFlightRArrivalDate(flight,rArrivalDate);

    //rDepartDate before rArrivalDate
    if(datesCheck(rDepartDate,rArrivalDate)){ free(rArrivalDate); free(rDepartDate); free(aux); destroyFlight(flight); return NULL;}
    free(rArrivalDate);
    free(rDepartDate);
    TOKENIZE(token,saveptr);

    char * pilot = nameCheck(token);
    if(!pilot){ free(aux); destroyFlight(flight); return NULL;}
    setFlightPilot(flight,pilot);
    free(pilot);
    TOKENIZE(token,saveptr);

    char * copilot = nameCheck(token);
    if(!copilot){ free(aux); destroyFlight(flight); return NULL;}
    setFlightCopilot(flight,copilot);
    free(copilot);
    TOKENIZE(token,saveptr);

    setFlightNotes(flight,token);
    free(aux);
    return flight;

}

static Passanger * passangerCheck(const char * line){
    char * aux = strdup(line);
    char * token = NULL;
    char * saveptr = aux;
    token = strtok_r(aux,";",&saveptr);
    Passanger * passanger = createPassanger();

    char * passangerFlightId = idCheck(token);
    if(!passangerFlightId){ free(aux); destroyPassanger(passanger); return NULL;}
    setPassangerFlightId(passanger,passangerFlightId);
    free(passangerFlightId);
    TOKENIZE(token,saveptr);

    char * passangerUserId = idCheck(token);
    if(!passangerUserId){ free(aux); destroyPassanger(passanger); return NULL;}
    setPassangerUserId(passanger,passangerUserId);
    free(passangerUserId);

    free(aux);
    return passanger;
}