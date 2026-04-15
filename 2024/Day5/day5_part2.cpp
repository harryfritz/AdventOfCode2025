
/////////////////////////////////////////////////
//
// Advent of Code 2024
// Day 5 - Part two
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

// Returns all pairs of the specified page found in the rules list
vector <int> getRules(vector <vector <int>>& rules, int page) {
    vector <int> secondPages;
    for(vector <int> rule : rules) {
        if(rule[0] == page) secondPages.push_back(rule[1]);
    }
    return secondPages;
}

// Returns middle element of vector with odd size
int middleElement(vector <int>& arr) {
    return arr[arr.size() / 2];
}

void swapPages(vector <int>& update, int page1Index, int page2Index) {
    int temp = update[page1Index];
    update[page1Index] = update[page2Index];
    update[page2Index] = temp;
}

// Builds string from vector <int> assuming all elements are two-digits
string printUpdate(vector <int>& update) {
    string s = "";
    int size = update.size();
    for(int page = 0; page < size; page++) {
        s.push_back('0' + update[page]/10);
        s.push_back('0' + update[page]%10);
        if(page < size - 1) s.push_back(',');
    }
    return s;
}

int main() {
  
    ifstream file;
    file.open("input.txt");
    string input;

    vector <vector <int>> rules;
    vector <vector <int>> updates;
    bool ruleSection = true;
    while(getline(file, input)) {

        // cout << "\n" << input;

        if(input == "") {
            ruleSection = false;
        } else {
            if(ruleSection) {
                vector <int> rule;
                for(string s : split(input, '|')) {
                    rule.push_back(stoi(s));
                }
                rules.push_back(rule);
            } else {
                vector <int> update;
                for(string s : split(input, ',')) {
                    update.push_back(stoi(s));
                }
                updates.push_back(update);
            }
        }
    
    }

     
    vector <vector <int>> incorrectUpdates;
    for(vector <int> update : updates) {
        cout << "\n" << printUpdate(update) << " - ";
        bool correct = true;
        for(int page = 0; page < update.size() && correct; page++) {
            for(int secondPage : getRules(rules, update[page])) {
                for(int cursor = page - 1; cursor >= 0 && correct; cursor--){
                    if(update[cursor] == secondPage) correct = false;
                }
            }
        }
        
        if(correct) {
            cout << "Correct";
        } else {
            cout << "Incorrect";
            incorrectUpdates.push_back(update);
        }
    }

    cout << "\n\nIncorrects:";
    long long answer = 0;
    for(vector <int> update : incorrectUpdates) {
        cout << "\n" << printUpdate(update) << " -> ";
        
        bool correct = false;
        while(!correct) {
            correct = true;
            for(int page = 0; page < update.size() && correct; page++) {
                for(int secondPage : getRules(rules, update[page])) {
                    for(int cursor = page - 1; cursor >= 0 && correct; cursor--){
                        if(update[cursor] == secondPage) {
                            correct = false;
                            swapPages(update, page, cursor);
                        } 
                    }
                }
            }
        }
        
        cout << printUpdate(update);
        answer += middleElement(update);
    }

    cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}
