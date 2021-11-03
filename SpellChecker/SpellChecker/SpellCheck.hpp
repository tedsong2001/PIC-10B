#ifndef _SPELL_CHECK_
#define _SPELL_CHECK_
#include <iostream>
#include <unordered_set>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

class SpellCheck {
public:
    /**
     Constructs a SpellCheck class, without storing anything initially
     */
    SpellCheck();
    
    /**
     Reads a dictionary file and puts each word into an unordered set called "dictionary"
     @param dictionary_filename the file name of the dictionary
     */
    void read_dictionary(const std::string& dictionary_filename);
    
    /**
     Checks if a word is correctly spelled by seeing if a word is present in the dictionary
     @param word a word
     @return false if a word is not present in the dictionary, true if a word is present in the dictionary
     */
    bool is_valid(const std::string& word) const;
    
    /**
     Reads through a txt file that needs to be spell checked and prints the checked file into console window
     @param user_filename the file name of the txt file subject to spell check
     */
    void process_file(const std::string& user_filename);

private:
    std::unordered_set<std::string> dictionary; // unordered set for dictionary
};

/**
 Checks if a character is white space (space, new line, tab)
 @param c a character
 @return true if a character is white space, false if a character is not white space
 */
bool is_white_space(const char& c);

/**
 Checks if a word has a punctuation at the end
 @param word a word
 @return true if there is a punctuation at the end, false if there is no punctuation at the end
 */
bool final_punctuation(const std::string& word);

/**
 Mutates a string by changing the first capital letter into lowercase and by erasing the punctuation at the end, if present
 @param input a string that contains a word
 */
void depunctuate(std::string& input);

#endif
