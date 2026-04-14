
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 4 - Part one
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string word = "XMAS";

// 1 2 3
// 4 X 5
// 6 7 8

void searchAround(vector <string>& wordSearch, int letter, int i, int j, int dir, int &count) {
    
    if(word[letter] == 'S'){
        count++;
        return;
    }

    int rows = wordSearch.size();
    int columns = wordSearch[0].size();
    
    if(dir == 1) {
        if(i > 0 && j > 0) {
            if(wordSearch[i-1][j-1] == word[letter + 1]) {
                searchAround(wordSearch, letter + 1, i-1, j-1, dir, count);
            }
        }
    } else if(dir == 2) {
        if(i > 0) {
            if(wordSearch[i-1][j] == word[letter + 1]) {
                searchAround(wordSearch, letter + 1, i-1, j, dir, count);
            }
        }
    } else if(dir == 3) {
        if(i > 0 && j < columns - 1) {
            if(wordSearch[i-1][j+1] == word[letter + 1]) {
                searchAround(wordSearch, letter + 1, i-1, j+1, dir, count);
            }
        }
    } else if(dir == 4) {
        if(j > 0) {
            if(wordSearch[i][j-1] == word[letter + 1]) {
                searchAround(wordSearch, letter + 1, i, j-1, dir, count);
            }
        }
    } else if(dir == 5) {
        if(j < columns - 1) {
            if(wordSearch[i][j+1] == word[letter + 1]) {
                searchAround(wordSearch, letter + 1, i, j+1, dir, count);
            }
        }
    } else if(dir == 6) {
        if(i < rows - 1 && j > 0) {
            if(wordSearch[i+1][j-1] == word[letter + 1]) {
                searchAround(wordSearch, letter + 1, i+1, j-1, dir, count);
            }
        }
    } else if(dir == 7) {
        if(i < rows - 1) {
            if(wordSearch[i+1][j] == word[letter + 1]) {
                searchAround(wordSearch, letter + 1, i+1, j, dir, count);
            }
        }
    } else if(dir == 8) {
        if(i < rows - 1 && j < columns - 1) {
            if(wordSearch[i+1][j+1] == word[letter + 1]) {
                searchAround(wordSearch, letter + 1, i+1, j+1, dir, count);
            }
        }
    }
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    long long answer = 0; 
    vector <string> wordSearch;
    while(getline(file, input)) {
        cout << "\n" << input;
        wordSearch.push_back(input);
    }

    int count = 0;
    for(int i = 0; i < wordSearch.size(); i++){
        for(int j = 0; j < wordSearch[i].size(); j++){
            if(wordSearch[i][j] == 'X') for(int dir = 1; dir <= 8; dir++) searchAround(wordSearch, 0, i, j, dir, count);
        }
    }

    cout << "\n\nAnswer: " << count;

    file.close();
    return 0;
}
