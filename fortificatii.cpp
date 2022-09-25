#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    long long n, m, b;
    long long k;
    vector<long long> barbarians;
    vector<pair<long long, long long>> adj[200000];
    long long vect[200000];
    long long nodes[100000] = {0};

    bool check_if_barbarians(long long node) {
        for (long long i = 0; i < barbarians.size(); i++) {
            if (barbarians[i] == node) {
                return true;
            }
        }
        return false;
    }

    void read_input() {
        ifstream fin("fortificatii.in");
        fin >> n >> m >> k;

        // read the barbarians
        fin >> b;
        for (long long i = 0; i < b; i++) {
            long long x;
            fin >> x;
            barbarians.push_back(x);
            nodes[x] = 1;
        }

        // read the adjacency matrix
        for (long long i = 0; i < m; i++) {
            long long x, y, z;
            fin >> x >> y >> z;

            // if x is barberian and y is not add the edge
            if (nodes[x] == 1 && nodes[y] == 0) {
                adj[y].push_back(make_pair(x, z));
            }

            // if y is barberian and x is not add the edge
            if (nodes[y] == 1 && nodes[x] == 0) {
                adj[x].push_back(make_pair(y, z));
            }

            // if both are not barberians add the edge
            if (nodes[x] == 0 && nodes[y] == 0) {
                adj[x].push_back(make_pair(y, z));
                adj[y].push_back(make_pair(x, z));
            }
        }
        fin.close();
    }

    struct compare {
        bool operator()(pair<long long, long long> p1,
                        pair<long long, long long> p2) {
            return p2.second < p1.second;
        }
    };

    void dijsktra(long long source, vector<long long> &solutie,
                                    vector<long long> &cost, long long n) {
        for (long long i = 1; i <= n; i++) {
            solutie[i] = LONG_LONG_MAX;
            cost[i] = -1;
        }

        priority_queue<pair<long long, long long>,
                            vector<pair<long long, long long>>, compare> queue;
        pair<long long, long long> queue_pair;
        vector<long long> visited(n + 1, 0);
        solutie[source] = 0;
        cost[source] = -1;

        queue_pair.first = source;
        queue_pair.second = solutie[source];
        queue.push(queue_pair);

        while (!queue.empty()) {
            pair<long long, long long> top_pair = queue.top();
            queue.pop();

            long long node = top_pair.first;
            if (visited[node] == 0) {
                for (pair<long long, long long> neigh : adj[node]) {
                    if (solutie[node] + neigh.second < solutie[neigh.first]) {
                        solutie[neigh.first] = solutie[node] + neigh.second;
                        cost[neigh.first] = node;
                        pair<long long, long long> aux_pair;
                        aux_pair.first = neigh.first;
                        aux_pair.second = solutie[neigh.first];
                        queue.push(aux_pair);
                    }
                }
                visited[node] = 1;
            }
        }
    }

    void function(long long equal_numbers, long long diff, long long counter,
                  long long *result) {
        while ((k > equal_numbers * diff) && (diff != 0)) {
            // update k
            k -= equal_numbers * diff;

            // update numbers
            for (long long i = 0; i < equal_numbers; i++) {
                vect[i] += diff;
            }
            equal_numbers++;

            // update equal_numbers
            for (long long i = equal_numbers; i < counter; i++) {
                if (vect[i] == vect[i - 1]) {
                    equal_numbers++;
                } else {
                    break;
                }
            }

            // update diff
            if (equal_numbers != counter) {
                diff = vect[equal_numbers] - vect[0];
            } else {
                diff = 0;
            }
        }

        if (k == 0) {
            *result = vect[equal_numbers - 1];
        } else {
            *result = vect[equal_numbers - 1] + (k / equal_numbers);
        }
    }

    void print_output() {
        ofstream fout("fortificatii.out");
        vector<long long> solutie(n + 1, 0);
        vector<long long> cost(n + 1, 0);

        dijsktra(1, solutie, cost, n);

        long long counter = 0;
        for (long long i = 1; i <= n; i++) {
            for (auto &p : adj[i]) {
                if (nodes[i] == 0 && nodes[p.first] == 1) {
                    if (solutie[i] == LONG_LONG_MAX) {
                        continue;
                    }
                    vect[counter++] = p.second + solutie[i];
                }
            }
        }

        sort(vect, vect + counter);

        long long result = 0;
        long long equal_numbers = 1;

        for (long long i = 1; i < counter; i++) {
            if (vect[i] == vect[i - 1]) {
                equal_numbers++;
            } else {
                break;
            }
        }

        long long diff = vect[equal_numbers] - vect[0];

        function(equal_numbers, diff, counter, &result);

        fout << result << endl;
        fout.close();
    }
};

int main() {
    auto *task = new (nothrow) Task();
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
