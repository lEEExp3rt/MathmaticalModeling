#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Point {
public:
    double x, y;
    double weight;
    Point(double x = 0, double y = 0, double weight = 0) : x(x), y(y), weight(weight) {}
};

inline double distance(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// 评价函数，可更改
inline double Evaluate_Function(Point src, Point dest, double speed)
{
    double dist = distance(src, dest);
    return dest.weight * speed / dist;
}

double Traverse(const vector<Point>& points, const double speed, const double maxTime, bool visited[], int index, int cnt, double time)
{
    int nPoints = points.size();
    // 所有点都被访问，递归终止
    if (cnt == nPoints - 1 || time > maxTime)
        return 0;
    visited[index] = true;
    double maxValue = 0;
    for (int i = 0; i < nPoints; i++) {
        if (visited[i] || i == index) continue; // 已经访问过或是自己
        double value = Traverse(points, speed, maxTime, visited, i, cnt + 1, time + distance(points[index], points[i]) / speed);
        // 发现更优解
        if (value > maxValue) {
            maxValue = value;
        }
        visited[i] = false; // 重做
    }
    return points[index].weight + maxValue;
}

double Max_Weight(vector<Point> points, const double sp, const double maxTime)
{
    int nPoints = points.size();
    double maxWeight = 0;
    for (int i = 0; i < nPoints; i++) {
        // 初始化
        bool visited[nPoints] = {false};
        vector<int> path;
        double value = Traverse(points, sp, maxTime, visited, i, 0, 0);
        if (value > maxWeight) {
            maxWeight = value;
        }
    }
    return maxWeight;
}

int main()
{
    double V, t; // 速度，探测时间
    cin >> V >> t;
    int nPoints; // 目标点个数
    cin >> nPoints;
    vector<Point> points;
    vector<bool> visited(nPoints, false);
    for (int i = 0; i < nPoints; i++) {
        double x, y, weight;
        cin >> x >> y >> weight;
        points.push_back(Point(x, y, weight));
    }
    double weight = Max_Weight(points, V, t);
    cout << weight << endl;
    return 0;
}