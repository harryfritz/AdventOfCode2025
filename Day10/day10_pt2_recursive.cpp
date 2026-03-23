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

using namespace std;

#define INF 1000000

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

int minBtnPresses(vector <vector <int>>& buttons, vector <int>& joltages) {

    bool zero = true;
    for(int i = 0; i < joltages.size() && zero; i++) {
        if(joltages[i] != 0) {
            zero = false;
        }
    }
    if(zero) {
        return 0;
    }

    vector <int> btnPresses;
    vector <vector <vector <int>>> allCombinations;

    // Populate allCombinations with every possible button combination from 1 to buttons.size()
    for(int i = 1; i <= buttons.size(); i++) {
        vector <vector <vector <int>>> combinations;
        vector <vector <int>> dataArr;
        combinationUtil(buttons, 0, i, combinations, dataArr);
        for(vector <vector <int>> combination : combinations) {
            allCombinations.push_back(combination);
        }
    }

    // Goes through every combination checking which patterns match joltages
    for(int btnComb = 0; btnComb < allCombinations.size(); btnComb++) {
        
        // pattern adds all buttons from a given combination. Ex.: (1,3) (1,2) = [0101] [0110] = [0211]
        vector <int> pattern = allCombinations[btnComb][0];
        for(int btn = 1; btn < allCombinations[btnComb].size(); btn++) {
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
            vector <int> joltagesCache = joltages;
            for(int i = 0; i < joltagesCache.size(); i++) {
                joltagesCache[i] -= pattern[i];
                joltagesCache[i] /= 2;
                if(joltagesCache[i] < 0) {
                    validComb = false;
                }
            }

            if(validComb) {
                int min = minBtnPresses(buttons, joltagesCache);
                if(min != -1){
                    btnPresses.push_back(2*min + allCombinations[btnComb].size());
                }
            }
            
        }

    }
    
    if(btnPresses.size() == 0) {
        return -1;
    } else {
        int minPresses = btnPresses[0];
        for(int presses : btnPresses) {
            if(presses < minPresses) {
                minPresses = presses;
            }
        }
        return minPresses;
    }
    
}

int main() {
  
    ifstream file;
    file.open("example.txt");
    string input;

    vector <int> joltages;
    vector <vector <int>> buttons;

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

        if(line == 2) {
            int presses = minBtnPresses(buttons, joltages);
            answer += presses;
            cout << "\nLine " << line << " - " << presses << " Presses";
        }
 
    }

    
    
    cout << "\n\nAnswer: " << answer;
    
    
    file.close();
    return 0;
    
}
