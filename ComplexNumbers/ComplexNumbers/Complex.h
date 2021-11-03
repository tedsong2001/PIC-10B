#ifndef _COMPLEX_
#define _COMPLEX_

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

class Complex {
private:
    double real; // stores the real part of the complex number
    double imaginary; // stores the imaginary part of the complex number

public:
    
    /**
     Default constructor: sets real and imaginary to 0, unless specific parameter is given
     @param _real input of real part of complex number
     @param _imaginary input of imaginary part of complex number
     */
    constexpr Complex(double _real = 0, double _imaginary = 0) :
        real(_real), imaginary(_imaginary) {}

    /**
     constructor accepting string
     @param input the string
     */
    Complex(const std::string& input);
    
    
    
//    Complex(const std::string& input) : real(0), imaginary (0) {
//        std::stringstream s(input);
//        double x = 0.;
//        char sign = '+';
//
//        while ( !s.eof() ) {
//            if ( (s.peek() == '+') || (s.peek() == '-') ) {
//                sign = s.get();
//            }
//
//            if ( s.peek() != 'i' ) {
//                s >> x;
//                if ( s.peek() != 'i' ) {
//                    if (sign == '+') {
//                        real += x;
//                    }
//                    else {
//                        real += (-x);
//                    }
//                }
//                else {
//                    if (sign == '+') {
//                        imaginary += x;
//                    }
//                    else {
//                        imaginary += (-x);
//                    }
//                }
//            }
//            else {
//                if (sign == '+') {
//                    imaginary += 1;
//                }
//                else {
//                    imaginary += (-1);
//                }
//            }
//        }
//
//    }
    
    /**
     Binary operator += to add two complex numbers, changing the left-hand-side
     @param rhs the complex number on the right-hand-side of operation
     @return the updated complex number on the left-hand-side of operation
     */
    constexpr Complex& operator+=(const Complex& rhs) {
        real += rhs.real; // updates the real part
        imaginary += rhs.imaginary; // updates the imaginary part
        return *this; // returns updated complex number
    }
    
    /**
     Unary operator + to return a copy of a complex number
     @return a copy of the complex number
     */
    constexpr Complex operator+() const {
        return Complex(real, imaginary); // returns a copy of the number
    }
    
    /**
     Unary operator ++ resembling the prefix, increments real part of complex number
     @return the updated complex number
     */
    constexpr Complex operator++() {
        ++real; // increments the real part of complex number
        return *this; // returns the updated complex number
    }
    
    /**
     Binary operator ++ resembling the postfix, increments real part of complex number
     @param unused an unused int for the compiler to tell the difference between pre vs. postfix
     @return the updated complex number
     */
    constexpr Complex operator++(int unused) {
        Complex copy(*this); // makes a copy of the complex number
        ++real; // increments the real part of complex number;
        return copy; // returns the copy with updated complex number
    }
    
    /**
     Binary operator += to subtract two complex numbers, changing the left-hand-side
     @param rhs the complex number on the right-hand-side of the operation
     @return the updated complex number on the left-hand-side of the operation
     */
    constexpr Complex& operator-=(const Complex& rhs) {
        real -= rhs.real; // updates the real part
        imaginary -= rhs.imaginary; // updates the imaginary part
        return *this; // returns the updated real part
    }
    
    /**
     Unary operator - to return complex number with negated parts
     @return complex number after real and imaginary parts are negated
     */
    constexpr Complex operator-() const {
        return Complex(-real, -imaginary); // returns with negated values
    }
    
    /**
     Unary operator -- resembling the prefix, decrements real part of complex number
     @return the updated complex number
     */
    constexpr Complex operator--() {
        --real; // decrements the real part of complex number
        return *this; // returns the updated complex number
    }
    
    /**
     Binary operator -- resembling the postfix, decrements real part of complex number
     @param unused an unused int for the compiler to tell the difference between pre vs. postfix
     @return the updated complex number
     */
    constexpr Complex operator--(int unused) {
        Complex copy(*this); // creates a copy of the complex number
        --real; // decrements the real part of complex number
        return copy; // returns the copy with updated complex number
    }
    
    /**
     Binary operator *= to multiply two complex numbers, changing the left-hand-side
     @param rhs the complex number on the right hand side of the operation
     @return the updated complex number on the left hand side of the operation
     */
    constexpr Complex& operator*=(const Complex& rhs) {
        double a = real;
        double b = imaginary;
        double c = rhs.real;
        double d = rhs.imaginary;
        real = (a * c) - (b * d); // updates real part
        imaginary = (b * c) + (a * d); // updates imaginary part
        return *this; // returns the updated complex number
    }
    
    /**
     Binary operator /= to divide two complex numbers, changing the left-hand-side
     @param rhs the complex number on the right hand side of the operation
     @return the updated complex number on the left hand side of the operation
     */
    constexpr Complex& operator/=(const Complex& rhs) {
        double a = real;
        double b = imaginary;
        double c = rhs.real;
        double d = rhs.imaginary;
        real = ( (a * c) + (b * d) ) / ( (c * c) + (d * d) );
            // updates real part
        imaginary = ( (b * c) - (a * d) ) / ( (c * c) + (d * d) );
            // updates imaginary part
        return *this; // returns the updated complex number
    }
    
    /**
     Unary operator ~ to return conjugate of complex number
     @return the conjugate of complex number
     */
    constexpr Complex operator~() {
        return Complex(real, -imaginary); // returns conjugate
    }
    
