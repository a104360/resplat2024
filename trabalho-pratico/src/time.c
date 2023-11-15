#include "../include/time.h"
#include <stdbool.h>
#include <glib.h>

typedef struct time{
    int sec;         /* seconds,  range 0 to 59          */
    int min;         /* minutes, range 0 to 59           */
    int hour;        /* hours, range 0 to 23             */
    int mday;        /* day of the month, range 1 to 31  */
    int mon;         /* month, range 0 to 11             */
    int year;        /* The number of years since 0      */
} Time;


int getYear(Time * time){
    return time->year;
}
int getMon(Time * time){
    time->mon;
}
int getMday(Time * time){
    time->mday;
}
int getHour(Time * time){
    time->hour;
}
int getMin(Time * time){
    time->min;
}
int getSec(Time * time){
    time->sec;
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
    initTime(time);
    g_free(time);
}

 Time * createTime(){
    Time * t = g_malloc(sizeof(struct time));
    initTime(t);
    return t;
}

  void setTime(Time *t,int year,int mon,int mday,int hour,int min,int sec){
    t->year = year;
    t->mon = mon;
    t->mday = mday;
    t->hour = hour;
    t->min = min;
    t->sec = sec;
}

  void copyTime(Time * t,Time * aux){
    t->year = aux->year;
    t->mday = aux->mday;
    t->mon = aux->mon;
    t->hour = aux->hour;
    t->min = aux->min;
    t->sec = aux->sec;
}

 bool compareTimes(Time *t1,Time*t2){

    if(t1->year != t2->year)
        if(t1->year > t2->year) return false;

    if(t1->mon != t2->mon)
        if(t1->mon > t2->mon) return false;
    
    if(t1->mday != t2->mday)
        if(t1->mday > t2->mday) return false;
    
    if(t1->hour != t2->hour)
        if(t1->hour > t2->hour) return false;

    if(t1->min != t2->min)
        if(t1->min > t2->min) return false;
    
    if(t1->sec != t2->sec)
        if(t1->sec > t2->sec) return false;
    
    return true;
}

int numberOfDays(Time * start,Time * end){
    return (365 * (end->year - start->year)) + (30 * (end->mon - start->mon)) + (end->mday - start->mday);
}

