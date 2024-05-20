#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
    double weight;
};

struct Area {
    double r;
    Point center;
};

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};

void printVector(const vector<pair<int, int>> areas)
{
    for (const pair<int, int>& area : areas) {
        cout << "(" << area.first << ", " << area.second << ") -> ";
    }
    cout << endl;
}

void traverse(const vector<vector<Area>> areas, const int gridX, const int gridY, const double maxTime, const double dTime, int indexX, int indexY, double time, vector<pair<int, int>>& path, bool& flag)
{
    if (time > maxTime) {
        if (flag) {
            printVector(path);
            flag = false;
        }
        return;
    }
    path.push_back(make_pair(indexX, indexY));
    flag = true;
    for (int i = 0; i < 4; i++) {
        int newX = indexX + dx[i];
        int newY = indexY + dy[i];
        if (newX < 0 || newX >= gridX || newY < 0 || newY >= gridY) continue;
        traverse(areas, gridX, gridY, maxTime, dTime, newX, newY, time + dTime, path, flag);
    }
    path.pop_back();
    return ;
}

int main()
{
    double maxTime; // 最大时间
    double speed, r; // 无人机参数
    int nPoints; // 点的数量
    cin >> maxTime >> speed >> r >> nPoints;
    // 读入点
    vector<Point> points(nPoints);
    double minX = 1e9, minY = 1e9; // 区域最小跨度
    double maxX = 0, maxY = 0; // 区域最大跨度
    for (int i = 0; i < nPoints; i++) {
        cin >> points[i].x >> points[i].y >> points[i].weight;
        minX = min(minX, points[i].x);
        minY = min(minY, points[i].y);
        maxX = max(maxX, points[i].x);
        maxY = max(maxY, points[i].y);
    }
    // 区域栅格化
    int gridX = ceil((maxX - minX) / 2 * r);
    int gridY = ceil((maxY - minY) / 2 * r);
    vector<vector<Area>> areas(gridX, vector<Area>(gridY));
    for (int i = 0; i < gridX; i++) {
        for (int j = 0; j < gridY; j++) {
            double centerX = minX + (2 * i + 1) * r;
            double centerY = minY + (2 * j + 1) * r;
            areas[i][j].r = r;
            areas[i][j].center.x = centerX;
            areas[i][j].center.y = centerY;
            areas[i][j].center.weight = 0;
        }
    }
    // 计算每个区域的权重
    for (int i = 0; i < nPoints; i++) {
        int x = (points[i].x - minX) / (2 * r);
        int y = (points[i].y - minY) / (2 * r);
        areas[x][y].center.weight += points[i].weight;
    }

    // 开始搜索
    vector<pair<int, int>> path;
    bool flag = false;
    traverse(areas, gridX, gridY, maxTime, 2 * r / speed, 0, 0, 0, path, flag);
    return 0;
}