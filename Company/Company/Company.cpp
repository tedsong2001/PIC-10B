#include "Company.h"

unsigned int Employee::next_id = 0; // static variable, next_id set to start at 0


Employee::Employee(std::string _name, std::string _email) : name(std::move(_name)), email(std::move(_email)) {
    next_id = find_next_id(); // finds the next available id number and sets next_id to make sure that next_id isn't set to an already existing id number
    id = next_id; // id is initialized with next_id
    next_id = find_next_id(); // finds the next available id number and sets next_id
}


Employee::Employee(std::ifstream& in_file) {
    
    /* basic format for each txt file is [employee type] '\t' [name] '\t' [email] '\t' [id]
     [employee type] is already recorded through the save functions */
    
    const char C = '\t'; // C is the tab character
    std::getline(in_file, name, C); // gets the name from the file, and then removes tab
    std::getline(in_file, email, C); // gets the email from the file, and then removes tab
    in_file >> id; // gets the id from the file
}


void Employee::print() const {
    std::cout << name << '\t' << id << '\t' << email << '\n'; // prints the name, id, and email
}


void Employee::write_data(std::ofstream& out_file) const {
    out_file << name << '\t' << email << '\t' << id; // writes name, email, and id onto file
}


const std::string& Employee::get_name() const {
    return name; // returns the name of an employee
}


const unsigned int& Employee::get_id() const {
    return id; // returns the id of an employee
}


HourlyWorker::HourlyWorker(std::string _name, std::string _email, double& _rate) : Employee(_name, _email), hours(0), rate(_rate) {} // constructs an hourly worker


HourlyWorker::HourlyWorker(std::ifstream& in_file) : Employee(in_file) {
    
    /* name, email, and id already recorded through the Employee constructor */
    
    in_file.ignore(); // ignores the tab that was after the id
    in_file >> hours; // gets the hours
    in_file.ignore(); // ignores the tab after hours
    in_file >> rate; // gets the rate
}


void HourlyWorker::set_hours(const unsigned int& hrs) {
    hours = hrs; // sets the hours worked
}


void HourlyWorker::print_pay() const {
    std::cout << get_name() << " receives $" << hours * rate << '\n'; // prints the payment info
}


void HourlyWorker::save() const {
    std::string file_name = "employee" + std::to_string(get_id()) + ".txt"; // creates file_name
    std::ofstream out_file; // creates output file stream
    out_file.open(file_name); // opens the output file
    out_file << "hourly" << '\t'; // writes "hourly" on the file
    write_data(out_file); // writes name, email, id on the file
    out_file << '\t' << hours << '\t' << rate; // writes the hours and hourly rate on the file
    out_file.close(); // closes the file
}


SalariedWorker::SalariedWorker(std::string _name, std::string _email, double& _salary) : Employee(_name, _email), salary(_salary) {} // constructs a salaried worker


SalariedWorker::SalariedWorker(std::ifstream& in_file) : Employee(in_file) {
    
    /* name, email, and id already recorded through the Employee constructor */
    
    in_file.ignore(); // ignores the tab after the id
    in_file >> salary; // gets the salary
}


void SalariedWorker::print_pay() const {
    std::cout << get_name() << " receives $" << salary << '\n'; // prints payment info
}


void SalariedWorker::save() const {
    std::string file_name = "employee" + std::to_string(get_id()) + ".txt"; // creates a file_name
    std::ofstream out_file; // creates an output file stream
    out_file.open(file_name); // opens output file
    out_file << "salaried" << '\t'; // writes "salaried" on the file
    write_data(out_file); // writes name, email, and id on the file
    out_file << '\t' << salary; // writes salary on the file
    out_file.close(); // closes the file
}


Company::Company() {
    size_t num = 0; // potential number on employee.txt file (basically, the potential id number)
    while (true) { // infinite loop, reads through the employee.txt files
        std::string file_name = "employee" + std::to_string(num) + ".txt"; // creates file_name
        std::ifstream in_file; // creates input file stream
        in_file.open(file_name); // opens file stream
        if (in_file.fail()) { // if file cannot be opened, there is no file with the id number
            break; // breaks the while loop, end of construction
        }
        else { // if file can be opened
            std::string type = ""; // string
            std::getline(in_file, type, '\t'); // gets the employee type, removes the tab
            if (type == "hourly") { // if type is hourly
                employees.push_back(std::make_shared<HourlyWorker>(in_file)); // adds Hourly worker into employees vector/list
            }
            else if (type == "salaried") { // if type is salaried
                employees.push_back(std::make_shared<SalariedWorker>(in_file)); // adds Salaried worker into employees vector/list
            }
        }
        in_file.close(); // file closed
        ++num; // increments to check the next file
    }
}


