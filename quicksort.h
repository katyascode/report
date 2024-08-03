#ifndef QUICKSORT_H
#define QUICKSORT_H

void quickSortUint64_t(uint64_t arr[], int lo, int hi);
void quickSortDouble(double arr[], int lo, int hi); 
void quickSortFloat(float arr[], int lo, int hi);

void vecQuickSortUint64_t(uint64_t arr[], int lo, int hi);
void vecQuickSortDouble(double arr[], int lo, int hi);
void vecQuickSortFloat(float arr[], int lo, int hi);


void libQuickSortUint64_t(uint64_t arr[], int n);
void libQuickSortDouble(double arr[], int n);
void libQuickSortFloat(float arr[], int n);

void libSortUint64_t(uint64_t arr[], int n);
void libSortDouble(double arr[], int n);
void libSortFloat(float arr[], int n);

int partitionUint64_t(uint64_t arr[], int lo, int hi);
int partitionDouble(double arr[], int lo, int hi);
int partitionFloat(float arr[], int lo, int hi);

int vecPartitionUint64_t(uint64_t arr[], int lo, int hi);
int vecPartitionDouble(double arr[], int lo, int hi);
int vecPartitionFloat(float arr[], int lo, int hi);

int compareUint64_t(const void* a, const void* b);
int compareFloat(const void* a, const void* b);
int compareDouble(const void* a, const void* b);

#endif
