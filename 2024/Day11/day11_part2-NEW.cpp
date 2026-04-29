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

    vector <vector <long long>> stones1;
    vector <vector <long long>> stones2;
    
    stones1.push_back({});
    while(getline(file, input)) {

        // cout << "\n" << input;

        for(string s : split(input, ' ')) {
            stones1[0].push_back(stoll(s));
        }
    
    }

    const long long max_size = 10000000;
    int vector = 1;
    
    for(int blink = 0; blink < 75; blink++) {
        
        if(vector == 1) {
            
            int stones2Address = 0;
            long long stones2ArrCount = 0;
            long long stones2Count = 0;
            stones2.push_back({});
            for(auto stoneArr : stones1) {
                for(long long stone : stoneArr) {
                    if(stone == 0) {
                        stones2[stones2Address].push_back(1);
                        stones2ArrCount++;
                        stones2Count++;
                    } else if(digits(stone)%2 == 0) {
                        long long divider = evenIntegerDivider(stone);
                        stones2[stones2Address].push_back(stone/divider);
                        stones2[stones2Address].push_back(stone%divider);
                        stones2ArrCount+=2;
                        stones2Count+=2;
                    } else {
                        stones2[stones2Address].push_back(stone*2024);
                        stones2ArrCount++;
                        stones2Count++;
                    }
                    
                    if(stones2ArrCount > max_size) {
                        stones2.push_back({});
                        stones2Address++;
                        stones2ArrCount = 0;
                    }
                }
            }
            stones1.clear();
            vector = 2;
            cout << "\nBlink " << blink << ": " << stones2Count << " Stones";
        } else {
            int stones1Address = 0;
            long long stones1ArrCount = 0;
            long long stones1Count = 0;
            stones1.push_back({});
            for(auto stoneArr : stones2) {
                for(long long stone : stoneArr) {
                    if(stone == 0) {
                        stones1[stones1Address].push_back(1);
                        stones1ArrCount++;
                        stones1Count++;
                    } else if(digits(stone)%2 == 0) {
                        long long divider = evenIntegerDivider(stone);
                        stones1[stones1Address].push_back(stone/divider);
                        stones1[stones1Address].push_back(stone%divider);
                        stones1ArrCount+=2;
                        stones1Count+=2;
                    } else {
                        stones1[stones1Address].push_back(stone*2024);
                        stones1ArrCount++;
                        stones1Count++;
                    }
                    
                    if(stones1ArrCount > max_size) {
                        stones1.push_back({});
                        stones1Address++;
                        stones1ArrCount = 0;
                    }
                }
            }
            stones2.clear();
            vector = 1;
            cout << "\nBlink " << blink << ": " << stones1Count << " Stones";
        }

    }

    if(vector == 1) cout << "\n\nAnswer: " << stones1.size();
    else cout << "\n\nAnswer: " << stones2.size();
    
    

    file.close();
    return 0;
}