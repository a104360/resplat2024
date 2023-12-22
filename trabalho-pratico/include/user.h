#ifndef USER_H
#define USER_H
#include "../include/time.h" 
#include "../include/database.h"
#include <stdbool.h>

typedef Database Users;

typedef struct user User;

User * createUser();
void initUser(User *);
void destroyUser(User *);

void setUserId(User *, const char *);
char * getUserId(User *);

void setUserName(User *, const char *);
char * getUserName(User *);

void setUserEmail(User *, const char *);
char * getUserEmail(User *);

void setUserPhone(User *,const char *);
char * getUserPhone(User *);

void setUserBday(User *,Time *);
Time * getUserBday(User *);

void setUserSex(User *, const char);
char getUserSex(User *);

void setUserPassport(User *, const char *);
char * getUserPassport(User *);

void setUserCountryCode(User *, const char *);
char * getUserCountryCode(User *);

void setUserAddress(User *, const char *);
char * getUserAddress(User *);

void setUserAccountCreation(User *,Time *);
Time * getUserAccountCreation(User *);

void setUserPayMethod(User *, const char *);
char * getUserPayMethod(User *);

void setUserAccountStatus(User *, const bool);
bool getUserAccountStatus(User *);

int getUserAge(User *);

void copyUser(User *,User *);

#endif