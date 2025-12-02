/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 1 - Puzzle 1
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

    int arrowPos = 50;
    int password = 0;
    
    string input;
    int rotation = 0;
    while (getline(file, input))
    {
        cout << input + " - New Arrow Position: ";
        
        
        
        if(input[0] == 'L'){
            rotation = -stoi(input.erase(0,1));
            while(arrowPos + rotation < 0){
                rotation += 100;
            }        
        } else if(input[0] == 'R'){
            rotation = stoi(input.erase(0,1));
            while(arrowPos + rotation > 99){
                rotation -= 100;
            }
        } else {
            cerr << "Reading error!";
        }        
        arrowPos += rotation;

        if(arrowPos == 0){
            password++;
        }
        
        cout << to_string(arrowPos) + "\n";

    }

    cout << "Password: " + to_string(password);


    file.close();

    return 0;
}