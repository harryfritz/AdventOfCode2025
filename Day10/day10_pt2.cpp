/////////////////////////////////////////////////
//
// Advent of Code 2025
// Day 10 - Part one and two
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

using namespace std; 

class Fraction {

    private:
        int mdc(int n, int d) const {
            if(n < 0){
                n = -n;
            }
            if(d < 0){
                d = -d;
            }
            if(n < d){
                int x = n;
                n = d;
                d = x;
            }

            vector <int> euclid = {n, d};
            for(int i = 1; euclid[i] != 0; i++){
                euclid.push_back(euclid[i-1] % euclid[i]);
            }

            return euclid[euclid.size() - 2];
        }

        Fraction simplify(const Fraction& x) const {
            int newNum = x.num;
            int newDen = x.den;

            int max = mdc(newNum, newDen);
            while(max > 1){
                newNum = newNum / max;
                newDen = newDen / max;
                max = mdc(newNum, newDen);
            }

            if(newNum == newDen){
                return Fraction(1,1);
            } else if(newNum == 0){
                return Fraction(0,1);
            } else if(newDen < 0){
                return Fraction(-newNum, -newDen);
            } else {
                return Fraction(newNum, newDen);
            }
        }

    public:
        int num;
        int den;

        Fraction(int n, int d) : num(n), den(d) {}

        Fraction add(const Fraction& another) const {
            int newNum = num * another.den + den * another.num;
            int newDen = den * another.den;

            return simplify(Fraction(newNum, newDen));
        }

        Fraction sub(const Fraction& another) const {
            int newNum = num * another.den - den * another.num;
            int newDen = den * another.den;

            return simplify(Fraction(newNum, newDen));
        }

        Fraction mult(const Fraction& another) const {
            int newNum = num * another.num;
            int newDen = den * another.den;

            return simplify(Fraction(newNum, newDen));
        }

        Fraction div(const Fraction& another) const {
            int newNum = num * another.den;
            int newDen = den * another.num;

            return simplify(Fraction(newNum, newDen));
        }

        string show(){
            if(den == 1){
                return to_string(num);
            } else {
                return to_string(num) + "/" + to_string(den);
            }
        }

        bool compare(const Fraction& x, const string op) const {
            Fraction a = simplify(Fraction(num, den));
            Fraction b = simplify(x);
            
            if(op == "=="){
                if(a.num == b.num && a.den == b.den){
                    return true;
                } else {
                    return false;
                }
            } else if(op == "!="){
                if(a.num != b.num || a.den != b.den){
                    return true;
                } else {
                    return false;
                }
            } 
            
            float af = (float) a.num / (float) a.den;
            float bf = (float) b.num / (float) b.den;
            if(op == ">"){
                if(af > bf){
                    return true;
                } else {
                    return false;
                }
            } else if(op == ">="){
                if(af >= bf){
                    return true;
                } else {
                    return false;
                }
            } else if(op == "<"){
                if(af < bf){
                    return true;
                } else {
                    return false;
                }
            } else if(op == "<="){
                if(af <= bf){
                    return true;
                } else {
                    return false;
                }
            }

            return false;
        }

};


void printMatrix(string name, vector <vector <Fraction>>& M){
    cout << "\n" << name << ": ";
    for(vector <Fraction> row : M){
        for(Fraction m : row){
            cout << "\t" << m.show();
        }
        cout << "\n";
    }
}

void printArray(string name, vector <Fraction>& V){
    cout << "\n" << name << ": ";
    for(Fraction m : V){
        cout << "\t" << m.show();
    }
}

vector <vector <int>> transpose(vector <vector <int>> M){
    for(int i = 0; i < M.size(); i++){
        for(int j = 0; j < i; j++){
            int x = M[i][j];
            M[i][j] = M[j][i];
            M[j][i] = x;
        }
    }

    return M;
}

Fraction itof(int i){
    return Fraction(i,1);
}

void interchangeRows(vector <Fraction>& row1, vector <Fraction>& row2){
    vector <Fraction> rowBuff = row2;
    row2 = row1;
    row1 = rowBuff;
}

vector <vector <Fraction>> replaceColWithArray(vector <vector <Fraction>> M, int col, vector <Fraction> arr){
    for(int i = 0; i < M.size(); i++){
        M[i][col] = arr[i];
    }

    return M;
}

void addSubTwoRows(vector <Fraction>& row1, vector <Fraction> row2, bool add){
    if(add){
        for(int i = 0; i < row1.size(); i++){
            row1[i] = row1[i].add(row2[i]);
        }
    } else {
        for(int i = 0; i < row1.size(); i++){
            row1[i] = row1[i].sub(row2[i]);
        }
    }
}

vector <Fraction> multRowbyConstant(vector <Fraction> row, Fraction k){
    for(int i = 0; i < row.size(); i++){
        row[i] = row[i].mult(k);
    }
    return row;
}

