/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 11 - Part two
// Author: Fritz, M.H.
//
// 
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stack>

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

void DfsRecursive(int node, int dest, const std::vector<std::vector<int>>& graph, std::vector<bool>& visited, long long &count) {
    
    if(node == dest) {
        count++;
        return;
    }
    
    visited[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            DfsRecursive(neighbor, dest, graph, visited, count);  // Recursive call for unvisited neighbors
        }
    }

    visited[node] = false;
}

void DfsIterative(int start, int finish, const std::vector<std::vector<int>>& graph, long long &count) {
    
    std::vector<bool> visited(graph.size(), false);  // Initialize visited array
    std::stack<int> stk;  // Create a stack for DFS

    stk.push(start);  // Push the starting node

    while (!stk.empty()) {
        int node = stk.top();
        stk.pop();

        if (!visited[node]) {
            visited[node] = true;  // Mark the node as visited
            
            // Push all unvisited neighbors onto the stack
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    stk.push(neighbor);
                    visited[node] = false;
                }
            }

            if(node == finish) {
                count++;
                visited[node] = false;
            }

            // visited[node] = false;
        }
    }
}


int main() {
    
    std::ifstream file;
    std::string fileName = "input.txt";
    file.open(fileName);
    std::string input;

    std::map <std::string, int> nodeDictionary;
    int graphSize = 1;
    while(getline(file, input)) {        
        
        std::vector <std::string> device = split(input, ' ');
        device[0].pop_back(); // Remove ':'

        nodeDictionary.insert({device[0], graphSize});
        
        graphSize++;
    }
    
    // Include node "out"
    nodeDictionary.insert({"out", graphSize});
    graphSize++; 

    file.close();
    file.open(fileName);
    std::vector <std::vector <int>> graph(graphSize);
    for(int line = 0; getline(file, input); line++) {        
        
        std::vector <std::string> device = split(input, ' ');
        device[0].pop_back(); // Remove ':'
        
        for(int output = 1; output < device.size(); output++) {
            graph[line + 1].push_back(nodeDictionary.at(device[output]));
        }
 
    }

    std::vector <bool> visited(graph.size(), false); 

    int source = nodeDictionary.at("svr");
    int destination = nodeDictionary.at("out");

    long long count = 0;
    DfsRecursive(source, destination, graph, visited, count);
    // DfsIterative(source, destination, graph, count);
    std::cout << "\n\nAnswer: " << count;

    // long long answer = countPaths(graphSize, edgeList, source, destination);
    // cout << "\n\nAnswer: " << answer;
    
    file.close();
    return 0;
    
}
