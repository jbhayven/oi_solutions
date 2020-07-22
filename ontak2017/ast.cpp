#include <bits/stdc++.h>
using namespace std;

class Asteroid {
    const int mass;
    const Asteroid *p1;
    const Asteroid *p2;
    
    struct Range {
        vector<pair<int, int>> subranges;
        
        Range (const vector<pair<int, int>> v) : subranges(v) {}
        
        int get_min_necess(int val) const {
            for (auto rng : subranges) {
                if (rng.second < val) continue;
                
                int smol_add = (max(val, rng.first) - val);
                if (2 * smol_add < val)
                    return smol_add;
                
                if (2 * val < smol_add)
                    return smol_add; // actually very big
                
                int big_add = 2 * val + 1;
                if (val + big_add <= rng.second)
                    return big_add;
            }
            assert(false);
        }
        
        void add(int reductor) {
            for (auto &rng : subranges) {
                rng.first += reductor;
                rng.second += reductor;
            }
        }
        
        void drop_less(int limit) {
            vector<pair<int, int>> new_ranges;
            for (auto rng : subranges) {
                if (rng.second < limit) continue;
                new_ranges.push_back({max(rng.first, limit), rng.second});
            }
            subranges = new_ranges;
        }
        
        bool can_zero() const {
            for (auto rng : subranges) 
                if (rng.first <= 0 && 0 <= rng.second) 
                    return true;
            return false;
        }
        
        void cut_out(int a, int b) {
            vector<pair<int, int>> new_ranges;
            for (auto rng : subranges) {
                if (rng.second < a || b < rng.first) {
                    new_ranges.push_back(rng);
                    continue;
                }
                
                if (rng.first < a)
                    new_ranges.push_back({rng.first, a-1});
                if (b < rng.second)
                    new_ranges.push_back({b+1, rng.second});
            }
            subranges = new_ranges;
        }
        
        void add_rng(int a, int b) {
            cut_out(a, b);
            vector<pair<int, int>> new_ranges;
            for (auto rng : subranges) {
                if (rng.first >= b) break;
                new_ranges.push_back(rng);
            }
            new_ranges.push_back({a, b});
            for (auto rng : subranges) {
                if (rng.first <= b) continue;
                new_ranges.push_back(rng);
            }
            subranges = new_ranges;
        }
    };
    
public:
    Asteroid(int mass) : 
        mass(mass), p1(nullptr), p2(nullptr) {}
    
    Asteroid(Asteroid *p1, Asteroid *p2) :
        mass(p1->mass > 2 * p2->mass || p2->mass > 2 * p1->mass ? 
             p1->mass + p2->mass : 0),
        p1(p1), p2(p2) {}
    
    int ans(int minim_mass) const {
        return ans(Range({{minim_mass, 1e9}}));
    }
    
    int process(const Asteroid *p1, const Asteroid *p2, const Range &r) const {
        Range sub_r(r);
        
        sub_r.add(-p2->mass);
        
        if (!r.can_zero())
            sub_r.cut_out((p2->mass + 1) / 2, 2 * p2->mass);
        else 
            sub_r.add_rng((p2->mass + 1) / 2, 2 * p2->mass);
        
        sub_r.drop_less(0);
        
        return p1->ans(sub_r);
    }
    
    int ans(const Range &r) const {
        int result = r.get_min_necess(mass);
        if (r.can_zero()) result = min(result, (mass + 1) / 2);
        if (p1 == nullptr && p2 == nullptr) 
            return result;
        
        result = min(result, process(p1, p2, r));
        result = min(result, process(p2, p1, r));
        
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m;
    vector<Asteroid> ast;
    
    cin >> n >> m;
    ast.reserve(2*n);
    for (int i = 0; i < n; i++) {
        int mass; cin >> mass;
        ast.push_back(Asteroid(mass));
    }
    
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        ast.push_back(Asteroid(&ast[a], &ast[b]));
    }
    
    int ans = ast.back().ans(m);
    
    if (ans > 0) 
        cout << 1 << " " << ans << endl;
    else 
        cout << 0 << " " << 0 << endl;
    
    return 0;
}
