/*******************************************************************************
 * Name        : stairclimber.cpp
 * Description : Lists the number of ways to climb n stairs.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector<vector<int>> total_ways;
vector<int> steps;

vector< vector<int> > get_ways(int num_stairs) {
    // Returns a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    
    if(num_stairs == 0) {
        // If there are no stairs:
        total_ways.push_back(steps);
    } else if(num_stairs == 1) {
        // If there is only 1 stair:
        // Recursive call for only possible way to climb
        steps.push_back(1);
        get_ways(num_stairs - 1);
        steps.pop_back();
    } else if(num_stairs == 2) {
        // If there are only 2 stairs:
        // Recursive calls for all two possible ways to climb
        steps.push_back(1);
        get_ways(num_stairs - 1);
        steps.pop_back();
        steps.push_back(2);
        get_ways(num_stairs - 2);
        steps.pop_back();
    } else {
        // If the number of stairs is 3 or greater:
        // Recursive calls for all three possible ways to climb
        steps.push_back(1);
        get_ways(num_stairs - 1);
        steps.pop_back();
        steps.push_back(2);
        get_ways(num_stairs - 2);
        steps.pop_back();
        steps.push_back(3);
        get_ways(num_stairs - 3);
        steps.pop_back();
    }

    return total_ways;

}

void display_ways(const vector< vector<int> > &ways) {
    // Displays the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    for(int i = 0; i < (int) ways.size(); i++) {
        // Number formatting for when there are more than 9 total ways
        if((int) ways.size() > 9) {
            if(i < 9) {
                // If printing first 9 ways of the total ways
                cout << " " << (i + 1) << ". " << "[";
            } else {
                // If not printing first 9 ways of the total ways
                cout << (i + 1) << ". " << "[";
            }
        } else {
            // Number formating for when there aren't more than 9 total ways
            cout << (i + 1) << ". " << "[";
        }
        
        // Printing actual steps
        for(int j = 0; j < (int) ways[i].size(); j++) {
            if(j != ((int) ways[i].size()) - 1) {
                cout << ways[i][j] << ", ";
            } else {
                cout << ways[i][j];
            }
        }
        cout << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {
	int num_of_stairs;
    istringstream iss;

    // Checking if too many/no input arguments
	if(argc != 2) {
		cerr << "Usage: ./stairclimber <number of stairs>" << endl;
		return 1;
	}

    // Checking if input is not an int
	iss.str(argv[1]);
	if(!(iss >> num_of_stairs)) {
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}

    // Checking if input is not a positive int
    if(num_of_stairs <= 0) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
	
    // When input is valid:
    vector<vector<int>> total_ways_final = get_ways(num_of_stairs);
    
    if(num_of_stairs == 1) {
        cout << "1 way to climb 1 stair." << endl;
    } else {
        cout << total_ways_final.size() << " ways to climb " << num_of_stairs << " stairs." << endl;
    }
    
    display_ways(total_ways_final);

    return 0;

}