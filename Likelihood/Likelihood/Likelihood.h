#ifndef _LIKELIHOOD_
#define _LIKELIHOOD_

#include <string>
#include <vector>
#include <thread>
#include <random>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <mutex>

namespace pic10b {

    class Simulation {

    private:
        unsigned trials; // how many trials are to be run per time step
        double likelihood; // the value of the likelihood

    public:

        /**
         Constructor
         */
        Simulation(const unsigned& _trials);

        /**
         Accesses likelihood
         @return likelihood
         */
        double& get_likelihood();

        /**
         Scale the current value of likelihood by the probability of reaching
         target from init with the values dT, eta, and lam given
         @param init the number of employees present at the start of a year according to the data
         @param target the number of employees there should be the next year according to the data
         @param dT the time step in years
         @param eta a Poisson rate
         @param lam the rate for an Exponential distribution
         @param num_threads the number of threads to use
         */
        void evolve(int init, int target, double dT, double eta, double lam, unsigned num_threads);

    };

    /**
     Updates the file name of data, the values of probability distributions, number of trials to run,
     and max number of threads to use based on user input
     @param file_name file name of the data
     @param eta Poisson rate
     @param lam rate for exponential distribution
     @param num_trials number of trials to run
     @param max_threads maximum number of threads to use
     */
    void set_parameters(std::string& file_name, double& eta, double& lam, int& num_trials, unsigned& max_threads);

    /**
     Reads the file and stores annual employee count
     @param file_name name of the file with data
     @return vector storing the yearly counts
     */
    std::vector<int> read_inputs(std::string& file_name);

    /**
     Calculates employee count for next year
     @param init initial population
     @param dT time step
     @param eta Poisson rate
     @param lam rate for exponential distribution
     @return employee count for next year
     */
    int find_new_pop(int init, double dT, double eta, double lam);

    /**
     Increments number of successful trials
     @param success number of successful trials
     @param increase how much to increase number of success
     */
    void increment(int* success, int increase);

    /**
     Performs simulation to determine if the employee count, starting from init,
     matches target after one year using the eta, dT, and lam parameters
     @param low start # of simulations
     @param up end # of simulations
     @param init initial population
     @param target target population
     @param dT time step
     @param eta Poisson rate
     @param lam rate for exponential distribution
     */
    void evolve_all(int low, int up, int* succ, int init, int target, double dT, double eta, double lam);

    /**
     Generates an int using from Poissin distribution (provided by Prof. Lindstrom)
     @param eta Poissin rate
     @param dT time step in years
     @return int from Poissin distribution
     */
    int poiss_in(double eta, double dT);

    /**
     Generates a length of time from exponential distribution using rate lam (provided by Prof. Lindstrom)
     @param lam rate for exponential distribution
     @return length of time from exponential distribution
     */
    double exp_out(double lam);


}

#endif
