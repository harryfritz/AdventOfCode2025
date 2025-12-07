/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 7 - Part one and two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  
    ifstream file;
    file.open("input.txt");

    string input;
    vector<vector <char>> manifold;
    for(int i = 0; getline(file, input); i++){
        manifold.push_back({});
        for(int j = 0; j < input.size(); j++){
            manifold[i].push_back(input[j]);
        }
    }

    int totalSplits = 0;
    for(int i = 0; i < manifold.size(); i++){
        cout << "\n";
        for(int j = 0; j < manifold[i].size(); j++){
            if(i == 0) {
                if(manifold[i][j] == 'S') {
                    manifold[i+1][j] = '|';
                }
            } else if (i != 1) {
                if(manifold[i][j] == '^' && manifold[i-1][j] == '|'){
                    manifold[i][j-1] = '|';
                    manifold[i][j+1] = '|';
                    totalSplits++;
                } else if(manifold[i-1][j] == '|') {
                    manifold[i][j] = '|';
                }
            }
            cout << manifold[i][j];
        }
    }

    cout << "\nTotal Splits: " << totalSplits;
    
    file.close();
    return 0;
}