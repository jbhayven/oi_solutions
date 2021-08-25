#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 10;

int n;
int l;
vector<int> neigh[MAX_N];
int p[MAX_N];

pair<int, int> max_son[MAX_N];
int max_result[MAX_N];

int result = 0;

void ukorzen(int i) {
    max_son[i] = {1, i};
    
    for (auto j : neigh[i]) {
        if (p[i] == j) continue;
        
        p[j] = i;
        ukorzen(j);
    
        max_son[i] = max(max_son[i], make_pair(max_son[j].first + 1, j));
    }
}

void add(int i, priority_queue<pair<int, int>> &cand, int depth = -1) {
    for (auto j : neigh[i]) {
        if (p[i] == j || max_son[i].second == j) 
            continue;
        
        cand.push(make_pair(max_son[j].first - depth, max_son[j].second));
    }
    
    if (max_son[i].second != i)
        add(max_son[i].second, cand, depth == -1 ? -1 : depth + 1);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); 
    
    cin >> n >> l;
    
    if (l == 0) {
        cout << 0 << endl;
        exit(0);
    }
    
    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        neigh[a].push_back(b);
        neigh[b].push_back(a);
    }
    
    p[1] = -1;
    ukorzen(1);
    
    priority_queue< pair<int, int> > cand;
    cand.push(make_pair(max_son[1].first, 1));
    
    while (l && !cand.empty()) {
        auto top = cand.top(); cand.pop();
        std::cout << top.first << " " << top.second << std::endl;
        
        priority_queue< pair<int, int> > reserve;
        add(top.second, reserve, 0);
        
        if (!cand.empty()) {
            reserve.push(cand.top());
            if (reserve.top() == cand.top()) 
                cand.pop();
        }
            
        result += top.first;
        add(top.second, cand);
        
        if (!reserve.empty()) {
            result += reserve.top().first;
            add(reserve.top().second, cand);
        }
    }
    
    cout << result << endl;
    
    return 0;
}
