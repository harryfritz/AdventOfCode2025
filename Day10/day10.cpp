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

using namespace std; 

vector <vector <char> > indicators;

vector <vector <vector <int> > > buttons;

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

        string button = input.substr(input.find("]"), input.find("{") - 1);
        buttons.push_back({});
        for(char c : button){
            if(c == '('){
                buttons[i].push_back({});
            }
        }
    }
    
    
    file.close();
    return 0;
}