#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

#define MAXVALUE 99999999

long textTOarray(FILE *input, long a[]){
    int ct = 0;
    if (input == NULL)
    {
        printf("Can't open file for reading.\n");
    }
    else
    {
        printf("%s\n", "Start");
        while(fscanf(input,"%d", &a[ct]) == 1){
            ct ++;
        }
    }
    return ct;

}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(long arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void merge(long arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(long arr[], int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void quicksort(int number[25],int first,int last){
   int i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(number[i]<=number[pivot]&&i<last)
            i++;
         while(number[j]>number[pivot])
            j--;
         if(i<j){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }

      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);

   }
}

int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void countSort(long arr[], int n, int exp)
{
    static int output[9999999]; // output array
    int i, count[10] = { 0 };

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixsort(int arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

int main()
{
    FILE *input1 = fopen("input.txt", "r");
    static long b[MAXVALUE], a[MAXVALUE];
    int ct;
    ct = textTOarray(input1, a);
    printf("%d\n", ct);
/*
    for(int i=0; i<ct; i++){
        b[i] = a[i];
    }
    for(int i = 0; i < ct; i++){
           printf("%d ", a[i]);

    }
    printf("\n");
    bubbleSort(b,ct);
    printArray(b,ct);

    for(int i=0; i<ct; i++){
        b[i] = a[i];
    }
    for(int i = 0; i < ct; i++){
       printf("%d ", a[i]);

    }
    printf("\n");
    insertionSort(b,ct);
    printArray(b,ct);

    for(int i=0; i<ct; i++){
        b[i] = a[i];
    }
    for(int i = 0; i < ct; i++){
       printf("%d ", a[i]);

    }
    printf("\n");
    mergeSort(b, 0, ct-1);
    printArray(b, ct);

    for(int i=0; i<ct; i++){
        b[i] = a[i];
    }
    for(int i = 0; i < ct; i++){
       printf("%d ", a[i]);

    }
    printf("\n");
    quicksort(b,0,ct-1);
    printArray(b,ct);

    for(int i=0; i<ct; i++){
        b[i] = a[i];
    }
    for(int i = 0; i < ct; i++){
       printf("%d ", a[i]);

    }
    printf("\n");
    radixsort(b,ct);
    printArray(b,ct);


    for(int i=0; i<ct; i++){
        b[i] = a[i];
    }
    for(int i = 0; i < ct; i++){
       printf("%d ", a[i]);

    }
    printf("\n");
    heapSort(b,ct);
    printArray(b,ct);

*/
    for(int i=0; i<ct; i++){
        b[i] = a[i];
    }
    printf("%s\n", "Start");
    selectionSort(b,ct);
    //printArray(b,ct);

    return 0;
}
