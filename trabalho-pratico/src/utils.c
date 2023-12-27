#include "../include/utils.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct auxiliar{
    char ** names;
    int * list;
    int size;
} Auxiliar;

static void initAux(Auxiliar * temp,int num){
    temp->names = malloc(sizeof(char *) * num);
    for(int i = 0;i < num;temp->names[i] = NULL,i++);
    temp->list = malloc(sizeof(int) * num);
    for(int i = 0;i < num;temp->list[i] = 0,i++);
}

Auxiliar * createAux(int num){
    Auxiliar * temp = malloc(sizeof(struct auxiliar));
    initAux(temp,num);
    return temp;
}

void setAuxName(Auxiliar * temp,int position,char * name){
    if(temp->names[position]) ffree(temp->names[position]);
    temp->names[position] = strdup(name);
}
char *getAuxName(Auxiliar * temp,int position){
    return strdup(temp->names[position]);
}

void setAuxListElement(Auxiliar * temp,int position,int num){
    temp->list[position] = num;
}

int getAuxListElement(Auxiliar * temp,int position){
    return temp->list[position];
}

void setAuxSize(Auxiliar * temp,int num){
    temp->size = num;
}
int getAuxSize(Auxiliar * temp){
    return temp->size;
}

void destroyAux(Auxiliar * temp){
    for(int i = 0;i < temp->size;ffree(temp->names[i]),i++);
    ffree(temp->list);
    ffree(temp);
}





typedef struct integers {
    // keeps names
    char ** names;
    // keeps the list of lists of delays
    int ** list;
    // Number of different airports
    int intSize;
    // List of sizes of the delays arrays
    int * listSize;
} Integers;


static void initIntegers(Integers * integers,int num){
    integers->names = malloc(sizeof(char *) * num);
    for(int i = 0;i < num;integers->names[i] = NULL,i++)
    integers->list = malloc(sizeof(int *) * num);
    for(int i = 0;i < num;i++) {
        integers->list[i] = malloc(sizeof(int) * 300);
        for(int j = 0; j < 300;j++){
            integers->list[i][j] = -1;
        }
    }
    integers->intSize = 0;
    integers->listSize = malloc(sizeof(int) * num);
    for(int i = 0;i < num;i++){
        integers->listSize[i] = 0;
    }
}

Integers * createIntegers(int num){
    Integers * integers = malloc(sizeof(struct integers));
    initIntegers(integers,num);
    return integers;
}


void setIntNamesElement(Integers * temp,int position,char * element){
    if(!element) return;
    if(temp->names[position]) ffree(temp->names[position]);
    temp->names[position] = strdup(element);
}


char * getIntNamesElement(Integers * temp ,int position){
    if(temp->names[position]) return strdup(temp->names[position]);
    return NULL;
}


void setIntListElement(Integers * temp,int arrayPosition,int delayPosition,int num){
    temp->list[arrayPosition][delayPosition] = num;
}


int getIntListElement(Integers * temp,int arrayPosition,int delayPosition){
    return temp->list[arrayPosition][delayPosition];
}

void setIntList(Integers * temp,int position,int * array,int size){
    temp->listSize[position] = size;
    for(int i = 0;i < size;temp->list[position][i] = array[i],i++);
}

int * getIntList(Integers * temp,int position){
    int size = getIntListSize(temp,position);
    int * aux = malloc(sizeof(int) * size);
    for(int i = 0;i < size;aux[i] = temp->list[position][i],i++);
    return aux;
}


void incIntListSize(Integers * temp,int position){
    temp->listSize[position]++;
}
void decIntListSize(Integers * temp,int position){
    temp->listSize[position]--;
}
int getIntListSize(Integers * temp,int position){
    return temp->listSize[position];
}

void incIntSize(Integers * temp){
    temp->intSize++;
}
void decIntSize(Integers * temp){
    temp->intSize--;
}
int getIntSize(Integers * temp){
    return temp->intSize;
}

void destroyIntegers(Integers * temp){
    ffree(temp->list);
    ffree(temp);
}


typedef struct time{
    int sec;         /* seconds,  range 0 to 59          */
    int min;         /* minutes, range 0 to 59           */
    int hour;        /* hours, range 0 to 23             */
    int mday;        /* day of the month, range 1 to 31  */
    int mon;         /* month, range 1 to 12             */
    int year;        /* The number of years since 0      */
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
    ffree(time);
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
        snprintf(string,11,"%d/%02d/%02d",time->year,time->mon,time->mday);
        return string;
    }


    char* dateString = (char*)malloc(20); // Sufficient space for "YYYY-MM-DD HH:MM:SS\0"
    
    if (dateString == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

        snprintf(dateString, 20, "%d/%02d/%02d %02d:%02d:%02d",
                time->year, time->mon, time->mday,
                time->hour, time->min, time->sec);

    return dateString;
}





void ffree(void * ptr){
    if(ptr){
        free(ptr);
        ptr = NULL;
    }
}



void initArrays(void *** ptr, int max){
    *ptr = (void **)malloc(sizeof(void *) * max);
}