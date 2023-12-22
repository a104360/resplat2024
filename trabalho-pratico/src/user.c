#include "../include/user.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>

typedef struct user{
    char * id;
    char * name;
    char * email;
    char * phone_number;
    struct time * birth_date;
    char sex;
    char * passport;
    char * country_code;
    char * address;
    struct time * account_creation;
    char * pay_method;
    bool account_status;
} User;





void initUser(User * user){
    if(!user) return;
    user->id = NULL;
    user->name = NULL;
    user->email = NULL;
    user->phone_number = NULL;
    user->birth_date = createTime();
    user->sex = '\0';
    user->passport = NULL;
    user->country_code = NULL;
    user->address = NULL;
    user->account_creation = createTime();
    user->pay_method = NULL;
    user->account_status = false;
}

User * createUser(){
    User * u = NULL;
    u = malloc(sizeof(struct user));
    initUser(u);    
    return u;

}
void destroyUser(User *user) {
    if(user) {
        ffree(user->id);
        ffree(user->name);
        ffree(user->email);
        ffree(user->phone_number);
        if(user->sex) user->sex = '\0';
        ffree(user->passport);
        ffree(user->country_code);
        ffree(user->address);
        ffree(user->pay_method);
        if(user->account_creation != NULL) destroyTime(user->account_creation);
        if(user->birth_date != NULL) destroyTime(user->birth_date);
        
        ffree(user);
    }
}



