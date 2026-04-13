/////////////////////////////////////////////////
//
// Advent of Code - Useful methods and algorithms
// 
// Author: Fritz, M.H.
//
/////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

// Returns the number of digits of an integer
int digits(int id){
    int digits = 0;
    while (id) {
        id /= 10;
        digits++;
    }
    return digits;
}

// Returns the transposed of a matrix of Integers
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

// Return true if vector of integers contains at least one instance of value
bool vectorContains(vector <int>& vec, int value){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i] == value) return true;
    }
    return false;
}

//Point compression is missing


// Recursively populates 'combinations' with all combinations of 'r' elements of 'source'. 'dataArr' is a aux vector, mandatory
// 'ind' begins on '0' when calling for the first time
void combinationUtil(vector <vector <int>>& source, int ind, int r, 
                        vector <vector <vector <int>>>& combinations, vector <vector <int>>& dataArr) {
    int n = source.size();

    if(ind == 0) {
        dataArr.clear();
        combinations.clear();
    }
    
    if(dataArr.size() == r) {
        combinations.push_back(dataArr);
        return;
    }

    for(int i = ind; i < n; i++) {
        dataArr.push_back(source[i]);
        combinationUtil(source, i + 1, r, combinations, dataArr);
        dataArr.pop_back();
    }
}

// Return vector of strings as parts of 'text' separated by the 'delim' char (any amount of 'delim')
// Useful for processing puzzle inputs
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

// Class for working with Fractions as Integers (overrides operators, for example)
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

// Incomplete Class to work with Integer Matrixes (Or Fraction Matrixes)
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


// Converts Integer to Fraction
Fraction itof(int i){
    return Fraction(i,1);
}

// Prints a matrix of Integers
void printMatrix_old(vector<vector <int>>& matrix) {
    for(int i = 0; i < matrix.size(); i++){
        cout << "\n";
        for(int j = 0; j < matrix[i].size(); j++){
            cout << "\t" << matrix[i][j];
        }
    }
}

// Prints a matrix of Fractions with 'name'
void printMatrix(string name, vector <vector <Fraction>>& M){
    cout << "\n" << name << ": ";
    for(vector <Fraction> row : M){
        for(Fraction m : row){
            cout << "\t" << m;
        }
        cout << "\n";
    }
}

// Prints Array of Fractions with 'name'
void printArray(string name, vector <Fraction>& V){
    cout << "\n" << name << ": ";
    for(Fraction m : V){
        cout << "\t" << m;
    }
}

// Intercharge two rows (as array references)
void interchangeRows(vector <Fraction>& row1, vector <Fraction>& row2){
    vector <Fraction> rowBuff = row2;
    row2 = row1;
    row1 = rowBuff;
}

// Replaces Matrix M column with array (used for Gauss Elimination)
vector <vector <Fraction>> replaceColWithArray(vector <vector <Fraction>>& M, int col, vector <Fraction>& arr){
    for(int i = 0; i < M.size(); i++){
        M[i][col] = arr[i];
    }

    return M;
}

// Adds or subtracts two given arrays (result returns in the first)
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

// Multiplies row by constant
vector <Fraction> multRowbyConstant(vector <Fraction>& row, Fraction k){
    for(int i = 0; i < row.size(); i++){
        row[i] *= k;
    }
    return row;
}

// Performs Gauss Elimination on Matrix A, using Array B as constant
vector <vector <Fraction>> gaussEliminationSolve(vector <vector <Fraction>>& A, vector <Fraction>& B){

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

// Multiplies two Matrixes (no consistency check, can overflow)
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

// Performs Recursive DFS search.
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

// Performs Iterative DFS with a stack (no recursion)
void DfsIterative(int start, int finish, const std::vector<std::vector<int>>& graph, long long &count) {
    
    std::vector<bool> visited(graph.size(), false);  // Initialize visited array
    std::stack<int> stk;  // Create a stack for DFS

    stk.push(start);  // Push the starting node

    while (!stk.empty()) {
        int node = stk.top();
        stk.pop();

        if (!visited[node]) {
            visited[node] = true;  // Mark the node as visited
            
            // Push all unvisited neighbors onto the stack
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    stk.push(neighbor);
                    visited[node] = false;
                }
            }

            if(node == finish) {
                count++;
                visited[node] = false;
            }

            // visited[node] = false;
        }
    }
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
    cout << "\n";
    
    while(getline(file, input)){
        cout << "\n" + input;
    }
    
    file.close();

    return 0;
}