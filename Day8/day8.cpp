/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 8 - Part one and two
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

vector <vector <int>> jBoxes;

vector <vector <double>> distances;

vector <vector <int>> circuits;

double lineDistance(int box1, int box2){
    if(box1 == box2) return 0;
    
    int x = jBoxes[box2][0] - jBoxes[box1][0];
    int y = jBoxes[box2][1] - jBoxes[box1][1];
    int z = jBoxes[box2][2] - jBoxes[box1][2];

    return sqrt(pow(x,2) + pow(y,2) + pow(z,2)); 
}

void printCircuits(){
    for(int i = 0; i < circuits.size(); i++){
        cout << "\nc" << i << ": {";
        for(int j = 0; j < circuits[i].size(); j++){
            if(j == circuits[i].size() - 1){
                cout << circuits[i][j] << "}";
            } else {
                cout << circuits[i][j] << ",";
            }
        }
    }
}

bool vectorContains(vector <int> vec, int value){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] == value) return true;
    }
    return false;
}

void connectBoxes(int box1, int box2){
    int box1Circuit;
    int box2Circuit;
    for(int i = 0; i < circuits.size(); i++){
        if(vectorContains(circuits[i], box1)){
            box1Circuit = i;
        }
        if(vectorContains(circuits[i], box2)){
            box2Circuit = i;
        }
    }
    
    if(box1Circuit != box2Circuit){
        circuits[box1Circuit].insert(circuits[box1Circuit].end(), circuits[box2Circuit].begin(), circuits[box2Circuit].end());
    }

    for(int i = 0; i < circuits[box1Circuit].size(); i++){
        for(int j = i; j < circuits[box1Circuit].size(); j++){
            if(i != j) {
                distances[circuits[box1Circuit][i]][circuits[box1Circuit][j]] = 0;
                distances[circuits[box1Circuit][j]][circuits[box1Circuit][i]] = 0;
            }
        }
    }

    if(box1Circuit != box2Circuit){
        circuits.erase(circuits.begin() + box2Circuit);
    }
    
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    // Build jBoxes
    for(int i = 0; getline(file, input); i++){
        jBoxes.push_back({});
        
        int firstComma = input.find(",");
        int secondComma = input.find(",", input.find(",") + 1);
        jBoxes[i].push_back(stoi(input.substr(0, firstComma)));
        jBoxes[i].push_back(stoi(input.substr(firstComma + 1, secondComma - firstComma - 1)));
        jBoxes[i].push_back(stoi(input.substr(secondComma + 1, input.size() - secondComma)));
    }

    //Build circuits start
    for(int i = 0; i < jBoxes.size(); i++){
        circuits.push_back({i});
    }

    // Build distances
    for(int box1 = 0; box1 < jBoxes.size(); box1++){
        distances.push_back({});
        for (int box2 = 0; box2 < jBoxes.size(); box2++){
            if(box2 > box1) {
                distances[box1].push_back(0);
            } else {
                distances[box1].push_back(lineDistance(box1, box2));
            }
            
        }
    }

    //Print distances
    // for(int j = 0; j < distances.size(); j++) cout << "\t" << j;
    // for(int box1 = 0; box1 < jBoxes.size(); box1++){
    //     cout << "\n" << box1;
    //     for (int box2 = 0; box2 <= box1; box2++){
    //         cout << "\t" << distances[box1][box2];
    //     }
    // }

    //Determine Maximum Distance
    double maxDist = 0;
    for(int i = 0; i < distances.size(); i++){
        for(int j = 0; j <= i; j++){
            if(distances[i][j] > maxDist){
                maxDist = distances[i][j];
            }
        }
    }


    //Part 1 count = 1000
    for(int count = 0; circuits.size() > 2; count++){
        //Show number of iterations
        cout << "\nCount: " << count;
        
        //Determine Minimum Distance
        double minDist = maxDist;
        int iMin = 0, jMin = 0;
        for(int i = 0; i < distances.size(); i++){
            for(int j = 0; j <= i; j++){
                if(distances[i][j] < minDist && distances[i][j] > 0){
                    minDist = distances[i][j];
                    iMin = i;
                    jMin = j;
                }
            }
        }

        //Add box to circuit
        connectBoxes(iMin, jMin);
        
    }
        
    printCircuits();

    // //Print distances
    // cout << "\n";
    // for(int j = 0; j < distances.size(); j++) cout << "\t" << j;
    // for(int box1 = 0; box1 < jBoxes.size(); box1++){
    //     cout << "\n" << box1;
    //     for (int box2 = 0; box2 <= box1; box2++){
    //         cout << "\t" << distances[box1][box2];
    //     }
    // }

    //Determine Minimum Distance
    double minDist = maxDist;
    int iMin = 0, jMin = 0;
    for(int i = 0; i < distances.size(); i++){
        for(int j = 0; j <= i; j++){
            if(distances[i][j] < minDist && distances[i][j] > 0){
                minDist = distances[i][j];
                iMin = i;
                jMin = j;
            }
        }
    }
    cout << "\nLast connection:" << iMin << " and " << jMin << "  X Coord Multiply:" << jBoxes[iMin][0] * jBoxes[jMin][0];

    // Part 1
    // int threeLargest = 1;
    // for(int count = 0; count < 3; count++){
    //     int maxSize = 0;
    //     int iMaxSize = 0;
    //     for(int i = 0; i < circuits.size(); i++){
    //         if(circuits[i].size() > maxSize){
    //             maxSize = circuits[i].size();
    //             iMaxSize = i;
    //         }
    //     }
    //     threeLargest *= maxSize;
    //     circuits.erase(circuits.begin() + iMaxSize);
    // }

    // cout << "\nThree Largest Product: " << threeLargest;

    file.close();
    return 0;
}