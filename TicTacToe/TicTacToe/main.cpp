#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Player {
public:
    // constructor
    /**
     Constructor makes a player, given a name and token, with score of 0
     @param NAME player's name
     @param TOKEN player's token ('x' or 'o')
     */
    Player(const string NAME, const char TOKEN) : PLAYER_NAME(NAME), PLAYER_TOKEN(TOKEN), score(0) {}

    // mutator
    /**
     Increases a player's score if they wins
     */
    void win() { ++score; }
    
    // accessor
    /**
     Accessing a player's name
     @return player's name
     */
    string get_name() const { return PLAYER_NAME; }
    
    /**
     Accessing a player's token ('o' or 'x')
     @return player's token
     */
    char get_token() const { return PLAYER_TOKEN; }
    
    /**
     Accessing a player's score
     @return player's score
     */
    int get_score() const { return score; }
    
private:
    // member variables
    const string PLAYER_NAME;
    const char PLAYER_TOKEN;
    int score;
};

/**
 Print function for the Tic-Tac-Toe board
 @param current_board vector that contains the Tic-Tac-Toe board
 */
void print(const vector<string>& current_board);

/**
 Updates the Tic-Tac-Toe board for each player's turn
 @param current_board vector that contains the Tic-Tac-Toe
 @param token player's token (x or o)
 @param desired_row the row in which the player wants to place token
 @param desired_column the column in which the player wants to place token
 */
void update(vector<string>& current_board, const int& token, int& desired_row, int& desired_column);

/**
 Executes a player's turn: input row and column and then updating the Tic-Tac-Toe board
 @param _player the current player
 @param _board vector that contains Tic-Tac-Toe board
 */
void player_turn(const Player& _player, vector<string>& _board);

/**
 Checks if a player has won (getting 3 in a row on Tic-Tac-Toe board)
 @param current_board vector that contains Tic-Tac-Toe board
 @return true if user won, false if user has not won yet
 */
bool is_Win(const vector<string>& current_board);

int main() {
    cout << "This is a Tic Tac Toe game!" << '\n';
    cout << "How many rounds would you like to play? ";
    int desired_rounds = 0; // desired number of rounds
    cin >> desired_rounds; // inputs desired number of rounds
    
    cout << "Please enter the name of player 1: ";
    string name1 = ""; // name of player 1
    cin.ignore(); // to ensure player's name is properly inputted
    getline(cin, name1); // inputs name of player 1
    Player player1(name1, 'x'); // creates a Player, player1 is assigned the 'x' token
    
    cout << "Thanks. Please enter the name of player 2: ";
    string name2 = ""; // name of player 2
    getline(cin, name2); // inputs name of player 2
    Player player2(name2, 'o'); // creates another Player, player2 is assigned the 'o' token
    
    cout << "Let the game begin!" << '\n';
    
    for (size_t current_round = 0; current_round < desired_rounds; ++current_round) { // playing number of desired_rounds
        vector<string> board {" 1 2 3", "1 | | ", " -----", "2 | | ", " -----", "3 | | "}; // fresh Tic-Tac-Toe board
        print(board); // prints the Tic-Tac-Toe board
        
        size_t turn_count = 0; // counting number of player turns
        size_t total_turns = 9; // maximum number of turns in a Tic-Tac-Toe game is 9
        
        /* The following if statement is for alternating purposes.
         Player1 will start every even round. Player2 will start every odd round.
         Player1 plays every even turn. Player2 plays every odd turn.
         So, turn_count and total_turns will be increased by 1 during odd rounds to ensure alternating. */
        if (current_round % 2 == 1) {
            ++turn_count;
            ++total_turns;
        }
        
        while (turn_count < total_turns) { // while turn_count is less than total_turns
            if (turn_count % 2 == 0) { // Player1 plays every even turn
                player_turn(player1, board); // Player1 places token on desired position on Tic-Tac-Toe board
            }
            else { // Player2 plays every odd turn
                player_turn(player2, board); // Player2 places token on desired position on Tic-Tac-Toe board
            }
            print(board); // printing the Tic-Toe-Toe board after every turn
            if (is_Win(board)) { // If there is a win (3-in-a-row)
                if (turn_count % 2 == 0) { // If there is a win on an even turn, Player1 wins
                    player1.win();
                    cout << player1.get_name() << " won the round!" << '\n';
                }
                else { // If there is a win on an odd turn, Player2 wins
                    player2.win();
                    cout << player2.get_name() << " won the round!" << '\n';
                }
                break; // While loop breaks, thus ending the round
            }
            else if (!is_Win(board) && (turn_count == 8)) { // If no one wins by the last turn, the game is a draw
                cout << "It's a draw!" << '\n';
                break; // While loop breaks, thus ending the round
            }
            else { // If no one has won yet and if there are more turns to be played
            ++turn_count; // adds to turn_count after each player's turn
            }
        }
        
        cout << "Presently, " << player1.get_name() << " has " << player1.get_score() << " points and " << player2.get_name() << " has " << player2.get_score() << " points." << '\n'; // announcing score board
    }
    
    if (player1.get_score() > player2.get_score()) { // if player1 has higher score than player2, then player 1 wins
        cout << player1.get_name() << " won the game!" << '\n';
    }
    else if (player2.get_score() > player1.get_score()) {// if player2 has higher score than player2, then player 1 wins
        cout << player2.get_name() << " won the game!" << '\n';
    }
    else { // if player scores are equal, then tie
        cout << "It's a tie!" << '\n';
    }
    
    return 0;
}

