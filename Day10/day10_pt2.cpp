/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 10 - Part one and two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std; 

bool isButtonCombCorrect(vector <char>& indicators, vector <int>& btnComb){    
    for(int i = 0; i < indicators.size(); i++){
        if(btnComb[i] % 2 == 0 && indicators[i] == '#' || btnComb[i] % 2 == 1 && indicators[i] == '.') {
            return false;
        }
    }
    return true;
}

void combinationUtil(vector <vector <int>>& machine, int ind, int r, 
                        vector <vector <vector <int>>>& combinations, vector <vector <int>>& dataArr) {
    int n = machine.size();

    if(ind == 0){
        dataArr.clear();
        combinations.clear();
    }
    
    if (dataArr.size() == r) {
        combinations.push_back(dataArr);
        return;
    }

    for(int i = ind; i < n; i++) {
        dataArr.push_back(machine[i]);
        combinationUtil(machine, i + 1, r, combinations, dataArr);
        dataArr.pop_back();
    }
}

vector <vector <int>> buttonCombinations(vector <vector <int>>& machine, int r){
    vector <vector <vector <int>>> combinations;
    vector <vector <int>> dataArr;
    vector <vector <int>> btnComb;

    combinationUtil(machine, 0, r, combinations, dataArr);

    for(int i = 0; i < combinations.size(); i++){
        btnComb.push_back({});
        for(int k = 0; k < combinations[i][0].size(); k++){
            int sum = 0;
            for(int j = 0; j < combinations[i].size(); j++){
                sum += combinations[i][j][k];
            }
            btnComb[i].push_back(sum);
        }
    }

    return btnComb;
}

int main() {
  
    ifstream file;
    file.open("example.txt");
    string input;

    vector <vector <int>> joltages;
    vector <vector <vector <int>>> buttons;

    for(int i = 0; getline(file, input); i++){
        cout << "\n" + input;
        
        string joltagesStr = input.substr(input.find("{"), input.find("}"));
        for(int i = 0; i < joltagesStr.size(); i++){
            i = joltagesStr.find(',', i);
            cout << "\nComma: " << i;
        }
        
        // joltages.push_back({});
        // for(char c : joltagesStr){
        //     if(c >= '0' && c <= '9'){
        //         joltages[i].push_back(c - 48);
        //     }
        // }

        string button = input.substr(input.find("]") + 1, input.find("{") - input.find("]") - 1);
        buttons.push_back({});
        int j = -1;
        for(int c = 0; c < button.size(); c++){
            if(button[c] == '('){
                buttons[i].push_back({});
                j++;
                for(int k = 0; k < joltages[i].size(); k++){
                    buttons[i][j].push_back(0);
                }
            }
            if(button[c] >= '0' && button[c] <= '9'){
                buttons[i][j][button[c] - 48] = 1;
            }
        }
    }    
    
    // int answer = 0;
    // for(int machine = 0; machine < buttons.size(); machine++){
    //     bool foundCombination = false;
    //     for(int presses = 1; presses <= buttons[machine].size() && !foundCombination; presses++){            

    //         for(vector <int> combination : buttonCombinations(buttons[machine], presses)){
    //             if(isButtonCombCorrect(indicators[machine], combination)){
    //                 cout << "\nMachine " << machine << ", " << presses << " button presses";
    //                 foundCombination = true;
    //                 answer += presses;
    //                 break;
    //             }
    //         }

    //     }
    // }

    // cout << "\n\nAnswer: " << answer;
    

    file.close();
    return 0;
}