vector <vector <Fraction>> gaussEliminationSolve(vector <vector <Fraction>> A, vector <Fraction>& B){
    vector <vector <Fraction>> X;

    bool printSteps = true;

    //Build extended Matrix
    for(int i = 0; i < A.size(); i++){
        A[i].push_back(B[i]);
    }
    
    if(printSteps) printMatrix("A", A);
    
    for(int col = 0; col < A[0].size() - 1; col++){

        //Make sure A[col][col] = 1
        for(int i = col + 1; A[col][col].num == 0 && i < A.size(); i++){
            if(A[i][col].num != 0){
                interchangeRows(A[col], A[i]);
            }
        }
        for(int i = col + 1; A[col][col].num != A[col][col].den && i < A.size(); i++){
            if(A[i][col].num == A[i][col].den){
                interchangeRows(A[col], A[i]);
            }
        }
        if(A[col][col].num == 0){
            //Pivot!
        } else if(A[col][col].num != A[col][col].den){
            A[col] = multRowbyConstant(A[col], Fraction(1,1).div(A[col][col]));
        }
        if(printSteps) printMatrix("A", A);

        //Elimination
        for(int i = col + 1; i < A.size(); i++){
            if(A[i][col].num != 0){
                addSubTwoRows(A[i], multRowbyConstant(A[col], A[i][col].mult(Fraction(-1,1))), true);
            }
        }
        if(printSteps) printMatrix("A", A);
    }

    for(int col = A[0].size() - 2; col >= 0; col--){
        //Backwards Elimination - UP
        for(int i = col - 1; i >= 0; i--){
            if(A[i][col].num != 0){
                addSubTwoRows(A[i], multRowbyConstant(A[col], A[i][col].mult(Fraction(-1,1))), true);
            }
        }
        if(printSteps) printMatrix("A", A);
    }

    for(int i = 0; i < A.size(); i++){
        X.push_back({A[i][A[i].size() - 1]});
    }

    vector <int> pivots;
    for(int i = 0; i < A.size(); i++){
        bool zeroCol = true;
        for(int j = 0; j < A[i].size() - 1 && zeroCol; j++){
            if(A[i][j].num != 0){
                zeroCol = false;
            }
        }
        if(zeroCol){
            pivots.push_back(i);
        }
    }

    for(int p : pivots){
        for(int i = 0; i < A.size(); i++){
            if(i == p){
                X[i].push_back(Fraction(1,1));
            } else {
                X[i].push_back(A[i][p].mult(Fraction(-1,1)));
            }
        }
    }

    if(printSteps) printMatrix("X", X);
    return X;

}

int main() {
  
    ifstream file;
    file.open("example.txt");
    string input;

    vector <vector <int>> joltages;
    vector <vector <vector <int>>> buttons;

    cout << "\n\nInput:";
    for(int i = 0; getline(file, input); i++){
        cout << "\n" + input;
        
        joltages.push_back({});
        string joltagesStr = input.substr(input.find("{") + 1, input.find("}") - input.find("{") - 1);
        int comma = 0;
        for(int k = 0; k < joltagesStr.size() && comma != -1;){
            comma = joltagesStr.find(',', k);
            joltages[i].push_back(stoi(joltagesStr.substr(k, comma - k)));
            k = comma + 1;
        }

        string button = input.substr(input.find("]") + 1, input.find("{") - input.find("]") - 1);
        buttons.push_back({});
        int j = -1;
        for(int c = 0; c < button.size(); c++){
            if(button[c] == '('){
                buttons[i].push_back({});
                j++;
                for(int k = 0; k < joltages[i].size(); k++){
                    buttons[i][j].push_back(0);
                }
            }
            if(button[c] >= '0' && button[c] <= '9'){
                buttons[i][j][button[c] - 48] = 1;
            }
        }
    }

    cout << "\n";
    Fraction answer = Fraction(0,1);
    // for(int machine = 0; machine < buttons.size(); machine++){
    for(int machine = 0; machine < 1; machine++){
        
        
        Fraction totalPresses = Fraction(0,1);
        for(int jolt : joltages[machine]){
            totalPresses.num += jolt;
        }
        cout << "\n\nMachine " << machine << " - MaxPresses: " << totalPresses.show();        

        //Case Example Machine 2
        while(buttons[machine].size() < buttons[machine][0].size()){
            buttons[machine].push_back({});
            for(int i : buttons[machine][0]){
                buttons[machine][buttons[machine].size() - 1].push_back(0);
            }
        }
        
        vector <vector <Fraction>> btnCombF;
        if(buttons[machine].size() == buttons[machine][0].size()){
            vector <vector <int>> transp = transpose(buttons[machine]);
            for(int i = 0; i < transp.size(); i++){
                btnCombF.push_back({});
                for(int j = 0; j < transp[i].size(); j++){
                    btnCombF[i].push_back(itof(transp[i][j]));
                }
            }
        } else {

        }
        
        vector <Fraction> joltagesF;
        for(int i = 0; i < joltages[machine].size(); i++){
            joltagesF.push_back(itof(joltages[machine][i]));
        }

        // printMatrix("btn", btnCombF);

        vector <vector <Fraction>> X;
        X = gaussEliminationSolve(btnCombF, joltagesF);
        printMatrix("X", X);

        
        vector <Fraction> result;
        for(int i = 0; i < X.size(); i++){
            result.push_back(X[i][0]);
        }
        
        
        Fraction maxResult = Fraction(0,1);
        for(Fraction f : result){
            if(f.compare(maxResult, ">")){
                maxResult = f;
            }
        }
        for(int j = 1; j < X[0].size(); j++){
            for(Fraction t = Fraction(0,1); t.compare(maxResult, "<"); t = t.add(Fraction(1,1))){
            
                bool allPos = true;
                Fraction presses = Fraction(0,1);

                for(int i = 0; i < result.size() && allPos; i++){
                    result[i] = result[i].add(X[i][j].mult(t));
                    presses = presses.add(result[i]);
                    if(result[i].num < 0){
                        allPos = false;
                    }
                }

                if(allPos && presses.compare(totalPresses, "<")){
                    totalPresses = presses;
                }
                
            }
        }
        
        cout << totalPresses.show() << " Presses";
                
        answer = answer.add(totalPresses);
    }
    
    cout << "\n\nAnswer: " << answer.show();
    
    
    file.close();
    return 0;
    
}