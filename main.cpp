#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

vector<double> probabilidades = { 0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,0.2,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,0.3,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,0.4,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,0.5,0.51,0.52,0.53,0.54,0.55,0.56,0.57,0.58,0.59,0.6,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,0.7,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.8,0.81,0.82,0.83,0.84,0.85, 0.86, 0.87,0.88,0.89,0.9,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99};

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

double fRand(double min, double max) {
    return min + ( fmod(rand(), ( max - min + 1 )) );
}

int iRand(int min, int max) {
    if (max <= 1) {
        return 0;
    }
    int range = max - min + 1;
    return rand() % range + min;
}

void addProbs(vector< vector<double> > &mat) {

    for (int i = 1; i < mat.size(); i++) {
        double currProb = 1.0;
        int j = 1;
        while (currProb > 0.00) {

            if (j >= mat[0].size()) {    
                j = 1;
            }

            if (i == j) {
                j++;
                continue;
            }

            int newIdx = iRand(0, currProb * 100);
            double prob = probabilidades[newIdx];

            currProb -= prob;
            mat[i][j] += prob;

            j++;
        }
    }
}

int main() {

    // This enable the unique random generation
    srand(time(NULL));

    cout << " BATTLEFIELD " << endl;

    int nTeams;

    cout << " Cuantos grupos van a pelear? : ";
    cin >> nTeams;

    // Creating the matrix and adding it's indexes
    vector< vector<double> > mat(nTeams + 1, vector<double>(nTeams + 1, 0.0));
    addIndexes(mat);
    addProbs(mat);

    printMat(mat);

    return 0;
}