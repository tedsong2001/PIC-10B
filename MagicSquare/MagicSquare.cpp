#include "MagicSquare.h"

// constructor
MagicSquare::MagicSquare(const size_t& size) : solution(0) { // solution initialized to 0
	for (size_t i = 0; i < size; ++i) { // i represents row
		std::vector<int> temp = {}; // a vector of ints
		for (size_t j = 0; j < size; ++j) { // j represents column
			temp.push_back(0); // vector will have size number of ints, all set to 0 to signify empty
		}
		square.push_back(temp); // adds the vector to square, thus creating a row
	}
}

// checks if position is empty
bool MagicSquare::empty(const size_t& row, const size_t& column) {
	if (square[row][column] == 0) { // if the position is a 0 (empty)
		return true; // returns true
	}
	else { // if the position is filled
		return false; // returns false
	}
}

// checks if a specific number is taken
bool MagicSquare::taken(const int& num) {
	for (size_t i = 0; i < square.size(); ++i) { // i represents row
		for (size_t j = 0; j < square.size(); ++j) { // j represents column
			if (square[i][j] == num) { // if the num is taken
				return true; // returns true
			}
		}
	}
	return false; // if the num is not taken, returns false
}

// checks if row and columns are valid
bool MagicSquare::checkRow(const size_t& num) const {
	const int TARGET = square.size() * ((static_cast<double>((square.size() * square.size()) + 1)) / 2);
		// target sum
	int sum = 0; // sum to check if row/column hits target sum

	size_t row_converted = (num / square.size()) - 1;
		// if the "row" is bigger than square.size(), the number is converted to the actual row

	// checks the row
	for (size_t i = 0; i < square.size(); ++i) { // goes through each int
		sum += square[row_converted][i]; // adds the ints of one row
	}
	if (sum != TARGET) { // if sum is not target sum
		return false; // returns false
	}

	// checks the columns
	for (size_t i = 0; i < square.size(); ++i) { // i represents the column number
		sum = 0;
		for (size_t j = 0; j < square.size(); ++j) { // j represents the row number
			sum += square[j][i]; // adds the ints of a columnn
		}
		if (sum > TARGET) { // if sum exceeds target sum
			return false; // returns false
		}
	}

	// if the square has managed to pass all the qualifications
	return true; // returns true
}

// checks if the whole square is valid
bool MagicSquare::checkValid() const {

	const int TARGET = square.size() * ((static_cast<double>((square.size() * square.size()) + 1)) / 2);
	// target sum
	int sum = 0; // variable that will contain sum

	// rows
	for (size_t i = 0; i < square.size(); ++i) { // i represents row number
		sum = 0; // resets sum to 0 after every row
		for (size_t j = 0; j < square.size(); ++j) { // j represents int position (column)
			sum += square[i][j]; // adds every int of a row into sum
		}
		if (sum != TARGET) { // if sum does not match target sum
			return false; // return false
		}
	}

	// columns
	sum = 0; // reset sum to 0
	for (size_t i = 0; i < square.size(); ++i) { // i represents int position (column)
		sum = 0; // resets sum to 0 after every column check
		for (size_t j = 0; j < square.size(); ++j) { // j represents row
			sum += square[j][i]; // adds every int of a column to sum
		}
		if (sum != TARGET) { // if sum does not match target sum
			return false; // return false
		}
	}

	// top left to bottom right diagonal
	sum = 0; // resets sum
	for (size_t i = 0; i < square.size(); ++i) {
		sum += square[i][i]; // adds each element on the diagonal
	}
	if (sum != TARGET) { // if the sum is not target sum
		return false; // returns false
	}

	// top right to bottom left-diagonal
	sum = 0; // resets sum
	for (size_t i = 0; i < square.size(); ++i) {
		sum += square[i][square.size() - 1 - i]; // adds each element on the diagonal
	}
	if (sum != TARGET) { // if the sum is not target sum
		return false; // returns false
	}
	else { // if sum is target sum and square has managed to pass all the previous requirements
		return true; // returns true
	}
}

// get function
std::vector<std::vector<int>>& MagicSquare::get_square() {
	return square; // returns the MagicSquare
}

