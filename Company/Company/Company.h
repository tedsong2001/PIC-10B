#ifndef _COMPANY_
#define _COMPANY_

#include <vector>
#include <memory>
#include <iomanip>
#include "SalariedWorker.h"
#include "HourlyWorker.h"

class Company {
public:
    /**
     Default constructor that reads through all files and creates Employees of suitable type and stores them as pointers
     */
    Company();
    
    
    /**
     Displays how many employees are in the company and prints the directory
     */
    void print_directory() const;
    
    
    /**
     Runs through the vector and allows user to set hours for hourly workers
     */
    void do_hours();
    
    
    /**
     Runs through employees and calls print_pay function
     */
    void print_payroll() const;
    
    
    /**
     Creates a salaried worker
     */
    void create_salaried();
    
    
    /**
     Creates a hourly worker
     */
    void create_hourly();
    
    
    /**
     Asks user what type of employee they want to create
     */
    void create_employee();
    
    
private:
    std::vector<std::shared_ptr<Employee>> employees; // vector of employees
};

/**
 Runs the events
 */
void run_events();


#endif
