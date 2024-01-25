#include "../include/time.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct time{
    short int sec;         /* seconds,  range 0 to 59          */
    short int min;         /* minutes, range 0 to 59           */
    short int hour;        /* hours, range 0 to 23             */
    short int mday;        /* day of the month, range 1 to 31  */
    short int mon;         /* month, range 1 to 12             */
    short int year;        /* The number of years since 0      */
} Time;


int getYear(Time * time){
    return time->year;
}
int getMon(Time * time){
    return time->mon;
}
int getMday(Time * time){
    return time->mday;
}
int getHour(Time * time){
    return time->hour;
}
int getMin(Time * time){
    return time->min;
}
int getSec(Time * time){
    return time->sec;
}


void initTime(Time * tempo){
    tempo->hour = 0;
    tempo->min = 0;
    tempo->sec = 0;
    tempo->mday = 0;
    tempo->year = 0;
    tempo->mon = 0;
}

void destroyTime(Time *time) {
    if(time == NULL) return; 
    ffree((void **) &time);
}

Time * createTime(){
    Time * t = malloc(sizeof(struct time));
    initTime(t);
    return t;
}

void setTime(Time *t,int year,int mon,int mday,int hour,int min,int sec){
    if(t == NULL) return;
    t->year = year;
    t->mon = mon;
    t->mday = mday;
    t->hour = hour;
    t->min = min;
    t->sec = sec;
}

void copyTime(Time * t,Time * aux){
    if(t == NULL || aux == NULL) return;
    t->year = aux->year;
    t->mday = aux->mday;
    t->mon = aux->mon;
    t->hour = aux->hour;
    t->min = aux->min;
    t->sec = aux->sec;
}


int compareTimes(Time *t1,Time*t2){
    if(t2 == NULL || t1 == NULL) return false; 
    if(t1->year != t2->year){
        if(t1->year > t2->year) return false;
        else return true;
    }
    if(t1->mon != t2->mon){
        if(t1->mon > t2->mon) return false;
        else return true;
    }
    if(t1->mday != t2->mday){
        if(t1->mday > t2->mday) return false;
        else return true;
    }
    if(t1->hour != t2->hour){
        if(t1->hour > t2->hour) return false;
        else return true;
    }
    if(t1->min != t2->min){
        if(t1->min > t2->min) return false;
        else return true;
    }
    if(t1->sec != t2->sec){
        if(t1->sec > t2->sec) return false;
        else return true;
    }
    return 10;
}


int numberOfDays(Time * start,Time * end){
    if(end->mday > start->mday) return (end->mday - start->mday);
    else return(start->mday - end->mday);
}



char * timeToString(Time * time){
    if(time == NULL) return NULL;
    
    if(time->hour == 0 && time->min == 0 && time->sec == 0){
        char * string = malloc(sizeof(char) * 11);
        if(string == NULL) return NULL;
        snprintf(string,11,"%hd/%02hd/%02hd",time->year,time->mon,time->mday);
        return string;
    }


    char* dateString = (char*)malloc(20); // Sufficient space for "YYYY-MM-DD HH:MM:SS\0"
    
    if (dateString == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

        snprintf(dateString, 20, "%hd/%02hd/%02hd %02hd:%02hd:%02hd",
                time->year, time->mon, time->mday,
                time->hour, time->min, time->sec);

    return dateString;
}

