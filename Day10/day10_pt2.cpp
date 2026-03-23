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
#include <cstdarg>

using namespace std; 

class Fraction {

    private:
        int num;
        int den;

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

    public:
        Fraction(int n, int d) : num(n), den(d) {}

        Fraction() : num(0), den(1) {}
        
        int getNum(){
            return num;
        }
        
        int getDen(){
            return den;
        }

        Fraction abs() const {
            return Fraction(std::abs(num), den);
        }

        friend std::ostream& operator<< (std::ostream& stream, Fraction& F) {
            if(F.den == 1){
                stream << F.num;
            } else {
                stream << F.num << "/" << F.den;
            }
            return stream;
        }

        friend Fraction operator+(const Fraction& A, const Fraction& B){
            return A.add(B);
        }

        friend Fraction& operator+=(Fraction& A, const Fraction& B){
            A = A.add(B);
            return A;
        }

        friend Fraction operator-(const Fraction& A, const Fraction& B){
            return A.sub(B);
        }

        friend Fraction& operator-=(Fraction& A, const Fraction& B){
            A = A.sub(B);
            return A;
        }

        friend Fraction operator*(const Fraction& A, const Fraction& B){
            return A.mult(B);
        }

        friend Fraction& operator*=(Fraction& A, const Fraction& B){
            A = A.mult(B);
            return A;
        }

        friend Fraction operator/(const Fraction& A, const Fraction& B){
            return A.div(B);
        }

        friend Fraction& operator/=(Fraction& A, const Fraction& B){
            A = A.div(B);
            return A;
        }

        friend bool operator==(const Fraction& A, const Fraction& B){
            return A.compare(B, "==");
        }

        friend bool operator==(const Fraction& A, const int& B){
            return A.compare(Fraction(B,1), "==");
        }

        friend bool operator!=(const Fraction& A, const Fraction& B){
            return A.compare(B, "!=");
        }

        friend bool operator!=(const Fraction& A, const int& B){
            return A.compare(Fraction(B,1), "!=");
        }

        friend bool operator>(const Fraction& A, const Fraction& B){
            return A.compare(B, ">");
        }

        friend bool operator>(const Fraction& A, const int& B){
            return A.compare(Fraction(B,1), ">");
        }

        friend bool operator<(const Fraction& A, const Fraction& B){
            return A.compare(B, "<");
        }

        friend bool operator<(const Fraction& A, const int& B){
            return A.compare(Fraction(B,1), "<");
        }

        friend bool operator>=(const Fraction& A, const Fraction& B){
            return A.compare(B, ">=");
        }

        friend bool operator>=(const Fraction& A, const int& B){
            return A.compare(Fraction(B,1), ">=");
        }

        friend bool operator<=(const Fraction& A, const Fraction& B){
            return A.compare(B, "<=");
        }

        friend bool operator<=(const Fraction& A, const int& B){
            return A.compare(Fraction(B,1), "<=");
        }

};

class MatrixInt {

    private:
        vector <vector <int>> matrix;

    public:

        MatrixInt(vector <vector <int>> _matrix){
            matrix = _matrix;
        }

        MatrixInt(int rows, int columns){
            vector <int> _rows(rows, 0);
            matrix = vector(columns, _rows);
        }

        MatrixInt(){
            matrix.push_back({});
            matrix[0].push_back({});
        }

};

void printMatrix(string name, vector <vector <Fraction>>& M){
    cout << "\n" << name << ": ";
    for(vector <Fraction> row : M){
        for(Fraction m : row){
            cout << "\t" << m;
        }
        cout << "\n";
    }
}

void printArray(string name, vector <Fraction>& V){
    cout << "\n" << name << ": ";
    for(Fraction m : V){
        cout << "\t" << m;
    }
}

vector <vector <int>> transpose(vector <vector <int>>& M){
    
    int rows = M[0].size();
    int cols = M.size();
    
    vector <vector <int>> tM(rows, vector <int> (cols));
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            tM[i][j] = M[j][i];
        }
    }

    return tM;
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
            row1[i] += row2[i];
        }
    } else {
        for(int i = 0; i < row1.size(); i++){
            row1[i] -= row2[i];
        }
    }
}

vector <Fraction> multRowbyConstant(vector <Fraction> row, Fraction k){
    for(int i = 0; i < row.size(); i++){
        row[i] *= k;
    }
    return row;
}

