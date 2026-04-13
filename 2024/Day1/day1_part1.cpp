/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 1 - Part one
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

int main() {
  
    ifstream file;
    file.open("example.txt");
    string input;

    while(getline(file, input)) {

        vector <string> str = split(input, ' ');
        cout << "\n" << input;
        
    }


    file.close();
    return 0;
}