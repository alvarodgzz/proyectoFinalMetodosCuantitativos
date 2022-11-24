#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <float.h>
#include <cstdlib>

using namespace std;

int nTeams;
vector<int> teams;

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

double fRand(double a, double b) {
  float random = ((float) rand()) / (float) RAND_MAX;
  float diff = b - a;
  float r = random * diff;
  return a + r;
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

void endGame(int winner) {
    cout << "==========================================" << endl;
    cout << "Group " << winner << " is the winner!" << endl;
    cout << "==========================================" << endl;
    exit(0);
}

void teamsCheck(vector< vector<double> > &mat, vector<int> &guerreros) {

    vector< vector<double> >::iterator itMat;
    itMat = mat.begin();
    ++itMat;

    int colIdx = 0;

    bool teamDown = false;

    int teamDefeated = 0;

    for (auto it = guerreros.begin(); it != guerreros.end(); ++it) {
      if (*it <= 0) {

        teamDefeated = mat[0][colIdx + 1];

        guerreros.erase(it);
        teams.erase(remove(teams.begin(), teams.end(), colIdx + 1), teams.end());
        mat.erase(remove(mat.begin(), mat.end(), *itMat), mat.end());
        teamDown = true;

        break;
      }
      itMat++;
      colIdx++;
    }

    if (teamDown) {

      for (int i = 0; i < mat.size(); i++) {
          mat[i].erase(std::remove(mat[i].begin(), mat[i].end(), mat[i][colIdx + 1]), mat[i].end());
      }
        cout << "Group " << teamDefeated << " is annihilated!" << endl;
      cout << "==========================================" << endl;

      if (guerreros.size() == 1) {
        endGame(teams[0]);
      }
      cout << "Reconfiguring stochastic matrix" << endl;
      printMat(mat);
    }

}

void runGame(vector< vector<double> > &mat, vector<int> &guerreros) {

    // Teams check, if a team runs out of warriors we need to refactor de matrix
    teamsCheck(mat, guerreros);

    // Playing team
    int actTeam = iRand(1, mat[0].size() - 1);
    double victimTeam = fRand(0.01, 0.99);

    double minDiff = DBL_MAX;
    int attackTo = -1;

    //do {
      for (int i = 1; i < mat[0].size(); i++) {
        if (actTeam == i) {
          cout << "ëntra" << endl;
          continue;
        }
        double actDiff = abs(victimTeam - mat[actTeam][i]);
        if (actDiff < minDiff) {
          minDiff = actDiff;
          attackTo = i;
        }
      }
    //} while (actTeam == attackTo);

    cout << "Group " << mat[actTeam][0] << " attacked " << mat[0][attackTo] << endl;
    guerreros[attackTo - 1] -= 1;
}

int main() {

    // This enable the unique random generation
    srand(time(NULL));

    cout << " BATTLEFIELD " << endl;

    // Number of teams that will battle
    int nTeams;
    cout << " Cuantos grupos van a pelear? : ";
    cin >> nTeams;

    // Number of warriors per team
    vector<int> guerreros(nTeams, 0);
    for (int i = 0; i < nTeams; i++) {
        teams.push_back(i + 1);
        cout << " Cuantos guerreros tiene el grupo " << i + 1 << ": ";
        int nGuerreros;
        cin >> nGuerreros;
        guerreros[i] = nGuerreros;
    }

    // Creating the matrix and adding it's indexes
    vector< vector<double> > mat(nTeams + 1, vector<double>(nTeams + 1, 0.0));
    addIndexes(mat);
    addProbs(mat);

    printMat(mat);

    cout << "Number of warrios for each group " << endl;
    for (int i = 0; i < guerreros.size(); i++) {
        cout << "Group " << i + 1 << ": " << guerreros[i] << endl;
    }
    cout << "==========================================" << endl;


    while (!guerreros.empty()) {

      runGame(mat, guerreros);

      cout << "Number of warrios for each group " << endl;
      for (int i = 0; i < guerreros.size(); i++) {
          cout << "Group " << mat[i + 1][0] << ": " << guerreros[i] << endl;
      }
      cout << "==========================================" << endl;
    }

    return 0;
}
