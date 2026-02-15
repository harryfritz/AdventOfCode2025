/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 10 - Part one and two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std; 

vector <vector <char> > indicators;

vector <vector <int> > buttons;

vector <int> buttonCombinations;



int intPow(int base, int exponent){
    int result = 1;
    for(int i = 0; i < exponent; i++){
        result *= base;
    }
    return result;
}

bool isButtonSeqCorrect(int machine, int buttonResult){    
    for(int i = 0; i < indicators[machine].size(); i++){
        int digit = ((buttonResult / intPow(10,i)) % 10);
        if(digit % 2 == 0 && indicators[machine][i] == '#' || digit % 2 == 1 && indicators[machine][i] == '.') {
            return false;
        }
    }
    return true;
}

void combineButtons(int machine, int k){
    
}

int main() {
  
    ifstream file;
    file.open("example.txt");
    string input;
    
    for(int i = 0; getline(file, input); i++){
        cout << "\n" + input;
        
        string indicator = input.substr(1, input.find("]") - 1);
        indicators.push_back({});
        for(char c : indicator){
            indicators[i].push_back(c);
        }

        string button = input.substr(input.find("]") + 1, input.find("{") - input.find("]") - 1);
        buttons.push_back({});
        int j = -1;
        for(int c = 0; c < button.size(); c++){
            if(button[c] == '('){
                buttons[i].push_back({});
                j++;
            }
            if(button[c] >= '0' && button[c] <= '9'){
                buttons[i][j] += intPow(10,button[c] - 48);
            }
        }
    }

    
    
    
    int machine = 0;
    for(int pushes = 1; pushes <= indicators[machine].size(); pushes++){
        

        
        
        if(isButtonSeqCorrect(machine, 1));
    }

    
    
    file.close();
    return 0;
}