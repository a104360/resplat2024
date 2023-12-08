#include "../include/dataTypes.h"
#include "../include/time.h"
#include "../include/sort.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*

void mergeF(Flight ** arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    Flight ** L = malloc(sizeof(Flight *) * n1);
    Flight ** R = malloc(sizeof(Flight *) * n2);

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
 
    Reservation ** L = malloc(sizeof(Reservation *) * n1);
    Reservation ** R = malloc(sizeof(Reservation *) * n2);

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
    L = NULL;
    free(R);
    R = NULL;
}
 
void mergeSortR(Reservation ** arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
 
        mergeSortR(arr, l, m);
        mergeSortR(arr, m + 1, r);
 
        mergeR(arr, l, m, r);
    }
}
*7
*/





// Performs a merge sort of the array a with the given length, the function 
// provides an easier/prettier interface for using merge sort for the 
// programmer as they simply need to provide the array and its length
// and the type of what is stored in the array
void mergeSort(void ** a, int length,const char * type)
{
  // call the merge sort recursion function, the left index of 0 and the
  // right index of length - 1 are provided as we are initially looking 
  // at sorting "the entire array"
  mSortRecursion(a, 0, length - 1,type);
}

// Applies the merge sort algorithm to the array a between the left index l
// and the right index r.  This function implements the recursive 
// divide-and-conquer step of the merge sort algorithm, splitting the array
// portion between l...r at the middle, and calling itself on each portion, 
// before applying the function to merge the sorted portions of the array 
// that will result.
void mSortRecursion(void ** a, int l, int r,const char * type)
{
  // we stop recursion when l >= r
  if (l < r)
  {
    // find the midpoint of l and r
    int m = l + (r - l) / 2;
  
    // apply the function recursively to the left and right portions split 
    // at the midpoint
    mSortRecursion(a, l, m,type);
    mSortRecursion(a, m + 1, r,type);
  
    // at this point both portions of the array have been sorted, and we now 
    // merge the sorted portions of the array
    mergeSortedArrays(a, l, m, r,type);
  }
}






