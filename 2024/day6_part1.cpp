
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 6 - Part one
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

char rotateGuard(char guard) {
    if(guard == '^') return '>';
    if(guard == '>') return 'v';
    if(guard == 'v') return '<';
    if(guard == '<') return '^';
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    vector <string> map;
    int guardX = 0;
    int guardY = 0;
    while(getline(file, input)) {
        cout << "\n" << input;
        map.push_back(input);
        for(int c = 0; c < input.size(); c++) {
            if(input[c] == '^'){
                guardX = c;
                guardY = map.size() - 1;
            } 
        }    
    }
    
    bool exit = false;
    while(!exit) {
        int nextX = guardX;
        int nextY = guardY;
        if(map[guardY][guardX] == '^') {            
            nextY--;
        } else if(map[guardY][guardX] == '>') {
            nextX++;
        } else if(map[guardY][guardX] == 'v') {
            nextY++;
        } else if(map[guardY][guardX] == '<') {
            nextX--;
        }

        if(nextX < 0 || nextX >= map[0].size() || nextY < 0 || nextY >= map.size()) {
            exit = true;
            map[guardY][guardX] = 'X';
        } else {
            if(map[nextY][nextX] == '.' || map[nextY][nextX] == 'X') {
                map[nextY][nextX] = map[guardY][guardX];
                map[guardY][guardX] = 'X';
                guardX = nextX;
                guardY = nextY;
            } else if(map[nextY][nextX] == '#') {
                map[guardY][guardX] = rotateGuard(map[guardY][guardX]);
            }
        }

    }

    long long answer = 0; 

    cout << "\n";
    for(string s : map){
        cout << "\n" << s;
        for(char c : s) {
            if(c == 'X') answer++;
        }
    }

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}
