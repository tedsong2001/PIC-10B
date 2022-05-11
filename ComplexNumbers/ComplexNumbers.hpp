#ifndef ComplexNumbers_hpp
#define ComplexNumbers_hpp

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

class Complex {
    
private:
    double real, imag;
    
public:
    
    /**
     Default constructor
     @param _real the real part of the complex number
     @param _imag the imaginary part of the complex number
     */
    constexpr Complex(double _real = 0, double _imag = 0) : real(_real), imag(_imag) {}
    
    /**
     Constructor that accepts string
     @param s the string
     */
    Complex(const std::string& s);
        
    /**
     Binary += operator
     @param rhs Complex number on the right-hand-side of the +=
     @return sum of the 2 complex numbers
     */
    constexpr Complex& operator+=(const Complex& rhs) {
        // add up the real and imag
        real += rhs.real;
        imag += rhs.imag;
        
        return *this; // return the sum (left-hand complex number will be changed)
    }
    
    /**
     Unary + operator
     @return copy of the complex number
     */
    constexpr Complex operator+() const {
        return Complex(real, imag);
    }
    
    /**
     Prefix ++ (unary)
     @return incremented Complex number
     */
    constexpr Complex& operator++() {
        ++real;
        return *this;
    }
    
    /**
     Postfix ++ (binary)
     @return copy of the original Complex number
     */
    constexpr Complex operator++(int unused) {
        Complex copy(*this); // create a copy
        ++real; // increment the real part of the original
        return copy; // return the copy
    }
    
    /**
     Binary -= operator
     @param rhs Complex number on the right-hand-side of -=
     @return difference of the complex numbers
     */
    constexpr Complex& operator-=(const Complex& rhs) {
        // subtract the real and imag
        real -= rhs.real;
        imag -= rhs.imag;
        
        return *this; // return the difference (left-hand complex number will be changed
    }
    
    /**
     Unary - operator
     @return negated complex number
     */
    constexpr Complex operator-() const {
        return Complex(-real, -imag);
    }
    
    /**
     Prefix -- (unary)
     @return decremented Complex number
     */
    constexpr Complex& operator--() {
        --real;
        return *this;
    }
    
    /**
     Postfix -- (binary)
     @return copy of the original Complex number
     */
    constexpr Complex operator--(int unused) {
        Complex copy(*this); // create a copy
        --real; // decrement the real part of the original
        return copy; // return the copy
    }
    
    /**
     Binary *= operator
     @param rhs Complex number on the right-hand-side of the *=
     @return product of two complex numbers
     */
    constexpr Complex operator*=(const Complex& rhs) {
        int _real = (real * rhs.real) - (imag * rhs.imag); // get the real part of the product
        int _imag = (imag * rhs.real) + (real * rhs.imag); // get the imag part of the product
        
        // update the member variables
        real = _real;
        imag = _imag;
        
        return *this; // return the product (left-hand complex number will be changed
    }
    
    /**
     Binary /= operator
     @param rhs Complex number on the right-hand-side of the /=
     @return quotient of two complex numbers
     */
    constexpr Complex operator/=(const Complex& rhs) {
        // get the real and imag part of the quotient
        int _real = ((real * rhs.real) + (imag * rhs.imag)) / ((rhs.real * rhs.real) + (rhs.imag * rhs.imag));
        int _imag = ((imag * rhs.real) - (real * rhs.imag)) / ((rhs.real * rhs.real) + (rhs.imag * rhs.imag));
        
        // update the member variables
        real = _real;
        imag = _imag;
        
        return *this; // return the quotient (left-hand complex number will be changed
    }
    
    /**
     Unary ~ operator
     @return the conjugate of a complex number
     */
    constexpr Complex operator~() const {
        return Complex(real, -imag);
    }
    
    /**
     Call operator
     @return the complex number set to 0
     */
    constexpr Complex& operator()() {
        // set real and imag to 0
        real = 0;
        imag = 0;
        
        return *this; // return the updated complex number
    }
    
    /**
     Subscript operator
     @param s string
     @return either the real part or imag part of complex number, error if invalid address
     */
    double& operator[](const std::string& s);
    
    /**
     Subscript operator (const overload)
     @param s string
     @return either the real part or imag part of complex number, error if invalid address
     */
    const int operator[](const std::string& s) const;
    
    /**
     Converts from Complex number to string
     @return the string output
     */
    operator std::string() const;
        
