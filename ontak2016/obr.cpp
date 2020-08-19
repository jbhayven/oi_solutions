#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

struct Vector {
    int x, y;
    Point a, b;
    
    Vector(Point a, Point b) : x(b.x - a.x), y(b.y - a.y), a(a), b(b) {}
    
    long long operator*(const Vector &other) const {
        return (long long) x * other.y - (long long) y * other.x;
    }
    
    long double len() {
        return sqrt((long long) x * x + (long long) y * y);
    }
    
    long double dist(Point p) {
        long double area = (Vector(a, p) * Vector(p, b));
        return abs(area / len());
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, k;
    cin >> n >> k;
    
    vector<Point> points(n);
    vector<Vector> vectors;
    
    for (Point &p : points)
        cin >> p.x >> p.y;
    
    sort (points.begin(), points.end(), 
        [](Point a, Point b){ return make_pair(a.x, a.y) < make_pair(b.x, b.y); });
    
    for (Point &p : points)
        for (Point &q : points) 
            if (make_pair(p.x, p.y) < make_pair(q.x, q.y))
                vectors.emplace_back(p, q);
    
    auto angular = [](Vector a, Vector b){ return (a * b) > 0; };
    sort(vectors.begin(), vectors.end(), angular);
    
    map<pair<int, int>, int> to_right;
    map<int, Point> with_score;
    
    for (int i = 0; i < n; i++) {
        to_right[{points[i].x, points[i].y}] = i;
        with_score[i] = points[i];
    }
    
    long double result = 1e14;
    
    for (Vector &v : vectors) {
        int curr_score = to_right.at({v.b.x, v.b.y});
        
        if (curr_score + 1 >= k)
            result = min(result, v.dist(with_score.at(curr_score + 1 - k)) / 2);
        if (curr_score + k - 2 < n)
            result = min(result, v.dist(with_score.at(curr_score + k - 2)) / 2);
        
        to_right[{v.a.x, v.a.y}]++;
        to_right[{v.b.x, v.b.y}]--;
        with_score[curr_score] = v.a;
        with_score[curr_score - 1] = v.b;
    }
    
    cout << setprecision(12) << result << endl;
    
    return 0;
}
