#include <bits/stdc++.h>
using namespace std;

#define REP(i, x) for(int i = 0; i < x; i++)
#define FOR(i, x) for(int i = 1; i <=x; i++)
#define PB push_back

const int MAX_N = 5020;

int n;
vector<int> graph[MAX_N];
stack<int> result;
bool visited[MAX_N];

void start(int nr, int type) {
    visited[nr] = true;
    
    if(type == 1) result.push(nr);
    for(int neighbour : graph[nr]) 
        if(visited[neighbour] == false)
            start(neighbour, 1-type);
    if(type == 0) result.push(nr);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    REP(i, n-1) {
        int a, b;
        cin >> a >> b;
        graph[a].PB(b);
        graph[b].PB(a);
    }
    start(1, 1);
    while(!result.empty()) {
        cout << result.top() << endl;
        result.pop();
    }
    return 0;
}
