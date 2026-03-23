/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 10 - Part two Recursive
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std; 

void combinationUtil(vector <vector <int>>& buttons, int ind, int r, 
                        vector <vector <vector <int>>>& combinations, vector <vector <int>>& dataArr) {
    int n = buttons.size();

    if(ind == 0){
        dataArr.clear();
        combinations.clear();
    }
    
    if (dataArr.size() == r) {
        combinations.push_back(dataArr);
        return;
    }

    for(int i = ind; i < n; i++) {
        dataArr.push_back(buttons[i]);
        combinationUtil(machine, i + 1, r, combinations, dataArr);
        dataArr.pop_back();
    }
}

vector <string> split(const string& s, char delim) {
    vector <string> tokens;
    string token;
    stringstream ss(s);
    
    while (getline(ss, token, delim)){
        tokens.push_back(token);
    }

    return tokens;
}

int minBtnPresses(vector <vector <int>>& buttons, vector <int> joltages){

    vector <vector <vector <int>>> combinations;
    vector <vector <int>> dataArr;

    combinationUtil(buttons, 0, )
    
    
    
    
    
    return 1000000;
}

int main() {
  
    ifstream file;
    file.open("example.txt");
    string input;

    vector <int> joltages;
    vector <vector <int>> buttons;

    int answer = 0;

    while(getline(file, input)){        
        
        vector <string> tokens = split(input, ' ');
        tokens.erase(tokens.begin());

        joltages.clear();
        string inner = tokens.back().substr(1, tokens.back().size() - 2);
        vector <string> joltagesStr = split(inner, ',');

        for(string j : joltagesStr){
            joltages.push_back(stoi(j));
        }
        
        tokens.pop_back();
        buttons.clear();

        for (string token : tokens) {
            
            vector <int> button;
            string inner = token.substr(1, token.size() - 2);
            vector<string> buttonsStr = split(inner, ',');

            for (string t : buttonsStr) {
                button.push_back(stoi(t));
            }
            buttons.push_back(button);
        }

        answer += minBtnPresses(buttons, joltages);
        
    }

    
    
    cout << "\n\nAnswer: " << answer;
    
    
    file.close();
    return 0;
    
}
