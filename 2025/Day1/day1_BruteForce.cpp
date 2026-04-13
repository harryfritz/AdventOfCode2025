/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 1 - Puzzles 1 and 2
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
    
    
    // Puzzle 1
    file.open("input.txt");

    if (!file) {
        cerr << "Unable to open file input.txt";
        exit(1);   
    }

    int arrowPos = 50;
    int password = 0;
    int steps;
    
    string input;
    while (getline(file, input))
    {
        cout << input + " - New Arrow Position: ";
        
        steps = 0;
        if(input[0] == 'L'){
            steps = stoi(input.erase(0,1));
            while(steps > 0){
                arrowPos--;
                if(arrowPos < 0){
                    arrowPos = 99;
                }
                steps--;
            }
            if(arrowPos == 0){
                password++;
            }   
        } else if(input[0] == 'R'){
            steps = stoi(input.erase(0,1));
            while(steps > 0){
                arrowPos++;
                if(arrowPos > 99){
                    arrowPos = 0;
                }
                steps--;
            }
            if(arrowPos == 0){
                password++;
            } 
        } else {
            cerr << "Reading error!";
        }        
        
        cout << to_string(arrowPos) + "\n";

    }

    cout << "Password: " + to_string(password);

    file.close();

    
    
    
    // Puzzle 2
    file.open("input.txt");

    if (!file) {
        cerr << "Unable to open file input.txt";
        exit(1);   
    }

    arrowPos = 50;
    password = 0;
    
    while (getline(file, input))
    {
        cout << input + " - New Arrow Position: ";
        
        steps = 0;
        if(input[0] == 'L'){
            steps = stoi(input.erase(0,1));
            while(steps > 0){
                arrowPos--;
                if(arrowPos == 0){
                    password++;
                }
                if(arrowPos < 0){
                    arrowPos = 99;
                }
                steps--;
            }
        } else if(input[0] == 'R'){
            steps = stoi(input.erase(0,1));
            while(steps > 0){
                arrowPos++;
                if(arrowPos > 99){
                    arrowPos = 0;
                }
                if(arrowPos == 0){
                    password++;
                }
                steps--;
            }
        } else {
            cerr << "Reading error!";
        }        
        
        cout << to_string(arrowPos) + "\n";

    }

    cout << "Password: " + to_string(password);

    file.close();

    return 0;
}