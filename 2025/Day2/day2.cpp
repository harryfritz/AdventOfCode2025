/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 2 - Part one and two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int digits(long long id){
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

long long isIDvalid_partTwo(long long id){
    //Checks if ID is valid.
    //If yes, return id
    //If no, return 0
    
    int numDig = digits(id);

    long long uni = 1;
    long long dec = 10;
    long long step;

    int lastDig = -1;
    for(int j = 1; j <= numDig/2; j++){
        uni = 1;
        dec = 10;
        for(int i = 1; i < j; i++){
            dec *= 10;
        }
        step = dec;
        for(int i = 1; i <= numDig/j && numDig%j == 0; i++) {
            
            if(i > 1){
                if(lastDig != (id % dec) / uni){
                    break;
                }

                if(i == numDig/j){
                    return id;
                }
            }
            lastDig =  (id % dec) / uni;

            uni = dec;
            dec *= step;
        }
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
    long long oldAnswer = 0;

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
            answer += isIDvalid_partTwo(id);
            if(answer != oldAnswer){
                oldAnswer = answer;
                cout << "\ninvalid id:" + to_string(id) + " new answer:" + to_string(answer);
            } 
        }

        nextChar = commaPos + 1;
        if(commaPos == std::string::npos){
            break;
        }
        commaPos = input.find(",",nextChar);

    }

    file.close();
    return 0;
}