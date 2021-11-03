#include "SpellCheck.hpp"

SpellCheck::SpellCheck() : dictionary() {}; // default constructor, doesn't store anything initially


void SpellCheck::read_dictionary(const std::string& dictionary_filename) {
    std::ifstream dictionary_file; // creates an input file for the dictionary
    dictionary_file.open(dictionary_filename); // opens the input file based on the file name of the dictionary txt file
    
    if ( dictionary_file.fail() ) { // Error message, in case there is a problem with opening the dictionary file
        std::cout << "Error opening dictionary file." << '\n';
    }
    
    while (true) { // while true
        std::string line = ""; // creates line for storing each word in a dictionary
        dictionary_file >> line; // inputs words from the dictionary file into line
        if (dictionary_file) { // if there is something to input
            dictionary.insert(line); // the word is inserted into the unordered set called dictionary
        }
        else { break; } // if there is nothing to input, the while loop breaks
    }
    dictionary_file.close(); // closes the dictionary file that was opened
}


bool SpellCheck::is_valid(const std::string& word) const {
    if ( dictionary.find(word) == dictionary.end() ) { return false; } // returns false if a word cannot be found in the unordered set called dictionary
    else { return true; } // returns true if a word is found
}


void SpellCheck::process_file(const std::string& user_filename) {
    
    std::ifstream user_file; // creates an input file for the user's file that needs to be spell checked
    user_file.open(user_filename); // opens the input file based on the name of the file, given by the user
    
    if ( user_file.fail() ) { // Error message, in case there is a problem with opening the user's file
        std::cout << "Error opening user's file." << '\n';
    }
    
    std::string output = ""; // a string representing the console display at the end of the function
    
    while (user_file) { // while there is something to input from user_file
        if ( is_white_space( user_file.peek() ) ) { // if peek function sees that the character is white space
            char ch = user_file.get(); // creates a character and the get function stores the white space into ch
            output += ch; // the white space is added onto the string called output
        }
        else { // if the character is not white space
            std::string word = ""; // creates a string
            user_file >> word; // inputs a word from user_file into the string word
            
            if ( is_valid(word) ) { output += word; } // if the word is valid, meaning that it is found in the dictionary
            else { // if the word is not valid, meaning not found in the dictionary
                std::string temp = word; // stores the content of word into a temporary string to preserve the original text
                depunctuate(temp); // depunctuates temp (making the first capital letter lowercase and getting rid of the final punctuation
                
                if ( is_valid(temp) ) { output += word; } // if the depunctuated word is valid, then the original text is added onto the string called output
                else { // if the depunctuated word is not valid, it means that the word is incorrectly spelled
                    if ( final_punctuation(word) ) { // if there is a final punctuation
                        char punc = word[word.length() - 1]; // the final character (the final punctuation) is stored into punc
                        word = word.substr(0, word.length() - 1); // gets rid of the final punctuation from word
                        output += ('*' + word + '*' + punc); // then adds the word surrounded by * and followed by the punc, into output
                        // Ex. "roda." (supposed to be road) --> "*roda*."
                    }
                    else if (word != ""){ // if there is no final punctuation or is not ""
                        output += ('*' + word + '*'); // then adds the word surrounded by * into output
                        // Ex. "roda" (supposed to be road) --> "*roda*"
                    }
                }
            }
        }
    }
    
    user_file.close(); // closes the user_file that was opened
    std::cout << output << '\n'; // prints the output followed by an endline
}


bool is_white_space(const char& c) {
    return ( (c == ' ') || (c == '\n') || (c == '\t') ); // if the character is a white space, returns true
    // otherwise, returns false
}


bool final_punctuation(const std::string& word) {
    if ( word == "" ) { return false; } // returns false if empty string
    std::vector<char> punc_list = { '.' , ',' , '!' , '?' , ';' , ':' }; // vector of possible punctuations
    
    for (size_t i = 0; i < punc_list.size(); ++i) { // going through each element (punctuation) of the punc_list
        if (word[word.length() - 1] == punc_list[i]) { return true; } // if the character matches one of the punctuations, returns true
    }
    
    return false; // if character does not match punctuation, returns false
}


void depunctuate(std::string& input) {
    if ( (input[0] >= 'A') && (input[0] <= 'Z') ) { // if the first character of the string is a capital letter
        input[0] += ('a' - 'A'); // the character is converted to lowercase
    }
    if ( final_punctuation(input) ) { // if the string has a final punctuation
        input.erase(input.length() - 1); // erases the last character, which is the final punctuation
    }
}
