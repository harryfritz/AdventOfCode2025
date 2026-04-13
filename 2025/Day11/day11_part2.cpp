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
#include <list>
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

void dfs(__int16& node, __int16& destination, std::vector <std::vector <__int16>>& graph, std::vector <bool>& visited, 
    long long &cnt, bool DACvisited, bool FFTvisited) {
    
    if(node == 431) return;

    if(node == 477) return;
    
    if (node == destination && DACvisited && FFTvisited) {
        cnt++;
        // cout << "\r" << count << "   ";
        return;
    }

    visited[node] = true;
    if(node == 10) DACvisited = true;
    if(node == 3) FFTvisited = true;

    for (__int16 neighbor : graph[node]) {
        // dfs(neighbor, destination, graph, visited, cnt);
        if (!visited[neighbor]) {
            dfs(neighbor, destination, graph, visited, cnt, DACvisited, FFTvisited);
        }
    }

    visited[node] = false;
    if(node == 10) DACvisited = false;
    if(node == 3) FFTvisited = false;
}

long long countPaths(int n, std::vector <std::vector <__int16>>& edgeList, __int16 &source, __int16 &destination) {

    std::vector <std::vector <__int16>> graph(n + 1);
    for (auto &edge : edgeList) {
        __int16 u = edge[0];
        __int16 v = edge[1];
        graph[u].push_back(v);
    }

    std::vector <bool> visited(n + 1, false);
    long long cnt = 0; 

    dfs(source, destination, graph, visited, cnt, false, false);

    return cnt;
}

int main() {
    
    std::ifstream file;
    std::string fileName = "input.txt";
    file.open(fileName);
    std::string input;

    std::map <std::string, __int16> nodeDictionary;
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
    std::vector< std::vector<__int16>> edgeList;
    for(__int16 line = 1; getline(file, input); line++) {        
        
        std::vector <std::string> device = split(input, ' ');
        device[0].pop_back(); // Remove ':'
        
        for(__int16 output = 1; output < device.size(); output++) {
            edgeList.push_back({line, nodeDictionary.at(device[output])});
        }
 
    }

    __int16 source = nodeDictionary.at("svr");
    __int16 destination = nodeDictionary.at("out");

    long long answer = countPaths(graphSize, edgeList, source, destination);
    std::cout << "\n\nAnswer: " << answer;
    
    file.close();
    return 0;
    
}
