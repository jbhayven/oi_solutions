#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 3010;

vector<int> graph[MAX_N];
vector<int> inv[MAX_N];

struct comp_t {
    vector<int> vertices;
};

vector<comp_t> components;
int component[MAX_N];
vector<int> przekupny(MAX_N, -1);

void DFS(int i, const vector<int> graph[], 
                vector<bool> &visited, 
                vector<int> &order) {
    visited[i] = true;
    
    for(int neighbour : graph[i])
        if(visited[neighbour] == false)
            DFS(neighbour, graph, visited, order);
    order.push_back(i);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, p;
    cin >> n >> p;
    while(p--) {
        int no, price;
        cin >> no >> price;
        przekupny[no] = price;
    }
    
    int r;
    cin >> r;
    while(r--) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        inv[b].push_back(a);
    }
    
    vector<bool> visited(n+1, false);
    vector<int> order;
    for(int i = 1; i <= n; i++) 
        if(visited[i] == false)
            DFS(i, graph, visited, order);
    
    visited = vector<bool>(n+1, false);
    while(!order.empty()) {
        int cand = order.back();
        order.pop_back();
        if(visited[cand] == false) {
            components.push_back(comp_t());
            DFS(cand, inv, visited, components.back().vertices);
            for(int v : components.back().vertices)
                component[v] = components.size() - 1;
        }
    }
    
    visited = vector<bool>(components.size(), false);
    
    int min_cost = 0;
    for(size_t i = 0; i < components.size(); i++) {
        if(visited[i] == false) {
            visited[i] = true;
            int temp_min = INT_MAX;
            for(int v : components[i].vertices) {
                if(przekupny[v] != -1) temp_min = min(temp_min, przekupny[v]);
            }
            
            if(temp_min == INT_MAX)
                visited[i] = false;
            else 
                min_cost += temp_min;
        }
        
        if(visited[i] == true)
            for(int v : components[i].vertices)
                for(int neighbour : graph[v])
                    visited[component[neighbour]] = true;
    }
    
    // Trzeba wypisać numer agenta o najmniejszym numerze (według wzorcówki)
    for(int i = 1; i <= n; i++)
        if(visited[component[i]] == false) {
            cout << "NIE" << endl;
            cout << i << endl;
            return 0;
        }
    
    cout << "TAK" << endl;
    cout << min_cost << endl;
    
    return 0;
}
