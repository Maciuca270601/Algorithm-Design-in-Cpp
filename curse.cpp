#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    int N, M, A;
    int piste[21][100000];
    int antrenamente[100000];
    static constexpr int NMAX = (int)1e5 + 5;
    vector<int> adj[NMAX];

    // order[i] = j means that the i-th car is better than the j-th car
    vector<pair<int, int>> order;





    void read_input() {
        ifstream fin("curse.in");

        fin >> N >> M >> A;

        for (int a = 1; a <= A; a++) {
            for (int n = 1; n <= N; n++) {
                fin >> piste[n][a];
            }
        }

        fin.close();
    }

    void extract_orders() {
        for (int p = 1; p <= N; p++) {
            for (int a = 1; a < A; a++) {
                if ((piste[p][a] !=  piste[p][a + 1]) &&
                    (antrenamente[a] == 1)) {
                    order.push_back(make_pair(piste[p][a], piste[p][a + 1]));
                    antrenamente[a] = 0;
                }
            }
        }
    }

    vector<int> get_result() {
        return solve_dfs();
    }

     vector<int> solve_dfs() {
        // vectorul rezultat (in final contine o permutare pentru 1, 2, ..., n)
        vector<int> topsort;

        // used[node] = 1 daca node a fost deja vizitat, 0 altfel
        vector<int> used(M + 1, 0);

        // pentru fiecare nod
        for (int node = 1; node <= M; ++node) {
            // daca nodul este nevizitat, pornim o parcurgere
            if (!used[node]) {
                dfs(node, used, topsort);
            }
        }

        // rezultatul a fost obtinut in ordine inversa
        reverse(topsort.begin(), topsort.end());

        return topsort;
    }

    void dfs(int node, vector<int>& used, vector<int>& topsort) {
        used[node] = 1;

        // parcurg vecinii
        for (auto& neigh : adj[node]) {
            if (!used[neigh]) {
                dfs(neigh, used, topsort);
            }
        }

        // dupa ce am vizitat recursiv toti vecinii, adaugam
        // nodul la sortare
        topsort.push_back(node);
    }





    void print_output() {
        ofstream fout("curse.out");
        for (int i = 1; i < A; i++) {
            antrenamente[i] = 1;
        }

        extract_orders();

        for (auto &p : order) {
            adj[p.first].push_back(p.second);
         }

        vector<int> result = get_result();

        for (auto &p : result) {
            fout << p << " ";
        }
        fout << endl;
        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task();
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