// solves the square
void MagicSquare::solveSquare(size_t num) {
	size_t total_slot = square.size() * square.size(); // total number of slots to fill

	if (num == 0) { // at the start
		for (size_t n = 0; n <= total_slot; ++n) { // goes through all the possible numbers
			if (taken(n)) { // if a number is taken
				used_up.insert(n); // adds the number to used_up
			}
		}
		solveSquare(num + 1); // "incremented" num into function call, so that recursion can begin
	}

	else if (num == total_slot + 1) { // if num finished going through ALL the slots
		if (checkValid()) { // checks if the square is valid
			std::cout << square << '\n'; // if so, prints the magic square
			++solution; // adds to the solution counter
		}
	}

	else if (num < total_slot + 1) { // if still going through the slots
		if ((num != 1) && (num % square.size() == 1)) { // if num is now at the beginning of a new row
			if (!checkRow(num)) { // checks if the row is not valid
				solveSquare(total_slot + 1); // next permutation
				return;
			}
		}

		const size_t ROW = (num - 1) / square.size(); // the row of the num-th slot
		const size_t COLUMN = (num - 1) % square.size(); // the column of the num-th slot

		if (empty(ROW, COLUMN)) { // if the position is empty
			for (size_t n = 0; n <= total_slot; ++n) { // goes through all possible numbers
				if (!taken(n)) { // if a number is not taken
					square[ROW][COLUMN] = n; // the number takes that position
					used_up.insert(n); // number is added to used_up

					solveSquare(num + 1); // recursive call

					square[ROW][COLUMN] = 0; // reset the slot
					used_up.erase(n); // removes the used number from used_up
				}
			}
		}
		else { // if the position is not empty
			solveSquare(num + 1); // skips over the current slot and goes to check the next
		}
	}
}

// get function for solution counter
const size_t& MagicSquare::get_solution() const {
	return solution; // returns the number of solutions
}

// operator >> for vector
std::istream& operator>>(std::istream& in, std::vector<std::vector<int>>& v) {
	for (size_t i = 0; i < v.size(); ++i) {
		std::string format = "";
		std::getline(in, format); // user formats each line

		int count = 0; // counts how many ints in a vector of v (this resets to 0 after each input)
		std::string num = ""; // temporary string will contain the numbers in the format string
		for (size_t j = 0; j < format.length(); ++j) { // goes through the format
			if ((format[j] == '*') || (format[j] == ' ')) {
				if (format[j] == '*') { // if character is *
					++count; // increments count because * signifies a random int
					num = ""; // resets num
				}
				else { // if a character is a space
					if (num != "") { // if num contains a string
						std::stringstream s(num); // stringstream created
						int x = 0; // int variable created
						s >> x; // x reads in the stringstream
						v[i][count] = x; // value of x assigned to the position in v, respective to user's input
						++count; // increments count
						num = ""; // resets num
					}
				}
			}
			else { // if a character is a number
				num += format[j]; // adds the number to the temporary num
			}

			if ((j == format.length() - 1) && (format[j] != '*')) { // if last character is reached and the character is not *
				std::stringstream s(num); // stringstream created
				int x = 0; // int variable created
				s >> x; // x reads in the stringstream
				v[i][count] = x; // value of x assigned to the position in v, respective to user's format
			}
		}
	}
	return in; // returns input stream
}

// Operator >> for MagicSquare
std::istream& operator>>(std::istream& in, MagicSquare& ms) {
	return in >> ms.get_square(); // returns input stream
}

// Operator << for vector
std::ostream& operator<<(std::ostream& out, std::vector<std::vector<int>>& v) {
	for (size_t i = 0; i < v.size(); ++i) { // goes through the rows
		for (size_t j = 0; j < v[i].size(); ++j) { // goes through the columns (the ints of the inside vector)
			out << v[i][j] << ' '; // outputs each int
		}
		out << '\n'; // every row is followed by \n
	}
	return out; // returns output stream
}

// Operator << for MagicSquare
std::ostream& operator<<(std::ostream& out, MagicSquare& ms) {
	return out << ms.get_square(); // returns output stream
}