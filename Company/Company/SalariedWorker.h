#ifndef _SALARIED_WORKER_
#define _SALARIED_WORKER_

#include "Employee.h"

class SalariedWorker : public Employee {
public:
    /**
     Constructor that accepts name, email, and salary
     @param _name the name input
     @param _email the email input
     @param _salary the salary input
     */
    SalariedWorker(std::string _name, std::string _email, double& _salary);
    
    
    /**
     Constructor that accepts an input file stream
     @param in_file the input file stream
     */
    SalariedWorker(std::ifstream& in_file);
    
    
    /**
     Prints payment
     */
    void print_pay() const override;
    
    
    /**
     Saves employee information to their file
     */
    void save() const override;
    
    
private:
    double salary; // employee's salary
};

#endif
