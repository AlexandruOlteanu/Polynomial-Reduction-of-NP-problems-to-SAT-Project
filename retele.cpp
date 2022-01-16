#include <bits/stdc++.h>
#include "task.h"
using namespace std;

const int maxn = 1e3;
const string oracleInputFile = "sat.cnf";

class Task1 : public Task {
    public:
        int n, m, k;
        vector<int> v[maxn];
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
                v[x].push_back(y);
                v[y].push_back(x);
            }

        }
        void formulate_oracle_question() {
            ofstream out (oracleInputFile);
            out << "p cnf";
            

        }
        void decipher_oracle_answer() {
            
        }
        void write_answer() {
            cout << n << " " << m << " " << k << '\n';
            for (auto u:v) {
                for (auto u1:u) {
                    cout << u1 << " ";
                }
            }
        }
};



int main() {
    
    Task1 retele;
    retele.solve();



    return 0;
}