void setUserId(User * user, const char * line){
    if(line == NULL) return;
    if (user == NULL) return;

    if (user->id != NULL) {
        if(strlen(line) > strlen(user->id)){
            char * temp = realloc(user->id,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->id = temp;
            return;
        }else{
            strncpy(user->id,line,strlen(user->id));
            user->id[strlen(user->id)] = '\0';
            return;
        }
    }
    if (line) user->id = strdup(line); 
}


 char * getUserId(User * user){
    if(user->id){
        char * aux = strdup(user->id);
        return aux;
    }
    return NULL;
}


  void setUserName(User * user,const char * line){
    if(line == NULL) return;
    if(user->name) {
        if(strlen(line) > strlen(user->name)){
            char * temp = realloc(user->name,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->name = temp;
            return;
        }else{
            strncpy(user->name,line,strlen(user->name));
            user->name[strlen(user->name)] = '\0';
            return;
        }
    }
    if(line) user->name =strdup(line);
}

 char * getUserName(User * user){
     if(user->name){
        char * aux =strdup(user->name);
        return aux;
    }
    return NULL;
}


 void setUserEmail(User * user,const char * line){
    if(line == NULL) return;
    if(user->email != NULL) {
        if(strlen(line) > strlen(user->email)){
            char * temp = realloc(user->email,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->email = temp;
            return;
        }else{
            strncpy(user->email,line,strlen(user->email));
            user->email[strlen(user->email)] = '\0';
            return;
        }
    }
    user->email = strdup(line);
}

 char * getUserEmail(User * user){
    if(user->email != NULL){
        char * aux = strdup(user->email);
        return aux;
    }
    return NULL;
}

 void setUserPhone(User * user,const char * line){
    if(line == NULL) return;
    if(user == NULL) return;
    if(user->phone_number != NULL){
        if(strlen(line) > strlen(user->phone_number)){
            char * temp = realloc(user->phone_number,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->phone_number = temp;
            return;
        }else{
            strncpy(user->phone_number,line,strlen(user->phone_number));
            user->phone_number[strlen(user->phone_number)] = '\0';
            return;
        }
    }
    user->phone_number = strdup(line);
}

/*
void setUserPhone2(User * user, const char * line){
    if(user->phone_number != NULL) 
        ffree(user->phone_number);
        user->phone_number = NULL;

    // Pass 'phone' instead of 'token'
    char * phone = phoneNumberCheck(line);
    if(!phone) {
        fprintf(stderr, "Error checking phone number\n");
        return;  // or handle the error appropriately
    }

    user->phone_number = strdup(phone);
    ffree(phone);
}
*/

 char * getUserPhone(User * user){
    if(user->phone_number){
        char * aux = strdup(user->phone_number);
        return aux;
    }
    return NULL;
}



  void setUserBday(User * user ,Time * tempo){
    if(!user->birth_date) user->birth_date = createTime();
    copyTime(user->birth_date,tempo);
}

 Time * getUserBday(User * user){
    if(user->birth_date){
        Time * aux = createTime();
        copyTime(aux,user->birth_date);
        return aux;
    }
    return NULL;
}


void setUserSex(User * user ,const char line){
    user->sex = (char) line;
}

 char getUserSex(User * user){
    return user->sex;
}


  void setUserPassport(User * user ,const char * line){
    if(user == NULL) return;
    if(line == NULL) return;
    if(user->passport){
        if(strlen(line) > strlen(user->passport)){
            char * temp = realloc(user->passport,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->passport = temp;
            return;
        }else{
            strncpy(user->passport,line,strlen(user->passport));
            user->passport[strlen(user->passport)] = '\0';
            return;
        }
    }
    user->passport =strdup(line);
}

 char * getUserPassport(User * user){
    if(user->passport){
        char * aux =strdup(user->passport);
        return aux;
    }
    return NULL;
}


 void setUserCountryCode(User * user ,const char * line){
    if(user == NULL) return;
    if(line == NULL) return;
    if(user->country_code) {
        if(strlen(line) > strlen(user->country_code)){
            char * temp = realloc(user->country_code,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->country_code = temp;
            return;
        }else{
            strncpy(user->country_code,line,strlen(user->country_code));
            user->country_code[strlen(user->country_code)] = '\0';
            return;
        }
    }
    user->country_code =strdup(line);
}

 char * getUserCountryCode(User * user){
    if(user->country_code){
        char * aux =strdup(user->country_code);
        return aux;
    }
    return NULL;
}


 void setUserAddress(User * user ,const char * line){
    if(user == NULL) return;
    if(line == NULL) return;
    if(user->address) {
        if(strlen(line) > strlen(user->address)){
            char * temp = realloc(user->address,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->address = temp;
            return;
        }else{
            strncpy(user->address,line,strlen(user->address));
            user->address[strlen(user->address)] = '\0';
            return;
        }
    }
    user->address = strdup(line);
}

 char * getUserAddress(User * user){
    if(user->address){
        char * aux = strdup(user->address);
        return aux;
    }
    return NULL;
}


void setUserAccountCreation(User * user ,Time *tempo){
    if(user == NULL) return;
    if(tempo == NULL) return;
    if(user->account_creation == NULL) user->account_creation = createTime();
    copyTime(user->account_creation,tempo);
}

 Time * getUserAccountCreation(User * user){
    if(user->account_creation){
        Time * t = createTime();
        copyTime(t,user->account_creation);
        return t;
    }
    return NULL;
}


void setUserPayMethod(User * user ,const char * line){
    if(user == NULL) return;
    if(line == NULL) return;
    if(user->pay_method) {
        if(strlen(line) > strlen(user->pay_method)){
            char * temp = realloc(user->pay_method,strlen(line)+ 1);
            strncpy(temp,line,strlen(line));
            temp[strlen(line)] = '\0';
            user->pay_method = temp;
            return;
        }else{
            strncpy(user->pay_method,line,strlen(user->pay_method));
            user->pay_method[strlen(user->pay_method)] = '\0';
            return;
        }
    }
    user->pay_method = strdup(line);
}

 char * getUserPayMethod(User * user){
    if(user->pay_method){
        char * aux =strdup(user->pay_method);
        return aux;
    }
    return NULL;
}


  void setUserAccountStatus(User * user ,const bool status){
    if(user == NULL) return;
    user->account_status = status;

}

 bool getUserAccountStatus(User * user){
    if(user){
        return user->account_status;
    }
    return false;
} 


int getUserAge(User * user){
    Time * userBday = getUserBday(user);
    int n = PYEAR - (getYear(userBday));
    if(PMON >= getMon(userBday)){
        if(PDAY >= getMday(userBday)){
            destroyTime(userBday);
            return n + 1;
        }
    }
    destroyTime(userBday);
    return n;
}

void copyUser(User * dest,User * src){
    if(src == NULL) return;
    char * uId = getUserId(src);
    char * uName = getUserName(src);
    char * uEmail = getUserEmail(src);
    char * uPhone = getUserPhone(src);
    char * uPassport = getUserPassport(src);
    char * uCountry = getUserCountryCode(src);
    char * uAddress = getUserAddress(src);
    char * uPay = getUserPayMethod(src);
    Time * bDay = getUserBday(src);
    Time * accCreation = getUserAccountCreation(src);
    setUserId(dest,uId);
    setUserName(dest,uName);
    setUserEmail(dest,uEmail);
    setUserPhone(dest,uPhone);
    setUserBday(dest,bDay);
    setUserSex(dest,getUserSex(src));
    setUserPassport(dest,uPassport);
    setUserCountryCode(dest,uCountry);
    setUserAddress(dest,uAddress);
    setUserAccountCreation(dest,accCreation);
    setUserPayMethod(dest,uPay);
    setUserAccountStatus(dest,getUserAccountStatus(src));
    ffree(uId);
    ffree(uName);
    ffree(uEmail);
    ffree(uPhone);
    ffree(uPassport);
    ffree(uCountry);
    ffree(uAddress);
    ffree(uPay);
    ffree(bDay);
    ffree(accCreation);
}