/*
 * <Copyright Alexandru Olteanu, grupa 322CA, alexandruolteanu2001@gmail.com>
 */
#include <bits/stdc++.h>
#include "clique_help.cpp"
using namespace std;

/**
 * Acest Task reprezinta de fapt inversa problemei retele intr-o oarecare 
 * masura. Pentru a afla numarul k minim de noduri ce trebuie scoase pentru
 * a obtine doar noduri izolate trebuie de fapt sa construim cel mai mare
 * clique pe graful complementar (Acest clique va reprezenta toate nodurile 
 * ce raman la final si nu au muchii intre ele). Astfel, dupa aflarea acestui
 * clique maxim, se vor scoate restul nodurilor, raspunsul fiind optim
 * */
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
         * Se citeste numarul de noduri si de muchii ale grafului
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

        /**
         * Se realizeaza complementul matricei de adiacenta pentru
         * a putea calcula grupul maxim de noduri initial nediacente 
         * ce vor ramane in urma scoterii celorlalte noduri
         * */
        void build_complement_matrix() {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    matrix[i][j] ^= 1;
                }
            }
        }

        /**
         * Aceasta functie calculeaza cu ajutorul cautarii 
         * binare numarul minim de noduri ce trebuie scos pentru 
         * a ramane doar noduri nediacente.
         * */
        void find_minimum_removing_nodes() {

            // Ma folosesc de un obiect de tip Retele pentru a calcula
            // la fiecare pas daca se poate forma un clique cu k noduri
            // pe matricea complementara.
            clique_help.setN(n);
            clique_help.setM(m);
            clique_help.setMatrix(matrix);

            // Folosesc cautare binara pentru  o mai eficienta aflare a numarului 
            // k maxim ce respecta conditia
            int low = 1, high = n;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                clique_help.setK(mid);
                formulate_oracle_question();
                ask_oracle();
                ifstream in(oracleOutputFile);
                string answer;
                in >> answer;
                
                // Daca raspunsul dat de Oracol pentru k-ul curent este True
                // se va adauga intreg rasounsul in vectorul oracle_answer
                // si se va incerca o valoare mai mare pentru k, in caz
                // contrar se va incerca o valoare mai mica pentru k
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

        /**
         * Apeleaza functia de creare a clauzelor pe baza matricei complementare
         * si numarului k curent
         * */
        void formulate_oracle_question() {
            clique_help.formulate_oracle_question();
        }
        /**
         * In urma construirii clauzelor si primirea raspunsurilor din partea oracolului, 
         * datele pentru cel mai mare k posibil sunt stocate in oracle_answer. Acestea trebuie 
         * prelucrate pentru a afisa raspunsul la problema acestui task.
         * */
        void decipher_oracle_answer() {
            bool visited[maxn] = {0};
            // Se marcheaza ca vizitat toate nodurile ce sunt 
            // pozitive din raspunsul oracolului.
            for (auto u : oracle_answer) {
                if (u > 0) {
                    u %= n;
                    if (u == 0) {
                        u = n;
                    }
                    visited[u] = 1;
                }
            }

            // Elementele ce trebuie sterse sunt cele care au ramas nevizitate
            // (Nu fac parte din elementele ce alcatuiesc clique maxim pe matricea 
            // complementara)
            // Nodurile ce trebuie sterse sunt stocate in vectorul solution
            for (int i = 1; i <= n; ++i) {
                if (!visited[i]) {
                    solution.push_back(i);
                }
            }
        }
        /**
         * Odata descifrat oracolul se afiseaza vectorul solution, vector ce 
         * reprezinta valorile finale ce trebuie scoase din graf pentru ca toate
         * cele ramase sa fie izolate
         * */
        void write_answer() {
            for (auto number : solution) {
                cout << number << " ";
            }
        }
};


int main() {
    
    //Declararea obiectului de tip Reclame si apelarea functiei solve
    Reclame reclame;
    reclame.solve();

    return 0;
}