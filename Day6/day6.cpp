/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 6 - Part one and two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define INPUTLINES 5

int main() {
  
    ifstream file;
    string fileName = "input.txt";
    file.open(fileName);
    string input;

    for(int i = 0; i < INPUTLINES; i++){
        getline(file, input);
    }

    vector<char> operators;
    for(int i = 0; i < input.size() - 1; i++){
        if(input[i] == '+' || input[i] == '*'){
            operators.push_back(input[i]);
        }
    }

    file.close();
    file.open(fileName);


    // Part 2
    vector<vector <int>> numbers;
    for(int i = 0; i < operators.size(); i++){
        numbers.push_back({});
    }
    
    vector<vector <char>> inMatrix;
    vector<vector <char>> inMatrixTransp;
    for(int i = 0; i < INPUTLINES - 1; i++){
        inMatrix.push_back({});
        getline(file, input);
        for(int j = 0; j < input.size(); j++){
            inMatrix[i].push_back(input[j]);
        }
    }

    for(int i = 0; i < inMatrix.size(); i++){
        for(int j = inMatrix[i].size() - 1; j >= 0; j--){
            if(i == 0){
                inMatrixTransp.push_back({});
            }
            inMatrixTransp[inMatrix[i].size() - 1 - j].push_back(inMatrix[i][j]);
        }
    }
    
    string str;
    for(int i = 0, j = 0; i < inMatrixTransp.size(); i++){
        string str(inMatrixTransp[i].begin(), inMatrixTransp[i].end());
        if(str.find_first_not_of(' ') != string::npos) {
            numbers[j].push_back(stoi(str));
        } else {
            j++;
        }
    }
    
    long long columnResult;
    long long grandTotal = 0;
    for(int i = operators.size() - 1; i >= 0; i--){
        if(operators[i] == '+'){
            columnResult = 0;
            for(int j = 0; j < numbers[operators.size() - i - 1].size(); j++){
                columnResult += numbers[operators.size() - i - 1][j];
            }
        } else if (operators[i] == '*'){
            columnResult = 1;
            for(int j = 0; j < numbers[operators.size() - i - 1].size(); j++){
                columnResult *= numbers[operators.size() - i - 1][j];
            }
        }
        cout << "\nColumn " << i << ": " << columnResult;
        grandTotal += columnResult;
    }

    cout << "\nGrand Total: " << grandTotal;

    // // Part 1
    // vector<vector <int>> numbers;
    // for(int i = 0; i < operators.size(); i++){
    //     numbers.push_back({});
    // }

    // int column;
    // for(int i = 0; i < INPUTLINES - 1; i++){
    //     getline(file, input);
    //     column = 0;
    //     for(int j = 0; j < input.size(); ){
    //         if(input[j] != ' '){
    //             numbers[column].push_back(stoi(input.substr(j, input.find(" ", j))));
    //             column++;
    //             j = input.find(" ", j);
    //         } else {
    //             j++;
    //         }
    //     }
    // }



    // long long columnResult;
    // long long grandTotal = 0;
    // for(int i = 0; i < operators.size(); i++){
    //     if(operators[i] == '+'){
    //         columnResult = 0;
    //         for(int j = 0; j < numbers[i].size(); j++){
    //             columnResult += numbers[i][j];
    //         }
    //     } else if (operators[i] == '*'){
    //         columnResult = 1;
    //         for(int j = 0; j < numbers[i].size(); j++){
    //             columnResult *= numbers[i][j];
    //         }
    //     }
    //     cout << "\nColumn " << i << ": " << columnResult;
    //     grandTotal += columnResult;
    // }

    // cout << "\nGrand Total: " << grandTotal;
    
    file.close();
    return 0;
}