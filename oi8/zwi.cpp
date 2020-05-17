#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10100;

struct edge {
    pair<int, int> v;
    int len;
    int impression;
    
    edge(int a, int b, int l, int i) :
        v({a, b}),
        len(l),
        impression(i)
    {}
    
    int other(int u) {
        if(v.first == u) return v.second;
        return v.first;
    }
};

vector<int> graph[MAX_N];
vector<edge> edges;

int n;

list<pair<int, int>> generate_euler(int u) {
    static vector<bool> visited(2*n + 1, false);
    
    list<pair<int, int>> result;
    
    int src = u;
    do {
        for(int edge_no : graph[src]) {
            if(visited[edge_no]) continue;
            
            visited[edge_no] = true;
            
            result.push_back(make_pair(src, edge_no));
            src = edges[edge_no].other(src);
            break;
        }
    } while(src != u);
    
    for(auto it = result.begin(); it != result.end(); it++)
        result.splice(it, (generate_euler(it->first)));
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int total_len = 0;
    int total_impression = 0;
    
    cin >> n;
    for(int i = 0; i < 2*n; i++) {
        int a, b, l, inf;
        cin >> a >> b >> l >> inf;
        
        total_len += l;
        total_impression += inf;
        
        edges.push_back(edge(a, b, l, inf));
        
        graph[a].push_back(i);
        graph[b].push_back(i);
    }
    
    if(total_len > total_impression) {
        cout << "NIE" << endl;
        return 0;
    }
    
    auto euler = generate_euler(1);
    list<int> impression_deltas;
    
    auto it1 = euler.begin();
    auto it2 = ++euler.begin();
    
    euler.push_back(euler.front());
    while(it2 != euler.end()) {
        edge e1 = edges[it1->second];
        edge e2 = edges[it2->second];
        
        impression_deltas.push_back(e1.impression - (e1.len + e2.len) / 2);
        
        it1++;
        it2++;
    }
    euler.pop_back();
    int curr_impression = 0;
    for(int delta : impression_deltas) {
        while(curr_impression < 0) {
            euler.push_back(euler.front());
            euler.pop_front();
            
            impression_deltas.push_back(impression_deltas.front());
            curr_impression -= impression_deltas.front();
            impression_deltas.pop_front();
        }
        curr_impression += delta;
    }
    
    cout << "TAK" << endl;
    cout << 2*n << endl;
    cout << euler.front().second + 1 << " " 
         << edges[euler.front().second].other(euler.front().first) << endl;;
    euler.pop_front();
    for(auto i : euler)
        cout << i.second + 1 << endl;
    
    return 0;
}
