/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 1 - Part two
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

int partition(vector<int> &vec, int low, int high) {
    int pivot = vec[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    vector <int> leftColumn, rightColumn;
    while(getline(file, input)) {

        vector <string> IDs = split(input, ' ');
        
        // build leftColumn and rightColumns vectors
        leftColumn.push_back(stoi(IDs[0]));
        rightColumn.push_back(stoi(IDs[1]));
        
    }

    // Sort leftColumn and rightColumn
    quickSort(leftColumn, 0, leftColumn.size() - 1);
    quickSort(rightColumn, 0, rightColumn.size() - 1);

    // Traverse leftColumn
    //      Traverse rightColumn starting on last position (since both are sorted)
    //      Increase multiplier for every position found where left == right
    //      Increase SimilarityScore acordingly with multiplier
    int cursor = 0;
    long long answer = 0;
    int multiplier = 0;
    for(int left = 0; left < leftColumn.size(); left++) {
        
        if(left >= 1){
            if(leftColumn[left] == leftColumn[left - 1]) {
                answer += leftColumn[left] * multiplier;
            } else {
                multiplier = 0;
            }
        }

        if(multiplier == 0) {
            int rightID = rightColumn[cursor];
            while(rightID <= leftColumn[left] && cursor < rightColumn.size() - 1) {
                if(rightID == leftColumn[left]) multiplier++;
                if(cursor < rightColumn.size() - 1) cursor++; 
                rightID = rightColumn[cursor];
            }
            answer += leftColumn[left] * multiplier;
        }
        
    } 

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}