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

int determinant(vector <vector <int>>& matrix){

    if(matrix.size() == 2){
        return matrix[0][0] * matrix[0][0] - matrix[0][1] * matrix[1][0];
    }

    int det = 0;
    for(int j = 0; j < matrix[0].size(); j++){
        vector <vector <int>> minor = matrix;

        minor.erase(minor.begin());
        for(int i = 0; i < minor.size(); i++){
            minor[i].erase(minor[i].begin() + j);
        }

        if(j % 2 == 0){
            det += matrix[0][j] * determinant(minor);
        } else {
            det -= matrix[0][j] * determinant(minor);
        }
    }

    return det;

}

vector <int> sysSolution(vector <vector <int>>& A, vector <int>& B){
    vector <int> X;

    int detA = determinant(A);

    for(int x = 0; x < B.size(); x++){
        vector <vector <int>> Ab = A;
        for(int i = 0; i < B.size(); i++){
            Ab[i][x] = B[i];
        }
        X.push_back(determinant(Ab) / detA);
    }

    return X;

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

    vector <vector <vector <int>>> btnComb;
    vector <vector <int>> dataArr;

    int machine = 1;
    vector <vector <int>> base;
    
    
    
    
    file.close();
    return 0;
    
    int answer = 0;
    for(int machine = 0; machine < buttons.size(); machine++){
        int buttonsPressed = 100000;
        combinationUtil(buttons[machine], 0, joltages[machine].size(), btnComb, dataArr);
        for(vector <vector <int>> base : btnComb){
            if(determinant(base) != 0){
                vector <int> solution = sysSolution(base, joltages[machine]);
                int sum = 0;
                for(int press : solution){
                    if(press < 0){
                        sum = 0;
                        break;
                    }
                    sum += press;
                }
                if(sum < buttonsPressed){
                    buttonsPressed = sum;
                }
            }
        }
        answer += buttonsPressed;
    }
    cout << "\n\nAnswer: " << answer;

    // int answer = 0;
    // for(int machine = 0; machine < buttons.size(); machine++){
        
    //     cout << "\nMachine " << machine;

    //     int presses = 0;
    //     for(int i = 0; i < joltages[machine].size(); i++){
    //         if(joltages[machine][i] > presses){
    //             presses = joltages[machine][i];
    //         }
    //     }

    //     int maxPresses = presses * joltages[machine].size();
    //     cout << " MaxPresses: " << maxPresses;
    //     bool found = false;
    //     while(presses < maxPresses && !found){

    //         cout << "\n\t" << presses << " presses";
            
    //         vector <int> btnPresses;
            
    //         for(int i = 0; i < presses; i++){
    //             btnPresses.push_back(1);
    //         }

    //         for(int i = 0; i < buttons[machine].size() - 1; i++){
    //             btnPresses.push_back(0);
    //         }

    //         sort(btnPresses.begin(), btnPresses.end());
    //         do {
    //             int acum = 0;
    //             vector <int> btnComb;
    //             for (int i = 0; i < btnPresses.size(); i++){
    //                 if(btnPresses[i] == 0){
    //                     btnComb.push_back(acum);
    //                     acum = 0;
    //                 } else if(btnPresses[i] == 1){
    //                     acum++;
    //                 }
    //                 if(i == btnPresses.size() - 1){
    //                     btnComb.push_back(acum);
    //                 }
    //             }

    //             if(isBtnCombCorrect(btnComb, buttons[machine], joltages[machine])){
    //                 found = true;
    //                 answer += presses;
    //             }

    //         } while (next_permutation(btnPresses.begin(), btnPresses.end()) && !found);

    //         presses++;
    //     }

    // }

    // cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}