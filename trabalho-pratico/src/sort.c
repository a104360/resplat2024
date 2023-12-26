#include "../include/reservation.h"
#include "../include/flight.h"
#include "../include/time.h"
#include "../include/sort.h"
#include "../include/utils.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// merges the two sorted portions of the array a between the indexes l ... m
// and m + 1 ... r
static void mergeSortedArrays(void ** a, int l, int m, int r,const char * type)
{
    // calculate the length of the left and right portions of the array
    int left_length = m - l + 1;
    int right_length = r - m;

    if(!strcoll(type,"Reservation")){

        Reservation ** reservations = (Reservation **) a;

        // create temporary arrays to store these portions
        Reservation ** temp_left = malloc(sizeof(struct reservation *) * left_length);
        Reservation ** temp_right = malloc(sizeof(struct reservation *) * right_length);

        // used as index/counter variables for the 3 arrays a, temp_left, temp_right
        int i, j, k;

        // copy the left portion into the temp_left array
        for (int i = 0; i < left_length; i++)
            temp_left[i] = reservations[l + i];

        // copy the right portion into the temp_right array
        for (int i = 0; i < right_length; i++)
            temp_right[i] = reservations[m + 1 + i];

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
                reservations[k] = temp_right[j];
                j++;
                continue;
            }

            if(j == right_length && i < left_length){
                reservations[k] = temp_left[i];
                i++;
                continue;
            }

            Time * left = getReservBeginDate(temp_left[i]);
            Time * right = getReservBeginDate(temp_right[j]);

            int n = compareTimes(left,right);

            if ((i < left_length) && (j >= right_length || n != 0))//temp_left[i] <= temp_right[j]))
            {
                if(n == 10){
                    char * leftId = getReservId(temp_left[i]);
                    char * rightId = getReservId(temp_right[j]);
                    if(strcoll(leftId,rightId) < 0){
                        reservations[k] = temp_left[i];
                        i++;
                    }else{
                        reservations[k] = temp_right[j];
                        j++;
                    }
                    free(leftId);
                    free(rightId);
                }
                else{
                    reservations[k] = temp_right[j];
                    j++;
                }
            }
            // otherwise if the next element in temp_right than the next element in 
            // temp_left OR we have reached the end of temp_left, store the next 
            // element from the temp_right array into the next element in array a
            else
            {
                if(n == 10){
                    char * leftId = getReservId(temp_left[i]);
                    char * rightId = getReservId(temp_right[j]);
                    if(strcoll(leftId,rightId) < 0){
                        reservations[k] = temp_left[i];
                        i++;
                    }else{
                        reservations[k] = temp_right[j];
                        j++;
                    }
                    free(leftId);
                    free(rightId);
                }
                else{
                    reservations[k] = temp_left[i];
                    i++;
                }
            }
            destroyTime(right);
            destroyTime(left);
        }  
        free(temp_left);
        free(temp_right);
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

            int n = compareTimes(left,right);
            
            if ((i < left_length) && (j >= right_length || n != 0))//temp_left[i] <= temp_right[j]))
            {
                if(n == 10){
                    char * leftId = getFlightId(temp_left[i]);
                    char * rightId = getFlightId(temp_right[j]);
                    if(strcoll(leftId,rightId) < 0){
                        flights[k] = temp_left[i];
                        i++;
                    }else{
                        flights[k] = temp_right[j];
                        j++;
                    }
                    free(leftId);
                    free(rightId);
                }
                else{
                    flights[k] = temp_right[j];
                    j++;
                }
            }
            // otherwise if the next element in temp_right than the next element in 
            // temp_left OR we have reached the end of temp_left, store the next 
            // element from the temp_right array into the next element in array a
            else
            {
                if(n == 10){
                    char * leftId = getFlightId(temp_left[i]);
                    char * rightId = getFlightId(temp_right[j]);
                    if(strcoll(leftId,rightId) < 0){
                        flights[k] = temp_left[i];
                        i++;
                    }else{
                        flights[k] = temp_right[j];
                        j++;
                    }
                    free(leftId);
                    free(rightId);
                }
                else{
                    flights[k] = temp_left[i];
                    i++;
                }
            }
            destroyTime(right);
            destroyTime(left);
        }  
        free(temp_left);
        free(temp_right);
    }
    if(!strcoll(type,"Int")){
        int * aux = (int *) a[0];

        int temp_left[left_length];
        int temp_right[right_length];

        int i, j, k;

        for (int i = 0; i < left_length; i++) temp_left[i] = aux[l + i];

        for (int i = 0; i < right_length; i++) temp_right[i] = aux[m + 1 + i];

        for (i = 0, j = 0, k = l; k <= r; k++){
            if ((i < left_length) && (j >= right_length || temp_left[i] <= temp_right[j]))
            {
                aux[k] = temp_left[i];
                i++;
            }else{
                aux[k] = temp_right[j];
                j++;
            }
        }  

    }
    if(!strcoll(type,"Integers")){
        
        Integers * temp = (Integers *) a[1];
        int * integers = (int *) a[0];
        

        // create temporary arrays to store these portions
        int * temp_left = malloc(sizeof(int) * left_length);
        int * temp_right = malloc(sizeof(int) * right_length);

        // used as index/counter variables for the 3 arrays a, temp_left, temp_right
        int i, j, k;

        // copy the left portion into the temp_left array
        for (int i = 0; i < left_length; i++)
            temp_left[i] = integers[l + i];

        // copy the right portion into the temp_right array
        for (int i = 0; i < right_length; i++)
            temp_right[i] = integers[m + 1 + i];

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

            // The left array is out 
            if(i == left_length && j < right_length){ 
                integers[k] = temp_right[j]; // Change the delay 
                // swap names
                void * main = getIntNamesElement(temp,k);
                void * selected = getIntNamesElement(temp,r + j);
                setIntNamesElement(temp,k,selected);
                setIntNamesElement(temp,r + j,main);
                // Swap arrays
                void * less = getIntList(temp,k);// Keeps the array of the position we will put the new array
                void * great = getIntList(temp,r + j); // Keep the array that is going to be put in the new position
                setIntList(temp,k,great); // swap 1
                setIntList(temp,r + j,less); // swap 2
                ffree(great);
                ffree(less);
                j++;
                continue;
            }

            if(j == right_length && i < left_length){
                integers[k] = temp_left[i];

                void * main = getIntNamesElement(temp,k);
                void * selected = getIntNamesElement(temp,l + i);
                setIntNamesElement(temp,k,selected);
                setIntNamesElement(temp,l + i,main);

                void * less = getIntList(temp,k);
                void * great = getIntList(temp,l + i);
                setIntList(temp,k,great);
                setIntList(temp,l + i,less);

                ffree(great);
                ffree(less);

                i++;
                continue;
            }

            
            if ((i < left_length) && (j >= right_length || temp_left[i] >= temp_right[j]))//temp_left[i] <= temp_right[j]))
            {
               
                integers[k] = temp_right[j];
                void * main = getIntNamesElement(temp,k);
                void * selected = getIntNamesElement(temp,r + j);
                setIntNamesElement(temp,k,selected);
                setIntNamesElement(temp,r + j,main);
                void * less = getIntList(temp,k);
                void * great = getIntList(temp,r + j);
                setIntList(temp,k,great);
                setIntList(temp,r + j,less);
                ffree(great);
                ffree(less);
                j++;
                //}
            }
            // otherwise if the next element in temp_right than the next element in 
            // temp_left OR we have reached the end of temp_left, store the next 
            // element from the temp_right array into the next element in array a
            else
            {
                /*if(n == 10){
                    char * leftId = getFlightId(temp_left[i]);
                    char * rightId = getFlightId(temp_right[j]);
                    if(strcoll(leftId,rightId) < 0){
                        integers[k] = temp_left[i];
                        i++;
                    }else{
                        integers[k] = temp_right[j];
                        j++;
                    }
                    free(leftId);
                    free(rightId);
                }
                else{*/
                integers[k] = temp_left[i];
                void * main = getIntNamesElement(temp,k);
                void * selected = getIntNamesElement(temp,l + i);
                setIntNamesElement(temp,k,selected);
                setIntNamesElement(temp,l + i,main);
                void * less = getIntList(temp,k);
                void * great = getIntList(temp,l + i);
                setIntList(temp,k,great);
                setIntList(temp,l + i,less);
                ffree(great);
                ffree(less);
                i++;
                //}
            }
            //destroyTime(right);
            //destroyTime(left);
        }  
        ffree(temp_left);
        ffree(temp_right);
    }
}

// Applies the merge sort algorithm to the array a between the left index l
// and the right index r.  This function implements the recursive 
// divide-and-conquer step of the merge sort algorithm, splitting the array
// portion between l...r at the middle, and calling itself on each portion, 
// before applying the function to merge the sorted portions of the array 
// that will result.
static void mSortRecursion(void ** a, int l, int r,const char * type)
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