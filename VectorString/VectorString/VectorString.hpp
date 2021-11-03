#ifndef _VECTOR_STRING_
#define _VECTOR_STRING_
#include <string>
#include <memory>

namespace pic10b {
    class VectorString {
    public:
        /**
         Default Constructor: sets vec_size at 0, vec_capacity at 1, and creates dynamic array with the capacity of vec_capacity
         */
        VectorString();
        
        
        /**
         Constructor accepts size input
         @param sz the size input for the vector size
         */
        VectorString(const std::size_t& sz);
        
        
        /**
         Constructor that accepts a size and string: vec_capacity is twice the size, dynamic array has the capacity of vec_capacity, and all string variables initialized with the string
         @param sz the size input for the vector size
         @param str the string input
         */
        VectorString(const std::size_t& sz, const std::string& str);
        
        
        /**
         Copy constructor that creates a copy of an already existing vector
         @param vs the vector that is being copied
         */
        VectorString(const VectorString& vs);
        
        
        /**
         Move constructor that moves the resources of an rvalue to an lvalue object
         @param vs the rvalue vector that is being copied
         */
        VectorString(VectorString&& vs);
        
        
        /**
         Copy assignment operator
         @param rhs the vector on the right-hand-side of the assignment
         */
        VectorString& operator = (const VectorString& rhs);
        
        
        // Move assignment operator
        /**
         Move assignment operator
         @param rhs the vector on the right-hand-side of the assignment
         */
        VectorString& operator = (VectorString&& rhs);
        
        
        /**
         Acts like push_back of an actual vector: adds an element at the end
         @param str the string input that will be added at the end of the vector
         */
        void push_back(const std::string& str);
        
        
        /**
         Acts like pop_back of an actual vector: removes the last element
         */
        void pop_back();
        
        
        /**
         Deletes an element at a given position and shifts subsequent elements backwards
         @param num the position of the vector
         */
        void deleteAt(const size_t& num);
        
        
        /**
         Inserts an element at a given position and shifts elements forward
         @param num the position of the vector
         */
        void insertAt(const size_t& num, const std::string& str);
        
        
        /**
         Accesses the size of the vector
         @return the number of elements in the vector (the size)
         */
        const size_t& size() const;
        
        
        /**
         Accesses the actual capacity of the dynamic array
         @return the underlying size of the dynamic array (the capacity)
         */
        const size_t& capacity() const;
        
        
        /**
         Accesses a specific element of the dynamic array (vector)
         @return the specific element of the dynamic array (vector
         */
        std::string& at(const size_t& num) const;
        
        
    private:
        size_t vec_size;
        size_t vec_capacity;
        std::unique_ptr<std::string[]> ptr;
    };
}


#endif
