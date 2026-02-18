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
#include <algorithm>

using namespace std; 

bool isBtnCombCorrect(vector <int>& btnComb, vector <vector <int>>& buttons, vector <int>& joltages){

    vector <int> joltagesTry;
    for(int i = 0; i < joltages.size(); i++){
        joltagesTry.push_back(0);
    }

    for(int i = 0; i < btnComb.size(); i++){
        for(int k = 0; k < joltagesTry.size(); k++){
            joltagesTry[k] += btnComb[i] * buttons[i][k];
        }
    }

    for(int i = 0; i < joltagesTry.size(); i++){
        if(joltagesTry[i] != joltages[i]){
            return false;
        }
    }
    
    return true;
}

int main() {
  
    ifstream file;
    file.open("example.txt");
    string input;

    vector <vector <int>> joltages;
    vector <vector <vector <int>>> buttons;

    for(int i = 0; getline(file, input); i++){
        cout << "\n" + input;
        
        joltages.push_back({});
        string joltagesStr = input.substr(input.find("{") + 1, input.find("}") - input.find("{") - 1);
        int comma = 0;
        for(int k = 0; k < joltagesStr.size() && comma != -1;){
            comma = joltagesStr.find(',', k);
            joltages[i].push_back(stoi(joltagesStr.substr(k, comma - k)));
            k = comma + 1;
        }

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

    int answer = 0;
    for(int machine = 0; machine < buttons.size(); machine++){
        
        cout << "\nMachine " << machine;

        int presses = 0;
        for(int i = 0; i < joltages[machine].size(); i++){
            if(joltages[machine][i] > presses){
                presses = joltages[machine][i];
            }
        }

        int maxPresses = presses * joltages[machine].size();
        cout << " MaxPresses: " << maxPresses;
        bool found = false;
        while(presses < maxPresses && !found){

            cout << "\n\t" << presses << " presses";
            
            vector <int> btnPresses;
            
            for(int i = 0; i < presses; i++){
                btnPresses.push_back(1);
            }

            for(int i = 0; i < buttons[machine].size() - 1; i++){
                btnPresses.push_back(0);
            }

            sort(btnPresses.begin(), btnPresses.end());
            do {
                int acum = 0;
                vector <int> btnComb;
                for (int i = 0; i < btnPresses.size(); i++){
                    if(btnPresses[i] == 0){
                        btnComb.push_back(acum);
                        acum = 0;
                    } else if(btnPresses[i] == 1){
                        acum++;
                    }
                    if(i == btnPresses.size() - 1){
                        btnComb.push_back(acum);
                    }
                }

                if(isBtnCombCorrect(btnComb, buttons[machine], joltages[machine])){
                    found = true;
                    answer += presses;
                }

            } while (next_permutation(btnPresses.begin(), btnPresses.end()) && !found);

            presses++;
        }

    }

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}