#include <string>
#include <sstream>
#include <iostream>
#include <vector>

bool inArray(char& c, std::vector<char>& v) {
    bool found = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        if (c == v[i]) {
            found = 1;
        }
    }
    return found;
}

int main() {
    
    std::cout << "Input string\n"
    std::string mine = "";
    std::cin >> mine;
    
    bool valid = 1;
    
    if (valid) {
        std::stringstream stream(mine); // a stringstream that reads in the complex number
        
        double real = 0; // will store real part
        double imaginary = 0; // will store imaginary part
        char sign = '+'; // will store the sign
        
        
        
        while (stream) {
            
            if (stream.peek() == '-' || stream.peek() == '+') { // if there is a sign char
                stream.get(sign); // stores that char into sign
            }
            
            double temp = 0; // temporary var that will hold an int
            char trash; // trash char. when there is 'i', trash will store that 'i'
            
            if (stream.peek() == 'i') {
                stream.get(trash);
                
                temp = 1;
                
                if (sign == '-') {
                    temp *= (-1);
                }
                
                imaginary += temp;
            }
            else {
                stream >> temp; // stream will read in an integer
                
                if (sign == '-') { // if the previous sign was a negative
                    temp *= (-1); // changes temp to negative
                }
                    
                if (stream.peek() == 'i') { // if the peek sees an 'i'
                    imaginary += temp; // then the integer will be added to imaginary
                    stream.get(trash); // trash will then store the 'i'
                }
                else { // if the peek does not see an i
                    real += temp; // integer will be added to real
                }
            }
        }
        
        std::cout << real << ' ' << imaginary << std::endl;
    }
    else {
        std::cout << "Invalid complex number" << '\n';
    }
    
    
    
    return 0;
}
