/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 2 - 
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int isIDvalid(int id){
    //Checks if ID is valid.
    //If yes, return id
    //If no, return 0

    return 0;
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    if (!file) {
        cerr << "Unable to open file input.txt";
        exit(1);   
    }

    long int answer = 0;

    string input;
    getline(file, input);

    int nextChar = 0;
    int commaPos = input.find(",",nextChar);
    string nextRange;
    long int rangeStart, rangeEnd;
    while(true){
        
        nextRange = input.substr(nextChar,commaPos-nextChar);
        cout << "(" + to_string(commaPos) + ") " + nextRange + " ";
        
        rangeStart = stoll(nextRange.substr(0, nextRange.find("-")));
        rangeEnd = stoll(nextRange.substr(nextRange.find("-") + 1, nextRange.size() - nextRange.find("-")));
        for(long int id = rangeStart; id <= rangeEnd; id++){
            answer += isIDvalid(id);
        }
        cout << "new answer: " + to_string(answer) + "\n";

        nextChar = commaPos + 1;
        if(commaPos == std::string::npos){
            break;
        }
        commaPos = input.find(",",nextChar);
    }

    file.close();
    return 0;
}