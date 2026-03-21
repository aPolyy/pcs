#include <iostream>

int main() {
    static const int N = 6;
    double arr[N] = {1.1, 2.3, 4.5, 1.0, 2.5, 5.1};
    double tmp;
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 0; i < N - 1; i++) {
            if (arr[i] > arr[i+1]) {
                tmp = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = tmp; 
                flag = true;
            }
        }
    }
    for (int i = 0; i < N; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
    return 0;
}