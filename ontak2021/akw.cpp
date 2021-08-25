#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 500100;
int n, q;
int result;

struct FU {
    
    struct info {
        int best;
        int flooded;
        
        info () : best(0), flooded(0) {}
        
        void merge(info &other) {
            best += other.best;
            flooded += other.flooded;
        }
        
        int upd_flooded(int change) {
            flooded += change;
            
            if (flooded > best) {
                int diff = flooded - best;
                
                best = flooded;
                return diff;
            } else {
                return 0;
            }
        }
    } i;
    
    FU* p;
    
    FU* F () {
        return p == this ? p : (p = p->F());
    }
    
    void U (FU &other) {
        FU* p1 = F();
        FU* p2 = other.F();
        
        if (p1 == p2) return;
         
        p1->p = p2;
        p2->i.merge(p1->i);
    }
    
    FU () : p(this) {}
    
    int upd(int change) {
        return F()->i.upd_flooded(change);
    }
    
} segment[MAX_N];

struct req_info {
    int x;
    int w;
    int s;
};

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n >> q;
    
    vector< pair<int, int> > unif(n-1);
    for (int i = 0; i < n-1; i++) {
        cin >> unif[i].first;
        unif[i].second = i+1; 
    }
    sort(unif.begin(), unif.end());
    unif.emplace_back(2e9, -1);
    
    vector< req_info > reqs(q);
    for (auto &i : reqs) {
        cin >> i.x >> i.w >> i.s;
        result += (i.s == 0);
    }
    sort(reqs.begin(), reqs.end(), [](req_info &a, req_info &b){ return a.w < b.w; });
    
    int i = 0, j = 0;
    while (j < q) {
        while (unif[i].first < reqs[j].w) {
            segment[unif[i].second].U(segment[unif[i].second + 1]);
            i++;
        }
        
        unordered_map<FU*, int> upd;
        
        do {
            upd[segment[reqs[j].x].F()] += reqs[j].s ? 1 : -1;
            j++;
        } while (j < q && reqs[j].w == reqs[j-1].w);
    
        for (auto &i : upd) {
            result += i.first->upd(i.second);
        }
    }
    
    cout << result << endl;
    
    return 0;
}
