#include "SpellCheck.hpp"
using namespace std;

int main() {
    
    SpellCheck my_spellcheck; // creates _spellcheck with the SpellCheck class
    my_spellcheck.read_dictionary("dictionary.txt"); // dictionary.txt is the file name to create the dictionary
    
    cout << "Enter file to spell check: ";
    string txt_file = ""; // string for user's file name that needs to be spell checked
    cin >> txt_file; // user inputs the name of the file that needs to be spell checked

    my_spellcheck.process_file(txt_file); // processes the file and spell checks it

    return 0;
}
