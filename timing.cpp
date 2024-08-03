#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "quicksort.h"

#define SIZE 32768

#define TIMING_RESULT(DESCR, CODE) do { \
    struct timespec start, end; \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start); \
    CODE; \
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end); \
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; \
    printf("%25s took %7.1f ms\n", descr, elapsed * 1000); \
} while(0)

uint64_t* create_array_uint64_t(int length) {
    uint64_t* array = (uint64_t*)malloc(length * sizeof(uint64_t));
    
    if (array == NULL) return NULL;

    for (int i = 0; i < length; i++) {
        array[i] = (uint64_t)rand();
    }

    return array;
}

uint64_t* create_sorted_array_uint64_t(int length) {
    uint64_t* array = (uint64_t*)malloc(length * sizeof(uint64_t));
    
    if (array == NULL) return NULL;

    for (int i = 0; i < length; i++) {
        array[i] = (uint64_t)i;
    }

    return array;
}

uint64_t* create_reverse_sorted_array_uint64_t(int length) {
    uint64_t* array = (uint64_t*)malloc(length * sizeof(uint64_t));
    
    if (array == NULL) return NULL;

    for (int i = 0; i < length; i++) {
        array[i] = (uint64_t)(length-i-1);
    }

    return array;
}


double* create_array_double(int length) {
    double* array = (double*)malloc(length * sizeof(double));
    
    if (array == NULL) return NULL;

    for (int i = 0; i < length; i++) {
        array[i] = (double)rand();
    }

    return array;
}

double* create_sorted_array_double(int length) {
    double* array = (double*)malloc(length * sizeof(double));
    
    if (array == NULL) return NULL;

    for (int i = 0; i < length; i++) {
        array[i] = (double)i;
    }

    return array;
}

double* create_reverse_sorted_array_double(int length) {
    double* array = (double*)malloc(length * sizeof(double));
    
    if (array == NULL) return NULL;

    for (int i = 0; i < length; i++) {
        array[i] = (double)(length-i-1);
    }

    return array;
}

float* create_array_float(int length) {
    float* array = (float*)malloc(length * sizeof(float));
    
    if (array == NULL) return NULL;

    for (int i = 0; i < length; i++) {
        array[i] = (float)rand();
    }
    
    return array;
}

float* create_sorted_array_float(int length) {
    float* array = (float*)malloc(length * sizeof(float));
    
    if (array == NULL) return NULL;

    for (int i = 0; i < length; i++) {
        array[i] = (float)i;
    }

    return array;
}

float* create_reverse_sorted_array_float(int length) {
    float* array = (float*)malloc(length * sizeof(float));
    
    if (array == NULL) return NULL;

    for (int i = 0; i < length; i++) {
        array[i] = (float)(length-i-1);
    }

    return array;
}

void qs_speed_uint64_t(const char* descr, void qs(uint64_t[], int, int)) {
    uint64_t* arr = create_array_uint64_t(SIZE);
    // uint64_t* arr = create_sorted_array_uint64_t(SIZE);
    // uint64_t* arr = create_reverse_sorted_array_uint64_t(SIZE);
    TIMING_RESULT(descr, qs(arr, 0, SIZE-1));
    free(arr);
}

void qs_speed_lib_uint64_t(const char* descr, void qs(uint64_t arr[], int n)) {
    uint64_t* arr = create_array_uint64_t(SIZE);
    // uint64_t* arr = create_sorted_array_uint64_t(SIZE);
    // uint64_t* arr = create_reverse_sorted_array_uint64_t(SIZE);
    TIMING_RESULT("Library QuickSort", qs(arr, SIZE));
    free(arr);
}

void qs_speed_float(const char* descr, void qs(float[], int, int)) {
    float* arr = create_array_float(SIZE*2);
    // float* arr = create_sorted_array_float(SIZE*2);
    // float* arr = create_reverse_sorted_array_float(SIZE);
    TIMING_RESULT(descr, qs(arr, 0, (SIZE)-1));
    free(arr);
}

void qs_speed_lib_float(const char* descr, void qs(float arr[], int n)) {
    float* arr = create_array_float(SIZE*2);
    // float* arr = create_sorted_array_float(SIZE*2);
    // float* arr = create_reverse_sorted_array_float(SIZE);
    TIMING_RESULT("Library QuickSort", qs(arr, SIZE));
    free(arr);
}

void qs_speed_double(const char* descr, void qs(double[], int, int)) {
    double* arr = create_array_double(SIZE);
    // double* arr = create_sorted_array_double(SIZE);
    // double* arr = create_reverse_sorted_array_double(SIZE);
    TIMING_RESULT(descr, qs(arr, 0, SIZE-1));
    free(arr);
}

void qs_speed_lib_double(const char* descr, void qs(double arr[], int n)) {
    // double* arr = create_array_double(SIZE);
    // double* arr = create_sorted_array_double(SIZE);
    double* arr = create_reverse_sorted_array_double(SIZE);
    TIMING_RESULT("Library QuickSort", qs(arr, SIZE));
    free(arr);
}

int main(void) {
    printf("Testing on uint64_t Datasets\n");
    qs_speed_uint64_t("QuickSort", quickSortUint64_t);
    qs_speed_uint64_t("Vectorized QuickSort", vecQuickSortUint64_t);
    qs_speed_lib_uint64_t("Library QuickSort", libQuickSortUint64_t);
    qs_speed_lib_uint64_t("Library Sort", libSortUint64_t);
    printf("\n\n");

    printf("Testing on Float Datasets\n");
    qs_speed_float("QuickSort", quickSortFloat);
    qs_speed_float("Vectorized QuickSort", vecQuickSortFloat);
    qs_speed_lib_float("Library QuickSort", libQuickSortFloat);
    qs_speed_lib_float("Library Sort", libSortFloat);
    printf("\n\n");

    printf("Testing on Double Datasets\n");
    qs_speed_double("QuickSort", quickSortDouble);
    qs_speed_double("Vectorized QuickSort", vecQuickSortDouble);
    qs_speed_lib_double("Library QuickSort", libQuickSortDouble);
    qs_speed_lib_double("Library Sort", libSortDouble);
    printf("\n\n");

    return 0;
}