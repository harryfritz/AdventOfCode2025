/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 9 - Part one and two
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

vector <vector <int>> redTiles;
vector <vector <int>> compRedTiles;

vector <int> rows;
vector <int> columns;
vector <vector <char>> compTileMap;

void compVoidTilesFilling(int firstTileX, int firstTileY){
    
    compTileMap[firstTileX][firstTileY] = '.';
    
    vector <vector <int>> tilesToFill;
    tilesToFill.push_back({firstTileX, firstTileY});
    int centerTileX;
    int centerTileY;
    
    while(tilesToFill.size() > 0){
        centerTileX = tilesToFill[0][0];
        centerTileY = tilesToFill[0][1];
        
        if(centerTileX - 1 >= 0){
            if(compTileMap[centerTileY][centerTileX - 1] == 'x'){
                compTileMap[centerTileY][centerTileX - 1] = '.';
                tilesToFill.push_back({centerTileX - 1, centerTileY});
            }
        }
        
        if(centerTileX + 1 < compTileMap[centerTileY].size()){
            if(compTileMap[centerTileY][centerTileX + 1] == 'x'){
                compTileMap[centerTileY][centerTileX + 1] = '.';
                tilesToFill.push_back({centerTileX + 1, centerTileY});
            }
        }
        
        if(centerTileY - 1 >= 0){
            if(compTileMap[centerTileY - 1][centerTileX] == 'x'){
                compTileMap[centerTileY - 1][centerTileX] = '.';
                tilesToFill.push_back({centerTileX, centerTileY - 1});
            }
        }
        
        if(centerTileY + 1 < compTileMap.size()){
            if(compTileMap[centerTileY + 1][centerTileX] == 'x'){
                compTileMap[centerTileY + 1][centerTileX] = '.';
                tilesToFill.push_back({centerTileX, centerTileY + 1});
            }
        }
        

        tilesToFill.erase(tilesToFill.begin());       

    }
    

}

bool isAreaValid(int tile1, int tile2){
    int x1, x2, y1, y2;
    if(compRedTiles[tile1][0] <= compRedTiles[tile2][0]){
        x1 = compRedTiles[tile1][0];
        x2 = compRedTiles[tile2][0];
    } else {
        x1 = compRedTiles[tile2][0];
        x2 = compRedTiles[tile1][0];
    }
    if(compRedTiles[tile1][1] <= compRedTiles[tile2][1]){
        y1 = compRedTiles[tile1][1];
        y2 = compRedTiles[tile2][1];
    } else {
        y1 = compRedTiles[tile2][1];
        y2 = compRedTiles[tile1][1];
    }

    for(int i = y1; i <= y2; i++){
        for(int j = x1; j <= x2; j++){
            if(compTileMap[i][j] == '.'){
                return false;
            }
        }
    }

    return true;

}

