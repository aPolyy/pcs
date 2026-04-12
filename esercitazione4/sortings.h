#pragma once

#include <vector>
#include <algorithm>

template<typename T>
bool is_sorted(const std::vector<T>& vec) {
    int sz = vec.size();
    if (sz == 0)
        return true;
    for (int i = 0; i < sz - 1; i++)
        if (vec[i] > vec[i + 1])
            return false;

    return true;
}

template<typename T>
void bubblesort(std::vector<T>& vec) {
    int sz = vec.size();

    if (sz == 0)
        return;

    for (int i = 0; i < sz - 1; i++) 
        for (int j = sz - 1; j > i; j--) 
            if (vec[j] < vec[j - 1])
                std::swap(vec[j], vec[j - 1]);

    return;
}

template<typename T>
void insertionsort(std::vector<T>& vec) {
    int sz = vec.size();

    if (sz == 0)
        return;

    for (int j = 1; j < sz; j++) {
        T key = vec[j];
        int i = j - 1;
        while (i >= 0 && vec[i] > key) {
            vec[i+1] = vec[i];
            i = i-1;
        }
        vec[i+1] = key;
    }
    return;
}

template<typename T>
void selectionsort(std::vector<T>& vec) {
    int sz = vec.size();

    if (sz == 0)
        return;

    for (int i = 0; i < sz - 1; i++) {
        int imin = i;
        for (int j = i + 1; j < sz; j++) 
            if (vec[j] < vec[imin])
                imin = j;
        std::swap(vec[i], vec[imin]);
    }
    return;
}
