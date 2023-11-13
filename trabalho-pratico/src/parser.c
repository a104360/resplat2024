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



 char * idCheck(const char * line){
    CHECKLEN(line);
}

// Free necessary
 char * nameCheck(const char * line){
    CHECKLEN(line);
}

 char * phoneNumberCheck(const char * line){
    if(line[0] == '\0') return NULL;
    char * n = strdup(line);
    return n;
}

 char sexCheck(const char * line){
    if(line[0] == 'm' || line[0] == 'M') return 'M';
    if(line[0] == 'f' || line[0] == 'F') return 'F';
    return line[0];
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
// tm.year = years after 1900
// Example : the year 2023 would appear on tm.year as 123
 int yearCheck(const char * line){
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
 int monthCheck(const char * line){
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
 int dayCheck(const char * line){
    if(line[8] < '0' || line[8] > '3') return false;
    if(line[9] < '0' && line[9] > '9') return false;
    char * aux = malloc(sizeof(char) * 2);
    aux[0] = line[8];
    aux[1] = line[9]; 
    int n = atoi(aux);
    return n;
}

// format : nnnn/nn/nn (0 <= n <= 9)
 Time * dateCheck(const char * line){
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
    free(date);
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
 int minuteCheck(const char * line){
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
 int secondsCheck(const char * line){
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
    char * email = malloc(sizeof(strlen(line)));
    strcpy(email,line);
    return email;
}

// format : LL (L is a letter)
 char * countryCheck(const char * line){
    if(!line) return NULL;
    if(line[2] == '\0') return NULL;
    if(line[3] == '\0'){
        char * country = malloc(sizeof(char) * 2);
        strcpy(country,line);
        return country;
    }
    return NULL;
}

// active vs inactive (all varitations)
 bool accStatusCheck(const char * line){
    char * aux = strdup(line);
    ALLVAR(aux);
    if(!strcmp(line,"active") || !strcmp(line,"inactive")) return true;
    return false;
}

// total_seats must not be less than the number of passangers
 unsigned int seatsCheck(const char * sold){
    int virtual = atoi(sold);
    return virtual;
}

// length == 3 && all variations
 bool airportCheck(const char * departure,const char * arrival){
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
 unsigned int hotelStarsCheck(const char * line){
    if((int) line[0] >= '1' && (int) line[0] <= '5') return (int) line[0] - '0';
    return false;
}

// int tax : 0 <= tax
// if invalid, functions returns -1
 double taxCheck(const char * line){
    double n = atof(line);
    if(n < 0) return -1;
    return n;
}

// int price : 0 < price
// if invalid, functions returns -1
 double pricePNightCheck(const char * line){
    double n = atof(line);
    if(n <= 0) return -1;
    return n;
}

// bool breakfast : if(false){"f","false",0,""} else {"t","true","1"}
 bool breakfastCheck(const char * line){
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
 unsigned int reviewCheck(const char * line){
    if((int) line[0] > '0' && (int) line[0] - '0' < 0 && (int) line[0] - '0' > 4 ) return false;
    return (int) line[0] - '0';
}

// *** The next 4 functions receive the full line ***  


 User * userCheck(const char * line){
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
    if(userBday == NULL) { free(aux); destroyUser(user); return NULL;}
    setUserBday(user,userBday);
    destroyTime(userBday);
    TOKENIZE(token,saveptr);

    //check userSex
    char sex = sexCheck(token);
    if(sex == '\0') { free(aux); destroyUser(user); return NULL;}
    setUserSex(user,(char) sex);
    sex = '\0';
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
    destroyTime(userAccountCreation);
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
    
    free(aux);
    return user;
}

 Reservation * reservationCheck(const char * line){
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
    if(!compareTimes(beginDate,endDate)){ destroyTime(beginDate); destroyTime(endDate); free(aux); destroyReservation(reservation); return NULL;}
    destroyTime(endDate);
    destroyTime(beginDate);
    TOKENIZE(token,saveptr);

    double pricePerNight = pricePNightCheck(token);
    if(!pricePerNight){ free(aux); destroyReservation(reservation); return NULL;}
    setReservPricePerNight(reservation, pricePerNight);
    TOKENIZE(token,saveptr);

    bool includesBreakfast = breakfastCheck(token);
    if(!includesBreakfast){ free(aux); destroyReservation(reservation); return NULL;}
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

 Flight * fligthCheck(const char * line){
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
    if(!planeModel){ free(planeModel); free(aux); destroyFlight(flight); return NULL;}
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
    if(compareTimes(sDepartDate,sArrivalDate) == false){ destroyTime(sArrivalDate); destroyTime(sDepartDate); free(aux); destroyFlight(flight); return NULL;}
    destroyTime(sArrivalDate);
    destroyTime(sDepartDate);
    TOKENIZE(token,saveptr);

    Time * rDepartDate = dateCheck(token);
    if(!rDepartDate){ free(aux); destroyFlight(flight); return NULL;}
    setFlightRDepartureDate(flight,rDepartDate);
    TOKENIZE(token,saveptr);

    Time * rArrivalDate = dateCheck(token);
    if(!rArrivalDate){ free(aux); destroyFlight(flight); return NULL;}
    setFlightRArrivalDate(flight,rArrivalDate);

    //rDepartDate before rArrivalDate
    if(compareTimes(rDepartDate,rArrivalDate) == false){ free(rArrivalDate); free(rDepartDate); free(aux); destroyFlight(flight); return NULL;}
    destroyTime(rArrivalDate);
    destroyTime(rDepartDate);
    TOKENIZE(token,saveptr);

    char * pilot = nameCheck(token);
    if(!pilot){ free(pilot); free(aux); destroyFlight(flight); return NULL;}
    setFlightPilot(flight,pilot);
    free(pilot);
    TOKENIZE(token,saveptr);

    char * copilot = nameCheck(token);
    if(!copilot){ free(copilot); free(aux); destroyFlight(flight); return NULL;}
    setFlightCopilot(flight,copilot);
    free(copilot);
    TOKENIZE(token,saveptr);

    setFlightNotes(flight,token);
    free(aux);
    return flight;

}

 Passanger * passangerCheck(const char * line){
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