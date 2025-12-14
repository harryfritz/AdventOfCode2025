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

using namespace std;

vector <vector <vector <int>>> presents;

void buildPresents(string _fileName){
    ifstream file;
    file.open("example.txt");

    string input;
    
    for(int index = 0; getline(file, input) && index < 6; ){
        if(input[0] >= '0' && input[0] <= '5'){
            presents.push_back({});
            getline(file, input);
            for(int row = 0; !input.empty(); row++){
                presents[index].push_back({});
                for(int column = 0; column < input.size(); column++){
                    presents[index][row].push_back(input[column]);
                }
                getline(file, input);
            }
            index++;
        }
    }

    file.close();
}


int main() {
  
    string fileName = "example.txt";
    
    buildPresents(fileName);

    ifstream file;
    file.open(fileName);
    string input;

    for(int i = 0; i < 5 * presents.size(); i++) getline(file, input);
    
    getline(file, input);
    int columns = stoi(input.substr(0,input.find('x')));
    int rows = stoi(input.substr(input.find('x') + 1, input.find(':') - input.find('x')));

    vector <vector <int>> treeSpace;
    for(int i = 0; i < rows; i++){
        treeSpace.push_back({});
        for(int j = 0; j < columns; j++){
            treeSpace[i].push_back('.');
        }
    }

    

    
    
    return 0;
}