#include <bits/stdc++.h>
using namespace std;

struct Vector;

struct Point {
    double x, y;
    
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    Point(pair<double, double> a) : x(a.first), y(a.second) {}
    
    const Point operator+(const Vector &v) const;
};

struct Vector {
    long double x, y;
    
    Vector() : x(0), y(0) {}
    Vector(pair<double, double> a) : x(a.first), y(a.second) {}
    Vector(Point a, Point b) : x(b.x - a.x), y(b.y - a.y) {}
    
    long double prod (const Vector &other) const {
        return x * other.y - y * other.x;  
    }
    
    static long double prod (const Vector &a, const Vector &b) {
        return a.prod(b);
    }
    
    long double len () const {
        return sqrt(y * y + x * x);
    }
    
    Vector operator*=(double a) {
        x *= a;
        y *= a;
        return *this;
    }
    
    Vector operator/=(double a) {
        x /= a;
        y /= a;
        return *this;
    }
    
    
    Vector operator+=(const Vector&other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    Vector operator-=(const Vector&other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    
    const Vector operator*(double a) const {
        return Vector(*this) *= a;
    }
    
    const Vector operator/(double a) const {
        return Vector(*this) /= a;
    }
    
    const Vector operator+(const Vector&other) const {
        return Vector(*this) += other;
    }
    
    const Vector operator-(const Vector&other) const {
        return Vector(*this) -= other;
    }
};
    
const Point Point::operator+(const Vector &v) const {
    return Point(x + v.x, y + v.y);
}

pair<vector<Point>, vector<Point>> get_hulls(vector<Point> points) {
    sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
        if (a.x == b.x) return a.y < b.y;
        return a.x < b.x;
    });
    
    vector<Point> upper_hull, lower_hull;
    
    for (auto pt = points.begin(); pt != points.end(); pt++) {
        while(upper_hull.size() >= 2 && 
            Vector::prod({upper_hull.end()[-2], upper_hull.end()[-1]}, {upper_hull.end()[-1], *pt}) >= 0)
                upper_hull.pop_back();
        upper_hull.push_back(*pt);
    }
    
    for (auto pt = points.rbegin(); pt != points.rend(); pt++) {
        while(lower_hull.size() >= 2 && 
            Vector::prod({lower_hull.end()[-2], lower_hull.end()[-1]}, {lower_hull.end()[-1], *pt}) >= 0)
                lower_hull.pop_back();
        lower_hull.push_back(*pt);
    }
    
    return {upper_hull, lower_hull};
}

long double dist(const Point &a, const Point &b, const Point &c) {
    long double area = Vector::prod({a, b}, {a, c});
    long double len = Vector(a, b).len();
    
    return abs(area / len);
}

long double opt_dist(const Point &l, const Point &p, const Point &r, 
                     Vector left, Vector right) {
    Vector v_r{p, r};
    Vector v_l{p, l};
    
    if (Vector::prod(v_r, v_l) < 0) {
        swap(v_l, v_r);
        left *= -1;
        right *= -1;
    }
    
    long double ans = max(dist(p, p+right, p + v_l), dist(p, p+right, p + v_r));
    ans = min(ans, max(dist(p, p+left, p + v_l), dist(p, p+left, p + v_r)));
    
    Vector left_90({left.y, -left.x});
    Vector right_90({-right.y, right.x});
    
    if (Vector::prod(right_90, left) >= 0) {
        left = right_90;
        right = left_90;
    }
    
    const long double eps = 1e-5;
    while(abs(dist(p, p+left, p + v_l) - dist(p, p+right, p + v_l)) > eps ||
          abs(dist(p, p+left, p + v_r) - dist(p, p+right, p + v_r)) > eps) {
        Vector diff = (right - left) / 2.0;
        Vector mid = left + diff;
        if (dist(p, p + mid, p + v_l) > dist(p, p + mid, p + v_r))
            right = mid;
        else
            left = mid;
    }
    ans = min(ans, max(dist(p, p+right, p + v_l), dist(p, p+left, p + v_r)));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    Point p;
    vector<Point> points;
    cin >> p.x >> p.y;
    
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        points.emplace_back(x, y);
    }
    
    auto hulls = get_hulls(points);
    
    long double ans = 1e14;
    size_t i = 0, j = 0;
    
    Vector last({0, 1});
    
    while(i < hulls.first.size() - 1 || j < hulls.second.size() - 1) {
        Point p1 = hulls.first[i];
        Point p2 = hulls.second[j];
        Vector next;
        
        if (i == hulls.first.size() - 1) {
            next = Vector(hulls.second[j+1], hulls.second[j]);
            j++;
        } else if (j == hulls.second.size() - 1) {
            next = Vector(hulls.first[i], hulls.first[i+1]);
            i++;
        } else {
            Vector v1(hulls.first[i], hulls.first[i+1]);
            Vector v2(hulls.second[j+1], hulls.second[j]);
            if (Vector::prod(v1, v2) > 0) {
                next = v2;
                j++;
            } else {
                next = v1;
                i++;
            }
        }
        
        ans = min(ans, opt_dist(p1, p, p2, last, next));
        last = next;
    }
    
    ans = min(ans, opt_dist(hulls.first.back(), p, hulls.second.back(), last, Vector({0, -1000})));

    cout << setprecision(20);
    cout << ans << endl;
    return 0;
}

