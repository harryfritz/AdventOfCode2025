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

bool isBtnCombCorrect(vector <int>& btnComb, vector <vector <int>>& buttons, vector <int>& joltages){

    vector <int> joltagesTry;
    for(int i = 0; i < joltages.size(); i++){
        joltagesTry.push_back(0);
    }

    for(int i = 0; i < btnComb.size(); i++){
        for(int k = 0; k < joltagesTry.size(); k++){
            joltagesTry[k] += btnComb[i] * buttons[i][k];
        }
    }

    for(int i = 0; i < joltagesTry.size(); i++){
        if(joltagesTry[i] != joltages[i]){
            return false;
        }
    }
    
    return true;
}

void combinationUtil(vector <vector <int>>& machine, int ind, int r, 
                        vector <vector <vector <int>>>& combinations, vector <vector <int>>& dataArr) {
    int n = machine.size();

    if(ind == 0){
        dataArr.clear();
        combinations.clear();
    }
    
    if (dataArr.size() == r) {
        combinations.push_back(dataArr);
        return;
    }

    for(int i = ind; i < n; i++) {
        dataArr.push_back(machine[i]);
        combinationUtil(machine, i + 1, r, combinations, dataArr);
        dataArr.pop_back();
    }
}

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

int determinant(vector <vector <int>>& matrix){

    if(matrix.size() == 2){
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    int det = 0;
    for(int j = 0; j < matrix[0].size(); j++){
        vector <vector <int>> minor = matrix;

        minor.erase(minor.begin());
        for(int i = 0; i < minor.size(); i++){
            minor[i].erase(minor[i].begin() + j);
        }

        if(j % 2 == 0){
            det += matrix[0][j] * determinant(minor);
        } else {
            det -= matrix[0][j] * determinant(minor);
        }
    }

    return det;

}

Fraction determinantF(vector <vector <Fraction>>& matrix){

    if(matrix.size() == 2){
        return matrix[0][0].mult(matrix[1][1]).sub(matrix[0][1].mult(matrix[1][0]));
    }

    Fraction det = Fraction(0,1);
    for(int j = 0; j < matrix[0].size(); j++){
        vector <vector <Fraction>> minor = matrix;

        minor.erase(minor.begin());
        for(int i = 0; i < minor.size(); i++){
            minor[i].erase(minor[i].begin() + j);
        }

        if(j % 2 == 0){
            det = det.add(matrix[0][j].mult(determinantF(minor)));
        } else {
            det = det.sub(matrix[0][j].mult(determinantF(minor)));
        }
    }

    return det;

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

vector <int> cramerSolve(vector <vector <int>>& A, vector <int>& B){
    vector <int> X;

    int detA = determinant(A);

    for(int x = 0; x < B.size(); x++){
        vector <vector <int>> Ab = A;
        for(int i = 0; i < B.size(); i++){
            Ab[i][x] = B[i];
        }
        X.push_back(determinant(Ab) / detA);
    }

    return X;

}

void interchangeRows(vector <Fraction>& row1, vector <Fraction>& row2){
    vector <Fraction> rowBuff = row2;
    row2 = row1;
    row1 = rowBuff;
}

vector <vector <Fraction>> interchangeCols(vector <vector <Fraction>> M, int col1, int col2){
    for(int i = 0; i < M.size(); i++){
        Fraction x = M[i][col1];
        M[i][col1] = M[i][col2];
        M[i][col2] = x;
    }

    return M;
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

    //Build extended Matrix
    for(int i = 0; i < A.size(); i++){
        A[i].push_back(B[i]);
    }
    
    // printMatrix("A", A);
    
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
        // printMatrix("A", A);

        //Elimination
        for(int i = col + 1; i < A.size(); i++){
            if(A[i][col].num != 0){
                addSubTwoRows(A[i], multRowbyConstant(A[col], A[i][col].mult(Fraction(-1,1))), true);
            }
        }
        // printMatrix("A", A);
    }

    for(int col = A[0].size() - 2; col >= 0; col--){
        //Backwards Elimination - UP
        for(int i = col - 1; i >= 0; i--){
            if(A[i][col].num != 0){
                addSubTwoRows(A[i], multRowbyConstant(A[col], A[i][col].mult(Fraction(-1,1))), true);
            }
        }
        // printMatrix("A", A);
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
                // X[i].push_back(Fraction(1,1));
            } else {
                X[i].push_back(A[i][p].mult(Fraction(-1,1)));
            }
        }
    }

    // printMatrix("A", A);
    return X;

}