void Company::print_directory() const {
    std::cout << "There are " << employees.size() << " employees:" << '\n'; // prints total employees
    for (size_t i = 0; i < employees.size(); ++i) { // goes through the list of employees
        employees[i]->print(); // prints contact/directory information
    }
}


void Company::do_hours() {
    for (size_t i = 0; i < employees.size(); ++i) { // going through all the employees
        auto hourly_worker = std::dynamic_pointer_cast<HourlyWorker>(employees[i]); // dynamic pointer casting an employee
        if (hourly_worker) { // if the dynamic_pointer_cast is possible (if the worker is an HourlyWorker)
            std::cout << "How many hours did " << hourly_worker->get_name() << " work? "; //
            unsigned int hrs = 0; // creates hours variable
            std::cin >> hrs; // input hours an employee worked
            hourly_worker->set_hours(hrs); // sets the hours
            hourly_worker->save(); // updates employee information onto their file
        }
    }
}


void Company::print_payroll() const {
    for (size_t i = 0; i < employees.size(); ++i) { // going through all the employees
        employees[i]->print_pay(); // prints their payment
    }
}


void Company::create_salaried() {
    std::cin.ignore(); // for getline to work properly
    std::cout << "Enter name: ";
    std::string name_input = ""; // name_input string
    std::getline(std::cin, name_input); // inputs employee name
    std::cout << "Enter email: ";
    std::string email_input = ""; // email_input string
    std::cin >> email_input; // inputs employee email
    std::cout << "Enter salary: $";
    double salary_input = 0.; // salary_input variable
    std::cin >> salary_input; // inputs employee salary
    SalariedWorker salary_worker(name_input, email_input, salary_input); // creates a SalariedWorker
    salary_worker.save(); // saves the employee information
    employees.push_back(std::make_shared<SalariedWorker>(salary_worker)); // adds the employee onto the list of employees
}


void Company::create_hourly() {
    std::cin.ignore(); // for getline to work properly
    std::cout << "Enter name: ";
    std::string name_input = ""; // name_input string
    std::getline(std::cin, name_input); // inputs employee name
    std::cout << "Enter email: ";
    std::string email_input; // email_input string
    std::cin >> email_input; // inputs email
    std::cout << "Enter hourly rate: $";
    double rate_input = 0; // rate_input string
    std::cin >> rate_input; // inputs employee hourly rate
    HourlyWorker hourly_worker(name_input, email_input, rate_input); // creates an HourlyWorker
    hourly_worker.save(); // saves the employee information
    employees.push_back(std::make_shared<HourlyWorker>(hourly_worker)); // adds the employee onto the list
}


void Company::create_employee() {
    std::cout << "What type of employee?" << '\n'; // asks what type of employee to be created
    std::cout << "S - Salaried" << '\n';
    std::cout << "H - Hourly" << '\n';
    std::cout << "Abort (all other inputs)?";
    char type;
    std::cin >> type; // inputs respective character for type of employee to be created
    
    if (type == 'S') { create_salaried(); } // if user wants to create a SalariedWorker
    else if (type == 'H') { create_hourly(); } // if user wants to create an HourlyWorker
    else { std::cout << "creation aborted"; } // if user aborts creation
}


unsigned int find_next_id() {
    unsigned int id_number = 0; // potential id_number created
    while (true) { // infinite loop, reads through all employee.txt files
        std::string file_name = "employee" + std::to_string(id_number) + ".txt"; // creates potential file_name
        std::ifstream in_file; // creates an input file stream
        in_file.open(file_name); // opens input file
        if (in_file.fail()) { // if a file cannot open, it means that there is no file with the specific id_number
            return id_number; // id_number is returned (while loop is also broken)
        }
        else { // if a file can be opened, it means that a file with a specific id_number exists
            in_file.close(); // close the input file
            ++id_number; // increments id_number to check the next employee.txt file
        }
    }
}


void run_events() {
    
    Company my_company; // creates a Company
    
    while (true) { // infinite loop, constantly asks what user wants to do
        std::cout << "What would you like to do?" << '\n'; // menu
        std::cout << "C - Create Employee" << '\n';
        std::cout << "D - Display Current Directory" << '\n';
        std::cout << "H - Set Hours" << '\n';
        std::cout << "P - Print Payroll" << '\n';
        std::cout << "Quit (all other inputs)?";
        char input;
        std::cin >> input; // user inputs desired option
        
        if (input == 'C') { // if user wants to create an employee
            my_company.create_employee();
        }
        
        else if (input == 'D') { // if user wants to print the current directory
            my_company.print_directory();
        }
        
        else if (input == 'H') { // if user wants to set hours
            my_company.do_hours();
        }
        
        else if (input == 'P') { // if user wants to print payroll
            my_company.print_payroll();
        }
        
        else { // if user wants to quit
            break;
        }
        
        std::cout << '\n';
    }
}
