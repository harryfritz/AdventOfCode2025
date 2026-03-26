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
#include <math.h>
#include <algorithm>
#include <list>
#include <map>
#include <queue>

using namespace std;

class Graph {
    
    private:
        map <string, list<string>> adjList; // Adjacency list to store the graph

        void dfs(string node, string dest, map<string, bool> &visited, int &count){

            if(dest != "out"){
                if(node == "out"){
                    return;
                }
            }
            
            
            if(node == dest) {
                count++;
                cout << "\r" << count << "   ";
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

        void bfs(int start, vector<vector<int>>& graph, int vertices){
            vector<bool> visited(vertices, false); // Track visited vertices
            queue<int> q;
            visited[start] = true; //Mark starting vertex as visited
            q.push(start); // added to queue

            while(!q.empty()){
                int current = q.front(); // Get the next vertex to explore
                q.pop(); // Remove it from queue
                cout << current << " ";
                // Visit all the neighbours of the current vertex
                for(int neighbour : graph[current]){
                    if(!visited[neighbour]){ // if not visited
                        visited[neighbour] = true; // mark as visited
                        q.push(neighbour); // Add to the queue
                    }
                }
            }
        }

        void dfsRestricted(string node, string dest, map<string, bool> &visited, int &count, vector <string> &mandatoryNodes){

            if(node == dest) {
                if(mandatoryNodes.empty()){
                    count++;
                    cout << "\r" << count << "   ";
                }
                return;
            }

            visited.at(node) = true;
            
            bool mandNode = false;
            for(int i = 0; i < mandatoryNodes.size(); i++){
                if(node == mandatoryNodes[i]) {
                    mandNode = true;
                    mandatoryNodes.erase(mandatoryNodes.begin() + i);
                }
            }

            for(string neighbor : adjList.at(node)) {
                if(!visited.at(neighbor)) {
                    dfsRestricted(neighbor, dest, visited, count, mandatoryNodes);
                }
            }

            visited.at(node) = false;
            if(mandNode){
                mandatoryNodes.push_back(node);
            }

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
            
            
            cout << "\n" << count;
            
            dfs(source, destination, visited, count);

            // bfs(source, destination, visited, count);

            return count;
        }

        int possibleRestrictedPaths(string source, string destination, vector <string> mandatoryNodes) {
            map<string, bool> visited;
            visited.insert({"out", false});
            for (auto node : adjList) visited.insert({node.first, false});
            int count = 0;

            cout << "\n" << count;
            
            dfsRestricted(source, destination, visited, count, mandatoryNodes);

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

void dfs(int node, int dest, vector<vector<int>> &graph, vector<bool> &visited, int &count) {
    
    if (node == dest) {
        count++;
        cout << "\r" << count << "   ";
        return;
    }

    visited[node] = true;

    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, dest, graph, visited, count);
        }
    }

    visited[node] = false;
}

int countPaths(int n, vector<vector<int>> &edgeList, int source, int destination) {

    vector<vector<int>> graph(n + 1); 
    for (auto &edge : edgeList) {
        int u = edge[0];
        int v = edge[1];
        graph[u].push_back(v);
    }

    vector<bool> visited(n + 1, false);
    int count = 0;

    dfs(source, destination, graph, visited, count);

    return count;
}

int main() {
    
    ifstream file;
    string fileName = "input.txt";
    file.open(fileName);
    string input;

    Graph devices;

    for(int line = 0; getline(file, input); line++) {        
        
        vector <string> device = split(input, ' ');
        device[0].pop_back(); // Remove ':'

        for(int output = 1; output < device.size(); output++) {
            devices.add_edge(device[0], device[output]);
        }
 
    }
    
    // int answer = devices.possiblePaths("svr","out");
    int answer = devices.possibleRestrictedPaths("svr", "out", {"dac","fft"});
    cout << "\n\nAnswer: " << answer;

    // map <string, int> nodeDictionary;
    // int graphSize = 0;
    // while(getline(file, input)) {        
        
    //     vector <string> device = split(input, ' ');
    //     device[0].pop_back(); // Remove ':'

    //     nodeDictionary.insert({device[0], graphSize + 1});
        
    //     graphSize++;
    // }
    
    // // Include node "out"
    // nodeDictionary.insert({"out", graphSize + 1});
    // graphSize++; 

    // file.close();
    // file.open(fileName);
    // vector<vector<int>> edgeList;
    // for(int line = 0; getline(file, input); line++) {        
        
    //     vector <string> device = split(input, ' ');
    //     device[0].pop_back(); // Remove ':'
        
    //     for(int output = 1; output < device.size(); output++) {
    //         edgeList.push_back({line + 1, nodeDictionary.at(device[output])});
    //     }
 
    // }

    // int source = nodeDictionary.at("svr");
    // int destination = nodeDictionary.at("out");

    // int answer = countPaths(graphSize, edgeList, source, destination);
    // cout << "\n\nAnswer: " << answer;
    
    file.close();
    return 0;
    
}
