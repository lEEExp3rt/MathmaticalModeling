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

inline double TimeToReach(Area src, Area dst, double speed)
{
    double xx = dst.center.x - src.center.x;
    double yy = dst.center.y - src.center.y;
    double dist = sqrt(xx * xx + yy * yy);
    return dist / speed;
}

const int dx[3] = {-1, 0, 1};
const int dy[3] = {-1, 0, 1};

double traverse(const vector<vector<Area>> areas, const int gridX, const int gridY, const double maxTime, const double speed, int indexX, int indexY, double time, vector<vector<bool>>& visited)
{
    if (time > maxTime) {
        return 0;
    }
    visited[indexX][indexY] = true;
    double maxWeight = 0;
    for (int i = 0; i < 3; i++) {
        int newX = indexX + dx[i];
        for (int j = 0; j < 3; j++) {
            if (!i && !j) continue;
            int newY = indexY + dy[j];
            if (newX < 0 || newX >= gridX || newY < 0 || newY >= gridY || visited[newX][newY]) continue;
            double weight = traverse(areas, gridX, gridY, maxTime, speed, newX, newY, time + TimeToReach(areas[indexX][indexY], areas[newX][newY], speed), visited);
            if (weight > maxWeight) maxWeight = weight;
            visited[newX][newY] = false;
        }
    }
    return areas[indexX][indexY].center.weight + maxWeight;
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
    vector<vector<bool>> visited(gridX, vector<bool>(gridY, false));
    double maxWeight = traverse(areas, gridX, gridY, maxTime, speed, 0, 0, 0, visited);
    cout << maxWeight << endl;
}