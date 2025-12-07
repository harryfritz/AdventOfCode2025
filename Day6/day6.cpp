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

    std::vector<char> operators;
    for(int i = 0; i < input.size() - 1; i++){
        if(input[i] == '+' || input[i] == '*'){
            operators.push_back(input[i]);
        }
    }

    file.close();
    file.open(fileName);

    

    vector<vector <int>> numbers;
    for(int i = 0; i < operators.size(); i++){
        numbers.push_back({});
    }

    int column;
    for(int i = 0; i < INPUTLINES - 1; i++){
        getline(file, input);
        column = 0;
        for(int j = 0; j < input.size(); ){
            if(input[j] != ' '){
                numbers[column].push_back(stoi(input.substr(j, input.find(" ", j))));
                column++;
                j = input.find(" ", j);
            } else {
                j++;
            }
        }
    }

    long long columnResult;
    long long grandTotal = 0;
    for(int i = 0; i < operators.size(); i++){
        if(operators[i] == '+'){
            columnResult = 0;
            for(int j = 0; j < numbers[i].size(); j++){
                columnResult += numbers[i][j];
            }
        } else if (operators[i] == '*'){
            columnResult = 1;
            for(int j = 0; j < numbers[i].size(); j++){
                columnResult *= numbers[i][j];
            }
        }
        cout << "\nColumn " << i << ": " << columnResult;
        grandTotal += columnResult;
    }

    cout << "\nGrand Total: " << grandTotal;
    
    file.close();
    return 0;
}