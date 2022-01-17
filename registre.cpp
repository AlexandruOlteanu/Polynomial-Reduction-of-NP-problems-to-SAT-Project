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
 * Acest task reprezinta la baza problema K-Coloring care este 
 * NP Hard. Vom rezolva in continuare aceasta problema transformand 
 * conditiile impuse in propozitii logice (SAT)
 * */

class Registre : public Task {
    public:
        int n, m, k;
        int matrix[maxn][maxn] = {0};
        vector<pair<int, int>> solution;
        /**
         * Functie de rezolvare a intregului task. Actiunile sunt apelate consecutiv
         * */
        void solve() {
            read_problem_data();
            formulate_oracle_question();
            ask_oracle();
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
            cin >> n >> m >> k;
            for (int i = 1; i <= m; ++i) {
                int x, y;
                cin >> x >> y;
                matrix[x][y] = matrix[y][x] = 1;
            }
        }
        /**
         * Se construieste fisierul "sat.cnf" prin adaugarea 
         * antetului "p cnf" urmat de numarul de variabile si 
         * numarul de clauze ce urmeaza sa fie printate.
         * In continuare se formeaza clauzele corespunzatoare 
         * pentru algatuirea unei propozitii logice ce duce la
         * rezolvarea problemei.
         * */
        void formulate_oracle_question() {
            ofstream out (oracleInputFile);
            out << "p cnf " << k * n << " ";
            //Calculul numarului clauzelor, realizat prin analiza
            //complexitatilor bucatilor de cod ce urmeaza
            int clause = n;
            clause +=2 * m * k; 
            clause += (k - 1) * k / 2 * n;
            out << clause << '\n';

            //O prima conditie ce trebuie respectata este aceea 
            //ca pentru fiecare nod i ∈ [1, n], acesta trebuie sa
            //primeasca cel putin una din culorile de la 1 la k
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= k; ++j) {
                    out << (j - 1) * n + i << " ";
                }
                //Incheierea unei clauze cu caracterul "0"
                out << "0\n";
            }

            //Cea de a doua conditie este de a ne asigura ca niciodata
            //o pereche ce este conectata direct printr-o muchie nu va
            //avea ambii membri de aceeasi culoare. Pentru aceasta se parcurge 
            //matricea de adiacenta si se aleg perechile ce au muchie intre ele.
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (matrix[i][j]) {
                        for (int t = 1; t <= k; ++t) {
                                out << -((t - 1) * n + i) << " " << -((t - 1) * n + j) << " 0\n";
                        }
                    }
                }
            }

            //Cea de a treia conditie, fiind si cea finala este ca un nod sa aiba o singura culoare
            //dintre cele k valabile, pentru aceasta fiind necesara traversarea prin toate
            //cele k pozitii si construirea clauzelor pentru fiecare posibiliate in care
            //unul din cele n noduri ar putea avea mai multe culori
            for (int i = 1; i <= k; ++i) {
                for (int j = i + 1; j <= k; ++j) {
                    for (int t = 1; t <= n; ++t) {
                        out << -((i - 1) * n + t) << " " << -((j - 1) * n + t) << " 0\n";
                    }
                }
            }

            //Inschiderea fisierului sat.cnf
            out.close();

        }

        /**
         * In urma construirii clauzelor si primirea raspunsului din partea oracolului, 
         * aceste date sunt stocate in fisierul sat.sol. Acestea trebuie prelucrate pentru
         * a afisa raspunsul la problema acestui task
         * */
        void decipher_oracle_answer() {
            ifstream in(oracleOutputFile);
            string s;
            //Se citeste raspunsul cu privirea la existenta unei solutii
            in >> s;
            //Daca raspunul este adevarat (Exista solutie), se citeste 
            //sirul de n * k variabile si pentru fiecare variabila ce este
            //pozitiva se considera ca fiind urmatoare asignare a unei culori
            //pentru un anumit nod
            if (s == "True") {
                int length;
                in >> length;
                for (int i = 1; i <= n * k; ++i) {
                    int x; in >> x;
                    if (x > 0) {
                        //Se calculeaza grupul din care face parte variabila, 
                        //grup ce reprezinta culoarea respectivei variabile
                        int division = x / n;
                        if (x % n != 0) {
                            ++division;
                        }
                        x %= n;
                        if (x == 0)x = n;
                        //Se creaza o pereche de forma {nod, culoare}
                        solution.push_back({x, division});
                    }
                }
            }
            //In caz constrar, se adauga rezultatul {-1, -1} vectorului solution, 
            //simbol pentru inexistenta unei solutii
            else {
                solution.push_back({-1, -1});
            }
        }

        /**
         * Odata descifrat oracolul se afiseaza "False" daca prima valoare din 
         * vectorul solution este -1 sau "True" insotit de intregul vector in 
         * cazul existentei solutiei dupa ce acesta este sortat pentru afisarea 
         * nodurilor in ordine ascendenta
         * */
        void write_answer() {
           if (solution[0].first == -1) {
               cout << "False";
           }
           else {
               cout << "True\n";
               //Sortarea
               sort(solution.begin(), solution.end());
               for (auto number : solution) {
                   cout << number.second << " ";
               }
           }
        }
};


int main() {
    
    //Declararea obiectului de tip Retele si apelarea functiei solve
    Registre registre;
    registre.solve();


    return 0;
}