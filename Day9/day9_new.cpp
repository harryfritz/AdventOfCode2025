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


vector <vector <int>> redTiles;

// vector <vector <char>> tileMap;


vector <vector <int>> largestAreas;

long long int tilesFilled = 0;


vector <long long int> areas;
vector <vector <int> > areasCoordinates;

void insertAreas(int tile1, int tile2, long long int area){
    if(areas.size() == 0){
        areas.insert(areas.begin(), area);
        areasCoordinates.insert(areasCoordinates.begin(), {tile1, tile2});
        return;
    }
    
    for(int i = 0; i < areas.size(); i++){
        if(area < areas[i]){
            areas.insert(areas.begin() + i, area);
            areasCoordinates.insert(areasCoordinates.begin() + i, {tile1, tile2});
            return;
        } else if(i == areas.size() - 1){
            areas.insert(areas.begin() + i + 1, area);
            areasCoordinates.insert(areasCoordinates.begin() + i + 1, {tile1, tile2});
            return;
        }
    }
}


bool isTileInside(int tileX, int tileY){
    
    //Ray Casting
    vector <char> tileLine;// = tileMap[tileY];
    int borderCrossCounter = 0;
    bool enableCrossCounter = true;

    for(int x = tileX + 1; x < tileLine.size() && tileLine[x] != 'o'; x++){
        if(tileLine[x] == 'X' && enableCrossCounter){
            borderCrossCounter++;
        } else if(tileLine[x] == '#'){
            enableCrossCounter = !enableCrossCounter;
        }
    }

    if(borderCrossCounter % 2 == 0){
        return false;
    } else {
        return true;
    }

    return true;
    
    
    
    // Scanner Methdo
    for(int k = tileY; ; k--){
        if(tileMap[k][tileX] == '#' || tileMap[k][tileX] == 'X'){
            break;
        } else if(tileMap[k][tileX] == 'o'){
            return false;
        }
    }
    
    for(int k = tileY; ; k++){
        if(tileMap[k][tileX] == '#' || tileMap[k][tileX] == 'X'){
            break;
        } else if(tileMap[k][tileX] == 'o'){
            return false;
        }
    }

    for(int k = tileX; ; k--){
        if(tileMap[tileY][k] == '#' || tileMap[tileY][k] == 'X'){
            break;
        } else if(tileMap[tileY][k] == 'o'){
            return false;
        }
    }

    for(int k = tileX; ; k++){
        if(tileMap[tileY][k] == '#' || tileMap[tileY][k] == 'X'){
            break;
        } else if(tileMap[tileY][k] == 'o'){
            return false;
        }
    }

    return true;
}

bool isAreaValid_old(int tile1, int tile2){

    cout << '\n';
    if(redTiles[tile1][0] < redTiles[tile2][0] && redTiles[tile1][1] < redTiles[tile2][1]){
        for(int i = redTiles[tile1][1]; i <= redTiles[tile2][1]; i++){
            for(int j = redTiles[tile1][0]; j <= redTiles[tile2][0]; j++){
                cout << "\r     (" << j << "," << i << ")          ";
                if(tileMap[i][j] == '.'){
                    if(!isTileInside(j, i)) return false;
                }
            }
        }
    } else if(redTiles[tile1][0] < redTiles[tile2][0] && redTiles[tile1][1] >= redTiles[tile2][1]){
        for(int i = redTiles[tile2][1]; i <= redTiles[tile1][1]; i++){
            for(int j = redTiles[tile1][0]; j <= redTiles[tile2][0]; j++){
                cout << "\r     (" << j << "," << i << ")          ";
                if(tileMap[i][j] == '.'){
                    if(!isTileInside(j, i)) return false;
                }
            }
        }
    } else if(redTiles[tile1][0] >= redTiles[tile2][0] && redTiles[tile1][1] < redTiles[tile2][1]){
        for(int i = redTiles[tile1][1]; i <= redTiles[tile2][1]; i++){
            for(int j = redTiles[tile2][0]; j <= redTiles[tile1][0]; j++){
                cout << "\r     (" << j << "," << i << ")          ";
                if(tileMap[i][j] == '.'){
                    if(!isTileInside(j, i)) return false;
                }
            }
        }
    } else if(redTiles[tile1][0] >= redTiles[tile2][0] && redTiles[tile1][1] >= redTiles[tile2][1]){
        for(int i = redTiles[tile2][1]; i <= redTiles[tile1][1]; i++){
            for(int j = redTiles[tile2][0]; j <= redTiles[tile1][0]; j++){
                cout << "\r     (" << j << "," << i << ")          ";
                if(tileMap[i][j] == '.'){
                    if(!isTileInside(j, i)) return false;
                }
            }
        }
    }

    

    return true;

}

