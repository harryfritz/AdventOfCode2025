/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 7 - Part one and two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector <int>> manifold;


vector<vector <long long>> manifold1;
vector<vector <int>> manifold2;

vector <int> manifoldLine;
int rowSize = 0;
int columnSize = 0;

long long timelines = 0;

void beamTrack(int row, int column){
    for(int i = row + 1; i < manifold.size(); i++){
        if(i == manifold.size() - 1){
            timelines++;
            cout << "\nBeam Timelines: " << timelines;
        } else if(manifold[i][column] == '^'){
            beamTrack(i, column - 1);
            beamTrack(i, column + 1);
            break;
        }
 
    }
    
}

void beamTrackLine(int row, int column){
    
    for(int i = row + 1; i < columnSize; i++){
        if(i == columnSize - 1){
            timelines++;
            cout << "\nBeam Timelines: " << timelines;
        } else if(manifoldLine[i*rowSize + column] == '^'){
            beamTrackLine(i, column - 1);
            beamTrackLine(i, column + 1);
            break;
        }
 
    }
    
}

void printMatrix (vector<vector <long long>> matrix) {
    for(int i = 0; i < matrix.size(); i++){
        cout << "\n";
        for(int j = 0; j < matrix[i].size(); j++){
            if(matrix[i][j] >= 0){
                cout << "+" << matrix[i][j];
            } else {
                cout << "-" << -1*matrix[i][j];
            }
            
            // cout << (char)matrix[i][j];
        }
    }
} 

        
int main() {
  
    ifstream file;
    string fileName = "input.txt";
    file.open(fileName);
    string input;

    for(int i = 0; getline(file, input); i++){
        manifold1.push_back({});
        for(int j = 0; j < input.size(); j++){
            if(input[j] == 'S'){
                manifold1[i].push_back(-2);
            } else if(input[j] == '^'){
                manifold1[i].push_back(-1);
            } else if(input[j] == '.'){
                manifold1[i].push_back(0);
            }
        }
    }

    printMatrix(manifold1);

    file.close();
    file.open(fileName);
        for(int i = 0; getline(file, input); i++){
            manifold2.push_back({});
            for(int j = 0; j < input.size(); j++){
                 manifold2[i].push_back(input[j]);
            }
        }

    int totalSplits1 = 0;
    int totalSplits2 = 0;
    cout << "\n\n\n";
    for(int j = 0; j < manifold1[0].size(); j++){
        if(manifold1[0][j] >= 0){
                cout << "+" << manifold1[0][j];
            } else {
                cout << "-" << -1*manifold1[0][j];
            }
    }
    for(int i = 1; i < manifold1.size(); i++){
        cout << "\n";
        for(int j = 0; j < manifold1[i].size(); j++){            
            if(manifold1[i][j] == -1 && manifold1[i-1][j] > 0){
                manifold1[i][j-1] += manifold1[i-1][j];
                manifold1[i][j+1] += manifold1[i-1][j];
                
                totalSplits1++;
            } else if(manifold1[i-1][j] > 0) {
                manifold1[i][j] += manifold1[i-1][j];
            } else if(manifold1[i-1][j] == -2) {
                manifold1[i][j] = 1;
            }

            if(manifold2[i][j] == '^' && manifold2[i-1][j] == '|'){
                manifold2[i][j-1] = '|';
                manifold2[i][j+1] = '|';
                totalSplits2++;
            } else if(manifold2[i-1][j] == '|') {
                manifold2[i][j] = '|';
            } else if(manifold2[i-1][j] == 'S') {
                manifold2[i][j] = '|';
            } 
            cout << (char)manifold2[i][j];

            if(totalSplits1 != totalSplits2){
                cout << "\n\n*****\nWRONG LINE: totalSplits1:" << totalSplits1 << " totalSplits2:" << totalSplits2
                     << " i:" << i << " j:" << j;
                break;
            }



        }
        for(int j = 0; j < manifold1[i].size(); j++){
            if(manifold1[i][j] >= 0){
                cout << "+" << manifold1[i][j];
            } else {
                cout << "-" << -1*manifold1[i][j];
            }
        } 
    }

    timelines = 0;
    for(int j = 0, i = manifold1.size() - 1; j < manifold1[i].size(); j++){
        timelines += manifold1[i][j];
    }

    cout << "\nTotal Splits1: " << totalSplits1;
    cout << "\nTotal Splits2: " << totalSplits2;
    cout << "\nTotal Timelines: " << timelines;



    // Part 1
    // file.close();
    // file.open(fileName);
    //     for(int i = 0; getline(file, input); i++){
    //         manifold2.push_back({});
    //         for(int j = 0; j < input.size(); j++){
    //              manifold2[i].push_back(input[j]);
    //         }
    //     }
    // int totalSplits2 = 0;
    // for(int i = 1; i < manifold2.size(); i++){
    //     cout << "\n";
    //     for(int j = 0; j < manifold2[i].size(); j++){
    //         if(manifold2[i][j] == '^' && manifold2[i-1][j] == '|'){
    //             manifold2[i][j-1] = '|';
    //             manifold2[i][j+1] = '|';
    //             totalSplits2++;
    //         } else if(manifold2[i-1][j] == '|') {
    //             manifold2[i][j] = '|';
    //         } else if(manifold2[i-1][j] == 'S') {
    //             manifold2[i][j] = '|';
    //         } 
    //         cout << manifold2[i][j];
    //     }
    // }

    // cout << "\nTotal Splits: " << totalSplits2;   



    // for(int i = 0; getline(file, input); i++){
    //     columnSize++;
    //     for(int j = 0; j < input.size(); j++){
    //         manifoldLine.push_back(input[j]);
    //         if(i == 0) rowSize++;
    //     }
    // }

    // cout << "\nRowSize:" << rowSize << " Column Size: " << columnSize;

    // for(int j = 0; j < rowSize; j++){
    //     if(manifoldLine[j] == 'S'){
    //         beamTrackLine(0, j);
    //     }
    // }


    // // for(int j = 0; j < manifold[0].size(); j++){
    // //     if(manifold[0][j] == 'S'){
    // //         beamTrack(0, j);
    // //     }
    // // }
    
    

    // // Part 2 using DFS - Failed, takes too long
    // for(int i = 0; i < manifold.size(); i++){
    //     for(int j = 0; j < manifold[i].size(); j++){
    //         if(manifold[i][j] == '^'){
    //             graph.push_back({});
    //             manifold[i][j] = graph.size() - 1;
    //         } else if(i == manifold.size() - 1){
    //             graph.push_back({-1});
    //             manifold[i][j] = graph.size() - 1;
    //         } else{
    //             if(manifold[i][j] == '.'){
    //                 manifold[i][j] = -1;
    //             } else if(manifold[i][j] == 'S'){
    //                 manifold[i][j] = -2;
    //             }
    //         }
    //     }
    // }
    // printMatrix(manifold);

    // int nodeCount = 0;
    // for(int i = 0; i < manifold.size(); i++){
    //     for(int j = 0; j < manifold[i].size(); j++){
    //         if(manifold[i][j] >= 0 && i < manifold.size() - 1){
    //             for(int i2 = i + 1; i2 < manifold.size(); i2++){
    //                 if(manifold[i2][j-1] >= 0){
    //                     graph[nodeCount].push_back(manifold[i2][j-1]);
    //                     break;
    //                 }
    //             }
    //             for(int i2 = i + 1; i2 < manifold.size(); i2++){
    //                 if(manifold[i2][j+1] >= 0){
    //                     graph[nodeCount].push_back(manifold[i2][j+1]);
    //                     break;
    //                 }
    //             }
    //             nodeCount++;
    //         }
    //     }
    // }
        
    // printGraph(graph);

    // nodeScan(graph[0]);

    // cout << "\nTimelines: " << timelines;

    // // Part 2 - Failed
    // int totalSplits = 0;
    // int timelines = 0;
    // for(int i = 0; i < manifold.size(); i++){
    //     cout << "\n";
    //     for(int j = 0; j < manifold[i].size() && i > 0; j++){
    //         if(manifold[i-1][j] == '|' || manifold[i-1][j] == 'S'){
    //             if(manifold[i][j] == '^'){
                    
    //                 manifold[i][j-1] = '|';
    //                 manifold[i][j+1] = '|';

    //                 // if(timelines%5 == 0){
    //                 //     manifold[i][j-1] = '|';
    //                 // } else {
    //                 //     manifold[i][j+1] = '|';
    //                 // }

    //                 totalSplits++;
    //                 timelines +=2;
    //             } else {
    //                 manifold[i][j] = '|';
    //             }
    //         }
    //     }
    //     for(int j = 0; j < manifold[i].size(); j++) cout << manifold[i][j];
    // }

    // cout << "\nTotal Splits: " << totalSplits;
    // cout << "\nTotal Timelines: " << timelines;

    // // Part 1
    // int totalSplits = 0;
    // for(int i = 0; i < manifold.size(); i++){
    //     cout << "\n";
    //     for(int j = 0; j < manifold[i].size(); j++){
    //         if(i == 0) {
    //             if(manifold[i][j] == 'S') {
    //                 manifold[i+1][j] = '|';
    //             }
    //         } else if (i != 1) {
    //             if(manifold[i][j] == '^' && manifold[i-1][j] == '|'){
    //                 manifold[i][j-1] = '|';
    //                 manifold[i][j+1] = '|';
    //                 totalSplits++;
    //             } else if(manifold[i-1][j] == '|') {
    //                 manifold[i][j] = '|';
    //             }
    //         }
    //         cout << manifold[i][j];
    //     }
    // }

    // cout << "\nTotal Splits: " << totalSplits;
    
    file.close();
    return 0;
}