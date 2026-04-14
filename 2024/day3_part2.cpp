
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

vector <size_t> findAll(string& str, string pattern) {
    int cursor = 0;
    auto nextPos = str.find(pattern, cursor);
    vector <size_t> found;
    while(nextPos != string::npos) {
        found.push_back(nextPos);
        cursor = nextPos + 1;
        nextPos = str.find(pattern, cursor);
    }
    return found;
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    long long answer = 0; 
    while(getline(file, input)) {

        cout << "\n" << input;

        vector <size_t> dos = findAll(input, "do()");
        vector <size_t> donts = findAll(input, "don't()");
        vector <size_t> muls = findAll(input, "mul(");
        
        for(size_t mul : muls) {
            string sub = input.substr(mul + 4, input.find(")", mul) - mul - 4);
            cout << "\n" << mul << ": " << sub;

            if(true) {
                vector <string> numbers = split(sub, ',');
                if(numbers.size() == 2) {
                    if(isStringNumber(numbers[0]) && isStringNumber(numbers[1])) {
                        int product = stoi(numbers[0]) * stoi(numbers[1]);
                        answer += product;
                        cout << " - Valid - " << numbers[0] << "x" << numbers[1] << "=" << product;
                    } else {
                        cout << " - Invalid, elements non-numeral";
                    }
                } else {
                    cout << " - Invalid, more than 2 elements";
                }
            } else {
                cout << " - Invalid, Function Deactivated";
            } 
        }
    }

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}
