#include "../include/dataTypes.h"
#include "../include/time.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


void mergeF(Flight ** arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    Flight ** L = malloc(getFlightSize() * n1);
    Flight ** R = malloc(getFlightSize() * n2);

    for (i = 0; i < n1; i++)
        copyFlight(L[i],arr[l + i]);
    for (j = 0; j < n2; j++)
        copyFlight(R[j],arr[m + 1 + j]);
 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (compareTimes(getFlightSDepartureDate(R[i]),getFlightSDepartureDate(L[j])) == true) {
            copyFlight(arr[k],L[i]);
            i++;
        }
        else {
            copyFlight(arr[k],R[j]);
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        copyFlight(arr[k],L[i]);
        i++;
        k++;
    }
 
    while (j < n2) {
        copyFlight(arr[k],R[j]);
        j++;
        k++;
    }
    free(L);
    free(R);
}
 
void mergeSortF(Flight ** arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
 
        mergeSortF(arr, l, m);
        mergeSortF(arr, m + 1, r);
 
        mergeF(arr, l, m, r);
    }
}





void mergeR(Reservation ** arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    Reservation ** L = malloc(getReservSize() * n1);
    Reservation ** R = malloc(getReservSize() * n2);

    for (i = 0; i < n1; i++)
        copyReservation(L[i],arr[l + i]);
    for (j = 0; j < n2; j++)
        copyReservation(R[j],arr[m + 1 + j]);
 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (compareTimes(getReservBeginDate(R[i]),getReservBeginDate(L[j])) == true) {
            copyReservation(arr[k],L[i]);
            i++;
        }
        else {
            copyReservation(arr[k],R[j]);
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        copyReservation(arr[k],L[i]);
        i++;
        k++;
    }
 
    while (j < n2) {
        copyReservation(arr[k],R[j]);
        j++;
        k++;
    }
    free(L);
    free(R);
}
 
void mergeSortR(Reservation ** arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
 
        mergeSortR(arr, l, m);
        mergeSortR(arr, m + 1, r);
 
        mergeR(arr, l, m, r);
    }
}