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

using namespace std;


int main() {
  
    ifstream file;
    file.open("input.txt");
    if (!file) {
        cerr << "Unable to open file input.txt";
        exit(1);   
    }

    string input;

    while(getline(file, input)){
        cout << "\n" + input;
    }
    
    
    file.close();
    return 0;
}