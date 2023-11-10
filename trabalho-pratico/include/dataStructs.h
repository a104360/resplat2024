#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <stdbool.h>

typedef struct node Node;

typedef struct htable HashTable;

static HashTable * createTable();

static void destroyTable(HashTable *);

static int hash(int,void *);

static void insertHTable(HashTable *,void *,void *);



typedef struct binTree BinTree;

static BinTree * createTree();

static void destroyTree(BinTree * );

static insertTree(  )

#endif