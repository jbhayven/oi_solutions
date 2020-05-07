/* Привет всем, кто читает нынешний комментарь! Я не ожидал, что кто-нибудь реально
 * скатит и посмотрит в этот файл, но, видимо, ошибся. Ну ладно же, если вы это 
 * реально случайно (или не случайно) нашли в моей репозитории, напишите мне, 
 * что-ли.
 * 
 * Мне просто интересно узнать, зачем вы сюда посмотрели. Ведь задачка довольно
 * несложная и вы должны успеть решить её даже без подсказки...
 */

#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 3010;

vector<int> inc[MAX_N];
bool is_cyclic[MAX_N];
int a, b, n, m;

void cyclic_DFS(int u, int d = 0, int parent = -1) {
    static vector<int> low(n+1, -1);
    
    low[u] = d;
    for(int v : inc[u]) {
        if(v == parent) continue;
        
        if(low[v] == -1)
            cyclic_DFS(v, d + 1, u);
        
        low[u] = min(low[u], low[v]);
        
        if(low[v] <= d) 
            is_cyclic[u] = true;
    }
}

vector<int> short_path(int start) {
    vector<int> result(n+1, -1);
    queue<int> q;
    
    result[start] = 0;
    q.push(start);
    
    while(!q.empty()) {
        int curr = q.front(); q.pop();
        for(int v : inc[curr]) {
            if(result[v] != -1) continue;
            
            result[v] = result[curr] + 1;
            q.push(v);
        }
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m >> a >> b;
    
    int u, v;
    while(m--) {
        cin >> u >> v;
        inc[u].push_back(v);
        inc[v].push_back(u);
    }
    
    cyclic_DFS(a);
    
    vector<int> dist_a = short_path(a);
    vector<int> dist_b = short_path(b);
    
    for(int i = 1; i <= n; i++)
        if(is_cyclic[i] && (dist_a[i] < dist_b[i])) {
            cout << "NIE" << endl;
            return 0;
        }
    
    int best = 0;
    queue<int> q( {a} );
    while(!q.empty()) {
        int curr = q.front(); q.pop();
        best = max(best, dist_b[curr]);
        for(int v : inc[curr])
            if(!is_cyclic[v] && dist_a[v] > dist_a[curr])
                q.push(v);
    }
    
    cout << best << endl;
    
    return 0;
}
