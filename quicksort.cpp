#include <iostream>
#include <algorithm>
#include <stdint.h>

#include "quicksort.h"
#include "vectorclass.h"

using namespace std;

void quickSortUint64_t(uint64_t arr[], int lo, int hi) {
    if(lo < hi) { // Compare start and end indeces 
        int p = partitionUint64_t(arr, lo, hi); // Return partition index
        quickSortUint64_t(arr, lo, p-1); // Sort partitions
        quickSortUint64_t(arr, p+1, hi);
    }
}

void quickSortDouble(double arr[], int lo, int hi) {
    if(lo < hi) { // Compare start and end indeces 
        int p = partitionDouble(arr, lo, hi); // Return partition index
        quickSortDouble(arr, lo, p-1); // Sort partitions
        quickSortDouble(arr, p+1, hi);
    }
}

void quickSortFloat(float arr[], int lo, int hi) {
    if(lo < hi) { // Compare start and end indeces 
        int p = partitionFloat(arr, lo, hi); // Return partition index
        quickSortFloat(arr, lo, p-1); // Sort partitions
        quickSortFloat(arr, p+1, hi);
    }
}

// Calls vectorized partition function
void vecQuickSortUint64_t(uint64_t arr[], int lo, int hi) {
    if (lo < hi) {
        int p = vecPartitionUint64_t(arr, lo, hi);
        vecQuickSortUint64_t(arr, lo, p-1); // Sort partitions
        vecQuickSortUint64_t(arr, p+1, hi);
    }
}

void vecQuickSortDouble(double arr[], int lo, int hi) {
    if (lo < hi) {
        int p = vecPartitionDouble(arr, lo, hi);
        vecQuickSortDouble(arr, lo, p-1); // Sort partitions
        vecQuickSortDouble(arr, p+1, hi);
    }
}

void vecQuickSortFloat(float arr[], int lo, int hi) {
    if (lo < hi) {
        int p = vecPartitionFloat(arr, lo, hi);
        vecQuickSortFloat(arr, lo, p-1); // Sort partitions
        vecQuickSortFloat(arr, p+1, hi);
    }
}

// Can change to accomodate single or double-precision
void libQuickSortUint64_t(uint64_t arr[], int n) {
    qsort((void*)arr, n, sizeof(uint64_t), compareUint64_t);
}

void libQuickSortDouble(double arr[], int n) {
    qsort((void*)arr, n, sizeof(double), compareDouble);
}

void libQuickSortFloat(float arr[], int n) {
    qsort((void*)arr, n, sizeof(float), compareFloat);
}

void libSortUint64_t(uint64_t arr[], int n) {
    sort(arr, arr + n);
}

void libSortDouble(double arr[], int n) {
    sort(arr, arr + n);
}

void libSortFloat(float arr[], int n) {
    sort(arr, arr + n);
}

/**** Helper functions ****/
int partitionUint64_t(uint64_t arr[], int lo, int hi) {
    // Choose pivot at the end of the array
    uint64_t pivot = arr[hi];
    int i = (lo-1);
    
    for (int j = lo; j <= hi-1; j++) {
        //If current element is smaller than the pivot
        if(arr[j] < pivot) {
            //Increment index of smaller element
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    // Swap the pivot
    std::swap(arr[i+1],arr[hi]);
    // Return new partition at the high end of the array segment
    return (i+1);
}

int partitionDouble(double arr[], int lo, int hi) {
    // Choose pivot at the end of the array
    double pivot = arr[hi];
    int i = (lo-1);
    
    for (int j = lo; j <= hi-1; j++) {
        //If current element is smaller than the pivot
        if(arr[j] < pivot) {
            //Increment index of smaller element
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    // Swap the pivot
    std::swap(arr[i+1],arr[hi]);
    // Return new partition at the high end of the array segment
    return (i+1);
}

int partitionFloat(float arr[], int lo, int hi) {
    // Choose pivot at the end of the array
    float pivot = arr[hi];
    int i = (lo-1);
    
    for (int j = lo; j <= hi-1; j++) {
        //If current element is smaller than the pivot
        if(arr[j] < pivot) {
            //Increment index of smaller element
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    // Swap the pivot
    std::swap(arr[i+1],arr[hi]);
    // Return new partition at the high end of the array segment
    return (i+1);
}

int vecPartitionUint64_t(uint64_t arr[], int lo, int hi) {
    int i = (lo-1);
    Vec8uq pivot = arr[hi]; // Loads pivot into a vector for elementwise comparison

    for (int j = lo; j <= hi-8; j+=8) {
        // Utilize SIMD operations for partitioning
        Vec8uq elements = Vec8uq().load(&arr[j]); // Loads first 8 elements of array 
        Vec8qb field = elements < pivot; // Perform elementwise comparison and store results 

        for (int k = 0; k < 8; k++) {
            if (field[k]) { // Swap elements that satisfied comparison
                i++; 
                std::swap(arr[i], arr[j+k]);
            }
        }
    }

    // Process remaining elements if array size is not a multiple of 8
    for (int j = hi - (hi-lo) % 8; j < hi; j++) {
        if (arr[j] < arr[hi]) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[hi]);
    return (i + 1);
}

int vecPartitionFloat(float arr[], int lo, int hi) {
    int i = lo - 1;
    Vec8f pivot = arr[hi];

    for (int j = lo; j <= hi - 8; j += 8) {
        Vec8f elements = Vec8f().load(&arr[j]);
        Vec8fb field = elements < pivot;

        for (int k = 0; k < 8; k++) {
            if (field[k]) {
                i++;
                std::swap(arr[i], arr[j + k]);
            }
        }
    }

    for (int j = hi - (hi - lo) % 8; j < hi; j++) {
        if (arr[j] < arr[hi]) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[hi]);
    return i + 1;
}

int vecPartitionDouble(double arr[], int lo, int hi) {
    int i = lo - 1;
    Vec4d pivot = arr[hi];

    for (int j = lo; j <= hi - 4; j += 4) {
        Vec4d elements = Vec4d().load(&arr[j]);
        Vec4db field = elements < pivot;

        for (int k = 0; k < 4; k++) {
            if (field[k]) {
                i++;
                std::swap(arr[i], arr[j + k]);
            }
        }
    }

    for (int j = hi - (hi - lo) % 4; j < hi; j++) {
        if (arr[j] < arr[hi]) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[hi]);
    return i + 1;
}

int compareUint64_t(const void* a, const void* b) {
    if (*(uint64_t*)a < *(uint64_t*)b) return -1;
    if (*(uint64_t*)a > *(uint64_t*)b) return 1;
    return 0;
}

int compareFloat(const void* a, const void* b) {
    if (*(float*)a < *(float*)b) return -1;
    if (*(float*)a > *(float*)b) return 1;
    return 0;
}

int compareDouble(const void* a, const void* b) {
    if (*(double*)a < *(double*)b) return -1;
    if (*(double*)a > *(double*)b) return 1;
    return 0;
}