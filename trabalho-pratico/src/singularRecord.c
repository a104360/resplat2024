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
    for(int i = 0;i < num;temp->list[i] = 0,i++);
    temp->size = 0;
}

SingularRecord * createSRecord(int num){
    SingularRecord * temp = malloc(sizeof(struct sRecord));
    initSRecord(temp,num);
    return temp;
}

void setSRecordName(SingularRecord * temp,int position,char * name){
    if(temp->names[position]) ffree(temp->names[position]);
    temp->names[position] = strdup(name);
}
char *getSRecordName(SingularRecord * temp,int position){
    if(!temp->names[position]) return NULL;
    return strdup(temp->names[position]);
}

char ** getSRecordNames(SingularRecord * temp){
    if(temp->size == 0){
        char ** sRecord = malloc(sizeof(char *));
        sRecord[0] = NULL;
        return sRecord;
    }
    char ** sRecord = malloc(sizeof(char *) * temp->size);
    for(int i = 0;i < temp->size;i++){
        if(temp->names[i]) sRecord[i] = temp->names[i];
        else sRecord[i] = NULL;
    }
    return sRecord;
}


void setSRecordListElement(SingularRecord * temp,int position,int num){
    temp->list[position] = num;
}

int getSRecordListElement(SingularRecord * temp,int position){
    return temp->list[position];
}

void setSRecordSize(SingularRecord * temp,int num){
    temp->size = num;
}
int getSRecordSize(SingularRecord * temp){
    return temp->size;
}

void destroySRecord(SingularRecord * temp){
    for(int i = 0;i < temp->size;ffree(temp->names[i]),i++);
    ffree(temp->list);
    ffree(temp);
}
