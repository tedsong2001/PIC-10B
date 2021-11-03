#include <vector>
#include <iostream>
#include <memory>
#include <string>

class A {
private:
    int a = 0;
public:
    int add() {
        return a + 2;
    }
};

int main() {
    
    A a;
    
    
    
    std::cout << (std::move(a)).add();
    
}
