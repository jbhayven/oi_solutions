#include <bits/stdc++.h>
using namespace std;

struct Tree {
    int l, r;
    Tree *left, *right;
    int bonus;
    pair<int, int> result;
    
    Tree (int l, int r) :
        l(l), r(r),
        left(nullptr), right(nullptr),
        bonus(0), result({0, r - l + 1})
    {}
    
    void update(pair<int, int> &a, pair<int, int> b) {
        if (b.first == a.first) a.second += b.second;
        if (b.first < a.first) a = b;
    }
    
    inline pair<int, int> get_real_result() {
        return {result.first + bonus, result.second};
    }
    
    void propagate() {
        int s = (l + r) / 2;
        
        if (left == nullptr) 
            left = new Tree(l, s);
            
        if (right == nullptr) 
            right = new Tree(s + 1, r);
            
        if (!bonus) return;
        
        left->bonus += bonus;
        right->bonus += bonus;
        
        result.first += bonus;
        bonus = 0;
    }
    
    void refresh() {
        if (left == nullptr) return;
        
        result = left->get_real_result();
        update(result, right->get_real_result());
    }
    
    pair<int, int> add_intern(int a, int b, int val) {
        if (a <= l && r <= b) {
            bonus += val;
            return get_real_result();
        }
        
        propagate();
        
        int s = (l + r) / 2;
        
        pair<int, int> res = {INT_MAX, 0};
        
        if (a <= s) update(res, left->add_intern(a, b, val));
        if (b > s) update(res, right->add_intern(a, b, val));
        
        refresh();
    
        return res;
    }
    
    pair<int, int> get_min(int a, int b) {
        return add_intern(a, b, 0);
    }
    
    void add_val(int a, int b, int val) {
        add_intern(a, b, val);
    }
};

struct Change {
    int x;
    int y1, y2;
    int mod;
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n;
    vector<Change> rects[16];
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2, p;
        cin >> x1 >> y1 >> x2 >> y2 >> p;
        
        for (int a = 0; a < 4; a++) {
            for (int b = 0; b < 4; b++) {
                if (((1 << (4 * a + b)) & p) == 0) continue;
                
                int start_x, start_y, end_x, end_y;
                start_x = x1 + a;
                start_y = y1 + b;
                
                if (start_x > x2 || start_y > y2) 
                    continue;
                
                end_x = start_x + 4 * ((x2 - start_x) / 4);
                end_y = start_y + 4 * ((y2 - start_y) / 4);
                
                if (end_x < start_x || end_y < start_y) 
                    continue;
                
                int rem_x = start_x % 4;
                int rem_y = start_y % 4;
                rects[rem_x * 4 + rem_y].push_back({
                    .x = start_x / 4,
                    .y1 = start_y / 4,
                    .y2 = end_y / 4,
                    .mod = 1
                });
                rects[rem_x * 4 + rem_y].push_back({
                    .x = end_x / 4 + 1,
                    .y1 = start_y / 4,
                    .y2 = end_y / 4,
                    .mod = -1
                });
            }
        }
    }
    
    Tree *t = new Tree(0, 1e9);
    
    long long result = 0;
    for (int i = 0; i < 16; i++) {
        sort(rects[i].begin(), rects[i].end(), 
            [](const Change &a, const Change &b) {
                return a.x < b.x;
            });
        
        int x_0 = 0;
        for (auto &c : rects[i]) {
            result += 1000000001LL * (c.x - x_0);
            auto min_info = t->get_min(0, 1e9);
            if (min_info.first == 0) {
                result -= (long long) min_info.second * (c.x - x_0);
            }
            x_0 = c.x;
            t->add_val(c.y1, c.y2, c.mod);
        }
    }
    
    cout << result << endl;
    
    return 0;
}
