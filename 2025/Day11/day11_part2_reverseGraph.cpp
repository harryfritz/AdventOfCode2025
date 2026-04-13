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

bool vectorContains(std::vector <int>& V, int x) {
    for(int v : V) {
        if(v == x) return true;
    }
    return false;
}

void dfs(int node, int destination, std::vector <std::vector <int>>& graph, std::vector <bool>& visited, long long &cnt) {
    
    if (node == destination) {
        cnt++;
        // cout << "\r" << count << "   ";
        return;
    }

    visited[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, destination, graph, visited, cnt);
        }
    }

    visited[node] = false;

}

int main() {
    
    std::ifstream file;
    std::string fileName = "example3.txt";
    file.open(fileName);
    std::string input;

    std::vector <std::string> lines;
    std::map <std::string, int> nodeDictionary;
    int graphSize = 0;
    while(getline(file, input)) {        
        lines.push_back(input);
        std::vector <std::string> device = split(input, ':');
        nodeDictionary.insert({device[0], graphSize});
        graphSize++;
    }
    nodeDictionary.insert({"out", graphSize});
    graphSize++;

    std::vector <std::vector <int>> adjList(graphSize);
    std::vector <std::vector <int>> reverseAdjList(graphSize);
    for(std::string line : lines) {
        std::vector <std::string> device = split(line, ' ');
        device[0].pop_back(); // Remove ':'
        for(int i = 1; i < device.size(); i++) {
            int parentNode = nodeDictionary.at(device[0]);
            int childNode = nodeDictionary.at(device[i]);
            adjList[parentNode].push_back(childNode);
            if(!vectorContains(reverseAdjList[childNode], parentNode)) {
                reverseAdjList[childNode].push_back(parentNode);
            }
        }
    }

    std::vector <bool> visited(graphSize, false);

    long long answer = 0;
    int source = nodeDictionary.at("svr");
    int destination = nodeDictionary.at("eee");
    
    dfs(source, destination, adjList, visited, answer);
    std::cout << "\n\nAnswer: " << answer;

//   Normal List  
//      svr -> out: too long (biggest 11 digits)
//      svr -> dac: too long (biggest 4 digits)
//      svr -> fft: too long (biggest zero)
//      dac -> fft: 0
//      fft -> dac: too long (biggest 4 digits)
//      dac -> out: 21653
//      fft -> out: too long (biggest 10 digits)
// 
//   Reversed List  
//      out -> svr: too long (biggest 10 digits)
//      out -> dac: too long (biggest zero)
//      out -> fft: too long (biggest 4 digits)
//      dac -> fft: too long (biggest 4 digits)
//      fft -> dac: 0
//      dac -> svr: too long (biggest 10 digits)
//      fft -> svr: 3011
// 
    
    file.close();
    return 0;
    
}
