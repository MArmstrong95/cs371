/*
    Morgan Armstrong
    cs371
    9/13/18
    Purpose: Convert input in the form of Roman Numerals (up to 100)
             and output the equivalent base 10 value.
*/

#include <iostream>     // For user input + output
#include <string>       // For roman numeral input
#include <algorithm>    // For transform->input to uppercase
using namespace std;

/*
    State Table:
        | 16 States
        | 5 possible values: I, V, X, L, C
        | 0 (q0) == non accept state
*/
const int stateT[16][5] = {
    /* q0 */ {1, 2, 3, 4, 5},
    /* q1 */ {6, 8, 10, 0, 0},
    /* q2 */ {9, 0, 0, 0, 0},
    /* q3 */ {1, 2, 11, 13, 15},
    /* q4 */ {1, 2, 14, 0, 0},
    /* q5 */ {0, 0, 0, 0, 0},
    /* q6 */ {7, 0, 0, 0, 0},
    /* q7 */ {0, 0, 0, 0, 0},
    /* q8 */ {0, 0, 0, 0, 0},
    /* q9 */ {6, 0, 0, 0, 0},
    /* q10 */{0, 0, 0, 0, 0},
    /* q11 */{1, 2, 12, 0, 0},
    /* q12 */{1, 2, 0, 0, 0},
    /* q13 */{1, 2, 0, 0, 0},
    /* q14 */{1, 2, 11, 0, 0},
    /* q15 */{1, 2, 0, 0, 0}
};

/*
    Function: value
        | Params: r -> I || V || X || L || C
        | Purpose: Determine the value of the roman numeral
*/
int value(char r) {
    if (r == 'I')
        return 1;
    if (r == 'V')
        return 5;
    if (r == 'X')
        return 10;
    if (r == 'L')
        return 50;
    if (r == 'C')
        return 100;

    // Return -1 if invalid
    return -1;
}

/*
    Function: stateVal
        | Params: r -> I || V || X || L || C
        | Purpose: Determine which column to move to in State Table
*/
int stateVal(char r) {
    // Return -1 if invalid char input
    int rVal = -1;

    if (r == 'I')
        rVal = 0;
    if (r == 'V')
        rVal = 1;
    if (r == 'X')
        rVal = 2;
    if (r == 'L')
        rVal = 3;
    if (r == 'C')
        rVal = 4;

    return rVal;
}

/*
    Function: convertToRomanNumeral
        | Params: inText -> string to be parsed
        | Purpose: determine the integer value of the roman numeral string
*/
int convertToRomanNumeral(string &inText) {

    // init result number
    int answer = 0;

    // Loop through input
    for (int i = 0; i < inText.length(); i++) {
        int s1 = value(inText[i]);

        if (i+1 < inText.length()) {
            int s2 = value(inText[i+1]);

            if (s1 >= s2) {
                answer += s1;
            } else {
                answer = answer + s2 - s1;
                i++;
            }
        } else {
            answer += s1;
            i++;
        }
    }
    return answer;
}

int main() {

    // init state->q0, input->empty string
    int currState = 0;
    string input = "";

    // Prompt for user input and get input
    cout << "Enter a Roman Numeral (1-100 || -1 to exit): ";
    cin >> input;

    while (input != "-1") {

        // Convert input to uppercase to allow for lowercase input
        transform(input.begin(), input.end(), input.begin(), ::toupper);

        // Traverse through input string and find if state is accepted
        for (int i = 0; i < input.length(); i++) {
            currState = stateT[currState][stateVal(input[i])];

            if (currState == 0) {
                cout << endl << input << ": Invalid Roman Numeral" << endl;
                break;
            }
        }

        // If in an accept state, convert input from roman numeral to integer
        if (currState != 0) {
            cout << endl << input << ": " << convertToRomanNumeral(input) << endl;
        }
        currState = 0;
        input = "";

        cout << "Enter a Roman Numeral (1-100) (-1 to exit): ";
        cin >> input;
    }

    return 0;
}
