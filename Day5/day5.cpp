/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 5 - Part one and two
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
    if (!file) {
        cerr << "Unable to open file input.txt";
        exit(1);   
    }

    string input;
    vector<vector <long long>> ranges;
    long long id;
    bool isFresh;
    long long freshCount = 0;
    

    for(int i = 0; getline(file, input); i++){
        if(input == "") break;
        ranges.push_back({stoll(input.substr(0, input.find("-"))), stoll(input.substr(input.find("-") + 1, input.size() - input.find("-")))});
    }    
    
    while(getline(file, input)){
        cout << "\n" + input;

        isFresh = false;
        id = stoll(input);
        for(int i = 0; i < ranges.size(); i++){
            if(id >= ranges[i][0] && id <= ranges[i][1]){
                isFresh = true;
                break;
            }
        }

        if(isFresh){
            cout << " fresh";
            freshCount++;
        } else {
            cout << " spoiled";
        }

    }

    cout << "\nFresh Count: " << freshCount;
    
    file.close();
    return 0;
}