#include <concepts>
#include <iostream>
#include <numeric> // uso gcd

template <typename I> requires std::integral<I> // nb qui con tipi unsigned posso avere overflow con numeri negativi e/o sottrazioni
class rational {
    I num_;
    I den_;

    void simplify() {
        if (den_ == 0) {           // qui le uniche rappresentazioni ammissibili sono
                                   // NaN = 0/0, +Inf = 1/0 e -Inf = -1/0
            if (num_ != 0)
                num_ = (num_ > 0) ? 1 : -1;
        }
        else if (num_ == 0) 
            den_ = 1;
        else {                     // porto in rappresentazione unica
            I g = std::gcd(num_, den_);
            num_/= g;
            den_/= g;
            if (den_ < 0) {        // porto i segni al numeratore
                num_ = -num_;
                den_ = -den_;
            }
        }
    }

    // La logica di Inf e NaN è gestita da simplify
    // 0/0 è NaN e tutte le operazioni con un 0/0 continuano a restituire 0/0
    //
    // 1/0 e -1/0 sono +Inf e -Inf e le uniche cose da gestire separatemente sono
    // somma di infiniti con lo stesso segno
    // sottrazione di infiniti con segni diversi


public: 
    rational()
    : num_(I(0)), den_(I(1)) 
    {}

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

    // metto i check di Inf e NaN pubblici per usarli dopo con l'output
    bool isInf() const {
        return (num_!=0) && (den_==0);
    }

    bool isNaN() const {
        return (num_==0) && (den_==0);
    }

    rational& operator+=(const rational& other) {
        // a/b + c/d = (ad + bc)/bd
        if (isInf() && other.isInf() && (num_*other.num_ > 0)) 
            return *this;
        num_ = num_*other.den_ + other.num_*den_;
        den_ *= other.den_;
        simplify();
        return *this;
    }
    
    rational operator+(const rational& other) const {
        rational ans;
        if (isInf() && other.isInf() && (num_*other.num_ > 0)) {
            ans.num_ = num_;
            ans.den_ = 0;
            return ans;
        }
        ans.num_ = num_*other.den_ + other.num_*den_;
        ans.den_ = den_*other.den_;
        ans.simplify();
        return ans;
    }
    
    rational operator-=(const rational& other) {
        // a/b + (-c)/d = (ad - bc)/bd
        if (isInf() && other.isInf() && (num_*other.num_ < 0)) 
            return *this;
        num_ = num_*other.den_ - other.num_*den_;
        den_ *= other.den_;
        simplify();
        return *this;
    }
    
    rational operator-(const rational& other) const {
        rational ans;
        if (isInf() && other.isInf() && (num_*other.num_ < 0)) {
            ans.num_ = num_;
            ans.den_ = 0;
            return ans;
        }
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
    if (q.isNaN())
        os << "NaN";
    else if (q.isInf())
        os << (q.num() > 0 ? "+Inf" : "-Inf");
    else 
        os << q.num() << "/" << q.den();
    return os;
}