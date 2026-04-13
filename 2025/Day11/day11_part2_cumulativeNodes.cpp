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
#include <queue>

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

bool vectorContains(std::vector <std::string>& V, std::string s) {
    for(std::string v : V) {
        if(v == s) return true;
    }
    return false;
}

int main() {
    
    std::ifstream file;
    std::string fileName = "input.txt";
    file.open(fileName);
    std::string input;

    std::map <std::string, std::vector <std::string>> adjMap;
    std::map <std::string, std::vector <std::string>> reverseAdjMap;
    std::vector <std::string> nodes;
    while(getline(file, input)) {        
        std::vector <std::string> device = split(input, ' ');
        device[0].pop_back(); // Remove ':'
        if(!vectorContains(nodes, device[0])) {
            nodes.push_back(device[0]);
        } 
        auto it = reverseAdjMap.find(device[0]);
        if(it == reverseAdjMap.end()) {
            reverseAdjMap.insert({device[0], {}});
        }
        for(int i = 1; i < device.size(); i++) {
            adjMap[device[0]].push_back(device[i]);

            it = adjMap.find(device[i]);
            if(it == adjMap.end()) {
                adjMap.insert({device[i], {}});
                if(!vectorContains(nodes, device[i])) {
                    nodes.push_back(device[i]);
                } 
                reverseAdjMap[device[i]].push_back(device[0]);
            } else {
                if(!vectorContains(reverseAdjMap.at(device[i]), device[0])) {
                    reverseAdjMap[device[i]].push_back(device[0]);
                }
            }
        }   
    }

    std::map <std::string, std::vector <long long>> graph;
    for(std::string node : nodes) {
        graph[node] = {-2, 0, 0, 0};
    }
    
    std::string source = "out";
    
    std::queue <std::string> q;
    q.push(source);
    while(!q.empty()){
        std::string node = q.front();
        q.pop();
        bool ready = true;
        for(std::string parent : adjMap.at(node)) {
            if(graph.at(parent)[0] < 0) ready = false;   
        }

        if(ready) {
            graph.at(node) = {0, 0, 0, 0};
            if(node == source){
                graph.at(node) = {1, 0, 0, 0};
            } else {
                for(std::string parent : adjMap.at(node)) {                    
                    for(int i = 0; i < graph.at(node).size(); i++) {
                        graph.at(node)[i] += graph.at(parent)[i];
                    }
                }
                if(node == "dac") {
                    graph.at(node)[1] = graph.at(node)[0];
                    graph.at(node)[3] = graph.at(node)[2];
                    graph.at(node)[0] = 0;
                    graph.at(node)[2] = 0;
                } 
                if(node == "fft") {
                    graph.at(node)[2] = graph.at(node)[0];
                    graph.at(node)[3] = graph.at(node)[1];
                    graph.at(node)[0] = 0;
                    graph.at(node)[1] = 0;
                }
            }

            for(std::string child : reverseAdjMap.at(node)) {
                if(graph.at(child)[0] == -2) {
                    graph.at(child) = {-1, 0, 0, 0};
                    q.push(child);
                }
            }
        } else {
            q.push(node);
        }
        
    }

    std::cout << "\nAnswer: " << graph.at("svr")[0] << ", " << graph.at("svr")[1] << ", " << graph.at("svr")[2] << ", " << graph.at("svr")[3];
    
    file.close();
    return 0;
    
}
