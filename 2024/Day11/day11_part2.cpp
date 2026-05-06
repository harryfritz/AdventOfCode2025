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

void insertOrIncrease(vector <vector <long long>>& stones, long long stoneValue, long long stoneAmount) {
    bool insert = true;
    long long stonePos = 0;
    while(stonePos < stones.size()){
        if(stones[stonePos][0] == stoneValue) {
            insert = false;
            break;
        }
        stonePos++;
    }

    if(insert){
        stones.push_back({stoneValue, stoneAmount});
    } else {
        stones[stonePos][1] += stoneAmount;
    }
}

long long stonesAmount(vector <vector <long long>>& stones) {
    long long result = 0;
    for(vector <long long> stone : stones) {
        result += stone[1];
    }
    return result;
}

int main() {

    ifstream file;
    file.open("input.txt");
    string input;

    vector <vector <long long>> stones1;
    vector <vector <long long>> stones2;

    while(getline(file, input)) {

        // cout << "\n" << input;

        for(string s : split(input, ' ')) {
            stones1.push_back({stoll(s),1});
        }
    
    }

    int arr = 1;
    for(int blink = 0; blink < 75; blink++) {
        
        if(arr == 1) {
            for(vector <long long> stone : stones1) {
                long long stoneValue = stone[0];
                if(stoneValue == 0) {
                    insertOrIncrease(stones2, 1, stone[1]);
                } else if(digits(stoneValue)%2 == 0) {
                    long long divider = evenIntegerDivider(stoneValue);
                    insertOrIncrease(stones2, stoneValue/divider, stone[1]);
                    insertOrIncrease(stones2, stoneValue%divider, stone[1]);
                } else {
                   insertOrIncrease(stones2, stoneValue*2024, stone[1]);
                }
            }
            stones1.clear();
            cout << "\nBlink " << blink << ": " << stonesAmount(stones2) << " Stones";   
            arr = 2;
        } else {
            for(vector <long long> stone : stones2) {
                long long stoneValue = stone[0];
                if(stoneValue == 0) {
                    insertOrIncrease(stones1, 1, stone[1]);
                } else if(digits(stoneValue)%2 == 0) {
                    long long divider = evenIntegerDivider(stoneValue);
                    insertOrIncrease(stones1, stoneValue/divider, stone[1]);
                    insertOrIncrease(stones1, stoneValue%divider, stone[1]);
                } else {
                   insertOrIncrease(stones1, stoneValue*2024, stone[1]);
                }
            }
            stones2.clear();
            cout << "\nBlink " << blink << ": " << stonesAmount(stones1) << " Stones";   
            arr = 1;
        }   
        
    }

    if(arr == 1) {
        cout << "\n\nAnswer: " << stonesAmount(stones1);    
    } else {
        cout << "\n\nAnswer: " << stonesAmount(stones2);            
    }
    
    file.close();
    return 0;
}
