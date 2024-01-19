#include "../include/temporary.h"
#include <stdlib.h>
#include <string.h>


typedef struct temporary {
    void * database;//
    char * id;
    void ** list;//
    int num;
    int sum;
    void * begin;//
    void * end;//
    int max;
} Temporary;


static void initTemp(Temporary * temp){
    temp->begin = NULL;
    temp->end = NULL;
    temp->database = NULL;
    temp->id = NULL;
    temp->list = NULL;
    temp->num = 0;
    temp->sum = 0;
    temp->max = 0;
}

Temporary * createTemporary(){
    Temporary * temp = malloc(sizeof(struct temporary));
    initTemp(temp);
    return temp;

}


void destroyTemporary(Temporary * temp){
    destroyTime(temp->begin);
    destroyTime(temp->end);
    ffree(temp->id);
    ffree(temp->list);
    temp->database = NULL;
    temp->num = 0;
    temp->sum = 0;
    temp->max = 0;
    ffree(temp);
}

void destroyTemporaryChar(Temporary * temp){
    for(int i = 0;i < temp->max;i++){
        ffree((((char **) temp->begin)[i]));
    }
    ffree(temp->begin);
    ffree(temp->end);
    ffree(temp->id);
    for(int i = 0;i < temp->max;i++){
        ffree((((char **) temp->list)[i]));
    }
    ffree(temp->list);
    temp->database = NULL;
    temp->num = 0;
    temp->sum = 0;
    temp->max = 0;
    ffree(temp);
}

void setTempDatabase(Temporary * temp,void * database){
    temp->database = database;
}
void * getTempDatabase(Temporary * temp){
    return temp->database;
}
    
void setTempId(Temporary * temp,char * id){
    ffree(temp->id);
    temp->id = strdup(id);
}
char * getTempId(Temporary * temp){
    return strdup(temp->id);
}

void setTempList(Temporary * temp,void ** list){
    ffree(temp->list);
    temp->list = list;
}

void setTempListElement(Temporary * temp,void * element,int position){
    temp->list[position] = element;
}
void setTempListElementChar(Temporary * temp,char * element,int position){
    char ** list = (char **) temp->list;
    if(list[position]) ffree(list[position]);
    list[position] = strdup(element);
}

const void * getTempListElement(Temporary * temp,int position){
    return (const void *) temp->list[position];
}   

void ** getTempList(Temporary * temp){
    void ** list = malloc(sizeof(void *) * temp->num);
    for(int i = 0;i < temp->num;list[i] = temp->list[i],i++);
    return list;
}

Flight ** getTempListFlights(Temporary * temp){
    Flight ** list = malloc(sizeof(Flight *) * temp->num);
    for(int i = 0;i < temp->num;copyFlight(list[i],temp->list[i]),i++);
    return list;
}

char ** getTempListChar(Temporary * temp){
    char ** list = malloc(sizeof(char *)* temp->max);
    for(int i = 0; i < temp->max; i++){
        char * aux = (char *) temp->list[i];
        list[i] = strdup(aux);
    }

    return list;
}

void setTempNum(Temporary * temp,int num){
    temp->num = num;
}
void incTempNum(Temporary *temp){
    temp->num++;
}

int getTempNum(Temporary * temp){
    return temp->num;
}

void setTempSum(Temporary * temp,int sum){
    temp->sum = sum;
}

void increaseTempSum(Temporary * temp,int num){
    temp->sum += num;
}

int getTempSum(Temporary * temp){
    return temp->sum;
}


void setTempBegin(Temporary * temp,Time * begin){
    if(!begin) return;
    if(!temp->begin) temp->begin = createTime();
    copyTime(temp->begin,begin);
}
Time * getTempBegin(Temporary * temp){
    if(!temp->begin) return NULL;
    Time * time = createTime();
    copyTime(time,temp->begin);
    return time;
}

void setTempEnd(Temporary * temp,Time * end){
    if(!end) return;
    if(!temp->end) temp->end = createTime();
    copyTime(temp->end,end);
}
Time * getTempEnd(Temporary * temp){
    if(!temp->end) return NULL;
    Time * time = createTime();
    copyTime(time,temp->end);
    return time;
}

void setTempMax(Temporary * temp,int max){
    temp->max = max;
}

int getTempMax(Temporary * temp){
    return temp->max;
}

void setTempAux(Temporary * temp,char ** element){
    temp->begin = (void *) element;
}

void setTempAuxElement(Temporary * temp, void * element, int position){
    void ** aux = (void **) temp->begin;
    aux[position] = element;
}

void setTempAuxElementChar(Temporary * temp,char * element,int position){
    char ** list = (char **) temp->begin;
    if(list[position]) ffree(list[position]);
    list[position] = strdup(element);
}

void * getTempAux(Temporary * temp){
    return temp->begin;
}


char ** getTempAuxChar(Temporary * temp){
    char ** list = (char **) temp->begin;
    int max = temp->max;
    char ** dup = malloc(sizeof(char *) * max);
    for(int i = 0;i < max;i++){
        dup[i] = strdup(list[i]);
    }
    return dup;
}
