#include <bits/stdc++.h>
using namespace std;

#define MAXINT 2147483647

class QItem {
 public:
    int row;
    int col;
    int dist;
    QItem(int x, int y, int w)
        : row(x), col(y), dist(w) {
    }
};

class Square {
 public:
    int row, column;
    Square(int x, int y)
        : row(x), column(y) {
    }
};

class Task {
 public:
    void solve() {
        read_input();
        create_paths();
        print_output();
    }

 private:
    int n, m;
    vector<Square> dirty_square_list;
    vector<Square> robot_square_list;
    int robot_dirty_path[500][500];
    int dirty_dirty_path[500][500];
    char grid[1001][1001];
    int result = MAXINT;
    vector<bool> visited;
    vector<int> times;

    void read_input() {
        ifstream fin("curatare.in");
        fin >> n >> m;

        // read the matrix from input file
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fin >> grid[i][j];

                // if the square is dirty, add it to the dirty list
                if (grid[i][j] == 'S') {
                    dirty_square_list.push_back(Square(i, j));
                }

                // if the square is a robot, add it to the robot list
                if (grid[i][j] == 'R') {
                    robot_square_list.push_back(Square(i, j));
                }
            }
        }

        // initialize the visited array
        for (int i = 0; i < dirty_square_list.size(); i++) {
            visited.push_back(false);
        }

        fin.close();
    }


    int minDistance(char grid[1001][1001], int startRow, int startCol,
                    int endRow, int endCol) {
        QItem source(0, 0, 0);

        /*  
        To keep track of visited QItems. 
        Marking blocked cells as visited.
        */
        bool visited[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 'X') {
                    visited[i][j] = true;
                } else {
                    visited[i][j] = false;
                }

                // Finding source
                if ((i == startRow) && (j == startCol)) {
                    source.row = i;
                    source.col = j;
                }
            }
        }

        // applying BFS on matrix cells starting from source
        queue<QItem> q;
        q.push(source);
        visited[source.row][source.col] = true;
        while (!q.empty()) {
            QItem p = q.front();
            q.pop();

            // Destination found;
            if ((p.row == endRow) && (p.col == endCol)) {
                return p.dist;
            }

            // moving up
            if ((p.row - 1 >= 0) && (visited[p.row - 1][p.col] == false)) {
                q.push(QItem(p.row - 1, p.col, p.dist + 1));
                visited[p.row - 1][p.col] = true;
            }

            // moving down
            if ((p.row + 1 < n) && (visited[p.row + 1][p.col] == false)) {
                q.push(QItem(p.row + 1, p.col, p.dist + 1));
                visited[p.row + 1][p.col] = true;
            }

            // moving left
            if ((p.col - 1 >= 0) && (visited[p.row][p.col - 1] == false)) {
                q.push(QItem(p.row, p.col - 1, p.dist + 1));
                visited[p.row][p.col - 1] = true;
            }

            // moving right
            if ((p.col + 1 < m) && (visited[p.row][p.col + 1] == false)) {
                q.push(QItem(p.row, p.col + 1, p.dist + 1));
                visited[p.row][p.col + 1] = true;
            }
        }
        return -1;
    }


    void create_paths() {
        // create the paths between the dirty squares and the dirty squares
        for (int i = 0; i < dirty_square_list.size(); i++) {
            for (int j = 0; j < dirty_square_list.size(); j++) {
                if (i != j) {
                    int dist = minDistance(grid, dirty_square_list[i].row,
                                           dirty_square_list[i].column,
                                           dirty_square_list[j].row,
                                           dirty_square_list[j].column);
                    dirty_dirty_path[i][j] = dist;
                }
            }
        }

        // create the paths between the robots and the dirty squares
        for (int i = 0; i < robot_square_list.size(); i++) {
            for (int j = 0; j < dirty_square_list.size(); j++) {
                int dist = minDistance(grid, robot_square_list[i].row,
                                       robot_square_list[i].column,
                                       dirty_square_list[j].row,
                                       dirty_square_list[j].column);
                robot_dirty_path[i][j] = dist;
            }
        }

        // initialize the times array
        for (int i = 0; i < robot_square_list.size(); i++) {
            times.push_back(0);
        }
    }


    void bkt(vector<Square> robot_square_list,
             vector<Square> dirty_square_list,
             int robot_dirty_path[500][500],
             int dirty_dirty_path[500][500],
             vector<int> times, vector<bool> visited,
             int *result) {
        // it means that all dirty squares have been cleaned
        int clean_bool = 1;

        for (int i = 0; i < dirty_square_list.size(); i++) {
            if (visited[i] == false) {
                clean_bool = 0;
                break;
            }
        }

        // if all the dirty squares have been cleaned, we have found a solution
        if (clean_bool == 1) {
            // obtain new max time for times array
            int max_time = 0;
            for (int i = 0; i < times.size(); i++) {
                if (times[i] > max_time) {
                    max_time = times[i];
                }
            }

            // if the new max time is smaller than the current max time,
            // we proceed in finding a solution
            if (max_time < *result) {
                *result = max_time;
            }

            return;
        }

        // recursion of the backtracking
        for (int i = 0; i < dirty_square_list.size(); i++) {
            for (int j = 0; j < robot_square_list.size(); j++) {
                if (visited[i] == false) {
                    // clean the dirty square
                    visited[i] = true;

                    // update the time of the robot j
                    // that clean the dirty square i
                    times[j] += robot_dirty_path[j][i];

                    // update the position of the robot so it can clean it
                    // and save the old position for recursion purposes
                    int old_row = robot_square_list[j].row;
                    int old_col = robot_square_list[j].column;
                    robot_square_list[j].row = dirty_square_list[i].row;
                    robot_square_list[j].column = dirty_square_list[i].column;

                    // save the dirty squares paths to other dirty squares
                    // and update robot paths to dirty squares
                    int old_dirty_path[500][500];
                    for (int k = 0; k < dirty_square_list.size(); k++) {
                        old_dirty_path[j][k] = robot_dirty_path[j][k];

                        if (k != i) {
                            robot_dirty_path[j][k] = dirty_dirty_path[i][k];
                        }
                    }

                    // apply the recursion
                    bkt(robot_square_list, dirty_square_list, robot_dirty_path,
                        dirty_dirty_path, times, visited, result);

                    // restore the old values

                    // make the dirty square dirty again
                    visited[i] = false;

                    // restore the time of the robot j
                    // that cleaned the dirty square i
                    times[j] -= robot_dirty_path[j][i];

                    // restore the position of the robot
                    // back to its original square
                    robot_square_list[j].row = old_row;
                    robot_square_list[j].column = old_col;

                    // update robot path to other dirty squares
                    for (int k = 0; k < dirty_square_list.size(); k++) {
                        robot_dirty_path[j][k] = old_dirty_path[j][k];
                    }
                }
            }
        }
    }

    void print_output() {
        ofstream fout("curatare.out");

        bkt(robot_square_list, dirty_square_list,
            robot_dirty_path, dirty_dirty_path,
            times, visited, &result);
        fout << result << '\n';

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
