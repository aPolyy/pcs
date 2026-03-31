#include <concepts>
#include <iostream>
#include <numeric> // uso gcd

template <typename I> requires std::integral<I> // qua possono mettere roba unsigned, poi la sottrazione si rompe?
class rational {
    I num_;
    I den_;

    void simplify() {
        if (den_ == 0) {
            //todo
        }
        else if (num_ == 0) 
            den_ = 1;
        else {                     // rappresentazione unica
            I g = std::gcd(num_, den_);
            num_/= g;
            den_/= g;
            if (den_ < 0) {        // porto i segni al numeratore
                num_ = -num_;
                den_ = -den_;
            }
        }
    }

    // todo Implementare la logica di Inf e Nan
    // 2 strade
    // 1) usare le operazioni con 1/0 e 0/0 e mettere dei flag nelle print
    //    devo capire se è tutto coerente con quello che mi aspetto
    // 2) fare un template per Inf e Nan che interagisca con gli int

public: 
    rational()
    : num_(I(0)), den_(I(1)) 

    rational(const I& rnum, const I& rden)
    : num_(rnum), den_(rden)
    {
        simplify();
    }  

    I num() const {
        return num_;
    }

    I den() const {
        return den_;
    }

    rational& operator+=(const rational& other) {
        // a/b + c/d = (ad + bc)/bd
        num_ = num_*other.den_ + other.num_*den_;
        den_ *= other.den_;
        simplify();
        return *this;
    }
    
    rational operator+(const rational& other) const {
        rational ans;
        ans.num_ = num_*other.den_ + other.num_*den_;
        ans.den_ = den_*other.den_;
        ans.simplify();
        return ans;
    }
    
    rational operator-=(const rational& other) {
        // a/b + (-c)/d = (ad - bc)/bd
        num_ = num_*other.den_ - other.num_*den_;
        den_ *= other.den_;
        simplify();
        return *this;
    }
    
    rational operator-(const rational& other) const {
        rational ans;
        ans.num_ = num_*other.den_ - other.num_*den_;
        ans.den_ = den_*other.den_;
        ans.simplify();
        return ans;
    }
    
    rational operator*=(const rational& other) {
        // a/b * c/d = (ac)/(bd)
        num_ *= other.num_;
        den_ *= other.den_;
        simplify();
        return *this;
    }
    
    rational operator*(const rational& other) const {
        rational ans;
        ans.num_ = num_*other.num_;
        ans.den_ = den_*other.den_;
        ans.simplify();
        return ans;
    }
    
    rational operator/=(const rational& other) {
        // (a/b) / (c/d) = (ad)/(bc)
        num_*=other.den_;
        den_*=other.num_;
        simplify();
        return *this; 
    }

    rational operator/(const rational& other) const {
        rational ans;
        ans.num_ = num_*other.den_;
        ans.den_ = den_*other.num_;
        ans.simplify();
        return ans;
    }

};

template<typename I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& q) {
    os << q.num() << "/" << q.den();
    return os;
}