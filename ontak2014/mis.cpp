#include <bits/stdc++.h>
using namespace std;

struct inter {
    int min_x;
    int max_x;
    int min_y;
    int max_y;
};

bool fits(const inter &a, const inter &b) {
    if (b.min_x > a.max_x) return false;
    if (b.max_x < a.min_x) return false;

    if (b.min_y > a.max_y) return false;
    if (b.max_y < a.min_y) return false;
    
    return true;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int a, b; cin >> a >> b;
    int n; cin >> n;
    vector<inter> proste(n + 1);
    proste[0] = { .min_x = a, .max_x = a, .min_y = b, .max_y = b };
    for (int i = 1; i <= n; i++)
        cin >> proste[i].min_x >> proste[i].min_y >> proste[i].max_x >> proste[i].max_y;
        
    set<int> interesting_points;
    for (auto &p : proste) {
        interesting_points.insert(abs(p.min_x));
        interesting_points.insert(abs(p.max_x));
        interesting_points.insert(abs(p.min_y));
        interesting_points.insert(abs(p.max_y));
    }
    
    inter curr_rect{ .min_x = 0, .max_x = 0, .min_y = 0, .max_y = 0 };
    vector<int> dist(n + 1, -1);
    for (int pt : interesting_points) {
        curr_rect.min_x = min(curr_rect.min_x, -pt);
        curr_rect.min_y = min(curr_rect.min_y, -pt);
        
        curr_rect.max_x = max(curr_rect.max_x, pt);
        curr_rect.max_y = max(curr_rect.max_y, pt);
        
        bool got;
        do {
            got = false;
            for (int i = 0; i <= n; i++) {
                if (dist[i] == -1 && fits(curr_rect, proste[i])) {
                    dist[i] = pt;
                    curr_rect.min_x = min(curr_rect.min_x, proste[i].min_x);
                    curr_rect.min_y = min(curr_rect.min_y, proste[i].min_y);
                    
                    curr_rect.max_x = max(curr_rect.max_x, proste[i].max_x);
                    curr_rect.max_y = max(curr_rect.max_y, proste[i].max_y);
                    got = true;
                }
            }
        } while (got);
    }
    
    cout << dist[0] << endl;
    
    return 0;
}
