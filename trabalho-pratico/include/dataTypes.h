#ifndef DATATYPES_H
#define DATATYPES_H

enum structs;

typedef struct time Time;

typedef struct user User;

typedef struct flight Flight;

typedef struct reservation Reservation;

typedef struct passanger Passanger;




Time * createTime();

void initTime(Time *);

void setTime(Time *,Time *);

void destroyTime(Time *); 



User * createUser();

void initUser(User *);

void destroyUser(User *);



Flight * createFlight();

void initFlight(Flight *);

void destroyFlight(Flight *);



Reservation * createReservation();

void initReservation(Reservation *);

void destroyReservation(Reservation *);




Passanger * createPassanger();

void initPassanger(Passanger *);

void destroyPassanger(Passanger *);





void setUserId(User *,char *);
char * getUserId(User *);

void setUserName(User *,char *);
char * getUserName(User *);

void setUserEmail(User *,char *);
char * getUserEmail(User *);

void setUserBday(User *,Time *);
Time * getUserBday(User *);

void setUserSex(User *,char *);
char * getUserSex(User *);

void setUserPassport(User *,char *);
char * getUserPassaport(User *);

void setUserCountryCode(User *,char *);
char * getUserCountryCode(User *);

void setUserAddress(User *,char *);
char * getUserAddress(User *);

void setUserAccountCreation(User *,Time *);
Time * getUserAccountCreation(User *);

void setUserPayMethod(User *,char *);
char * getUserPayMethod(User *);

void setUserAccountStatus(User *,bool);
bool getUserAccountStatus(User *);














void setFlightId(Flight *,char *);
char *getFlightId(Flight *);
    
void setFlightAirline(Flight *, char *);
char *getFlightAirline(Flight *);

void setFlightPlaneModel(Flight *,char *);
char *getFlightPlaneModel(Flight *);

void setFlightTotalSeats(Flight *,unsigned int);
unsigned int getFlightTotalSeats(Flight *);

void setFlightOrigin(Flight *,char *);
char *getFlightOrigin(Flight *);

void setFlightDestination(Flight *,char *);
char *getFlightDestination(Flight *);

void setFlightSDepartureDate(Flight *,Time *);
Time *getFlightSDepartureDate(Flight *);

void setFlightSArrivalDate(Flight *,Time *);
Time *getFlightSArrivalDate(Flight *);

void setFlightRDepartureDate(Flight *, Time *);
Time *getFlightRDepartureDate(Flight *);

void setFlightRArrivalDate(Flight *,Time *);
Time *getFlightRArrivalDate(Flight *);

void setFlightPilot(Flight *,char *);
char *getFlightPilot(Flight *);

void setFlightCopilot(Flight *,char *);
char *getFlightCopilot(Flight *);

void setFlightNotes(Flight *,char *);
char *getFlightNotes(Flight *);













void setReservId(Reservation *,char *);
char *getReservId(Reservation *);

void setReservUserId(Reservation *, char *);
char *getReservUserId(Reservation *);

void setReservHotelId(Reservation *, char *);
char *getReservHotelId(Reservation *);

void setReservHotelName(Reservation *,char *);
char *getReservHotelName(Reservation *);

void setReservHotelStars(Reservation *,unsigned int);
unsigned int getReservHotelStars(Reservation *);

void setReservCityTax(Reservation *,double);
double getReservCityTax(Reservation *);

void setReservHotelAddress(Reservation *, char *);
char *getReservHotelAddress(Reservation *);

void setReservBeginDate(Reservation*,Time *);
Time *getReservBeginDate(Reservation *);

void setReservEndDate(Reservation *,Time *);
Time *getReservEndDate(Reservation *);

void setReservPricePerNight(Reservation *,double);
double getReservPricePerNight(Reservation *);

void setReservBreakfast(Reservation *,bool);
bool getReservBreakfast(Reservation *);

void setReservRoomDetails(Reservation *,char *);
char *getReservRoomDetails(Reservation *);

void setReservRating(Reservation *,unsigned int);
unsigned int getReservRating(Reservation *);

void setReservComment(Reservation *,char *);
char *getReservComment(Reservation *);







void setPassangerFlightId(Passanger *,char *);
char *getPassangerFlightId(Passanger *);

void setPassangerUserId(Passanger *,char *);
char *getPassangerUserId(Passanger *);

#endif