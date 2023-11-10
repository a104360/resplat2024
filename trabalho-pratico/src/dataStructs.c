#include "../include/dataStructs.h"
#include "../include/dataTypes.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <glib.h>



typedef struct node
{
    void * data;
    int key;
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

typedef struct bTree {
    void * node;
    struct bTree * less;
    struct bTree * more;
} BTree;

static BTree * createTree(){
    BTree * tree = malloc(sizeof(struct bTree));
    tree->node = NULL;
    tree->less = NULL;
    tree->more = NULL;
    return tree;
}

static void destroyTree(BTree * tree){
    if(tree){
        free(tree->node);
        destroyTree(tree->less);
        destroyTree(tree->more);
    }
    return;
}

int nFolhas(BTree *a) {
    if(!a) return 0;
    if(a->less || a->more){
        int n = 0;
        n += nFolhas(a->less) + nFolhas(a->more);
        return n;
    }
    int n = 1;
    n += nFolhas(a->less) + nFolhas(a->more);
    return n;
}

static void * search(BTree * a, void * x) {
    if(!a) return NULL;
    if(a->node == x) return a;
    return procura(a->node,x) ? procura(a->node,x) : procura(a->node,x);
}

BTree * maisEsquerda (BTree * a) {
    if(!a) return NULL;
    if(!a->less) return a;
    return maisEsquerda(a->less);
}