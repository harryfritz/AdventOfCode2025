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

using namespace std;

vector <vector <long long>> redTiles;

vector <vector <char>> tileMap;

void printTileMap(){
    for(vector <char> tileLine : tileMap){
        cout << "\n";
        for(char tile : tileLine){
            cout << tile;
        }
    }
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    cout << "\n";
    for(int i = 0; getline(file, input); i++){        
        redTiles.push_back({stoll(input.substr(0,input.find(","))),stoll(input.substr(input.find(",") + 1,input.size() - input.find(",")))});
    }

    //Build Tile Matrix
    int xMax = 0;
    int yMax = 0;
    for(vector <long long> redTile : redTiles){ //Define Tile Size
        if(redTile[0] > xMax){
            xMax = redTile[0];
        }
        if(redTile[1] > yMax){
            yMax = redTile[1];
        }
    }
    
    //Fill Tile Map with '.'
    vector <char> tileLine;
    cout << "\n";
    for(int j = 0; j < xMax + 3; j++){
        tileLine.push_back('.');
        cout << "\rBuild Tile Line j:" << j;
    }
    cout << "\n";
    for(int i = 0; i < yMax + 2; i++){
        cout << "\rBuild Tile Map i:" << i;
        tileMap.push_back(tileLine);
    }
    
    //Draw Tilemaps borders
    cout << "\n";
    for(int i = 0; i < tileMap.size(); i++){
        tileMap[i][0] = 'o';
        tileMap[i][tileMap[i].size()-1] = 'o';
        cout << "\rDraw Borders 1"; 
    }
    cout << "\n";
    for(int j = 0; j < tileMap[0].size(); j++){
        tileMap[0][j] = 'o';
        tileMap[tileMap.size()-1][j] = 'o';
        cout << "\rDraw Borders 2"; 
    }
    
    cout << "\n";
    //Place Red Tiles on Tile Matrix
    for(vector <long long> redTile : redTiles){
        tileMap[redTile[1]][redTile[0]] = '#';
        cout << "\rPlace Red Tiles"; 
    }

    //Place Green Tiles Contour
    cout << "\n";
    for(int redTile = 0; redTile < redTiles.size(); redTile++){
        cout << "\rGreen Tiles Contour"; 
        if(redTile != redTiles.size() - 1){
            if(redTiles[redTile][0] == redTiles[redTile+1][0]){
                if(redTiles[redTile][1] < redTiles[redTile+1][1]){
                    for(int i = redTiles[redTile][1] + 1; i < redTiles[redTile+1][1]; i++) tileMap[i][redTiles[redTile][0]] = 'X';
                } else {
                    for(int i = redTiles[redTile][1] - 1; i > redTiles[redTile+1][1]; i--) tileMap[i][redTiles[redTile][0]] = 'X';
                }
            } else if(redTiles[redTile][1] == redTiles[redTile+1][1]){
                if(redTiles[redTile][0] < redTiles[redTile+1][0]){
                    for(int j = redTiles[redTile][0] + 1; j < redTiles[redTile+1][0]; j++) tileMap[redTiles[redTile][1]][j] = 'X';
                } else {
                    for(int j = redTiles[redTile][0] - 1; j > redTiles[redTile+1][0]; j--) tileMap[redTiles[redTile][1]][j] = 'X';
                }
            }
        } else {
            if(redTiles[redTile][0] == redTiles[0][0]){
                if(redTiles[redTile][1] < redTiles[0][1]){
                    for(int i = redTiles[redTile][1] + 1; i < redTiles[0][1]; i++) tileMap[i][redTiles[redTile][0]] = 'X';
                } else {
                    for(int i = redTiles[redTile][1] - 1; i > redTiles[0][1]; i--) tileMap[i][redTiles[redTile][0]] = 'X';
                }
            } else if(redTiles[redTile][1] == redTiles[0][1]){
                if(redTiles[redTile][0] < redTiles[0][0]){
                    for(int j = redTiles[redTile][0] + 1; j < redTiles[0][0]; j++) tileMap[redTiles[redTile][1]][j] = 'X';
                } else {
                    for(int j = redTiles[redTile][0] - 1; j > redTiles[0][0]; j--) tileMap[redTiles[redTile][1]][j] = 'X';
                }
            }
        }
    }

    // Place Green Tiles Filling
    cout << "\n";
    for(int y = 0; y < tileMap.size(); y++){
        cout << "\rGreen Tiles Filling y:" << y; 
        bool fillGreen = false;
        int lastX = 0;
        for(int x = 0; x < tileMap[y].size(); x++){
            if(tileMap[y][x] == 'X'){
                if(x != lastX+1) {
                    fillGreen = !fillGreen;
                }
                lastX = x;
            }
            
            if(tileMap[y][x] == '.' && fillGreen){
                tileMap[y][x] = 'X';
                
                // bool isInside = true;
                // if(y < x){
                //     for(int k = y - 1; isInside; k--){
                //         if(tileMap[k][x] == '#' || tileMap[k][x] == 'X'){
                //             break;
                //         } else if(tileMap[k][x] == 'o'){
                //             isInside = false;
                //         }
                //     }
                //     for(int k = y + 1; isInside; k++){
                //         if(tileMap[k][x] == '#' || tileMap[k][x] == 'X'){
                //             break;
                //         } else if(tileMap[k][x] == 'o'){
                //             isInside = false;
                //         }
                //     }
                //     for(int k = x - 1; isInside; k--){
                //         if(tileMap[y][k] == '#' || tileMap[y][k] == 'X'){
                //             break;
                //         } else if(tileMap[y][k] == 'o'){
                //             isInside = false;
                //         }
                //     }
                //     for(int k = x + 1; isInside; k++){
                //         if(tileMap[y][k] == '#' || tileMap[y][k] == 'X'){
                //             break;
                //         } else if(tileMap[y][k] == 'o'){
                //             isInside = false;
                //         }
                //     }
                // } else {
                //     for(int k = x - 1; isInside; k--){
                //         if(tileMap[y][k] == '#' || tileMap[y][k] == 'X'){
                //             break;
                //         } else if(tileMap[y][k] == 'o'){
                //             isInside = false;
                //         }
                //     }
                //     for(int k = x + 1; isInside; k++){
                //         if(tileMap[y][k] == '#' || tileMap[y][k] == 'X'){
                //             break;
                //         } else if(tileMap[y][k] == 'o'){
                //             isInside = false;
                //         }
                //     }
                //     for(int k = y - 1; isInside; k--){
                //         if(tileMap[k][x] == '#' || tileMap[k][x] == 'X'){
                //             break;
                //         } else if(tileMap[k][x] == 'o'){
                //             isInside = false;
                //         }
                //     }
                //     for(int k = y + 1; isInside; k++){
                //         if(tileMap[k][x] == '#' || tileMap[k][x] == 'X'){
                //             break;
                //         } else if(tileMap[k][x] == 'o'){
                //             isInside = false;
                //         }
                //     }   
                // }
                // 
                // if(isInside){
                //     tileMap[y][x] = 'X';
                // }
            }
        }
    }

    // printTileMap();

    cout << "\n";
    long long maxArea = 0;
    for(int tile1 = 0; tile1 < redTiles.size(); tile1++){
        for(int tile2 = tile1 + 1; tile2 < redTiles.size(); tile2++){
            bool areaValid = true;

            if(tile1 == 6) break;
            if(tile2 == 6) break;
            
            int x0, y0, x1, y1;
            if(redTiles[tile1][0] < redTiles[tile2][0]){
                x0 = redTiles[tile1][0];
                x1 = redTiles[tile2][0];
            } else {
                x0 = redTiles[tile2][0];
                x1 = redTiles[tile1][0];
            }
            if(redTiles[tile1][1]< redTiles[tile2][1]){
                y0 = redTiles[tile1][1];
                y1 = redTiles[tile2][1];
            } else {
                y0 = redTiles[tile2][1];
                y1 = redTiles[tile1][1];
            }

            
            for(int i = y0; i <= y1 && areaValid; i++){
                for(int j = x0; j <= x1 && areaValid; j++){
                    cout << "\rTile Map i:" << i << " j:" << j;
                    if(tileMap[i][j] == '.') areaValid = false;
                }
            }
            
            if(areaValid){
                long long area = (1 + llabs(redTiles[tile1][0] - redTiles[tile2][0])) * (1 + llabs(redTiles[tile1][1] - redTiles[tile2][1]));
                if(area > maxArea){
                    maxArea = area;
                    cout << "\nTile1:" << tile1 << "\tTile2:" << tile2 << "\tArea:" << area << "\tMaxArea:" << maxArea << " **\n";
                } else {
                    cout << "\nTile1:" << tile1 << "\tTile2:" << tile2 << "\tArea:" << area << "\tMaxArea:\n" << maxArea;
                }
            }

        }
    }

    file.close();
    return 0;
}