void printTileMap(){
    for(int i = 0; i < TILEMAP_HEIGHT; i++){
        cout << '\n';
        for(int j = 0; j < TILEMAP_WIDTH; j++){
            cout << tileMap[i][j];
        }
    }
    
    
    // for(vector <char> tileLine : tileMap){
    //     cout << '\n';
    //     for(char tile : tileLine){
    //         cout << tile;
    //     }
    // }
}

void printLargestAreas(){
    cout << "\nLargest Areas: " << largestAreas.size();
    for(vector <int> line : largestAreas){
        cout << '\n';
        for(int tile : line){
            cout << " " << tile;
        }
    }
}

void drawTilemapBorders(){
    //Draw Tilemaps borders
    cout << '\n';
    for(int i = 0; i < TILEMAP_HEIGHT; i++){
        tileMap[i][0] = 'o';
        tileMap[i][TILEMAP_WIDTH-1] = 'o';
        cout << "\rDraw Vertical Borders " << i; 
    }
    cout << '\n';
    for(int j = 0; j < TILEMAP_WIDTH; j++){
        tileMap[0][j] = 'o';
        tileMap[TILEMAP_HEIGHT-1][j] = 'o';
        cout << "\rDraw Horizontal Borders " << j; 
    }
    
    // cout << '\n';
    // for(int i = 0; i < tileMap.size(); i++){
    //     tileMap[i][0] = 'o';
    //     tileMap[i][tileMap[i].size()-1] = 'o';
    //     cout << "\rDraw Vertical Borders " << i; 
    // }
    // cout << '\n';
    // for(int j = 0; j < tileMap[0].size(); j++){
    //     tileMap[0][j] = 'o';
    //     tileMap[tileMap.size()-1][j] = 'o';
    //     cout << "\rDraw Horizontal Borders " << j; 
    // }
}

void placeRedTiles(){
    cout << '\n';
    //Place Red Tiles on Tile Matrix
    for(vector <int> redTile : redTiles){
        tileMap[redTile[1]][redTile[0]] = '#';
        cout << "\rPlace Red Tiles"; 
    }
}

