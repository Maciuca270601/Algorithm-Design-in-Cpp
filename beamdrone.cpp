#include <bits/stdc++.h>
using namespace std;

#define MAXINT 2147483647

class QItem {
 public:
    int row;
    int col;
    QItem(int x, int y)
        : row(x), col(y) {
    }
};

class Square {
 public:
    int row, column;
    Square(int x, int y)
        : row(x), column(y){
    }
};

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    int n, m;
    char grid[1001][1001];
    int start_row, start_column;
    int end_row, end_column;
    int dist[1001][1001] = {0};
    int directions[1001][1001] = {0};

    void read_input() {
        ifstream fin("beamdrone.in");
        fin >> n >> m;

        fin >> start_row >> start_column;
        fin >> end_row >> end_column;

        // read the matrix from input file
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fin >> grid[i][j];
            }
        }

        grid[start_row][start_column] = 'S';
        grid[end_row][end_column] = 'D';

        fin.close();
    }


    int minDistance(char grid[1001][1001], int startRow,
                    int startCol, int endRow,
                    int endCol, int direction) {
        QItem source(0, 0);
        bool visited[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 'W') {
                    visited[i][j] = true;
                    dist[i][j] = -1;
                } else {
                    visited[i][j] = false;
                }
            }
        }

        // applying BFS on matrix cells starting from source
        queue<QItem> q;
        source.row = startRow;
        source.col = startCol;
        q.push(source);
        visited[source.row][source.col] = true;
        while (!q.empty()) {
            QItem p = q.front();
            q.pop();

            // moving up
            int i = 1;
            while ((p.row - i >= 0) && (grid[p.row - i][p.col] != 'W')) {
                if (visited[p.row - i][p.col] == false) {
                    q.push(QItem(p.row - i, p.col));
                    if (directions[p.row][p.col] == 3 ||
                        directions[p.row][p.col] == 4) {
                        dist[p.row - i][p.col] = dist[p.row][p.col] + 1;
                    } else {
                        dist[p.row - i][p.col] = dist[p.row][p.col];
                    }
                    visited[p.row - i][p.col] = true;
                }
                directions[p.row - i][p.col] = 1;
                if ((p.row - i == endRow) && (p.col == endCol)) {
                    return dist[p.row - i][p.col];
                }
                i++;
            }

            // moving right
            i = 1;
            while ((p.col + i < m) && (grid[p.row][p.col + i] != 'W')) {
                if (visited[p.row][p.col + i] == false) {
                    q.push(QItem(p.row, p.col + i));
                    if (directions[p.row][p.col] == 1 ||
                       directions[p.row][p.col] == 2) {
                        dist[p.row][p.col + i] = dist[p.row][p.col] + 1;
                    } else {
                        dist[p.row][p.col + i] = dist[p.row][p.col];
                    }
                    visited[p.row][p.col + i] = true;
                }
                directions[p.row][p.col + i] = 4;
                if ((p.row == endRow) && (p.col + i == endCol)) {
                    return dist[p.row][p.col + i];
                }
                i++;
            }

            // moving left
            i = 1;
            while ((p.col - i >= 0) && (grid[p.row][p.col - i] != 'W')) {
                if (visited[p.row][p.col - i] == false) {
                    q.push(QItem(p.row, p.col - i));
                    if (directions[p.row][p.col] == 1 ||
                       directions[p.row][p.col] == 2) {
                        dist[p.row][p.col - i] = dist[p.row][p.col] + 1;
                    } else {
                        dist[p.row][p.col - i] = dist[p.row][p.col];
                    }
                    visited[p.row][p.col - i] = true;
                }
                directions[p.row][p.col - i] = 3;
                if ((p.row == endRow) && (p.col - i == endCol)) {
                    return dist[p.row][p.col - i];
                }
                i++;
            }

            // moving down
            i = 1;
            while ((p.row + i < n) && (grid[p.row + i][p.col] != 'W')) {
                if (visited[p.row + i][p.col] == false) {
                    q.push(QItem(p.row + i, p.col));
                    if (directions[p.row][p.col] == 3 ||
                       directions[p.row][p.col] == 4) {
                        dist[p.row + i][p.col] = dist[p.row][p.col] + 1;
                    } else {
                        dist[p.row + i][p.col] = dist[p.row][p.col];
                    }
                    visited[p.row + i][p.col] = true;
                }
                directions[p.row + i][p.col] = 2;
                if ((p.row + i == endRow) && (p.col == endCol)) {
                    return dist[p.row + i][p.col];
                }
                i++;
            }
        }
        return -1;
    }


    void print_output() {
        ofstream fout("beamdrone.out");


        int direction = 1;
        // direction = 1 => up
        // direction = 2 => down
        // direction = 3 => left
        // direction = 4 => right
        int result = minDistance(grid, start_row, start_column,
                                 end_row, end_column, direction);
        fout << result << endl;
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
