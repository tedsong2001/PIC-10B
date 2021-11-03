#include "Complex.h"

// Constructor
Complex::Complex(const std::string& input) : real(0), imaginary(0) {
    std::stringstream s(input);
    double x = 0.;
    char sign = '+';
    
    std::string num = "";
    for (size_t i = 0; i < input.length(); ++i) {
        if ( (input[i] == '+') || (input[i] == '-')) { // if signs
            std::stringstream real_stream(num);
            real_stream >> x;
            
            if (sign == '+') {
                real += x; // adds number to real
            }
            else {
                real += (-x);
            }
            
            num = ""; // reset
            x = 0;
            
            if (input[i] == '+') { // sign changes
                sign = '+';
            }
            else {
                sign = '-';
            }
        }
        if ( input[i] == 'i') { // if imaginary
            if (num == "") {
                if ( sign == '+') {
                    imaginary += 1; // updates imaginary
                }
                else {
                    imaginary += (-1);
                }
                num = "";
            }
            else {
                std::stringstream imag_stream(num);
                imag_stream >> x;
                if (sign == '+') {
                    imaginary += x; // updates imginary
                }
                else {
                    imaginary += (-x);
                }
                num = "";
            }
        }
        else {
            num += input[i]; //adds numbers
        }
    }
}

// []
double& Complex::operator[](const std::string& idx) {
    if (idx == "real") {
        return real; // returns real part of complex number
    }
    else if (idx == "imag") {
        return imaginary; // returns imaginary part of complex number
    }
    else {
        throw std::out_of_range("invalid index: " + idx);
        // throws an error, not caught
    }
}

// [] overloaded on const
double Complex::operator[](const std::string& idx) const {
    if (idx == "real") {
        return real; // returns real part of complex number
    }
    else if (idx == "imag") {
        return imaginary; // returns imaginary part of complex number
    }
    else {
        throw std::out_of_range("invalid index: " + idx);
        // throws an error, not caught
    }
}

// user defined literal
Complex::operator std::string() const {
    std::string real_num = std::to_string(real);
    std::string imag_num = std::to_string(imaginary);
    
    // remove 0 and . for real_num
    for (size_t i = real_num.length() - 1; i > 0; --i) {
        // goes through each character of real_num
        if (real_num[i] == '0') { // if char is 0
            real_num.pop_back(); // removes 0
        }
        else if (real_num[i] == '.') { // if char is .
            real_num.pop_back(); // removes .
            break; // breaks loop
        }
        else { // if char is not 0 or .
            break; // breaks loop
        }
    }
    
    // remove 0 and . for imag_num
    for (size_t i = imag_num.length() - 1; i > 0; --i) {
        // goes through each character of imag_num
        if (imag_num[i] == '0') { // if char is 0
            imag_num.pop_back(); // removes 0
        }
        else if (imag_num[i] == '.') { // if char is .
            imag_num.pop_back(); // removes .
            break; // breaks loop
        }
        else { // if char is not 0 or .
            break; // breaks loop
        }
    }
    
    std::string complex_num = ""; // will contain complex num
    if (imag_num[0] == '-') { // if imag_num is negative
        if (imaginary == -1) { // if imaginary is -1
            complex_num = real_num + "-i";
        }
        else { // if imaginary is any other negative number
            complex_num = real_num + imag_num + 'i';
        }
    }
    else { // if imag_num is not negative
        if (imaginary == 1) { // if imaginary is 1
            complex_num = real_num + "i";
        }
        else if (imaginary == 0) { // if imaginary is 0
            complex_num = real_num;
        }
        else { // if imaginary is any other positive number
            complex_num = real_num + '+' + imag_num + 'i';
        }
    }
    
    return complex_num; // returns the string holding complex num
}

// <<
std::ostream& operator<<(std::ostream& out, const Complex& c) {
    if (c["imag"] > 0) { // if imag is positive
        if (c["imag"] == 1) { // if imag is 1
            out << c["real"] << "+i";
        }
        else { // if imag is every other positive number
            out << c["real"] << '+' << c["imag"] << 'i';
        }
    }
    else if (c["imag"] < 0) { // if imag is negative
        if (c["imag"] == -1) { // if imag is -1
            out << c["real"] << "-i";
        }
        else { // if imag is every other negative number
            out << c["real"] << c["imag"] << 'i';
        }
    }
    else { // if imag is 0
        out << c["real"];
    }
    return out; // returns output
}

// >>
std::istream& operator>>(std::istream& in, Complex& c) {
    in >> c["real"] >> c["imag"]; // reads in real and imag
    
    if ( in.fail() ) { // error message if input fail
        throw std::runtime_error("istream error");
    }
    
    return in; // returns input
}