int main() {  
    ifstream file;
    file.open("input.txt");
    string input;

    cout << "\n";
    int firstX, firstY;
    for(int i = 0; getline(file, input); i++){        
        if(i == 0){
            firstX = stoi(input.substr(0,input.find(",")));
            firstY = stoi(input.substr(input.find(",") + 1,input.size() - input.find(",")));
        }
        redTiles.push_back({stoi(input.substr(0,input.find(","))),stoi(input.substr(input.find(",") + 1,input.size() - input.find(",")))});
    }
    redTiles.push_back({firstX, firstY});

    rows.push_back(0);
    for(int i = 0; i < redTiles.size() - 1; i++){
        rows.push_back(redTiles[i][1]);
        rows.push_back(redTiles[i+1][1] + 1);
    }
    sort(rows.begin(), rows.end());
    rows.erase(unique(rows.begin(), rows.end()), rows.end());

    columns.push_back(0);
    for(int i = 0; i < redTiles.size() - 1; i++){
        columns.push_back(redTiles[i][0]);
        columns.push_back(redTiles[i+1][0] + 1);
    }
    sort(columns.begin(), columns.end());
    columns.erase(unique(columns.begin(), columns.end()), columns.end());
    
    for(int redTile = 0; redTile < redTiles.size(); redTile++){
        for(int i = 0; i < columns.size(); i++){
            if(columns[i] == redTiles[redTile][0]){
                for(int j = 0; j < rows.size(); j++){
                    if(rows[j] == redTiles[redTile][1]){
                        compRedTiles.push_back({i,j});
                        break;
                    }
                }
                break;
            }
        }
    }
    
    for(int i = 0; i < rows.size(); i++){
        compTileMap.push_back({});
        for(int j = 0; j < columns.size(); j++){
            compTileMap[i].push_back('x');
        }
    }

    for(int redTile = 0; redTile < compRedTiles.size(); redTile++){
        compTileMap[compRedTiles[redTile][1]][compRedTiles[redTile][0]] = '#';
    }

    for(int redTile = 0; redTile < compRedTiles.size() - 1; redTile++){
        if(compRedTiles[redTile][0] == compRedTiles[redTile + 1][0]){
            if(compRedTiles[redTile + 1][1] > compRedTiles[redTile][1]){
                for(int i = compRedTiles[redTile][1] + 1; i < compRedTiles[redTile + 1][1]; i++){
                    compTileMap[i][compRedTiles[redTile][0]] = 'X';
                }
            } else {
                for(int i = compRedTiles[redTile][1] - 1; i > compRedTiles[redTile + 1][1]; i--){
                    compTileMap[i][compRedTiles[redTile][0]] = 'X';
                }
            }
        } else if(compRedTiles[redTile][1] == compRedTiles[redTile + 1][1]){
            if(compRedTiles[redTile + 1][0] > compRedTiles[redTile][0]){
                for(int i = compRedTiles[redTile][0] + 1; i < compRedTiles[redTile + 1][0]; i++){
                    compTileMap[compRedTiles[redTile][1]][i] = 'X';
                }
            } else {
                for(int i = compRedTiles[redTile][0] - 1; i > compRedTiles[redTile + 1][0]; i--){
                    compTileMap[compRedTiles[redTile][1]][i] = 'X';
                }
            }
        }
    }

    compVoidTilesFilling(0, 0);
    
    ofstream myFile("output.txt");
    
    cout << '\n';
    cout << '\n';
    for(vector <char> tileLine : compTileMap){
        cout << '\n';
        myFile << endl;
        for(char tile : tileLine){
            cout << tile;
            myFile << tile;
        }
    }

    long long int largestArea = 0;
    int tile1LA = 0;
    int tile2LA = 0;
    for(int tile1 = 0; tile1 < compRedTiles.size(); tile1++){
        for(int tile2 = tile1 + 1; tile2 < compRedTiles.size(); tile2++){
            if(isAreaValid(tile1, tile2)){
                int redTile1x = columns[compRedTiles[tile1][0]];
                int redTile1y = rows[compRedTiles[tile1][1]];
                
                int redTile2x = columns[compRedTiles[tile2][0]];
                int redTile2y = rows[compRedTiles[tile2][1]];
                
                int x1, y1, x2, y2;
                if(redTile1x <= redTile2x){
                    x1 = redTile1x;
                    x2 = redTile2x;
                } else {
                    x1 = redTile2x;
                    x2 = redTile1x;
                }
                if(redTile1y <= redTile2y){
                    y1 = redTile1y;
                    y2 = redTile2y;
                } else {
                    y1 = redTile2y;
                    y2 = redTile1y;
                }

                long long int area = (1 + x2 - x1) * (1 + y2 - y1);
                if(area > largestArea){
                    largestArea = area;
                    tile1LA = tile1;
                    tile2LA = tile2;
                }
            }
        }
    }

    cout << "\nLargest Area: " << largestArea << " tile1: " << tile1LA << " tile2: " << tile2LA;

    file.close();
    return 0;

}