#include "../include/temporary.h"
#include "../include/utils.h"
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
    ffree((void **) &temp->id);
    ffree((void **) &temp->list);
    temp->database = NULL;
    temp->num = 0;
    temp->sum = 0;
    temp->max = 0;
    ffree((void **) &temp);
}

void destroyTemporaryFlight(Temporary * temp){
    destroyTime(temp->begin);
    destroyTime(temp->end);
    ffree((void **) &temp->id);
    for(int i = 0;i < temp->max;i++){
        destroyFlight((((Flight **) temp->list)[i]));
    }
    ffree((void **) &temp->list);
    temp->database = NULL;
    temp->num = 0;
    temp->sum = 0;
    temp->max = 0;
    ffree((void **) &temp);
}

void destroyTemporaryReservation(Temporary * temp){
    destroyTime(temp->begin);
    destroyTime(temp->end);
    ffree((void **) &temp->id);
    for(int i = 0;i < temp->max;i++){
        destroyReservation((((Reservation **) temp->list)[i]));
    }
    ffree((void **) &temp->list);
    temp->database = NULL;
    temp->num = 0;
    temp->sum = 0;
    temp->max = 0;
    ffree((void **) &temp);
}

void destroyTemporaryChar(Temporary * temp){
    for(int i = 0;i < temp->max;i++){
        ffree((void **) &(((char **) temp->begin)[i]));
    }
    ffree((void **) &temp->begin);
    ffree((void **) &temp->end);
    ffree((void **) &temp->id);
    for(int i = 0;i < temp->max;i++){
        ffree((void **) &(((char **) temp->list)[i]));
    }
    ffree((void **) &temp->list);
    temp->database = NULL;
    temp->num = 0;
    temp->sum = 0;
    temp->max = 0;
    ffree((void **) &temp);
}

void setTempDatabase(Temporary * temp,void * database){
    temp->database = database;
}
void * getTempDatabase(Temporary * temp){
    return temp->database;
}
    
void setTempId(Temporary * temp,char * id){
    ffree((void **) &temp->id);
    temp->id = strdup(id);
}
char * getTempId(Temporary * temp){
    if(!temp->id) return NULL;
    return strdup(temp->id);
}

void setTempList(Temporary * temp,void ** list){
    ffree((void **) &temp->list);
    temp->list = list;
}

void setTempListElement(Temporary * temp,void * element,int position){
    temp->list[position] = element;
}

void setTempListElementReservation(Temporary * temp,Reservation * element,int position){
    Reservation ** list = (Reservation **) temp->list;
    if(temp->num >= temp->max){
        if(extendArray(&temp->list,temp->num,temp->num * 2) == 0) return;
        setTempMax(temp,temp->num * 2);
    }
    
    if(list[position] && temp->list[position]){
        copyReservation(temp->list[position],element);
        return;
    }
    temp->list[position] = (void *) createReservation();
    copyReservation((Reservation *)temp->list[position],element);
}


Reservation ** getTempListReservations(Temporary * temp){
    int max = temp->num;
    Reservation ** list = malloc(sizeof(Reservation *) * max);
    for(int i = 0;i < max;i++){
        list[i] = NULL;
        list[i] = createReservation();
        copyReservation(list[i],temp->list[i]);
    }
    return list;
}

void setTempListFlight(Temporary * temp,Flight * element,int position){
    Flight ** list = (Flight **) temp->list;
    if(temp->num >= temp->max){
        if(extendArray(&temp->list,temp->num,temp->num * 2) == 0) return;
        setTempMax(temp,temp->num * 2);
    }
    if(temp->list[position]) {
        copyFlight(temp->list[position],element);
        return;
    }
    temp->list[position] = (void *) createFlight();
    copyFlight(temp->list[position],element);
}

void setTempListElementChar(Temporary * temp,char * element,int position){
    char ** list = (char **) temp->list;
    if(temp->num >= temp->max){
        if(extendArray((void ***) &temp->list,temp->num,temp->num * 2) == 1) setTempMax(temp,temp->num * 2);
        else return;
    }
    if(list[position]) ffree((void **) &list[position]);
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

Flight * getTempListFlight(Temporary * temp,int position){
    Flight * flight = createFlight();
    if(temp->list[position]){
        copyFlight(flight,temp->list[position]);
        return flight;
    }
    return NULL;
}

Flight ** getTempListFlights(Temporary * temp){
    Flight ** list = malloc(sizeof(Flight *) * temp->num);
    for(int i = 0;i < temp->num;i++){
        list[i] = createFlight();
        copyFlight(list[i],(Flight *)temp->list[i]);
    }
    return list;
}

char * getTempListCharElement(Temporary * temp, int position){
    char ** list = (char **) temp->list;
    if(list[position]){
        return strdup(list[position]);
    }
    return NULL;
}

char ** getTempListChars(Temporary * temp){
    char ** list = malloc(sizeof(char *)* temp->num);
    for(int i = 0; i < temp->num; i++){
        list[i] = NULL;
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
    if(list[position]) ffree((void **) &list[position]);
    list[position] = strdup(element);
}

void * getTempAux(Temporary * temp){
    return temp->begin;
}


char ** getTempAuxChar(Temporary * temp){
    char ** list = (char **) temp->begin;
    int max = temp->num;
    char ** dup = malloc(sizeof(char *) * max);
    for(int i = 0;i < max;i++){
        dup[i] = strdup(list[i]);
    }
    return dup;
}
