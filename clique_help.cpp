/*
 * <Copyright Alexandru Olteanu, grupa 322CA, alexandruolteanu2001@gmail.com>
 */
#include <bits/stdc++.h>
#include "task.h"
using namespace std;

const int maxn = 1e3;
const string oracleInputFile = "sat.cnf";
const string oracleOutputFile = "sat.sol";


/**
 * Aceasta clasa este o copie a clasei Retele, clasa construita pentru
 * a putea fi inclusa in fisierul reclame.cpp
 * */
class Retele : public Task {
    public:
        int n, m, k;
        int matrix[maxn][maxn] = {0};
        vector<int> solution;
        void solve() {
            read_problem_data();
            formulate_oracle_question();
            ask_oracle();
            decipher_oracle_answer();
            write_answer();
        }
        void read_problem_data() {
            cin >> n >> m >> k;
            for (int i = 1; i <= m; ++i) {
                int x, y;
                cin >> x >> y;
                matrix[x][y] = matrix[y][x] = 1;
            }
        }
        void formulate_oracle_question() {
            ofstream out (oracleInputFile);
            out << "p cnf " << k * n << " ";
            int clause = k;
            clause +=(n * n - 2 * m) * (k - 1) * k / 2; 
            clause += (k - 1) * k / 2 * n;
            clause += k * (n - 1) * n / 2;
            out << clause << '\n';
            for (int i = 1; i <= k; ++i) {
                for (int j = 1; j <= n; ++j) {
                    out << (i - 1) * n + j << " ";
                }
                out << "0\n";
            }
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (!matrix[i][j]) {
                        for (int t = 1; t < k; ++t) {
                            for (int t1 = t + 1; t1 <= k; ++t1) {
                                out << -((t - 1) * n + i) << " " << -((t1 - 1) * n + j) << " 0\n";
                            }
                        }

                    }
                }
            }
            for (int i = 1; i <= k; ++i) {
                for (int j = i + 1; j <= k; ++j) {
                    for (int t = 1; t <= n; ++t) {
                        out << -((i - 1) * n + t) << " " << -((j - 1) * n + t) << " 0\n";
                    }
                }
            }

            for (int i = 1; i <= k; ++i) {
                for (int j = 1; j <= n; ++j) {
                    for (int t = j + 1; t <= n; ++t) {
                        out << -((i - 1) * n + j) << " " << -((i - 1) * n + t) << " 0\n";
                    }
                }
            }
            out.close();

        }

        void decipher_oracle_answer() {
            ifstream in(oracleOutputFile);
            string s;
            in >> s;
            if (s == "True") {
                int length;
                in >> length;
                for (int i = 1; i <= n * k; ++i) {
                    int x; in >> x;
                    if (x > 0) {
                        x %= n;
                        if (x == 0)x = n;
                        solution.push_back(x);
                    }
                }
            }
            else {
                solution.push_back(-1);
            }
        }

        void write_answer() {
           if (solution[0] == -1) {
               cout << "False";
           }
           else {
               cout << "True\n";
               for (auto number : solution) {
                   cout << number << " ";
               }
           }
        }

        void setN(int n) {
            this -> n = n;
        }

        void setM(int m) {
            this -> m = m;
        }

        void setK(int k) {
            this -> k = k;
        }

        void setMatrix(int matrix[maxn][maxn]) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    this -> matrix[i][j] = matrix[i][j];
                }
            }
        }
};