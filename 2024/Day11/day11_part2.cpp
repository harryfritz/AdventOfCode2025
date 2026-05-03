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
#include <map>

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

void insertOrIncrease(map <long long, long long>& stones, long long value) {
    auto s = stones.find(value);
    if(s == stones.end()) stones.insert({value,1});
    else stones.at(value)++;
}

long long mapCount(map <long long, long long>& stones) {
    long long result = 0;
    for(auto stone : stones) {
        result += stone.second;
    }
}

int main() {

    ifstream file;
    file.open("example.txt");
    string input;

    map <long long, long long> stones;

    while(getline(file, input)) {

        // cout << "\n" << input;

        for(string s : split(input, ' ')) {
            insertOrIncrease(stones, stoll(s));
        }
    
    }

    for(int blink = 0; blink < 25; blink++) {
        
        for(auto& stone : stones){
            stone.second--;
            long long stoneValue = stone.first;
            if(stoneValue == 0) {
                insertOrIncrease(stones, 1);
            } else if(digits(stoneValue)%2 == 0) {
                long long divider = evenIntegerDivider(stoneValue);
                insertOrIncrease(stones, stoneValue/divider);
                insertOrIncrease(stones, stoneValue%divider);
            } else {
                insertOrIncrease(stones, stoneValue*2024);
            }
        }
        
        cout << "\nBlink " << blink << ": " << stones.size() << " Stones";        
        
    }

    // cout << "\n\nAnswer: " << stones.size();    

    file.close();
    return 0;
}
