
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 3 - Part one
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
    while(getline(file, input)) {

        cout << "\n" << input;

        int cursor = 0;
        auto nextPos = input.find("mul(", cursor);
        while(nextPos != string::npos) {
            
            string sub = input.substr(nextPos + 4, input.find(")", nextPos) - nextPos - 4);
            cout << "\n" << nextPos << ": " << sub;

            vector <string> numbers = split(sub, ',');
            if(numbers.size() == 2) {
                if(isStringNumber(numbers[0]) && isStringNumber(numbers[1])) {
                    int product = stoi(numbers[0]) * stoi(numbers[1]);
                    answer += product;
                    cout << " - Valid - " << numbers[0] << "x" << numbers[1] << "=" << product;
                } else {
                    cout << " - Invalid";
                }
            } else {
                cout << " - Invalid";
            }

            cursor = nextPos + 1;
            nextPos = input.find("mul(", cursor);

        }

        
    }

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}
