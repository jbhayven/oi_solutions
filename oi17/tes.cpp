#include <bits/stdc++.h>
using namespace std;

array<vector<int>, 1000100> waiting;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int m, n;
    cin >> m;
    
    vector<int> patt(m);
    for (int &a : patt) cin >> a;
    
    cin >> n;
    
    vector<vector<int>> seq(n);
    vector<size_t> pos(n, 0);
    
    for (auto &s : seq) {
        int m_i; cin >> m_i;
        s.resize(m_i);
        for (int &a : s)
            cin >> a;
    }
    
    for (int i = 0; i < n; i++)
        waiting[seq[i][0]].push_back(i);
    
    for (int a : patt) {
        vector<int> to_handle = move(waiting[a]);
        
        for (int s : to_handle) {
            pos[s]++;
            if (pos[s] == seq[s].size()) 
                continue;
            
            int new_num = seq[s][pos[s]];
            waiting[new_num].push_back(s);
        }
    }
    
    for (int i = 0; i < n; i++) 
        cout << (pos[i] == seq[i].size() ? "TAK" : "NIE") << endl;
    
    return 0;
}
