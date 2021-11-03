#ifndef _FINAL_DO_
#define _FINAL_DO_
#include <vector>
#include <string>

/**
 Base Case: implements function with 1 argument
 @tparam Funct function typename
 @tparam Type the type of argument
 @param func the function
 @param param argument
*/
template<typename Funct, typename Type>
 void do_for_one(Funct& func, Type& param) {
    func(param); // implements function with one argument
}

/**
 Implements function
 @tparam Function function typename
 @tparam Tfirst type of the first argument
 @tparam Trest type of the rest of the arguments
 @param func the function
 @param param the first argument
 @param params the rest of the arguments
 */
template<typename Function, typename Tfirst, typename...Trest>
 void do_for_one(Function& func, Tfirst& param, Trest&...params) {
    func(param); // implements function with first argument
    do_for_one(func, params...); // recursive call for the rest of the arguments
    // when there is only argument left, the above base case is called
}

/**
 Implements the function by calling the above functions
 @tparam F function typename
 @tparam T type fof the arguments
 @param func the function
 @param args the arguments
 */
template<typename F, typename...T>
 void do_for_each(F& func, T&...args) {
    do_for_one(func, args...); // implements the above function
}


#endif
