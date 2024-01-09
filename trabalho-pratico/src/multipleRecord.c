#include "../include/multipleRecord.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <string.h>

typedef struct mRecord {
    // keeps names
    char ** names;
    
    // keeps the list of lists of delays
    int ** list;
    
    // Number of different airports
    int size;

    // List of sizes of the delays arrays
    int * listSize;

    // Keeps the maximum number (allocated) of diferent names
    int max;
} MultipleRecord;


static void initMRecord(MultipleRecord * MRecord, int num) {
    MRecord->names = malloc(sizeof(char *) * num);
    for (int i = 0; i < num; i++)
        MRecord->names[i] = NULL;

    MRecord->list = (int **)malloc(sizeof(int *) * num);
    for (int i = 0; i < num; i++) {
        MRecord->list[i] = malloc(sizeof(int) * 300);
        for (int j = 0; j < 300; j++) {
            MRecord->list[i][j] = -1;
        }
    }

    MRecord->size = 0;
    MRecord->listSize = malloc(sizeof(int) * num);
    for (int i = 0; i < num; i++) {
        MRecord->listSize[i] = 0;
    }
    MRecord->max = num;
}

MultipleRecord * createMRecord(int num){
    MultipleRecord * MRecord = malloc(sizeof(struct mRecord));
    initMRecord(MRecord,num);
    return MRecord;
}


void setMRecordNamesElement(MultipleRecord * temp,int position,char * element){
    if(!element) return;
    if(temp->names[position]) ffree((void **)&temp->names[position]);
    temp->names[position] = strdup(element);
}


char * getMRecordNamesElement(MultipleRecord * temp ,int position){
    if(temp->names[position]) return strdup(temp->names[position]);
    return NULL;
}


void setMRecordListElement(MultipleRecord * temp,int arrayPosition,int delayPosition,int num){
    temp->list[arrayPosition][delayPosition] = num;
}


int getMRecordListElement(MultipleRecord * temp,int arrayPosition,int delayPosition){
    return temp->list[arrayPosition][delayPosition];
}

void setMRecordList(MultipleRecord * temp,int position,int * array,int size){
    if(!temp->list[position]) 
        temp->list[position] = malloc(sizeof(int) * size);
    for(int i = 0;i < size;i++){
        temp->list[position][i] = array[i];
    }
    temp->listSize[position] = size;
}

int * getMRecordList(MultipleRecord * temp,int position){
    int size = getMRecordListSize(temp,position);
    int * aux = malloc(sizeof(int) * size);
    for(int i = 0;i < size;aux[i] = temp->list[position][i],i++);
    return aux;
}


void incMRecordListSize(MultipleRecord * temp,int position){
    temp->listSize[position]++;
}
void decMRecordListSize(MultipleRecord * temp,int position){
    temp->listSize[position]--;
}
int getMRecordListSize(MultipleRecord * temp,int position){
    return temp->listSize[position];
}

void incMRecordSize(MultipleRecord * temp){
    temp->size++;
}
void decMRecordSize(MultipleRecord * temp){
    temp->size--;
}
int getMRecordSize(MultipleRecord * temp){
    return temp->size;
}

void destroyMRecord(MultipleRecord *temp) {
    // Free the memory for the 'list' array
    for (int i = 0; i < temp->max; i++) {
        ffree((void **)&temp->list[i]);
    }
    ffree((void **)&(temp->list));

    // Free the memory for the 'listSize' array
    ffree((void **)&temp->listSize);

    // Free the memory for the 'names' array
    for (int i = 0; i < temp->max; i++) {
        ffree((void **)&temp->names[i]);
    }
    ffree((void **)&temp->names);

    // Free the memory for the 'temp' structure itself
    ffree((void **)&temp);
}
