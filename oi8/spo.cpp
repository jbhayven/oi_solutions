#include <bits/stdc++.h>
using namespace std;

struct Component {
    vector<Component*> from;
    vector<int> in;
    bool is_okay;
    
    Component() : is_okay(true) {}
    
    void mark_bad() {
        if (is_okay == false) return;
        
        is_okay = false;
        for (Component* c : from)
            c->mark_bad();
    }
};

void do_dfs(vector<bool> &visited, vector<vector<int>> &neighbours, int v, const function<void(int)> &func) {
    visited[v] = true;
    for (int i : neighbours[v]) 
        if (!visited[i])
            do_dfs(visited, neighbours, i, func);
    func(v);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> wym(2*n);
    vector<vector<int>> anti_wym(2*n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        wym[a].push_back(b^1);
        wym[b].push_back(a^1);
        anti_wym[a^1].push_back(b);
        anti_wym[b^1].push_back(a);
    }
    
    vector<bool> visited(2*n, false);
    
    /* Order reverse-topologically */
    stack<int> back_order;
    auto first_func = [&](int v){ back_order.push(v); };
    
    for (int i = 0; i < 2*n; i++) {
        if (visited[i]) continue;
        do_dfs(visited, wym, i, first_func);
    }
    
    /* Create components */
    visited = vector<bool>(2*n, false);
    vector<Component*> is_in(2*n);
    vector<Component> comps;
    comps.reserve(2*n);
    auto back_func = [&](int v){ 
        for (int j : anti_wym[v])
            if (is_in[j] != is_in[v])
                comps.back().from.push_back(is_in[j]);
                
        comps.back().in.push_back(v); 
        is_in[v] = &comps.back(); 
    };
    
    while(!back_order.empty()) {
        int top = back_order.top();
        back_order.pop();
        if (visited[top]) continue;
        comps.emplace_back();
        do_dfs(visited, anti_wym, top, back_func);
    }
    
    /* If two opposite versions force each other 
     * (are in the same component), no solution exists */
    for (int i = 0; i < n; i++) if (is_in[2*i] == is_in[2*i+1]) {
        cout << "NIE" << endl;
        exit(0);
    }
    
    /* Else collect from topologically highest, exclude conflicts */
    vector<int> deputies;
    
    for (auto cp = comps.rbegin(); cp != comps.rend(); cp++) {
        if (cp->is_okay == false)
            continue;
        
        for (int i : cp->in) {
            deputies.push_back(i);
            is_in[i^1]->mark_bad();
        }
    }
    
    sort(deputies.begin(), deputies.end());
    for (int d : deputies)
        cout << d + 1 << endl;
    
    return 0;
}
