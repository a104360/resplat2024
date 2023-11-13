#include "../include/dataStructs.h"
#include "../include/dataTypes.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <glib.h>




/*

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
}*/