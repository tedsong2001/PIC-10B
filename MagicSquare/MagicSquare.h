#ifndef _MAGIC_SQUARE_
#define _MAGIC_SQUARE_

#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_set>
#include <string>

class MagicSquare {
private:
	std::vector<std::vector<int>> square; // the square
	std::unordered_set<int> used_up; // list of integers already in the square
	size_t solution; // solution counter

public:
	/**
	Constructor that accepts size
	@param size the size of the square
	*/
	MagicSquare(const size_t& size);
	

	/**
	Checks if a given position in the magic square is empty
	@param row the row of the magic square
	@param column the column of the magic square
	@return true if empty, false if not
	*/
	bool empty(const size_t& row, const size_t& column);
	

	/*
	Checks if a given number is already used in the magic square
	@param num the given number to be checked
	@return true if the number is taken, false if the number is not taken
	*/
	bool taken(const int& num);



	/**
	Checks if the square could potentially be valid by making sure row doesn't exceed target sum
	@param row to be checked
	@return true if valid, false if not
	*/
	bool checkRow(const size_t& row) const;
	

	/**
	Checks if the whole square is valid
	@return true if square is valid, false if not
	*/
	bool checkValid() const;
	
	/**
	Accesses the square
	@return reference to the square
	*/
	std::vector<std::vector<int>>& get_square();
	

	/**
	Solves the Magic Square
	@param index an index tracking the number of slots already considered
	*/
	void solveSquare(size_t num);

	/**
	Accesses the solution counter
	@return the number of solutions
	*/
	const size_t& get_solution() const;
};


/**
Operator >> to read from a stream into a vector
@param in the input stream
@param v the vector
@return the input stream
*/
std::istream& operator>>(std::istream& in, std::vector<std::vector<int>>& v);


/**
Operator >> to read from a stream into a MagicSquare class
@param in the input stream
@param ms the MagicSquare class
@return the input stream
*/
std::istream& operator>>(std::istream& in, MagicSquare& ms);


/**
Operator << to write a vector into output stream
@param out the output stream
@param v the vector
@param the output stream
*/
std::ostream& operator<<(std::ostream& out, std::vector<std::vector<int>>& v);


/**
Operator << to write a MagicSquare class into output stream
@param out the output stream
@param ms the MagicSquare class
@return the output stream
*/
std::ostream& operator<<(std::ostream& out, MagicSquare& ms);


#endif