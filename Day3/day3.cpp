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
    long long bank[BANKSIZE];
    long long maxJoltage;
    long long totalJoltage = 0;

    int pos;
    int posMax;
    long long multiplier;

    // Part 2 - Optimized
    while(getline(file, input)){
        cout << "\n" + input + " - ";

        for(int i = 0; i < BANKSIZE; i++){
            bank[i] = input[i] - 48;
        }

        multiplier = 100000000000;
        pos = 0;
        posMax = -1;
        maxJoltage = 0;
        for(int i = 0; i < 12; i++){
            pos = posMax + 1;
            posMax = pos;
            while(pos < BANKSIZE + i - 11){
                if(bank[pos] > bank[posMax]){
                    posMax = pos;
                }
                pos++;
            }

            maxJoltage += multiplier * bank[posMax];
            multiplier /= 10;
        }   

        totalJoltage += maxJoltage;
        cout << "maxJoltage:" + to_string(maxJoltage) + " totalJoltage:" + to_string(totalJoltage);
    }

    file.close();
    return 0;

    // // Part 1 - Optimized
    // while(getline(file, input)){
    //     cout << "\n" + input + " - ";

    //     for(int i = 0; i < BANKSIZE; i++){
    //         bank[i] = input[i] - 48;
    //     }

    //     multiplier = 10;
    //     pos = 0;
    //     posMax = -1;
    //     maxJoltage = 0;
    //     for(int i = 0; i < 2; i++){
    //         pos = posMax + 1;
    //         posMax = pos;
    //         while(pos < BANKSIZE + i - 1){
    //             if(bank[pos] > bank[posMax]){
    //                 posMax = pos;
    //             }
    //             pos++;
    //         }

    //         maxJoltage += multiplier * bank[posMax];
    //         multiplier /= 10;
    //     }   

    //     totalJoltage += maxJoltage;
    //     cout << "maxJoltage:" + to_string(maxJoltage) + " totalJoltage:" + to_string(totalJoltage);
    // }

    // file.close();
    // return 0;

    // // Part 2 - Brute force - Takes too long
    // while(getline(file, input)){
    //     cout << "\n" + input + " - ";

    //     for(int i = 0; i < BANKSIZE; i++){
    //         bank[i] = input[i] - 48;
    //     }
        
    //     joltage = 0;
    //     maxJoltage = 0;

    //     for(int a11 = 0; a11 < BANKSIZE - 11; a11++){
    //         for(int a10 = a11+1; a10 < BANKSIZE - 10; a10++){
    //             for(int a9 = a10+1; a9 < BANKSIZE - 9; a9++){
    //                 for(int a8 = a9+1; a8 < BANKSIZE - 8; a8++){
    //                     for(int a7 = a8+1; a7 < BANKSIZE - 7; a7++){
    //                         for(int a6 = a7+1; a6 < BANKSIZE - 6; a6++){
    //                             for(int a5 = a6+1; a5 < BANKSIZE - 5; a5++){
    //                                 for(int a4 = a5+1; a4 < BANKSIZE - 4; a4++){
    //                                     for(int a3 = a4+1; a3 < BANKSIZE - 3; a3++){
    //                                         for(int a2 = a3+1; a2 < BANKSIZE - 2; a2++){
    //                                             for(int a1 = a2+1; a1 < BANKSIZE - 1; a1++){
    //                                                 for(int a0 = a1+1; a0 < BANKSIZE; a0++){
                  
    //                 joltage =       100000000000*bank[a11] + 10000000000*bank[a10] + 1000000000*bank[a9] + 
    //                                 100000000*bank[a8] + 10000000*bank[a7] + 1000000*bank[a6] + 
    //                                 100000*bank[a5] + 10000*bank[a4] + 1000*bank[a3] + 
    //                                 100*bank[a2] + 10*bank[a1] + bank[a0];

    //                 if(joltage > maxJoltage){
    //                     maxJoltage = joltage;
    //                 }

    //                                                 }
    //                                             }
    //                                         }
    //                                     }
    //                                 }
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }

    //     totalJoltage += maxJoltage;
    //     cout << "maxJoltage:" + to_string(maxJoltage) + " totalJoltage:" + to_string(totalJoltage);
    // }

    // file.close();
    // return 0;
    
    // // Part 1 - Solved
    // while(getline(file, input)){
    //     cout << "\n" + input + " - ";

    //     for(int i = 0; i < BANKSIZE; i++){
    //         bank[i] = input[i] - 48;
    //     }
        
    //     joltage = 0;
    //     maxJoltage = 0;

    //     for(int i = 0; i < BANKSIZE - 1; i++){
    //         for(int j = i+1; j < BANKSIZE; j++){

    //             joltage = 10*bank[i] + bank[j];

    //             if(joltage > maxJoltage){
    //                 maxJoltage = joltage;
    //             }
    //         }
    //     }

    //     totalJoltage += maxJoltage;
    //     cout << "maxJoltage:" + to_string(maxJoltage) + " totalJoltage:" + to_string(totalJoltage);
    // }

    // file.close();
    // return 0;
}