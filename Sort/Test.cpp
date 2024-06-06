#include "Sort.h"

int main(){
    srand(time(0));
    const int n = 1000000;
    long long comp;
    int* ascending = new int[n];
    int* descending = new int[n];
    int* random = new int[n];

    for (int i = 0; i < n; i++){
        ascending[i] = i;
        descending[i] = n - i;
        random[i] = rand() % n;
    }

    // массивы указателей для косвенной сорт
    int** ptrAsc = new int*[n];
    int** ptrDes = new int*[n];
    int** ptrRan = new int*[n];

    for (int i = 0; i < n; i++){
        ptrAsc[i] = &ascending[i];
        ptrDes[i] = &descending[i];
        ptrRan[i] = &random[i];
    }
    //Shell Sort
    std::cout << "Shell Sort: " << std::endl;
    comp = Sort<int>::Shell_sort(ptrAsc, n);
    std::cout << "Ascending Array comp: " << comp << std::endl;
    std::cout << "Is Sorted: " << (Sort<int>::isSorted(ptrAsc, n) ? "Yes" : "No") << std::endl;

    comp = Sort<int>::Shell_sort(ptrDes, n);
    std::cout << "Descending Array comp: " << comp << std::endl;
    std::cout << "Is Sorted: " << (Sort<int>::isSorted(ptrDes, n) ? "Yes" : "No") << std::endl;

    comp = Sort<int>::Shell_sort(ptrRan, n);
    std::cout << "Random Array comp: " << comp << std::endl;
    std::cout << "Is Sorted: " << (Sort<int>::isSorted(ptrRan, n) ? "Yes" : "No") << std::endl << std::endl;
    
    //Heap Sort
    std::cout << "Heap Sort(Pyramid Sort): " << std::endl;
    comp = Sort<int>::Heap_sort(ptrAsc, n);
    std::cout << "Ascending Array comp: " << comp << std::endl;
    std::cout << "Is Sorted: " << (Sort<int>::isSorted(ptrAsc, n) ? "Yes" : "No") << std::endl;

    comp = Sort<int>::Heap_sort(ptrDes, n);
    std::cout << "Descending Array comp: " << comp << std::endl;
    std::cout << "Is Sorted: " << (Sort<int>::isSorted(ptrDes, n) ? "Yes" : "No") << std::endl;

    comp = Sort<int>::Heap_sort(ptrRan, n);
    std::cout << "Random Array comp: " << comp << std::endl;
    std::cout << "Is Sorted: " << (Sort<int>::isSorted(ptrRan, n) ? "Yes" : "No") << std::endl;

    system("pause");
    return 0;
}