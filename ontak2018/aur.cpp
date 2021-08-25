#include <bits/stdc++.h>
using namespace std;
struct Point {
    long long x;
    long long y;
};

struct Vector {
    long long x;
    long long y;
    double result;
    
    double len() const {
        return sqrt(x * x + y * y);
    }
    
    long long operator*(const Vector &other) const {
        return x * other.y - y * other.x;
    }
    
    Vector() : x(0), y(0) {}
    
    Vector(int x, int y) : 
        x(x), 
        y(y) {}

    Vector(Point from, Point to) : 
        x(to.x - from.x), 
        y(to.y - from.y) {}
        
    friend Point operator+(const Point &p, const Vector &other) {
        return Point{ .x = p.x + other.x, .y = p.y + other.y };
    }
};

pair<double, double> solve_quad(double a, double b, double c) {
    double delta = b * b - 4 * a * c;
    
    return make_pair((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
}

double r;

double get_dist(Point start, Point to, const Vector dir) {
    Vector diff_vec(start, to);
    Vector third(start + dir, to);
    
    double len_a = diff_vec.len();
    double len_b = dir.len();
    double len_c = third.len();
    
    double minucosalfa2a = ((len_c * len_c) - (len_a * len_a) - (len_b * len_b)) / len_b;
    
    auto solve = solve_quad(1, minucosalfa2a, len_a * len_a - r * r);
    
    return max(solve.first, solve.second);
}

pair<double, const Point*> get_opt(Point start, const vector<Point> &pts, const Vector v) {
    double opt = 1e18;
    const Point *ptr = nullptr;
    
    for (auto &pt : pts) {
        double dist = get_dist(start, pt, v);
        if (dist < opt) {
            opt = dist;
            ptr = &pt;
        }
    }
    
    return make_pair(opt, ptr);
}

void update_result(int p, int r, Point start,
                   const vector<Point> &pts, 
                   const vector<Vector*> &lines) {
    if (r < p) return;
    
    if (p == r) {
        lines[p]->result = get_opt(start, pts, *lines[p]).first;
        return;
    }
    
    int s = (p + r) / 2;
    
    pair<double, const Point*> left, mid, right;
    
    left = get_opt(start, pts, *lines[p]);
    mid = get_opt(start, pts, *lines[s]);
    right = get_opt(start, pts, *lines[r]);
    
    if (left.second == mid.second) {
        for (int i = p; i <= s; i++)
            lines[i]->result = get_dist(start, *mid.second, *lines[i]);
    } else update_result(p, s, start, pts, lines);
    
    if (mid.second == right.second) {
        for (int i = s + 1; i <= r; i++)
            lines[i]->result = get_dist(start, *mid.second, *lines[i]);
    } else update_result(s + 1, r, start, pts, lines);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    Point start;
    int n, q;

    cin >> start.x >> start.y >> r;
    cin >> n;
    
    vector<Point> pts(n);
    for (auto &p : pts) 
        cin >> p.x >> p.y;
    
    cin >> q;
    
    vector<Vector> all_vecs(q);
    vector<Vector*> left, right;
    
    for (int i = 0; i < q; i++) {
        cin >> all_vecs[i].x >> all_vecs[i].y;
        if (all_vecs[i].x < 0 || (all_vecs[i].x == 0 && all_vecs[i].y < 0))
            left.push_back(&all_vecs[i]);
        else
            right.push_back(&all_vecs[i]);
    }
    
    auto sorter = [](const Vector *a, const Vector *b) {
        return (*a) * (*b) > 0;
    };
    
    sort(left.begin(), left.end(), sorter); 
    sort(right.begin(), right.end(), sorter); 
    
    update_result(0, left.size() - 1, start, pts, left);
    update_result(0, right.size() - 1, start, pts, right);
    
    for (auto &v : all_vecs) 
        cout << setprecision(20) << v.result << endl;
    
    return 0;
}
