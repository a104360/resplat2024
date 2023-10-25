#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include <stdbool.h>

typedef struct node Node;

typedef struct htable HashTable;

static HashTable * createTable();

static void destroyTable(HashTable *);

static int hash(int,void *);

static void insertHTable(HashTable *,void *,void *);

#endif