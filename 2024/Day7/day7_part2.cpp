
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 7 - Part two
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

void findCombinations(vector<char>& arr, vector<char>& current, int r, vector<vector<char>>& result) {
    if (current.size() == r) {
        result.push_back(current);
        return;
    }
    for (int i = 0; i < arr.size(); i++) {
        current.push_back(arr[i]);
        findCombinations(arr, current, r, result); 
        current.pop_back();
    }
}

// Returns all the possible '+' and '*' combinations of n elements
vector <vector <char>> operatorsComb(int n) {
    vector <char> operators = {'+','*','|'};
    vector <char> current;
    vector <vector <char>> result;
    findCombinations(operators, current, n, result);
    return result;
}

// Ex: a=123, b=456, returns 123456
long long concatenate(long long a, long long b) {
    long long bDig = b;
    while(bDig){
        bDig /= 10;
        a *= 10;
    }
    return a + b;
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

        cout << "\n" << eq << "\t" << testValue << ":";
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
                } else if(op == '|') {
                    result = concatenate(result, equation[i]);
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
