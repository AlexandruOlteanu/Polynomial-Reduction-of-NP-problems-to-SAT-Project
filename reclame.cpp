/*
 * <Copyright Alexandru Olteanu, grupa 322CA, alexandruolteanu2001@gmail.com>
 */
#include <bits/stdc++.h>
#include "clique_help.cpp"
using namespace std;


class Reclame : public Task {
    public:
        int n, m;
        int matrix[maxn][maxn] = {0};
        Retele clique_help;

        vector<int> solution, oracle_answer;
        /**
         * Functie de rezolvare a intregului task. Actiunile sunt apelate consecutiv
         * */
        void solve() {
            read_problem_data();
            build_complement_matrix();
            find_minimum_removing_nodes();
            decipher_oracle_answer();
            write_answer();
        }
        /**
         * Se citeste numarul de noduri, de muchii si dimensiunea grupului cautat
         * dupa care se citesc cele m muchii, muchia i fiind intre nodurile (Xi, Yi).
         * De asemenea, se formeaza matricea de adiacenta ce va ajuta in continuare la
         * formarea clauzelor
         * */
        void read_problem_data() {
            cin >> n >> m;
            for (int i = 1; i <= m; ++i) {
                int x, y;
                cin >> x >> y;
                matrix[x][y] = matrix[y][x] = 1;
            }
        }

        void build_complement_matrix() {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (!matrix[i][j]) {
                        matrix[i][j] = 1;
                    }
                    else {
                        matrix[i][j] = 0;
                    }
                }
            }
        }

        void find_minimum_removing_nodes() {
            clique_help.setN(n);
            clique_help.setM(m);
            clique_help.setMatrix(matrix);

            int low = 1, high = n;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                clique_help.setK(mid);
                formulate_oracle_question();
                ask_oracle();
                ifstream in(oracleOutputFile);
                string answer;
                in >> answer;
                //cout << "Alex " << answer << " " << mid << '\n';
                //cout << "Maria " << clique_help.n << " " << clique_help.k << " ";
                //cout << '\n';
                if (answer == "True") {
                    oracle_answer.clear();
                    int length;
                    in >> length;
                    for (int i = 1; i <= length; ++i) {
                        int x;
                        in >> x;
                        oracle_answer.push_back(x);
                    }
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }
            
        }

        void formulate_oracle_question() {
            clique_help.formulate_oracle_question();
        }
        /**
         * In urma construirii clauzelor si primirea raspunsului din partea oracolului, 
         * aceste date sunt stocate in fisierul sat.sol. Acestea trebuie prelucrate pentru
         * a afisa raspunsul la problema acestui task
         * */
        void decipher_oracle_answer() {
            bool vis[maxn] = {0};
            for (auto u : oracle_answer) {
                if (u > 0) {
                    u %= n;
                    if (u == 0) {
                        u = n;
                    }
                    vis[u] = 1;
                }
            }
            for (int i = 1; i <= n; ++i) {
                if (!vis[i]) {
                    solution.push_back(i);
                }
            }
        }
        /**
         * Odata descifrat oracolul se afiseaza "False" daca prima valoare din 
         * vectorul solution este -1 sau "True" insotit de intregul vector in 
         * cazul existentei solutiei
         * */
        void write_answer() {
            for (auto number : solution) {
                cout << number << " ";
            }
        }


};


int main() {
    
    
    Reclame reclame;
    reclame.solve();

    return 0;
}