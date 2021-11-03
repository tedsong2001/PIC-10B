#include "Likelihood.h"

std::mutex MUTEX; // global mutex

namespace pic10b {

    // Constructor
    Simulation::Simulation(const unsigned& _trials) : trials(_trials), likelihood(1.) {}



    // Accesses likelihood
    double& Simulation::get_likelihood() {
        return likelihood; // returns likelihood
    }


    // evolve function
    void Simulation::evolve(int init, int target, double dT, double eta, double lam, unsigned num_threads) {

        int success = 0; // counts successes

        std::vector<std::thread> threads; // container of threads

        int chunk = trials / num_threads; // a chunk is the number of trials over number of threads to perform
        int last = trials % num_threads; // last chunk is the remainder

        int low = 1; // the lower bound for evolve_all is 1 person
        int high = 0; // higher bound for evolve_all, will be changed in for loop
        for (size_t i = 0; i <= num_threads - 1; ++i) { // going from 0 to num_threads

            if (i == (num_threads - 1)) { // if last thread
                high = chunk + last; // high will be the chunk + remainder
            }
            else { // if not last thread
                high = chunk; // high will be just a regular chunk
            }

            threads.emplace_back(std::thread(evolve_all, low, high, &success, init, target, dT, eta, lam)); // thread added to vector of threads
        } // by the end of loop, the vector size will be the same as num_threads


        for (size_t i = 0; i < threads.size(); ++i) { // for all threads in the vector
            threads[i].join(); // joins the threads
        }

        likelihood *= static_cast<double>(success) / trials; // updates likelihood
    }


    // Sets parameters
    void set_parameters(std::string& file_name, double& eta, double& lam, int& num_trials, unsigned& max_threads) {

        // user inputs eta and lambda
        std::cout << "Enter values for eta [/yr] and lambda [/yr]: ";
        std::cin >> eta >> lam;

        // user inputs file name
        std::cout << "Enter data file name: ";
        std::cin >> file_name;

        // user inputs number of trials to do
        std::cout << "How many particles? ";
        std::cin >> num_trials;

        // user inputs maximum number of threads to try
        std::cout << "Enter maximum number of threads to try: ";
        std::cin >> max_threads;

    }



    // Reads the file
    std::vector<int> read_inputs(std::string& file_name) {
        std::ifstream in_file; // creates ifstream
        in_file.open(file_name); // opens file with the file_name

        if (in_file.fail()) { // if the file failed to open
            std::cout << "Can't open file" << '\n'; // error message
        }

        std::vector<int> data; // creates a vector that will store the data of the file

        while (true) { // "infinite" loop for reading in data from the file

            int i = 0; // variable that contain the data
            in_file >> i; // reads in int

            if (in_file) { // if still in_file
                data.push_back(i); // adds the int into data
            }

            else { // if end of file
                break; // breaks the loop
            }

        }

        in_file.close(); // closes the file

        return data; // returns the data
    }


    // Finds new population
    int find_new_pop(int init, double dT, double eta, double lam) {
        // returns random int from Poisson distribution with eta rate and dT time step
        int num_in = poiss_in(eta, dT);

        int num_out = 0; // counts population leaving
        for (size_t i = 1; i <= init; ++i) { // starting from individual 1 to size of initial pop.

            // returns random length of time from exponential distribution
            double val = exp_out(lam);

            if (val < dT) { // if the random length of time is greater than time step
                ++num_out; // increment population leaving
            }

        }

        return init + num_in - num_out; // returns new population
    }



    // Increment (thread-safe)
    void increment(int* success, int increase) {
        MUTEX.lock(); // code starting here locked, increment...
        (*success) += increase; // increments number of successful trials
        MUTEX.unlock(); // unlock so other threads can print
    }



    // evolve_all function
    void evolve_all(int low, int up, int* succ, int init, int target, double dT, double eta, double lam) {

        int good_trials = 0; // counts number of successful trials

        for (int i = low; i <= up; ++i) { // from lower bound to upper bound

            if (find_new_pop(init, dT, eta, lam) == target) { // if new population is positive
                ++good_trials; // increment number of successful trials
            }

        }

        increment(succ, good_trials); // increments total number of success by number of good_trials
    }


    // Generates an int from poissin distribution
    int poiss_in(double eta, double dT) {
        thread_local std::default_random_engine eng{ std::random_device()() };
        std::poisson_distribution<int> p{ eta * dT };
        return p(eng);
    }


    // generates length of time sampled from exponential distribution
    double exp_out(double lam) {
        thread_local std::default_random_engine eng{ std::random_device()() };
        std::exponential_distribution<> e{ lam };
        return e(eng);
    }

}

