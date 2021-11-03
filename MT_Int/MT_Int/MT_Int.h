#ifndef _MT_INT_
#define _MT_INT_
#include <iostream>
#include <memory>

class Int {
public:
    /**
     Default constructor, sets p to nullptr
     */
    Int();
    
    /**
     Constructor, accepts an int and p points to the int
     @param num the given int that p will point to
     */
    Int(int num);
    
    /**
     Copy constructor
     @param my_Int the given Int that will be copy constructed from
     */
    Int(const Int& my_Int);
    
    /**
     Move constructor
     @param my_Int the rvalue instance of Int that will be move constructed from
     */
    Int(Int&& my_Int);
    
    /**
     Copy assignment operator
     @param rhs the instance of Int on the right-hand-side of the assignment
     */
    Int& operator= (const Int& rhs);
    
    /**
     Move assignment operator
     @param rhs the rvalue instance of Int on the right-hand-side of the assignment
     */
    Int& operator= (Int&& rhs);
    
    /**
     Mutator, changes the value that P points to
     @param num the new value that P will point to
     */
    void set(int num);
    
    /**
     Accessor, checks if p is valid for dereferencing (seeing if p is nullptr or not)
     @return true if p is not null, false if p is null
     */
    bool valid() const;
    
    /**
     Accessor, retrieves the int that p points to
     @return the int that p points to
     */
    int& get();
    
    /**
     Accessor, retrieves the int that p points to (function is overloaded on const)
     @return the int that p points to
     */
    int get() const;
    
    /**
     Destructor
     */
    ~Int();
    
private:
    int* p; // points to a value on the heap
};

#endif