int main() {
  
    ifstream file;
    file.open("input.txt");
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

    vector <vector <int>> base;
    
    int answer = 0;
    for(int machine = 0; machine < buttons.size(); machine++){
        
        
        int totalPresses = 0;
        for(int jolt : joltages[machine]){
            totalPresses += jolt;
        }
        cout << "\n\nMachine " << machine << " - MaxPresses: " << totalPresses;        
        
        //Case Example Machine 0
        for(int i = 0; i < buttons[machine].size(); i++){
            while(buttons[machine][i].size() < buttons[machine].size()){
                buttons[machine][i].push_back(0);
            }
        }
        while(joltages[machine].size() < buttons[machine].size()){
            joltages[machine].push_back(0);
        }

        //Case Example Machine 2
        while(buttons[machine].size() < buttons[machine][0].size()){
            buttons[machine].push_back({});
            for(int i : buttons[machine][0]){
                buttons[machine][buttons[machine].size() - 1].push_back(0);
            }
        }
        
        // combinationUtil(buttons[machine], 0, joltages[machine].size(), btnComb, dataArr);
        
        vector <vector <int>> transp = transpose(buttons[machine]);
        vector <vector <Fraction>> btnCombF;

        for(int i = 0; i < transp.size(); i++){
            btnCombF.push_back({});
            for(int j = 0; j < transp[i].size(); j++){
                btnCombF[i].push_back(itof(transp[i][j]));
            }
        }

        vector <Fraction> joltagesF;
        for(int i = 0; i < joltages[machine].size(); i++){
            joltagesF.push_back(itof(joltages[machine][i]));
        }

        
        // printMatrix("btn", btnCombF);
        
        
        Fraction det = determinantF(btnCombF);
        cout << " - Det(btnCombF)=" + det.show();
        bool isBtnCombValid = true;
        if(det.num == 0){
            for(int i = 0; i < btnCombF.size() && isBtnCombValid; i++){
                vector <vector <Fraction>> btnCombFi = replaceColWithArray(btnCombF, i, joltagesF);
                Fraction detI = determinantF(btnCombFi);
                cout << " - Det(btnCombF" << i << ")=" + detI.show();
                if(detI.num != 0){
                    isBtnCombValid = false;
                    cout << " - BtnComb Invalid";
                }
            }
        } 

        if(isBtnCombValid){
            cout << " - BtnComb Valid";

            vector <vector <Fraction>> X;
            X = gaussEliminationSolve(btnCombF, joltagesF);
            printMatrix("X", X);

            bool isXValid = true;
            for(int i = 0; i < X.size(); i++){
                if(X[i][0].num < 0){
                    isXValid = false;
                    cout << "\n\tResult invalid";
                }
            }

            if(isXValid){
                cout << "\n\tResult Valid: ";

                Fraction pressesF = Fraction(0,1);
                for(vector <Fraction> row : X){
                    for(Fraction x : row){
                        pressesF = pressesF.add(x);
                    }
                }
                int presses = pressesF.num;
                cout << pressesF.show() << " Presses. Int=" << presses;
                
                if(presses < totalPresses){
                    totalPresses = presses;
                }

            }
            
        }
        
        answer += totalPresses;
    }
    
    cout << "\n\nAnswer: " << answer;
    
    
    file.close();
    return 0;
    
    // int answer = 0;
    // for(int machine = 0; machine < buttons.size(); machine++){
    //     int buttonsPressed = 100000;
    //     combinationUtil(buttons[machine], 0, joltages[machine].size(), btnComb, dataArr);
    //     for(vector <vector <int>> base : btnComb){
    //         if(determinant(base) != 0){
    //             vector <int> solution = cramerSolve(base, joltages[machine]);
    //             int sum = 0;
    //             for(int press : solution){
    //                 if(press < 0){
    //                     sum = 0;
    //                     break;
    //                 }
    //                 sum += press;
    //             }
    //             if(sum < buttonsPressed){
    //                 buttonsPressed = sum;
    //             }
    //         }
    //     }
    //     answer += buttonsPressed;
    // }
    // cout << "\n\nAnswer: " << answer;

    // int answer = 0;
    // for(int machine = 0; machine < buttons.size(); machine++){
        
    //     cout << "\nMachine " << machine;

    //     int presses = 0;
    //     for(int i = 0; i < joltages[machine].size(); i++){
    //         if(joltages[machine][i] > presses){
    //             presses = joltages[machine][i];
    //         }
    //     }

    //     int maxPresses = presses * joltages[machine].size();
    //     cout << " MaxPresses: " << maxPresses;
    //     bool found = false;
    //     while(presses < maxPresses && !found){

    //         cout << "\n\t" << presses << " presses";
            
    //         vector <int> btnPresses;
            
    //         for(int i = 0; i < presses; i++){
    //             btnPresses.push_back(1);
    //         }

    //         for(int i = 0; i < buttons[machine].size() - 1; i++){
    //             btnPresses.push_back(0);
    //         }

    //         sort(btnPresses.begin(), btnPresses.end());
    //         do {
    //             int acum = 0;
    //             vector <int> btnComb;
    //             for (int i = 0; i < btnPresses.size(); i++){
    //                 if(btnPresses[i] == 0){
    //                     btnComb.push_back(acum);
    //                     acum = 0;
    //                 } else if(btnPresses[i] == 1){
    //                     acum++;
    //                 }
    //                 if(i == btnPresses.size() - 1){
    //                     btnComb.push_back(acum);
    //                 }
    //             }

    //             if(isBtnCombCorrect(btnComb, buttons[machine], joltages[machine])){
    //                 found = true;
    //                 answer += presses;
    //             }

    //         } while (next_permutation(btnPresses.begin(), btnPresses.end()) && !found);

    //         presses++;
    //     }

    // }

    // cout << "\n\nAnswer: " << answer;

    file.close();
    return 0;
}