// merges the two sorted portions of the array a between the indexes l ... m
// and m + 1 ... r
void mergeSortedArrays(void ** a, int l, int m, int r,const char * type)
{
    // calculate the length of the left and right portions of the array
    int left_length = m - l + 1;
    int right_length = r - m;

    if(!strcoll(type,"Reservation")){

        Reservation ** reservs = (Reservation **) a;
        // create temporary arrays to store these portions
        Reservation ** temp_left = malloc(sizeof(struct reservation *) * left_length);
        Reservation ** temp_right = malloc(sizeof(struct reservation *) * right_length);

        // used as index/counter variables for the 3 arrays a, temp_left, temp_right
        int i, j, k;

        // copy the left portion into the temp_left array
        for (int i = 0; i < left_length; i++)
            temp_left[i] = reservs[l + i];

        // copy the right portion into the temp_right array
        for (int i = 0; i < right_length; i++)
            temp_right[i] = reservs[m + 1 + i];

        // Use i to move through the indexes of temp_left, j to move through the 
        // indexes of temp_right, and k to move through the portion of the array 
        // a from l ... r.  We basically keep checking the "head" of temp_left 
        // and temp_right (knowing both arrays are sorted) and put the smaller of 
        // the two into array a (using i, j, k to move through the arrays).  When
        // we run out elements in either temp_left or temp_right, the remaining 
        // elements from the other array will be copied over into a.
        for (i = 0, j = 0, k = l; k <= r; k++)
        {
            // so long as we have not already reached the end of the temp_left array 
            // with our variable i, then if the next element in the left_temp array 
            // is smaller OR if we have reached the end of the temp_right array, 
            // then store the next element from temp_left into the next element in 
            // the array a

            if(i == left_length && j < right_length){
                reservs[k] = temp_right[j];
                j++;
                continue;
            }

            if(j == right_length && i < left_length){
                reservs[k] = temp_left[i];
                i++;
                continue;
            }

            Time * left = getReservBeginDate(temp_left[i]);
            Time * right = getReservBeginDate(temp_right[j]);
            
            if ((i < left_length) && (j >= right_length || compareTimes(left,right)))//temp_left[i] <= temp_right[j]))
            {
                reservs[k] = temp_right[j];
                j++;
            }
            // otherwise if the next element in temp_right than the next element in 
            // temp_left OR we have reached the end of temp_left, store the next 
            // element from the temp_right array into the next element in array a
            else
            {
                reservs[k] = temp_left[i];
                i++;
            }
            destroyTime(left);  
            destroyTime(right);
        }  
    }
    if(!strcoll(type,"Flight")){

        Flight ** flights = (Flight **) a;

        // create temporary arrays to store these portions
        Flight ** temp_left = malloc(sizeof(struct flight *) * left_length);
        Flight ** temp_right = malloc(sizeof(struct flight *) * right_length);

        // used as index/counter variables for the 3 arrays a, temp_left, temp_right
        int i, j, k;

        // copy the left portion into the temp_left array
        for (int i = 0; i < left_length; i++)
            temp_left[i] = flights[l + i];

        // copy the right portion into the temp_right array
        for (int i = 0; i < right_length; i++)
            temp_right[i] = flights[m + 1 + i];

        // Use i to move through the indexes of temp_left, j to move through the 
        // indexes of temp_right, and k to move through the portion of the array 
        // a from l ... r.  We basically keep checking the "head" of temp_left 
        // and temp_right (knowing both arrays are sorted) and put the smaller of 
        // the two into array a (using i, j, k to move through the arrays).  When
        // we run out elements in either temp_left or temp_right, the remaining 
        // elements from the other array will be copied over into a.
        for (i = 0, j = 0, k = l; k <= r; k++)
        {
            // so long as we have not already reached the end of the temp_left array 
            // with our variable i, then if the next element in the left_temp array 
            // is smaller OR if we have reached the end of the temp_right array, 
            // then store the next element from temp_left into the next element in 
            // the array a

            if(i == left_length && j < right_length){
                flights[k] = temp_right[j];
                j++;
                continue;
            }

            if(j == right_length && i < left_length){
                flights[k] = temp_left[i];
                i++;
                continue;
            }

            Time * left = getFlightSDepartureDate(temp_left[i]);
            Time * right = getFlightSDepartureDate(temp_right[j]);

            if ((i < left_length) && (j >= right_length || compareTimes(left,right)))//temp_left[i] <= temp_right[j]))
            {
                flights[k] = temp_right[j];
                j++;
            }
            // otherwise if the next element in temp_right than the next element in 
            // temp_left OR we have reached the end of temp_left, store the next 
            // element from the temp_right array into the next element in array a
            else
            {
                flights[k] = temp_left[i];
                i++;
            }
            destroyTime(right);
            destroyTime(left);
        }  
        free(temp_left);
        free(temp_right);
    }
}


/*
//
//          [38, 27, 43, 3, 9, 82, 10]
//                     /   \
//       [38, 27, 43, 3]   [9, 82, 10]
//        /         |         |      \
//   [38, 27]    [43, 3]   [9, 82]   [10]
//    /   |      /    |    /    \      |
// [38]  [27]  [43]  [3]  [9]   [82]  [10]
//    \  /       \   /     \     /     |
//   [27, 38]    [3, 43]   [9, 82]    [10]
//       \         /          \        /
//     [3, 27, 38, 43]        [9, 10, 82]
//           \                  /
//          [3, 9, 10, 27, 38, 43, 82]
//
// The array is first broken up into progressively smaller unsorted portions of
// the array, and once we have "sub-arrays" of 1 element they are by definition
// sorted arrays.  From here the "sorted arrays" are merged together until we 
// arrive at the complete sorted array.
//
Example visualization of the merge sort algorithm:
*/ 