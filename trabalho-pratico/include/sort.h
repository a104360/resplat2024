#ifndef SORT_H
#define SORT_H

/*
Sorts an array of pointers, requesting as arguments: 
    ARRAY of pointers 
    LENGTH of the array
    TYPE of what is store in the array (Reservation/Flight)
*/ 
void mergeSort(void **,int,const char *);

void mSortRecursion(void **,int,int,const char *);

void mergeSortedArrays(void **,int,int,int,const char *);


#endif