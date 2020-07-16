#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100100
#define MAX_K 202

vector<int> graph[MAX_N];
int sphinx[MAX_N];

int visited[MAX_N];
bool needs_be[MAX_K];
int epoc[MAX_N];

bool can_reach(int start, int end, int max_weight) {
    visited[start] = max_weight + 1;
    
    if (sphinx[start] > max_weight && !needs_be[sphinx[start]])
        return false;
    if (sphinx[end] > max_weight && !needs_be[sphinx[end]])
        return false;
        
    if (start == end) 
        return true;
        
    for (int neighbour : graph[start]) {
        if (visited[neighbour] != max_weight + 1
            && can_reach(neighbour, end, max_weight))
            return true;
    }
    
    return false;
}

vector< vector<int> > get_pows() {
    vector<int> digits(100, 0);
    digits[0] = 1;
    
    vector< vector<int> > pows(1, digits);
    for (int i = 1; i < MAX_K; i++) {
        vector<int> new_num(pows[i-1]);
        for (int &i : new_num)
            i *= 2;
        for (size_t i = 0; i < new_num.size() - 1; i++)
            if (new_num[i] >= 10) {
                new_num[i] -= 10;
                new_num[i+1]++;
            }
        pows.push_back(new_num);
    }
    
    return pows;
}

vector<int> build_solution(vector<vector<int>> pows, bool needed[]) {
    vector<int> solv(100, 0);
    for (int i = 0; i < MAX_K; i++) {
        if (needed[i] == false) continue;
        
        for (size_t j = 0; j < pows[i].size() - 1; j++) {
            solv[j] += pows[i][j];
            if (solv[j] >= 10) {
                solv[j] -= 10;
                solv[j+1]++;
            }
        }
    }
    
    while(solv.back() == 0) solv.pop_back();
    return solv;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int n, m, s, t, k;
    cin >> n >> m >> s >> t >> k;
    
    for (int i = 1; i <= n; i++)
        cin >> sphinx[i];
        
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    for (k; k >= 0; k--) {
        if (can_reach(s, t, k-1) == false)
            needs_be[k] = true;
    }
    
    vector< vector<int> > pows = get_pows();
    vector<int> solv = build_solution(pows, needs_be);
    
    while(!solv.empty()) {
        cout << solv.back();
        solv.pop_back();
    }
    cout << endl;
    
    return 0;
}
