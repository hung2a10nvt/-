#include <iostream>
#include <fstream>
#include <algorithm>
#include "Olympiad.h"

template<class T>
void ShellSort(T** A, int n){
    int i, h, j;
    for (h = 1; h <= n / 9; h = h * 3 + 1);

    while (h > 0){
        for (i = h; i < n; i++){
            T* temp = A[i];
            for (j = i; j >= h && *A[j - h] < *temp; j -= h){
                A[j] = A[j - h];
            }
            A[j] = temp;
        }
        h = h / 3; 
    }
}


int main(){
    srand(time(0));
    int n;
    std::cin >> n;
    
    Olympiad** List = new Olympiad*[n];
    // Случайные учасники
    for (int i = 0; i < n; ++i) {
        List[i] = new Olympiad(Olympiad::Random());
    }

    //
    ShellSort<Olympiad>(List, n);
    // std::reverse(List, List + n);
    std::ofstream outputFile("ranking.txt");
    outputFile << "Ranking of Participants: " << std::endl;
    for (int i = 0; i < n; i++){
        outputFile << *List[i] << std::endl << std::endl;
    }
    outputFile.close();

    for (int i = 0; i < n; ++i) {
        delete List[i];
    }
    delete[] List;

    return 0;
}