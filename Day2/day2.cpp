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

int digits(long int id){
    //Tells how many digits an id has
    int digits = 0;
    while (id) {
        id /= 10;
        digits++;
    }
    return digits;
}


long long isIDvalid(long long id){
    //Checks if ID is valid.
    //If yes, return id
    //If no, return 0
        
    int numDig = digits(id);
    if(numDig%2 != 0) return 0; //exclude all IDs with odd number of digits
    
    int lowerHalf, higherHalf;
    int splitter = 1;
    for(int i = 0; i < numDig/2; i++){
        splitter *= 10;
    }
    lowerHalf = id % splitter;
    higherHalf = id / splitter; 

    if(lowerHalf == higherHalf){
        return id;
    }

    return 0;
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    if (!file) {
        cerr << "Unable to open file input.txt";
        exit(1);   
    }

    long long answer = 0;

    string input;
    getline(file, input);

    int nextChar = 0;
    int commaPos = input.find(",",nextChar);
    string nextRange;
    long long rangeStart, rangeEnd;
    
    while(true){
        
        nextRange = input.substr(nextChar,commaPos-nextChar);
        cout << "\n(" + to_string(commaPos) + ") " + nextRange + " ";
        
        rangeStart = stoll(nextRange.substr(0, nextRange.find("-")));
        rangeEnd = stoll(nextRange.substr(nextRange.find("-") + 1, nextRange.size() - nextRange.find("-")));
        for(long long id = rangeStart; id <= rangeEnd; id++){
            answer += isIDvalid(id);
            if(isIDvalid(id) != 0){
                cout << "\ninvalid id:" + to_string(id) + " new answer:" + to_string(answer);
            } 
        }
        //cout << "new answer: " + to_string(answer) + "\n";

        nextChar = commaPos + 1;
        if(commaPos == std::string::npos){
            break;
        }
        commaPos = input.find(",",nextChar);

    }

    file.close();
    return 0;
}