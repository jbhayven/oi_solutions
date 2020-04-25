#include <bits/stdc++.h>
using namespace std;

struct coord_t {
    int x;
    int y;
    
    void rot45() {
        int new_y = y - x;
        int new_x = x + y;
        
        x = new_x;
        y = new_y;
    }

    bool operator<(coord_t other) {
        if(this->x < other.x) return true;
        if(this->x > other.x) return false;
        
        return this->y > other.y;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    
    vector<coord_t> pts(n);
    for(coord_t &point: pts) {
        cin >> point.x >> point.y;
        point.rot45();
    }
    
    sort(pts.begin(), pts.end());
    
    set<int> lines;
    
    for(coord_t point : pts) {
        auto found = lines.lower_bound(point.y);
        
        if(found != lines.end())
            lines.erase(found);
    
        lines.insert(point.y);
    }
    
    cout << lines.size() << endl;
    return 0;
}
