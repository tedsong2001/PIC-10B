#ifndef _EMPLOYEE_
#define _EMPLOYEE_

#include <iostream>
#include <string>
#include <fstream>

class Employee {
public:
    /**
     Constructor that accepts name and email address
     @param _name the name input
     @param _email the email address input
     */
    Employee(std::string _name, std::string _email);
    
    
    /**
     Constructor that accepts an input file stream
     @param in_file the input file stream
     */
    Employee(std::ifstream& in_file);
    
    
    /**
     Prints directory information
     */
    void print() const;
    
    
    /**
     Writes the name, email, and id of the employee to a file
     */
    virtual void write_data(std::ofstream& out_file) const;
    
    
    /**
     Purely virtual function for printing payments
     */
    virtual void print_pay() const = 0;
    
    
    /**
     Purely virtual function for saving employee file
     */
    virtual void save() const = 0;
    
    
    /**
     Accesses name
     @return name of employee
     */
    const std::string& get_name() const;
    
    
    /**
     Accesses id
     @return id of employee
     */
    const unsigned int& get_id() const;
    

    /**
     Destructor
     */
    virtual ~Employee() = default;
    
    
    /**
     Re-enables copy constructor
     */
    Employee(const Employee&) noexcept = default;
    
    
    /**
     Re-enables move constructor
     */
    Employee(Employee&&) noexcept = default;
    
    
private:
    std::string name; // employee's name
    std::string email; // employee's email address
    unsigned int id; // employee's id
    static unsigned int next_id; // stores the value of the next id to be created
};

/**
 Finds the next available id number
 @return returns the next available id number
 */
unsigned int find_next_id();


#endif
