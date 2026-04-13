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

    
    
    
    cout << "\n\n\n\n";
    // Puzzle 2
    file.open("input.txt");

    if (!file) {
        cerr << "Unable to open file input.txt";
        exit(1);   
    }

    arrowPos = 50;
    password = 0;
    rotation = 0;

    int column = 0;

    while (getline(file, input))
    {
        cout << "Pt2-" + input + "-New Pos:";
        
        
        
        if(input[0] == 'L'){
            rotation = -stoi(input.erase(0,1));
            while(arrowPos + rotation < 0){
                rotation += 100;
                password++;
            }
            if(arrowPos == 0){
                password--;
            }     

            arrowPos += rotation;
            if(arrowPos == 0){
                password++;
            }   
        } else if(input[0] == 'R'){
            rotation = stoi(input.erase(0,1));
            while(arrowPos + rotation > 99){
                rotation -= 100;
                if(arrowPos + rotation != 0) {
                    password++;
                }
            }

            arrowPos += rotation;
            if(arrowPos == 0){
                password++;
            }  
        } else {
            cerr << "Reading error!";
        }        
        
        cout << to_string(arrowPos) + " PWD: " + to_string(password);
        if(column <= 3) {
            column++;
            cout << "\t";
        } else {
            column = 0;
            cout << "\n";
        }

    }

    cout << "New Password: " + to_string(password);

    file.close();

    return 0;
}