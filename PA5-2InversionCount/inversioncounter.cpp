/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Description : Counts the number of inversions in an array.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time using two nested loops.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    // Initializing variable to keep count of the number of inversions
    long numOfInv = 0;

    // Using nested loop to find number of inversions
    for(int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            // Checking if array[i] and array[j] are in order; if not, increment numOfInv
            if(array[i] > array[j]) {
                numOfInv++;
            }
        }
    }

    return numOfInv;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!

    // Initializing empty array (scratch) of same length as array
    int* scratch = new int[length];
    // Finding numOfInv using mergesort function
    long numOfInv = mergesort(array, scratch, 0, length - 1);
    // Deallocating memory used by array scratch
    delete[] scratch;
    return numOfInv;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long numOfInv = 0;
    int mid;

    if(low < high) {
        // Finding middle of array; initializing necessary variables for mergesort
        mid = low + (high - low)/2;
        int L = low;
        int H = mid + 1;

        // Recursive calls for both halves of array
        long numOfInvL = mergesort(array, scratch, low, mid);
        long numOfInvR = mergesort(array, scratch, mid + 1, high);

        // Adding numOfInv from recursive calls
        numOfInv += numOfInvL + numOfInvR;

        // Sorting array and counting/incrementing numOfInv as is necessary
        for(int k = low; k <= high; k++) {
            if(L <= mid && (H > high || array[L] <= array[H])) {
                scratch[k] = array[L];
                L = L + 1;
            } else {
                scratch[k] = array[H];
                H = H + 1;
                // Incrementing numOfInv by number of inversions solved via the sorting
                numOfInv += mid - L + 1;
            }
        }

        // Setting values in array to sorted values
        for(int k = low; k <= high; k++) {
            array[k] = scratch[k];
        }
    }
    return numOfInv;
}



int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

    // Checking if proper amount of arguments/user input; throwing error if not
    if(argc > 2) {
        cerr << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }

    // Setting option based on argument/user input
    string option = (argc == 2) ? argv[1] : "";

    // Checking if option is valid; throwing error if not
    if(!(option == "slow" || option == "")) {
        cerr << "Error: Unrecognized option '" << option << "'." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    long numOfInv;
    int length = values.size();

    // Checking if no integers were input; throwing error if so
    if(length == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    // Calling proper method based on argument/user input (either "slow" or "" (fast))
    if(option == "slow") {
        numOfInv = count_inversions_slow(&values[0], length);
        cout << "Number of inversions (slow): " << numOfInv << endl;
    } else {
        numOfInv = count_inversions_fast(&values[0], length);
        cout << "Number of inversions (fast): " << numOfInv << endl;
    }

    return 0;
}
