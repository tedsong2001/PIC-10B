#include "final_do.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>

void get_rid(std::string& s) {
    for (size_t i = 0; i < s.length() - 1; ++i) {
        s[i] = s[i+1];
    }
    s.pop_back();
}

void print(const std::string& s) {
    std::cout << s << std::endl;
}

int main() {
    std::string a("Hello");
    std::string b = "Bye";
    std::string c = "Bitch";
    
    do_for_each(get_rid, a, b, c);
    
    do_for_each(print, a, b, c);
    

    return 0;
}
