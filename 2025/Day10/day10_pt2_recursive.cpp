/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 10 - Part two Recursive
// Author: Fritz, M.H.
//
// https://www.reddit.com/r/adventofcode/comments/1pk87hl/2025_day_10_part_2_bifurcate_your_way_to_victory/
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

#define INF 1000000

vector <vector <int>> buttons;
vector <vector <vector <int>>> allCombinations;

void combinationUtil(vector <vector <int>>& buttons, int ind, int r, 
                        vector <vector <vector <int>>>& combinations, vector <vector <int>>& dataArr) {
    int n = buttons.size();

    if(ind == 0) {
        dataArr.clear();
        combinations.clear();
    }
    
    if(dataArr.size() == r) {
        combinations.push_back(dataArr);
        return;
    }

    for(int i = ind; i < n; i++) {
        dataArr.push_back(buttons[i]);
        combinationUtil(buttons, i + 1, r, combinations, dataArr);
        dataArr.pop_back();
    }
}

vector <string> split(const string& text, char delim) {
    vector <string> tokens;
    
    int nextDelim = 0, cursor = 0;
    while(nextDelim >= 0) {
        nextDelim = text.find(delim, cursor + 1);
        tokens.push_back(text.substr(cursor, nextDelim - cursor));
        cursor = nextDelim + 1;
    }

    return tokens;
}

int minBtnPresses(vector <int>& joltages, int line, int level) {

    bool allZero = true;
    for(int i = 0; i < joltages.size(); i++) {
        if(joltages[i] < 0) {
            return INF;
        } else if(joltages[i] != 0) {
            allZero = false;
        }
    }
    if(allZero) {
        return 0;
    }

    int minPresses = INF;
    
    // Goes through every combination checking which patterns match joltages
    vector <vector <vector <int>>> validCombinations;
    for(int btnComb = 0; btnComb < allCombinations.size(); btnComb++) {
    
        // pattern adds all buttons from a given combination. Ex.: (1,3) (1,2) = [0101] [0110] = [0211]
        vector <int> pattern(joltages.size(),0);
        for(int btn = 0; btn < allCombinations[btnComb].size(); btn++) {
            for(int i = 0; i < pattern.size(); i++) {
                pattern[i] += allCombinations[btnComb][btn][i];
            }
        }     
        
        // Check if pattern matches parity with joltages. If yes, moves forward
        bool validComb = true;
        for(int i = 0; i < pattern.size() && validComb; i++) {
            if((pattern[i] % 2) != (joltages[i] % 2) || pattern[i] > joltages[i]){
                validComb = false;
            }
        }

        if(validComb){
            validCombinations.push_back(allCombinations[btnComb]);
        }

    }    
    
    // Goes through every valid combination
    for(int btnComb = 0; btnComb < validCombinations.size(); btnComb++) {
        
        vector <int> pattern(joltages.size(),0);
        for(int btn = 0; btn < validCombinations[btnComb].size(); btn++) {
            for(int i = 0; i < pattern.size(); i++) {
                pattern[i] += validCombinations[btnComb][btn][i];
            }
        } 

        vector <int> joltagesCache = joltages;
        int multiplier = 1;
        
        for(int i = 0; i < joltagesCache.size(); i++) joltagesCache[i] -= pattern[i];

        bool allEven = true;
        for(int j : joltagesCache) if(j%2==1) allEven = false;
        if(allEven){
            for(int i = 0; i < joltagesCache.size(); i++) joltagesCache[i] /= 2;
            multiplier = 2;
        }

        int min = multiplier*minBtnPresses(joltagesCache, line, level+1) + validCombinations[btnComb].size();

        if(min < minPresses){
            minPresses = min;
        }

    }

    return minPresses;
    
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    vector <int> joltages;
    
    int answer = 0;

    for(int line = 0; getline(file, input); line++) {        
        
        vector <string> tokens = split(input, ' ');
        tokens.erase(tokens.begin());

        joltages.clear();
        string inner = tokens.back().substr(1, tokens.back().size() - 2);
        vector <string> joltagesStr = split(inner, ',');

        for(string j : joltagesStr) {
            joltages.push_back(stoi(j));
        }
        
        tokens.pop_back();

        buttons.clear();
        for (string token : tokens) {
            
            vector <int> button;
            string inner = token.substr(1, token.size() - 2);
            vector<string> buttonsStr = split(inner, ',');

            for(int j : joltages) button.push_back(0);
            for (string t : buttonsStr) {
                button[stoi(t)] = 1;
            }
            buttons.push_back(button);
        }

        if(true) {            
            
            // Populate allCombinations with every possible button combination from 1 to buttons.size()
            allCombinations.clear();
            for(int i = 0; i <= buttons.size(); i++) {
                vector <vector <vector <int>>> combinations;
                vector <vector <int>> dataArr;
                combinationUtil(buttons, 0, i, combinations, dataArr);
                for(vector <vector <int>> combination : combinations) {
                    allCombinations.push_back(combination);
                }
            }
            
            int presses = minBtnPresses(joltages, line, 0);
            answer += presses;
                       
            cout << "\nLine " << line << " - " << presses << " Presses";
        }
 
    }

    cout << "\n\nAnswer: " << answer;
    
    file.close();
    return 0;
    
}
