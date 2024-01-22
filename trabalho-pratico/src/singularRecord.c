#include "../include/singularRecord.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>

typedef struct sRecord{
    char ** names;
    int * list;
    int size;
} SingularRecord;

static void initSRecord(SingularRecord * temp,int num){
    temp->names = malloc(sizeof(char *) * num);
    for(int i = 0;i < num;temp->names[i] = NULL,i++);
    temp->list = malloc(sizeof(int) * num);
    for(int i = 0;i < num;temp->list[i] = -1,i++);
    temp->size = 0;
}

SingularRecord * createSRecord(int num){
    SingularRecord * temp = malloc(sizeof(struct sRecord));
    initSRecord(temp,num);
    return temp;
}

void setSRecordName(SingularRecord * temp,int position,char * name){
    if(temp->names[position]) ffree((void **)&temp->names[position]);
    temp->names[position] = strdup(name);
}
char *getSRecordName(SingularRecord * temp,int position){
    if(!temp->names[position]) return NULL;
    return strdup(temp->names[position]);
}

int getSRecordNamePosition(SingularRecord * temp,const char * name){
    int i = 0;
    while(i < temp->size){
        if(!strcoll(name,temp->names[i])) return i;
        i++;
    }
    return -1;
}

char ** getSRecordNames(SingularRecord * temp){
    if(temp->size == 0){
        char ** sRecord = malloc(sizeof(char *));
        sRecord[0] = NULL;
        return sRecord;
    }
    char ** sRecord = malloc(sizeof(char *) * temp->size);
    for(int i = 0;i < temp->size;i++){
        if(temp->names[i]) sRecord[i] = strdup(temp->names[i]);
        else sRecord[i] = NULL;
    }
    return sRecord;
}


void setSRecordListElement(SingularRecord * temp,int position,int num){
    temp->list[position] = num;
}

void incSRecordNameElement(SingularRecord * temp,const char * name){
    int i = 0;
    while(i < temp->size){
        if(!strcoll(temp->names[i],name)){
            temp->list[i]++;
            return;
        }
        i++;
    }
    if(i < temp->size){
        setSRecordName(temp,i,(char *) name);
        setSRecordListElement(temp,i,1);
        return;
    }
    
}

int getSRecordListElement(SingularRecord * temp,int position){
    return temp->list[position];
}

void setSRecordSize(SingularRecord * temp,int num){
    temp->size = num;
}

void incSRecordSize(SingularRecord * temp){
    temp->size++;
}

void incSRecordListElement(SingularRecord * temp,int position){
    temp->list[position]++;
}
int getSRecordSize(SingularRecord * temp){
    return temp->size;
}

void destroySRecord(SingularRecord ** temp){
    for(int i = 0;i < (*temp)->size;ffree((void **)&(*temp)->names[i]),i++);
    ffree((void **)&(*temp)->names);
    ffree((void **)&(*temp)->list);
    ffree((void **)&(*temp));
}
