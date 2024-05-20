#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Point {
public:
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
};

inline bool compare(const Point& a, const Point& b) {
    if (a.x >= 0 && b.x < 0) return true;
    if (a.x < 0 && b.x >= 0) return false;
    if (a.x == 0 && b.x == 0) {
        if (a.y >= 0 || b.y >= 0) return a.y > b.y;
        return b.y > a.y;
    }
    return a.x * b.y - a.y * b.x > 0;
}

vector<Point> sortPointsCounterClockwise(vector<Point>& points) {
    int n = points.size();
    // 找到最左下角的点，并将其放在数组的开头
    int minIdx = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[minIdx].y || (points[i].y == points[minIdx].y && points[i].x < points[minIdx].x)) {
            minIdx = i;
        }
    }
    swap(points[0], points[minIdx]);
    // 将最左下角的点作为基准点，对其他点按照相对于基准点的极角排序
    sort(points.begin() + 1, points.end(), [&](const Point& a, const Point& b) {
        double cross = (a.x - points[0].x) * (b.y - points[0].y) - (a.y - points[0].y) * (b.x - points[0].x);
        if (abs(cross) < 1e-9) {
            double distA = (a.x - points[0].x) * (a.x - points[0].x) + (a.y - points[0].y) * (a.y - points[0].y);
            double distB = (b.x - points[0].x) * (b.x - points[0].x) + (b.y - points[0].y) * (b.y - points[0].y);
            return distA < distB;
        }
        return cross > 0;
    });

    return points;
}

inline double crossProduct(Point p0, Point p1, Point p2)
{
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

inline double area(vector<Point>& points)
{
    int n = points.size();
    double area = 0.0;
    for (int i = 1; i < n - 1; i++) {
        int j = i + 1;
        area += crossProduct(points[0], points[i], points[j]);
    }
    return abs(area) / 2.0;
}

int main()
{
    int nPoints, nAreas;
    double V, d; // nPoints: 凸多边形点个数, nAreas: 划分区域个数, V: 无人机速度, d: 无人机搜索半径
    cin >> nPoints >> nAreas >> V >> d;
    vector<Point> points; // x and y coordinates of points.
    for (int i = 0; i < nPoints; i++) {
        double x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }
    points = sortPointsCounterClockwise(points); // Sort the points counterclockwise.
    // Max horizontal distance between two points.
    double AreaRequired = area(points) / nAreas; // The area required per area.
    cout << AreaRequired / (V * 2 * d) << endl;
    return 0;
}