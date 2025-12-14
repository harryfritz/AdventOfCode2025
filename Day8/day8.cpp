/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day X - Part one and two
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

int main() {
  
    ifstream file;
    file.open("example.txt");
    string input;

    for(int i = 0; getline(file, input); i++){
        jBoxes.push_back({});
        
        int firstComma = input.find(",");
        int secondComma = input.find(",", input.find(",") + 1);
        jBoxes[i].push_back(stoi(input.substr(0, firstComma)));
        jBoxes[i].push_back(stoi(input.substr(firstComma + 1, secondComma - firstComma - 1)));
        jBoxes[i].push_back(stoi(input.substr(secondComma + 1, input.size() - secondComma)));
    }

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

    for(int j = 0; j < distances.size(); j++) cout << "\t" << j;
    for(int box1 = 0; box1 < jBoxes.size(); box1++){
        cout << "\n" << box1;
        for (int box2 = 0; box2 <= box1; box2++){
            cout << "\t" << distances[box1][box2];
        }
    }

    double maxDist = 0;
    for(int i = 0; i < distances.size(); i++){
        for(int j = 0; j <= i; j++){
            if(distances[i][j] > maxDist){
                maxDist = distances[i][j];
            }
        }
    }

    for(int count = 0; count < 10; count++){
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

        for(int i = 0; i < circuits.size(); i++){
            for(int j = 0; j < circuits[i].size(); j++){
                if(circuits[i][j] == iMin){
                    circuits[i].push_back(jMin);
                    iMin = 0;
                    jMin = 0;
                } else if(circuits[i][j] == jMin){
                    iMin = 0;
                    jMin = 0;
                    circuits[i].push_back(iMin);
                }            
            }
        }
        if(iMin != 0 && jMin != 0){
            circuits.push_back({iMin, jMin});
        }
        
        distances[iMin][jMin] = 0;
    }
        
    printCircuits();


    
    file.close();
    return 0;
}