    /**
     Call operator taking no argument, sets real and imaginary part to 0
     @return the complex number with real and imaginary part set to 0
     */
    constexpr Complex& operator()() {
        real = 0; // sets real to 0
        imaginary = 0; // sets imaginary to 0
        return *this; // returns the updated complex number
    }
    
    /**
     Subscript operator, returning a part of the complex number
     @param idx an input, taking either "real" or "imag"
     @return real / imaginary part of complex number, or error if idx is out of range
     */
    double& operator[](const std::string& idx);
    
    /**
     Subscript operator, returning a part of the complex number (this func is overloaded on const)
     @param idx an input, taking either "real" or "imag"
     @return real / imaginary part of complex number, or error if idx is out of range
     */
    double operator[](const std::string& idx) const;
        
    /**
     Converts complex number to string
     @return the string containing complex number expression
     */
    operator std::string() const;
    
};


/**
 Binary operator + to add two complex numbers
 @param c1 a complex number
 @param c2 another complex number
 @return the sum of the two complex numbers
 */
constexpr Complex operator+(Complex c1, const Complex& c2) {
    // creates a copy of c1 so c1 will not change
    return c1 += c2; // returns the sum of c1 and c2
}

/**
 Binary operator - to subtract two complex numbers
 @param c1 a complex number
 @param c2 another complex number
 @return the difference of the two complex numbers
 */
constexpr Complex operator-(Complex c1, const Complex& c2) {
    // creates a copy of c1 so c1 will not change
    return c1 -= c2; // returns the difference of c1 and c2
}

/**
 Binary operator * to multiply two complex numbers
 @param c1 a complex number
 @param c2 another complex number
 @return the product of the two complex numbers
 */
constexpr Complex operator*(Complex c1, const Complex& c2) {
    // creates a copy of c1 so c1 will not change
    return c1 *= c2; // returns the product of c1 and c2
}

/**
 Binary operator / to divide two complex numbers
 @param c1 a complex number
 @param c2 another complex number
 @return the quotient of the two complex numbers
 */
constexpr Complex operator/(Complex c1, const Complex& c2) {
    // creates a copy of c2 so c2 will not change
    return c1 /= c2; // returns the quotient of c1 and c2
}

/**
 Operator << to print or display complex number
 @param out output stream
 @param c complex number
 @return the output stream
 */
std::ostream& operator<<(std::ostream& out, const Complex& c);


/**
 Operator >> to read in 2 double values
 @param in the input stream
 @param c the complex number
 @return the input stream
 */
std::istream& operator>>(std::istream& in, Complex& c);


/**
 Comparison operator < seeing if one complex num is less than another complex num
 @param c1 the complex num on the left
 @param c2 the complex num on the right
 @return true if c1 < c2, false if not
 */
constexpr bool operator<(const Complex& c1, const Complex& c2) {
    if ( c1["real"] == c2["real"] ) { // if the real part is the same
        return ( c1["imag"] < c2["imag"] ); // compares the imag part
    }
    else { // if real part is not the same
        return ( c1["real"] < c2["real"] ); // compares the real part
    }
}

/**
 Comparison operator == seeing if two complex num are equal
 @param c1 the complex num on the left
 @param c2 the complex num on the right
 @return true if c1 == c2, false if not
 */
constexpr bool operator==(const Complex& c1, const Complex& c2) {
    // if real part is the same
    if ( !(c1["real"] < c2["real"]) && !(c2["real"] < c1["real"]) ) {
        return ( !(c1["imag"] < c2["imag"]) && !(c2["imag"] < c1["imag"]) ); // returns if imaginary part is the same
    }
    else { // if real part is not the same
        return false; // returns
    }
}

/**
 Comparison operator > seeing if one complex num is greater than another complex num
 @param c1 the complex num on the left
 @param c2 the complex num on the right
 @return true if c1 > c2, false if not
 */
constexpr bool operator>(const Complex& c1, const Complex& c2) {
    if ( c1["real"] == c2["real"] ) { // if real part is the same
        return ( c1["imag"] > c2["imag"] ); // compares the imag part
    }
    else { // if real part is not the same
        return ( c1["real"] > c2["real"] ); // compares the real part
    }
}

/**
 Comparison operator <= seeing if one complex num is less than or equal to another complex num
 @param c1 the complex num on the left
 @param c2 the complex num on the right
 @return true if c1 <= c2, false if not
 */
constexpr bool operator<=(const Complex& c1, const Complex& c2) {
    return (c1 < c2) || (c1 == c2); // returns the bool
}

/**
 Comparison operator >= seeing if one complex num is greater than or equal to another complex num
 @param c1 the complex num on the left
 @param c2 the complex num on the right
 @return true if c1 >= c2, false if not
 */
constexpr bool operator>=(const Complex& c1, const Complex& c2) {
    return (c1 > c2) || (c1 == c2); // returns the bool
}

/**
 Comparison operator != seeing if two complex num are not equal
 @param c1 the complex num on the left
 @param c2 the complex num on the right
 @return true if c1 != c2, false if not
 */
constexpr bool operator!=(const Complex& c1, const Complex& c2) {
    return !(c1 == c2); // returns the bool
}

/**
 User defined literal, for imaginary number
 @param x value of imaginary number
 @return complex number, with the given value of imaginary number
 */
constexpr Complex operator""_i(long double x) {
    return Complex{ 0, static_cast<double>(x) };
    // returns the complex number
}

#endif
