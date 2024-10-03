#include <bits/stdc++.h>
using namespace std;
using db = double;  // 换long double时，需要同时替换alpha、abs、getTheta函数
const db eps = 1e-9;

inline int sign(db x) { return x < -eps ? -1 : x > eps; }
inline int cmp(db x, db y) { return sign(x - y); }

// 点 Point
struct Point {
    db x, y;

    Point() : x(0), y(0) {}
    Point(db _x, db _y) : x(_x), y(_y) {}

    Point operator+(const Point &p) const { return {x + p.x, y + p.y}; }
    Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }
    Point operator*(const db &d) const { return {x * d, y * d}; }
    Point operator/(const db &d) const { return {x / d, y / d}; }

    bool operator<(Point p) const {
        int gg = cmp(x, p.x);
        if (gg) {
            return gg == -1;
        } else {
            return cmp(y, p.y) == -1;
        }
    }

    // 这里的比较可能不满足传递性，因为这是基于eps的比较
    bool operator==(Point p) const { return cmp(x, p.x) == 0 && cmp(y, p.y) == 0; }

    db dot(Point p) { return x * p.x + y * p.y; }
    db det(Point p) { return x * p.y - y * p.x; }

    db alpha() { return atan2(y, x); }
    db abs() { return sqrt(abs2()); }
    db abs2() { return x * x + y * y; }
    Point unit() { return *this / abs(); }
    Point rot90() { return {-y, x}; }
    Point rot(db theta) { return {x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta)}; }
    int quad() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) >= 0); }
};

inline db dot(Point p, Point q) { return p.x * q.x + p.y * q.y; }
inline db det(Point p, Point q) { return p.x * q.y - p.y * q.x; }  // 判断 向量p 是否在 向量q 的顺时针方向
inline db dis(Point p, Point q) { return (p - q).abs(); }
// 判断 向量p1p2 是否在 向量p1p3 的顺时针方向
inline db cross(Point p1, Point p2, Point p3) { return det(p2 - p1, p3 - p1); }
inline int cross_S(Point p1, Point p2, Point p3) { return sign(cross(p1, p2, p3)); }