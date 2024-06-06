#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#ifndef SORT_H
#define SORT_H

template <class T> 
class Sort{
    public:
        static long long Shell_sort(T **A, int n);
        static long long Heap_sort(T **A, int n);
        static void sift(T **A, int i, int m, long long &comp);
        static bool isSorted(T** A, int n);
};

// Проверить
template <class T>
bool Sort<T>::isSorted(T** A, int n){
    for (int i = 1; i < n; i++) {
            if (*A[i - 1] > *A[i]) {
                return false;
            }
        }
    return true;
}

// Shell
template <class T> 
long long Sort<T>::Shell_sort(T **A, int n){
    long long comp = 0;
    int i, h, j;
    for (h = 1; h <= n / 9; h = h * 3 + 1);

    while (h >= 1){
        for (i = h; i < n; i++){
            for (j = i - h; j >= 0 && ++comp && *A[j] > *A[j+h]; j -= h){
                std::swap(*A[j], *A[j+h]);
            }
        }
        h = (h - 1) / 3;
    }

    return comp;
}

//Heap

template <class T>
void Sort<T>::sift(T **A, int i, int m, long long &comp){
    int j = i, k = i * 2 + 1;	 // k - левый сын
    while (k <= m) 
    {
        if (k<m && ++comp && *A[k] < *A[k+1]) 
            k++; // k - больший сын
        if (++comp && *A[j] < *A[k]){
            std::swap(A[j], A[k]); 
            j = k; 
            k = k * 2+1; 
        }
        else break;
    }
}

template <class T>
long long Sort<T>::Heap_sort(T **A, int n){
    long long comp = 0;
    int i, m;
     // построение пирамиды
    for (i = n / 2; i >= 0; i--) 
        sift(A, i, n-1, comp);
    // сортировка массива
    for (m = n - 1; m >= 1; m--)
    {
        std::swap(A[0], A[m]);
        sift(A, 0, m-1, comp);
    }

    return comp;
}

#endif