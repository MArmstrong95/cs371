/*
    Morgan Armstrong
    cs371
    10/25/18
    Purpose: Create a mini-compiler
*/

#include <iostream>
#include <locale>
using namespace std;

/*
    State Table:
        | 5 States
        | 5 possible values: [A-Z] [0-9] [operator] [specChar] [space] [_, %, &]
        | 0 (q0) == non accept state
*/
const int stateT[5][6] = {
    /* Start: q0 */ {1, 2, 3, 4, 0, 0},
    /* Var:   q1 */ {1, 1, 3, 4, 0, 1},
    /* Digit: q2 */ {1, 2, 3, 4, 0, 0},
    /* Oper:  q3 */ {1, 2, 3, 4, 0, 0},
    /* spCh:  q4 */ {1, 2, 3, 4, 0, 0}
};

/*
    Function: isReserved
        | Params: inText -> string to be compared
        | Purpose: determine if the variable is a reserved word
*/
bool isReserved(string &inText) {
    if (inText == "PROGRAM"  || inText == "BEGIN"    || inText == "END"
        || inText == "IF"    || inText == "THEN"     || inText == "ELSE"
        || inText == "WHILE" || inText == "INTEGER"  || inText == "REAL"
        || inText == "FLOAT") {
        return true;
    }
    return false;
}

/*
    Function: getCode
        | Params: state-> current state, inText -> string to be compared
        | Purpose: determine the code to be returned, based on state and text
*/
int getCode(int state, string &inText) {

    if (state == 0) {
        return 600;
    } if (state == 1) {
        return 100;
    } if (state == 2) {
        return 200;
    } if (state == 3) {
        if (inText == "+") {
            return 301;
        } if (inText == "-") {
            return 302;
        } if (inText == "<") {
            return 303;
        } if (inText == ">") {
            return 304;
        } if (inText == "=") {
            return 305;
        }
        // default operator code
        return 300;
    } if (state == 4) {
        if (inText == ";") {
            return 401;
        } if (inText == ",") {
            return 402;
        } if (inText == ":") {
            return 404;
        } if (inText == "?") {
            return 405;
        } if (inText == "^") {
            return 406;
        }
        // default special char code
    } if (state == 5) {
        if (inText == "PROGRAM") {
            return 501;
        } if (inText == "BEGIN") {
            return 502;
        } if (inText == "END") {
            return 503;
        } if (inText == "IF") {
            return 504;
        } if (inText == "THEN") {
            return 505;
        } if (inText == "ELSE") {
            return 506;
        } if (inText == "WHILE") {
            return 507;
        } if (inText == "INTEGER") {
            return 508;
        } if (inText == "REAL") {
            return 509;
        } if (inText == "FOR") {
            return 510;
        }
        return 500;
    }

    return 600;
}

/*
    Function: stateVal
        | Params: r-> [A-Z] [0-9] [operator] [specChar] [space] [_, %, &]
        | Purpose: determine next state to go to in the FS Table
*/
int stateVal(char r) {

    int rVal = 0;

    if (isalpha(r)) {
        rVal = 0;
    }
    if (isdigit(r)) {
        rVal = 1;
    }
    if (r ==  '+' || r == '-' || r == '<' || r == '>' || r == '=') {
        rVal = 2;
    }
    if (r == ';' || r == ',' || r == ':' || r == '?' || r == '^') {
        rVal = 3;
    }
    if (r == ' ') {
        rVal = 4;
    }
    if (r == '_' || r == '%' || r == '&') {
        rVal == 5;
    }

    return rVal;
}

int main() {

    // init state->q0, input->empty string
    int currState = 0;
    string input = "", newStr = "";

    // Prompt for user input and get input
    cout << "Enter string(s) to be analyzed: (* to exit): ";
    cin >> input;

    while (input != "*") {

        for (int i = 0; i < input.length(); i++) {

            currState = stateT[currState][stateVal(input[i])];

            // Build string to check if reserved word
            if (isalpha(input[i])) {
                newStr = newStr + input[i];
            }

            // Check for reserved word
            if (isReserved(newStr)) {
                currState = 5;
            }

        }

        // Output code to screen
        cout << getCode(currState, input) << endl;

        newStr.clear();
        input.clear();
        currState = 0;

        cin >> input;
    }

    return 0;
}
