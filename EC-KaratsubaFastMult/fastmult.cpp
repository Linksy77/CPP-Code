/*******************************************************************************
 * Name        : fastmult.cpp
 * Description : Computes the product of two large (base-10) integers using the Karatsuba fast multiplication algorithm.
 ******************************************************************************/
#include <iostream>
#include <sstream>

using namespace std;

string padding(const string& a, int zerosToAdd) {
    string aCopy = a;

    for(int i = 0; i < zerosToAdd; i++) {
        aCopy = "0" + aCopy;
    }
    return aCopy;
}

string add(const string& a, const string& b) {
    string aCopy = a;
    string bCopy = b;

    string result = "";
    int sum;
    int carry = 0;

    // Making aCopy and bCopy of the same length
    if(a.length() > b.length()) {
        int zerosToAdd = a.length() - b.length();
        bCopy = padding(bCopy, zerosToAdd);
    } else if(b.length() > a.length()) {
        int zerosToAdd = b.length() - a.length();
        aCopy = padding(aCopy, zerosToAdd);
    }

    // Addition loop
    for(int i = (aCopy.length() - 1); i > -1; i--) {
        sum = (aCopy[i] - '0') + (bCopy[i] - '0') + carry;

        // Checking if carrying is necessary & adjusting values accordingly
        if(sum >= 10) {
            result = to_string(sum%10) + result;
            carry = sum/10;
        } else {
            result = to_string(sum) + result;
            carry = 0;
        }
    }

    if(carry > 0) {
        result = to_string(carry) + result;
    }

    return result;
}

string subtract(const string& a, const string& b) {
    string aCopy = a;
    string bCopy = b;

    string result = "";
    int diff;
    int regroup = 0;

    // Making aCopy and bCopy of the same length
    if(a.length() > b.length()) {
        int zerosToAdd = a.length() - b.length();
        bCopy = padding(bCopy, zerosToAdd);
    } else if(b.length() > a.length()) {
        int zerosToAdd = b.length() - a.length();
        aCopy = padding(aCopy, zerosToAdd);
    }

    // Subtraction loop
    for(int i = (int)(aCopy.length() - 1); i > -1; i--) {
        diff = (aCopy[i] - '0') - (bCopy[i] - '0') - regroup;

        // Checking if regrouping is necessary & adjusting values accordingly
        if(diff < 0) {
            diff += 10;
            regroup = 1;
        } else {
            regroup = 0;
        }

        result = to_string(diff) + result;
    }

    return result;
}

string multiply(const string& a, const string& b) {
    string result = "";
    int resCalc = 0;

    // Multiplication loop
    for(int i = 0; i < (b[0] - '0'); i++) {
        resCalc += (a[0] - '0');
    }

    result = to_string(resCalc);
    return result;
}

string karatsuba(const string& a, const string& b) {
    string aCopy = a;
    string bCopy = b;

    // Making sure aCopy is the lesser of the two nums 
    if(aCopy.length() > bCopy.length()) {
        swap(aCopy, bCopy);
    }

    // Making aCopy and bCopy of the same length
    aCopy = padding(aCopy, (int)(bCopy.length() - aCopy.length()));

    // Base case
    if((int)(aCopy.length()) == 1) {
        return multiply(aCopy, bCopy);
    }

    // Making length of nums even
    if((int)(aCopy.length())%2 != 0) {
        aCopy = "0" + aCopy;
        bCopy = "0" + bCopy;
    }

    // Splitting a and b into left (l) and right (r) halves
    string al = aCopy.substr(0, (int)(aCopy.length()/2));
    string ar = aCopy.substr((int)(aCopy.length()/2), (int)(aCopy.length()/2));
    string bl = bCopy.substr(0, (int)(bCopy.length()/2));
    string br = bCopy.substr((int)(bCopy.length()/2), (int)(bCopy.length()/2));

    // Computing (al * bl) and (ar * br) to find 1st coeff and to have for subsequent use
    string albl = karatsuba(al, bl);    // albl = al * bl (coeff1)
    string arbr = karatsuba(ar, br);    // arbr = ar * br

    // Computing the 2nd coeff.: (((al + ar) * (bl + br)) - ((al * bl) + (ar * br)))
    string alrblr = karatsuba((add(al, ar)), (add(bl, br)));    // alrblr = (al + ar) * (bl + br)
    string sumablabr = add(albl, arbr);                         // sumablabr = (al * bl) + (ar * br)
    string coeff2 = subtract(alrblr, sumablabr);                // coeff2 = alrblr - sumablabr

    // Multiplying coeff1 by 10^(aCopy.length())
    string firstTerm = albl;
    for(int i = 0; i < (int)(aCopy.length()); i++) {
        firstTerm = firstTerm + "0";
    }

    // Multiplying coeff2 by 10^((aCopy.length())/2)
    string secondTerm = coeff2;
    for(int i = 0; i < ((int)(aCopy.length()))/2; i++) {
        secondTerm = secondTerm + "0";
    }

    // Calculating & returning result
    string result = add(firstTerm, add(secondTerm, arbr));

    return result;
}

string finalAdjust(const string& a) {
    int firstNonZero = 0;
    string adjustedResult = "";

    // Loop to find first index position from the left that is not zero
    while(to_string(a[firstNonZero] - '0') == "0") {
        firstNonZero++;
    }

    // Checking to see if there is no adjustment needed
    if(firstNonZero == 0) {
        return a;
    }

    // If adjustment is needed: return string without the padding from the beginning
    for(int i = firstNonZero; i < (int)(a.length()); i++) {
        adjustedResult += a[i];
    }

    return adjustedResult;
}

int main(int argc, char *argv[]) {
    string x = argv[1];
    string y = argv[2];

    if(x == "0" || y == "0") {
        cout << "0" << endl;
    } else {
        // Making x and y of the same length
        if(x.length() > y.length()) {
            int zerosToAdd = x.length() - y.length();
            y = padding(y, zerosToAdd);
        } else if(y.length() > x.length()) {
            int zerosToAdd = y.length() - x.length();
            x = padding(x, zerosToAdd);
        }

        // Removing any padding from beginning of result & printing result
        string result = finalAdjust(karatsuba(x, y));
        cout << result << endl;
    }

    return 0;
}