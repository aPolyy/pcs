#include "timecounter.h"
#include "sortings.h"
#include "randfiller.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    randfiller rf;
    timecounter tc;
    double time;
    for (int sz = 4; sz <= 8192; sz *= 2) {
        std::cout << "Dimensione: " << sz << std::endl;
        std::vector<int> vi(sz);
        rf.fill(vi, -10000, 10000);
        
        std::vector<int>vi_copy(sz);
        for (int i = 0; i < sz; i++)
            vi_copy[i] = vi[i];

        tc.tic();
        bubblesort(vi_copy);
        time = tc.toc();
        std::cout << "Bubblesort: " << time << "s\n";

        for (int i = 0; i < sz; i++)
            vi_copy[i] = vi[i];

        tc.tic();
        insertionsort(vi_copy);
        time = tc.toc();
        std::cout << "Insertionsort: " << time << "s\n";

        for (int i = 0; i < sz; i++)
            vi_copy[i] = vi[i];

        tc.tic();
        selectionsort(vi_copy);
        time = tc.toc();
        std::cout << "Selectionsort: " << time << "s\n";

        for (int i = 0; i < sz; i++)
            vi_copy[i] = vi[i];

        tc.tic();
        std::sort(vi_copy.begin(), vi_copy.end());
        time = tc.toc();
        std::cout << "std::sort: " << time << "s\n";

    }
}