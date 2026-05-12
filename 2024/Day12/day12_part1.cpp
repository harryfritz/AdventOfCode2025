
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 12 - Part one
// Author: Fritz, M.H.
//
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector <string> split(const string& text, char delim) {
    vector <string> tokens;
    int nextDelim = 0, cursor = 0;
    while(nextDelim >= 0) {
        nextDelim = text.find(delim, cursor + 1);
        tokens.push_back(text.substr(cursor, nextDelim - cursor));
        if(nextDelim >= 0) {
            cursor = nextDelim;
            while(text[cursor] == delim) cursor++;
        }
    }
    return tokens;
}

void processPlot(vector <string>& garden, int row, int column, vector <vector <bool>>& processedPlots, int& area, int& perimeter) {
    area++;
    processedPlots[row][column] = true;
    char plot = garden[row][column];
    
    if(row == 0) {
        perimeter++;
    } else {
        if(garden[row - 1][column] == plot) {
            if(!processedPlots[row - 1][column]) processPlot(garden, row - 1, column, processedPlots, area, perimeter);
        } else {
            perimeter++;
        }
    }

    if(column == 0) {
        perimeter++;
    } else {
        if(garden[row][column - 1] == plot) {
            if(!processedPlots[row][column - 1]) processPlot(garden, row, column - 1, processedPlots, area, perimeter);
        } else {
            perimeter++;
        }
    }

    if(row == garden.size() - 1) {
        perimeter++;
    } else {
        if(garden[row + 1][column] == plot) {
            if(!processedPlots[row + 1][column]) processPlot(garden, row + 1, column, processedPlots, area, perimeter);
        } else {
            perimeter++;
        }
    }

    if(column == garden[0].size() - 1) {
        perimeter++;
    } else {
        if(garden[row][column + 1] == plot) {
            if(!processedPlots[row][column + 1]) processPlot(garden, row, column + 1, processedPlots, area, perimeter);
        } else {
            perimeter++;
        }
    }

}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    vector <string> garden;
    while(getline(file, input)) {
        cout << "\n" << input;
        garden.push_back(input);
    }
    cout << "\n";

    vector <bool> allFalse(garden[0].size(), false);
    vector <vector <bool>> processedPlots(garden.size(), allFalse);

    long long answer = 0; 

    while(true) {
        int row = -1;
        int column = -1;
        for(int i = 0; i < garden.size() && row == -1; i++) {
            for(int j = 0; j < garden[i].size() && column == -1; j++) {
                if(!processedPlots[i][j]) {
                    row = i;
                    column = j;
                }
            }
        }
        
        if(row == -1 && column == -1) {
            break;
        }

        int area = 0;
        int perimeter = 0;
        processPlot(garden, row, column, processedPlots, area, perimeter);
        int price = area*perimeter;
        answer += price;
        cout << "\nRegion of " << garden[row][column] << " plants. Area: " << area << "\tPerimeter: " << perimeter << "\tPrice: " << price;
    }
    
    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}
