#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "randfiller.h"
#include "sortings.h"

int main()
{
    // test random sugli interi
    randfiller rf;
    for (int i = 0; i < 100; i++) {
        int sz = std::rand() % 1000 + 1;
        std::vector<int> vi(sz);
        rf.fill(vi, -10000, 10000);
        insertionsort<int>(vi);
        if (is_sorted<int>(vi) == false)
            return EXIT_FAILURE;
    }

    // todo?? test su float e double

    // test su stringhe scelte
    std::vector<std::string> vs = {"pasta", "pizza", "panino", "birra", "hamburger", "quadro", "calcio", "pallone", "ombrellone", "piscina"};
    insertionsort<std::string>(vs);
    if (is_sorted<std::string>(vs) == false)
            return EXIT_FAILURE;
            
    return EXIT_SUCCESS;
}