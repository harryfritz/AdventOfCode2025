#include <bits/stdc++.h>
using namespace std;

string input;

// globals
vector<int> JOLTAGES;
vector<vector<int>> BUTTONS;

unordered_map<string, vector<pair<int, vector<int>>>> combosByPattern;
unordered_map<string, long long> cache;

// helpers
string joinVector(const vector<int>& v) {
    string s;
    for (size_t i = 0; i < v.size(); i++) {
        s += to_string(v[i]);
        if (i != v.size() - 1) s += ",";
    }
    return s;
}

vector<string> split(const string& s, char delim) {
    vector<string> tokens;
    string token;
    stringstream ss(s);
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

// parsing //////////////////////////////////////////////////////////

void setJoltages(const string& text) {
    JOLTAGES.clear();

    string inner = text.substr(1, text.size() - 2);
    vector<string> tokens = split(inner, ',');

    for (auto& t : tokens) {
        JOLTAGES.push_back(stoi(t));
    }
}

vector<int> createButton(const string& text) {
    vector<int> button;

    string inner = text.substr(1, text.size() - 2);
    vector<string> tokens = split(inner, ',');

    for (auto& t : tokens) {
        button.push_back(stoi(t));
    }

    return button;
}

void parseInputLine(const string& line) {
    vector<string> tokens = split(line, ' ');

    tokens.erase(tokens.begin()); // remove "lights"

    setJoltages(tokens.back());
    tokens.pop_back();

    BUTTONS.clear();

    for (auto& token : tokens) {
        BUTTONS.push_back(createButton(token));
    }
}

// patterns //////////////////////////////////////////////////////////

string patternFromJoltage(const vector<int>& joltage) {
    string pattern;
    for (int j : joltage) {
        pattern += to_string(j % 2);
    }
    return pattern;
}

void fillPatternsAndCombosWith(int bitwiseCombo) {
    int presses = 0;
    vector<int> joltage(JOLTAGES.size(), 0);

    for (int buttonIndex = 0; buttonIndex < (int)BUTTONS.size(); buttonIndex++) {

        int adjustedIndex = BUTTONS.size() - 1 - buttonIndex;
        int val = bitwiseCombo >> adjustedIndex;

        if ((val & 1) != 1) continue;

        presses++;

        const vector<int>& button = BUTTONS[buttonIndex];

        for (int idx : button) {
            joltage[idx] += 1;
        }
    }

    string pattern = patternFromJoltage(joltage);

    combosByPattern[pattern].push_back({presses, joltage});
}

void fillPatternsAndCombos() {
    combosByPattern.clear();

    int total = 1 << BUTTONS.size();

    for (int i = 0; i < total; i++) {
        fillPatternsAndCombosWith(i);
    }
}

// search //////////////////////////////////////////////////////////

long long countPresses(const vector<int>& target);

long long search() {
    cache.clear();
    return countPresses(JOLTAGES);
}

long long countPresses(const vector<int>& target) {
    string key = joinVector(target);

    if (cache.count(key)) return cache[key];

    bool onlyZeros = true;

    for (int j : target) {
        if (j < 0) return LLONG_MAX;
        if (j > 0) onlyZeros = false;
    }

    if (onlyZeros) return 0;

    string pattern = patternFromJoltage(target);

    long long total = LLONG_MAX;

    if (!combosByPattern.count(pattern)) {
        cache[key] = total;
        return total;
    }

    for (auto& combo : combosByPattern[pattern]) {
        int presses = combo.first;
        const vector<int>& comboJoltage = combo.second;

        vector<int> halfTarget(JOLTAGES.size());

        for (size_t i = 0; i < JOLTAGES.size(); i++) {
            halfTarget[i] = (target[i] - comboJoltage[i]) / 2;
        }

        long long result = countPresses(halfTarget);

        if (result != LLONG_MAX) {
            long long totalPresses = presses + 2 * result;
            total = min(total, totalPresses);
        }
    }

    cache[key] = total;
    return total;
}

// main //////////////////////////////////////////////////////////

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream file("input.txt");
    string line;
    vector<string> lines;

    while (getline(file, line)) {
        if (!line.empty())
            lines.push_back(line);
    }

    long long result = 0;

    for (const string& rawLine : lines) {
        
        parseInputLine(rawLine);
        
        fillPatternsAndCombos();
        
        result += search();
    }

    cout << "the answer is " << result << "\n";

    return 0;
}