    /**
     Helper function that converts a double to a string
     @param x the value of the double
     @return string form of the double
     */
    const std::string dtos(const double& x) const;
        
    friend std::istream& operator>>(std::istream& in, Complex& c); // allows istream operator to access private variables
};

/**
 Binary + operator
 @param left Complex number on the left of +
 @param right Complex number on the right of +
 @return the sum of two complex numbers
 */
constexpr Complex operator+(Complex left, const Complex& right) {
    return left += right;
}

/**
 Binary - operator
 @param left Complex number on the left of -
 @param right Complex number on the right of -
 @return the difference of two complex numbers
 */
constexpr Complex operator-(Complex left, const Complex& right) {
    return left -= right;
}

/**
 Binary * operator
 @param left Complex number on the left of *
 @param right Complex number on the right of *
 @return the product of two complex numbers
 */
constexpr Complex operator*(Complex left, const Complex& right) {
    return left *= right;
}

/**
 Binary / operator
 @param left Complex number on the left of /
 @param right Complex number on the right of /
 @return the quotient of two complex numbers
 */
constexpr Complex operator/(Complex left, const Complex& right) {
    return left /= right;
}

/**
 Formats the output
 @param out ostream that will be returned
 @param c complex number
 @return formatted output
 */
std::ostream& operator<<(std::ostream& out, const Complex& c);


/**
 Reads two doubles and puts them in the complex number
 @param in istream
 @param c complex number
 @return istream
 */
std::istream& operator>>(std::istream& in, Complex& c);


/**
 Checks if a complex number is lesser than another
 @param left Complex number left of <
 @param right Complex number right of <
 @return true if left is lesser, false if not
 */
constexpr bool operator<(const Complex& left, const Complex& right) {
    double l_real = left["real"];
    double l_imag = left["imag"];
    double r_real = right["real"];
    double r_imag = right["imag"];
    
    if (l_real < r_real) { // if the real part of left is lesser, return true
        return true;
    }
    else if (l_real > r_real) { // if the real part of left is greater, return false
        return false;
    }
    
    // Code reaches here if the real parts are equivalent
    
    if (l_imag < r_imag) { // if the imag part of left is lesser, return true
        return true;
    }
    
    return false; // if code reaches here, left is not lesser than right so return false
}

/**
 Checks if two complex numbers are equal
 @param left Complex number left of ==
 @param right Complex number right of ==
 @return true if equal, false if not
 */
constexpr bool operator==(const Complex& left, const Complex& right) {
    return (left["real"] == right["real"]) && (left["imag"] == right["imag"]);
}

/**
 Checks if a complex number is greater than another
 @param left Complex number left of >
 @param right Complex number right of >
 @return true if left is greater, false if not
 */
constexpr bool operator>(const Complex& left, const Complex& right) {
    double l_real = left["real"];
    double l_imag = left["imag"];
    double r_real = right["real"];
    double r_imag = right["imag"];
    
    if (l_real > r_real) { // if the real part of left is greater, return true
        return true;
    }
    else if (l_real < r_real) { // if the real part of left is lesser, return true
        return false;
    }
    
    // Code reaches here if the real parts are equivalent
    
    if (l_imag > r_imag) { // if the imag part of left is greater, return true
        return true;
    }
    
    return false; // if code reaches here, left is not greater than right so return false
}

/**
 Checks if a complex number is lesser or equal to another
 @param left Complex number left of <=
 @param right Complex number right of <=
 @return true if left is lesser or equal to right, false if not
 */
constexpr bool operator<=(const Complex& left, const Complex& right) {
    return (left < right) || (left == right);
}

/**
 Checks if a complex number is greater or equal to another
 @param left Complex number left of >=
 @param right Complex number right of >=
 @return true if left is greater or equal to right, false if not
 */
constexpr bool operator>=(const Complex& left, const Complex& right) {
    return (left > right) || (left == right);
}

/**
 Checks if a complex number is not equal to another
 @param left Complex number left of !=
 @param right Complex number right of !=
 @return true if left not equal to right, false if equal
 */
constexpr bool operator!=(const Complex& left, const Complex& right) {
    return !(left == right);
}

/**
 User-defined literal
 @param x the value of the literal (imaginary part)
 @return complex number created with user-defined literal
 */
constexpr Complex operator ""_i(long double x) {
    double i = x;
    return Complex(0, i);
}



#endif /* ComplexNumbers_hpp */
