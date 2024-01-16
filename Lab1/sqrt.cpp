/*******************************************************************************
 * Filename: sqrt.cpp
 * Description: Lab 1: Computes the square root of num to the precision defined by epsilon (if provided).
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
using namespace std;

double sqrt(double num, double epsilon) {
    if(num < 0) {
        return numeric_limits<double>::quiet_NaN();
    }
    
    if(num == 0 || num == 1) {
        return num;
    }

    double last_guess = num;
    double next_guess = 0;

    while(!(abs(last_guess - next_guess) <= epsilon)) {
        if(next_guess != 0){
            last_guess = next_guess;
        }
        next_guess = (last_guess + num/last_guess) / 2;
    }

    return next_guess;

}

int main(int argc, char* argv[]) {
    double n, eps;
    istringstream iss;

    if(argc != 3 && argc != 2) {
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }

    iss.str(argv[1]);
    if(!(iss >> n)) {
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }

    iss.clear();

    if(argc == 2) {
        eps = 1e-7;
    } else {
        iss.str(argv[2]);
        if((!(iss >> eps)) || eps <= 0) {
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
    }

    cout << fixed << setprecision(8) << sqrt(n, eps) << endl;

    return 0;

}