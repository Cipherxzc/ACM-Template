// 判断 直线p1p2 和 直线q1q2 是否相交
bool isLL(Point p1, Point p2, Point q1, Point q2) { return sign(cross(q1, q2, p1) - cross(q1, q2, p2)) != 0; }

// 判断 直线p1p2 和 直线q1q2 是否严格相交
bool isLL_strict(Point p1, Point p2, Point q1, Point q2) { return cross_S(p1, p2, q1) * cross_S(p1, p2, q2) < 0; }

// 求交点
Point getLL(Point p1, Point p2, Point q1, Point q2) {
    db a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}

// 判断区间是否相交
bool intersect(db l1, db r1, db l2, db r2) {
    if (l1 > r1) swap(l1, r1);
    if (l2 > r2) swap(l2, r2);
    return cmp(r1, l2) != -1 && cmp(r2, l1) != -1;
}

// 线段相交
bool isSS(Point p1, Point p2, Point q1, Point q2) {
    return intersect(p1.x, p2.x, q1.x, q2.x) && intersect(p1.y, p2.y, q1.y, q2.y) &&
           cross_S(p1, p2, q1) * cross_S(p1, p2, q2) <= 0 && cross_S(q1, q2, p1) * cross_S(q1, q2, p2) <= 0;
}

// 线段严格相交(不能交于端点)
bool isSS_strict(Point p1, Point p2, Point q1, Point q2) {
    return cross_S(p1, p2, q1) * cross_S(p1, p2, q2) < 0 && cross_S(q1, q2, p1) * cross_S(q1, q2, p2) < 0;
}

// x 是否在 l 和 r 之间
bool isMiddle(db x, db l, db r) {
    if (l > r) swap(l, r);
    return cmp(l, x) <= 0 && cmp(x, r) <= 0;
}

// 点q 是否在 点p1 和 点p2 之间
bool isMiddle(Point q, Point p1, Point p2) { return isMiddle(q.x, p1.x, p2.x) && isMiddle(q.y, p1.y, p2.y); }

// 点q 是否在 直线p1p2 上
bool onLine(Point q, Point p1, Point p2) { return cross_S(p1, p2, q) == 0; }

// 点q 是否在 线段p1p2 上
bool onSeg(Point q, Point p1, Point p2) { return cross_S(p1, p2, q) == 0 && isMiddle(q, p1, p2); }

// 点q 是否在 线段p1p2 上(严格)
bool onSeg_strict(Point q, Point p1, Point p2) {
    return cross_S(p1, p2, q) == 0 && sign(dot(q - p1, p1 - p2)) * sign(dot(q - p2, p1 - p2));
}

// 求 q 到 直线p1p2 的投影(垂足)
Point proj(Point q, Point p1, Point p2) {
    Point dir = p2 - p1;
    return p1 + dir * (dot(dir, q - p1) / dir.abs2());
}

// 求 q 以 直线p1p2 为轴的反射
Point reflect(Point q, Point p1, Point p2) { return proj(p1, p2, q) * 2 - q; }

// 求 q 到 线段p1p2 的最小距离
db disPS(Point q, Point p1, Point p2) {
    if (p1 == p2) {
        return dis(p1, q);
    }
    Point v1 = p2 - p1, v2 = q - p1, v3 = q - p2;
    if (sign(dot(v1, v2)) == -1) {
        return v2.abs();
    } else if (sign(dot(v1, v3)) == 1) {
        return v3.abs();
    } else {
        return fabs(det(v1, v2) / v1.abs());
    }
}

// 求 线段p1p2 与 线段q1q2 的距离
db disSS(Point p1, Point p2, Point q1, Point q2) {
    if (isSS(p1, p2, q1, q2)) {
        return 0;
    } else {
        return min(min(disPS(p1, p2, q1), disPS(p1, p2, q2)), min(disPS(q1, q2, p1), disPS(q1, q2, p2)));
    }
}