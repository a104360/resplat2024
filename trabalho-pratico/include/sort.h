#ifndef SORT_H
#define SORT_H
#include "../include/dataTypes.h"

void mergeF(Flight ** arr, int l, int m, int r);

void mergeSortF(Flight ** arr, int l, int r);


void mergeR(Reservation ** arr, int l, int m, int r);

void mergeSortR(Reservation ** arr, int l, int r);

#endif