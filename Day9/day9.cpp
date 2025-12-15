/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 9 - Part one and two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector <vector <long long>> coordinates;

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    cout << "\n";
    for(int i = 0; getline(file, input); i++){        
        coordinates.push_back({stoll(input.substr(0,input.find(","))),stoll(input.substr(input.find(",") + 1,input.size() - input.find(",")))});
    }
    
    long long maxArea = 0;
    for(int tile1 = 0; tile1 < coordinates.size(); tile1++){
        for(int tile2 = tile1; tile2 < coordinates.size(); tile2++){
            long long area = (1 + llabs(coordinates[tile1][0] - coordinates[tile2][0])) * (1 + llabs(coordinates[tile1][1] - coordinates[tile2][1]));
            if(area > maxArea){
                maxArea = area;
                cout << "\nTile1:" << tile1 << "\tTile2:" << tile2 << "\tArea:" << area << "\tMaxArea:" << maxArea << " **";
            } else {
                cout << "\nTile1:" << tile1 << "\tTile2:" << tile2 << "\tArea:" << area << "\tMaxArea:" << maxArea;
            }
        }
    }

    file.close();
    return 0;
}