#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void addIndexes(vector< vector<double> > &mat) {

    int cont = 1;

    for (int i = 1; i < mat.size(); i++) {
        mat[0][i] = cont;
        mat[i][0] = cont;
        cont++;
    }
}

void printMat(vector< vector<double> > mat) {

    for (int i = 0; i < mat.size(); i++) {
        
        for (int j = 0; j < mat[0].size(); j++) {
            if (i == 0 && j == 0) {
                cout << "    ";
                continue;
            }
            if (i == 0 || j == 0) {
                if (i == 0) {
                    cout << int(mat[i][j]) << "    ";
                } else {
                    cout << int(mat[i][j]) << " ";
                }
            } else {
                cout << setprecision(2) << fixed;
                cout << mat[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {

    cout << " BATTLEFIELD " << endl;

    int nTeams;

    cout << " Cuantos grupos van a pelear? : ";
    cin >> nTeams;

    // Creating the matrix and adding it's indexes
    vector< vector<double> > mat(nTeams + 1, vector<double>(nTeams + 1, 0.0));
    addIndexes(mat);

    
    printMat(mat);

    return 0;
}