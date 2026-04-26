#include "timecounter.h"
#include "sortings.h"
#include "randfiller.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[]) {
    randfiller rf;
    timecounter tc;
    double time;
    int N = 1000;
    int sz = 1000;
    if (argc == 3){
        N = std::stoi(argv[1]);
        sz = std::stoi(argv[2]);
    }

    std::cout << "Media ottenuta con " << N << " prove su vettori di dimensione " << sz << "\n\n";

    std::vector<std::vector<int>> vvi(N, std::vector<int>(sz));
    std::vector<std::vector<int>> vvi_copy(N, std::vector<int>(sz));
    for (int i = 0; i < N; i++) 
        rf.fill(vvi[i], -10000, 10000);

    // bubblesort
    vvi_copy = vvi;
    tc.tic();
    for (int i = 0; i < N; i++)
        bubblesort(vvi_copy[i]);
    time = (tc.toc())/((double) N);
    std::cout << "Bubblesort: " << time << "s\n";

    // insertionsort
    vvi_copy = vvi;
    tc.tic();
    for (int i = 0; i < N; i++)
        insertionsort(vvi_copy[i]);
    time = (tc.toc())/((double) N);
    std::cout << "Insertionsort: " << time << "s\n";

    // selectionsort
    vvi_copy = vvi;
    tc.tic();
    for (int i = 0; i < N; i++)
        selectionsort(vvi_copy[i]);
    time = (tc.toc())/((double) N);
    std::cout << "Selectionsort: " << time << "s\n";

    // mergesort
    vvi_copy = vvi;
    tc.tic();
    for (int i = 0; i < N; i++)
        mergesort(vvi_copy[i], 0, sz-1);
    time = (tc.toc())/((double) N);
    std::cout << "Mergesort: " << time << "s\n";
    
    // quicksort
    vvi_copy = vvi;
    tc.tic();
    for (int i = 0; i < N; i++)
        quicksort(vvi_copy[i], 0, sz-1);
    time = (tc.toc())/((double) N);
    std::cout << "Quicksort: " << time << "s\n";

    // std::sort
    vvi_copy = vvi;
    tc.tic();
    for (int i = 0; i < N; i++)
        sort(vvi_copy[i].begin(), vvi_copy[i].end());
    time = (tc.toc())/((double) N);
    std::cout << "std::sort: " << time << "s\n";

}