#include "../include/database.h"
#include "../include/user.h"
#include "../include/flight.h"
#include "../include/reservation.h"
#include "../include/utils.h"
#include <ctype.h>
#include <stdio.h>

typedef struct database {
    GHashTable * table;
} Database;

Database * createDatabase(void (*func)()){
    Database * database = malloc(sizeof(struct database));
    GDestroyNotify function = (GDestroyNotify) func;
    database->table = g_hash_table_new_full(g_str_hash,g_str_equal,free,(GDestroyNotify) function);
    return database;
}

void insertOnDatabase(void * dBase,const char * id,void * element){
    Database * database = (Database *) dBase;
    g_hash_table_insert((GHashTable *)database->table,(gpointer)id,(gpointer) element);
}

void * lookupElement(const void * dBase ,const char * id){
    Database * database = (Database *) dBase;
    void * element = g_hash_table_lookup((GHashTable *)database->table,(gconstpointer)id);
    return element;
}

int getDatabaseSize(const void * database){
    Database * dBase = (Database *) database;
    return g_hash_table_size(dBase->table);
}

void applyForEach(void * database,void (*func)(gpointer,gpointer,gpointer),void * data){
    Database * dBase = (Database *) database;
    g_hash_table_foreach((GHashTable *) dBase->table,(GHFunc) (*func),(gpointer)data);
}

void destroyDatabase(void * database){
    Database * dBase = (Database *) database;
    g_hash_table_destroy(dBase->table);
    ffree(database);
}











typedef struct temporary {
    void * database;
    char * id;
    void ** list;
    int num;
    int sum;
    void * begin;
    void * end;
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

void ** getTempList(Temporary * temp){
    void ** list = malloc(sizeof(void *) * temp->num);
    for(int i = 0;i < temp->num;list[i] = temp->list[i],i++);
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



