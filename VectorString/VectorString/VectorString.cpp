#include "VectorString.hpp"
using namespace pic10b;

/* default constructor
 vec_size is 0, vec_capacity is 1, ptr can hold strings and has capacity of 1 (vec_capacity) */
VectorString::VectorString() : vec_size(0), vec_capacity(1), ptr(new std::string[vec_capacity]) {}


/* constructor accepts size
 vec_capacity is twice of vec_size, ptr can hold strings and has capacity of vec_capacity */
VectorString::VectorString(const size_t& sz) : vec_size(sz), vec_capacity(sz * 2), ptr(new std::string[vec_capacity]) {}


/* constructor accepts size and string
 vec_capacity is twice of vec_size, string variables for ptr are initialized with the s */
VectorString::VectorString(const size_t& sz, const std::string& str) : vec_size(sz), vec_capacity(sz * 2), ptr(new std::string[vec_capacity]) {
    for (size_t i = 0; i < vec_size; ++i) { // for all string variables
        ptr[i] = str; // initialized with the input string
    }
}


// copy constructor
VectorString::VectorString(const VectorString& vs) : vec_size(vs.vec_size), vec_capacity(vs.vec_capacity), ptr(nullptr) {
    // vec_size and vec_capacity copied through initializer list
    
    ptr.reset(new std::string[vs.vec_capacity]); // ptr now has the same capacity of vs
    for (size_t i = 0; i < vs.vec_size; ++i) { // goes through each element of vs
        ptr[i] = vs.ptr[i]; // copies the element of vs
    }
}

// move constructor
VectorString::VectorString(VectorString&& vs) : VectorString() { // default constructor invoked
    std::swap(vec_size, vs.vec_size); // swaps the vec_size
    std::swap(vec_capacity, vs.vec_capacity); // swaps the vec_capacity
    std::swap(ptr, vs.ptr); // swaps the ptr
}


// copy assignment operator
VectorString& VectorString::operator = (const VectorString& rhs) {
    if (this == &rhs) { // if self-assign, just return the reference to the clas
        return *this;
    }
    else {
        vec_size = rhs.vec_size; // copies vec_size of rhs
        vec_capacity = rhs.vec_capacity; // copies vec_capacity of rhs
        ptr.reset(new std::string[rhs.vec_capacity]); // ptr now has the same capacity as rhs.ptr
        for (size_t i = 0; i < rhs.vec_size; ++i) { // goes through each element of rhs
            ptr[i] = rhs.ptr[i]; // copies the element of rhs
        }
        return *this; // returns the reference to the class
    }
}


// move assignment operator
VectorString& VectorString::operator = (VectorString&& rhs) {
    std::swap(vec_size, rhs.vec_size); // swaps the vec_size
    std::swap(vec_capacity, rhs.vec_capacity); // swaps the vec_capacity
    std::swap(ptr, rhs.ptr); // swaps the ptr
    
    return *this; // returns the reference to the class
}


// push_back mutator
void VectorString::push_back(const std::string& str) {
    if (vec_size < vec_capacity) { // if there is space in the dynamic array to add another element
        ptr[vec_size] = str; // adds the string input at the end of the vector
        ++vec_size; // updates the vector size
    }
    else { // if adding another element will cause the size to exceed the capacity of dynamic array
        vec_capacity *= 2; // doubles vec_size
        std::unique_ptr<std::string[]> temp(new std::string[vec_capacity]); // creates temporary dynamic array
        for (size_t i = 0; i < vec_size; ++i) { // goes through each element of dynamic array
            temp[i] = ptr[i]; // each element of ptr copied to temp
        }
        ptr.reset( temp.release() ); // ptr reverts to original state, except doubled capacity. temp points to null
        ptr[vec_size] = str; // adds the string input at the end of ptr
        ++vec_size; // updates vector size
    }
}


// pop_back mutator
void VectorString::pop_back() {
    --vec_size; // just reduces the vec_size
    // the value will still remain in memory but can be overwritten
}


// deleteAt mutator
void VectorString::deleteAt(const size_t& num) {
    for (size_t i = num; i < vec_size; ++i) { // from the element at the given position to the last element
        ptr[i] = ptr[i + 1]; // removes the element at the given position and shifts each element backwards
    }
    --vec_size; // updates vec_size
}


// insertAt mutator
void VectorString::insertAt(const size_t& num, const std::string& str) {
    if (vec_size < vec_capacity) { // if there is space in the dynamic array to add another element
        for (size_t i = vec_size; i > num; --i) { // backwards from last element to element at given position
            ptr[i] = ptr[i - 1]; // elements are shifted forward
        }
        ptr[num] = str; // adds the string to the desired position
        ++vec_size; // updates the vec_size
    }
    
    else { // if adding another element will cause the size to exceed the capacity of dynamic array
        vec_capacity *= 2; // doubles vec_size
        std::unique_ptr<std::string[]> temp(new std::string[vec_capacity]); // creates temporary dynamic array
        for (size_t i = 0; i < vec_size; ++i) { // goes through each element of dynamic array
            temp[i] = ptr[i]; // each element of ptr copied to temp
        }
        ptr.reset( temp.release() ); // ptr reverts to original state, except doubled capacity. temp points to null
        
        for (size_t k = vec_size; k > num; --k) { // // backwards from last element element at given position
            ptr[k] = ptr[k - 1]; // elements are shifted forward
        }
        ptr[num] = str; // adds the string to desired position
        ++vec_size; // updates the vec_size
    }
}


// accessor for vec_size
const size_t& VectorString::size() const {
    return vec_size; // returns the number of elements in the vector (the size)
}


// accessor for vec_capacity
const size_t& VectorString::capacity() const {
    return vec_capacity; // returns the size of the underlying dynamic array (the capacity)
}


// accessor for a specific element
std::string& VectorString::at(const size_t& num) const {
    return ptr[num]; // returns the specific element
}
