/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 11 - Part one
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <queue>

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

int digits(long long number) {
    if(number < 10) return 1;
    return 1 + digits(number/10);
}

long long evenIntegerDivider(long long number) {
    long long divider = 1;
    int halfDigits = digits(number) / 2;
    for(int i = 0; i < halfDigits; i++) {
        divider *= 10;
    }
    return divider;
}

int main() {

    ifstream file;
    file.open("input.txt");
    string input;

    queue <long long> stones;

    while(getline(file, input)) {

        // cout << "\n" << input;

        for(string s : split(input, ' ')) {
            stones.push(stoll(s));
        }
    
    }

    for(int blink = 0; blink < 75; blink++) {
        
        long long queueSize = stones.size();
        for(long long i = 0; i < queueSize; i++) {
            long long stone = stones.front();
            stones.pop();
            if(stone == 0) {
                stones.push(1);
            } else if(digits(stone)%2 == 0) {
                long long divider = evenIntegerDivider(stone);
                stones.push(stone/divider);
                stones.push(stone%divider);
            } else {
                stones.push(stone*2024);
            }
        }
        cout << "\nBlink " << blink << ": " << stones.size() << " Stones";        
        
    }

    cout << "\n\nAnswer: " << stones.size();    

    file.close();
    return 0;
}
