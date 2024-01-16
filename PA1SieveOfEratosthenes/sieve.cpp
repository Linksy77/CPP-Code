/*******************************************************************************
 * Name        : sieve.cpp
 * Description : PA1 - Sieve of Eratosthenes: Prints all prime numbers up to and including the user input.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.

    cout << endl << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    // Finding the width of the largest prime number
    // & the number of primes you can fit in a row
    const int max_prime_width = num_digits(max_prime_),
              primes_per_row = 80 / (max_prime_width + 1);

    int numInRow = 1;
    // int currNum = 2;
    // int remainingNumsToPrint = num_primes_;

    // If all nums to be printed fit on one row
    if(num_primes_ <= primes_per_row) {
        for(int currNum = 2; currNum <= limit_; currNum++) {
            if(is_prime_[currNum]) {
                if(currNum != max_prime_) {
                    // If num is not the last prime in the row
                    cout << currNum << " ";
                } else {
                    // If num is the last prime in the row
                    cout << currNum;
                }
            }
        }
    } else {
     // If we need more than row to print all nums
        for(int currNum = 2; currNum <= limit_; currNum++) {
            if(is_prime_[currNum]) {
                // If the current number is the last number in the row
                if(numInRow == primes_per_row) {
                    cout << setw(max_prime_width) << currNum << endl;
                    numInRow = 1;
                } else if(currNum == max_prime_) {
                // If not the last num in a row, but last overall num
                    cout << setw(max_prime_width) << currNum;
                } else {
                // If not last num in row or overall
                    cout << setw(max_prime_width) << currNum << " ";
                    numInRow++;
                }
            }
        }
    }
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.

    // Initializing is_prime_ with true and false values
    is_prime_[0] = false;
    is_prime_[1] = false;
    for(int i = 2; i <= limit_; i++) {
        is_prime_[i] = true;
    }


    // Sieve of Eratosthenes algorithm
    for(int i = 2; i <= sqrt(limit_); i++) {
        if(is_prime_[i] == true) {
            for(int j = i * i; j <= limit_; j += i) {
                is_prime_[j] = false;
            }
        }
    }


    // Counting the number of primes & finding the maximum prime number
    num_primes_ = 0;
    max_prime_ = 2;

    for(int i = 2; i <= limit_; i++) {
        if(is_prime_[i] == true) {
            num_primes_++;
            if(max_prime_ < i) {
                max_prime_ = i;
            }
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    
    int count = 0;

    while(num > 0) {
        count += 1;
        num /= 10;
    }

    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.

    PrimesSieve pSieve(limit);

    pSieve.display_primes();
    
    return 0;
}