vector <vector <Fraction>> gaussEliminationSolve(vector <vector <Fraction>> A, vector <Fraction>& B){

    bool printSteps = true;

    //Build extended Matrix
    for(int i = 0; i < A.size(); i++){
        A[i].push_back(B[i]);
    }
    
    if(printSteps){
        cout << "\nExtended Matrix";
        printMatrix("A", A);
    }
    
    for(int col = 0; col < A.size(); col++){

        //Make sure A[col][col] = 1
        for(int i = col + 1; A[col][col] == 0 && i < A.size(); i++){
            if(A[i][col] != 0){
                interchangeRows(A[col], A[i]);
            }
        }
        for(int i = col + 1; A[col][col] != 1 && i < A.size(); i++){
            if(A[i][col] == 1){
                interchangeRows(A[col], A[i]);
            }
        }
        
        if(A[col][col] != 1){
            A[col] = multRowbyConstant(A[col], Fraction(1,1) / A[col][col]);
        }
        
        if(printSteps){
            cout << "\nPivoting col " << col;
            printMatrix("A", A);
        }

        //Elimination
        for(int i = col + 1; i < A.size(); i++){
            if(A[i][col] != 0){
                addSubTwoRows(A[i], multRowbyConstant(A[col], A[i][col] * Fraction(-1,1)), true);
            }
        }
        
        if(printSteps){
            cout << "\nElimination col " << col;
            printMatrix("A", A);
        }
    }

    for(int col = A[0].size() - 1; col > 0; col--){
        int row = col;
        if(row >= A.size()){
            row = A.size() - 1;
        }
        
        bool validPivot = true;
        if(A[row][col] == 0){
            validPivot = false;
        } 
        for(int i = col - 1; i >= 0 && validPivot; i--){
            if(A[row][i] != 0){
                validPivot = false;
            } 
        }        
        
        if(validPivot){
            //Backwards Elimination - UP
            for(int i = row - 1; i >= 0; i--){
                if(A[i][col] != 0){
                    addSubTwoRows(A[i], multRowbyConstant(A[row], A[i][col] * Fraction(-1,1)), true);
                }
            }
        }

        if(printSteps){
            cout << "\nBackwards Elimination col " << col;
            printMatrix("A", A);
        }
    }
    
    vector <vector <Fraction>> X;
    for(int i = 0; i < A[0].size() - 1; i++){
        X.push_back({Fraction(0,1)});
    }

    vector <int> pivots;
    vector <int> nonPivots;
    for(int col = 0; col < A[0].size() - 1; col++){
        bool colPivot = true;
        int pivotPos = -1;
        
        for(int i = 0; i < A.size() && colPivot; i++){
            if(A[i][col] != 0){
                if(pivotPos == -1){
                    pivotPos = i;
                } else {
                    colPivot = false;
                }
            }
            if(i == A.size() - 1 && pivotPos == -1){
                colPivot = false;
            }
        }

        if(colPivot){
            X[col][0] = A[pivotPos][A[0].size() - 1];
            pivots.push_back(col);
        } else {
            nonPivots.push_back(col);
        }

    }
    
    for(int pivot = 0; pivot < nonPivots.size(); pivot++){
        for(int i = 0; i < X.size(); i++){
            X[i].push_back(Fraction(0,1));
        }
        X[nonPivots[pivot]][pivot + 1] = Fraction(1,1);

        for(int i = 0; i < pivots.size(); i++){
            X[pivots[i]][pivot + 1] = A[i][nonPivots[pivot]] * Fraction(-1,1);
        }

    }

    if(printSteps) printMatrix("X", X);
    return X;

}

vector <vector <Fraction>> matrixMult(vector <vector <Fraction>>& A, vector <vector <Fraction>>& B){
    vector <Fraction> cols(B[0].size(), Fraction(0,1));
    vector <vector <Fraction>> result(A.size(), cols);
    if(A[0].size() == B.size()){
        for(int row = 0; row < result.size(); row++){
            for(int col = 0; col < result[col].size(); col++){
                for(int i = 0; i < B.size(); i++){
                    result[row][col] += A[row][i] * B[i][col];
                }
            }
        }
    }

    return result;
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

    cout << "\n";
    Fraction answer = Fraction(0,1);

    // for(int machine = 0; machine < buttons.size(); machine++){
    for(int machine = 1; machine < 2; machine++){
        
        Fraction maxPresses = Fraction(0,1);
        for(int jolt : joltages[machine]){
            maxPresses += Fraction(jolt,1);
        }
        cout << "\n\nMachine " << machine << " - MaxPresses: " << maxPresses;        

        //Case Example Machine 2
        while(buttons[machine].size() < buttons[machine][0].size()){
            buttons[machine].push_back({});
            for(int i : buttons[machine][0]){
                buttons[machine][buttons[machine].size() - 1].push_back(0);
            }
        }
        
        vector <vector <Fraction>> btnCombF;
        vector <vector <int>> transp = transpose(buttons[machine]);
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

        vector <vector <Fraction>> X;
        X = gaussEliminationSolve(btnCombF, joltagesF);
        printMatrix("X", X);

        int maxDen = 1;
        for(int i = 0; i < X.size(); i++){
            for(int j = 0; j < X[i].size(); j++){
                if(X[i][j].getDen() > maxDen){
                    maxDen = X[i][j].getDen();
                }
            }
        }

        for(int i = 0; i < X.size(); i++){
            for(int j = 0; j < X[i].size(); j++){
                X[i][j] *= Fraction(maxDen,1);
            }
        }
        printMatrix("X", X);
        
        vector <Fraction> result;
        for(int i = 0; i < X.size(); i++){
            result.push_back(X[i][0]);
        }
        
        Fraction maxResult = Fraction(0,1);
        for(Fraction f : result){
            if(f.abs() > maxResult){
                maxResult = f.abs();
            }
        }
        
        Fraction totalPresses = Fraction(0,1);
        if(X[0].size() > 1){
            
            vector <vector <Fraction>> bounds;

            for(int j = 1; j < X[0].size(); j++){
                bounds.push_back({Fraction(),Fraction()});

                for(int i = 0; i < X.size(); i++){
                    if(X[i][j] > 0){
                        if(X[i][0] >= 0){
                            bounds[j-1][0] = Fraction(-X[i][0].getNum()/X[i][0].getNum(),1);
                            bounds[j-1][1] = maxPresses;
                        } else {
                            bounds[j-1][0] = Fraction(-X[i][0].getNum()/X[i][0].getNum() + 1,1);
                            bounds[j-1][1] = maxPresses;
                        }
                    } else if(X[i][j] < 0){
                        if(X[i][0] >= 0){
                            bounds[j-1][1] = Fraction(-X[i][0].getNum()/X[i][0].getNum(),1);
                        } else {
                            
                        }
                    }
                    
                }
                
                  
            }

        } else {
            for(int i = 0; i < X.size(); i++){
                totalPresses += X[i][0];
            }
        }
        
        cout << "\n" << totalPresses << " Presses";
        answer += totalPresses;
        
    }
    
    cout << "\n\nAnswer: " << answer;
    
    
    file.close();
    return 0;
    
}
