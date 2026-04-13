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
#include <map>

std::vector <std::string> split(const std::string& text, char delim) {
    std::vector <std::string> tokens;
    
    int nextDelim = 0, cursor = 0;
    while(nextDelim >= 0) {
        nextDelim = text.find(delim, cursor + 1);
        tokens.push_back(text.substr(cursor, nextDelim - cursor));
        cursor = nextDelim + 1;
    }

    return tokens;
}

int countTiles(std::vector <std::string>& shape) {
    int tiles = 0;
    for(std::string s : shape) for(char c : s) if(c == '#') tiles++; 
    return tiles;
}

int getTreeSize(std::vector <int>& tree) {
    return tree[0] * tree[1];
}

int main() {
  
    std::ifstream file;
    file.open("input.txt");
    std::string input;

    std::vector <std::vector <std::string>> shapes(6);
    std::vector <std::vector <int>> trees;
    
    int shapeCount;
    int treesCount = -1;
    while(getline(file, input)) {
        if(!input.empty()) {
            if(input[1] == ':') {
                shapeCount = input[0] - '0';
            } else if(input[0] == '.' || input[0] == '#') {
                shapes[shapeCount].push_back(input);
            } else if(input[2] == 'x') {
                trees.push_back({});
                treesCount++;
                for(std::string treeInfo : split(input, ' ')) {
                    if(treeInfo[treeInfo.size() - 1] == ':'){
                        treeInfo.pop_back(); // Remove the ':'
                        for(std::string treeSize : split(treeInfo, 'x')) {
                            trees[treesCount].push_back(stoi(treeSize));
                        }
                    } else {
                        trees[treesCount].push_back(stoi(treeInfo));
                    }
                }
            }
        }
        
    }

    int canFit = 0;

    int treeIndex = 0;
    for(std::vector <int> tree : trees) {
        std::cout << "\nTree " << treeIndex << ": ";
        
        int presentsSize = 0;
        for(int i = 2; i < tree.size(); i++) {
            std::cout << tree[i] << "x" << countTiles(shapes[i - 2]);
            presentsSize += tree[i] * countTiles(shapes[i - 2]);
            if(i != tree.size() - 1){
                std::cout << " + ";
            } else {
                std::cout << " = " << presentsSize;
            }
        }

        int treeSize = tree[0] * tree[1];
        std::cout << " Tree size: " << tree[0] << "x" << tree[1] << " = " << treeSize;
        if(presentsSize > treeSize) {
            std::cout << " CANNOT FIT";
        } else {
            std::cout << " CAN FIT";
            canFit++;
        }

        treeIndex++;
    }  



    std::cout << "\nAnswer: " << canFit;

    file.close();
    return 0;
}