// Function Definitions

void print(const vector<string>& current_board) {
    for (size_t i = 0; i < current_board.size(); ++i) { // for each element in the vector
        cout << current_board[i] << '\n'; // prints each element, followed by a \n
    }
}

void update(vector<string>& current_board, const int& token, int& desired_row, int& desired_column) {
    /* Changes desired_row into the actual row on current_board vector
     Ex. User wants to place token on row 3. On the vector, it would be element 5. */
    desired_row = (2 * desired_row) - 1;
    
    /* Changes desired_column into the actual "column" on current_board vector
     Ex. User wants to place token on column 3. On the vector, it would be character 5 of an element. */
    desired_column = (2 * desired_column) - 1;
    
    current_board[desired_row][desired_column] = token; // Places user's token on desired position
}

void player_turn(const Player& _player, vector<string>& _board) {
    cout << "It is " << _player.get_name() << "\'s turn." << '\n';
    cout << "Where would you like to play? Enter your row position and column position: row col: ";
    int _row = 0;
    int _column = 0;
    cin >> _row >> _column; // Player inputs where he/she wants to place token on Tic-Tac-Toe board
    update(_board, _player.get_token(), _row, _column); // updates the Tic-Tac-Toe board
}

bool is_Win(const vector<string>& current_board) {
    const string ROW1 = current_board[1]; // ROW1 on Tic-Tac-Toe board corresponds to element 1 on the current_board vector
    const string ROW2 = current_board[3]; // ROW2 on Tic-Tac-Toe board corresponds to element 3 on the current_board vector
    const string ROW3 = current_board[5]; // ROW3 on Tic-Tac-Toe board corresponds to element 5 on the current_board vector
    
    const int COLUMN1 = 1; // COLUMN1 on Tic-Tac-Toe board corresponds to character 1 of a string on the current_board vector
    const int COLUMN2 = 3; // COLUMN2 on Tic-Tac-Toe board corresponds to character 3 of a string on the current_board vector
    const int COLUMN3 = 5; // COLUMN3 on Tic-Tac-Toe board corresponds to character 5 of a string on the current_board vector
    
    // Horizontal check
    if ((ROW1[COLUMN1] == ROW1[COLUMN2]) && (ROW1[COLUMN2] == ROW1[COLUMN3]) && (ROW1[COLUMN1] != ' ')) { return true; } // if 3-in-a-row in top row
    else if ((ROW2[COLUMN1] == ROW2[COLUMN2]) && (ROW2[COLUMN2] == ROW2[COLUMN3]) && (ROW2[COLUMN1] != ' ')) { return true; } // if 3-in-a-row in middle row
    else if ((ROW3[COLUMN1] == ROW3[COLUMN2]) && (ROW3[COLUMN2] == ROW3[COLUMN3]) && (ROW3[COLUMN1] != ' ')) { return true; } // if 3-in-a-row in bottom row
    
    // Vertical check
    else if ((ROW1[COLUMN1] == ROW2[COLUMN1]) && (ROW2[COLUMN1] == ROW3[COLUMN1]) && (ROW1[COLUMN1] != ' ')) { return true; } // if 3-in-a-row in left column
    else if ((ROW1[COLUMN2] == ROW2[COLUMN2]) && (ROW2[COLUMN2] == ROW3[COLUMN2]) && (ROW1[COLUMN2] != ' ')) { return true; } // if 3-in-a-row in middle column
    else if ((ROW1[COLUMN3] == ROW2[COLUMN3]) && (ROW2[COLUMN3] == ROW3[COLUMN3]) && (ROW1[COLUMN3] != ' ')) { return true; } // if 3-in-a-row in right column
    
    // Diagonal check
    else if ((ROW1[COLUMN1] == ROW2[COLUMN2]) && (ROW2[COLUMN2] == ROW3[COLUMN3]) && (ROW1[COLUMN1] != ' ')) { return true; } // if 3-in-a-row from top left to bottom right
    else if ((ROW1[COLUMN3] == ROW2[COLUMN2]) && (ROW2[COLUMN2] == ROW3[COLUMN1]) && (ROW1[COLUMN3] != ' ')) { return true; } // if 3-in-a-row from top right to bottom left
    
    else { return false; } // returns false if a player has not won yet
}
