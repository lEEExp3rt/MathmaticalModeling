#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

struct Node {
    int x, y;
    double g, h, f;
    Node(int _x, int _y, double _g, double _h, double _f) : x(_x), y(_y), g(_g), h(_h), f(_f) {}
};

int n, m;
vector<vector<int>> grid;
vector<vector<double>> dist;
vector<vector<bool>> visited;

double heuristic(int x, int y) {
    return sqrt(pow(x - n - 1, 2) + pow(y - m - 1, 2));
}

void astar() {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(0, 0, 0, heuristic(0, 0), 0));
    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();
        if (curr.x == n - 1 && curr.y == m - 1) {
            cout << "Found path with cost " << curr.f << endl;
            return;
        }
        if (visited[curr.x][curr.y]) continue;
        visited[curr.x][curr.y] = true;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;
                int nx = curr.x + i, ny = curr.y + j;
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                double ng = curr.g + 1;
                double nh = heuristic(nx, ny);
                double nf = ng + nh;
                if (dist[nx][ny] > nf) {
                    dist[nx][ny] = nf;
                    pq.push(Node(nx, ny, ng, nh, nf));
                }
            }
        }
    }
    cout << "No path found" << endl;
}

int main() {
    cin >> n >> m;
    grid.resize(n, vector<int>(m));
    dist.resize(n, vector<double>(m, numeric_limits<double>::infinity()));
    visited.resize(n, vector<bool>(m, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    dist[0][0] = 0;
    astar();
    return 0;
}