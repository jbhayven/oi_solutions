#include <bits/stdc++.h>
using namespace std;

struct FU {
    FU* p;
    
    FU () : p(this) {}
    
    FU* find() {
        return (p == p->p ? p : p = p->find());
    }
    
    void UNION(FU &other) {
        FU* a = find();
        FU* b = other.find();
        
        if (a != b) a->p = b;
    }
};

const int MAX_M = 350000;
struct e {
    int u, v;
    int len;
    bool ans;
} edges[MAX_M];

const int MAX_N = 10000;
FU comp[MAX_N];

const int MAX_LEN = 110000;
vector<e*> cand[MAX_LEN];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].len;
        cand[edges[i].len].push_back(&edges[i]);
    }
    
    for (int i = 1; i < MAX_LEN; i++) {
        for (e* edge : cand[i]) {
            int u = edge->u;
            int v = edge->v;
            if (comp[u].find() == comp[v].find())
                edge->ans = false;
            else
                edge->ans = true;
        }
        for (e* edge : cand[i]) {
            comp[edge->u].UNION(comp[edge->v]);
        }
    }
    
    for (int i = 1; i <= m; i++) {
        cout << (edges[i].ans ? "TAK" : "NIE") << std::endl;
    }
    
    return 0;
}
