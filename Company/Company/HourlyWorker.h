#ifndef _HOURLY_WORKER_
#define _HOURLY_WORKER_

#include "Employee.h"

class HourlyWorker : public Employee {
public:
    /**
     Constructor that accepts name, email, and hourly rate. Hours initially set to 0
     @param _name the name input
     @param _email the email input
     @param _rate the hourly rate input
     */
    HourlyWorker(std::string _name, std::string _email, double& _rate);
    
    
    /**
     Constructor that accepts an input file stream
     @param in_file the input file stream
     */
    HourlyWorker(std::ifstream& in_file);
    
    
    /**
     Sets the hours worked
     @param hrs the number of hours worked
     */
    void set_hours(const unsigned int& hrs);
    
    
    /**
     Prints payment
     */
    void print_pay() const override;
    
    
    /**
     Saves employee information to their file
     */
    void save() const override;

    
private:
    unsigned int hours; // hours worked
    double rate; // hourly pay rate
};


#endif
