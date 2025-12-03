/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 3 - Part one and two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define BANKSIZE 100

int main() {
  
    ifstream file;
    file.open("input.txt");
    if (!file) {
        cerr << "Unable to open file input.txt";
        exit(1);   
    }

    string input;
    int bank[BANKSIZE];
    int joltage;
    int maxJoltage;
    int totalJoltage = 0;

    while(getline(file, input)){
        cout << "\n" + input + " - ";

        for(int i = 0; i < BANKSIZE; i++){
            bank[i] = input[i] - 48;
        }
        
        joltage = 0;
        maxJoltage = 0;

        for(int i = 0; i < BANKSIZE - 1; i++){
            for(int j = i+1; j < BANKSIZE; j++){

                joltage = 10*bank[i] + bank[j];

                if(joltage > maxJoltage){
                    maxJoltage = joltage;
                }
            }
        }

        totalJoltage += maxJoltage;
        cout << "maxJoltage:" + to_string(maxJoltage) + " totalJoltage:" + to_string(totalJoltage);
    }

    file.close();
    return 0;
}