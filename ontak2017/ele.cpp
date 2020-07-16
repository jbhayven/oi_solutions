#include <bits/stdc++.h>
using namespace std;

#define squared(x) ((long long) (x) * (x))

struct Point {
    int x;
    int y;
    int no;
};

bool create_edges(vector<Point>       &pts, 
                  vector<vector<int>> &edges,
                  long long            diff_dist) {
    if (pts.size() < 2) return true;
    
    size_t half = pts.size() / 2;
    int half_pos = pts[half].x;
    
    vector<Point> left(pts.begin(), pts.begin() + half);
    vector<Point> right(pts.begin() + half, pts.end());
    pts.clear();
    
    if (!create_edges(left, edges, diff_dist)) return false;
    if (!create_edges(right, edges, diff_dist)) return false;
    
    /* Merge */
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i].y <= right[j].y)
            pts.push_back(left[i++]);
        else
            pts.push_back(right[j++]);
    }
    
    while (i < left.size())
        pts.push_back(left[i++]);
    while (j < right.size()) 
        pts.push_back(right[j++]);
        
    vector<Point> middle;
    for (const Point& p : pts) 
        if (squared(p.x - half_pos) <= diff_dist)
            middle.push_back(p);
            
    for (i = 0, j = 0; i < middle.size(); i++) {
        while(j < middle.size() 
              && squared(middle[j].y - middle[i].y) <= diff_dist) {
            j++;
        }
        if (j - i > 6) return false;
        for (size_t k = i + 1; k < j; k++) {
            if (squared(middle[i].x - middle[k].x) 
                + squared(middle[i].y - middle[k].y) <= diff_dist) {
                edges[middle[i].no].push_back(middle[k].no);
                edges[middle[k].no].push_back(middle[i].no);
            }
        }
    }
    
    return true;
}

vector<int> get_whites(const vector<vector<int>> &edges, int n) {
    vector<bool> visited(n, false);
    vector<bool> is_white(n, false);
    
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        
        stack<int> to_visit;
        to_visit.push(i);
        visited[i] = true;
        
        while (!to_visit.empty()) {
            int v = to_visit.top();
            to_visit.pop();
            
            for (int close : edges[v]) {
                if (visited[close]) {
                    if (is_white[close] == is_white[v])
                        throw runtime_error("Cannot assign colours");
                } else {
                    visited[close] = true;
                    is_white[close] = !is_white[v];
                    to_visit.push(close);
                }
            }
        }
    }
    
    vector<int> result;
    for (int i = 0; i < n; i++)
        if (is_white[i]) 
            result.push_back(i);
    
    return result;
}

bool check_is_correct(const vector<vector<int>> &edges, int n) {
    try {
        get_whites(edges, n);
    } catch (runtime_error& e) {
        return false;
    }
    
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n; cin >> n;
    
    vector<Point> pts(n);
    for (int i = 0; i < n; i++) {
        pts[i].no = i;
        cin >> pts[i].x >> pts[i].y;
    }
    sort(pts.begin(), pts.end(), 
        [](const Point &a, const Point &b){
            return a.x < b.x;
        });
    
    long long ans_min = 0;
    long long ans_max = 1e18 + 6;
    
    while (ans_min < ans_max) {
        long long mid = (ans_min + ans_max) / 2;
        
        vector< Point > pts_cpy(pts);
        vector< vector<int> > edges(n);
        if (create_edges(pts_cpy, edges, mid)
            && check_is_correct(edges, n)) {
            ans_min = mid + 1;
        }
        else {
            ans_max = mid;
        }
    }
    
    cout << ans_min << endl;
    
    vector< vector<int> > edges(n);
    create_edges(pts, edges, ans_min - 1);
    vector<int> whites = get_whites(edges, n);
    vector<bool> is_white(n, false);
    
    cout << whites.size() << endl;
    
    for (int i : whites) {
        is_white[i] = true;
        cout << i + 1 << " ";
    }
    cout << endl;
    
    vector<int> blacks;
    for (int i = 0; i < n; i++) {
        if (is_white[i]) continue;
        blacks.push_back(i);
    }
    
    cout << blacks.size() << endl;
    for (int i : blacks)
        cout << i + 1 << " ";
    cout << endl;
    
    return 0;
}
