#include <bits/stdc++.h>
using namespace std;

#define MAX_M 300100

int ans[MAX_M];

struct Edge {
    int u;
    int v;
    int number;
    
    Edge(int u, int v, int number) :
        u(u), v(v), number(number) {}
};

inline void do_dfs1(int v, const vector<vector<int>>& edges, 
    vector<bool>& visited, stack<int>& rev_order) {
        
    visited[v] = true;
    
    for (int dest : edges[v]) {
        if (visited[dest]) continue;
        
        do_dfs1(dest, edges, visited, rev_order);
    }
    
    rev_order.push(v);
}

inline void do_dfs2(int v, const vector<vector<int>>& edges, 
    vector<bool>& visited, vector<int>& which_comp, int comp) {
        
    visited[v] = true;
    
    for (int dest : edges[v]) {
        if (visited[dest]) continue;
        
        do_dfs2(dest, edges, visited, which_comp, comp);
    }
    
    which_comp[v] = comp;
}

void find_ans(const vector<Edge>& edges, int nodes, int size, int l, int r) {
    if (l > r) return;
    int s = (l + r) / 2;
    
    vector<vector<int>> norm(size  + 1);
    vector<vector<int>> rev(size + 1);
    vector<bool> visited(size + 1, false);
    
    for (const Edge& e : edges) {
        if (e.number > s) continue;
        
        norm[e.u].push_back(e.v);
        rev[e.v].push_back(e.u);
    }
    
    stack<int> rev_order;
    
    for (int i = 1; i <= size; i++) {
        if (visited[i]) continue;
        
        do_dfs1(i, norm, visited, rev_order);
    }
    
    fill(visited.begin(), visited.end(), false);

    int comp = 0;
    int visited_cnt = rev_order.size();
    vector<int> which_comp(size + 1, 0);
    
    while (!rev_order.empty()) {
        int v = rev_order.top();
        rev_order.pop();
        if (visited[v]) continue;
        
        comp++;
        do_dfs2(v, rev, visited, which_comp, comp);
    }
    
    int delta = comp - visited_cnt;
    ans[s] = nodes + delta; 
    
    int l_size = 0;
    vector<int> mappings(size + 1, 0);
    vector<Edge> left, right;
    for (Edge e : edges) {
        int comp1, comp2;
        
        if (which_comp[e.u] == 0)
            which_comp[e.u] = ++comp;
            
        if (which_comp[e.v] == 0)
            which_comp[e.v] = ++comp;
        
        comp1 = which_comp[e.u];
        comp2 = which_comp[e.v];
        
        if (comp1 == comp2) {
            if (mappings[e.u] == 0)
                mappings[e.u] = ++l_size;
                
            if (mappings[e.v] == 0)
                mappings[e.v] = ++l_size;
            left.push_back(Edge(mappings[e.u], 
                                 mappings[e.v], 
                                 e.number));
        }
        else
            right.push_back(Edge(comp1, comp2, e.number));
    }
    
    find_ans(left, nodes, l_size, l, s-1);
    find_ans(right, nodes + delta, comp, s+1, r);
}    

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m; cin >> n >> m;
    
    vector<Edge> edges;
    
    int a, b; 
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        edges.push_back(Edge(a, b, i));
    }
    
    find_ans(edges, n, n, 0, m-1);
    
    for (int i = 0; i < m; i++) 
        cout << ans[i] << " ";
    cout << endl;

    return 0;
}
