
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 3 - Part two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector <string> split(const string& text, char delim) {
    vector <string> tokens;
    int nextDelim = 0, cursor = 0;
    while(nextDelim >= 0) {
        nextDelim = text.find(delim, cursor + 1);
        tokens.push_back(text.substr(cursor, nextDelim - cursor));
        if(nextDelim >= 0) {
            cursor = nextDelim;
            while(text[cursor] == delim) cursor++;
        }
    }
    return tokens;
}

bool isStringNumber(string& str) {
    for(char c : str) {
        if(c < '0' || c > '9') return false;
    }

    return true;
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    long long answer = 0; 
    bool enabled = true;
    while(getline(file, input)) {

        cout << "\n" << input;

        
        for(int c = 0; c < input.size(); c++) {
            if(input[c] == 'd' && input[c+1] == 'o' && input[c+2] == '(' && input[c+3] == ')') {
                enabled = true;
            } 
            if(input[c] == 'd' && input[c+1] == 'o' && input[c+2] == 'n' && input[c+3] == 39
                && input[c+4] == 't' && input[c+5] == '(' && input[c+6] == ')') {
                enabled = false;
            }
            if(input[c] == 'm' && input[c+1] == 'u' && input[c+2] == 'l' && input[c+3] == '(') {
                string sub = input.substr(c + 4, input.find(")", c) - c - 4);
                cout << "\n" << c << ": " << sub;
                vector <string> numbers = split(sub, ',');
                if(numbers.size() == 2) {
                    if(isStringNumber(numbers[0]) && isStringNumber(numbers[1])) {
                        if(enabled) {
                            int product = stoi(numbers[0]) * stoi(numbers[1]);
                            answer += product;
                            cout << " - Valid - " << numbers[0] << "x" << numbers[1] << "=" << product;
                        } else {
                            cout << " - Invalid, disabled";
                        }
                    } else {
                        cout << " - Invalid, elements non-numeral";
                    }
                } else {
                    cout << " - Invalid, more than 2 elements";
                }
            }
        }
        
    }

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}
