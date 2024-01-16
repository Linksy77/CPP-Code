/*******************************************************************************
 * Name        : unique.cpp
 * Description : Determining uniqueness of chars with int as bit vector.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    int ascii_val;

    for(int i = 0; i < (int) s.length(); i++) {     // Iterating over every character in the string
        ascii_val = s[i];
        if(ascii_val < 'a' || ascii_val > 'z') {    // If ASCII value of the char. is outside the range of values for lowercase letters
            return false;
        }
    }

    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only.  Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.

    unsigned int used_chars = 0;

    for(int i = 0; i < (int) s.length(); i++) {         // Iterating over every character in the string
        int num_of_shifts = ('z' - s[i]);
        unsigned int curr_char = 0x1 << num_of_shifts;  // Setting the letter's corresponding bit to 1 in unsigned int used for comparison

        if(curr_char & used_chars) {                    // Using BWAND to see if letter has been found before 
            return false;
        } else {                                        // If letter has not been found before
            used_chars = used_chars | curr_char;        // Changing corresponding bit (in unsigned int keeping track of which letters were found) to 1
        }
    }

    return true;

}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    if(argc != 2) {                                     // If user did not provide proper amount of arguments
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }

    string s = argv[1];

    if(!(is_all_lowercase(s))) {                        // If string does not contain all lowercase letters
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if(all_unique_letters(s)) {                         // If all letters in the string are unique
        cout << "All letters are unique." << endl;
    } else {                                            // If not all letters in the string are unique
        cout << "Duplicate letters found." << endl;
    }

    return 0;

}
