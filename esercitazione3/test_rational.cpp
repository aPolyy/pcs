#include <iostream>
#include "rational.hpp"

int main() {

    rational <int> p(2, 4);
    rational <int> q(6, 9);
    std::cout << p << ", " << q << std::endl << std::endl;
    
    std::cout << p + q << std::endl;
    std::cout << p - q << std::endl;
    std::cout << p * q << std::endl;
    std::cout << p / q << std::endl;
    
    std::cout << std::endl;
    
    p += q;
    std::cout << p << std::endl;
    p -= q;
    std::cout << p << std::endl;
    p *= q;
    std::cout << p << std::endl;
    p /= q;
    std::cout << p << std::endl;
    
    rational<int> pInf(10, 0);
    rational<int> mInf(-10, 0);
    rational<int> NaN(0, 0);
    
    std::cout << pInf << ", " << mInf << ", " << NaN << std::endl << std::endl;
    
    std::cout << pInf + mInf << std::endl;
    std::cout << pInf - mInf << std::endl;
    std::cout << pInf * mInf << std::endl;
    std::cout << pInf / mInf << std::endl;

    std::cout << std::endl;
    
    std::cout << NaN + p << std::endl;
    std::cout << NaN + pInf << std::endl;
    
    std::cout << std::endl;

    return 0;
}