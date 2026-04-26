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

template<typename T>
void merge(std::vector<T>& vec, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    std::vector<T> L(n1);
    std::vector<T> R(n2);
    for (int i = 0; i < n1; i++) 
        L[i] = vec[p + i];
    for (int j = 0; j < n2; j++) 
        R[j] = vec[q + 1 + j];

    // todo: nelle slide è implementato con inf, qui ho messo un check sugli indici (e alloca n1+1, n2+1)
    // L[n1] = infinityT<T>;
    // R[n2] = infinityT<T>;

    int i = 0;
    int j = 0;
    for (int k = p; k <= r; k++) { //todo fixare gli indici qui
        if (i < n1 && (j >= n2 || L[i] <= R[j])) {
            vec[k] = L[i];
            i++;
        }
        else {
            vec[k] = R[j];
            j++;
        }
    }
    return;
}

template<typename T>
void mergesort(std::vector<T>& vec, int p, int r) {
    if (p < r) {
        int q = (p + r)/2;
        mergesort(vec, p, q);
        mergesort(vec, q+1, r);
        merge(vec, p, q, r);
    }
    return;
}

template<typename T>
int partition(std::vector<T>& vec, int p, int r) {
    T x = vec[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (vec[j] <= x) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i+1], vec[r]);
    return i+1;
}

template<typename T>
void quicksort(std::vector<T>& vec, int p, int r) {
    if (p < r) {
        int q = partition(vec, p, r);
        quicksort(vec, p, q-1);
        quicksort(vec, q+1, r);
    }
    return;
}
