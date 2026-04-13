/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 4 - Part one and two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define GRIDWIDTH 138
#define GRIDHEIGHT 138

int main() {
  
    ifstream file;
    file.open("input.txt");
    if (!file) {
        cerr << "Unable to open file input.txt";
        exit(1);   
    }

    string input;
    int goodRolls;
    int adjacentRolls;
    int totalGoodRolls = 0;
    int prevTotalGoodRolls = -1;
    char paperGrid[GRIDHEIGHT+2][GRIDWIDTH+2];
    
    // Part 2
    for(int j = 0; j < GRIDWIDTH + 2; j++) paperGrid[0][j] = 'b';
    for(int i = 0; i < GRIDHEIGHT + 2; i++) paperGrid[i][0] = 'b';
    for(int j = 0; j < GRIDWIDTH + 2; j++) paperGrid[GRIDHEIGHT+1][j] = 'b';
    for(int i = 0; i < GRIDHEIGHT + 2; i++) paperGrid[i][GRIDWIDTH+1] = 'b';

    for(int i = 1; i < GRIDHEIGHT + 1 && getline(file, input); i++) {
        for(int j = 1; j < GRIDWIDTH + 1; j++){
            paperGrid[i][j] = input[j-1];
        }
    }

    while(totalGoodRolls > prevTotalGoodRolls){
        
        if(totalGoodRolls > prevTotalGoodRolls){
            prevTotalGoodRolls = totalGoodRolls;
        }
        
        for(int i = 1; i < GRIDHEIGHT + 1; i++) {
            cout << "\n";
            goodRolls = 0;
            for(int j = 1;j < GRIDWIDTH + 1; j++){
                adjacentRolls = 0;

                if(paperGrid[i][j] == '@'){
                    if(paperGrid[i-1][j-1] == '@' || paperGrid[i-1][j-1] == 'x') adjacentRolls++;
                    if(paperGrid[i-1][j] == '@' || paperGrid[i-1][j] == 'x') adjacentRolls++;
                    if(paperGrid[i-1][j+1] == '@' || paperGrid[i-1][j+1] == 'x') adjacentRolls++;
                    if(paperGrid[i][j-1] == '@' || paperGrid[i][j-1] == 'x') adjacentRolls++;
                    if(paperGrid[i][j+1] == '@' || paperGrid[i][j+1] == 'x') adjacentRolls++;
                    if(paperGrid[i+1][j-1] == '@' || paperGrid[i+1][j-1] == 'x') adjacentRolls++;
                    if(paperGrid[i+1][j] == '@' || paperGrid[i+1][j] == 'x') adjacentRolls++;
                    if(paperGrid[i+1][j+1] == '@' || paperGrid[i+1][j+1] == 'x') adjacentRolls++;

                    if(adjacentRolls < 4) {
                        paperGrid[i][j] = 'x';
                        goodRolls++;     
                    }
                }
                
                cout << paperGrid[i][j];
            }
            cout << " " << goodRolls;
            totalGoodRolls += goodRolls;
        }

        cout << "\nTotal Good Rolls: " << totalGoodRolls;

        for(int i = 1; i < GRIDHEIGHT + 1; i++) {
            for(int j = 1;j < GRIDWIDTH + 1; j++){
                if(paperGrid[i][j] == 'x'){
                    paperGrid[i][j] = '.';
                }
            }
        }

    }

    

    
    
    file.close();
    return 0;

    // string input;
    // int goodRolls;
    // int adjacentRolls;
    // int totalGoodRolls = 0;
    // char paperGrid[GRIDHEIGHT+2][GRIDWIDTH+2];
    
    // // Part 1
    // for(int j = 0; j < GRIDWIDTH + 2; j++) paperGrid[0][j] = 'b';
    // for(int i = 0; i < GRIDHEIGHT + 2; i++) paperGrid[i][0] = 'b';
    // for(int j = 0; j < GRIDWIDTH + 2; j++) paperGrid[GRIDHEIGHT+1][j] = 'b';
    // for(int i = 0; i < GRIDHEIGHT + 2; i++) paperGrid[i][GRIDWIDTH+1] = 'b';

    // for(int i = 1; i < GRIDHEIGHT + 1 && getline(file, input); i++) {
    //     for(int j = 1; j < GRIDWIDTH + 1; j++){
    //         paperGrid[i][j] = input[j-1];
    //     }
    // }

    // for(int i = 1; i < GRIDHEIGHT + 1; i++) {
    //     cout << "\n";
    //     goodRolls = 0;
    //     for(int j = 1;j < GRIDWIDTH + 1; j++){
    //         adjacentRolls = 0;

    //         if(paperGrid[i][j] == '@'){
    //             if(paperGrid[i-1][j-1] == '@' || paperGrid[i-1][j-1] == 'x') adjacentRolls++;
    //             if(paperGrid[i-1][j] == '@' || paperGrid[i-1][j] == 'x') adjacentRolls++;
    //             if(paperGrid[i-1][j+1] == '@' || paperGrid[i-1][j+1] == 'x') adjacentRolls++;
    //             if(paperGrid[i][j-1] == '@' || paperGrid[i][j-1] == 'x') adjacentRolls++;
    //             if(paperGrid[i][j+1] == '@' || paperGrid[i][j+1] == 'x') adjacentRolls++;
    //             if(paperGrid[i+1][j-1] == '@' || paperGrid[i+1][j-1] == 'x') adjacentRolls++;
    //             if(paperGrid[i+1][j] == '@' || paperGrid[i+1][j] == 'x') adjacentRolls++;
    //             if(paperGrid[i+1][j+1] == '@' || paperGrid[i+1][j+1] == 'x') adjacentRolls++;

    //             if(adjacentRolls < 4) {
    //                 paperGrid[i][j] = 'x';
    //                 goodRolls++;     
    //             }
    //         }
            
    //         cout << paperGrid[i][j];
    //     }
    //     cout << " " << goodRolls;
    //     totalGoodRolls += goodRolls;
    // }

    // cout << "\nTotal Good Rolls: " << totalGoodRolls; 

    // file.close();
    // return 0;
}