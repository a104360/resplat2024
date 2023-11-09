#include "../include/dataStructs.h"
#include "../include/dataTypes.h"
#include "../include/utils.h"
#include <stdlib.h>


typedef struct node
{
    void * data;
    struct keypair * next;

} Node;

typedef struct htable
{
    size_t size;
    Node ** table;

} HashTable;

static HashTable * createTable(){
    HashTable * hTable = malloc(sizeof(struct htable));
    hTable->size = 0;
    hTable->table = NULL;
    return hTable;
}

static void destroyTable(HashTable * table){
    for(int i = 0;i < table->size;i++){
        Node * current = table->table[i];
        while(current){
            Node * aux = current->next;
            free(current);
            current = aux;
        }
        free(table->table[i]);
    }
    free(table);
}

static int hash(int size,void * data){
    int * index = (int *) data;
    return *index % size;
}

static void insertHTable(HashTable * hTable,void * key,void * data){
    int index = hash(hTable->size,key);

    Node * newElement = malloc(sizeof(struct node));
    newElement->data = data;
    newElement->next = NULL;

    // Handling collisions
    if(hTable->table[index] == NULL){
        hTable->table[index] = newElement;
    }else{
        Node * current = hTable->table[index];
        while(current->next){
            current = current->next;
        }
        current = newElement;
    }
}

