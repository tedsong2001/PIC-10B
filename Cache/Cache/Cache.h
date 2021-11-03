#ifndef _CACHE_
#define _CACHE_
#include <functional>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <utility>

namespace pic10b {
    
    /**
     @class cache class intends to store data and
     memorizes the highest and lowest values ever stored
     @tparam T type of data being stored
     @tparam N number of elements
     @tparam ord method of defining order
     */
    template<typename T, size_t N, typename ord = std::less<T>>
    class cache {

    private:
        T high; // highest val
        T low; // lowest val
        std::vector<T> v; // vector of vals
        ord less_than; // naming order
        size_t sz; // number of elements

        /**
         Prints the elements stored
         @param c the cache class, whose elements will be printed
         */
        friend void print(const cache& c) {
            for (size_t i = 0; i < c.sz; ++i) { // goes through elements
                std::cout << c.v[i] << ' '; // prints each element, followed by space
            }
        }

    public:

        /**
         @typedef const_iterator
         represents std::vector<T>
         */
        using const_iterator = typename std::vector<T>::const_iterator;

        /**
         Constructor
         @param _less_than the method of ordering, defaulted to std::less
         */
        cache(const ord& _less_than = ord()) : high(), low(), v{}, less_than(_less_than), sz(0) {}

        /**
         Insert an lvalue
         @param val the value to be inserted
         */
        void insert(T& val) {
            if (N <= 0) {
                throw std::logic_error("Container size cannot be lower than 1");
            }

            else if (sz < N) { // if there is still space
                if (sz == 0) { // if there are no elements
                    v.insert(v.begin(), val); // add val (newest values at front, oldest at back)
                    high = low = val; // set val to high and low
                    ++sz; // update sz
                }

                else { // if there are elements (but there is still space)
                    v.insert(v.begin(), val); // add val
                    if (less_than(val, low)) { // if val is lower than the current low
                        low = val; // update low
                    }

                    if (!less_than(val, high)) { // if val is greater than or equal to current high
                        high = val; // update high
                    }

                    ++sz; // update sz
                }
            }

            else { // if sz is equal to or greater than N
                v.insert(v.begin(), val); // add val

                v.pop_back(); // remove oldest value

                // check high and low
                for (size_t i = 0; i < v.size(); ++i) { // going through elements
                    if (less_than(v[i], low)) { // if the element is lower than the current low
                        low = v[i]; // updates low
                    }

                    if (!less_than(v[i], high)) { // if val is greater than or equal to current high
                        high = v[i]; // updates high
                    }
                }

            }
        }

        /**
         Insert an rvalue
         @param val the value to be inserted
         */
        void insert(T&& val) {
            if (N <= 0) { // if storage size is less than 1
                throw std::logic_error("Container size cannot be lower than 1"); // throw error
            }

            else if (sz < N) { // if there is still space
                if (sz == 0) { // if there are no elements
                    v.insert(v.begin(), val); // add val (newest values at front, oldest at back)
                    high = low = val; // set val to high and low
                    ++sz; // update sz
                }

                else { // if there are elements (but there is still space)
                    v.insert(v.begin(), val); // add val
                    if (less_than(val, low)) { // if val is lower than the current low
                        low = val; // update low
                    }

                    if (!less_than(val, high)) { // if val is greater than or equal to current high
                        high = val; // update high
                    }

                    ++sz; // update sz
                }
            }

            else { // if sz is equal to or greater than N
                v.insert(v.begin(), val); // add val

                v.pop_back(); // remove oldest value

                // check high and low
                for (size_t i = 0; i < v.size(); ++i) { // going through elements
                    if (less_than(v[i], low)) { // if the element is lower than the current low
                        low = v[i]; // updates low
                    }

                    if (!less_than(v[i], high)) { // if val is greater than or equal to current high
                        high = v[i]; // updates high
                    }
                }

            }
        }

        /**
         Emplace, adds multiple arguments
         @tparam Types the data type of the argument
         @param args arguments
         */
        template<typename... Types>
        void emplace(Types&&... args) {

            if (N <= 0) { // if storage size is less than 1
                throw std::logic_error("Container size cannot be lower than 1"); // throw error
            }

            else if (sz < N) { // if there is still space
                if (sz == 0) { // if there are no elements
                    v.insert(begin(), T(std::forward<Types>(args)...)); // add val (newest values at front, oldest at back)
                    high = low = v[0]; // set val to high and low
                    ++sz; // update sz
                }

                else { // if there are elements (but there is still space)
                    v.insert(begin(), T(std::forward<Types>(args)...)); // add val
                    if (less_than(v[0], low)) { // if val is lower than the current low
                        low = v[0]; // update low
                    }

                    if (!less_than(v[0], high)) { // if val is greater than or equal to current high
                        high = v[0]; // update high
                    }

                    ++sz; // update sz
                }
            }

            else { // if sz is equal to or greater than N
                v.insert(begin(), T(std::forward<Types>(args)...)); // add val

                v.pop_back(); // remove oldest value

                // check high and low
                for (size_t i = 0; i < v.size(); ++i) { // going through elements
                    if (less_than(v[i], low)) { // if the element is lower than the current low
                        low = v[i]; // updates low
                    }

                    if (!less_than(v[i], high)) { // if val is greater than or equal to current high
                        high = v[i]; // updates high
                    }
                }

            }
        }

        /**
         Removes the oldest element
         */
        void pop() {
            if (sz == 0) { // if no elements
                throw std::logic_error("pop nothing"); // throw error
            }

            v.pop_back(); // last element removed

            --sz; // sz update
        }

        /**
         Sets const_iterator at most recent element
         @return const_iterator at most recent element
         */
        const_iterator begin() {
            return v.begin(); // returns beginning of vector
        }

        /**
         Sets const_iterator at most distant element
         @return const_iterator at most distant element
         */
        const_iterator end() {
            return v.end(); // returns end of vector
        }

        /**
         Accesses size
         @return number of elements
         */
        size_t& size() {
            return sz; // returns sz
        }

        /**
         Accesses low
         @return lowest element
         */
        T& get_low() {
            return low; // return low
        }

        /**
         Access high
         @return highest element
         */
        T& get_high() {
            return high; // return high
        }
    };

}

#endif
