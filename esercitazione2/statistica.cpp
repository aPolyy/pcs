#include <iostream>
#include <cmath>
#include <algorithm>

int main() {
    static const int N = 6;
    double arr[N] = {1.1, 2.3, 4.5, 1.0, 2.5, 5.1};
    double Max = arr[0]; 
    double Min = arr[0]; 
    double Avg = arr[0]; 
    double Std_dev = std::pow(arr[0], 2);

    // Std_dev = sqrt(1/N * sum_k=1^N (x_i - Avg)^2) = ... = sqrt( 1/N * sum(k=1^N (x_i^2) - Avg^2 )

    for (int i = 1; i < N; i++) {
        Max = std::max(Max, arr[i]);
        Min = std::min(Min, arr[i]);
        Avg += arr[i];
        Std_dev += std::pow(arr[i], 2);
    }
    Avg /= N;
    Std_dev = std::sqrt(Std_dev/N - std::pow(Avg, 2));
    std::cout<< Max << std::endl << Min << std::endl << Avg << std::endl << Std_dev << std::endl;

}