void placeGreenTilesContour(){
    //Place Green Tiles Contour
    cout << '\n';
    for(int redTile = 0; redTile < redTiles.size(); redTile++){
        cout << "\rGreen Tiles Contour " << redTile; 
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
}

void buildTileMap(){
    //Build Tile Map
    int xMax = 0;
    int yMax = 0;
    for(vector <int> redTile : redTiles){ //Define Tile Map Size
        if(redTile[0] > xMax){
            xMax = redTile[0];
        }
        if(redTile[1] > yMax){
            yMax = redTile[1];
        }
    }

    cout << '\n';
    for(int i = 0; i < TILEMAP_HEIGHT; i++){
        cout << "\rBuild Tile Line " << i;
        for(int j = 0; j < TILEMAP_WIDTH; j++){
            tileMap[i][j] = 'x';
        }
    }


    // //Fill Tile Map with '.'
    // vector <char> tileLine;
    // cout << '\n';
    // for(int j = 0; j < xMax + 3; j++){
    //     tileLine.push_back('.');
    //     cout << "\rBuild Tile Column " << j;
    // }
    // cout << "\n";
    // for(int i = 0; i < yMax + 3; i++){
    //     cout << "\rBuild Tile Map Line " << i;
    //     tileMap.push_back(tileLine);
    // }
}

void placeGreenTilesFilling(){   
    // cout << '\n';
    // for(int i = 1; i < tileMap.size(); i++){
    //     bool horBorder = false;
    //     bool inside = false;
    //     cout << "\rFilling Map Line " << i;        
    //     for(int j = 0; j < tileMap[i].size(); j++){
            
    //         if(tileMap[i][j] == '#'){
    //             if(horBorder){

    //             }
    //             horBorder = !horBorder;
    //             // inside = !inside;
    //         } else if(tileMap[i][j] == 'X' && !horBorder){
    //             inside = !inside;
    //         } else if(inside){
    //             tileMap[i][j] = 'x';
    //         }
            
            
    //         // if(tileMap[i][j] == '.' && isTileInside(j, i) && tileMap[i-1][j] != '.'){
    //         //     tileMap[i][j] = 'x';
    //         // }
    //     }

    // }
}

void recursiveGreenTilesFilling(int centerTileX, int centerTileY){
    if(tileMap[centerTileY][centerTileX - 1] == '.'){
        cout << "\ntile " << centerTileX << ' ' << centerTileY;
        tileMap[centerTileY][centerTileX - 1] = 'x';
        recursiveGreenTilesFilling(centerTileX - 1, centerTileY);
    }
    if(tileMap[centerTileY][centerTileX + 1] == '.'){
        cout << "\ntile " << centerTileX << ' ' << centerTileY;
        tileMap[centerTileY][centerTileX + 1] = 'x';
        recursiveGreenTilesFilling(centerTileX + 1, centerTileY);
    }
    if(tileMap[centerTileY - 1][centerTileX] == '.'){
        cout << "\ntile " << centerTileX << ' ' << centerTileY;
        tileMap[centerTileY - 1][centerTileX] = 'x';
        recursiveGreenTilesFilling(centerTileX, centerTileY - 1);
    }
    if(tileMap[centerTileY + 1][centerTileX] == '.'){
        cout << "\ntile " << centerTileX << ' ' << centerTileY;
        tileMap[centerTileY + 1][centerTileX] = 'x';
        recursiveGreenTilesFilling(centerTileX, centerTileY + 1);
    }
}

void recursiveVoidTilesFilling(int centerTileX, int centerTileY){    
    int neighborTileX;
    int neighborTileY; 
    
    for(int count  = 0; count < 4; count++){
        switch (count)
        {
        case 0:
            neighborTileX = centerTileX - 1;
            neighborTileY = centerTileY; 
            break;
        case 1:
            neighborTileX = centerTileX + 1;
            neighborTileY = centerTileY;
            break;
        case 2:
            neighborTileX = centerTileX;
            neighborTileY = centerTileY - 1;
            break;
        case 3:
            neighborTileX = centerTileX;
            neighborTileY = centerTileY + 1;
            break;
        
        default:
            neighborTileX = 0;
            neighborTileY = 0;
            break;
        }

        if(tileMap[neighborTileY][neighborTileX] == 'x'){
            cout << "\ntile " << centerTileX << ' ' << centerTileY;
            tileMap[neighborTileY][neighborTileX] = '.';
            recursiveVoidTilesFilling(neighborTileX, neighborTileY);
        }

    }

    
}

void voidTilesFilling(int firstTileX, int firstTileY){
    
    vector <vector <int>> tilesToFill;
    tilesToFill.push_back({firstTileX, firstTileY});
    int centerTileX;
    int centerTileY;
    
    while(tilesToFill.size() > 0){
        centerTileX = tilesToFill[0][0];
        centerTileY = tilesToFill[0][1];
        
        if(tileMap[centerTileY][centerTileX - 1] == 'x'){
            tileMap[centerTileY][centerTileX - 1] = '.';
            tilesToFill.push_back({centerTileX - 1, centerTileY});
        }
        if(tileMap[centerTileY][centerTileX + 1] == 'x'){
            tileMap[centerTileY][centerTileX + 1] = '.';
            tilesToFill.push_back({centerTileX + 1, centerTileY});
        }
        if(tileMap[centerTileY - 1][centerTileX] == 'x'){
            tileMap[centerTileY - 1][centerTileX] = '.';
            tilesToFill.push_back({centerTileX, centerTileY - 1});
        }
        if(tileMap[centerTileY + 1][centerTileX] == 'x'){
            tileMap[centerTileY + 1][centerTileX] = '.';
            tilesToFill.push_back({centerTileX, centerTileY + 1});
        }

        tilesToFill.erase(tilesToFill.begin());
        
        if(tilesToFill.size() % 10000 == 0){
            cout << "\rTiles to fill: " << tilesToFill.size();
        }

        

    }
    

}

bool isAreaValid(int t1X, int t1Y, int t2X, int t2Y){
    
    int tile1X, tile1Y, tile2X, tile2Y;

    if(t1X <= t2X){
        tile1X = t1X;
        tile2X = t2X;
    } else {
        tile1X = t2X;
        tile2X = t1X;
    }

    if(t1Y <= t2Y){
        tile1Y = t1Y;
        tile2Y = t2Y;
    } else {
        tile1Y = t2Y;
        tile2Y = t1Y;
    }
    
    char a0, a1, a2;
    for(int i = tile1Y; i <= tile2Y; i++){
        for(int j = tile1X + 2; j <= tile2X; j++){
            a0 = tileMap[i][j - 2];
            a1 = tileMap[i][j - 1];
            a2 = tileMap[i][j];
            if(a1 == 'X' && a0 == '.' && a2 == '.'){
                return false;
            }
        }
    }
    
    for(int j = tile1X; j <= tile2X; j++){
        for(int i = tile1Y + 2; i <= tile2Y; i++){
            a0 = tileMap[i - 2][j];
            a1 = tileMap[i - 1][j];
            a2 = tileMap[i][j];
            if(a1 == 'X' && a0 == '.' && a2 == '.'){
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
    for(int i = 0; getline(file, input); i++){        
        redTiles.push_back({stoi(input.substr(0,input.find(","))),stoi(input.substr(input.find(",") + 1,input.size() - input.find(",")))});
    }

    // Go through every redTile combination
    cout << '\n';   
    for(int tile1 = 0; tile1 < redTiles.size(); tile1++){
        for(int tile2 = tile1 + 1; tile2 < redTiles.size(); tile2++){
            cout << "\rChecking redTile Combinations " << tile1 << " and " << tile2;
            long long int area = (1 + llabs(redTiles[tile1][0] - redTiles[tile2][0])) * (1 + llabs(redTiles[tile1][1] - redTiles[tile2][1]));
            insertAreas(tile1, tile2, area);
            if(areas.size() >= 900){
                areas.erase(areas.begin());
                areasCoordinates.erase(areasCoordinates.begin());
            }
        }
    }

    // buildTileMap();

    // drawTilemapBorders();

    // placeRedTiles();
    
    // placeGreenTilesContour();   
    
    // // printTileMap();

    // cout << '\n';
    // for(int i = areasCoordinates.size() - 1; i >= 0; i--){
    //     cout << "\rChecking Valid Areas " << i; 
    //     int tile1X = redTiles[areasCoordinates[i][0]][0];
    //     int tile1Y = redTiles[areasCoordinates[i][0]][1];
    //     int tile2X = redTiles[areasCoordinates[i][1]][0];
    //     int tile2Y = redTiles[areasCoordinates[i][1]][1];
    //     if(isAreaValid(tile1X, tile1Y, tile2X, tile2Y)){
    //         cout << "\n\nFound Valid Area i: " << i;
    //         break; 
    //     //     areasCoordinates.erase(areasCoordinates.begin() + i);
    //     //     areas.erase(areas.begin() + i);
    //     }
    // }

    // file.close();
    // return 0;




    buildTileMap();

    drawTilemapBorders();

    placeRedTiles();
    
    placeGreenTilesContour();

    // placeGreenTilesFilling();

    cout << '\n';
    tileMap[1][1] = '.';
    voidTilesFilling(1, 1);
    // recursiveVoidTilesFilling(1, 1);
    // recursiveGreenTilesFilling(98026 + 1, 50027);

    printTileMap();

    file.close();
    return 0;





    // // Go through every redTile combination
    // cout << '\n';
    // long long int maxArea = 0;
    // for(int tile1 = 0; tile1 < redTiles.size(); tile1++){
    //     for(int tile2 = tile1 + 1; tile2 < redTiles.size(); tile2++){
    //         long long int area = (1 + llabs(redTiles[tile1][0] - redTiles[tile2][0])) * (1 + llabs(redTiles[tile1][1] - redTiles[tile2][1]));
    //         if(area > maxArea){
    //             maxArea = area;
    //             cout << "\nRed Tiles " << tile1 << " and " << tile2 << "\tArea:" << area << "\tMaxArea:" << maxArea << " **";
    //             largestAreas.push_back({tile1, tile2});
    //         } 
    //     }
    // }

    printLargestAreas();

    cout << "\nValid Areas:";
    for(int i = largestAreas.size() - 1; i >= 0; i--){
        cout << '\n' << largestAreas[i][0] << " " << largestAreas[i][1] << ": " 
            << "(" << redTiles[largestAreas[i][0]][0] << "," << redTiles[largestAreas[i][0]][1] << ") to "
            << "(" << redTiles[largestAreas[i][1]][0] << "," << redTiles[largestAreas[i][1]][1] << ") - "
            << isAreaValid_old(largestAreas[i][0], largestAreas[i][1]);
    }


    file.close();
    return 0;
}