#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

using Point = pair<int, int>;

long long prod(Point p1, Point p2, Point p3) {
    return (long long) (p2.x - p1.x) * (p3.y - p1.y) - 
           (long long) (p3.x - p1.x) * (p2.y - p1.y);
}

list<Point> get_hull(vector<Point> &pts) {
    if (pts.size() < 2)
        return list<Point>(pts.begin(), pts.end());
    
    sort(pts.begin(), pts.end());
    vector<Point> top_hull;    
    for (auto pt : pts) {
        while(top_hull.size() >= 2 
            && prod(top_hull.end()[-2], top_hull.end()[-1], pt) >= 0)
            top_hull.pop_back();
            
        top_hull.push_back(pt);
    }
    
    reverse(pts.begin(), pts.end());
    vector<Point> bottom_hull;
    for (auto pt : pts) {
        while(bottom_hull.size() >= 2 
            && prod(bottom_hull.end()[-2], bottom_hull.end()[-1], pt) >= 0)
            bottom_hull.pop_back();
            
        bottom_hull.push_back(pt);
    }
    
    top_hull.pop_back();
    bottom_hull.pop_back();
    
    list<Point> results(top_hull.begin(), top_hull.end());
    results.insert(results.end(), bottom_hull.begin(), bottom_hull.end());
    
    return results;
}

bool try_wall(const list<Point> &wall_points, 
              const list<Point> &bad_points) {
                  
    if (wall_points.size() < 2) {
        if (bad_points.size() < 2) return true;
        return false;
    }
    
    for (auto it1 = wall_points.begin(), it2 = ++wall_points.begin();
        it2 != wall_points.end(); it1++, it2++) {
            
        bool possib = true;
        for (auto pt : bad_points) 
            if (prod(*it1, *it2, pt) <= 0) {
                possib = false;
                break;
            }
        
        if (possib == true) 
            return true;
    }
    
    bool possib = true;
    for (auto pt : bad_points) 
        if (prod(wall_points.back(), wall_points.front(), pt) <= 0) {
            possib = false;
            break;
        }
            
    return possib;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; 
    vector<Point> bajtocja;
    vector<Point> bitocja;
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y, t;
        cin >> t >> x >> y;
        if (t == 1) 
            bitocja.push_back({x, y});
        else 
            bajtocja.push_back({x, y});
    }
        
    list<Point> bajthull = get_hull(bajtocja);
    list<Point> bithull = get_hull(bitocja);
    
    if (try_wall(bajthull, bithull) || try_wall(bithull, bajthull)) 
        cout << "TAK" << endl;
    else
        cout << "NIE" << endl;
        
    return 0;
}
