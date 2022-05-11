#include "ComplexNumbers.hpp"

// constructor that reads in a string
Complex::Complex(const std::string& s) : Complex() {
    
    std::stringstream ss(s); // creates a stringstream out of the input string
    
    double num = 0; // will hold the number that is read
    char c; // will get each char of the string
    std::string number = ""; // will contain a number as c is added onto this string
    int sign = 1; // 1 if the previous sign was +, -1 if the previous sign was -
    
    while (true) {
        ss.get(c); // gets the char
        
        if (ss.eof()) { // if the eof is reached, break from while loop
            break;
        }
        
        if ((c >= '0' && c <= '9') || c == '.') { // if c is a number or a decimal point
            number += c; // add it onto the number string
        }
        else if (c == 'i') { // if c is an i
            std::stringstream temp(number); // get stringstream of number
            temp >> num; // read in the num
            if (num == 0) { // if the num is 0, it means that i is alone --> signifies i or -i
                imag += sign;
            }
            else { // if num is not 0, it means that imaginary value is greater than 1 or lesser than -1
                imag += (num * sign); // add the num to imaginary
            }
            number = ""; // clear out number
            num = 0; // reset num
        }
        else if (c == '+') { // if c is a +
            std::stringstream temp(number); // get stringstream of number
            temp >> num; // read in the num
            real += (num * sign); // add the num to real, depending on sign
            number = ""; // clear out number
            sign = 1; // set sign as positive
            num = 0; // reset num
        }
        else if (c == '-') { // if c is a -
            std::stringstream temp(number); // get stringstream of number
            temp >> num; // read in the num
            real += (num * sign); // add the num to real, depending on sign
            number = ""; // clear out number
            sign = -1; // set sign as negative
            num = 0; // reset num
        }
        else { // if any other char is in the string, thrwo error
            throw std::logic_error("bad input string: [" + s + "]");
        }
    }
    
    // read in the final value that wasn't read in the case the last term wasn't imaginary
    std::stringstream temp(number); // get stringstream of number
    temp >> num; // read in num
    real += (num * sign); // add the num to real, depending on sign

}

// Subscript operator
double& Complex::operator[](const std::string& s) {
    if (s == "real") {
        return real;
    }
    else if (s == "imag") {
        return imag;
    }
    else {
        throw std::out_of_range("invalid address: " + s);
    }
}

// Subscript operator, const overloaded
const int Complex::operator[](const std::string& s) const {
    if (s == "real") {
        return real;
    }
    else if (s == "imag") {
        return imag;
    }
    else {
        throw std::out_of_range("invalid address: [" + s + "]");
    }
}

// Converts to string
Complex::operator std::string() const {
    
    std::string s = ""; // will contain the string output of the complex number
    
    if (real == 0 && imag == 0) { // if real and imag are both 0, then set s to 0
        s = "0";
    }
    else { // if real and/or imag have some value
        
        if (real == 0) { // if real is 0
            if (imag == 1) { // if imag is 1, set s to i
                s = "i";
            }
            else if (imag == -1) { // imag is -1, set s to -i
                s = "-i";
            }
            else { // if imag is a non-zero number, format output
                s += dtos(imag) + "i";
            }
        }
        else { // if real is not 0
            s += dtos(real); // add the real part to s
            
            if (imag == 1) { // if imag is 1, add "+i" to s
                s += "+i";
            }
            else if (imag == -1) { // if imag is -1, add "-i" to s
                s += "-i";
            }
            else if (imag != 0) { // if imag is a non-zero number, format output
                if (imag > 0) {
                    s += "+";
                }
                s += dtos(imag) + "i";
            }
        }
    }
    
    
    return s; // return the string output
}

// helper function that converts a double to a string, without trailing 0s or decimal point
const std::string Complex::dtos(const double& x) const {
    
    if (x == 0) { // if x is 0, then just return "0"
        return "0";
    }
    
    std::string num = std::to_string(x); // create string version of x
    
    for (size_t i = num.length()-1; i >= 0; --i) { // going thru num, starting from last character
        if (num[i] == '0' || num[i] == '.') { // if the character is 0, then pop back
            num.pop_back();
        }
        else { // if the first non-zero character is reached, then break from for loop
            break;
        }
    }
    
    return num; // return num
}

// ostream operator
std::ostream& operator<<(std::ostream& out, const Complex& c) {
    
    out << std::string(c);
    
    return out; // return the ostream
}

// istream operator
std::istream& operator>>(std::istream& in, Complex& c) {
    in >> c.real >> c.imag; // reads the two doubles
    
    if (in.fail()) { // if fail, then throw error
        throw std::runtime_error("read error");
    }
    
    return in; // return the istream
}

