#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-8;

struct Point {
    long double x, y;
    
    Point () : x(0), y(0) {}
    Point (long double x, long double y) : x(x), y(y) {}
};

struct Vector {
    long double x;
    long double y;
    
    Vector () : x(0), y(0) {}
    
    Vector (long double x, long double y) : x(x), y(y) {}
    
    Vector (Point a, Point b) : 
        x(b.x - a.x), 
        y (b.y - a.y) {}
        
    long double len() const {
        return sqrt(x*x + y*y);
    }
    
    long double prod(const Vector &other) const {
        return other.y * x - other.x * y;
    }
    
    Vector operator*=(long double a) {
        x *= a;
        y *= a;
        return *this;
    }
};

double sgn(long double a) {
    return abs(a) < eps ? 0 : a / abs(a);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    Point o; cin >> o.x >> o.y;
    long double R; cin >> R;
    int n; cin >> n;
    
    vector<Point> pts(n);
    for (auto &p : pts) cin >> p.x >> p.y;
    pts.push_back(pts[0]);
    
    long double ans = 0;
    for (int i = 0; i < n; i++) {
        if (pts[i].x == o.x && pts[i].y == o.y) continue;
        if (pts[i+1].x == o.x && pts[i+1].y == o.y) continue;
        
        auto v1 = Vector(o, pts[i]);
        auto v2 = Vector(o, pts[i+1]);
        auto mid = Vector(pts[i], pts[i+1]);
        
        if (v1.len() < eps || v2.len() < eps || abs(v1.prod(v2)) < eps) continue;
        
        double mult = 1;
        long double add = 0;
        if (v1.prod(v2) < 0) {
            swap(v1, v2);
            mid *= -1;
            mult = -1;
        }
        
        if (v1.len() <= R && v2.len() <= R) {
            add += v1.prod(v2) / 2;
        } else {
            long double dist = (long double) v1.prod(mid) / mid.len();
            
            auto perpend = Vector(mid.y, -mid.x);
            perpend *= (dist / perpend.len());
            
            long double ang1 = acos(dist / v1.len());
            long double ang2 = acos(dist / R);
            long double ang3 = acos(dist / v2.len());
            
            if (v1.len() <= R) {
                add += dist * dist * (tan(ang2) * 2) / 4;
                add += v1.prod(perpend) / 2;
                
                add += (R * R) * (ang3 - ang2) / 2;
            } else if (v2.len() <= R) {
                add += (R * R) * (ang1 - ang2) / 2;
                
                add += dist * dist * (tan(ang2) * 2) / 4;
                add += perpend.prod(v2) / 2;
            } else {
                if (abs(dist) >= R || sgn(v1.prod(perpend)) == sgn(v2.prod(perpend))) {
                    add += (R * R) * (ang1 * sgn(v1.prod(perpend)) + ang3 * sgn(perpend.prod(v2))) / 2;
                } else {
                    add += (R * R) * (ang1 - ang2) / 2;
                    
                    add += dist * dist * (tan(ang2) * 2) / 2;
                
                    add += (R * R) * (ang3 - ang2) / 2;
                }
            }
        }
        
        add *= mult;
        ans += add;
    }
    
    if (abs(ans) < eps)
        cout << 0 << endl;
    else cout << setprecision(20) << abs(ans) << endl;
    
    return 0;
}
