/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 11 - Part one
// Author: Fritz, M.H.
//
// 
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <list>
#include <map>

using namespace std;

class Graph {
    
    private:
        map <string, list<string>> adjList; // Adjacency list to store the graph

        void dfs(string node, string dest, map<string, bool> &visited, int &count){

            if(node == dest) {
                count++;
                return;
            }

            visited.at(node) = true;

            for(string neighbor : adjList.at(node)) {
                if(!visited.at(neighbor)) {
                    dfs(neighbor, dest, visited, count);
                }
            }

            visited.at(node) = false;

        }

    public:
        void add_edge(string u, string v) {
            adjList[u].push_back(v);
        }

        void print() {
            cout << "Adjacency list for the Graph: " << endl;
            // Iterate over each vertex
            for (auto i : adjList) {
                // Print the vertex
                cout << i.first << " -> ";
                // Iterate over the connected vertices
                for (auto j : i.second) {
                    // Print the connected vertex
                    cout << j << " ";
                }
                cout << endl;
            }
        }

        int possiblePaths(string source, string destination) {

            map<string, bool> visited;
            visited.insert({"out", false});
            for (auto node : adjList) visited.insert({node.first, false});
            int count = 0;
            
            dfs(source, destination, visited, count);

            return count;
        }

};

vector <string> split(const string& text, char delim) {
    vector <string> tokens;
    
    int nextDelim = 0, cursor = 0;
    while(nextDelim >= 0) {
        nextDelim = text.find(delim, cursor + 1);
        tokens.push_back(text.substr(cursor, nextDelim - cursor));
        cursor = nextDelim + 1;
    }

    return tokens;
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    Graph devices;

    for(int line = 0; getline(file, input); line++) {        
        
        vector <string> device = split(input, ' ');
        device[0].pop_back(); // Remove ':'

        for(int output = 1; output < device.size(); output++) {
            devices.add_edge(device[0], device[output]);
        }
 
    }

    cout << "\nAnswer: " << devices.possiblePaths("you","out") << " possible paths.";
    
    file.close();
    return 0;
    
}
