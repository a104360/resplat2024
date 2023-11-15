#ifndef TIME_H
#define TIME_H
#include <stdbool.h>



typedef struct time Time;

int getYear(Time *);
int getMon(Time *);
int getMday(Time *);
int getHour(Time *);
int getMin(Time *);
int getSec(Time *);

void initTime(Time *);

void destroyTime(Time *);

Time * createTime();

void setTime(Time *,int,int,int,int,int,int);

void copyTime(Time *,Time *);

bool compareTimes(Time *,Time*);

int numberOfDays(Time *,Time *);

#endif