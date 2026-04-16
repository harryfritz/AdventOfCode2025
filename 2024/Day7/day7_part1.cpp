
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 7 - Part one
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

// Ex: n = 5, size = 8. returns "00000101"
string getBinaryString(int n, int size) {
    string s = "";
    for (int i = size - 1; i >= 0; i--) {
        if (n&(1<<i)) {
            s += '1';
        } else {
            s += '0';
        }
    }
    return s;
}

// Returns all the possible '+' and '*' combinations of n elements
vector <vector <char>> operatorsComb(int n) {
    vector <vector <char>> combs;
    int combCount = 1;
    for(int i = 0; i < n; i++) combCount *= 2;

    for(int combination = 0; combination < combCount; combination++) {
        vector <char> operators;
        for(char c : getBinaryString(combination, n)) {
            if(c == '0') {
                operators.push_back('+');
            } else if(c == '1') {
                operators.push_back('*');
            }
        }
        combs.push_back(operators);
    }
    return combs;
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    vector <long long> testValues;
    vector <vector <int>> equations;
    while(getline(file, input)) {

        // cout << "\n" << input;

        vector <string> line = split(input, ' ');
        line[0].pop_back(); // Remove the ':'
        testValues.push_back(stoll(line[0]));
        vector <int> equation;
        for(int e = 1; e < line.size(); e++) {
            equation.push_back(stoi(line[e]));
        }
        equations.push_back(equation);
    }

    long long answer = 0; 
    for(int eq = 0; eq < equations.size(); eq++) {
        vector <int> equation = equations[eq];
        long long testValue = testValues[eq];
        
        cout << "\n" << testValue << ":";
        for(int value : equation) cout << " " << value;
        cout << " - ";

        vector <vector <char>> operatorCombs = operatorsComb(equation.size() - 1);
        bool canBeTrue = false;

        for(vector <char> operators : operatorCombs) {
            long long result = equation[0];

            for(int i = 1; i < equation.size(); i++){
                char op = operators[i-1];
                if(op == '+') {
                    result += equation[i];
                } else if(op == '*') {
                    result *= equation[i];
                }
            }        

            if(result == testValue){
                canBeTrue = true;
                break;
            }
        }

        if(canBeTrue){
            cout << "Valid";
            answer += testValue;
        } else {
            cout << "Invalid";
        }
    }

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}
