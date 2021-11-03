#include "MagicSquare.h"

int main() {

	std::cout << "Enter a square size: ";
	size_t size = 0;
	std::cin >> size; // user inputs size

	while (size <= 0) { // if invalid input
		std::cout << "Invalid input. Enter a different size: "; // error message
		std::cin >> size; // user inputs a different size
	}
	
	std::cin.ignore(); // ensures good input when user formats square
	MagicSquare ms(size); // creates an instance of MagicSquare

	std::cout << "Enter a square format:" << '\n';
	std::cin >> ms; // user inputs properties for MagicSquare

	ms.solveSquare(0); // solves the MagicSquare

	// End message
	std::cout << "Solving complete!" << '\n';
	std::cout << "There were " << ms.get_solution() << " solutions!" << '\n'; // prints how many solutions found


	return 0;
}