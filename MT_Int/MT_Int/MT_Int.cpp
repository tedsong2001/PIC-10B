#include "MT_Int.h"

// Default constructor
Int::Int() : p(nullptr) {} // sets p to nullptr

// Constructor accepting an int
Int::Int(int num) : p(new int(num)) {} // p points to the given int

// Copy constructor
Int::Int(const Int& my_Int) : p(new int(*my_Int.p)) {} // p now has the same p that my_Int has

// Move constructor
Int::Int(Int&& my_Int) : Int() { // default constructor invoked
    std::swap(p, my_Int.p); // swaps p
}

// Copy assignment operator
Int& Int::operator= (const Int& rhs) {
    if (this == &rhs) { // if self-assignment, return reference to the class
        return *this;
    }
    else {
        *p = *rhs.p; // copies p from rhs
        return *this; // returns the reference to the class
    }
}

// Move assignment operator
Int& Int::operator= (Int&& rhs) {
    std::swap(p, rhs.p); // swaps p
    return *this; // returns the reference to the class
}

// Changes the value that p points to
void Int::set(int num) {
    if (p == nullptr) { // if p points to null
        p = new int(num); // p now points to a new int
    }
    else {
        *p = num; // value at which p points to is now the value of num
    }
}

// Checks if p is nullptr or not
bool Int::valid() const {
    if (p == nullptr) { // if p is null
        return false; // returns false
    }
    else { // if p points to something
        return true; // returns true
    }
}

// Retrieves the int that p points to
int& Int::get() {
    return *p; // returns the int that p points to
}

// Retrieves the int that p points to (this function is overloaded on const)
int Int::get() const {
    return *p; // returns the int that p points to
}

// Destructor
Int::~Int() {
    delete p; // delete p
    p = nullptr; // p is set to nullptr
    if (p) { // if p is still valid
        std::cout << *p << '\n'; // dereference p
    }
    delete p; // delete p again just in case
    std::cout << "Thanos has snapped his fingers." << '\n'; // prints message after destruction
}
